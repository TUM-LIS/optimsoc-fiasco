IMPLEMENTATION [or1k]:

#include "mem_region.h"

	IMPLEMENT
Kmem_alloc::Kmem_alloc()
{
	Mword alloc_size = Config::Kmem_size;

	//Map_base or Pmem_start, what do we need here FIXME
	a->init(Mem_layout::Map_base);

	/* First, collect non-used physical memory chunks
	 * into a list. */
	Mem_region_map<64> map;

	unsigned long avail_size = create_free_map(Kip::k(), &map); //map is used add available memory regions to it

	printf("Available phys mem: %08lx\n", avail_size);
	printf("alloc_size: %08ld\n", alloc_size);
	printf("map.length(): %08ld\n", map.length());

	for (int i = map.length() - 1; i >= 0 && alloc_size > 0; --i)
	{
		Mem_region f = map[i];

		if (f.size() > alloc_size)
			f.start += (f.size() - alloc_size);

		printf("[start:%08lx - end:%08lx size:%4ld kB]\n", f.start, f.end, f.size() >> 10);

		Kip::k()->add_mem_region(Mem_desc(f.start, f.end, Mem_desc::Reserved));

		//printf("    -> %08lx\n", Mem_layout::phys_to_pmem(f.start));
		//printf("    -> %08lx\n", f.start);

		a->add_mem((void*)Mem_layout::phys_to_pmem(f.start), f.size());
		alloc_size -= f.size();
	}
}

PUBLIC inline
Address
Kmem_alloc::to_phys(void *v) const
{
    printf("\x1b[31mKmem_alloc::to_phys return ~0\n\x1b[0m");
	// FIX
	(void)v;
	return ~0UL;
}

