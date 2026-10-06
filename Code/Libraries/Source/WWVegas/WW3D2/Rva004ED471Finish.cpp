// ?rva004ED471@Rva004ED471@@QAEXPAVModelNodeClass@HLodClass@@PBV23@PBXI_N@Z
// cl: /Ireference/shims/bfmevector /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?rva004ED471@Rva004ED471@@QAE... @ 0x004ED471, 189 bytes.
// Vector overflow for HLod ModelNode 0x14 stride: allocates max+old, copies
// [start pos), fills n, copies [pos finish) unless atend, frees old.
// Evidence: callers 0x004ED6C8 push_back overflow path passes pos value 1 1;
// callees rowed Copy 0x004ED0E9 Fill 0x004ED10F Assign 0x004ED0D7 allocator
// 0x395960 free 0x30830; prev/next share TU flags.
// The Copy/Fill/Copy helpers each take the allocator instance as a fourth
// argument; retail passes the address of a dedicated allocator local (its own
// stack slot distinct from the incoming count), which is why each call opens
// with a lea of that slot rather than reusing the count home.
#include "vector.h"
#include "vector3.h"
#include "ascii_string.h"

class RenderObjClass;

class HLodClass
{
public:
	class ModelNodeClass
	{
	public:
		ModelNodeClass & operator = (const ModelNodeClass &that);
		RenderObjClass *Model;
		int BoneIndex;
		Vector3 Offset;
	};
};

void __cdecl Rva004ED0D7Assign(HLodClass::ModelNodeClass *dst, const HLodClass::ModelNodeClass *src);
HLodClass::ModelNodeClass * __cdecl Rva004ED0E9Copy(const HLodClass::ModelNodeClass *first, const HLodClass::ModelNodeClass *last, HLodClass::ModelNodeClass *result, const void *h)
{ HLodClass::ModelNodeClass *r = result; const HLodClass::ModelNodeClass *f = first; while (f != last) { Rva004ED0D7Assign(r, f); ++f; ++r; } return r; }
HLodClass::ModelNodeClass * __cdecl Rva004ED10FFill(HLodClass::ModelNodeClass *dst, unsigned int count, const HLodClass::ModelNodeClass *src, const void *h)
{ HLodClass::ModelNodeClass *p = dst; unsigned int n = count; if (n <= 0) return p; do { Rva004ED0D7Assign(p, src); ++p; } while (--n != 0); return p; }
extern "C" void __cdecl free(void *);

struct BfmeStringRecord002CF4C6 {
    AsciiString *text0, *text1;
    unsigned int word0, word1;
    unsigned char flag0, flag1;
    BfmeStringRecord002CF4C6();
    BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &);
};
namespace _STL {
template <class T> class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
}

// The allocator instance the Copy/Fill helpers take as their fourth argument.
// Retail materialises its address with a lea before each of the three helper
// calls, at [ebp+0x1b] -- a slot distinct from the incoming count at
// [ebp+0x14]. An EMPTY struct is what places it there: a 4-byte member lands at
// [ebp+0x18] (aliasing the trailing bool) and an 8-byte member drops to
// [ebp-0xc]. The odd +0x1b slot is the size-1 address of the empty
// _STL::allocator, so the value is a placeholder and only its address matters.
struct _BfmeAllocatorHintType
{
};

class Rva004ED471
{
public:
	void rva004ED471(HLodClass::ModelNodeClass *pos, const HLodClass::ModelNodeClass *value, const void *dummy, unsigned int count, bool atend);
	HLodClass::ModelNodeClass *m_start;
	HLodClass::ModelNodeClass *m_finish;
	HLodClass::ModelNodeClass *m_end;
};

void Rva004ED471::rva004ED471(HLodClass::ModelNodeClass *pos, const HLodClass::ModelNodeClass *value, const void *dummy, unsigned int count, bool atend)
{
	unsigned int oldSize = (unsigned int)(m_finish - m_start);
	unsigned int *p = &count;
	unsigned int tmp = oldSize;
	if (tmp >= count) {
		p = &tmp;
	}
	unsigned int len = *p + oldSize;
	_STL::allocator<BfmeStringRecord002CF4C6> *alloc = (_STL::allocator<BfmeStringRecord002CF4C6> *)&m_end;
	HLodClass::ModelNodeClass *newStart = (HLodClass::ModelNodeClass *)alloc->allocate(len, 0);
	(void)dummy;
	_BfmeAllocatorHintType hintSlot;
	const void *hint = &hintSlot;
	HLodClass::ModelNodeClass *newFinish = Rva004ED0E9Copy(m_start, pos, newStart, hint);
	if (count == 1) {
		Rva004ED0D7Assign(newFinish, value);
		++newFinish;
	} else {
		newFinish = Rva004ED10FFill(newFinish, count, value, hint);
	}
	if (!atend) {
		newFinish = Rva004ED0E9Copy(pos, m_finish, newFinish, hint);
	}
	HLodClass::ModelNodeClass *oldStart = m_start;
	if (oldStart != 0) {
		free(oldStart);
	}
	m_start = newStart;
	m_finish = newFinish;
	m_end = newStart + len;
}