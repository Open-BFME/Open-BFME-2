// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
//
// STLport 4.5.3 vector<T>::push_back for element types whose push_back sits
// unclaimed in retail: the 55-byte body that copy-constructs at _M_finish
// through an out-of-line _Construct and otherwise calls _M_insert_overflow
// with __false_type.  Element types are code-generation views sized from the
// stride push_back adds to _M_finish (the stlport_pod_vector_bodies.cpp
// convention).  Where retail's _Construct callee is already rowed under a
// plain type name, that name is reused; otherwise the element is named after
// the push_back address and both callees are pinned at the addresses the
// retail REL32s prove.  No element layout beyond its size is claimed.
//
//   push_back   stride  _Construct  _M_insert_overflow  element
//   0x0004CF63   12     0x0004CC70  0x0004CE90          RvaSmartPtr12 (rowed _Construct type)
//   0x0005A084    4     0x002393AA  0x00058BBD          Rva0005A084Element
//   0x00082BE6    4     0x00087A5C  0x0008257F          Rva00082BE6Element
//   0x00082C1D    4     0x00087A5C  0x00082631          Rva00082C1DElement
//   0x0008B689    4     0x00087A5C  0x0008B503          Rva0008B689Element
//   0x0008DE1C   24     0x0008A173  0x0008B6C0          Rva0008DE1CElement
//   0x000AB3E2   24     0x000A9DF8  0x000AAF09          Rva000AB3E2Element
//   0x000AB419   16     0x000A9E0A  0x000AAFC6          Rva000AB419Element
//   0x000C3411    8     0x000BBA1A  0x000C1D98          Rva000C3411Element
//   0x000CF83C    8     0x000CF4D6  0x000CF76E          Rva000CF83CElement
//   0x00153A27    8     0x004F6B7B  0x001538C9          Rva00153A27Element
//   0x001741EB   48     0x00173351  0x00173EF9          Rva001741EBElement
//   0x001DAAF2    8     0x001D9B0F  0x001DA68C          Rva001DAAF2Element
//   0x001DF3F1   48     0x001DEDA7  0x001DF21C          Rva001DF3F1Element
//   0x0020A227    8     0x0020596A  0x002098A0          Rva0020A227Element
//   0x00214243   16     0x00211DFB  0x00213E3B          Rva00214243Element
//   0x002201D5   32     0x0021FA1A  0x00220105          Rva0021F876 (rowed _Construct type)
//   0x00260B88    8     0x0026061A  0x00260AD6          Rva00260B88Element
//   0x00287F76    8     0x002861B0  0x00287B4D          Rva00287F76Element
//   0x002898AC    8     0x002889E4  0x002895F8          Rva002898ACElement
//   0x002B9062    4     0x00087A5C  0x002B8174          Rva002B9062Element
//   0x002BC58D   20     0x002B8226  0x002BC3C6          Rva002B72C9 (rowed _Construct type)
//   0x00308E2C    8     0x0030CA53  0x00282870          Rva00308E2CElement
//   0x00318203    8     0x00317CA0  0x0031809E          Rva00318203Element
//   0x0032DC80    8     0x0032ACFC  0x0032D321          Rva0032DC80Element
//   0x0032EA3F   12     0x0032B598  0x0032E842          Rva0032EA3FElement
//   0x003328B6   12     0x003324A8  0x0033270E          Rva003328B6Element
//   0x00336AEC   36     0x00333295  0x003361C6          Rva00336AECElement
//   0x0033A23A   12     0x001FF819  0x00339FA7          Rva0033A23AElement
//   0x0037FFDD   72     0x0037F71F  0x0037FF20          Rva0037FFDDElement
//   0x0039A48E    8     0x00396170  0x00399EBE          Rva0039A48EElement
//   0x0039A4C5   12     0x0039619D  0x00399F70          BfmeStringRecord00395E75 (rowed _Construct type)
//   0x003F309A   24     0x003F2980  0x003F2B0B          LivingWorldRegionConnection (rowed _Construct type)
//   0x003F7B22    4     0x002B2FE2  0x003F79A0          Rva003F7B22Element
//   0x0040457D   20     0x00403B5A  0x00404457          Rva00403927 (rowed _Construct type)
//   0x0040C0C7   40     0x0040B99F  0x0040BFF4          Rva0040C0C7Element
//   0x00413B16   24     0x0041398E  0x00413A5F          Rva00413B16Element
//   0x00414258   24     0x004140D0  0x004141A1          Rva00414258Element
//   0x00414BA4   44     0x0041432C  0x004149BF          Rva00414BA4Element
//   0x004688D1   12     0x004676EB  0x0046824A          BfmeStringRecord00466E64 (rowed _Construct type)
//   0x00475F2A    4     0x004740AD  0x00475BE8          Rva00475F2AElement
//   0x004C3F09    8     0x004C3A9F  0x004C3DF4          Rva004C3F09Element
//   0x004E3E5A   32     0x004E2F27  0x004E3D52          Rva004E3E5AElement
//   0x004F87BC    4     0x00087A5C  0x004F823B          Rva004F87BCElement
//   0x004F8D92    4     0x00087A5C  0x004F88F6          Rva004F8D92Element
//   0x004F9018   12     0x004F6B69  0x004F8A35          Rva004F9018Element
//   0x004F93B0    8     0x004F6A52  0x004F8DFD          Rva004F93B0Element
//   0x00501E3F   20     0x00500873  0x00501A7C          Rva00501E3FElement
//   0x005334A4    4     0x0053229D  0x00532ED9          Rva005334A4Element
//   0x00566303   20     0x0052C392  0x00565CEB          Rva0052BE33 (rowed _Construct type)
//   0x00566575   16     0x0052C404  0x0056644E          Rva00566575Element
//   0x005668E9   12     0x0052D355  0x005665AC          Rva005668E9Element
//   0x0056A32B   12     0x00568C83  0x0056A1E4          Rva00568A20 (rowed _Construct type)
//   0x00578425    4     0x00087A5C  0x0057833B          Rva00578425Element
//   0x005C8624   72     0x005C83CD  0x005C856D          Rva005C8624Element
//   0x005E1E9B    4     0x00087A5C  0x005E1D5D          Rva005E1E9BElement
//   0x005E825C    4     0x005E71C6  0x005E818E          Rva005E71C6Ref (pinned _Construct type)
//   0x005E2B0E    4     0x00087A5C  0x005E2A40          Rva005E2B0EElement
//   0x005EB44A   36     0x005EA9A9  0x005EB379          GeometryShape (rowed _Construct type)
//   0x005EFD53    4     0x005F09FF  0x005EFB7E          Rva005EFD53Element
//   0x005F13E6    4     0x005F09FF  0x005F131A          Rva005F13E6Element
//   0x005FA197    4     0x00087A5C  0x005F9C05          Rva005FA197Element
//   0x005FA1CE    4     0x00087A5C  0x005F9CB7          Rva005FA1CEElement
//   0x00601A3A   12     0x0060173A  0x0060197D          Rva00601A3AElement

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class RvaSmartPtr12 { public: int a[3]; };
struct Rva0005A084Element { int a[1]; };
struct Rva00082BE6Element { int a[1]; };
struct Rva00082C1DElement { int a[1]; };
struct Rva0008B689Element { int a[1]; };
struct Rva0008DE1CElement { int a[6]; };
struct Rva000AB3E2Element { int a[6]; };
struct Rva000AB419Element { int a[4]; };
struct Rva000C3411Element { int a[2]; };
struct Rva000CF83CElement { int a[2]; };
struct Rva00153A27Element { int a[2]; };
struct Rva001741EBElement { int a[12]; };
struct Rva001DAAF2Element { int a[2]; };
struct Rva001DF3F1Element { int a[12]; };
struct Rva0020A227Element { int a[2]; };
struct Rva00214243Element { int a[4]; };
class Rva0021F876 { public: int a[8]; };
struct Rva00260B88Element { int a[2]; };
struct Rva00287F76Element { int a[2]; };
struct Rva002898ACElement { int a[2]; };
struct Rva002B9062Element { int a[1]; };
struct Rva002B72C9 { int a[5]; };
struct Rva00308E2CElement { int a[2]; };
struct Rva00318203Element { int a[2]; };
struct Rva0032DC80Element { int a[2]; };
struct Rva0032EA3FElement { int a[3]; };
struct Rva003328B6Element { int a[3]; };
struct Rva00336AECElement { int a[9]; };
struct Rva0033A23AElement { int a[3]; };
struct Rva0037FFDDElement { int a[18]; };
struct Rva0039A48EElement { int a[2]; };
struct BfmeStringRecord00395E75 { int a[3]; };
class LivingWorldRegionConnection { public: int a[6]; };
struct Rva003F7B22Element { int a[1]; };
class Rva00403927 { public: int a[5]; };
struct Rva0040C0C7Element { int a[10]; };
struct Rva00413B16Element { int a[6]; };
struct Rva00414258Element { int a[6]; };
struct Rva00414BA4Element { int a[11]; };
struct BfmeStringRecord00466E64 { int a[3]; };
struct Rva00475F2AElement { int a[1]; };
struct Rva004C3F09Element { int a[2]; };
struct Rva004E3E5AElement { int a[8]; };
struct Rva004F87BCElement { int a[1]; };
struct Rva004F8D92Element { int a[1]; };
struct Rva004F9018Element { int a[3]; };
struct Rva004F93B0Element { int a[2]; };
struct Rva00501E3FElement { int a[5]; };
struct Rva005334A4Element { int a[1]; };
class Rva0052BE33 { public: int a[5]; };
struct Rva00566575Element { int a[4]; };
struct Rva005668E9Element { int a[3]; };
class Rva00568A20 { public: int a[3]; };
struct Rva00578425Element { int a[1]; };
struct Rva005C8624Element { int a[18]; };
struct Rva005E1E9BElement { int a[1]; };
struct Rva005E71C6Ref { int a[1]; };
struct Rva005E2B0EElement { int a[1]; };
struct GeometryShape { int a[9]; };
struct Rva005EFD53Element { int a[1]; };
struct Rva005F13E6Element { int a[1]; };
struct Rva005FA197Element { int a[1]; };
struct Rva005FA1CEElement { int a[1]; };
struct Rva00601A3AElement { int a[3]; };

