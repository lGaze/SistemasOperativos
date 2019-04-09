/**************************************************************************/
/* @filename CFork.cpp
/* @author Victor Flores 
/* @date 2019/04/05
/* @brief 
/**************************************************************************/

#include "CFork.h"

/**
 * @brief default constructor 
 */
CFork::CFork() 
{
  id = 0;
}

/**
 * @brief constructor 
 */
CFork::CFork( const CFork & other ) : id(other.id)
{
}

/**
 * @brief default destructor
 */
CFork::~CFork()
{
}

/**
 * @brief low priority lock for pupils 
 */
void CFork::LowPrioLock()
{
  m_mutex1.lock();
  m_mutex2.lock();
  m_mutex3.lock();

  m_mutex2.unlock();

}

/**
 * @brief high priority lock for philosophers 
 */
void CFork::HighPrioLock()
{

  m_mutex1.lock();
  m_mutex2.lock();

  m_mutex2.unlock();
}

/**
 * @brief low priority unlock for pupils 
 */
void CFork::LowPrioUnlock()
{
  m_mutex1.unlock();
  m_mutex3.unlock();
}

/**
 * @brief Hiigh priority unlock for philosophers 
 */
void CFork::HighPrioUnlock()
{
  m_mutex1.unlock();
}
