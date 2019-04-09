/**************************************************************************/
/* @filename CTable.cpp
/* @author Victor Flores 
/* @date 2019/04/05
/* @brief 
/*************************************************************************/
#include "CTable.h"

#include <iostream>



CTable::CTable() :
  m_run( false )
{
}


CTable::~CTable()
{
}

/**
 * @brief entry point of the table 
 */
int CTable::Run()
{
  Init();

  std::thread thr( &CTable::CheckThreads, this );

  m_run = true;
  std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
  m_run = false;

  thr.join();
  destroy();
  system( "pause" );

  return 0;
}

/**
 * @brief Initializes all the vectors
 */
bool CTable::Init()
{
  std::cout << "How many philosophers" << std::endl;
  std::cin >> m_numPhilosophers;

  std::cout << "How many pupils" << std::endl;
  std::cin >> m_numPupils;

  m_numForks = m_numPhilosophers + m_numPupils;

  //FORKS
  for (int i = 0; i< m_numForks; i++)
  {
    CFork * f = new CFork();
    f->id = i;
    m_forks.push_back( f );
  }

  //PHILOSOPHER
  for ( int i = 0; i < m_numPhilosophers; i++ )
  {
      CPhilosopher * p = new CPhilosopher( PERSON_TYPE::kPhilosopher,
                                         m_forks[( i ) % m_forks.size()],
                                         m_forks[( i + m_forks.size() - 1 ) % m_forks.size()],
                                         i,
                                         this,
                                         100 );
    m_philosophers.push_back( p );
  }

  //PUPIL
  for ( int i = 0; i < m_numPupils; i++)
  {
    CPhilosopher * p = new CPhilosopher( PERSON_TYPE::kPupil,
                                         m_forks[( i ) % m_forks.size()],
                                         m_forks[( i + m_forks.size() - 1 ) % m_forks.size()],
                                         i,
                                         this,
                                         500 );
    m_pupil.push_back( p );

  }

  return true;
}

/**
 * @brief Check the threads to change the prio queue
 */
void CTable::CheckThreads()
{
  while ( m_run )
  {
    int i = 0;

    for (auto& it : m_philosophers)
    {
      if (it->m_isFull)
      {
        CPhilosopher * temp = it;
        m_philosophers.erase( m_philosophers.begin() + i );
        m_fullfiled.push_back( temp );
      }
      ++i;
    }
    i = 0;
    for ( auto& it : m_pupil)
    {
      if (it->m_isFull)
      {
        CPhilosopher * temp = it;
        m_pupil.erase( m_pupil.begin() + i );
        m_fullfiled.push_back( temp );
      }
      ++i;
    }
    i = 0;
    for (auto& it : m_fullfiled )
    {
      if (!(it->m_isFull))
      {
        CPhilosopher * temp = it;
        m_fullfiled.erase( m_fullfiled.begin() + i );
        if (it->m_personType == PERSON_TYPE::kPhilosopher)
        {
          m_philosophers.push_back( temp );
        }
        if ( it->m_personType == PERSON_TYPE::kPupil )
        {
          m_pupil.push_back( temp );
        }
      }
      ++i;
    }


  }
}

/**
 * @brief Destroys all the pointers 
 */
void CTable::destroy()
{
  for ( auto & it : m_philosophers )
  {
    delete it;
  }

  for ( auto & it : m_pupil )
  {
    delete it;
  }

  for ( auto & it : m_fullfiled )
  {
    delete it;
  }
  m_fullfiled.clear();
  m_pupil.clear();
  m_philosophers.clear();

}
