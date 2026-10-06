// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport vector push_back / _M_insert_overflow / __uninitialized_fill_n for a
// 36-byte element, default flags. Retail push_back 0x00166570 is called from
// the unclaimed HTree-area functions at 0x001666BA and 0x00166A57; it tests
// finish==end_of_storage and either placement-constructs through 0x001610F0
// and bumps finish by 0x24 or calls _M_insert_overflow 0x001663F0 with
// (pos value __false_type n=1 atend=true). The overflow body allocates via
// the byte allocator 0x000307F0 copies prefix/value/suffix through
// 0x001610F0 and frees the old block through 0x00030830.
//
// Element identity is not recovered. Elem36 is the stride-sized stand-in of
// ElementStrideWalks.cpp; the member split (dword + 16-byte block + three
// dwords + byte) follows the retail construct helper 0x001610F0 which copies
// +0x04..+0x13 as one block then +0x14/+0x18/+0x1C and the byte at +0x20.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

struct Elem36Block16
{
	int m_words[4];
};

struct Elem36Tail
{
	Elem36Block16 m_block;
	int m_word14;
	int m_word18;
	int m_word1C;
};

struct Elem36
{
	int m_word00;
	Elem36Tail m_tail;
	bool m_flag20;

	Elem36(const Elem36 &other)
		: m_word00(other.m_word00), m_tail(other.m_tail), m_flag20(other.m_flag20)
	{
	}
};

#include <memory>
namespace _STL {
template<> void _Construct<Elem36, Elem36>(Elem36 *, const Elem36 &);
}
#include <vector>

typedef _STL::vector<Elem36, _STL::allocator<Elem36> > Elem36Vector;

extern void (Elem36Vector::*const g_elem36PushBack)(const Elem36 &);
void (Elem36Vector::*const g_elem36PushBack)(const Elem36 &) = &Elem36Vector::push_back;