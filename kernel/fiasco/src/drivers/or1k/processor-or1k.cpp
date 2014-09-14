#include "types.h"
#include "spr.h"
#include "processor.h"

IMPLEMENTATION [or1k]:

EXTENSION class Proc
{
public:
 static Cpu_phys_id cpu_id();
};

/// Unblock external interrupts
IMPLEMENT static inline
void Proc::sti()
{
  unsigned p = Spr_Sr::read();
  //NOT_IMPL_PANIC
	asm ("l.sys 0x0815");
  Spr_Sr::write(p);
}

/// Block external interrupts
IMPLEMENT static inline
void Proc::cli()
{
  unsigned p = Spr_Sr::read();
/*  p |= (0xF << Spr_Sr::Interrupt_lvl); */
	asm volatile ("l.sys 0x0815");
  Spr_Sr::write(p);
}

/// Are external interrupts enabled ?
IMPLEMENT static inline
Proc::Status Proc::interrupts()
{
/*  return Spr_Sr::read() & (0xF << Spr_Sr::Interrupt_lvl); */
	asm volatile ("l.sys 0x0815");
	return Spr_Sr::read();
}

/// Block external interrupts and save the old state
IMPLEMENT static inline
Proc::Status Proc::cli_save()
{
  Status ret = Spr_Sr::read();
  Proc::cli();
  return ret;
}

/// Conditionally unblock external interrupts
IMPLEMENT static inline
void Proc::sti_restore(Status status)
{
  (void)status;
  Spr_Sr::write(status);
}

IMPLEMENT static inline
void Proc::pause()
{
  // XXX
}

IMPLEMENT static inline
void Proc::halt()
{
  // XXX
/*  asm volatile ("ta 0\n"); */
	asm volatile ("l.sys 0x0815");
}

/*IMPLEMENT static inline */
/*Mword Proc::wake(Mword srr1) */
/*{ */
/*  (void)srr1; */
/*  return 0; // XXX */
/*} */

IMPLEMENT static inline
void Proc::irq_chance()
{
  // XXX?
/*  asm volatile ("nop; nop;" : : :  "memory"); */
	asm volatile ("l.sys 0x0815");
}

IMPLEMENT static inline
void Proc::stack_pointer(Mword sp)
{
  (void)sp;
/*  asm volatile ("mov %0, %%sp\n" : : "r"(sp)); */
	asm volatile ("l.sys 0x0815");
}

IMPLEMENT static inline
Mword Proc::stack_pointer()
{
  Mword sp = 0;
/*  asm volatile ("mov %%sp, %0\n" : "=r" (sp)); */
	asm volatile ("l.sys 0x0815");
  return sp;
}

IMPLEMENT static inline
Mword Proc::program_counter()
{
  Mword pc = 0;
/*  asm volatile ("call 1\n\t" */
/*                "nop\n\t" // delay instruction */
/*		"1: mov %%o7, %0\n\t" */
/*		: "=r" (pc) : : "o7"); */
	asm volatile ("l.sys 0x0815");
  return pc;
}

PUBLIC static inline
template <int ASI>
Mword Proc::read_alternative(Mword reg)
{
	Mword ret;
/*	asm volatile("lda [%1] %2, %0" */
/*				  : "=r" (ret) */
/*				  : "r" (reg), */
/*				    "i" (ASI)); */
	asm volatile ("l.sys 0x0815");
	return ret;

}

PUBLIC static inline
template <int ASI>
void Proc::write_alternative(Mword reg, Mword value)
{
/*	asm volatile ("sta %0, [%1] %2\n\t" */
/*				  : */
/*				  : "r"(value), */
/*				    "r"(reg), */
/*				    "i"(ASI)); */
	asm volatile ("l.sys 0x0815");
}


IMPLEMENTATION [sparc && !mpcore]:

IMPLEMENT static inline
Cpu_phys_id Proc::cpu_id()
{ return Cpu_phys_id(0); }


