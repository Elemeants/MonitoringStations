#ifndef KERNEL_MODULE_LOADER_H
#define KERNEL_MODULE_LOADER_H

#include "utils/linked_list.h"
#include "utils/linked_list_utils.h"

template <typename T>
struct IRegister
{
protected:
  LinkedList<T> bus;

public:
  virtual void add(T item)
  {
    bus.add(item);
  }

  virtual void run() = 0;
};

#endif // !KERNEL_MODULE_LOADER_H