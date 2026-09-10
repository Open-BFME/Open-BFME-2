// cl: /O2 /DNDEBUG /MD
//
// Tagged array operator new, retail 0x006C4C30, 22 bytes.
// Same game-allocator table as mem_ops.cpp, memory class 2, with the
// extra argument forwarded as the allocation tag.

typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);
extern "C" GameAllocateFunction __gameMemAllocatePtr;

void *__cdecl operator new[](unsigned int size, unsigned int extra)
{
	unsigned tag = extra;
	unsigned bytes = size;
	return __gameMemAllocatePtr(bytes, 2, (const void *)tag);
}
