// cl: /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??4Rva003B1101@@QAEAAV0@ABV0@@Z @0x003B1337 (215B):
// Copy assignment for Rva003B1101 (dtor at 0x003B1101, deleting dtor at
// 0x003B152A). Base Overridable assign folds to the 5B empty body at
// 0x001FD28E, StringBase<char>::set folds to AsciiString assign at
// 0x000366F0, vector<int> assign pins to 0x0021C21B, OpaqueRefElement4
// assigns rowed at 0x00239099. Layout from the dtor TU plus retail offsets:
// string at +0x10, ints +0x14..+0x20, vector +0x24, int +0x30, opaques
// +0x34/+0x38, strings +0x3c/+0x40, ints +0x44..+0x54, bytes +0x58/+0x59,
// string +0x5c, int +0x60, 16B +0x64, ints +0x74/+0x78/+0x7c.
// Evidence: unlock lane, all callees rowed or pinned, neighbours same class.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> int * allocator<int>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@HV?$allocator@H@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<int, allocator<int> >::_M_clear(); }

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

// Native 0x0021C21B is owned by the non-POD-traited four-byte record
// specialization in StlSweepW5Rva0021C21B.cpp. Preserve this caller's
// storage and argument ABI while naming the verified out-of-line provider.
struct Rva0021C21BElement { char bytes[4]; };
typedef _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > RetailAssignVector;
namespace _STL {
template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &
vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(
    const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &);
}

typedef int Int;

#include "../../Include/Common/Overridable.h"

template <typename T>
class StringBase
{
public:
	void set(const StringBase &that);
private:
	T *m_data;
};

struct OpaqueRefElement4;
class OpaqueRefCounted;

struct OpaqueRefElement4
{
	OpaqueRefCounted *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
};

struct FourInts
{
	Int a;
	Int b;
	Int c;
	Int d;
};

class Rva003B1101 : public Overridable
{
public:
	Rva003B1101 &operator=(const Rva003B1101 &that);
private:
	StringBase<char> m_10; // +0x10
	Int m_14; // +0x14
	Int m_18; // +0x18
	Int m_1c; // +0x1c
	Int m_20; // +0x20
	_STL::vector<Int> m_24; // +0x24
	Int m_30; // +0x30
	OpaqueRefElement4 m_34; // +0x34
	OpaqueRefElement4 m_38; // +0x38
	StringBase<char> m_3c; // +0x3c
	StringBase<char> m_40; // +0x40
	Int m_44; // +0x44
	Int m_48; // +0x48
	Int m_4c; // +0x4c
	Int m_50; // +0x50
	Int m_54; // +0x54
	unsigned char m_58; // +0x58
	unsigned char m_59; // +0x59
	StringBase<char> m_5c; // +0x5c
	Int m_60; // +0x60
	FourInts m_64; // +0x64
	Int m_74; // +0x74
	Int m_78; // +0x78
	Int m_7c; // +0x7c
};

Rva003B1101 &Rva003B1101::operator=(const Rva003B1101 &that)
{
	Overridable::operator=(that);
	m_10.set(that.m_10);
	m_14 = that.m_14;
	m_18 = that.m_18;
	m_1c = that.m_1c;
	m_20 = that.m_20;
	*(RetailAssignVector *)&m_24 = *(const RetailAssignVector *)&that.m_24;
	m_30 = that.m_30;
	m_34 = that.m_34;
	m_38 = that.m_38;
	m_3c.set(that.m_3c);
	m_40.set(that.m_40);
	m_44 = that.m_44;
	m_48 = that.m_48;
	m_4c = that.m_4c;
	m_50 = that.m_50;
	m_54 = that.m_54;
	m_58 = that.m_58;
	m_59 = that.m_59;
	m_5c.set(that.m_5c);
	m_60 = that.m_60;
	m_64 = that.m_64;
	m_74 = that.m_74;
	m_78 = that.m_78;
	m_7c = that.m_7c;
	return *this;
}
