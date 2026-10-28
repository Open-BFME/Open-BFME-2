// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
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
// A push_back whose growth body only its owner unit can express is rowed
// there, beside that _M_insert_overflow.
//
//   push_back   stride  _Construct  _M_insert_overflow  element
//   0x0004CF63   12     0x0004CC70  0x0004CE90          RvaSmartPtr12 (rowed _Construct type)
//   0x0005A084    4     0x002393AA  0x00058BBD          (rowed in StlSweepW5Rva00058BBD.cpp)
//   0x00082BE6    4     0x00087A5C  0x0008257F          Rva00082BE6Element
//   0x00082C1D    4     0x00087A5C  0x00082631          Rva00082C1DElement
//   0x0008B689    4     0x00087A5C  0x0008B503          Rva0008B689Element
//   0x0008DE1C   24     0x0008A173  0x0008B6C0          Rva0008DE1CElement
//   0x000AB3E2   24     0x000A9DF8  0x000AAF09          Rva000AB3E2Element
//   0x000AB419   16     0x000A9E0A  0x000AAFC6          Rva000AB419Element
//   0x000C3411    8     0x000BBA1A  0x000C1D98          (rowed in StlportVectorAsciiScalarOverflow.cpp)
//   0x000CF83C    8     0x000CF4D6  0x000CF76E          Rva000CF83CElement
//   0x00153A27    8     0x004F6B7B  0x001538C9          Rva00153A27Element
//   0x001741EB   48     0x00173351  0x00173EF9          Rva001741EBElement
//   0x001DAAF2    8     0x001D9B0F  0x001DA68C          Rva001DAAF2Element
//   0x001DF3F1   48     0x001DEDA7  0x001DF21C          Rva001DF3F1Element
//   0x0020A227    8     0x0020596A  0x002098A0          Rva0020A227Element
//   0x00214243   16     0x00211DFB  0x00213E3B          (rowed in Rva00213E3BOverflow.cpp)
//   0x002201D5   32     0x0021FA1A  0x00220105          CreateAHeroClass (rowed _Construct type)
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
//   0x00566575   16     0x0052C404  0x0056644E          (rowed in Rva0056644EOverflow.cpp)
//   0x005668E9   12     0x0052D355  0x005665AC          Rva005668E9Element
//   0x0056A32B   12     0x00568C83  0x0056A1E4          Rva00568A20 (rowed _Construct type)
//   0x00578425    4     0x00087A5C  0x0057833B          Rva00578425Element
//   0x005C8624   72     0x005C83CD  0x005C856D          (rowed in VectorOverflowRva005C856D.cpp)
//   0x005E1E9B    4     0x00087A5C  0x005E1D5D          Rva005E1E9BElement
//   0x005E825C    4     0x005E71C6  0x005E818E          Rva005E71C6Ref (pinned _Construct type)
//   0x005E2B0E    4     0x00087A5C  0x005E2A40          Rva005E2B0EElement
//   0x005EB44A   36     0x005EA9A9  0x005EB379          GeometryShape (rowed _Construct type)
//   0x005EFD53    4     0x005F09FF  0x005EFB7E          Rva005EFD53Element
//   0x005F13E6    4     0x005F09FF  0x005F131A          Rva005F13E6Element
//   0x005FA197    4     0x00087A5C  0x005F9C05          Rva005FA197Element
//   0x005FA1CE    4     0x00087A5C  0x005F9CB7          Rva005FA1CEElement
//   0x00601A3A   12     0x0060173A  0x0060197D          (rowed in StlportVectorRva00601A3A.cpp)

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Typed placement-copy declarations use their existing retail owners.
struct TreeKey00242F5E;
void __cdecl Rva002889E4Construct(TreeKey00242F5E *, const TreeKey00242F5E &);
class Rva004733E0;
void __cdecl Rva0030CA53Set(Rva004733E0 *, const Rva004733E0 *);
class Rva00332EC8;
void __cdecl Rva00333295Construct(Rva00332EC8 *, const Rva00332EC8 &);
class Rva0037F551;
void __cdecl Rva0037F71FCopy(Rva0037F551 *, const Rva0037F551 &);
struct Rva004F6966;
class Rva004C5DD0;
struct Rva004C5DD0Pair;
void __cdecl Rva004F6A52Assign(Rva004C5DD0 *, const Rva004C5DD0Pair *);

// Placement-copy owners share the target two-pointer cdecl ABI.
void __cdecl Rva001D9B0FConstruct(void *, const void *);
void __cdecl Rva00317CA0Construct(void *, const void *);
void __cdecl Rva0032ACFCConstruct(void *, const void *);
void __cdecl Rva004C3A9FConstruct(void *, const void *);

class RvaSmartPtr12 { public: int a[3]; };
struct Rva00082BE6Element { int a[1]; };
struct Rva00082C1DElement { int a[1]; };
struct Rva0008B689Element { int a[1]; };
struct Rva0008DE1CElement { int a[6]; };
struct Rva000AB3E2Element { int a[6]; };
struct Rva000AB419Element { int a[4]; };
struct Rva000CF83CElement { int a[2]; };
struct Rva00153A27Element { int a[2]; };
struct Rva001741EBElement { int a[12]; };
struct Rva001DAAF2Element { int a[2]; };
struct Rva001DF3F1Element { int a[12]; };
struct Rva0020A227Element { int a[2]; };
class CreateAHeroManager { public: class CreateAHeroClass; };
typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;

