#pragma once

#include <stdint.h>
#include "io.h"

typedef struct {
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers;

extern void hang(void);

#define X86

#define __ASSERT(b, file, func, line)                                          \
	do {                                                                   \
		if (!(b)) {                                                    \
			writef("Assertion failed in file %s in function %s "   \
			       "on line %d.\n",                                \
			       file, func, line);                              \
			hang();                                                \
		}                                                              \
	} while (0);
#define ASSERT(b) __ASSERT(b, __FILE__, __FUNCTION__, __LINE__);

#define __PANIC(file, func, line)                                              \
	do {                                                                   \
		writef("Panic in file %s in function %s on line %d.\n", file,  \
		       func, line);                                            \
		hang();                                                        \
	} while (0);
#define PANIC() __PANIC(__FILE__, __FUNCTION__, __LINE__);

#ifdef DEBUG
#define __LOG(s, file, func, line, ...)                                        \
	do {                                                                   \
		writef("[Log (%s %s %d)]: ", file, func, line);                \
		writef(s "\n", ##__VA_ARGS__);                                 \
	} while (0);
#define LOG(s, ...) __LOG(s, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define __LOG(s, file, func, line)
#define LOG(s)
#endif

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof(*(arr)))
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) < (y) ? (y) : (x))
