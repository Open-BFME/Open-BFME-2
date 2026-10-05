// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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

struct Rva003328B6Element
{
	int a;
	Rva003328B6Element(const Rva003328B6Element &that);
};

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