class CreateAHeroManager::CreateAHeroClass { public: int a[8]; };
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
struct Rva0040C0C7Element { virtual ~Rva0040C0C7Element(); int a[9]; };
struct Rva00413B16Element { int a[6]; };
struct Rva00414258Element { int a[6]; };
struct Rva00414BA4Element { int a[11]; };
struct BfmeStringRecord00466E64 { int a[3]; };
struct Rva00475F2AElement { int a[1]; };
// bfme link decl-only Rva00475F2AElement
namespace _STL { template <> void vector<Rva00475F2AElement, allocator<Rva00475F2AElement> >::_M_clear(); }
struct Rva004C3F09Element { int a[2]; };
struct Rva004E3E5AElement { int a[8]; };
// The native24B placement copy87A5C copies the pointer and increments
// pointee refs4; native198B insertion4F9658 retains then releases its
// temporary with7DEEF. Keep this4B owning element consistent with that
// independently verified consumer rather than the old size-only view.
struct TargetRef00217D4C {virtual void *destroy(unsigned); int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva004F87BCElement {
 TargetRef00217D4C *m_ptr;
 Rva004F87BCElement(TargetRef00217D4C *p):m_ptr(p) {if(p) ++p->references;}
 Rva004F87BCElement(const Rva004F87BCElement &p):m_ptr(p.m_ptr) {if(m_ptr) ++m_ptr->references;}
 ~Rva004F87BCElement() {if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);}
};
struct Rva004F8D92Element { int a[1]; };
struct Rva004F9018Element { int a[3]; };
struct Rva004F93B0Element { int a[2]; };
struct Rva00501E3FElement { int a[5]; };
struct Rva005334A4Element { int a[1]; };
class Rva0052BE33 { public: int a[5]; };
struct Rva005668E9Element { int a[3]; };
class Rva00568A20 { public: int a[3]; };
struct Rva00578425Element { int a[1]; };
struct Rva005C8624Element { int a[18]; };
struct Rva005E1E9BElement { int a[1]; };
struct Rva005E71C6Ref { int a[1]; };
struct Rva005E2B0EElement { int a[1]; };
struct GeometryShape { int a[9]; };
#include "../../../../GameEngine/Source/Common/RegionIconSlotReferenceView.h"
struct Rva005F13E6Element { int a[1]; };
struct Rva005FA197Element { int a[1]; };
struct Rva005FA1CEElement { int a[1]; };

// The overflow/growth/destroy helpers the held vector<...> units own are
// emitted here too, and this TU's private-POD copies of them sort first in
// link order and win. Declaring the explicit specializations stops this TU
// emitting its (non-retail) copies, so the units below link to the providers
// they name:
//   StlportVectorRva005C8624AllocateCopy.cpp   (Rva005C8624Element)
//   stlport_vector_Rva0040C0C7_overflow.cpp    (Rva0040C0C7Element)
//   StlportVectorRva004E3E5AGrowth.cpp         (Rva004E3E5AElement)
//   StlportVectorOverflow0008257F.cpp          (Rva00082BE6Element)
//   StlportVectorOverflow00082631.cpp          (Rva00082C1DElement)
//
// Rva0040C0C7Element is the exception: retail's _M_insert_overflow at
// 0x0040BFF4 (owned retail-identically by
// stlport_vector_Rva0040C0C7_overflow.cpp) proves the 40-byte element has a
// virtual destructor, not the flat int[10] this TU used to assume. The
// polymorphic view (vptr + int[9], still 40 bytes) makes this TU's
// _Destroy/__destroy_aux/_M_clear copies bit-identical to the held unit's,
// and this TU sorts first in link order (0x4CF63 < 0x40C0C7), so they win
// retail-side. Declaring those three for Rva0040C0C7 instead leaves the held
// unit blocked by the peer POD copies (AwardSystemManager.obj).
namespace _STL {
template <> void _Destroy<Rva00082BE6Element *>(Rva00082BE6Element *, Rva00082BE6Element *);
template <> void _Destroy<Rva00082C1DElement *>(Rva00082C1DElement *, Rva00082C1DElement *);
template <> void _Destroy<Rva0008B689Element *>(Rva0008B689Element *, Rva0008B689Element *);
template <> void __destroy_aux<Rva00082BE6Element *>(Rva00082BE6Element *, Rva00082BE6Element *, const __false_type &);
template <> void __destroy_aux<Rva00082C1DElement *>(Rva00082C1DElement *, Rva00082C1DElement *, const __false_type &);
template <> void vector<Rva00082BE6Element, allocator<Rva00082BE6Element> >::_M_clear();
template <> void vector<Rva00082C1DElement, allocator<Rva00082C1DElement> >::_M_clear();
template <> void vector<Rva004E3E5AElement, allocator<Rva004E3E5AElement> >::_M_clear();
template <> void vector<Rva005C8624Element, allocator<Rva005C8624Element> >::_M_clear();
}

