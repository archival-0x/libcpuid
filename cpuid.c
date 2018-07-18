#define _GNU_SOURCE
#define __USE_LARGEFILE64
#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE

#include <stdint.h>
#include <string.h>
#include <python2.7/Python.h>

static const uint32_t 
valid_pmu_cpu_type[100] = {
    0x006F0, 0x10660 // IntelMerom
     
};


static inline void 
cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
    asm volatile("cpuid"
       : "=a" (*eax),
         "=b" (*ebx),
         "=c" (*ecx),
         "=d" (*edx)
       : "0" (*eax), "2" (*ecx));
}


static uint32_t
cpuid_processor_info()
{   
    /* temporary registers to hold results */
    uint32_t eax, ebx, ecx, edx;

    /* eax = 1 for processor information */
    eax = 1;
    cpuid( &eax, &ebx, &ecx, &edx );
    
    /* return signature, must be unmasked */
    return eax;
}


static void
cpuid_vendor(char * name)
{   
    /* set 12th char to 0 */
    name[12] = 0;    

    /* eax = 0 for vendor */
    uint32_t eax;
    eax = 0;    

    cpuid( &eax, (uint32_t *) &name[0], (uint32_t *) &name[8], (uint32_t *) &name[4] );
}


static PyObject* 
rrinit_check_cpuid(PyObject* self, PyObject* args)
{
    
    /* check vendor: only Intel and AMD processors supported */
    char vendor[13];
    cpuid_vendor(vendor);

    if (strcmp(vendor, "GenuineIntel") && strcmp(vendor, "AuthenticAMD")) {
        PyErr_Print(    
    }

    /* check CPU microarchitecture through unmask */
    uint32_t cpuid_data = cpuid_processor_info();
    uint32_t cpu_type = cpuid_data & 0xF0FF0;
} 
