#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/pm.h>

#include <asm/system.h>
#include <asm/machdep.h>

void (*pm_power_off)(void) = NULL;

static void rosco_sched_init(
        irqreturn_t (*timer_routine)(int, void *, struct pt_regs *))
{
        /*
         * Timer hardware will be added after the basic kernel
         * builds and links.
         */
}

static void rosco_tick(void)
{
}

static unsigned long rosco_gettimeoffset(void)
{
        return 0;
}

static void rosco_gettod(int *yearp, int *monp, int *dayp,
                         int *hourp, int *minp, int *secp)
{
        *yearp = 0;
        *monp  = 0;
        *dayp  = 0;
        *hourp = 0;
        *minp  = 0;
        *secp  = 0;
}

static void rosco_reset(void)
{
        local_irq_disable();

        for (;;)
                ;
}

void config_BSP(char *command, int len)
{
        printk(KERN_INFO "\nrosco_m68k Classic MC68010 support\n");

        mach_sched_init     = rosco_sched_init;
        mach_tick           = rosco_tick;
        mach_gettimeoffset  = rosco_gettimeoffset;
        mach_gettod         = rosco_gettod;
        mach_hwclk          = NULL;
        mach_set_clock_mmss = NULL;
        mach_reset          = rosco_reset;

        *command = '\0';
}
