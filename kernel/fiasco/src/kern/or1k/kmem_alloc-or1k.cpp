IMPLEMENTATION [or1k]:

#include "mem_space.h"
#include "mem_region.h"

IMPLEMENT
Kmem_alloc::Kmem_alloc()
{
	Mword alloc_size = Config::Kmem_size;

	a->init(Mem_layout::Map_base);

	/* First, collect non-used physical memory chunks
	 * into a list. */
	Mem_region_map<64> map;

	unsigned long avail_size = create_free_map(Kip::k(), &map); //map is used add available memory regions to it

	printf("Available phys mem: 0x%08lx\n", avail_size);

	for (int i = map.length() - 1; i >= 0 && alloc_size > 0; --i)
	{
		Mem_region f = map[i];

		if (f.size() > alloc_size)
			f.start += (f.size() - alloc_size);

		printf("  [start:%08lx - end:%08lx size:%4ld kB]\n", f.start, f.end, f.size() >> 10);

		Kip::k()->add_mem_region(Mem_desc(f.start, f.end, Mem_desc::Reserved));

		printf("    -> %08lx\n", Mem_layout::phys_to_pmem(f.start));
		printf("    -> %08lx\n", f.start);

		a->add_mem((void*)Mem_layout::phys_to_pmem(f.start), f.size());
		alloc_size -= f.size();
		printf("mapped %d\n", i);
	}
}

PUBLIC inline NEEDS["mem_space.h"]
Address
Kmem_alloc::to_phys(void *v) const
{
	 return Mem_space::kernel_space()->virt_to_phys((Address)v);
}

