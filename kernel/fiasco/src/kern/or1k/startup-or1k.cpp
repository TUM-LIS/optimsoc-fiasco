IMPLEMENTATION [or1k]:

#include "boot_info.h"
#include "config.h"
#include "cpu.h"
#include "fpu.h"
#include "ipi.h"
//#include "kern_lib_page.h"
#include "kernel_task.h"
#include "kip_init.h"
#include "kmem_alloc.h"
//#include "kmem_space.h"
#include "mem_space.h"
#include "mem_layout.h"
#include "per_cpu_data.h"
#include "per_cpu_data_alloc.h"
#include "perf_cnt.h"
//#include "pic.h"
#include "platform_control.h"
#include "processor.h"
#include "static_init.h"
#include "thread.h"
#include "timer.h"
#include "utcb_init.h"

#include <cstdlib>
#include <cstdio>

IMPLEMENT FIASCO_INIT FIASCO_NOINLINE
void
Startup::stage1()
{
  Proc::cli();
  Boot_info::init();
  Cpu::early_init();
  Config::init();
}

IMPLEMENT FIASCO_INIT FIASCO_NOINLINE
void
Startup::stage2()
{
  Kip_init::init();
 //init buddy allocator
 Kmem_alloc::init();
 // Initialize cpu-local data management and run constructors for CPU 0
 Per_cpu_data::init_ctors();
 // not really necessary for uni processor
 //Per_cpu_data_alloc::alloc(0);
 //Per_cpu_data::run_ctors();
// Cpu::cpus.cpu(0).init(true);
 //idle task
 Kernel_task::init();
// Pic::init();
// Timer::init(0);
 Utcb_init::init();
}
