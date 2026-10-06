// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_copy<T> helpers (38 bytes), same-shape siblings of
// the rowed copy at 0x000BBAA1. Each body walks a source range constructing
// each element out-of-line through T's own rowed _Construct (declared-only
// specialization below, resolving through that row), striding by sizeof(T).
// The bodies ride the vector copy constructor, instantiated per T below.
// Each T is declared minimally at its retail stride (8 bytes above,
// 12 bytes below) with the struct/class-ness of its rowed copy ctor;
// no member is touched. Siblings
// calling a _Construct dupe rather than its true address land as
// gen-alias rows, like the fill_n batch before this one.

#include <memory>
#include <vector>

#include "ascii_string.h"

struct NoCaseTreeValue4
{
	char m_body[4];
};

// Target push_back 0x0039A48E establishes an 8-byte element stride; retain an
// address-derived view because retail evidence does not identify its fields.
struct Rva0039A48EElement
{
	int a[2];
};

struct TreeKey00242F5E
{
public:
	TreeKey00242F5E();
	TreeKey00242F5E(const TreeKey00242F5E &other);
	char m_body[8];
};

struct BfmeStringRecord005DDD40
{
public:
	BfmeStringRecord005DDD40();
	BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &other);
	char m_body[8];
};

struct Rva0048130E
{
public:
	Rva0048130E();
	Rva0048130E(const Rva0048130E &other);
	char m_body[8];
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);

private:
	char m_pad[8];
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry();
	Rva0040CB11Entry(const Rva0040CB11Entry &other);

private:
	char m_pad[8];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> CopyNoCasePair;
typedef _STL::pair<const AsciiString, char> CopyPairC;

// Twelve-byte string records below: same 38-byte helper shape as above,
// striding 0xC per element through each record's own rowed _Construct.
struct BfmeStringRecord0022074B
{
public:
	BfmeStringRecord0022074B();
	BfmeStringRecord0022074B(const BfmeStringRecord0022074B &other);
	char m_body[12];
};

// Twenty-four-byte string record at 0x005EC43C: same 38-byte helper shape,
// striding 0x18 per element through its own rowed _Construct at 0x005EC4B6.
// Retail 0x005EC4E3 walks source range constructing each element out-of-line.
// Layout matches the 0x005EC43C copy ctor (UnicodeString plus five words).
struct BfmeStringRecord005EC43C
{
public:
	BfmeStringRecord005EC43C();
	BfmeStringRecord005EC43C(const BfmeStringRecord005EC43C &other);
	char m_body[24];
};

struct BfmeStringRecord00395E75
{
public:
	BfmeStringRecord00395E75();
	BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &other);
	char m_body[12];
};

struct BfmeStringRecord00466E64
{
public:
	BfmeStringRecord00466E64();
	BfmeStringRecord00466E64(const BfmeStringRecord00466E64 &other);
	char m_body[12];
};

struct BfmeStringRecord005F93E3
{
public:
	BfmeStringRecord005F93E3();
	BfmeStringRecord005F93E3(const BfmeStringRecord005F93E3 &other);
	char m_body[12];
};

class RvaSmartPtr12
{
public:
	RvaSmartPtr12();
	RvaSmartPtr12(const RvaSmartPtr12 &other);

private:
	char m_pad[12];
};

// Sixteen-byte string record at 0x002199C8: same 38-byte copy shape,
// striding 0x10 per element through its own rowed _Construct at 0x0021A95D.
// Layout matches the 0x002199C8 copy ctor (three AsciiStrings plus a word).
struct BfmeStringRecord002199C8
{
public:
	BfmeStringRecord002199C8();
	BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &other);
	char m_body[16];
};

// Twenty-byte string record at 0x00219A68: same 38-byte copy shape,
// striding 0x14 per element through its own rowed _Construct at 0x0021A98A.
// Layout matches the 0x00219A68 copy ctor (word plus two AsciiStrings plus two words).
struct BfmeStringRecord00219A68
{
public:
	BfmeStringRecord00219A68();
	BfmeStringRecord00219A68(const BfmeStringRecord00219A68 &other);
	char m_body[20];
};

namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template<> void _Construct<CopyNoCasePair, CopyNoCasePair>(CopyNoCasePair *, const CopyNoCasePair &);
template<> __declspec(nothrow) void _Construct<Rva0039A48EElement, Rva0039A48EElement>(Rva0039A48EElement *, const Rva0039A48EElement &);
template<> void _Construct<CopyPairC, CopyPairC>(CopyPairC *, const CopyPairC &);
template<> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
template<> void _Construct<Rva0048130E, Rva0048130E>(Rva0048130E *, const Rva0048130E &);
template<> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
template<> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, const Rva0040CB11Entry &);
template<> void _Construct<BfmeStringRecord0022074B, BfmeStringRecord0022074B>(BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &);
template<> void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *, const BfmeStringRecord00395E75 &);
template<> void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *, const BfmeStringRecord00466E64 &);
template<> void _Construct<BfmeStringRecord005F93E3, BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
template<> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *, const RvaSmartPtr12 &);
template<> void _Construct<BfmeStringRecord005EC43C, BfmeStringRecord005EC43C>(BfmeStringRecord005EC43C *, const BfmeStringRecord005EC43C &);
template<> void _Construct<BfmeStringRecord002199C8, BfmeStringRecord002199C8>(BfmeStringRecord002199C8 *, const BfmeStringRecord002199C8 &);
template<> void _Construct<BfmeStringRecord00219A68, BfmeStringRecord00219A68>(BfmeStringRecord00219A68 *, const BfmeStringRecord00219A68 &);
// LINK-COMDAT: retail allocate copies for these records are kept by the G7
// growth TU (StringRecordVectorGrowthG7.cpp) and CreateAHeroBlingFindOrAdd.cpp;
// declare them so this /O1 TU does not emit the lea+shl copies.
template<> BfmeStringRecord0022074B *allocator<BfmeStringRecord0022074B>::allocate(unsigned int, const void *) const;
template<> BfmeStringRecord005EC43C *allocator<BfmeStringRecord005EC43C>::allocate(unsigned int, const void *) const;
template<> BfmeStringRecord005F93E3 *allocator<BfmeStringRecord005F93E3>::allocate(unsigned int, const void *) const;
template<> BfmeStringRecord00219A68 *allocator<BfmeStringRecord00219A68>::allocate(unsigned int, const void *) const;
}

template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(const _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> > &);
template _STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> >::vector(const _STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> > &);
template _STL::vector<CopyPairC, _STL::allocator<CopyPairC> >::vector(const _STL::vector<CopyPairC, _STL::allocator<CopyPairC> > &);
template _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::vector(const _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > &);
template _STL::vector<Rva0048130E, _STL::allocator<Rva0048130E> >::vector(const _STL::vector<Rva0048130E, _STL::allocator<Rva0048130E> > &);
template _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> >::vector(const _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> > &);
template _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::vector(const _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> > &);
template _STL::vector<BfmeStringRecord0022074B, _STL::allocator<BfmeStringRecord0022074B> >::vector(const _STL::vector<BfmeStringRecord0022074B, _STL::allocator<BfmeStringRecord0022074B> > &);
template _STL::vector<BfmeStringRecord00395E75, _STL::allocator<BfmeStringRecord00395E75> >::vector(const _STL::vector<BfmeStringRecord00395E75, _STL::allocator<BfmeStringRecord00395E75> > &);
template _STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> >::vector(const _STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> > &);
template _STL::vector<BfmeStringRecord005F93E3, _STL::allocator<BfmeStringRecord005F93E3> >::vector(const _STL::vector<BfmeStringRecord005F93E3, _STL::allocator<BfmeStringRecord005F93E3> > &);
template _STL::vector<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> >::vector(const _STL::vector<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> > &);
template _STL::vector<BfmeStringRecord005EC43C, _STL::allocator<BfmeStringRecord005EC43C> >::vector(const _STL::vector<BfmeStringRecord005EC43C, _STL::allocator<BfmeStringRecord005EC43C> > &);
template _STL::vector<BfmeStringRecord002199C8, _STL::allocator<BfmeStringRecord002199C8> >::vector(const _STL::vector<BfmeStringRecord002199C8, _STL::allocator<BfmeStringRecord002199C8> > &);
template _STL::vector<BfmeStringRecord00219A68, _STL::allocator<BfmeStringRecord00219A68> >::vector(const _STL::vector<BfmeStringRecord00219A68, _STL::allocator<BfmeStringRecord00219A68> > &);

// Target _M_insert_overflow 0x00399EBE calls the 38-byte copy worker at
// 0x003961CA; its element construction relocates to 0x00396170.
template Rva0039A48EElement *_STL::__uninitialized_copy<Rva0039A48EElement *, Rva0039A48EElement *>(Rva0039A48EElement *, Rva0039A48EElement *, Rva0039A48EElement *, const _STL::__false_type &);
