/**
 * @file on_loop_repeat.h
 * @author Daniel Polanco (jpolanco@getinsoft.com)
 * @brief KernelTask func type declaration
 * @version 1.0
 * @date 2020-01-06
 * 
 */
#ifndef ON_LOOP_REPEAT_H
#define ON_LOOP_REPEAT_H

/**
 * @brief [Type] Represents a function that repeats on every loop function execution
 * 
 */
typedef void (*KernelTask)(void *);

#endif // !ON_LOOP_REPEAT_H