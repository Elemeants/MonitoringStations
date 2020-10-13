#if !defined(REGISTERS_TASK_REGISTER_H)
#define REGISTERS_TASK_REGISTER_H

#include "types/register.h"
#include "utils/linked_list_utils.h"

typedef void (*ITaskRegisterFunc)(void);

class _ITaskRegister : public IRegister<ITaskRegisterFunc>
{
public:
  void run()
  {
    _for_each(bus, task, ITaskRegisterFunc)
      task();
  }
};

#endif // REGISTERS_TASK_REGISTER_H
