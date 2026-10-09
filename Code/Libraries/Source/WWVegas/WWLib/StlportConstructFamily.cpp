// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<T, T> placement-copy helpers (45 bytes: null-guarded
// placement new of a copy under an EH frame), the shape of the rowed
// _Construct<AsciiString> at 0x0002C485 (stlport_construct_asciistring.cpp).
// Each one is the out-of-line _Construct that a vector push_back in
// StlportVectorPushBackFamily.cpp calls (pinned there); the element is the
// same address-named placeholder, declared here only with the copy
// constructor the retail body calls, which is pinned at that address.  No
// element layout is claimed.
//
//   _Construct  element                 copy ctor
//   0x001DEDA7  Rva001DF3F1Element      0x001DE878
//   0x003324A8  Rva003328B6Element      0x003322E5
//   0x0041398E  Rva00413B16Element      0x00413951
//   0x0041432C  Rva00414BA4Element      0x0055AB99
//   0x004E2F27  Rva004E3E5AElement      0x004E2C66
//   0x00500873  Rva00501E3FElement      0x005007AA
//   0x005C83CD  Rva005C8624Element      0x005C9217

#include <memory>

struct Rva001DF3F1Element
{
	int a;
	Rva001DF3F1Element(const Rva001DF3F1Element &that);
};

class Rva00394173Member
{
public:
	int m_00;
	Rva00394173Member(const Rva00394173Member &that);
};

struct Rva003328B6Element
{
	int m_00;
	int m_04;
	Rva00394173Member m_08;
	Rva003328B6Element(const Rva003328B6Element &that);
};

Rva003328B6Element::Rva003328B6Element(const Rva003328B6Element &that)
	: m_00(that.m_00)
	, m_04(that.m_04)
	, m_08(that.m_08)
{
}

struct Rva00413B16Element
{
	int a;
	Rva00413B16Element(const Rva00413B16Element &that);
};

struct Rva00414BA4Element
{
	int a;
	Rva00414BA4Element(const Rva00414BA4Element &that);
};

struct Rva004E3E5AElement
{
	int a;
	Rva004E3E5AElement(const Rva004E3E5AElement &that);
};

struct Rva00501E3FElement
{
	int a;
	Rva00501E3FElement(const Rva00501E3FElement &that);
};

struct Rva005C8624Element
{
	int a;
	Rva005C8624Element(const Rva005C8624Element &that);
};

template void _STL::_Construct<Rva001DF3F1Element, Rva001DF3F1Element>(Rva001DF3F1Element *, const Rva001DF3F1Element &);
template void _STL::_Construct<Rva003328B6Element, Rva003328B6Element>(Rva003328B6Element *, const Rva003328B6Element &);
template void _STL::_Construct<Rva00413B16Element, Rva00413B16Element>(Rva00413B16Element *, const Rva00413B16Element &);
template void _STL::_Construct<Rva00414BA4Element, Rva00414BA4Element>(Rva00414BA4Element *, const Rva00414BA4Element &);
template void _STL::_Construct<Rva004E3E5AElement, Rva004E3E5AElement>(Rva004E3E5AElement *, const Rva004E3E5AElement &);
template void _STL::_Construct<Rva00501E3FElement, Rva00501E3FElement>(Rva00501E3FElement *, const Rva00501E3FElement &);
template void _STL::_Construct<Rva005C8624Element, Rva005C8624Element>(Rva005C8624Element *, const Rva005C8624Element &);

// ??0Rva00500856@@QAE@ABU0@@Z @0x00500856 29B copy ctor of 0x18 struct with
// int at +0 and Rva00501E3FElement at +4. Retail copies the first dword with
// mov then tail-copies the subobject via the pinned Rva00501E3FElement copy
// ctor 0x005007AA. Callers 0x00500CD1 (45B _Construct twin) and 0x0050366B.
// _Construct at 0x00500873 proves the callee spelling.
struct Rva00500856
{
	int m_00;
	Rva00501E3FElement m_04;
	Rva00500856(const Rva00500856 &that);
};

