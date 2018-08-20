#include "cpuid.h"

static const uint32_t valid_pmu_cpu_type[25] = {
        0x106A0, 0x106E0, 0x206E0,          // IntelNehalem
        0x20650, 0x206C0, 0x206F0,          // IntelWestmere
        0x206A0, 0x206D0, 0x306e0,          // IntelSandyBridge
        0x306A0,                            // IntelIvyBridge
        0x306C0, 0x306F0, 0x40650, 0x40660, // IntelHaswell
        0x306D0, 0x40670, 0x406F0, 0x50660, // IntelBroadwell
        0x406e0, 0x50650, 0x506e0,          // IntelSkylake
        0x30670, 0x50670,                   // IntelSilvermont
        0x806e0, 0x906e0                    // IntelKabylake
};


/* checks for CPUID supports */
int check_cpuid_support()
{
        uint32_t pre_change, post_change;
        uint32_t id_flag = 0x200000;

        asm volatile("pushfl\n"          /* Save %eflags to restore later.  */
                     "pushfl\n"          /* Push second copy, for manipulation.  */
                     "popl %1\n"         /* Pop it into post_change.  */
                     "movl %1,%0\n"      /* Save copy in pre_change.   */
                     "xorl %2,%1\n"      /* Tweak bit in post_change.  */
                     "pushl %1\n"        /* Push tweaked copy... */
                     "popfl\n"           /* ... and pop it into %eflags.  */
                     "pushfl\n"          /* Did it change?  Push new %eflags... */
                     "popl %1\n"         /* ... and pop it into post_change.  */
                     "popfl"               /* Restore original value.  */
                    : "=&r" (pre_change), "=&r" (post_change)
                    : "ir" (id_flag));

        if (((pre_change ^ post_change) & id_flag) ==0)
            return 1;
        else
            return 0;
}


/* inline assembly interface to cpuid */
static inline void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}

/* returns processor information in eax register */
enum CPUArch_t cpuid_microarch()
{
        /* represents CPU microarchitecture */
        uint32_t cpu_arch;

        /* temporary registers to hold results */
        uint32_t eax, ebx, ecx, edx;

        /* eax = 1 for processor information */
        eax = 1;

        /* use all registers for output consuming purposes. */
        cpuid(&eax, &ebx, &ecx, &edx);

        /* retrieve CPU microarchitecture with unmask */
        cpu_arch = eax & 0xF0FF0;

        /* TODO: interpre cpu_arch */
}

/* stores vendor string in provided char pointer */
void cpuid_vendor(char * name)
{
        /* set 12th char to 0 */
        name[12] = 0;

        /* eax = 0 for vendor */
        uint32_t eax;
        eax = 0;

        /* call cpuid, storing output in ebx, edx, and ecx */
        cpuid(&eax, (uint32_t *) &name[0], (uint32_t *) &name[8], (uint32_t *) &name[4]);
}
