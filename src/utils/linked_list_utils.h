#if !defined(AGRICOS_KERNEL_LINKED_LIST_UTIL_H)
#define AGRICOS_KERNEL_LINKED_LIST_UTIL_H

#define _for_each(__list, __iterator, __type) \
  __type __iterator = __list.get(0);         \
  for (int i = 0; i < __list.size(); i++, __iterator = __list.get(i))

#define for_in_range(__type, __iterator, __min_range, __max_range) for (__type __iterator = (__min_range); (__iterator) < (__max_range); (__iterator)++)

#endif // AGRICOS_KERNEL_LINKED_LIST_UTIL_H