Rva00500856::Rva00500856(const Rva00500856 &that)
	: m_00(that.m_00)
	, m_04(that.m_04)
{
}

template void _STL::_Construct<Rva00500856, Rva00500856>(Rva00500856 *, const Rva00500856 &);

// More _Construct<T, T> bodies of the same 45-byte shape, each named by the
// rows that call it (push_back / _M_insert_overflow / uninitialized helpers or
// a list node factory for the same element view) and pinned there already:
//
//   _Construct  element                 copy ctor
//   0x003B8AD8  BfmePod104              0x0040E96D
//   0x0040B99F  Rva0040C0C7Element      0x0040B707
//   0x004140D0  Rva00414258Element      0x00414093
//   0x0052D355  Rva005668E9Element      0x004334D7
//   0x000C3717  BfmePod252              0x000C254B
//   0x000C78F3  BfmePod248              0x000C6B17
//   0x00289E69  BfmePod264              0x00289CEB
struct BfmePod104
{
	int a;
	BfmePod104(const BfmePod104 &that);
};
struct Rva0040C0C7Element
{
	int a;
	Rva0040C0C7Element(const Rva0040C0C7Element &that);
};
struct Rva00414258Element
{
	int a;
	Rva00414258Element(const Rva00414258Element &that);
};
struct Rva005668E9Element
{
	int a;
	Rva005668E9Element(const Rva005668E9Element &that);
};
struct BfmePod252
{
	int a;
	BfmePod252(const BfmePod252 &that);
};
struct BfmePod248
{
	int a;
	BfmePod248(const BfmePod248 &that);
};
struct BfmePod264 { int a[66]; };
// The experience-level copy now has its established Rva002894A2 owner.
// This declaration-only view passes the existing 0x108-byte list payload
// to that constructor; the helper retains its already rowed template name.
class Rva002894A2
{
public:
    Rva002894A2(const Rva002894A2 &);
private:
    char opaque[0x108];
};
template void _STL::_Construct<BfmePod104, BfmePod104>(BfmePod104 *, const BfmePod104 &);
template void _STL::_Construct<Rva0040C0C7Element, Rva0040C0C7Element>(Rva0040C0C7Element *, const Rva0040C0C7Element &);
template void _STL::_Construct<Rva00414258Element, Rva00414258Element>(Rva00414258Element *, const Rva00414258Element &);
template void _STL::_Construct<Rva005668E9Element, Rva005668E9Element>(Rva005668E9Element *, const Rva005668E9Element &);
template void _STL::_Construct<BfmePod252, BfmePod252>(BfmePod252 *, const BfmePod252 &);
template void _STL::_Construct<BfmePod248, BfmePod248>(BfmePod248 *, const BfmePod248 &);
namespace _STL {
template<> void _Construct<BfmePod264, BfmePod264>(BfmePod264 *p, const BfmePod264 &value)
{
    ::new ((void *)p) Rva002894A2(reinterpret_cast<const Rva002894A2 &>(value));
}
}

// Also the 45-byte _Construct for Rva00153729 (0x00153786, copy constructor
// 0x0015375A), named by its rowed callers: the uninitialized fill/copy and
// _M_insert_overflow of vector<Rva00153729>.
struct Rva00153729
{
	int a;
	Rva00153729(const Rva00153729 &that);
};
template void _STL::_Construct<Rva00153729, Rva00153729>(Rva00153729 *, const Rva00153729 &);

// And _Construct<BfmePod340> (0x004D9B98, copy constructor 0x001E4DEB),
// called by vector<BfmePod340>'s rowed uninitialized copy/fill and push_back
// (its overflow row spells the same element Rva004DA181Element).
struct BfmePod340
{
	int a;
	BfmePod340(const BfmePod340 &that);
};
template void _STL::_Construct<BfmePod340, BfmePod340>(BfmePod340 *, const BfmePod340 &);
