#ifndef CPU_H_
#define CPU_H_

#include <types.h>

typedef struct {
	char brand[49];
} cpu_t;

void cpu_detect(void);

u32 cpu_count(void);
const cpu_t *cpu_get(u32 n);

#endif /* CPU_H_ */
