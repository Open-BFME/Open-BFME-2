// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Throw()-specialized STLport _Construct<T> placement-copy helpers, 18 bytes
// each, retail 0x00053FA4, 0x0014F599, 0x0014F5D3, 0x0014F60D, 0x0039B8C6,
// 0x004EE1D0, 0x0052BD28 and 0x005DBD3D.
// Evidence: each body is byte-identical with relocations masked to the rowed
// _Construct<RvaSmartPtr12> 0x0004CC70 (stlport_construct_throw_spec.cpp),
// and its only call is the defined copy ctor of the T named here. No other
// unit emits these specializations, so plain definitions do not collide.
#include <memory>
#include <new>

class Rva00051C6C
{
public:
	Rva00051C6C(const Rva00051C6C &other);
};

class Rva0014F480
{
public:
	Rva0014F480(const Rva0014F480 &other);
};

class Rva0014F4A1
{
public:
	Rva0014F4A1(const Rva0014F4A1 &other);
};

class Rva0014F4C2
{
public:
	Rva0014F4C2(const Rva0014F4C2 &other);
};

class Rva0039B893
{
public:
	Rva0039B893(const Rva0039B893 &other);
};

class Rva003A6360Record
{
public:
	Rva003A6360Record(const Rva003A6360Record &other);
};

class Rva005DBCD1
{
public:
	Rva005DBCD1(const Rva005DBCD1 &other);
};

class Rva004E18A2
{
public:
	Rva004E18A2(const Rva004E18A2 &other);
};

namespace _STL {
template<> inline void _Construct<Rva00051C6C, Rva00051C6C>(Rva00051C6C *dest, const Rva00051C6C &source) throw() { new (dest) Rva00051C6C(source); }
template<> void _Construct<Rva0014F480, Rva0014F480>(Rva0014F480 *dest, const Rva0014F480 &source) throw() { new (dest) Rva0014F480(source); }
template<> void _Construct<Rva0014F4A1, Rva0014F4A1>(Rva0014F4A1 *dest, const Rva0014F4A1 &source) throw() { new (dest) Rva0014F4A1(source); }
template<> void _Construct<Rva0014F4C2, Rva0014F4C2>(Rva0014F4C2 *dest, const Rva0014F4C2 &source) throw() { new (dest) Rva0014F4C2(source); }
template<> void _Construct<Rva0039B893, Rva0039B893>(Rva0039B893 *dest, const Rva0039B893 &source) throw() { new (dest) Rva0039B893(source); }
template<> void _Construct<Rva003A6360Record, Rva003A6360Record>(Rva003A6360Record *dest, const Rva003A6360Record &source) throw() { new (dest) Rva003A6360Record(source); }
template<> void _Construct<Rva005DBCD1, Rva005DBCD1>(Rva005DBCD1 *dest, const Rva005DBCD1 &source) throw() { new (dest) Rva005DBCD1(source); }
template<> void _Construct<Rva004E18A2, Rva004E18A2>(Rva004E18A2 *dest, const Rva004E18A2 &source) throw() { new (dest) Rva004E18A2(source); }
}

// This function is a header inline in the copier units; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeStlportConstructCopySiblingsAnchor@@YAXXZ absent-from-retail
void _bfmeStlportConstructCopySiblingsAnchor()
{
    _STL::_Construct<Rva00051C6C, Rva00051C6C>(
        static_cast<Rva00051C6C *>(0), *static_cast<const Rva00051C6C *>(0));
}
#pragma inline_depth()