// Placement-copy and growth owners rowed under other names: push_back reaches
// the retail row through the inline forwarders below.
class Rva003AD160;
struct BfmeStringRecord005DDD40;
struct BfmeE8;
enum ScienceType { SCIENCE_INVALID = -1 };
class Rva004F6093Holder;
class Object;
void __cdecl Rva0026061AConstruct(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
void __cdecl Rva002B2FE2Copy(Rva004F6093Holder *, const Rva004F6093Holder &);
struct Rva005C856DRecord { int a[18]; };
namespace _STL
{
template <class _Tp, class _Alloc> class list;
template <> void _Construct<Rva003AD160, Rva003AD160>(Rva003AD160 *, const Rva003AD160 &) throw();
template <> void _Construct<vector<BfmeE8>, vector<BfmeE8> >(vector<BfmeE8> *, const vector<BfmeE8> &) throw();
template <> void _Construct<vector<ScienceType>, vector<ScienceType> >(vector<ScienceType> *, const vector<ScienceType> &) throw();
template <> void _Construct<list<Object *, allocator<Object *> >, list<Object *, allocator<Object *> > >(list<Object *, allocator<Object *> > *, const list<Object *, allocator<Object *> > &) throw();
}
// The clear worker of this vector is rowed as Rva002B61DD::rva002B61DD.
struct Rva002B61DD { void rva002B61DD(); };
namespace _STL { template <> __declspec(dllimport) __forceinline void vector<Rva003F7B22Element, allocator<Rva003F7B22Element> >::_M_clear() { ((Rva002B61DD *)this)->rva002B61DD(); } }

// The six-byte placement copy is rowed at 0x002861B0.
__declspec(nothrow) void __cdecl Rva002861B0Copy(void *, const void *);
// The four-byte placement copy (a counted pointer) is rowed at 0x00087A5C.
__declspec(nothrow) void __cdecl Rva00087A5CCopy(void **, void **);
// Placement-copy calls bind to the ledger or pinned owners retail calls.
namespace _STL
{
template <> __declspec(nothrow) void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *__p, const RvaSmartPtr12 &__val);
template <> __declspec(nothrow) void _Construct<Rva00082BE6Element, Rva00082BE6Element>(Rva00082BE6Element *__p, const Rva00082BE6Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00082C1DElement, Rva00082C1DElement>(Rva00082C1DElement *__p, const Rva00082C1DElement &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva0008B689Element, Rva0008B689Element>(Rva0008B689Element *__p, const Rva0008B689Element &__val)
{ Rva00087A5CCopy((void **)__p, (void **)&__val); }
template <> __declspec(nothrow) void _Construct<Rva0008DE1CElement, Rva0008DE1CElement>(Rva0008DE1CElement *__p, const Rva0008DE1CElement &__val);
template <> __declspec(nothrow) void _Construct<Rva000AB3E2Element, Rva000AB3E2Element>(Rva000AB3E2Element *__p, const Rva000AB3E2Element &__val);
template <> __declspec(nothrow) void _Construct<Rva000AB419Element, Rva000AB419Element>(Rva000AB419Element *__p, const Rva000AB419Element &__val);
template <> __declspec(nothrow) void _Construct<Rva000CF83CElement, Rva000CF83CElement>(Rva000CF83CElement *__p, const Rva000CF83CElement &__val);
template <> __declspec(nothrow) void _Construct<Rva00153A27Element, Rva00153A27Element>(Rva00153A27Element *__p, const Rva00153A27Element &__val);
template <> __declspec(nothrow) void _Construct<Rva001741EBElement, Rva001741EBElement>(Rva001741EBElement *__p, const Rva001741EBElement &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva001DAAF2Element, Rva001DAAF2Element>(Rva001DAAF2Element *__p, const Rva001DAAF2Element &__val)
{ Rva001D9B0FConstruct(__p, &__val); }
template <> __declspec(nothrow) void _Construct<Rva001DF3F1Element, Rva001DF3F1Element>(Rva001DF3F1Element *__p, const Rva001DF3F1Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0020A227Element, Rva0020A227Element>(Rva0020A227Element *__p, const Rva0020A227Element &__val);
template <> __declspec(nothrow) void _Construct<CreateAHeroClass, CreateAHeroClass>(CreateAHeroClass *__p, const CreateAHeroClass &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00260B88Element, Rva00260B88Element>(Rva00260B88Element *__p, const Rva00260B88Element &__val)
{ Rva0026061AConstruct(reinterpret_cast<BfmeStringRecord005DDD40 *>(__p), *reinterpret_cast<const BfmeStringRecord005DDD40 *>(&__val)); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void
_Construct<Rva00287F76Element, Rva00287F76Element>(Rva00287F76Element *__p, const Rva00287F76Element &__val)
{ Rva002861B0Copy(__p, &__val); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva002898ACElement, Rva002898ACElement>(Rva002898ACElement *__p, const Rva002898ACElement &__val)
{ Rva002889E4Construct(reinterpret_cast<TreeKey00242F5E *>(__p), *reinterpret_cast<const TreeKey00242F5E *>(&__val)); }
template <> __declspec(nothrow) void _Construct<Rva002B9062Element, Rva002B9062Element>(Rva002B9062Element *__p, const Rva002B9062Element &__val);
template <> __declspec(nothrow) void _Construct<Rva002B72C9, Rva002B72C9>(Rva002B72C9 *__p, const Rva002B72C9 &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00308E2CElement, Rva00308E2CElement>(Rva00308E2CElement *__p, const Rva00308E2CElement &__val)
{ Rva0030CA53Set(reinterpret_cast<Rva004733E0 *>(__p), reinterpret_cast<const Rva004733E0 *>(&__val)); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00318203Element, Rva00318203Element>(Rva00318203Element *__p, const Rva00318203Element &__val)
{ Rva00317CA0Construct(__p, &__val); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva0032DC80Element, Rva0032DC80Element>(Rva0032DC80Element *__p, const Rva0032DC80Element &__val)
{ Rva0032ACFCConstruct(__p, &__val); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva0032EA3FElement, Rva0032EA3FElement>(Rva0032EA3FElement *__p, const Rva0032EA3FElement &__val)
{ _Construct(reinterpret_cast<vector<BfmeE8> *>(__p), *reinterpret_cast<const vector<BfmeE8> *>(&__val)); }
template <> __declspec(nothrow) void _Construct<Rva003328B6Element, Rva003328B6Element>(Rva003328B6Element *__p, const Rva003328B6Element &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00336AECElement, Rva00336AECElement>(Rva00336AECElement *__p, const Rva00336AECElement &__val)
{ Rva00333295Construct(reinterpret_cast<Rva00332EC8 *>(__p), *reinterpret_cast<const Rva00332EC8 *>(&__val)); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva0033A23AElement, Rva0033A23AElement>(Rva0033A23AElement *__p, const Rva0033A23AElement &__val)
{ _Construct(reinterpret_cast<vector<ScienceType> *>(__p), *reinterpret_cast<const vector<ScienceType> *>(&__val)); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva0037FFDDElement, Rva0037FFDDElement>(Rva0037FFDDElement *__p, const Rva0037FFDDElement &__val)
{ Rva0037F71FCopy(reinterpret_cast<Rva0037F551 *>(__p), *reinterpret_cast<const Rva0037F551 *>(&__val)); }
template <> __declspec(nothrow) void _Construct<Rva0039A48EElement, Rva0039A48EElement>(Rva0039A48EElement *__p, const Rva0039A48EElement &__val);
template <> __declspec(nothrow) void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *__p, const BfmeStringRecord00395E75 &__val);
template <> __declspec(nothrow) void _Construct<LivingWorldRegionConnection, LivingWorldRegionConnection>(LivingWorldRegionConnection *__p, const LivingWorldRegionConnection &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva003F7B22Element, Rva003F7B22Element>(Rva003F7B22Element *__p, const Rva003F7B22Element &__val)
{ Rva002B2FE2Copy(reinterpret_cast<Rva004F6093Holder *>(__p), *reinterpret_cast<const Rva004F6093Holder *>(&__val)); }
template <> __declspec(nothrow) void _Construct<Rva00403927, Rva00403927>(Rva00403927 *__p, const Rva00403927 &__val);
template <> __declspec(nothrow) void _Construct<Rva0040C0C7Element, Rva0040C0C7Element>(Rva0040C0C7Element *__p, const Rva0040C0C7Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00413B16Element, Rva00413B16Element>(Rva00413B16Element *__p, const Rva00413B16Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00414258Element, Rva00414258Element>(Rva00414258Element *__p, const Rva00414258Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00414BA4Element, Rva00414BA4Element>(Rva00414BA4Element *__p, const Rva00414BA4Element &__val);
template <> __declspec(nothrow) void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *__p, const BfmeStringRecord00466E64 &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00475F2AElement, Rva00475F2AElement>(Rva00475F2AElement *__p, const Rva00475F2AElement &__val)
{ _Construct(reinterpret_cast<list<Object *, allocator<Object *> > *>(__p), *reinterpret_cast<const list<Object *, allocator<Object *> > *>(&__val)); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva004C3F09Element, Rva004C3F09Element>(Rva004C3F09Element *__p, const Rva004C3F09Element &__val)
{ Rva004C3A9FConstruct(__p, &__val); }
template <> __declspec(nothrow) void _Construct<Rva004E3E5AElement, Rva004E3E5AElement>(Rva004E3E5AElement *__p, const Rva004E3E5AElement &__val);
template <> __declspec(nothrow) void _Construct<Rva004F87BCElement, Rva004F87BCElement>(Rva004F87BCElement *__p, const Rva004F87BCElement &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva004F8D92Element, Rva004F8D92Element>(Rva004F8D92Element *__p, const Rva004F8D92Element &__val)
{ _Construct(reinterpret_cast<Rva004F87BCElement *>(__p), *reinterpret_cast<const Rva004F87BCElement *>(&__val)); }
template <> void _Construct<Rva004F6966, Rva004F6966>(Rva004F6966 *, const Rva004F6966 &);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva004F9018Element, Rva004F9018Element>(Rva004F9018Element *__p, const Rva004F9018Element &__val)
{ _Construct(reinterpret_cast<Rva004F6966 *>(__p), *reinterpret_cast<const Rva004F6966 *>(&__val)); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva004F93B0Element, Rva004F93B0Element>(Rva004F93B0Element *__p, const Rva004F93B0Element &__val)
{ Rva004F6A52Assign(reinterpret_cast<Rva004C5DD0 *>(__p), reinterpret_cast<const Rva004C5DD0Pair *>(&__val)); }
template <> __declspec(nothrow) void _Construct<Rva00501E3FElement, Rva00501E3FElement>(Rva00501E3FElement *__p, const Rva00501E3FElement &__val);
template <> __declspec(nothrow) void _Construct<Rva005334A4Element, Rva005334A4Element>(Rva005334A4Element *__p, const Rva005334A4Element &__val);
template <> __declspec(nothrow) void _Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *__p, const Rva0052BE33 &__val);
template <> __declspec(nothrow) void _Construct<Rva005668E9Element, Rva005668E9Element>(Rva005668E9Element *__p, const Rva005668E9Element &__val);
template <> __declspec(nothrow) void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *__p, const Rva00568A20 &__val);
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00578425Element, Rva00578425Element>(Rva00578425Element *__p, const Rva00578425Element &__val)
{ Rva00087A5CCopy((void **)__p, (void **)&__val); }
template <> __declspec(nothrow) void _Construct<Rva005C8624Element, Rva005C8624Element>(Rva005C8624Element *__p, const Rva005C8624Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005E1E9BElement, Rva005E1E9BElement>(Rva005E1E9BElement *__p, const Rva005E1E9BElement &__val);
template <> __declspec(nothrow) void _Construct<Rva005E71C6Ref, Rva005E71C6Ref>(Rva005E71C6Ref *__p, const Rva005E71C6Ref &__val);
template <> __declspec(nothrow) void _Construct<Rva005E2B0EElement, Rva005E2B0EElement>(Rva005E2B0EElement *__p, const Rva005E2B0EElement &__val);
template <> __declspec(nothrow) void _Construct<GeometryShape, GeometryShape>(GeometryShape *__p, const GeometryShape &__val);
template <> __declspec(nothrow) void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *__p, const Rva005EFD53Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005F13E6Element, Rva005F13E6Element>(Rva005F13E6Element *__p, const Rva005F13E6Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005FA197Element, Rva005FA197Element>(Rva005FA197Element *__p, const Rva005FA197Element &__val);
template <> __declspec(nothrow) void _Construct<Rva005FA1CEElement, Rva005FA1CEElement>(Rva005FA1CEElement *__p, const Rva005FA1CEElement &__val);
}


template void _STL::vector<RvaSmartPtr12>::push_back(const RvaSmartPtr12 &);
template void _STL::vector<Rva00082BE6Element>::push_back(const Rva00082BE6Element &);
template void _STL::vector<Rva00082C1DElement>::push_back(const Rva00082C1DElement &);
template void _STL::vector<Rva0008B689Element>::push_back(const Rva0008B689Element &);
template void _STL::vector<Rva0008DE1CElement>::push_back(const Rva0008DE1CElement &);
template void _STL::vector<Rva000AB3E2Element>::push_back(const Rva000AB3E2Element &);
template void _STL::vector<Rva000AB419Element>::push_back(const Rva000AB419Element &);
template void _STL::vector<Rva000CF83CElement>::push_back(const Rva000CF83CElement &);
template void _STL::vector<Rva00153A27Element>::push_back(const Rva00153A27Element &);
template void _STL::vector<Rva001741EBElement>::push_back(const Rva001741EBElement &);
template void _STL::vector<Rva001DAAF2Element>::push_back(const Rva001DAAF2Element &);
template void _STL::vector<Rva001DF3F1Element>::push_back(const Rva001DF3F1Element &);
template void _STL::vector<Rva0020A227Element>::push_back(const Rva0020A227Element &);
template void _STL::vector<CreateAHeroClass>::push_back(const CreateAHeroClass &);
template void _STL::vector<Rva00260B88Element>::push_back(const Rva00260B88Element &);
template void _STL::vector<Rva00287F76Element>::push_back(const Rva00287F76Element &);
template void _STL::vector<Rva002898ACElement>::push_back(const Rva002898ACElement &);
// The complete clear worker is owned by StlportVectorClearRva00577EF1.cpp.
template <> void _STL::vector<Rva002B9062Element>::_M_clear();

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
template void _STL::vector<Rva005668E9Element>::push_back(const Rva005668E9Element &);
template void _STL::vector<Rva00568A20>::push_back(const Rva00568A20 &);
template void _STL::vector<Rva00578425Element>::push_back(const Rva00578425Element &);
template void _STL::vector<Rva005E1E9BElement>::push_back(const Rva005E1E9BElement &);
template void _STL::vector<Rva005E71C6Ref>::push_back(const Rva005E71C6Ref &);
template void _STL::vector<Rva005E2B0EElement>::push_back(const Rva005E2B0EElement &);
template void _STL::vector<GeometryShape>::push_back(const GeometryShape &);
template void _STL::vector<Rva005EFD53Element>::push_back(const Rva005EFD53Element &);
template void _STL::vector<Rva005F13E6Element>::push_back(const Rva005F13E6Element &);
template void _STL::vector<Rva005FA197Element>::push_back(const Rva005FA197Element &);
template void _STL::vector<Rva005FA1CEElement>::push_back(const Rva005FA1CEElement &);

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
namespace _STL { template <> void vector<Rva005C856DRecord, allocator<Rva005C856DRecord> >::push_back(const Rva005C856DRecord &); }
#include "../../../Include/Lib/BfmeE16.h"
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
        ((_STL::vector<Rva005C856DRecord> *)this)->push_back(
            (const Rva005C856DRecord &)cell);
    }
private:
    unsigned int words[3];
};
struct Rva005C80D1Origin;
struct Rva005C80D1Point;
void Rva005C80D1Cell(const Rva005C80D1Origin *, const Rva005C80D1Point *, float, int *, int *);
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
    Rva005C80D1Cell((const Rva005C80D1Origin *)grid,
        (const Rva005C80D1Point *)coordinates, scale, &columns_, &rows);
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
// bfme link decl-only begin
namespace _STL { template <> void _Construct<GeometryShape, GeometryShape>(GeometryShape *, GeometryShape const &); }
namespace _STL { template <> void _Destroy<Rva004F9018Element *>(Rva004F9018Element *, Rva004F9018Element *); }
namespace _STL { template <> void _Destroy<Rva005E71C6Ref *>(Rva005E71C6Ref *, Rva005E71C6Ref *); }
namespace _STL { template <> void _Destroy<Rva00568A20 *>(Rva00568A20 *, Rva00568A20 *); }
namespace _STL { template <> void _Destroy<RvaSmartPtr12 *>(RvaSmartPtr12 *, RvaSmartPtr12 *); }
namespace _STL { template <> void _Destroy<Rva00501E3FElement>(Rva00501E3FElement *); }
namespace _STL { template <> void _Destroy<RvaSmartPtr12>(RvaSmartPtr12 *); }
namespace _STL { template <> void vector<GeometryShape, allocator<GeometryShape> >::_M_clear(); }
namespace _STL { template <> void vector<Rva00413B16Element, allocator<Rva00413B16Element> >::_M_clear(); }
namespace _STL { template <> void vector<Rva004F9018Element, allocator<Rva004F9018Element> >::_M_clear(); }
namespace _STL { template <> void vector<CreateAHeroClass, allocator<CreateAHeroClass> >::_M_clear(); }
namespace _STL { template <> void vector<Rva00403927, allocator<Rva00403927> >::_M_clear(); }
namespace _STL { template <> void vector<RvaSmartPtr12, allocator<RvaSmartPtr12> >::_M_clear(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@URva000CF83CElement@@V?$allocator@URva000CF83CElement@@@_STL@@@_STL@@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva000CF83CElement;
namespace _STL { template <> void vector<Rva000CF83CElement,allocator<Rva000CF83CElement> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00501E3FElement@@@_STL@@YAXPAURva00501E3FElement@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00501E3FElement;
namespace _STL { template <> void _Destroy<Rva00501E3FElement *>(Rva00501E3FElement *,Rva00501E3FElement *); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@URva0020A227Element@@V?$allocator@URva0020A227Element@@@_STL@@@_STL@@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0020A227Element;
namespace _STL { template <> void vector<Rva0020A227Element,allocator<Rva0020A227Element> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva0020A227Element@@@_STL@@YAXPAURva0020A227Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0020A227Element;
namespace _STL { template <> void _Destroy<Rva0020A227Element *>(Rva0020A227Element *,Rva0020A227Element *); }
// Retail's 4-byte vectors share one clear worker (0x00577EF1, rowed as
// vector<Rva002B9062Element>::_M_clear); this view reaches the protected member.
struct Rva002B9062ClearAccess : _STL::vector<Rva002B9062Element>
{
	__forceinline void clearWorker() { _M_clear(); }
};
struct Rva005FA1CEElement;
namespace _STL { template <> __declspec(dllimport) __forceinline void vector<Rva005FA1CEElement,allocator<Rva005FA1CEElement> >::_M_clear() { ((Rva002B9062ClearAccess *)this)->clearWorker(); } }
// Retail calls each of these helpers out of line at an address the ledger
// already rows under another spelling; each forwarder reaches that row with
// the call shape of the helper it replaces (generated from the retail REL32s).
class LivingWorldRegionConnection;
class Rva004E366E;
class Rva0052BE33;
struct BfmeAssignRecord44;
struct BfmeStringRecord00466E64;
struct BfmeStringRecord005DDD40;
struct DynamicPortalLink;
struct Elem00467DCD;
struct Rva001DF3F1Element;
struct Rva0022CD2A;
struct Rva00260B88Element;
struct Rva0027EA49;
struct Rva00308E2CElement;
struct Rva0032DC80Element;
struct Rva0032EA3FElement;
struct Rva0033A23AElement;
struct Rva00414258Element;
struct Rva00414BA4Element;
struct Rva00414BDBElement;
struct Rva004F6986;
struct Rva004F8D92Element;
struct Rva004F93B0Element;
struct Rva0052BF9BElem;
struct Rva005668E9Element;
struct RvaPair0032C0CA;
struct TreeHintRef00217D4C;
void __cdecl Rva00467DCDDestroy(Elem00467DCD *,Elem00467DCD *);
namespace _STL { template <> void __destroy_aux<struct Rva00414BDBElement *>(Rva00414BDBElement *,Rva00414BDBElement *,_STL::__false_type const &); }
namespace _STL { template <> void _Destroy<struct BfmeStringRecord005DDD40 *>(BfmeStringRecord005DDD40 *,BfmeStringRecord005DDD40 *); }
namespace _STL { template <> void _Destroy<struct Rva0027EA49 *>(Rva0027EA49 *,Rva0027EA49 *); }
void __cdecl Rva0032C0CADestroyPairs(RvaPair0032C0CA *,RvaPair0032C0CA *);
namespace _STL { template <> void _Destroy<struct DynamicPortalLink *>(DynamicPortalLink *,DynamicPortalLink *); }
void __cdecl Rva0022D941Destroy(Rva0022CD2A *,Rva0022CD2A *);
namespace _STL { template <> void _Destroy<struct BfmeAssignRecord44 *>(BfmeAssignRecord44 *,BfmeAssignRecord44 *); }
namespace _STL { template <> void _Destroy<struct TreeHintRef00217D4C *>(TreeHintRef00217D4C *,TreeHintRef00217D4C *); }
void __cdecl Rva004F8373Destroy(Rva004F6986 *,Rva004F6986 *);
void __cdecl Rva0052CEF6Clear(Rva004E366E *,Rva004E366E *);
void __cdecl Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *,LivingWorldRegionConnection *);
void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *,Rva0052BF9BElem *);
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct BfmeStringRecord00466E64 *>(BfmeStringRecord00466E64 * a0, BfmeStringRecord00466E64 * a1)
{ ((void (__cdecl *)(BfmeStringRecord00466E64 *,BfmeStringRecord00466E64 *))(void (__cdecl *)(Elem00467DCD *,Elem00467DCD *))&Rva00467DCDDestroy)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva001DF3F1Element *>(Rva001DF3F1Element * a0, Rva001DF3F1Element * a1)
{ ((void (__cdecl *)(Rva001DF3F1Element *,Rva001DF3F1Element *))(void (__cdecl *)(Rva00414BDBElement *,Rva00414BDBElement *,_STL::__false_type const &))&_STL::__destroy_aux<Rva00414BDBElement *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00260B88Element *>(Rva00260B88Element * a0, Rva00260B88Element * a1)
{ ((void (__cdecl *)(Rva00260B88Element *,Rva00260B88Element *))(void (__cdecl *)(BfmeStringRecord005DDD40 *,BfmeStringRecord005DDD40 *))&_STL::_Destroy<BfmeStringRecord005DDD40 *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00308E2CElement *>(Rva00308E2CElement * a0, Rva00308E2CElement * a1)
{ ((void (__cdecl *)(Rva00308E2CElement *,Rva00308E2CElement *))(void (__cdecl *)(Rva0027EA49 *,Rva0027EA49 *))&_STL::_Destroy<Rva0027EA49 *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva0032DC80Element *>(Rva0032DC80Element * a0, Rva0032DC80Element * a1)
{ ((void (__cdecl *)(Rva0032DC80Element *,Rva0032DC80Element *))(void (__cdecl *)(RvaPair0032C0CA *,RvaPair0032C0CA *))&Rva0032C0CADestroyPairs)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva0032EA3FElement *>(Rva0032EA3FElement * a0, Rva0032EA3FElement * a1)
{ ((void (__cdecl *)(Rva0032EA3FElement *,Rva0032EA3FElement *))(void (__cdecl *)(DynamicPortalLink *,DynamicPortalLink *))&_STL::_Destroy<DynamicPortalLink *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva0033A23AElement *>(Rva0033A23AElement * a0, Rva0033A23AElement * a1)
{ ((void (__cdecl *)(Rva0033A23AElement *,Rva0033A23AElement *))(void (__cdecl *)(DynamicPortalLink *,DynamicPortalLink *))&_STL::_Destroy<DynamicPortalLink *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00414258Element *>(Rva00414258Element * a0, Rva00414258Element * a1)
{ ((void (__cdecl *)(Rva00414258Element *,Rva00414258Element *))(void (__cdecl *)(Rva0022CD2A *,Rva0022CD2A *))&Rva0022D941Destroy)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00414BA4Element *>(Rva00414BA4Element * a0, Rva00414BA4Element * a1)
{ ((void (__cdecl *)(Rva00414BA4Element *,Rva00414BA4Element *))(void (__cdecl *)(BfmeAssignRecord44 *,BfmeAssignRecord44 *))&_STL::_Destroy<BfmeAssignRecord44 *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva004F8D92Element *>(Rva004F8D92Element * a0, Rva004F8D92Element * a1)
{ ((void (__cdecl *)(Rva004F8D92Element *,Rva004F8D92Element *))(void (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *))&_STL::_Destroy<TreeHintRef00217D4C *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva004F93B0Element *>(Rva004F93B0Element * a0, Rva004F93B0Element * a1)
{ ((void (__cdecl *)(Rva004F93B0Element *,Rva004F93B0Element *))(void (__cdecl *)(Rva004F6986 *,Rva004F6986 *))&Rva004F8373Destroy)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva005668E9Element *>(Rva005668E9Element * a0, Rva005668E9Element * a1)
{ ((void (__cdecl *)(Rva005668E9Element *,Rva005668E9Element *))(void (__cdecl *)(Rva004E366E *,Rva004E366E *))&Rva0052CEF6Clear)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<class LivingWorldRegionConnection *>(LivingWorldRegionConnection * a0, LivingWorldRegionConnection * a1)
{ ((void (__cdecl *)(LivingWorldRegionConnection *,LivingWorldRegionConnection *))(void (__cdecl *)(LivingWorldRegionConnection *,LivingWorldRegionConnection *))&Rva003F0CA1_DestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<class Rva0052BE33 *>(Rva0052BE33 * a0, Rva0052BE33 * a1)
{ ((void (__cdecl *)(Rva0052BE33 *,Rva0052BE33 *))(void (__cdecl *)(Rva0052BF9BElem *,Rva0052BF9BElem *))&Rva0022C8E3DestroyRange)(a0, a1); } }

struct Rva005FA197Element;
namespace _STL { template <> __declspec(dllimport) __forceinline void vector<Rva005FA197Element,allocator<Rva005FA197Element> >::_M_clear() { ((Rva002B9062ClearAccess *)this)->clearWorker(); } }
// _M_clear of these vectors is retail's shared clear worker of another vector
// (ICF), the same forwarders StlportVectorInsertOverflowFamily.cpp uses: this
// unit's growth-path copies then match the kept ones and reference no unrowed
// _Destroy instance (that unit no longer emits one).
struct Rva005F8F96;
struct BfmeStringRecord00426A5B;
class CameraMarker;
struct Rva002BB6BE20Rec;
class Rva0026E5B9 { public: ~Rva0026E5B9(); };
class Rva00399800 { public: ~Rva00399800(); };
struct Rva005F120F { void rva005F120F(); };
template <> void _STL::vector<Rva005F8F96>::_M_clear();
template <> void _STL::vector<BfmeStringRecord00426A5B>::_M_clear();
template <> void _STL::vector<CameraMarker>::_M_clear();
template <> void _STL::vector<Rva002BB6BE20Rec>::_M_clear();
template <class _Tp> struct ClearOwner : _STL::vector<_Tp> { public: using _STL::vector<_Tp>::_M_clear; };
namespace _STL
{
#define BFME_CLEAR_FORWARD(T, CALL) \
    template <> __declspec(dllimport) __forceinline void vector<T, allocator<T> >::_M_clear() { CALL; }
BFME_CLEAR_FORWARD(Rva00153A27Element, ((ClearOwner<Rva005F8F96> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva001DAAF2Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva002898ACElement, ((ClearOwner<CameraMarker> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva002B72C9, ((ClearOwner<Rva002BB6BE20Rec> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva00318203Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva003328B6Element, ((Rva0026E5B9 *)this)->Rva0026E5B9::~Rva0026E5B9())
BFME_CLEAR_FORWARD(Rva0039A48EElement, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva004C3F09Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva00578425Element, ((Rva002B9062ClearAccess *)this)->clearWorker())
BFME_CLEAR_FORWARD(Rva005E2B0EElement, ((Rva002B9062ClearAccess *)this)->clearWorker())
BFME_CLEAR_FORWARD(Rva005F13E6Element, ((Rva005F120F *)this)->rva005F120F())
BFME_CLEAR_FORWARD(BfmeStringRecord00395E75, ((Rva00399800 *)this)->Rva00399800::~Rva00399800())
#undef BFME_CLEAR_FORWARD
}
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva004C3F09Element@@@_STL@@YAXPAURva004C3F09Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004C3F09Element;
namespace _STL { template <> void _Destroy<Rva004C3F09Element *>(Rva004C3F09Element *,Rva004C3F09Element *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAUBfmeStringRecord00395E75@@@_STL@@YAXPAUBfmeStringRecord00395E75@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord00395E75;
namespace _STL { template <> void _Destroy<BfmeStringRecord00395E75 *>(BfmeStringRecord00395E75 *,BfmeStringRecord00395E75 *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva0039A48EElement@@@_STL@@YAXPAURva0039A48EElement@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0039A48EElement;
namespace _STL { template <> void _Destroy<Rva0039A48EElement *>(Rva0039A48EElement *,Rva0039A48EElement *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva003328B6Element@@@_STL@@YAXPAURva003328B6Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003328B6Element;
namespace _STL { template <> void _Destroy<Rva003328B6Element *>(Rva003328B6Element *,Rva003328B6Element *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva005E1E9BElement@@@_STL@@YAXPAURva005E1E9BElement@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005E1E9BElement;
namespace _STL { template <> void _Destroy<Rva005E1E9BElement *>(Rva005E1E9BElement *,Rva005E1E9BElement *); }
// Suppress this TU's non-retail copy of ??$__destroy@PAURva005E1E9BElement@@U1@@_STL@@YAXPAURva005E1E9BElement@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005E1E9BElement;
namespace _STL { template <> void __destroy<Rva005E1E9BElement *,Rva005E1E9BElement>(Rva005E1E9BElement *,Rva005E1E9BElement *,Rva005E1E9BElement *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00318203Element@@@_STL@@YAXPAURva00318203Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00318203Element;
namespace _STL { template <> void _Destroy<Rva00318203Element *>(Rva00318203Element *,Rva00318203Element *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva001DAAF2Element@@@_STL@@YAXPAURva001DAAF2Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001DAAF2Element;
namespace _STL { template <> void _Destroy<Rva001DAAF2Element *>(Rva001DAAF2Element *,Rva001DAAF2Element *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00153A27Element@@@_STL@@YAXPAURva00153A27Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00153A27Element;
namespace _STL { template <> void _Destroy<Rva00153A27Element *>(Rva00153A27Element *,Rva00153A27Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005E1E9BElement@@@_STL@@YAXPAURva005E1E9BElement@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005E1E9BElement;
namespace _STL { template <> void __destroy_aux<Rva005E1E9BElement *>(Rva005E1E9BElement *,Rva005E1E9BElement *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__destroy@PAURva005FA1CEElement@@U1@@_STL@@YAXPAURva005FA1CEElement@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA1CEElement;
namespace _STL { template <> void __destroy<Rva005FA1CEElement *,Rva005FA1CEElement>(Rva005FA1CEElement *,Rva005FA1CEElement *,Rva005FA1CEElement *); }
// Suppress this TU's non-retail copy of ??$__destroy@PAURva005FA197Element@@U1@@_STL@@YAXPAURva005FA197Element@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA197Element;
namespace _STL { template <> void __destroy<Rva005FA197Element *,Rva005FA197Element>(Rva005FA197Element *,Rva005FA197Element *,Rva005FA197Element *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva002B72C9@@@_STL@@YAXPAURva002B72C9@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva002B72C9;
namespace _STL { template <> void _Destroy<Rva002B72C9 *>(Rva002B72C9 *,Rva002B72C9 *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva002898ACElement@@@_STL@@YAXPAURva002898ACElement@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva002898ACElement;
namespace _STL { template <> void _Destroy<Rva002898ACElement *>(Rva002898ACElement *,Rva002898ACElement *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva005E2B0EElement@@@_STL@@YAXPAURva005E2B0EElement@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005E2B0EElement;
namespace _STL { template <> void _Destroy<Rva005E2B0EElement *>(Rva005E2B0EElement *,Rva005E2B0EElement *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005E2B0EElement@@@_STL@@YAXPAURva005E2B0EElement@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005E2B0EElement;
namespace _STL { template <> void __destroy_aux<Rva005E2B0EElement *>(Rva005E2B0EElement *,Rva005E2B0EElement *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva005F13E6Element@@@_STL@@YAXPAURva005F13E6Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005F13E6Element;
namespace _STL { template <> void _Destroy<Rva005F13E6Element *>(Rva005F13E6Element *,Rva005F13E6Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005F13E6Element@@@_STL@@YAXPAURva005F13E6Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005F13E6Element;
namespace _STL { template <> void __destroy_aux<Rva005F13E6Element *>(Rva005F13E6Element *,Rva005F13E6Element *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005FA1CEElement@@@_STL@@YAXPAURva005FA1CEElement@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA1CEElement;
namespace _STL { template <> void __destroy_aux<Rva005FA1CEElement *>(Rva005FA1CEElement *,Rva005FA1CEElement *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005FA197Element@@@_STL@@YAXPAURva005FA197Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA197Element;
namespace _STL { template <> void __destroy_aux<Rva005FA197Element *>(Rva005FA197Element *,Rva005FA197Element *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00578425Element@@@_STL@@YAXPAURva00578425Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00578425Element;
namespace _STL { template <> void _Destroy<Rva00578425Element *>(Rva00578425Element *,Rva00578425Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva00578425Element@@@_STL@@YAXPAURva00578425Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00578425Element;
namespace _STL { template <> void __destroy_aux<Rva00578425Element *>(Rva00578425Element *,Rva00578425Element *,__false_type const &); }

class Rva0030E8DF { public: void rva0030E8DF(); };
class SmoothCameraHeightField
{
public:
	void Initialize(const unsigned short *source, int unused,
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
	SmoothCameraHeightField m_heightField;
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
		m_heightField.Initialize(map->getData(), map->getDataSize(), map->getWidth(),
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
