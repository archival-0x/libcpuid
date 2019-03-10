#include "cpuid.h"

/* inline assembly interface to cpuid */
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


/* checks for CPUID support */
int
check_cpuid_support(void)
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

    if (((pre_change ^ post_change) & id_flag) == 0)
        return 1;
    else
        return 0;
}


/* returns highest input value recognizable by CPUID in
 * eax register
 *      eax = 0
 */
uint32_t
cpuid_highest_input(void)
{
    /* eax = 0 for highest value */
    uint32_t eax, ebx, ecx, edx;
    eax = 0;

    /* call cpuid, storing output in eax */
    cpuid(&eax, &ebx, &ecx, &edx);
    return eax;
}


/* stores vendor string in provided char pointer
 *      eax = 0
 */
const char *
cpuid_vendor(void)
{
    char name[13];

    /* set 12th char to 0 */
    name[12] = 0;

    /* eax = 0 for vendor */
    uint32_t eax;
    eax = 0;

    /* call cpuid, storing output in ebx, edx, and ecx */
    cpuid(&eax, (uint32_t *) &name[0], (uint32_t *) &name[8], (uint32_t *) &name[4]);

    if (strcmp(vendor, "GenuineIntel") == 0)
       return "Intel";
    else if (strcmp(vendor, "AuthenticAMD") == 0)
        return "AMD";
    else if (strcmp(vendor, "CentaurHauls") == 0)
        return "Centaur";
    else if (strcmp(vendor, "CyrixInstead") == 0)
        return "Cyrix";
    else if (strcmp(vendor, "HygonGenuine") == 0)
        return "Hygon";
    else if (strcmp(vendor, "TransmetaCPU") == 0)
        return "Transmeta";
    else if (strcmp(vendor, "Geode by NSC") == 0)
        return "NSC";
    else if (strcmp(vendor, "NexGenDriven") == 0)
        return "NexGen";
    else if (strcmp(vendor, "RiseRiseRise") == 0)
        return "Rise";
    else if (strcmp(vendor, "SiS SiS SiS ") == 0)
        return "SiS";
    else if (strcmp(vendor, "UMC UMC UMC ") == 0)
        return "UMC";
    else if (strcmp(vendor, "VIA VIA VIA ") == 0)
        return "VIA";
    else if (strcmp(vendor, "Vortex86 SoC") == 0)
        return "Vortex";
    else
        return "Other";
}




/* returns processor information in eax register
 *      eax = 1
 *      bits = 8..11
 */
const char *
cpuid_microarch(void)
{

    /* temporary registers to hold results */
    uint32_t eax, ebx, ecx, edx;

    /* eax = 1 for processor information */
    eax = 1;

    /* use all registers for output consuming purposes. */
    cpuid(&eax, &ebx, &ecx, &edx);

    /* retrieve CPU microarchitecture with unmask */
    switch (eax & 0xF0FF0) {
        case 0x006F0:
        case 0x10660:
            return "IntelMerom";
        case 0x10670:
        case 0x106D0:
            return "IntelPenryn";
        case 0x106A0:
        case 0x106E0:
        case 0x206E0:
            return "IntelNehalem";
        case 0x20650:
        case 0x206C0:
        case 0x206F0:
            return "IntelWestmere";
        case 0x206A0:
        case 0x206D0:
        case 0x306e0:
            return "IntelSandyBridge";
        case 0x306A0:
            return "IntelIvyBridge";
        case 0x306C0:
        case 0x306F0:
        case 0x40650:
        case 0x40660:
            return "IntelHaswell";
        case 0x306D0:
        case 0x40670:
        case 0x406F0:
        case 0x50660:
            return "IntelBroadwell";
        case 0x406e0:
        case 0x50650:
        case 0x506e0:
            return "IntelSkylake";
        case 0x30670:
        case 0x50670:
            return "IntelSilvermont";
        case 0x806e0:
        case 0x906e0:
            return "IntelKabylake";
        case 0x00f10:
            return "AMDRyzen";
        default:
            return NULL;
    }
}
