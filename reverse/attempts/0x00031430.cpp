// ?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXIPAD@Z
// partial score=0.9 date=2026-10-06
// ?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXIPAD@Z
// partial score=0.9 date=2026-10-06
// Banked candidate for GeneralAllocator block-dump formatter @0x00031430 (320B). 319/320 bytes.
// WALLS: (a) block loads to edx (retail) vs eax (all variants) -- pure allocator whim, cascades;
// (b) early lea eax,[edx+8] sandwiched between this/dst spills and size spill -- scheduler interleaving;
//   naming a data local flips the ebx/esi param assignment, inlining defers to add-inside-branch;
// (c) data-branch order (retail reloads block late via mov-eax/add-eax; variants hoist);
// (d) attr-branch wants inline ternaries (pointer locals give test-edi shape) -- untested solo.
// Solved: (block,left,dst) unsigned order, movzx uchar sep at +0x474, flags word at +4, direct param
// update + start anchor forces all three spills at retail slots, and-esp prolog via 256B = {0} buffer,
// _snprintf import auto-resolves, 0x311E0 candidate pin added. First two blocks (addr/size + calls)
// byte-exact through 0x314a4. Next: fix (a)/(b) without adding live ranges, then (d) via ternaries.
// t=55 model=muse-spark
// ?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXIPAD@Z @0x00031430 320B.
// GeneralAllocator block-dump formatter: appends "addr/size/data/attr" lines
// for one heap block into the caller's buffer, returning bytes appended.
// Target facts: this+4 carries flag bits 2/4 (attr line), this+0x474 is the
// %c separator reloaded for every _snprintf; block+4 masked 0x7FFFFFF8 minus
// 8 is the size, block+8 the data; thresholds 0x12/0x1E/0x10A/0x18 gate each
// line; the 256B stack buffer is zero-filled then passed to the pinned (not
// rowed) 0x000311E0 hex formatter as (src,count,ascii,wide=0,cap=0x100),
// whose text the "data:" line reads at ascii+4; "mapped"/"internal"/""
// pointers match the rdata strings. Address-derived name; the +0x474 member
// extends the 0x33A80 TU's view (same +4 word, wider span).
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer,
		unsigned int count, const char *format, ...);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	int rva00031430(const void *block, unsigned int left, char *dst);
	unsigned int rva000311E0(const void *src, unsigned int count,
		char *ascii, unsigned short *wide, unsigned int cap);

private:
	unsigned int m_00;
	unsigned int m_04;
	unsigned char m_pad08[0x474 - 8];
	unsigned char m_sep;
};

int GeneralAllocator::rva00031430(const void *block, unsigned int left, char *dst)
{
	char *start = dst;
	unsigned int size = (*(const unsigned int *)((const char *)block + 4) & 0x7FFFFFF8) - 8;
	if (left >= 0x12)
	{
		int n = _snprintf(dst, left, "addr: 0x%08x%c",
			(const char *)block + 8, m_sep);
		dst += n;
		left -= n;
	}
	if (left >= 0x1E)
	{
		int n = _snprintf(dst, left, "size: %10u (%8x)%c", size, size, m_sep);
		dst += n;
		left -= n;
	}
	if (left >= 0x10A)
	{
		char text[256] = { 0 };
		rva000311E0((const char *)block + 8, size, text, 0, 0x100);
		int n = _snprintf(dst, left, "data: %s%c", text + 4, m_sep);
		dst += n;
		left -= n;
	}
	unsigned int flags = m_04;
	if ((flags & 4) || (flags & 2))
	{
		if (left >= 0x18)
		{
			const char *mapped = (flags & 2) ? "mapped" : "";
			const char *which = (flags & 4) ? "internal" : "";
			int n = _snprintf(dst, left, "attr: %s %s%c", which, mapped, m_sep);
			dst += n;
			left -= n;
		}
	}
	return dst - start;
}

}
}
