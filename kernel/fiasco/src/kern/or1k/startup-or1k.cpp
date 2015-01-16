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
    printf("\nEntering: Startup::stage1\n");
    Mem_layout::add_pmem(Mem_layout::Ram_phys_base, Mem_layout::Map_base, 4<<20);
    Proc::cli();
    Boot_info::init();
    Cpu::early_init();
    Config::init();
    printf("Done: Startup::stage1\n");
}

IMPLEMENT FIASCO_INIT FIASCO_NOINLINE
void
Startup::stage2()
{
  Cpu_number const boot_cpu = Cpu_number::boot_cpu();
  printf("Entering: Startup::stage2\n");
  Mem_space::init_page_sizes();
  printf("Startup::stage2: Mem_space finished \n");

  Kip_init::init();
  printf("Startup::stage2: Kip_init finished \n");
  Kmem_alloc::init();
  printf("Startup::stage2: Kmem_alloc finished \n");

  // Initialize cpu-local data management and run constructors for CPU 0
  Per_cpu_data::init_ctors();
  Per_cpu_data_alloc::alloc(boot_cpu);
  Per_cpu_data::run_ctors(boot_cpu, false);

  //Kmem_space::init();
  Kernel_task::init();


  //only do the stuff as the sparc leon port


  //Mem_space::kernel_space(Kernel_task::kernel_task());
  //
  //Pic init is not doing anything in the kern folder
  //Pic::init();
  //Thread::init_per_cpu(boot_cpu, false);

  //Cpu::init_mmu();
/*  Cpu::cpus.cpu(boot_cpu).init(false, true); */
  //Cpu::cpus.cpu(boot_cpu).init(true);
  //Platform_control::init(boot_cpu);
  //Fpu::init(boot_cpu, false);
  //Ipi::init(boot_cpu);
  //Timer::init(boot_cpu);
  Timer::init((Cpu_number) 0);
  //Kern_lib_page::init();
  Utcb_init::init();
  printf("Startup::stage2 finished\n");
}
