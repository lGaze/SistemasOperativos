// Filosofos_Final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Utilities.h"
#include "CTable.h"
#include <iostream>


/**
 * @brief Mutex for log
 */
std::mutex logMutex;

void
Log( std::string a )
{
  std::lock_guard<std::mutex> semaphore( logMutex );
  std::cout << a << std::endl;
}



int main()
{
  CTable a;
  return a.Run();
}
