// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport46
// BFME2 record layouts recovered from complete retail copy constructors.
// These use STLport basic_string<char> (12 bytes), copied by 0x9170.
// Application names and scalar meanings remain unknown. Padding is not copied.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <memory>
#include <string>

// The record copies and assignments call the shared retail string providers
// at 0x9170 and 0x120C0; do not emit private copies of their helper graph.
namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const basic_string<char, char_traits<char>, allocator<char> > &);
template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::assign(const basic_string<char, char_traits<char>, allocator<char> > &);
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
// This unit owns retail's independent allocator cleanup at 0x46264A.
template void allocator<char>::deallocate(char *, size_t);
}

// Complete retail record copy at 0x00079C23.
struct BfmeNarrowRecord00079C23 {
    _STL::basic_string<char> text0, text1, text2; unsigned int word0, word1;
    BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23 &o);
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline BfmeNarrowRecord00079C23::BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23 &o) : text0(o.text0), text1(o.text1), text2(o.text2), word0(o.word0), word1(o.word1) {}

// ?bfmeAnchorBfmeNarrowRecord00079C23Ctor absent-from-retail
void *bfmeAnchorBfmeNarrowRecord00079C23Ctor(void *where, const BfmeNarrowRecord00079C23 &other)
{
	return ::new (where) BfmeNarrowRecord00079C23(other);
}
template void _STL::_Construct<BfmeNarrowRecord00079C23,BfmeNarrowRecord00079C23>(BfmeNarrowRecord00079C23*,const BfmeNarrowRecord00079C23&);

// Complete retail record copy at 0x000BFDC7.
struct BfmeNarrowRecord000BFDC7 {
    unsigned int word0; _STL::basic_string<char> text; unsigned int word1, word2, word3, word4;
    BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7 &other);
};
BfmeNarrowRecord000BFDC7::BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7 &other) : word0(other.word0), text(other.text), word1(other.word1), word2(other.word2), word3(other.word3), word4(other.word4) {}
template void _STL::_Construct<BfmeNarrowRecord000BFDC7,BfmeNarrowRecord000BFDC7>(BfmeNarrowRecord000BFDC7*,const BfmeNarrowRecord000BFDC7&);

// Complete retail record copy at 0x0041A5D2.
#include "BfmeNarrowRecord0041A5D2.h"
BfmeNarrowRecord0041A5D2::BfmeNarrowRecord0041A5D2(const BfmeNarrowRecord0041A5D2 &o) : text0(o.text0), short0(o.short0), text1(o.text1) {}
BfmeNarrowRecord0041A5D2::BfmeNarrowRecord0041A5D2() {}
BfmeNarrowRecord0041A5D2 &BfmeNarrowRecord0041A5D2::operator=(const BfmeNarrowRecord0041A5D2 &o)
{
	text0.assign(o.text0);
	short0 = o.short0;
	text1.assign(o.text1);
	return *this;
}
template void _STL::_Construct<BfmeNarrowRecord0041A5D2,BfmeNarrowRecord0041A5D2>(BfmeNarrowRecord0041A5D2*,const BfmeNarrowRecord0041A5D2&);

// Complete retail record copy at 0x0041A617.
#include "BfmeNarrowRecord0041A617.h"
BfmeNarrowRecord0041A617::BfmeNarrowRecord0041A617(const BfmeNarrowRecord0041A617 &other) : text(other.text), short0(other.short0), flag(other.flag) {}
BfmeNarrowRecord0041A617 &BfmeNarrowRecord0041A617::operator=(const BfmeNarrowRecord0041A617 &o)
{
	text.assign(o.text);
	short0 = o.short0;
	flag = o.flag;
	return *this;
}
template void _STL::_Construct<BfmeNarrowRecord0041A617,BfmeNarrowRecord0041A617>(BfmeNarrowRecord0041A617*,const BfmeNarrowRecord0041A617&);

// Complete retail record copy at 0x00427F75.
struct BfmeNarrowRecord00427F75 {
    _STL::basic_string<char> text0, text1;
    BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
};
BfmeNarrowRecord00427F75::BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other) : text0(other.text0), text1(other.text1) {}
template void _STL::_Construct<BfmeNarrowRecord00427F75,BfmeNarrowRecord00427F75>(BfmeNarrowRecord00427F75*,const BfmeNarrowRecord00427F75&);

// Complete retail record copy at 0x0054FEF1.
struct BfmeNarrowRecord0054FEF1 {
    _STL::basic_string<char> text; unsigned int word0, word1;
    BfmeNarrowRecord0054FEF1(const BfmeNarrowRecord0054FEF1 &other);
    BfmeNarrowRecord0054FEF1 &operator=(const BfmeNarrowRecord0054FEF1 &o);
};
BfmeNarrowRecord0054FEF1::BfmeNarrowRecord0054FEF1(const BfmeNarrowRecord0054FEF1 &other) : text(other.text), word0(other.word0), word1(other.word1) {}
BfmeNarrowRecord0054FEF1 &BfmeNarrowRecord0054FEF1::operator=(const BfmeNarrowRecord0054FEF1 &o)
{
	text.assign(o.text);
	word0 = o.word0;
	word1 = o.word1;
	return *this;
}
template void _STL::_Construct<BfmeNarrowRecord0054FEF1,BfmeNarrowRecord0054FEF1>(BfmeNarrowRecord0054FEF1*,const BfmeNarrowRecord0054FEF1&);

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??0Pivot24@@QAE@ABU0@@Z=??0BfmeNarrowRecord00427F75@@QAE@ABU0@@Z")
#pragma comment(linker, "/alternatename:??0VersionBlockEntry@@QAE@ABU0@@Z=??0BfmeNarrowRecord00427F75@@QAE@ABU0@@Z")

#include <deque>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Retain the 4.6 allocator helper used by the shared string-provider cohort.
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Retail keeps one deque<BfmeNarrowRecord0041A5D2> dtor (0x0041A51F); this unit calls it.
namespace _STL {
template <> deque<BfmeNarrowRecord0041A5D2, allocator<BfmeNarrowRecord0041A5D2> >::~deque();
template <> deque<BfmeNarrowRecord0041A617, allocator<BfmeNarrowRecord0041A617> >::~deque();  // 0x0041A57B
}

struct BfmePod16
{
	BfmePod16(const BfmePod16 &);
	~BfmePod16();
};

// The dedicated destructor unit supplies the retail 16-byte-record cleanup.
namespace _STL { template <> deque<BfmePod16, allocator<BfmePod16> >::~deque(); }

class Rva0041A63A
{
public:
	void rva0041A63A();
};

void Rva0041A63A::rva0041A63A()
{
	((_STL::deque<BfmeNarrowRecord0041A5D2> *)this)->~deque();
}

class Rva0041A63F
{
public:
	void rva0041A63F();
};

void Rva0041A63F::rva0041A63F()
{
	((_STL::deque<BfmeNarrowRecord0041A617> *)this)->~deque();
}

class Rva0054FF9B
{
public:
	void rva0054FF9B();
};

void Rva0054FF9B::rva0054FF9B()
{
	((_STL::deque<BfmePod16> *)this)->~deque();
}

class Rva0054FFA0
{
public:
	void rva0054FFA0();
};

void Rva0054FFA0::rva0054FFA0()
{
	((_STL::deque<BfmePod16> *)this)->~deque();
}

