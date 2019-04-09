/**************************************************************************/
/* @filename CPhilosopher.cpp
/* @author Victor Flores 
/* @date 2019/04/05
/* @brief 
/**************************************************************************/
#include "CPhilosopher.h"

#include "CTable.h"

#include <iostream>

#include "Utilities.h"



CPhilosopher::CPhilosopher( PERSON_TYPE::E _type, 
                            CFork * _leftFork,
                            CFork * _rightFork, 
                            int _id,
                            CTable * _table,
                            int time) :
  m_personType(_type),
  m_leftFork(_leftFork),
  m_rightFork(_rightFork),
  m_id(_id),
  m_currentState(STATE::kThink),
  m_table (_table),
  m_eatTimes(0),
  m_isFull(false),
  m_timeToThink(time),
  m_thread(&CPhilosopher::Run, this) {

  //Defines if the namelog is going to be Philosopher or Pupil
  if (m_personType == PERSON_TYPE::kPhilosopher)
  {
    m_nameLog = "Philosopher ";
    m_timesCanEat = 5;
  }
  else
  {
    m_nameLog = "Pupil ";
    m_timesCanEat = 2;
  }
}


CPhilosopher::~CPhilosopher()
{
  //Waits for all the threads to end 
  m_thread.join();
}

/**
 * @brief main loop 
 */
void 
CPhilosopher::Run()
{
  while ( !m_table->m_run );

  while ( m_table->m_run )
  {
     switch ( m_currentState )
     {
     case STATE::kEating: //if is eating calls the eating function
       Eating();
       break;
     case STATE::kThink: //if is think calls the thinking function
       Thinking();
       break;
     case STATE::kFull: //if is full calls the full function
       Full();
       break;

     default:
       break;
     }
  }
}


//Function for eating 
void 
CPhilosopher::Eating()
{

  switch ( m_personType )
  {
  case PERSON_TYPE::kPhilosopher:
    m_leftFork->HighPrioLock();
    m_rightFork->HighPrioLock();
    break;
  case PERSON_TYPE::kPupil:
    m_leftFork->LowPrioLock();
    m_rightFork->LowPrioLock();
    break;
  }

  Log( m_nameLog + std::to_string( m_id ) + " started eating" );
 
  static thread_local std::uniform_int_distribution<> dist( 1, 6 );
  std::this_thread::sleep_for( std::chrono::milliseconds( dist( rng ) * 50 ) );

  Log( m_nameLog + std::to_string( m_id ) + " finishes eating" );

  m_eatTimes++;

  Log( m_nameLog + 
       std::to_string( m_id ) + 
       " has eaten " + 
       std::to_string(m_eatTimes) +
       " times" );

  if (m_eatTimes >= m_timesCanEat)
  {
    m_isFull = true;
    m_currentState = STATE::kFull;
  }
  m_currentState = STATE::kThink;

  switch ( m_personType )
  {
  case PERSON_TYPE::kPhilosopher:
    m_leftFork->HighPrioUnlock();
    m_rightFork->HighPrioUnlock();
    break;
  case PERSON_TYPE::kPupil:
    m_leftFork->LowPrioUnlock();
    m_rightFork->LowPrioUnlock();
    break;
  }

}

//function for thinking
void 
CPhilosopher::Thinking()
{
  static thread_local std::uniform_int_distribution<> wait( 1, 6 );
  std::this_thread::sleep_for( std::chrono::milliseconds( wait( rng ) * m_timeToThink ) );

  Log( m_nameLog + std::to_string( m_id ) + " is thinking" );

  if (!m_isFull)
  {
    m_currentState = STATE::kEating;
  }
  else
  {
    m_currentState = STATE::kFull;
  }
}

//funtion for filled person
void 
CPhilosopher::Full()
{
  static thread_local std::uniform_int_distribution<> wait( 1, 6 );
  std::this_thread::sleep_for( std::chrono::milliseconds( wait( rng ) * 150 ) );
  Log( m_nameLog + std::to_string( m_id ) + " is full" );

  
  m_eatTimes--;
  
  if (m_eatTimes <= 0)
  {
    m_currentState = STATE::kEating;
    m_isFull = false;
    std::cout << m_nameLog.c_str() << m_id << " is Hungry again." << std::endl;
  }
}

