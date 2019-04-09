/**************************************************************************/
/* @filename CFork.h
/* @author Victor Flores 
/* @date 2019/04/05
/* @brief 
/**************************************************************************/
#pragma once
#include <mutex>

/**
 * @brief 
 */
class CFork
{
public:

  /**
   * @brief Default constructor
   */
  CFork();

  /**
   * @brief Copy constructor
   */
  CFork(const CFork& other);

  /**
   * @brief Default constructor
   */
  ~CFork();

  /************************************************************************/
  /* Methods                                                              */
  /************************************************************************/

  /**
   * @brief Lock by a low priority thread
   */
  void
    LowPrioLock();

  /**
   * @brief Lock by a high priority thread
   */
  void
    HighPrioLock();

  /**
   * @brief Unlock by a low priority thread
   */
  void
    LowPrioUnlock();

  /**
   * @brief Unlock by a high priority thread 
   */
  void
    HighPrioUnlock();

  
  std::mutex m_mutex1;

  std::mutex m_mutex2;

  std::mutex m_mutex3;

  /**
   * @brief id for the fork 
   */
  int id;

}; 

