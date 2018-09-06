#ifndef CPUID_H
#define __CPUID_H

#include <stdint.h>

/* checks if processor supports CPUID instructions */
int check_cpuid_support(void);

/* returns highest possible value CPUID can recognize for processor information */
uint32_t cpuid_highest_input(void);

/* returns a C-string that defines the vendor of CPU */
const char * cpuid_vendor(void);

/* returns an enum that defines the microarchitecuture of the CPU */
const char * cpuid_microarch(void);

#endif
