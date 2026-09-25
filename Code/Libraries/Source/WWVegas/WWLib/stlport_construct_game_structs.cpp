// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<T> placement-copy helpers, same-shape siblings of the
// rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own rowed copy ctor, and __EH_prolog resolves via its matched row.
// Each T is declared minimally (declared-only copy ctor, matching the
// struct/class-ness of its rowed copy ctor); no member is ever touched, so
// the emitted code is identical apart from the callee. Ledger names use the
// true _Construct<T> object symbol where it is still unspent, else a dup_
// name with an object-symbol note like 0x0002C485.

#include <memory>

struct TreeKey00242F5E
{
public:
	TreeKey00242F5E(const TreeKey00242F5E &other);
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
};

class FXList
{
public:
	FXList(const FXList &other);
};

struct BfmeStringRecord00239B46
{
public:
	BfmeStringRecord00239B46(const BfmeStringRecord00239B46 &other);
};

struct BfmeStringRecord005DDD40
{
public:
	BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &other);
};

class Rva0033A4F0
{
public:
	Rva0033A4F0(const Rva0033A4F0 &other);
};

template void _STL::_Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template void _STL::_Construct<GeometryInfo, GeometryInfo>(GeometryInfo *, const GeometryInfo &);
template void _STL::_Construct<FXList, FXList>(FXList *, const FXList &);
template void _STL::_Construct<BfmeStringRecord00239B46, BfmeStringRecord00239B46>(BfmeStringRecord00239B46 *, const BfmeStringRecord00239B46 &);
template void _STL::_Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
template void _STL::_Construct<Rva0033A4F0, Rva0033A4F0>(Rva0033A4F0 *, const Rva0033A4F0 &);
