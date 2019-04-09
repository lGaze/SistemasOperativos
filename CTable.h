/**************************************************************************/
/* @filename CTable.h
/* @author Victor Flores 
/* @date 2019/04/05
/* @brief 
/**************************************************************************/
#pragma once
#include <vector>

#include "CPhilosopher.h"

using namespace PERSON_TYPE;
using namespace STATE;

class CTable
{
public:

  std::atomic<bool> m_run;

  /**
   * @brief Default constructor for the table class
   */
  CTable();

  /**
   * @brief Default destructor for the table class
   */
  ~CTable();

  /**
   * @brief Main loop of the table class
   */
  int 
    Run();

  /**
   * @brief Function wich initializes the vectors of the pupils and philosophers
   */
  bool
    Init();

  /**
   * @brief Function wich checks if the philosophers or the pupils are full 
   */
  void
    CheckThreads();

private:

  /**
   * @brief Vector that stores the philosophers 
   */
  std::vector<CPhilosopher*> m_philosophers;

  /**
   * @brief Vector that stores the pupils 
   */
  std::vector<CPhilosopher*> m_pupil;

  /**
   * @brief Vector that stores the philosophers or the pupils that are full
   */
  std::vector<CPhilosopher*> m_fullfiled;

  /**
   * @brief Vector that stores all the forks in the table
   */
  std::vector<CFork*> m_forks;

  /**
   * @brief Number of the requested philosophers
   */
  int m_numPhilosophers;

  /**
   * @brief Number of the requested pupils 
   */
  int m_numPupils;

  /**
   * @brief Number of the requested forks 
   */
  int m_numForks;

  /**
   * @brief Function that destroys all the pointers
   */
  void destroy();


};

