// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::_M_insert_overflow (the push_back growth path) for
// the element types of StlportVectorPushBackFamily.cpp, whose retail push_back
// rows already name these bodies through pins.  Same recipe as
// StlportVectorGrowthFootprints.cpp: each element is reduced to its footprint
// (the stride its push_back adds) with an out-of-line copy ctor and dtor, and
// _Construct is declared as an explicit specialization so the copies call the
// element's matched _Construct row.  /G7 gives retail's imul scaling;
// _STLP_NO_EXCEPTIONS drops the EH frame retail does not have.
//
// Each body is the sole retail caller-side match for its push_back's
// _M_insert_overflow REL32 and is byte-identical with relocations masked.
// _M_clear and helper bodies reached only from one of these growth paths are
// landed from this unit as well; helpers folded across several vectors are
// pinned, not rowed.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// 12-byte element; push_back 0x0004CF63.
class RvaSmartPtr12 { char m_pad[12]; public: RvaSmartPtr12(const RvaSmartPtr12 &); ~RvaSmartPtr12(); };
// 8-byte element; push_back 0x000CF83C.
struct Rva000CF83CElement { char m_pad[8]; public: Rva000CF83CElement(const Rva000CF83CElement &); ~Rva000CF83CElement(); };
// 8-byte element; push_back 0x00153A27.
struct Rva00153A27Element { char m_pad[8]; public: Rva00153A27Element(const Rva00153A27Element &); ~Rva00153A27Element(); };
// 8-byte element; push_back 0x001DAAF2.
struct Rva001DAAF2Element { char m_pad[8]; public: Rva001DAAF2Element(const Rva001DAAF2Element &); ~Rva001DAAF2Element(); };
// 48-byte element; push_back 0x001DF3F1.
struct Rva001DF3F1Element { char m_pad[48]; public: Rva001DF3F1Element(const Rva001DF3F1Element &); ~Rva001DF3F1Element(); };
// 8-byte element; push_back 0x0020A227.
struct Rva0020A227Element { char m_pad[8]; public: Rva0020A227Element(const Rva0020A227Element &); ~Rva0020A227Element(); };
// 32-byte element; push_back 0x002201D5.
class Rva0021F876 { char m_pad[32]; public: Rva0021F876(const Rva0021F876 &); ~Rva0021F876(); };
// 8-byte element; push_back 0x00260B88.
struct Rva00260B88Element { char m_pad[8]; public: Rva00260B88Element(const Rva00260B88Element &); ~Rva00260B88Element(); };
// 8-byte element; push_back 0x00308E2C.
struct Rva00308E2CElement { char m_pad[8]; public: Rva00308E2CElement(const Rva00308E2CElement &); ~Rva00308E2CElement(); };
// 8-byte element; push_back 0x002898AC.
struct Rva002898ACElement { char m_pad[8]; public: Rva002898ACElement(const Rva002898ACElement &); ~Rva002898ACElement(); };
// 4-byte element; push_back 0x002B9062.
struct Rva002B9062Element { char m_pad[4]; public: Rva002B9062Element(const Rva002B9062Element &); ~Rva002B9062Element(); };
// 20-byte element; push_back 0x002BC58D.
struct Rva002B72C9 { char m_pad[20]; public: Rva002B72C9(const Rva002B72C9 &); ~Rva002B72C9(); };
// 8-byte element; push_back 0x00318203.
struct Rva00318203Element { char m_pad[8]; public: Rva00318203Element(const Rva00318203Element &); ~Rva00318203Element(); };
// 8-byte element; push_back 0x0032DC80.
struct Rva0032DC80Element { char m_pad[8]; public: Rva0032DC80Element(const Rva0032DC80Element &); ~Rva0032DC80Element(); };
// 12-byte element; push_back 0x0032EA3F.
struct Rva0032EA3FElement { char m_pad[12]; public: Rva0032EA3FElement(const Rva0032EA3FElement &); ~Rva0032EA3FElement(); };
// 12-byte element; push_back 0x003328B6.
struct Rva003328B6Element { char m_pad[12]; public: Rva003328B6Element(const Rva003328B6Element &); ~Rva003328B6Element(); };
// 12-byte element; push_back 0x0033A23A.
struct Rva0033A23AElement { char m_pad[12]; public: Rva0033A23AElement(const Rva0033A23AElement &); ~Rva0033A23AElement(); };
// 8-byte element; push_back 0x0039A48E.
struct Rva0039A48EElement { char m_pad[8]; public: Rva0039A48EElement(const Rva0039A48EElement &); ~Rva0039A48EElement(); };
// 12-byte element; push_back 0x0039A4C5.
struct BfmeStringRecord00395E75 { char m_pad[12]; public: BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &); ~BfmeStringRecord00395E75(); };
// 24-byte element; push_back 0x003F309A.
class LivingWorldRegionConnection { char m_pad[24]; public: LivingWorldRegionConnection(const LivingWorldRegionConnection &); ~LivingWorldRegionConnection(); };
// 4-byte element; push_back 0x003F7B22.
struct Rva003F7B22Element { char m_pad[4]; public: Rva003F7B22Element(const Rva003F7B22Element &); ~Rva003F7B22Element(); };
// 20-byte element; push_back 0x0040457D.
class Rva00403927 { char m_pad[20]; public: Rva00403927(const Rva00403927 &); ~Rva00403927(); };
// 24-byte element; push_back 0x00413B16.
struct Rva00413B16Element { char m_pad[24]; public: Rva00413B16Element(const Rva00413B16Element &); ~Rva00413B16Element(); };
// 24-byte element; push_back 0x00414258.
struct Rva00414258Element { char m_pad[24]; public: Rva00414258Element(const Rva00414258Element &); ~Rva00414258Element(); };
// 44-byte element; push_back 0x00414BA4.
struct Rva00414BA4Element { char m_pad[44]; public: Rva00414BA4Element(const Rva00414BA4Element &); ~Rva00414BA4Element(); };
// 12-byte element; push_back 0x004688D1.
struct BfmeStringRecord00466E64 { char m_pad[12]; public: BfmeStringRecord00466E64(const BfmeStringRecord00466E64 &); ~BfmeStringRecord00466E64(); };
// 4-byte element; push_back 0x00475F2A.
struct Rva00475F2AElement { char m_pad[4]; public: Rva00475F2AElement(const Rva00475F2AElement &); ~Rva00475F2AElement(); };
// 8-byte element; push_back 0x004C3F09.
struct Rva004C3F09Element { char m_pad[8]; public: Rva004C3F09Element(const Rva004C3F09Element &); ~Rva004C3F09Element(); };
// 4-byte element; push_back 0x004F87BC.
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
// Native27B range destruction4F72ED calls the existing34B reference-slot
// deleting cleanup with flags0 for every4B slot. The tag is unused; its
// cdecl spelling leaves stack cleanup to the caller just as retail does.
struct Rva005F8FCC {void *rva005F8FCC(unsigned);};
namespace _STL {
template<> void __destroy_aux<Rva004F87BCElement *>(Rva004F87BCElement *first,Rva004F87BCElement *last,const __false_type &)
{
 for(;first!=last;++first) reinterpret_cast<Rva005F8FCC *>(first)->rva005F8FCC(0);
}
}
// 4-byte element; push_back 0x004F8D92.
struct Rva004F8D92Element { char m_pad[4]; public: Rva004F8D92Element(const Rva004F8D92Element &); ~Rva004F8D92Element(); };
// 12-byte element; push_back 0x004F9018.
struct Rva004F9018Element { char m_pad[12]; public: Rva004F9018Element(const Rva004F9018Element &); ~Rva004F9018Element(); };
// 20-byte element; push_back 0x00501E3F.
struct Rva00501E3FElement { char m_pad[20]; public: Rva00501E3FElement(const Rva00501E3FElement &); ~Rva00501E3FElement(); };
// 20-byte element; push_back 0x00566303.
class Rva0052BE33 { char m_pad[20]; public: Rva0052BE33(const Rva0052BE33 &); ~Rva0052BE33(); };
// 12-byte element; push_back 0x005668E9.
struct Rva005668E9Element { char m_pad[12]; public: Rva005668E9Element(const Rva005668E9Element &); ~Rva005668E9Element(); };
// 12-byte element; push_back 0x0056A32B.
class Rva00568A20 { char m_pad[12]; public: Rva00568A20(const Rva00568A20 &); ~Rva00568A20(); };
// 4-byte element; push_back 0x00578425.
struct Rva00578425Element { char m_pad[4]; public: Rva00578425Element(const Rva00578425Element &); ~Rva00578425Element(); };
// 4-byte element; push_back 0x005E1E9B.
struct Rva005E1E9BElement { char m_pad[4]; public: Rva005E1E9BElement(const Rva005E1E9BElement &); ~Rva005E1E9BElement(); };
// 4-byte element; push_back 0x005E2B0E.
struct Rva005E2B0EElement { char m_pad[4]; public: Rva005E2B0EElement(const Rva005E2B0EElement &); ~Rva005E2B0EElement(); };
// 36-byte element; push_back 0x005EB44A.
struct GeometryShape { char m_pad[36]; public: GeometryShape(const GeometryShape &); ~GeometryShape(); };
// 4-byte element; push_back 0x005EFD53.
#include "../../../../GameEngine/Source/Common/RegionIconSlotReferenceView.h"
// 4-byte element; push_back 0x005F13E6.
struct Rva005F13E6Element { char m_pad[4]; public: Rva005F13E6Element(const Rva005F13E6Element &); ~Rva005F13E6Element(); };
// 4-byte element; push_back 0x005FA197.
struct Rva005FA197Element { char m_pad[4]; public: Rva005FA197Element(const Rva005FA197Element &); ~Rva005FA197Element(); };
// 4-byte element; push_back 0x005FA1CE.
struct Rva005FA1CEElement { char m_pad[4]; public: Rva005FA1CEElement(const Rva005FA1CEElement &); ~Rva005FA1CEElement(); };

