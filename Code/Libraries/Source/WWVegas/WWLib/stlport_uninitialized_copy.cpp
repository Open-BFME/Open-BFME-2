// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_copy<T> helpers (38 bytes), same-shape siblings of
// the rowed copy at 0x000BBAA1. Each body walks a source range constructing
// each element out-of-line through T's own rowed _Construct (declared-only
// specialization below, resolving through that row), striding by sizeof(T).
// The bodies ride the vector copy constructor, instantiated per T below.
// Each T is declared minimally at its retail stride (8 bytes) with the
// struct/class-ness of its rowed copy ctor; no member is touched. Siblings
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

namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template<> void _Construct<CopyNoCasePair, CopyNoCasePair>(CopyNoCasePair *, const CopyNoCasePair &);
template<> void _Construct<CopyPairC, CopyPairC>(CopyPairC *, const CopyPairC &);
template<> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
template<> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
}

template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(const _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> > &);
template _STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> >::vector(const _STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> > &);
template _STL::vector<CopyPairC, _STL::allocator<CopyPairC> >::vector(const _STL::vector<CopyPairC, _STL::allocator<CopyPairC> > &);
template _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::vector(const _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > &);
template _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> >::vector(const _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> > &);
