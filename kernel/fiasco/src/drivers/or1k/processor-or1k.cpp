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
// Enable interrupts
IMPLEMENT static inline
void Proc::sti()
{
  unsigned p = Spr_Sr::read();
	p |= Spr_Sr::Spr_Sr_bits::IEE;
  Spr_Sr::write(p);
}

/// Block external interrupts
// Disable interrupts
IMPLEMENT static inline
void Proc::cli()
{
  unsigned p = Spr_Sr::read();
	p &= ~Spr_Sr::Spr_Sr_bits::IEE;
  Spr_Sr::write(p);
}

/// Are external interrupts enabled ?
IMPLEMENT static inline
Proc::Status Proc::interrupts()
{
	return Spr_Sr::read() & Spr_Sr::Spr_Sr_bits::IEE;
}

/// Block external interrupts and save the old state
// Locks more like, block external interrupts and return old state
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
	// enable interrupts, otherwise would be hard to wake up?
	// Tick Timer Exception and
	// Interrupt Exception
  unsigned p = Spr_Sr::read();
	p = p |  Spr_Sr::Spr_Sr_bits::IEE | Spr_Sr::Spr_Sr_bits::TEE;
  Spr_Sr::write(p);
	// Power Management is optional, so how to sleep?
	// forever nop?
	for (;;)
	{
		asm volatile ("l.nop");
	}
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
  asm volatile ("l.nop");
}

IMPLEMENT static inline
void Proc::stack_pointer(Mword sp)
{
  (void)sp;
	asm volatile ("l.lwz r1,0(%0)\n\t"
	:
	: "r" (sp) );
}

IMPLEMENT static inline
Mword Proc::stack_pointer()
{
  Mword sp = 0;
	asm volatile ("l.sw 0(%0),r1\n\t"
	: "=r" (sp) );
  return sp;
}

IMPLEMENT static inline
Mword Proc::program_counter()
{
  Mword pc = 0;
	// to obtain program counter, the manual suggest to do it via l.jal
	asm volatile ("l.jal 1\n\t"
		"l.nop\n\t"
		"1: l.sw 0(%0), r9\n\t"
		: "=r" (pc) 
		:
		: "r9");
  return pc;
}

// 0815: this function is only present in sparc implementation
// Why is it needed? Can it be done another way
PUBLIC static inline
template <int ASI>
Mword Proc::read_alternative(Mword reg)
{
	Mword ret;
	asm volatile ("l.nop");
	return ret;
}

// 0815: this function is only present in sparc implementation
// Why is it needed? Can it be done another way
PUBLIC static inline
template <int ASI>
void Proc::write_alternative(Mword reg, Mword value)
{
	asm volatile ("l.nop");
}


IMPLEMENTATION [or1k && !mp]:

IMPLEMENT static inline
Cpu_phys_id Proc::cpu_id()
{ return Cpu_phys_id(0); }


// 0815 currently VR2 is not implemented in or1k-support.h
// otherwise it the CPU ID could be obtained by this SPR 

//IMPLEMENTATION [or1k && mp]:

