// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
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
// genuine _Construct<T> object symbol for its established owner. Distinct
// native copies have typed address-derived owners; application names remain unknown.

#include <memory>
#include "ascii_string.h"

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


class Rva0052BEF0
{
public:
	Rva0052BEF0(const Rva0052BEF0 &other);
};

class Rva0052BD59
{
public:
	Rva0052BD59(const Rva0052BD59 &other);
};

class Rva0052BE33
{
public:
	Rva0052BE33(const Rva0052BE33 &other);
};

class Rva0052BDE6
{
public:
	Rva0052BDE6(const Rva0052BDE6 &other);
};


template void _STL::_Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template void _STL::_Construct<GeometryInfo, GeometryInfo>(GeometryInfo *, const GeometryInfo &);
template void _STL::_Construct<FXList, FXList>(FXList *, const FXList &);
template void _STL::_Construct<Rva0052BEF0, Rva0052BEF0>(Rva0052BEF0 *, const Rva0052BEF0 &);
template void _STL::_Construct<Rva0052BD59, Rva0052BD59>(Rva0052BD59 *, const Rva0052BD59 &);
template void _STL::_Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *, const Rva0052BE33 &);
template void _STL::_Construct<Rva0052BDE6, Rva0052BDE6>(Rva0052BDE6 *, const Rva0052BDE6 &);

// Native unsigned-key/string map: subscript136A21 -> hint136777 ->
// insert136642/1364F7 -> node1364AC -> Construct13623C. The subscript
// default-constructs the mapped string and returns node+0x14; the node is
// 24 bytes with its 8-byte value at +0x10. STLport map::value_type supplies
// the const key. Its genuine pair copy folds onto the existing29B CF475
// owner; the separate TreeKey ConstructA7876 and handler760AB8 remain.
typedef _STL::pair<const unsigned int, AsciiString> UnsignedAsciiPair;
template void _STL::_Construct<UnsignedAsciiPair, UnsignedAsciiPair>(UnsignedAsciiPair *, const UnsignedAsciiPair &);

// Native Apt adder524845 supplies std::make_pair to vector52480E at+0C,
// which calls Construct523DD4. The erase/copy chain writes the first dword,
// excluding a const map key. Keep the existing producer's int source view:
// signedness is a source convention here, not a recovered original signature.
// The genuine pair copy folds onto CF475; TreeKeyA7876 keeps its own identity.
typedef _STL::pair<int, AsciiString> MutableAsciiPair;
template void _STL::_Construct<MutableAsciiPair, MutableAsciiPair>(MutableAsciiPair *, const MutableAsciiPair &);

// Distinct native placement-copy owners; original application names remain unknown.
void Rva0023FC3EConstruct(BfmeStringRecord00239B46 *dest, const BfmeStringRecord00239B46 &source)
{
    new (dest) BfmeStringRecord00239B46(source);
}

void Rva0026061AConstruct(BfmeStringRecord005DDD40 *dest, const BfmeStringRecord005DDD40 &source)
{
    new (dest) BfmeStringRecord005DDD40(source);
}

void Rva000BBA47Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva000CF4D6Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva002889E4Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva002927CBConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva0029FB9CConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva002A8C17Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva00382BC3Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva004634DCConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva0048C81FConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source)
{
    new (dest) TreeKey00242F5E(source);
}

void Rva003814A6Construct(BfmeStringRecord005DDD40 *dest, const BfmeStringRecord005DDD40 &source)
{
    new (dest) BfmeStringRecord005DDD40(source);
}
