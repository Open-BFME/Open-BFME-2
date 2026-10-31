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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
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
struct Rva004F6966;
class Rva004C5DD0;
struct Rva004C5DD0Pair;
void __cdecl Rva004F6A52Assign(Rva004C5DD0 *, const Rva004C5DD0Pair *);
void __cdecl Rva000BBA47Construct(TreeKey00242F5E *, const TreeKey00242F5E &);

// Placement-copy owners share the target two-pointer cdecl ABI.
void __cdecl Rva001D9B0FConstruct(void *, const void *);
void __cdecl Rva0020596AConstruct(void *, const void *);
void __cdecl Rva00317CA0Construct(void *, const void *);
void __cdecl Rva0032ACFCConstruct(void *, const void *);
void __cdecl Rva004C3A9FConstruct(void *, const void *);


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
class CreateAHeroManager { public: class CreateAHeroClass; };
typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;

class CreateAHeroManager::CreateAHeroClass { char m_pad[32]; public: CreateAHeroClass(const CreateAHeroClass &); ~CreateAHeroClass(); };
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
class BfmeNarrowRecord00427F75 { public: ~BfmeNarrowRecord00427F75(); };
struct Rva00413B16Element {
    char m_pad[24];
    Rva00413B16Element(const Rva00413B16Element &);
    __declspec(dllimport) __forceinline ~Rva00413B16Element()
    { ((BfmeNarrowRecord00427F75 *)this)->BfmeNarrowRecord00427F75::~BfmeNarrowRecord00427F75(); }
};
// 24-byte element; push_back 0x00414258.
struct Rva00414258Element { char m_pad[24]; public: Rva00414258Element(const Rva00414258Element &); ~Rva00414258Element(); };
// 44-byte element; push_back 0x00414BA4.
struct Rva00414BA4Element { char m_pad[44]; public: Rva00414BA4Element(const Rva00414BA4Element &); ~Rva00414BA4Element(); };
// 12-byte element; push_back 0x004688D1.
struct BfmeStringRecord00466E64 { char m_pad[12]; public: BfmeStringRecord00466E64(const BfmeStringRecord00466E64 &); ~BfmeStringRecord00466E64(); };
// 4-byte element; push_back 0x00475F2A.
struct Rva00475F2AElement { char m_pad[4]; public: Rva00475F2AElement(const Rva00475F2AElement &); ~Rva00475F2AElement(); };
// bfme link decl-only Rva00475F2AElement
namespace _STL { template <> void vector<Rva00475F2AElement, allocator<Rva00475F2AElement> >::_M_clear(); }
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
template<> __declspec(noinline) inline void __destroy_aux<Rva004F87BCElement *>(Rva004F87BCElement *first,Rva004F87BCElement *last,const __false_type &)
{
 for(;first!=last;++first) reinterpret_cast<Rva005F8FCC *>(first)->rva005F8FCC(0);
}
}
// 4-byte element; push_back 0x004F8D92.
struct Rva004F8D92Element { char m_pad[4]; public: Rva004F8D92Element(const Rva004F8D92Element &); ~Rva004F8D92Element(); };
// 12-byte element; push_back 0x004F9018.
struct Rva005F8F96 { ~Rva005F8F96(); };
struct Rva004F9018Element { char m_pad[12]; public: Rva004F9018Element(const Rva004F9018Element &); // Destruction is the rowed ??1Rva005F8F96, reached by a qualified call.
__declspec(dllimport) __forceinline ~Rva004F9018Element() { ((Rva005F8F96 *)this)->Rva005F8F96::~Rva005F8F96(); } };
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
// Owning handle like Rva004F87BCElement: retail has no out-of-line element
// dtor (its release is inlined into the scalar deleting dtor 0x005F8FCC).
struct Rva005E1E9BElement {
 TargetRef00217D4C *m_ptr;
 Rva005E1E9BElement(const Rva005E1E9BElement &);
 ~Rva005E1E9BElement() {if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);}
};
// 4-byte element; push_back 0x005E2B0E.
struct Rva005E2B0EElement { char m_pad[4]; public: Rva005E2B0EElement(const Rva005E2B0EElement &); ~Rva005E2B0EElement(); };
// 36-byte element; push_back 0x005EB44A.
struct GeometryShape { char m_pad[36]; public: GeometryShape(const GeometryShape &); ~GeometryShape(); };
// 4-byte element; push_back 0x005EFD53.
#include "../../../../GameEngine/Source/Common/RegionIconSlotReferenceView.h"
// Retail's range destroy 0x005EAA83 for this 36-byte vector calls the
// null-checked release dtor 0x005EA85F, not GeometryShape's 0x00255D17.
struct BfmeVectorRecord002AF478 { ~BfmeVectorRecord002AF478(); };
namespace _STL {
template <> __declspec(noinline) inline void _Destroy<GeometryShape *>(GeometryShape *first, GeometryShape *last)
{
	for (; first != last; ++first)
		((BfmeVectorRecord002AF478 *)first)->~BfmeVectorRecord002AF478();
}
}
// bfme link decl-only begin
namespace _STL { template <> void _Construct<GeometryShape, GeometryShape>(GeometryShape *, GeometryShape const &); }
namespace _STL { template <> void _Destroy<RvaSmartPtr12 *>(RvaSmartPtr12 *, RvaSmartPtr12 *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$_Destroy@PAUBfmePod104@@@_STL@@YAXPAUBfmePod104@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void _Destroy<BfmePod104 *>(BfmePod104 *,BfmePod104 *); }
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
// vector<ArmySummary>: its overflow 0x003B9184 is reached from the push_back
// 0x003B9369 (rowed over BfmePod104 in stlport_pod_vector_bodies.cpp) and from
// vector<ArmySummary>::_M_fill_insert 0x003F53DA (StlSweepW4Rva003F53DA.cpp).
// Its helpers are rowed over the BfmePod104 / BfmeAssignRecord104 spellings,
// so the forwarders below bind them by those names.
class ArmySummary { public: ArmySummary(const ArmySummary &); virtual ~ArmySummary(); private: char m_fields[0x64]; };
// 16-byte element; push_back 0x0032D2EA.
class BfmeThingUBB { char m_pad[16]; public: BfmeThingUBB(const BfmeThingUBB &); ~BfmeThingUBB(); };
// 4-byte element; push_back 0x005E825C.
struct Rva005E71C6Ref { char m_pad[4]; public: Rva005E71C6Ref(const Rva005E71C6Ref &); ~Rva005E71C6Ref(); };
// BuildQueueIconSelect supplies the native counted-reference range dispatcher.
namespace _STL {
template <> void _Destroy<Rva005E71C6Ref *>(Rva005E71C6Ref *, Rva005E71C6Ref *);
}

// 8-byte element; push_back 0x004F93B0.
struct Rva004F93B0Element { char m_pad[8]; public: Rva004F93B0Element(const Rva004F93B0Element &); ~Rva004F93B0Element(); };
// 156-byte element; push_back 0x004CC337 (stlport_asciistring_record_bodies.cpp).
struct BfmeStringTailRecord156 { char m_pad[156]; public: BfmeStringTailRecord156(const BfmeStringTailRecord156 &); ~BfmeStringTailRecord156(); };
// Placement-copy owners of the elements below: each push_back growth path
// reaches the retail row through the inline forwarder.
class Rva003AD160;
struct BfmeStringRecord005DDD40 { char m_pad[8]; };
struct BfmeE8;
enum ScienceType { SCIENCE_INVALID = -1 };
class Rva004F6093Holder;
class Object;
class Rva00193660;
struct Rva00193660Src;
void __cdecl Rva0032ACEASet(Rva00193660 *, const Rva00193660Src *);
void __cdecl Rva0026061AConstruct(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
void __cdecl Rva002B2FE2Copy(Rva004F6093Holder *, const Rva004F6093Holder &);
namespace _STL
{
template <class _Tp, class _Alloc> class list;
template <> void _Construct<Rva003AD160, Rva003AD160>(Rva003AD160 *, const Rva003AD160 &);
template <> void _Construct<vector<BfmeE8>, vector<BfmeE8> >(vector<BfmeE8> *, const vector<BfmeE8> &);
template <> void _Construct<vector<ScienceType>, vector<ScienceType> >(vector<ScienceType> *, const vector<ScienceType> &);
template <> void _Construct<list<Object *, allocator<Object *> >, list<Object *, allocator<Object *> > >(list<Object *, allocator<Object *> > *, const list<Object *, allocator<Object *> > &);
}
namespace _STL
{
template <> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *, const RvaSmartPtr12 &);
template <> void _Construct<Rva000CF83CElement, Rva000CF83CElement>(Rva000CF83CElement *, const Rva000CF83CElement &);
template <> void _Construct<Rva00153A27Element, Rva00153A27Element>(Rva00153A27Element *, const Rva00153A27Element &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva001DAAF2Element, Rva001DAAF2Element>(Rva001DAAF2Element *__p, const Rva001DAAF2Element &__val)
{ Rva001D9B0FConstruct(__p, &__val); }
template <> void _Construct<Rva001DF3F1Element, Rva001DF3F1Element>(Rva001DF3F1Element *, const Rva001DF3F1Element &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva0020A227Element, Rva0020A227Element>(Rva0020A227Element *__p, const Rva0020A227Element &__val)
{ Rva0020596AConstruct(__p, &__val); }
template <> void _Construct<CreateAHeroClass, CreateAHeroClass>(CreateAHeroClass *, const CreateAHeroClass &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva00260B88Element, Rva00260B88Element>(Rva00260B88Element *__p, const Rva00260B88Element &__val)
{ Rva0026061AConstruct(reinterpret_cast<BfmeStringRecord005DDD40 *>(__p), *reinterpret_cast<const BfmeStringRecord005DDD40 *>(&__val)); }
template <> __declspec(dllimport) __forceinline void _Construct<Rva00308E2CElement, Rva00308E2CElement>(Rva00308E2CElement *__p, const Rva00308E2CElement &__val)
{ Rva0030CA53Set(reinterpret_cast<Rva004733E0 *>(__p), reinterpret_cast<const Rva004733E0 *>(&__val)); }
template <> __declspec(dllimport) __forceinline void _Construct<Rva002898ACElement, Rva002898ACElement>(Rva002898ACElement *__p, const Rva002898ACElement &__val)
{ Rva002889E4Construct(reinterpret_cast<TreeKey00242F5E *>(__p), *reinterpret_cast<const TreeKey00242F5E *>(&__val)); }
template <> void _Construct<Rva002B9062Element, Rva002B9062Element>(Rva002B9062Element *, const Rva002B9062Element &);
template <> void _Construct<Rva002B72C9, Rva002B72C9>(Rva002B72C9 *, const Rva002B72C9 &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva00318203Element, Rva00318203Element>(Rva00318203Element *__p, const Rva00318203Element &__val)
{ Rva00317CA0Construct(__p, &__val); }
template <> __declspec(dllimport) __forceinline void _Construct<Rva0032DC80Element, Rva0032DC80Element>(Rva0032DC80Element *__p, const Rva0032DC80Element &__val)
{ Rva0032ACFCConstruct(__p, &__val); }
template <> __declspec(dllimport) __forceinline void _Construct<Rva0032EA3FElement, Rva0032EA3FElement>(Rva0032EA3FElement *__p, const Rva0032EA3FElement &__val)
{ _Construct(reinterpret_cast<vector<BfmeE8> *>(__p), *reinterpret_cast<const vector<BfmeE8> *>(&__val)); }
template <> void _Construct<Rva003328B6Element, Rva003328B6Element>(Rva003328B6Element *, const Rva003328B6Element &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva0033A23AElement, Rva0033A23AElement>(Rva0033A23AElement *__p, const Rva0033A23AElement &__val)
{ _Construct(reinterpret_cast<vector<ScienceType> *>(__p), *reinterpret_cast<const vector<ScienceType> *>(&__val)); }
template <> void _Construct<Rva0039A48EElement, Rva0039A48EElement>(Rva0039A48EElement *, const Rva0039A48EElement &);
template <> void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *, const BfmeStringRecord00395E75 &);
template <> void _Construct<LivingWorldRegionConnection, LivingWorldRegionConnection>(LivingWorldRegionConnection *, const LivingWorldRegionConnection &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva003F7B22Element, Rva003F7B22Element>(Rva003F7B22Element *__p, const Rva003F7B22Element &__val)
{ Rva002B2FE2Copy(reinterpret_cast<Rva004F6093Holder *>(__p), *reinterpret_cast<const Rva004F6093Holder *>(&__val)); }
template <> void _Construct<Rva00403927, Rva00403927>(Rva00403927 *, const Rva00403927 &);
template <> void _Construct<Rva00413B16Element, Rva00413B16Element>(Rva00413B16Element *, const Rva00413B16Element &);
template <> void _Construct<Rva00414258Element, Rva00414258Element>(Rva00414258Element *, const Rva00414258Element &);
template <> void _Construct<Rva00414BA4Element, Rva00414BA4Element>(Rva00414BA4Element *, const Rva00414BA4Element &);
template <> void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *, const BfmeStringRecord00466E64 &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva00475F2AElement, Rva00475F2AElement>(Rva00475F2AElement *__p, const Rva00475F2AElement &__val)
{ _Construct(reinterpret_cast<list<Object *, allocator<Object *> > *>(__p), *reinterpret_cast<const list<Object *, allocator<Object *> > *>(&__val)); }
template <> __declspec(dllimport) __forceinline void _Construct<Rva004C3F09Element, Rva004C3F09Element>(Rva004C3F09Element *__p, const Rva004C3F09Element &__val)
{ Rva004C3A9FConstruct(__p, &__val); }
template <> void _Construct<Rva004F87BCElement, Rva004F87BCElement>(Rva004F87BCElement *, const Rva004F87BCElement &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva004F8D92Element, Rva004F8D92Element>(Rva004F8D92Element *__p, const Rva004F8D92Element &__val)
{ _Construct(reinterpret_cast<Rva004F87BCElement *>(__p), *reinterpret_cast<const Rva004F87BCElement *>(&__val)); }
template <> void _Construct<Rva004F6966, Rva004F6966>(Rva004F6966 *, const Rva004F6966 &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva004F9018Element, Rva004F9018Element>(Rva004F9018Element *__p, const Rva004F9018Element &__val)
{ _Construct(reinterpret_cast<Rva004F6966 *>(__p), *reinterpret_cast<const Rva004F6966 *>(&__val)); }
template <> void _Construct<Rva00501E3FElement, Rva00501E3FElement>(Rva00501E3FElement *, const Rva00501E3FElement &);
template <> void _Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *, const Rva0052BE33 &);
template <> void _Construct<Rva005668E9Element, Rva005668E9Element>(Rva005668E9Element *, const Rva005668E9Element &);
template <> void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva00578425Element, Rva00578425Element>(Rva00578425Element *__p, const Rva00578425Element &__val)
{ _Construct(reinterpret_cast<Rva004F87BCElement *>(__p), *reinterpret_cast<const Rva004F87BCElement *>(&__val)); }
template <> void _Construct<Rva005E1E9BElement, Rva005E1E9BElement>(Rva005E1E9BElement *, const Rva005E1E9BElement &);
template <> void _Construct<Rva005E2B0EElement, Rva005E2B0EElement>(Rva005E2B0EElement *, const Rva005E2B0EElement &);
template <> void _Construct<GeometryShape, GeometryShape>(GeometryShape *, const GeometryShape &);
template <> void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *, const Rva005EFD53Element &);
template <> void _Construct<Rva005F13E6Element, Rva005F13E6Element>(Rva005F13E6Element *, const Rva005F13E6Element &);
template <> void _Construct<Rva005FA197Element, Rva005FA197Element>(Rva005FA197Element *, const Rva005FA197Element &);
template <> void _Construct<Rva005FA1CEElement, Rva005FA1CEElement>(Rva005FA1CEElement *, const Rva005FA1CEElement &);
template <> void _Construct<BfmeContainerRecord002CF46E, BfmeContainerRecord002CF46E>(BfmeContainerRecord002CF46E *, const BfmeContainerRecord002CF46E &);
template <> __declspec(dllimport) __forceinline void _Construct<_STL::Rva007719C0Element, _STL::Rva007719C0Element>(_STL::Rva007719C0Element *__p, const _STL::Rva007719C0Element &__val)
{ Rva000BBA47Construct(reinterpret_cast<TreeKey00242F5E *>(__p), *reinterpret_cast<const TreeKey00242F5E *>(&__val)); }
template <> void _Construct<BfmePod104, BfmePod104>(BfmePod104 *, const BfmePod104 &);
// Retail calls the rowed allocator<BfmePod104>::allocate 0x0040A673
// (stlport_pod_vector_bodies.cpp) out of line.
template <> BfmePod104 *allocator<BfmePod104>::allocate(size_t, const void *) const;
template <> __declspec(dllimport) __forceinline ArmySummary *allocator<ArmySummary>::allocate(size_t __n, const void *__hint) const
{ return reinterpret_cast<ArmySummary *>(reinterpret_cast<const allocator<BfmePod104> *>(this)->allocate(__n, __hint)); }
template <> __declspec(dllimport) __forceinline void _Construct<ArmySummary, ArmySummary>(ArmySummary *__p, const ArmySummary &__val)
{ _Construct(reinterpret_cast<BfmePod104 *>(__p), *reinterpret_cast<const BfmePod104 *>(&__val)); }
template <> __declspec(dllimport) __forceinline void _Construct<BfmeThingUBB, BfmeThingUBB>(BfmeThingUBB *__p, const BfmeThingUBB &__val)
{ Rva0032ACEASet(reinterpret_cast<Rva00193660 *>(__p), reinterpret_cast<const Rva00193660Src *>(&__val)); }
template <> void _Construct<Rva005E71C6Ref, Rva005E71C6Ref>(Rva005E71C6Ref *, const Rva005E71C6Ref &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva004F93B0Element, Rva004F93B0Element>(Rva004F93B0Element *__p, const Rva004F93B0Element &__val)
{ Rva004F6A52Assign(reinterpret_cast<Rva004C5DD0 *>(__p), reinterpret_cast<const Rva004C5DD0Pair *>(&__val)); }
template <> __declspec(dllimport) __forceinline void _Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(BfmeStringTailRecord156 *__p, const BfmeStringTailRecord156 &__val)
{ _Construct(reinterpret_cast<Rva003AD160 *>(__p), *reinterpret_cast<const Rva003AD160 *>(&__val)); }
}

// _M_clear of these vectors is retail's shared clear worker of another vector
// (ICF): the growth path calls that row through an inline forwarder, so this
// unit emits no unrowed _M_clear copy (and no element destructor reference).
struct Rva0046800B { void rva0046800B(); };
struct ConnectionVec { void Rva00565A24_ScrapStorage(); };
class Rva001DEF6B { public: ~Rva001DEF6B(); };
class Rva00308C13 { public: ~Rva00308C13(); };
class Rva00399800 { public: ~Rva00399800(); };
class Rva0026E5B9 { public: ~Rva0026E5B9(); };
struct Rva005F120F { void rva005F120F(); };
struct Rva0032E7E2 { void rva0032E7E2(); };
struct Rva00414148 { void rva00414148(); };
struct Rva004F89DB { void rva004F89DB(); };
struct Rva00565A42 { void rva00565A42(); };
struct Rva0056614DVec { void rva0056614D(); };
struct Rva002B61DD { void rva002B61DD(); };
struct BfmeStringRecord00426A5B { char m_pad[8]; };
struct BfmeAssignRecord44 { char m_pad[44]; };
struct BfmeAssignRecord104;
class CameraMarker;
struct Rva002BB6BE20Rec;
class Rva00214ADC;
namespace _STL {
template <> void _Destroy<Rva00214ADC *>(Rva00214ADC *, Rva00214ADC *);
template <> __declspec(dllimport) __forceinline void _Destroy<Rva00403927 *>(Rva00403927 *first, Rva00403927 *last)
{ _Destroy(reinterpret_cast<Rva00214ADC *>(first), reinterpret_cast<Rva00214ADC *>(last)); }
}
// The complete clear worker of Rva002B9062Element is owned by StlportVectorClearRva00577EF1.cpp.
template <> void _STL::vector<Rva002B9062Element>::_M_clear();
// Likewise owned by stlport_vector_stringrecord_5ddd40_allocate_copy.cpp,
// stlport_vector_stringrecord_426a5b_allocate_copy.cpp and stlport_asciistring_record_bodies.cpp.
template <> void _STL::vector<BfmeStringRecord005DDD40>::_M_clear();
template <> void _STL::vector<BfmeStringRecord00426A5B>::_M_clear();
template <> void _STL::vector<BfmeAssignRecord44>::_M_clear();
template <> void _STL::vector<BfmeAssignRecord104>::_M_clear();
template <> void _STL::vector<Rva005F8F96>::_M_clear();
template <> void _STL::vector<CameraMarker>::_M_clear();
template <> void _STL::vector<Rva002BB6BE20Rec>::_M_clear();
template <class _Tp> struct ClearOwner : _STL::vector<_Tp> { public: using _STL::vector<_Tp>::_M_clear; };
namespace _STL
{
#define BFME_CLEAR_FORWARD(T, CALL) \
    template <> __declspec(dllimport) __forceinline void vector<T, allocator<T> >::_M_clear() { CALL; }
BFME_CLEAR_FORWARD(BfmeStringRecord00466E64, ((Rva0046800B *)this)->rva0046800B())
BFME_CLEAR_FORWARD(LivingWorldRegionConnection, ((ConnectionVec *)this)->Rva00565A24_ScrapStorage())
BFME_CLEAR_FORWARD(Rva001DF3F1Element, ((Rva001DEF6B *)this)->Rva001DEF6B::~Rva001DEF6B())
BFME_CLEAR_FORWARD(Rva00153A27Element, ((ClearOwner<Rva005F8F96> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva001DAAF2Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva002898ACElement, ((ClearOwner<CameraMarker> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva002B72C9, ((ClearOwner<Rva002BB6BE20Rec> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva00318203Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva003328B6Element, ((Rva0026E5B9 *)this)->Rva0026E5B9::~Rva0026E5B9())
BFME_CLEAR_FORWARD(Rva0039A48EElement, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva004C3F09Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva00578425Element, ((ClearOwner<Rva002B9062Element> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva005E1E9BElement, ((ClearOwner<Rva002B9062Element> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva005E2B0EElement, ((ClearOwner<Rva002B9062Element> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva005F13E6Element, ((Rva005F120F *)this)->rva005F120F())
BFME_CLEAR_FORWARD(Rva007719C0Element, ((ClearOwner<CameraMarker> *)this)->_M_clear())
BFME_CLEAR_FORWARD(BfmePod104, ((ClearOwner<BfmeAssignRecord104> *)this)->_M_clear())
BFME_CLEAR_FORWARD(ArmySummary, ((ClearOwner<BfmeAssignRecord104> *)this)->_M_clear())
BFME_CLEAR_FORWARD(BfmeStringRecord00395E75, ((Rva00399800 *)this)->Rva00399800::~Rva00399800())
BFME_CLEAR_FORWARD(Rva00260B88Element, ((ClearOwner<BfmeStringRecord005DDD40> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva00308E2CElement, ((Rva00308C13 *)this)->Rva00308C13::~Rva00308C13())
BFME_CLEAR_FORWARD(Rva0032DC80Element, ((ClearOwner<BfmeStringRecord00426A5B> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva0032EA3FElement, ((Rva0032E7E2 *)this)->rva0032E7E2())
BFME_CLEAR_FORWARD(Rva0033A23AElement, ((Rva0032E7E2 *)this)->rva0032E7E2())
BFME_CLEAR_FORWARD(Rva003F7B22Element, ((Rva002B61DD *)this)->rva002B61DD())
BFME_CLEAR_FORWARD(Rva00414258Element, ((Rva00414148 *)this)->rva00414148())
BFME_CLEAR_FORWARD(Rva00414BA4Element, ((ClearOwner<BfmeAssignRecord44> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva004F8D92Element, ((ClearOwner<Rva002B9062Element> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva005FA197Element, ((ClearOwner<Rva002B9062Element> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva005FA1CEElement, ((ClearOwner<Rva002B9062Element> *)this)->_M_clear())
BFME_CLEAR_FORWARD(Rva004F93B0Element, ((Rva004F89DB *)this)->rva004F89DB())
BFME_CLEAR_FORWARD(Rva0052BE33, ((Rva00565A42 *)this)->rva00565A42())
BFME_CLEAR_FORWARD(Rva005668E9Element, ((Rva0056614DVec *)this)->rva0056614D())
#undef BFME_CLEAR_FORWARD
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
template void _STL::vector<CreateAHeroClass>::_M_insert_overflow(
    CreateAHeroClass *, const CreateAHeroClass &, const _STL::__false_type &, unsigned int, bool);
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
// Retail 0x004F81FC 63B: out-of-line destructor of the same vector (destroy the
// 12-byte element range through rowed _Destroy 0x004F7E78, then the allocator's
// _free through rowed 0x00030830).
template _STL::vector<Rva004F9018Element>::~vector();
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
template void _STL::vector<ArmySummary>::_M_insert_overflow(
    ArmySummary *, const ArmySummary &, const _STL::__false_type &, unsigned int, bool);
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

template void _STL::vector<BfmePod104>::_M_insert_overflow(
    BfmePod104 *, const BfmePod104 &, const _STL::__false_type &, unsigned int, bool);
