#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/seq_file.h>
#include <linux/errno.h>

#include <asm/irq.h>
#include <asm/machdep.h>
#include <asm/traps.h>

asmlinkage void system_call(void);
asmlinkage irqreturn_t bad_interrupt(int, void *, struct pt_regs *);
asmlinkage irqreturn_t inthandler1(void);
asmlinkage irqreturn_t inthandler2(void);
asmlinkage irqreturn_t inthandler3(void);
asmlinkage irqreturn_t inthandler4(void);
asmlinkage irqreturn_t inthandler5(void);
asmlinkage irqreturn_t inthandler6(void);
asmlinkage irqreturn_t inthandler7(void);

volatile unsigned int num_spurious;
unsigned int local_irq_count[NR_CPUS];

void init_IRQ(void)
{
        /*
         * rosco_m68k uses the MC68010 autovector interrupt inputs.
         *
         * Vector-table installation will be added after the initial
         * kernel build succeeds.
         */
}

int request_irq(unsigned int irq,
                irqreturn_t (*handler)(int, void *, struct pt_regs *),
                unsigned long flags,
                const char *devname,
                void *dev_id)
{
        return -ENXIO;
}

void free_irq(unsigned int irq, void *dev_id)
{
}

int show_interrupts(struct seq_file *p, void *v)
{
        return 0;
}

void process_int(int vec, struct pt_regs *fp)
{
        printk(KERN_ERR "rosco_m68k: unexpected interrupt vector %d\n", vec);
}

/*
 * /proc/interrupts initialization hook.
 * Real rosco_m68k IRQ support will be added later.
 */
void init_irq_proc(void)
{
}
