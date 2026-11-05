// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector<T>::~vector for element types whose _Destroy range
// helper is already rowed. Every member is the same-shape sibling of the
// AsciiString instantiation at 0x2CC70 (StlportAsciiStringVectorDtor.cpp):
// only the _Destroy callee differs, so each element type needs just a
// non-trivial destructor here to select that callee by name. Sizes and
// members are irrelevant to these bodies and are not modelled.
#include <vector>

// ??1?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@QAE@XZ @0x49e274
// (_Destroy at 0x32c0ca, pinned twin of the rowed 8-byte-pair destroy).
// QuantityModifier is ProductionUpdateModuleData's +0x1C modifier element: an
// 8-byte AsciiString-plus-int pair (full layout in the ctor TU
// ProductionUpdateModuleDataCtor.cpp, INI table 0x00C517F0). It keeps that
// real layout (implicit dtor) here so the _Destroy range COMDAT this unit
// emits is the same body the insert-overflow, parse and ctor units emit.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct QuantityModifier
{
	AsciiString m_templateName;
	int m_quantity;
};
template _STL::vector<QuantityModifier>::~vector();

// ??1?$vector@UBfmeVectorRecord000BDF17@@V?$allocator@UBfmeVectorRecord000BDF17@@@_STL@@@_STL@@QAE@XZ @0xc6878 (_Destroy at 0xc37cd)
struct BfmeVectorRecord000BDF17 { public: ~BfmeVectorRecord000BDF17(); };
template _STL::vector<BfmeVectorRecord000BDF17>::~vector();

// ??1?$vector@UBfmeObject476@@V?$allocator@UBfmeObject476@@@_STL@@@_STL@@QAE@XZ @0x1fd882 (_Destroy at 0x1fd6a4)
struct BfmeObject476 { public: ~BfmeObject476(); };
namespace _STL {template<> void _Destroy<BfmeObject476*>(BfmeObject476*,BfmeObject476*);}

template _STL::vector<BfmeObject476>::~vector();

// ??1?$vector@UBfmeObject544@@V?$allocator@UBfmeObject544@@@_STL@@@_STL@@QAE@XZ @0x4cae89 (_Destroy at 0x4cae71)
struct BfmeObject544 { public: ~BfmeObject544(); unsigned char m_opaque[544]; };
template _STL::vector<BfmeObject544>::~vector();

// ??1?$vector@URvaPair004C3D4C@@V?$allocator@URvaPair004C3D4C@@@_STL@@@_STL@@QAE@XZ @0x4c3d4c (_Destroy at 0x32c0ca, stride-identical fold with rowed Rva0032C0CADestroyPairs).
// ElvenWoodSpecialPowerModuleData's +0x7C member: retail destroys the range through the rowed 8-byte AsciiString-keyed DestroyPairs at 0x32C0CA then frees storage via 0x30830 (EH states 0/-1); called by the ElvenWood dtor at 0x004C3EEC plus its Unwind funclet. The 8-byte stride plus key dtor are all this body observes; true element name unproven so the honest RvaPair address name stands in for the 8-byte AsciiString-plus-int layout the retail destroy proves.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<BfmeVectorRecord000BDF17 *>(BfmeVectorRecord000BDF17 *, BfmeVectorRecord000BDF17 *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$_Destroy@PAVRva0021F876@@@_STL@@YAXPAVRva0021F876@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
#include "../../../../GameEngine/Include/GameLogic/CreateAHeroManager.h"
// Only the element's non-trivial destructor matters to these bodies.
class CreateAHeroManager::CreateAHeroSubClass { public: ~CreateAHeroSubClass(); };
typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;

