/**************************************************************************/
/* @filename CPhilosopher.h
/* @author Victor Flores 
/* @date 2019/04/05
/* @brief 
/*************************************************************************/

#pragma once

#include "CFork.h"
#include <random>
#include <atomic>
#include <iostream>

class CTable;

/**
 * @brief Enumerator for the Type of the Person, pupil or philosopher
 */
namespace PERSON_TYPE {
  enum E
  {
    kPhilosopher = 0,
    kPupil,
    kNumPersona
  };
}

/**
 * @brief Enumerator for the states of the philosopher or pupil
 */
namespace STATE {
  enum E
  {
    kEating = 0,
    kThink,
    kFull,
    kNumStates
  };
}


class CPhilosopher
{
public:

  /**
   * @brief Constructor of the philosopher class
   */
  CPhilosopher( PERSON_TYPE::E _type,
                CFork * _leftFork,
                CFork* _rightFork,
                int m_id,
                CTable * table,
                int tieme);

  /**
   * @brief Destructor of the philosopher class
   */
  ~CPhilosopher();

  /**
   * @brief Loop of the philosopher class
   */
  void
    Run();

  /**
   * @brief Atomic variable used by the philosophers or pupil to know if its full 
   */
  std::atomic<bool> m_isFull;
 
  /**
   * @brief Member variable used to know if is a pupil or a philosopher
   */
  PERSON_TYPE::E m_personType;

private:

  /**
   * @brief Function used by the  philosophers or the pupils to eat
   */
  void
    Eating();

  /**
   * @brief Function used by the  philosophers or the pupils to eat
   */
  void
    Thinking();

  /**
   * @brief Function used by the  philosophers or the pupils to eat
   */
  void
    Full();

  /**
   * @brief Reference to the fork class used as left fork 
   */
  CFork * m_leftFork;

  /**
   * @brief Reference to the fork class used as right fork
   */
  CFork * m_rightFork;

  /**
   * @brief Current state of the philosopher or the pupil 
   */
  STATE::E m_currentState;

  /**
   * @brief Variable used for random
   */
  std::mt19937 rng { std::random_device{}( ) };

  /**
   * @brief Num of the philosopher or the pupil 
   */
  int m_id;

  /**
   * @brief String variable to print if is a philosopher or a pupil 
   */
  std::string m_nameLog;

  /**
   * @brief Variable wich determinates how many times has eat
   */
  int m_eatTimes;

  /**
   * @brief Variable wich determinates how many times can eat
   */
  int m_timesCanEat;

  /**
   * @brief Times that the person can eat
   */
  int m_timeToThink;

  /**
   * @brief Reference to the table 
   */
  CTable * m_table;

public:
  std::thread m_thread;
};