// _Construct is declared, not defined: each call resolves to the address the
// retail push_back calls (a ledger row or a pin).
namespace _STL
{
template <> __declspec(nothrow) void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *__p, const RvaSmartPtr12 &__val);
template <> __declspec(nothrow) void _Construct<Rva0005A084Element, Rva0005A084Element>(Rva0005A084Element *__p, const Rva0005A084Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00082BE6Element, Rva00082BE6Element>(Rva00082BE6Element *__p, const Rva00082BE6Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00082C1DElement, Rva00082C1DElement>(Rva00082C1DElement *__p, const Rva00082C1DElement &__val);
template <> __declspec(nothrow) void _Construct<Rva0008B689Element, Rva0008B689Element>(Rva0008B689Element *__p, const Rva0008B689Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0008DE1CElement, Rva0008DE1CElement>(Rva0008DE1CElement *__p, const Rva0008DE1CElement &__val);
template <> __declspec(nothrow) void _Construct<Rva000AB3E2Element, Rva000AB3E2Element>(Rva000AB3E2Element *__p, const Rva000AB3E2Element &__val);
template <> __declspec(nothrow) void _Construct<Rva000AB419Element, Rva000AB419Element>(Rva000AB419Element *__p, const Rva000AB419Element &__val);
template <> __declspec(nothrow) void _Construct<Rva000C3411Element, Rva000C3411Element>(Rva000C3411Element *__p, const Rva000C3411Element &__val);
template <> __declspec(nothrow) void _Construct<Rva000CF83CElement, Rva000CF83CElement>(Rva000CF83CElement *__p, const Rva000CF83CElement &__val);
template <> __declspec(nothrow) void _Construct<Rva00153A27Element, Rva00153A27Element>(Rva00153A27Element *__p, const Rva00153A27Element &__val);
template <> __declspec(nothrow) void _Construct<Rva001741EBElement, Rva001741EBElement>(Rva001741EBElement *__p, const Rva001741EBElement &__val);
template <> __declspec(nothrow) void _Construct<Rva001DAAF2Element, Rva001DAAF2Element>(Rva001DAAF2Element *__p, const Rva001DAAF2Element &__val);
template <> __declspec(nothrow) void _Construct<Rva001DF3F1Element, Rva001DF3F1Element>(Rva001DF3F1Element *__p, const Rva001DF3F1Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0020A227Element, Rva0020A227Element>(Rva0020A227Element *__p, const Rva0020A227Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00214243Element, Rva00214243Element>(Rva00214243Element *__p, const Rva00214243Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0021F876, Rva0021F876>(Rva0021F876 *__p, const Rva0021F876 &__val);
template <> __declspec(nothrow) void _Construct<Rva00260B88Element, Rva00260B88Element>(Rva00260B88Element *__p, const Rva00260B88Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00287F76Element, Rva00287F76Element>(Rva00287F76Element *__p, const Rva00287F76Element &__val);
template <> __declspec(nothrow) void _Construct<Rva002898ACElement, Rva002898ACElement>(Rva002898ACElement *__p, const Rva002898ACElement &__val);
template <> __declspec(nothrow) void _Construct<Rva002B9062Element, Rva002B9062Element>(Rva002B9062Element *__p, const Rva002B9062Element &__val);
template <> __declspec(nothrow) void _Construct<Rva002B72C9, Rva002B72C9>(Rva002B72C9 *__p, const Rva002B72C9 &__val);
template <> __declspec(nothrow) void _Construct<Rva00308E2CElement, Rva00308E2CElement>(Rva00308E2CElement *__p, const Rva00308E2CElement &__val);
template <> __declspec(nothrow) void _Construct<Rva00318203Element, Rva00318203Element>(Rva00318203Element *__p, const Rva00318203Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0032DC80Element, Rva0032DC80Element>(Rva0032DC80Element *__p, const Rva0032DC80Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0032EA3FElement, Rva0032EA3FElement>(Rva0032EA3FElement *__p, const Rva0032EA3FElement &__val);
template <> __declspec(nothrow) void _Construct<Rva003328B6Element, Rva003328B6Element>(Rva003328B6Element *__p, const Rva003328B6Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00336AECElement, Rva00336AECElement>(Rva00336AECElement *__p, const Rva00336AECElement &__val);
template <> __declspec(nothrow) void _Construct<Rva0033A23AElement, Rva0033A23AElement>(Rva0033A23AElement *__p, const Rva0033A23AElement &__val);
template <> __declspec(nothrow) void _Construct<Rva0037FFDDElement, Rva0037FFDDElement>(Rva0037FFDDElement *__p, const Rva0037FFDDElement &__val);
template <> __declspec(nothrow) void _Construct<Rva0039A48EElement, Rva0039A48EElement>(Rva0039A48EElement *__p, const Rva0039A48EElement &__val);
template <> __declspec(nothrow) void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *__p, const BfmeStringRecord00395E75 &__val);
template <> __declspec(nothrow) void _Construct<LivingWorldRegionConnection, LivingWorldRegionConnection>(LivingWorldRegionConnection *__p, const LivingWorldRegionConnection &__val);
template <> __declspec(nothrow) void _Construct<Rva003F7B22Element, Rva003F7B22Element>(Rva003F7B22Element *__p, const Rva003F7B22Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00403927, Rva00403927>(Rva00403927 *__p, const Rva00403927 &__val);
template <> __declspec(nothrow) void _Construct<Rva0040C0C7Element, Rva0040C0C7Element>(Rva0040C0C7Element *__p, const Rva0040C0C7Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00413B16Element, Rva00413B16Element>(Rva00413B16Element *__p, const Rva00413B16Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00414258Element, Rva00414258Element>(Rva00414258Element *__p, const Rva00414258Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00414BA4Element, Rva00414BA4Element>(Rva00414BA4Element *__p, const Rva00414BA4Element &__val);
template <> __declspec(nothrow) void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *__p, const BfmeStringRecord00466E64 &__val);
template <> __declspec(nothrow) void _Construct<Rva00475F2AElement, Rva00475F2AElement>(Rva00475F2AElement *__p, const Rva00475F2AElement &__val);
template <> __declspec(nothrow) void _Construct<Rva004C3F09Element, Rva004C3F09Element>(Rva004C3F09Element *__p, const Rva004C3F09Element &__val);
template <> __declspec(nothrow) void _Construct<Rva004E3E5AElement, Rva004E3E5AElement>(Rva004E3E5AElement *__p, const Rva004E3E5AElement &__val);
template <> __declspec(nothrow) void _Construct<Rva004F87BCElement, Rva004F87BCElement>(Rva004F87BCElement *__p, const Rva004F87BCElement &__val);
template <> __declspec(nothrow) void _Construct<Rva004F8D92Element, Rva004F8D92Element>(Rva004F8D92Element *__p, const Rva004F8D92Element &__val);
template <> __declspec(nothrow) void _Construct<Rva004F9018Element, Rva004F9018Element>(Rva004F9018Element *__p, const Rva004F9018Element &__val);
template <> __declspec(nothrow) void _Construct<Rva004F93B0Element, Rva004F93B0Element>(Rva004F93B0Element *__p, const Rva004F93B0Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00501E3FElement, Rva00501E3FElement>(Rva00501E3FElement *__p, const Rva00501E3FElement &__val);
template <> __declspec(nothrow) void _Construct<Rva005334A4Element, Rva005334A4Element>(Rva005334A4Element *__p, const Rva005334A4Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *__p, const Rva0052BE33 &__val);
template <> __declspec(nothrow) void _Construct<Rva00566575Element, Rva00566575Element>(Rva00566575Element *__p, const Rva00566575Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005668E9Element, Rva005668E9Element>(Rva005668E9Element *__p, const Rva005668E9Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *__p, const Rva00568A20 &__val);
template <> __declspec(nothrow) void _Construct<Rva00578425Element, Rva00578425Element>(Rva00578425Element *__p, const Rva00578425Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005C8624Element, Rva005C8624Element>(Rva005C8624Element *__p, const Rva005C8624Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005E1E9BElement, Rva005E1E9BElement>(Rva005E1E9BElement *__p, const Rva005E1E9BElement &__val);
template <> __declspec(nothrow) void _Construct<Rva005E71C6Ref, Rva005E71C6Ref>(Rva005E71C6Ref *__p, const Rva005E71C6Ref &__val);
template <> __declspec(nothrow) void _Construct<Rva005E2B0EElement, Rva005E2B0EElement>(Rva005E2B0EElement *__p, const Rva005E2B0EElement &__val);
template <> __declspec(nothrow) void _Construct<GeometryShape, GeometryShape>(GeometryShape *__p, const GeometryShape &__val);
template <> __declspec(nothrow) void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *__p, const Rva005EFD53Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005F13E6Element, Rva005F13E6Element>(Rva005F13E6Element *__p, const Rva005F13E6Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005FA197Element, Rva005FA197Element>(Rva005FA197Element *__p, const Rva005FA197Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005FA1CEElement, Rva005FA1CEElement>(Rva005FA1CEElement *__p, const Rva005FA1CEElement &__val);
template <> __declspec(nothrow) void _Construct<Rva00601A3AElement, Rva00601A3AElement>(Rva00601A3AElement *__p, const Rva00601A3AElement &__val);
}

template void _STL::vector<RvaSmartPtr12>::push_back(const RvaSmartPtr12 &);
template void _STL::vector<Rva0005A084Element>::push_back(const Rva0005A084Element &);
template void _STL::vector<Rva00082BE6Element>::push_back(const Rva00082BE6Element &);
template void _STL::vector<Rva00082C1DElement>::push_back(const Rva00082C1DElement &);
template void _STL::vector<Rva0008B689Element>::push_back(const Rva0008B689Element &);
template void _STL::vector<Rva0008DE1CElement>::push_back(const Rva0008DE1CElement &);
template void _STL::vector<Rva000AB3E2Element>::push_back(const Rva000AB3E2Element &);
template void _STL::vector<Rva000AB419Element>::push_back(const Rva000AB419Element &);
template void _STL::vector<Rva000C3411Element>::push_back(const Rva000C3411Element &);
template void _STL::vector<Rva000CF83CElement>::push_back(const Rva000CF83CElement &);
template void _STL::vector<Rva00153A27Element>::push_back(const Rva00153A27Element &);
template void _STL::vector<Rva001741EBElement>::push_back(const Rva001741EBElement &);
template void _STL::vector<Rva001DAAF2Element>::push_back(const Rva001DAAF2Element &);
template void _STL::vector<Rva001DF3F1Element>::push_back(const Rva001DF3F1Element &);
template void _STL::vector<Rva0020A227Element>::push_back(const Rva0020A227Element &);
template void _STL::vector<Rva00214243Element>::push_back(const Rva00214243Element &);
template void _STL::vector<Rva0021F876>::push_back(const Rva0021F876 &);
template void _STL::vector<Rva00260B88Element>::push_back(const Rva00260B88Element &);
template void _STL::vector<Rva00287F76Element>::push_back(const Rva00287F76Element &);
template void _STL::vector<Rva002898ACElement>::push_back(const Rva002898ACElement &);
template void _STL::vector<Rva002B9062Element>::push_back(const Rva002B9062Element &);
template void _STL::vector<Rva002B72C9>::push_back(const Rva002B72C9 &);
template void _STL::vector<Rva00308E2CElement>::push_back(const Rva00308E2CElement &);
template void _STL::vector<Rva00318203Element>::push_back(const Rva00318203Element &);
template void _STL::vector<Rva0032DC80Element>::push_back(const Rva0032DC80Element &);
template void _STL::vector<Rva0032EA3FElement>::push_back(const Rva0032EA3FElement &);
template void _STL::vector<Rva003328B6Element>::push_back(const Rva003328B6Element &);
template void _STL::vector<Rva00336AECElement>::push_back(const Rva00336AECElement &);
template void _STL::vector<Rva0033A23AElement>::push_back(const Rva0033A23AElement &);
template void _STL::vector<Rva0037FFDDElement>::push_back(const Rva0037FFDDElement &);
template void _STL::vector<Rva0039A48EElement>::push_back(const Rva0039A48EElement &);
template void _STL::vector<BfmeStringRecord00395E75>::push_back(const BfmeStringRecord00395E75 &);
template void _STL::vector<LivingWorldRegionConnection>::push_back(const LivingWorldRegionConnection &);
template void _STL::vector<Rva003F7B22Element>::push_back(const Rva003F7B22Element &);
template void _STL::vector<Rva00403927>::push_back(const Rva00403927 &);
template void _STL::vector<Rva0040C0C7Element>::push_back(const Rva0040C0C7Element &);
template void _STL::vector<Rva00413B16Element>::push_back(const Rva00413B16Element &);
template void _STL::vector<Rva00414258Element>::push_back(const Rva00414258Element &);
template void _STL::vector<Rva00414BA4Element>::push_back(const Rva00414BA4Element &);
template void _STL::vector<BfmeStringRecord00466E64>::push_back(const BfmeStringRecord00466E64 &);
template void _STL::vector<Rva00475F2AElement>::push_back(const Rva00475F2AElement &);
template void _STL::vector<Rva004C3F09Element>::push_back(const Rva004C3F09Element &);
template void _STL::vector<Rva004E3E5AElement>::push_back(const Rva004E3E5AElement &);
template void _STL::vector<Rva004F87BCElement>::push_back(const Rva004F87BCElement &);
template void _STL::vector<Rva004F8D92Element>::push_back(const Rva004F8D92Element &);
template void _STL::vector<Rva004F9018Element>::push_back(const Rva004F9018Element &);
template void _STL::vector<Rva004F93B0Element>::push_back(const Rva004F93B0Element &);
template void _STL::vector<Rva00501E3FElement>::push_back(const Rva00501E3FElement &);
template void _STL::vector<Rva005334A4Element>::push_back(const Rva005334A4Element &);
template void _STL::vector<Rva0052BE33>::push_back(const Rva0052BE33 &);
template void _STL::vector<Rva00566575Element>::push_back(const Rva00566575Element &);
template void _STL::vector<Rva005668E9Element>::push_back(const Rva005668E9Element &);
template void _STL::vector<Rva00568A20>::push_back(const Rva00568A20 &);
template void _STL::vector<Rva00578425Element>::push_back(const Rva00578425Element &);
template void _STL::vector<Rva005C8624Element>::push_back(const Rva005C8624Element &);
template void _STL::vector<Rva005E1E9BElement>::push_back(const Rva005E1E9BElement &);
template void _STL::vector<Rva005E71C6Ref>::push_back(const Rva005E71C6Ref &);
template void _STL::vector<Rva005E2B0EElement>::push_back(const Rva005E2B0EElement &);
template void _STL::vector<GeometryShape>::push_back(const GeometryShape &);
template void _STL::vector<Rva005EFD53Element>::push_back(const Rva005EFD53Element &);
template void _STL::vector<Rva005F13E6Element>::push_back(const Rva005F13E6Element &);
template void _STL::vector<Rva005FA197Element>::push_back(const Rva005FA197Element &);
template void _STL::vector<Rva005FA1CEElement>::push_back(const Rva005FA1CEElement &);
template void _STL::vector<Rva00601A3AElement>::push_back(const Rva00601A3AElement &);

// Target 005C865B..005C8774: grid construction at two coordinates, with
// vector header +8, owner +14 and column count +18. The caller/helper chain
// establishes 72-byte cells. Nearby WB-named LargeGroupAudioGridCell methods
// supply a subsystem lead; address-derived types retain identity uncertainty.
struct Rva005C847BRecord
{
    Rva005C847BRecord(float *coordinates);
    ~Rva005C847BRecord();
    unsigned char bytes[72];
};
struct Rva005C84F1Record;
struct BfmeE16 { unsigned char bytes[16]; };
namespace _STL {
// Use the kept destructor provider; this unit does not instantiate another copy.
template <> class vector<Rva005C847BRecord, allocator<Rva005C847BRecord> >
{
public:
    ~vector();
private:
    unsigned int words[3];
};
template <> class vector<Rva005C84F1Record, allocator<Rva005C84F1Record> >
{
public:
    void reserve(unsigned int);
};
}
class AudioGridVectorHeader
{
public:
    __forceinline AudioGridVectorHeader(
        const _STL::allocator<BfmeE16> &alloc = _STL::allocator<BfmeE16>())
    {
        __assume(this != 0);
        typedef _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > Base;
        new(this) Base(alloc);
    }
    __forceinline ~AudioGridVectorHeader()
    {
        ((_STL::vector<Rva005C847BRecord> *)this)->~vector();
    }
    __forceinline void reserve(unsigned int count)
    {
        ((_STL::vector<Rva005C84F1Record> *)this)->reserve(count);
    }
    __forceinline void push_back(const Rva005C847BRecord &cell)
    {
        ((_STL::vector<Rva005C8624Element> *)this)->push_back(
            (const Rva005C8624Element &)cell);
    }
private:
    unsigned int words[3];
};
void rva005C80D1(void *, float *, float, int *, int *);
struct AudioGridCoordinates { float x, y; };
class Rva005C865B
{
public:
    Rva005C865B(void *owner, float *coordinates);
private:
    AudioGridCoordinates coordinates_;
    AudioGridVectorHeader cells_;
    void *owner_;
    int columns_;
};
// ??0Rva005C865B@@QAE@PAXPAM@Z
Rva005C865B::Rva005C865B(void *owner, float *coordinates)
    : coordinates_(*(AudioGridCoordinates *)coordinates), cells_()
{
    void *grid = (char *)owner + 0xE8;
    owner_ = owner;
    float scale = *(float *)((char *)owner + 0x10);
    int rows;
    rva005C80D1(grid, coordinates, scale, &columns_, &rows);
    cells_.reserve(columns_ * rows);
    for (int row = 0; row < rows; ++row) {
        float half = scale * 0.5f;
        float center[2];
        center[1] = row * scale + coordinates[1];
        center[1] += half;
        for (int column = 0; column < columns_; ++column) {
            center[0] = column * scale + coordinates[0] + half;
            cells_.push_back(Rva005C847BRecord(center));
        }
    }
}

// W3DView::initHeightForMap ported from Open-BFME-1 revision
// 34f59164f6d1efd413c5fd37f4894ec834c3c0fe, W3DViewInitHeightForMapBfme.cpp.
// Donor supplies algorithm and field-name leads. Target 0008D807..0008D925
// independently proves the W3DView caller chain, field offsets, clamp, scalar
// initializer ABI, camera virtuals +44/+48 and terrain virtuals +18/+9C.
// Target W3DView vftable BC756C slot21 also points directly to 48D807.
#include "ascii_string.h"

typedef float Real;
typedef bool Bool;

#include "Lib/Coord3D.h"

class Rva0030E8DF { public: void rva0030E8DF(); };
class Rva0030E961
{
public:
	void rva0030E961(const unsigned short *source, int unused,
		int sourceWidth, int sourceHeight, int state);

private:
	void *m_begin;
	void *m_finish;
	void *m_end;
	int m_width;
	int m_height;
	Real m_scale;
	int m_state;
	Bool m_ready;
};

class CameraResetAux
{
public:
	virtual void slot00();
	virtual Real slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18(Real *value, unsigned *position);
};

class WorldHeightMap
{
public:
	unsigned char m_padding00[0x08];
	int m_width;
	int m_height;
	int m_borderSize;
	unsigned char m_padding14[0x20 - 0x14];
	int m_dataSize;
	unsigned short *m_data;
	__forceinline int getWidth() const { return m_width; }
	__forceinline int getHeight() const { return m_height; }
	__forceinline int getBorderSize() const { return m_borderSize; }
	__forceinline int getDataSize() const { return m_dataSize; }
	__forceinline const unsigned short *getData() const { return m_data; }
};

class BfmeA1087
{
public:
	unsigned char m_padding00[0x37C0];
	WorldHeightMap *m_map;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, void *normal = 0) const;
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void *getTriggerAreaByName(const AsciiString &name);
};

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern TerrainLogic *TheTerrainLogic;

class W3DView
{
public:
	virtual void initHeightForMap();

private:
	unsigned char m_padding0004[0x0C - 0x04];
	Coord3D m_pos;
	unsigned char m_padding0018[0x28 - 0x18];
	unsigned m_positionState;
	unsigned char m_padding002C[0xA0 - 0x2C];
	Real m_cameraScale;
	unsigned char m_padding00A4[0x23E8 - 0xA4];
	Real m_cameraValueA;
	Real m_cameraValueB;
	unsigned char m_padding23E0[0x2408 - 0x23F0];
	Real m_groundLevel;
	unsigned char m_padding23FC[0x241C - 0x240C];
	Bool m_cameraConstraintValid;
	unsigned char m_padding240D[0x2458 - 0x241D];
	Rva0030E961 m_heightField;
	unsigned char m_padding2468[0x24BC - 0x2478];
	void *m_altCameraTrigger;
	unsigned char m_padding24B0[0x24C8 - 0x24C0];
	CameraResetAux m_cameraAux;

	void setCameraTransform();
};

void W3DView::initHeightForMap()
{
	reinterpret_cast<Rva0030E8DF *>(&m_heightField)->rva0030E8DF();

	WorldHeightMap *map = ((BfmeA1087 *)TheTerrainRenderObject)->m_map;
	if (map != 0)
	{
		m_heightField.rva0030E961(map->getData(), map->getDataSize(), map->getWidth(),
			map->getHeight(), map->getBorderSize());
	}

	m_groundLevel = TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0);
	static const Real maxGroundLevel = 700.0f;
	if (m_groundLevel > maxGroundLevel)
		m_groundLevel = maxGroundLevel;

	m_cameraAux.slot17();
	m_cameraAux.slot18(&m_cameraValueA, &m_positionState);
	m_cameraValueA *= m_cameraScale;
	m_cameraValueB = m_cameraScale * m_cameraValueB;
	m_cameraConstraintValid = false;
	setCameraTransform();

	// Target literal is VA 0x00BC7840.
	m_altCameraTrigger = TheTerrainLogic->getTriggerAreaByName(
		AsciiString("AltCamera"));
}
