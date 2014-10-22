int foo()
{
	for(;;)
	{
#if defined(ARCH_x86)
			asm("nop");
#elif defined(ARCH_arm)
			asm("mov r0,r0");
#elif defined(ARCH_or1k)
			asm("l.nop");
#else
#error Please add your arch
#endif
		}

	return 0;
}
