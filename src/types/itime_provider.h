/**
 * @file itime_provider.h
 * @author Daniel Polanco (jpolanco@getinsoft.com)
 * @brief ITimeProvider declaration
 * @version 1.0
 * @date 2020-01-15
 * 
 */
#ifndef ITIME_PROVIDER_H
#define ITIME_PROVIDER_H

#include "../utils/datetime.h"

/**
 * @brief [Interface] Interface that declares an method to get the time
 * 
 */
struct ITimeProvider
{
  /**
   * @brief Get the Time
   * 
   * @return Time_s
   */
  virtual Time_s getTime() = 0;
  
  /**
   * @brief Update time provider
   * 
   * @return Time_s
   */
  virtual void update() = 0;
};

typedef struct ITimeProvider ITimeProvider;

#endif // !ITIME_PROVIDER_H