// Element views of push_back rows outside StlportVectorPushBackFamily.cpp
// (and of 0x005E825C, landed there with this body); each push_back is the
// sole caller of its _M_insert_overflow, which names the element type.
// 12-byte element; push_back 0x0033E080.
struct BfmeContainerRecord002CF46E { char m_pad[12]; public: BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &); ~BfmeContainerRecord002CF46E(); };
// 8-byte element; push_back 0x000C3448.
namespace _STL { struct Rva007719C0Element { char m_pad[8]; public: Rva007719C0Element(const Rva007719C0Element &); ~Rva007719C0Element(); }; }
// 104-byte element; push_back 0x003B9369.
struct BfmePod104 { char m_pad[104]; public: BfmePod104(const BfmePod104 &); ~BfmePod104(); };
// 16-byte element; push_back 0x0032D2EA.
class BfmeThingUBB { char m_pad[16]; public: BfmeThingUBB(const BfmeThingUBB &); ~BfmeThingUBB(); };
// 4-byte element; push_back 0x005E825C.
struct Rva005E71C6Ref { char m_pad[4]; public: Rva005E71C6Ref(const Rva005E71C6Ref &); ~Rva005E71C6Ref(); };
// 8-byte element; push_back 0x004F93B0.
struct Rva004F93B0Element { char m_pad[8]; public: Rva004F93B0Element(const Rva004F93B0Element &); ~Rva004F93B0Element(); };
// 156-byte element; push_back 0x004CC337 (stlport_asciistring_record_bodies.cpp).
struct BfmeStringTailRecord156 { char m_pad[156]; public: BfmeStringTailRecord156(const BfmeStringTailRecord156 &); ~BfmeStringTailRecord156(); };
namespace _STL
{
template <> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *, const RvaSmartPtr12 &);
template <> void _Construct<Rva000CF83CElement, Rva000CF83CElement>(Rva000CF83CElement *, const Rva000CF83CElement &);
template <> void _Construct<Rva00153A27Element, Rva00153A27Element>(Rva00153A27Element *, const Rva00153A27Element &);
template <> void _Construct<Rva001DAAF2Element, Rva001DAAF2Element>(Rva001DAAF2Element *, const Rva001DAAF2Element &);
template <> void _Construct<Rva001DF3F1Element, Rva001DF3F1Element>(Rva001DF3F1Element *, const Rva001DF3F1Element &);
template <> void _Construct<Rva0020A227Element, Rva0020A227Element>(Rva0020A227Element *, const Rva0020A227Element &);
template <> void _Construct<Rva0021F876, Rva0021F876>(Rva0021F876 *, const Rva0021F876 &);
template <> void _Construct<Rva00260B88Element, Rva00260B88Element>(Rva00260B88Element *, const Rva00260B88Element &);
template <> void _Construct<Rva00308E2CElement, Rva00308E2CElement>(Rva00308E2CElement *, const Rva00308E2CElement &);
template <> void _Construct<Rva002898ACElement, Rva002898ACElement>(Rva002898ACElement *, const Rva002898ACElement &);
template <> void _Construct<Rva002B9062Element, Rva002B9062Element>(Rva002B9062Element *, const Rva002B9062Element &);
template <> void _Construct<Rva002B72C9, Rva002B72C9>(Rva002B72C9 *, const Rva002B72C9 &);
template <> void _Construct<Rva00318203Element, Rva00318203Element>(Rva00318203Element *, const Rva00318203Element &);
template <> void _Construct<Rva0032DC80Element, Rva0032DC80Element>(Rva0032DC80Element *, const Rva0032DC80Element &);
template <> void _Construct<Rva0032EA3FElement, Rva0032EA3FElement>(Rva0032EA3FElement *, const Rva0032EA3FElement &);
template <> void _Construct<Rva003328B6Element, Rva003328B6Element>(Rva003328B6Element *, const Rva003328B6Element &);
template <> void _Construct<Rva0033A23AElement, Rva0033A23AElement>(Rva0033A23AElement *, const Rva0033A23AElement &);
template <> void _Construct<Rva0039A48EElement, Rva0039A48EElement>(Rva0039A48EElement *, const Rva0039A48EElement &);
template <> void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *, const BfmeStringRecord00395E75 &);
template <> void _Construct<LivingWorldRegionConnection, LivingWorldRegionConnection>(LivingWorldRegionConnection *, const LivingWorldRegionConnection &);
template <> void _Construct<Rva003F7B22Element, Rva003F7B22Element>(Rva003F7B22Element *, const Rva003F7B22Element &);
template <> void _Construct<Rva00403927, Rva00403927>(Rva00403927 *, const Rva00403927 &);
template <> void _Construct<Rva00413B16Element, Rva00413B16Element>(Rva00413B16Element *, const Rva00413B16Element &);
template <> void _Construct<Rva00414258Element, Rva00414258Element>(Rva00414258Element *, const Rva00414258Element &);
template <> void _Construct<Rva00414BA4Element, Rva00414BA4Element>(Rva00414BA4Element *, const Rva00414BA4Element &);
template <> void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *, const BfmeStringRecord00466E64 &);
template <> void _Construct<Rva00475F2AElement, Rva00475F2AElement>(Rva00475F2AElement *, const Rva00475F2AElement &);
template <> void _Construct<Rva004C3F09Element, Rva004C3F09Element>(Rva004C3F09Element *, const Rva004C3F09Element &);
template <> void _Construct<Rva004F87BCElement, Rva004F87BCElement>(Rva004F87BCElement *, const Rva004F87BCElement &);
template <> void _Construct<Rva004F8D92Element, Rva004F8D92Element>(Rva004F8D92Element *, const Rva004F8D92Element &);
template <> void _Construct<Rva004F9018Element, Rva004F9018Element>(Rva004F9018Element *, const Rva004F9018Element &);
template <> void _Construct<Rva00501E3FElement, Rva00501E3FElement>(Rva00501E3FElement *, const Rva00501E3FElement &);
template <> void _Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *, const Rva0052BE33 &);
template <> void _Construct<Rva005668E9Element, Rva005668E9Element>(Rva005668E9Element *, const Rva005668E9Element &);
template <> void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &);
template <> void _Construct<Rva00578425Element, Rva00578425Element>(Rva00578425Element *, const Rva00578425Element &);
template <> void _Construct<Rva005E1E9BElement, Rva005E1E9BElement>(Rva005E1E9BElement *, const Rva005E1E9BElement &);
template <> void _Construct<Rva005E2B0EElement, Rva005E2B0EElement>(Rva005E2B0EElement *, const Rva005E2B0EElement &);
template <> void _Construct<GeometryShape, GeometryShape>(GeometryShape *, const GeometryShape &);
template <> void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *, const Rva005EFD53Element &);
template <> void _Construct<Rva005F13E6Element, Rva005F13E6Element>(Rva005F13E6Element *, const Rva005F13E6Element &);
template <> void _Construct<Rva005FA197Element, Rva005FA197Element>(Rva005FA197Element *, const Rva005FA197Element &);
template <> void _Construct<Rva005FA1CEElement, Rva005FA1CEElement>(Rva005FA1CEElement *, const Rva005FA1CEElement &);
template <> void _Construct<BfmeContainerRecord002CF46E, BfmeContainerRecord002CF46E>(BfmeContainerRecord002CF46E *, const BfmeContainerRecord002CF46E &);
template <> void _Construct<_STL::Rva007719C0Element, _STL::Rva007719C0Element>(_STL::Rva007719C0Element *, const _STL::Rva007719C0Element &);
template <> void _Construct<BfmePod104, BfmePod104>(BfmePod104 *, const BfmePod104 &);
template <> void _Construct<BfmeThingUBB, BfmeThingUBB>(BfmeThingUBB *, const BfmeThingUBB &);
template <> void _Construct<Rva005E71C6Ref, Rva005E71C6Ref>(Rva005E71C6Ref *, const Rva005E71C6Ref &);
template <> void _Construct<Rva004F93B0Element, Rva004F93B0Element>(Rva004F93B0Element *, const Rva004F93B0Element &);
template <> void _Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &);
}

