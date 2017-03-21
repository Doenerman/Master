#ifndef _TIMING_H
#define _TIMING_H

#define get_ticks(var) {                       \
      unsigned int __a, __d;                       \
      asm volatile("rdtsc" : "=a" (__a), "=d" (__d));          \
      var = ((unsigned long) __a) | (((unsigned long) __d) << 32); \
   } while(0)

#endif // _TIMING_H