namespace _STL { template <> void _Destroy<CreateAHeroClass *>(CreateAHeroClass *,CreateAHeroClass *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAUBfmeStringHeadRecord184@@@_STL@@YAXPAUBfmeStringHeadRecord184@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringHeadRecord184;
namespace _STL { template <> void _Destroy<BfmeStringHeadRecord184 *>(BfmeStringHeadRecord184 *,BfmeStringHeadRecord184 *); }
struct RvaPair004C3D4C { AsciiString m_key; int m_value; public: ~RvaPair004C3D4C(); };
template _STL::vector<RvaPair004C3D4C>::~vector();

// ??1?$vector@UBfmeStringHeadRecord160@@V?$allocator@UBfmeStringHeadRecord160@@@_STL@@@_STL@@QAE@XZ @0x00257583 63B.
// Neighbor vector dtor in same 00257 page: retail destroys the range through pinned _Destroy at 0x00257469 (24B wrapper delegating to matched 0x00256FEA loop stepping 0xA0 via releaseBuffer 0x48BA39) then frees via 0x30830; called at 0x00257CA0 in UNCLAIMED 0x00257C88. Same 63B Destroy+free shape as rowed family members under /O1 /GX flags (EHsc gives 59B missing the or-state). Element is the 160-byte AsciiString-head view already modelled in stlport_asciistring_record_bodies.cpp.
struct BfmeStringHeadRecord160 { AsciiString m_head; int m_tail[39]; public: ~BfmeStringHeadRecord160(); };
template _STL::vector<BfmeStringHeadRecord160>::~vector();

// ??1?$vector@URva0048130E@@V?$allocator@URva0048130E@@@_STL@@@_STL@@QAE@XZ @0x004815AE 63B.
// ProductionQueueHordeContainModuleData +0xD4 member vector: retail destroys the range through the rowed 8-byte filter-plus-string _Destroy at 0x00481595 then frees storage via 0x30830 (EH states 0/-1); called by the ModuleData dtor at 0x004817B6. Element is Rva0048130E whose dtor is rowed at 0x0048130E; size-free per the family rule.
struct Rva0048130E { public: ~Rva0048130E(); unsigned char m_data[8]; };
template _STL::vector<Rva0048130E>::~vector();

// ??1?$vector@VRva002A73B8@@V?$allocator@VRva002A73B8@@@_STL@@@_STL@@QAE@XZ @0x002AE486 63B.
// Same 63B Destroy-plus-free shape under /O1 /GX (EH states 0/-1): destroys the range
// through the ICF-twin _Destroy at 0x002A752F (pinned twin of the rowed 25B
// Rva002A752FDestroy at same address stride 0xC via rowed dtor 0x002A73B8) then frees
// via 0x30830; called at +0x20 by the 48B parent at 0x002AE627. Element is the 0xC
// Rva002A73B8 with rowed dtor at 0x002A73B8; 0xC pad gives the twin stride.
class Rva002A73B8 { public: ~Rva002A73B8(); private: char m_pad[0xC]; };
template _STL::vector<Rva002A73B8>::~vector();

// ??1?$vector@URva00395D77@@V?$allocator@URva00395D77@@@_STL@@@_STL@@QAE@XZ @0x0039977A 63B.
// CastleBehavior range vector: destroys via rowed 12-byte _Destroy at 0x00399336 then frees via 0x30830.
// Same 63B Destroy-plus-free shape as rowed 0x004815AE. Caller at 0x0039A1F1 plus Unwind funclets.
struct Rva00395D77 { public: ~Rva00395D77(); unsigned char m_data[12]; };
template _STL::vector<Rva00395D77>::~vector();

// ??1?$vector@URva000BEDF0Record@@V?$allocator@URva000BEDF0Record@@@_STL@@@_STL@@QAE@XZ @0x000c68c2 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x000c37e6 then frees via 0x30830; called at 0x000c8c74 plus Unwind funclets.
struct Rva000BEDF0Record { public: ~Rva000BEDF0Record(); unsigned char m_data[0x14]; };
template _STL::vector<Rva000BEDF0Record>::~vector();

// ??1?$vector@VRva001EC349@@V?$allocator@VRva001EC349@@@_STL@@@_STL@@QAE@XZ @0x001ECFDF 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x001ECFC6 then frees via 0x30830; caller at 0x001ED0F9.
class Rva001EC349 { public: ~Rva001EC349(); private: unsigned char m_pad[0x24]; };
template _STL::vector<Rva001EC349>::~vector();

// ??1?$vector@VRva001ED0DE@@V?$allocator@VRva001ED0DE@@@_STL@@@_STL@@QAE@XZ @0x001ED363 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x001ED34A then frees via 0x30830; caller at 0x001ED446.
class Rva001ED0DE { public: ~Rva001ED0DE(); private: unsigned char m_pad[0x24]; };
template _STL::vector<Rva001ED0DE>::~vector();

// ??1?$vector@URva00414BDBElement@@V?$allocator@URva00414BDBElement@@@_STL@@@_STL@@QAE@XZ @0x00414721 63B.
// Same 63B Destroy-plus-free shape: destroys the range through pinned
// _Destroy at 0x00414508 then frees via 0x30830; caller at 0x00414B5B in 0x00414B40; unblocks 0x00414B40.
struct Rva00414BDBElement { public: ~Rva00414BDBElement(); char m_pad[0x30]; };
// _Destroy is retail's 24-byte out-of-line body at 0x00414508 (StlportDestroyRva00414508.cpp); only declare it.
namespace _STL { template <> void _Destroy<Rva00414BDBElement *>(Rva00414BDBElement *, Rva00414BDBElement *); }
template _STL::vector<Rva00414BDBElement>::~vector();

// ??1?$vector@URvaPair0039973B@@V?$allocator@URvaPair0039973B@@@_STL@@@_STL@@QAE@XZ @0x0039973B 63B.
// Same 63B Destroy-plus-free shape under /O1 /GX (EH states 0/-1): destroys the range
// through the rowed 8-byte AsciiString-keyed DestroyPairs at 0x32C0CA then frees
// via 0x30830; caller at 0x0039A1FD plus Unwind funclets at 0xB81119/0xB81178.
// Sits just before CastleBehavior range vector 0x0039977A; 8-byte stride plus key
// dtor are all this body observes so the honest RvaPair address name stands in.
struct RvaPair0039973B { AsciiString m_key; int m_value; public: ~RvaPair0039973B(); };
template _STL::vector<RvaPair0039973B>::~vector();

// ??1?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@QAE@XZ @0x001D9F62 63B.
// Same 63B Destroy-plus-free shape under /O1 /GX (EH states 0/-1): destroys the range
// through the rowed 8-byte AsciiString-keyed DestroyPairs at 0x32C0CA then frees
// via 0x30830; landing unblocks 0x001DA2D5 and 0x001DAD68. Sits between TailRecord
// reserve 0x001D9E29 and overflow 0x001D9FAC; 8-byte stride plus key dtor are all
// this body observes so the honest RvaPair address name stands in.
struct RvaPair001D9F62 { AsciiString m_key; int m_value; public: ~RvaPair001D9F62(); };
template _STL::vector<RvaPair001D9F62>::~vector();

// ??1?$vector@UBfmeStringHeadRecord184@@V?$allocator@UBfmeStringHeadRecord184@@@_STL@@@_STL@@QAE@XZ @0x0008B64A 63B.
// Same 63B Destroy-plus-free shape under /O1 /GX (EH states 0/-1): destroys the range
// through the rowed _Destroy at 0x0008B632 then frees storage via 0x00030830;
// caller at 0x0008B79B in 0x0008B77D (+0x2C member). Element is the 184-byte
// AsciiString-head view in stlport_asciistring_record_bodies.cpp.
struct BfmeStringHeadRecord184 { public: ~BfmeStringHeadRecord184(); };
template _STL::vector<BfmeStringHeadRecord184>::~vector();

// ??1?$vector@UMade002CC5E1DamageScalar@@V?$allocator@UMade002CC5E1DamageScalar@@@_STL@@@_STL@@QAE@XZ @0x507bd0 (_Destroy at 0x507bb7)
// DamageNugget "DamageScalar" entries (Made002CC5E1DamageScalar.cpp); the
// nugget dtor at 0x00508684 calls this for its +0x168 member.
struct Made002CC5E1DamageScalar { public: ~Made002CC5E1DamageScalar(); };
// The range destroy over the real 8-byte element is the held unit's; this
// size view would build a wrong stride, so only declare it.
namespace _STL { template <> void _Destroy<Made002CC5E1DamageScalar *>(Made002CC5E1DamageScalar *, Made002CC5E1DamageScalar *); }
template _STL::vector<Made002CC5E1DamageScalar>::~vector();

// ??1?$vector@VCreateAHeroSubClass@CreateAHeroManager@@V?$allocator@VCreateAHeroSubClass@CreateAHeroManager@@@_STL@@@_STL@@QAE@XZ @0x0021F7A7 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x0021F466 then frees via 0x30830; caller at 0x0021F90E in 0x0021F8F3.
// Element is CreateAHeroManager::CreateAHeroSubClass (216 bytes; dtor 0x0021E50F).

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<CreateAHeroManager::CreateAHeroSubClass *>(CreateAHeroManager::CreateAHeroSubClass * f,CreateAHeroManager::CreateAHeroSubClass * l,__false_type const &) { for ( ; f != l; ++f) _Destroy(&*f); } }
template _STL::vector<CreateAHeroManager::CreateAHeroSubClass>::~vector();

// The following ~vector bodies share the 63B Destroy-plus-free shape under
// /O1 /GX. Each was placed as a masked-byte twin of the rowed instantiations
// above; its _Destroy REL32 (offset +0x1A) reads the address that the ledger
// already names as this element type's _Destroy, and no other element type's
// _Destroy is named there. Element views are the footprints already used for
// these types elsewhere; only their destructors matter to these bodies.

// ??1?$vector@URva00413B16Element@@V?$allocator@URva00413B16Element@@@_STL@@@_STL@@QAE@XZ @0x0022DC9B (_Destroy at 0x0022D928)
struct Rva00413B16Element { public: ~Rva00413B16Element(); };
// Use the retail range helper; this TU models only vector destruction.
namespace _STL { template <> void _Destroy<Rva00413B16Element *>(Rva00413B16Element *, Rva00413B16Element *); }
template _STL::vector<Rva00413B16Element>::~vector();

// ??1?$vector@URva002E2690Element@@V?$allocator@URva002E2690Element@@@_STL@@@_STL@@QAE@XZ @0x002B0B32 (_Destroy at 0x002AF4ED)
struct Rva002E2690Element { public: ~Rva002E2690Element(); };
// Use the retail range helper; this TU models only vector destruction.
namespace _STL { template <> void _Destroy<Rva002E2690Element *>(Rva002E2690Element *, Rva002E2690Element *); }
template _STL::vector<Rva002E2690Element>::~vector();

// ??1?$vector@URva000C828CElement@@V?$allocator@URva000C828CElement@@@_STL@@@_STL@@QAE@XZ @0x000C7720 (_Destroy at 0x000C4DEF)
struct Rva000C828CElement { public: ~Rva000C828CElement(); };
// Use the retail range helper; this TU models only vector destruction.
namespace _STL { template <> void _Destroy<Rva000C828CElement *>(Rva000C828CElement *, Rva000C828CElement *); }
template _STL::vector<Rva000C828CElement>::~vector();

// ??1?$vector@VRva0021F876@@V?$allocator@VRva0021F876@@@_STL@@@_STL@@QAE@XZ @0x0021FDEC (_Destroy at 0x0021FDD3)
class CreateAHeroManager::CreateAHeroClass { public: ~CreateAHeroClass(); };
template _STL::vector<CreateAHeroClass>::~vector();

// ??1?$vector@URva00511E48@@V?$allocator@URva00511E48@@@_STL@@@_STL@@QAE@XZ @0x0051211C 63B (pinned on the row ??1Rva0051211C@@QAE@XZ).
// AptMessenger's +0x28C member: range destroy through the 8-byte DestroyPairs at 0x32C0CA, then free; element view as in Rva00512000Finish.cpp.
struct Rva00511E48 { AsciiString m_str; char m_c; char m_pad[3]; ~Rva00511E48() {} };
template _STL::vector<Rva00511E48>::~vector();
