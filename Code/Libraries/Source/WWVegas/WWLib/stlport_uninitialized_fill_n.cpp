// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_fill_n<T> helpers (37 bytes), same-shape siblings
// of the rowed fill_n at 0x000B97E9. Each body null-guards the count, then
// constructs each element out-of-line through T's own rowed _Construct
// (declared-only specialization below, resolving through that row), striding
// by sizeof(T). Each T is declared minimally at its retail stride (8 bytes)
// with the struct/class-ness of its rowed copy ctor; no member is touched.

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

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> FillNoCasePair;
typedef _STL::pair<const AsciiString, char> FillPairC;

namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template<> void _Construct<FillNoCasePair, FillNoCasePair>(FillNoCasePair *, const FillNoCasePair &);
template<> void _Construct<FillPairC, FillPairC>(FillPairC *, const FillPairC &);
template<> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
template<> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
template<> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
}

template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(unsigned int, const TreeKey00242F5E &, const _STL::allocator<TreeKey00242F5E> &);
template _STL::vector<FillNoCasePair, _STL::allocator<FillNoCasePair> >::vector(unsigned int, const FillNoCasePair &, const _STL::allocator<FillNoCasePair> &);
template _STL::vector<FillPairC, _STL::allocator<FillPairC> >::vector(unsigned int, const FillPairC &, const _STL::allocator<FillPairC> &);
template _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::vector(unsigned int, const BfmeStringRecord005DDD40 &, const _STL::allocator<BfmeStringRecord005DDD40> &);
template _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> >::vector(unsigned int, const Rva002390CB &, const _STL::allocator<Rva002390CB> &);
template _STL::vector<AsciiString, _STL::allocator<AsciiString> >::vector(unsigned int, const AsciiString &, const _STL::allocator<AsciiString> &);