// Retail 0x0004CE90.
template void _STL::vector<RvaSmartPtr12>::_M_insert_overflow(
    RvaSmartPtr12 *, const RvaSmartPtr12 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x000CF76E.
template void _STL::vector<Rva000CF83CElement>::_M_insert_overflow(
    Rva000CF83CElement *, const Rva000CF83CElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x001538C9.
template void _STL::vector<Rva00153A27Element>::_M_insert_overflow(
    Rva00153A27Element *, const Rva00153A27Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x001DA68C.
template void _STL::vector<Rva001DAAF2Element>::_M_insert_overflow(
    Rva001DAAF2Element *, const Rva001DAAF2Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x001DF21C.
template void _STL::vector<Rva001DF3F1Element>::_M_insert_overflow(
    Rva001DF3F1Element *, const Rva001DF3F1Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x002098A0.
template void _STL::vector<Rva0020A227Element>::_M_insert_overflow(
    Rva0020A227Element *, const Rva0020A227Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00220105.
template void _STL::vector<Rva0021F876>::_M_insert_overflow(
    Rva0021F876 *, const Rva0021F876 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00260AD6.
template void _STL::vector<Rva00260B88Element>::_M_insert_overflow(
    Rva00260B88Element *, const Rva00260B88Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00282870.
template void _STL::vector<Rva00308E2CElement>::_M_insert_overflow(
    Rva00308E2CElement *, const Rva00308E2CElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x002895F8.
template void _STL::vector<Rva002898ACElement>::_M_insert_overflow(
    Rva002898ACElement *, const Rva002898ACElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x002B8174.
template void _STL::vector<Rva002B9062Element>::_M_insert_overflow(
    Rva002B9062Element *, const Rva002B9062Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x002BC3C6.
template void _STL::vector<Rva002B72C9>::_M_insert_overflow(
    Rva002B72C9 *, const Rva002B72C9 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0031809E.
template void _STL::vector<Rva00318203Element>::_M_insert_overflow(
    Rva00318203Element *, const Rva00318203Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0032D321.
template void _STL::vector<Rva0032DC80Element>::_M_insert_overflow(
    Rva0032DC80Element *, const Rva0032DC80Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0032E842.
template void _STL::vector<Rva0032EA3FElement>::_M_insert_overflow(
    Rva0032EA3FElement *, const Rva0032EA3FElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0033270E.
template void _STL::vector<Rva003328B6Element>::_M_insert_overflow(
    Rva003328B6Element *, const Rva003328B6Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00339FA7.
template void _STL::vector<Rva0033A23AElement>::_M_insert_overflow(
    Rva0033A23AElement *, const Rva0033A23AElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00399EBE.
template void _STL::vector<Rva0039A48EElement>::_M_insert_overflow(
    Rva0039A48EElement *, const Rva0039A48EElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00399F70.
template void _STL::vector<BfmeStringRecord00395E75>::_M_insert_overflow(
    BfmeStringRecord00395E75 *, const BfmeStringRecord00395E75 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x003F2B0B.
template void _STL::vector<LivingWorldRegionConnection>::_M_insert_overflow(
    LivingWorldRegionConnection *, const LivingWorldRegionConnection &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x003F79A0.
template void _STL::vector<Rva003F7B22Element>::_M_insert_overflow(
    Rva003F7B22Element *, const Rva003F7B22Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00404457.
template void _STL::vector<Rva00403927>::_M_insert_overflow(
    Rva00403927 *, const Rva00403927 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00413A5F.
template void _STL::vector<Rva00413B16Element>::_M_insert_overflow(
    Rva00413B16Element *, const Rva00413B16Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004141A1.
template void _STL::vector<Rva00414258Element>::_M_insert_overflow(
    Rva00414258Element *, const Rva00414258Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004149BF.
template void _STL::vector<Rva00414BA4Element>::_M_insert_overflow(
    Rva00414BA4Element *, const Rva00414BA4Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0046824A.
template void _STL::vector<BfmeStringRecord00466E64>::_M_insert_overflow(
    BfmeStringRecord00466E64 *, const BfmeStringRecord00466E64 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00475BE8.
template void _STL::vector<Rva00475F2AElement>::_M_insert_overflow(
    Rva00475F2AElement *, const Rva00475F2AElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004C3DF4.
template void _STL::vector<Rva004C3F09Element>::_M_insert_overflow(
    Rva004C3F09Element *, const Rva004C3F09Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004F823B.
template void _STL::vector<Rva004F87BCElement>::_M_insert_overflow(
    Rva004F87BCElement *, const Rva004F87BCElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004F88F6.
template void _STL::vector<Rva004F8D92Element>::_M_insert_overflow(
    Rva004F8D92Element *, const Rva004F8D92Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004F8A35.
template void _STL::vector<Rva004F9018Element>::_M_insert_overflow(
    Rva004F9018Element *, const Rva004F9018Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00501A7C.
template void _STL::vector<Rva00501E3FElement>::_M_insert_overflow(
    Rva00501E3FElement *, const Rva00501E3FElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00565CEB.
template void _STL::vector<Rva0052BE33>::_M_insert_overflow(
    Rva0052BE33 *, const Rva0052BE33 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005665AC.
template void _STL::vector<Rva005668E9Element>::_M_insert_overflow(
    Rva005668E9Element *, const Rva005668E9Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0056A1E4.
template void _STL::vector<Rva00568A20>::_M_insert_overflow(
    Rva00568A20 *, const Rva00568A20 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0057833B.
template void _STL::vector<Rva00578425Element>::_M_insert_overflow(
    Rva00578425Element *, const Rva00578425Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005E1D5D.
template void _STL::vector<Rva005E1E9BElement>::_M_insert_overflow(
    Rva005E1E9BElement *, const Rva005E1E9BElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005E2A40.
template void _STL::vector<Rva005E2B0EElement>::_M_insert_overflow(
    Rva005E2B0EElement *, const Rva005E2B0EElement &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005EB379.
template void _STL::vector<GeometryShape>::_M_insert_overflow(
    GeometryShape *, const GeometryShape &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005EFB7E.
template void _STL::vector<Rva005EFD53Element>::_M_insert_overflow(
    Rva005EFD53Element *, const Rva005EFD53Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005F131A.
template void _STL::vector<Rva005F13E6Element>::_M_insert_overflow(
    Rva005F13E6Element *, const Rva005F13E6Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005F9C05.
template void _STL::vector<Rva005FA197Element>::_M_insert_overflow(
    Rva005FA197Element *, const Rva005FA197Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005F9CB7.
template void _STL::vector<Rva005FA1CEElement>::_M_insert_overflow(
    Rva005FA1CEElement *, const Rva005FA1CEElement &, const _STL::__false_type &, unsigned int, bool);

// Retail 0x0033DCEA.
template void _STL::vector<BfmeContainerRecord002CF46E>::_M_insert_overflow(
    BfmeContainerRecord002CF46E *, const BfmeContainerRecord002CF46E &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x000C1E4A.
template void _STL::vector<_STL::Rva007719C0Element>::_M_insert_overflow(
    _STL::Rva007719C0Element *, const _STL::Rva007719C0Element &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x003B9184.
template void _STL::vector<BfmePod104>::_M_insert_overflow(
    BfmePod104 *, const BfmePod104 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0032CAA1.
template void _STL::vector<BfmeThingUBB>::_M_insert_overflow(
    BfmeThingUBB *, const BfmeThingUBB &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005E818E.
template void _STL::vector<Rva005E71C6Ref>::_M_insert_overflow(
    Rva005E71C6Ref *, const Rva005E71C6Ref &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004F8DFD.
template void _STL::vector<Rva004F93B0Element>::_M_insert_overflow(
    Rva004F93B0Element *, const Rva004F93B0Element &, const _STL::__false_type &, unsigned int, bool);

// Retail 0x004CC25C (push_back 0x004CC337 is its caller).
template void _STL::vector<BfmeStringTailRecord156>::_M_insert_overflow(
    BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &, const _STL::__false_type &, unsigned int, bool);

// Also landed from the instances above (sole growth-path callers):
//   0x0004CDAF 30B ?_M_clear@?$vector@VRvaSmartPtr12@@V?$allocator@VRvaSmartPtr12@@@_STL@@@_STL@@IAEXXZ
//   0x0021FE2B 30B ?_M_clear@?$vector@VRva0021F876@@V?$allocator@VRva0021F876@@@_STL@@@_STL@@IAEXXZ
//   0x004043E1 30B ?_M_clear@?$vector@VRva00403927@@V?$allocator@VRva00403927@@@_STL@@@_STL@@IAEXXZ
//   0x00413A06 30B ?_M_clear@?$vector@URva00413B16Element@@V?$allocator@URva00413B16Element@@@_STL@@@_STL@@IAEXXZ
//   0x004F7E78 25B ??$_Destroy@PAURva004F9018Element@@@_STL@@YAXPAURva004F9018Element@@0@Z
//   0x004F82ED 30B ?_M_clear@?$vector@URva004F9018Element@@V?$allocator@URva004F9018Element@@@_STL@@@_STL@@IAEXXZ
//   0x005EB2C9 30B ?_M_clear@?$vector@UGeometryShape@@V?$allocator@UGeometryShape@@@_STL@@@_STL@@IAEXXZ
//   0x004CC0A7 47B ??$__uninitialized_copy@PAUBfmeStringTailRecord156@@PAU1@@_STL@@YAPAUBfmeStringTailRecord156@@PAU1@00ABU__false_type@0@@Z
//   0x004CC0D6 40B ??$__uninitialized_fill_n@PAUBfmeStringTailRecord156@@IU1@@_STL@@YAPAUBfmeStringTailRecord156@@PAU1@IABU1@ABU__false_type@0@@Z
