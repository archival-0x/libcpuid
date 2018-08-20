#ifndef CPUID_H
#define __CPUID_H

#include <stdint.h>

typedef enum {
        IntelTest,
        IntelTest2,
        IntelTest3
} CPUArch_t;


/* checks if processor supports CPUID instructions */
int check_cpuid_support();

/* returns a C-string that defines the vendor of CPU */
void cpuid_vendor(char * name);

/* returns an enum that defines the microarchitecuture of the CPU */
CPUArch_t cpuid_microarch();

#endif
