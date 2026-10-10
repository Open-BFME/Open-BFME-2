// ?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXPADI@Z
// partial score=0.978 date=2026-10-10
// ?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXPADI@Z
// partial score=0.978 date=2026-10-10 (313/320 bytes, 7 diff lines)
// Banked Code port for GeneralAllocator block-dump formatter @0x00031430 (320B).
// State: home TU memory_pool.cpp, builds clean, all 27 existing rows exact;
// candidate body at 320/320 size with a 7-line entry wall (see WALLS).
// TO APPLY (4 edits in Code/GameEngine/Source/Common/System/memory_pool.cpp):
// 1. Add import decl next to the other dllimports:
//    extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);
// 2. In class GeneralAllocator, replace the rva00031430 decl with the TRUE order
//    (WB debug build proves (block, dst, left), not the address-derived (block, left, dst)):
//    int rva00031430(const void *block, char *dst, unsigned int left);
//    and add: unsigned int rva000311E0(const void *src, unsigned int count, char *ascii,
//      unsigned short *wide, unsigned int cap);  // matches existing pin, resolves the direct call
// 3. Insert the body below after rva000327E0's definition (with its comment header).
// 4. SAME commit must fix rva000327E0's call (positional values unchanged, labels corrected):
//    int result = rva00031430((const char *)blockData - 8, dst, left);
//    (327E0's own params are likewise (blockData, dst, left) in truth; its row needs no
//    change since the rel32 target address is unchanged once the 31430 row lands.)
// TO LAND: tools/add_match.py '?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXPADI@Z'
//   0x00031430 320 Code/GameEngine/Source/Common/System/memory_pool.cpp
// WALLS (7 lines, entry cluster + 1): retail loads block to EDX
//   (mov edx,[ebp+8]; mov edi,[edx+4]) vs all variants' EAX; retail orders
//   cmp/spills then lea eax,[edx+8] vs variants' add-eax-8 before cmp; plus
//   lea eax,[esp+0x1c] vs [esp+0x20] for text+4. Tried without gain: hoisted vs
//   inline data local (inline = add-inside-branch, worse), volatile size word,
//   named bytes intermediate, same-valued PHI on block, declaration reorder.
//   WB reference: python3 tools/wb_show.py 0x00031430 (696B debug body, same algorithm).
// NOTE: the pinned 0x311E0 QAE name may be mislabeled (game.dat passes ecx=size-ish
//   at the direct call site while WB calls it virtually); call bytes already match.
int GeneralAllocator::rva00031430(const void *block, char *dst, unsigned int left)
{
	char *start = dst;
	unsigned int size = (*(const unsigned int *)((const char *)block + 4) & 0x7FFFFFF8) - 8;
	const char *data = (const char *)block + 8;
	if (left >= 0x12)
	{
		int n = _snprintf(dst, left, "addr: 0x%08x%c",
			data, *(const unsigned char *)((const char *)this + 0x474));
		dst += n;
		left -= n;
	}
	if (left >= 0x1E)
	{
		int n = _snprintf(dst, left, "size: %10u (%8x)%c", size, size,
			*(const unsigned char *)((const char *)this + 0x474));
		dst += n;
		left -= n;
	}
	if (left >= 0x10A)
	{
		char text[256] = { 0 };
		rva000311E0(data, size, text, 0, 0x100);
		int n = _snprintf(dst, left, "data: %s%c", text + 4,
			*(const unsigned char *)((const char *)this + 0x474));
		dst += n;
		left -= n;
	}
	unsigned int flags = *(const unsigned int *)((const char *)block + 4);
	if ((flags & 4) || (flags & 2))
	{
		if (left >= 0x18)
		{
			const char *mapped = (flags & 2) ? "mapped" : "";
			const char *which = (flags & 4) ? "internal" : "";
			int n = _snprintf(dst, left, "attr: %s %s%c", which, mapped,
				*(const unsigned char *)((const char *)this + 0x474));
			dst += n;
			left -= n;
		}
	}
	return dst - start;
}
