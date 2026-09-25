// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);

private:
	void *m_data;
};

struct NoCaseTreeValue4
{
	char m_body[4];
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

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);

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

namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template<> void _Construct<CopyNoCasePair, CopyNoCasePair>(CopyNoCasePair *, const CopyNoCasePair &);
template<> void _Construct<CopyPairC, CopyPairC>(CopyPairC *, const CopyPairC &);
template<> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
template<> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
template<> void _Construct<BfmeStringRecord0022074B, BfmeStringRecord0022074B>(BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &);
template<> void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *, const BfmeStringRecord00395E75 &);
template<> void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *, const BfmeStringRecord00466E64 &);
template<> void _Construct<BfmeStringRecord005F93E3, BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
template<> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *, const RvaSmartPtr12 &);
}

template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(const _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> > &);
template _STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> >::vector(const _STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> > &);
template _STL::vector<CopyPairC, _STL::allocator<CopyPairC> >::vector(const _STL::vector<CopyPairC, _STL::allocator<CopyPairC> > &);
template _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::vector(const _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > &);
template _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> >::vector(const _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> > &);
template _STL::vector<BfmeStringRecord0022074B, _STL::allocator<BfmeStringRecord0022074B> >::vector(const _STL::vector<BfmeStringRecord0022074B, _STL::allocator<BfmeStringRecord0022074B> > &);
template _STL::vector<BfmeStringRecord00395E75, _STL::allocator<BfmeStringRecord00395E75> >::vector(const _STL::vector<BfmeStringRecord00395E75, _STL::allocator<BfmeStringRecord00395E75> > &);
template _STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> >::vector(const _STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> > &);
template _STL::vector<BfmeStringRecord005F93E3, _STL::allocator<BfmeStringRecord005F93E3> >::vector(const _STL::vector<BfmeStringRecord005F93E3, _STL::allocator<BfmeStringRecord005F93E3> > &);
template _STL::vector<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> >::vector(const _STL::vector<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> > &);
