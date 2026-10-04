// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector<T>::~vector for element types whose _Destroy range
// helper is already rowed. Every member is the same-shape sibling of the
// AsciiString instantiation at 0x2CC70 (StlportAsciiStringVectorDtor.cpp):
// only the _Destroy callee differs, so each element type needs just a
// non-trivial destructor here to select that callee by name. Sizes and
// members are irrelevant to these bodies and are not modelled.
#include <vector>

// ??1?$vector@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@_STL@@@_STL@@QAE@XZ @0x57994 (_Destroy at 0x54f94)
// Element view matches StlportOwnedDeque.cpp (kept ??_G at 0x51B1E): 4-byte owning ref.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref();
private:
    long refs;
};
struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
template _STL::vector<OpaqueRefElement4>::~vector();

// ??1?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@QAE@XZ @0x49e274
// (_Destroy at 0x32c0ca, pinned twin of the rowed 8-byte-pair destroy).
// QuantityModifier is ProductionUpdateModuleData's +0x1C modifier element: an
// 8-byte AsciiString-plus-int pair (full layout in the ctor TU
// ProductionUpdateModuleDataCtor.cpp, INI table 0x00C517F0). The 8-byte
// stride is all this body observes, so the element stays size-free here per
// the family rule; the range destroy folds with Rva0032C0CADestroyPairs.
struct QuantityModifier { public: ~QuantityModifier(); };
template _STL::vector<QuantityModifier>::~vector();

// ??1?$vector@UBfmeVectorRecord000BDF17@@V?$allocator@UBfmeVectorRecord000BDF17@@@_STL@@@_STL@@QAE@XZ @0xc6878 (_Destroy at 0xc37cd)
struct BfmeVectorRecord000BDF17 { public: ~BfmeVectorRecord000BDF17(); };
template _STL::vector<BfmeVectorRecord000BDF17>::~vector();

// ??1?$vector@UBfmeAssignRecord172@@V?$allocator@UBfmeAssignRecord172@@@_STL@@@_STL@@QAE@XZ @0x1eb945 (_Destroy at 0x1eb1b3)
struct BfmeAssignRecord172 { public: ~BfmeAssignRecord172(); };
template _STL::vector<BfmeAssignRecord172>::~vector();

// ??1?$vector@UBfmeObject476@@V?$allocator@UBfmeObject476@@@_STL@@@_STL@@QAE@XZ @0x1fd882 (_Destroy at 0x1fd6a4)
struct BfmeObject476 { public: ~BfmeObject476(); };
template _STL::vector<BfmeObject476>::~vector();

// ??1?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@QAE@XZ @0x3b904b (_Destroy at 0x3b8e13)
struct BfmeAssignRecord104 { public: ~BfmeAssignRecord104(); };
template _STL::vector<BfmeAssignRecord104>::~vector();

// ??1?$vector@UBfmeAssignRecord44@@V?$allocator@UBfmeAssignRecord44@@@_STL@@@_STL@@QAE@XZ @0x4146e2 (_Destroy at 0x4144f0)
struct BfmeAssignRecord44 { public: ~BfmeAssignRecord44(); };
template _STL::vector<BfmeAssignRecord44>::~vector();

// ??1?$vector@UBfmeObject544@@V?$allocator@UBfmeObject544@@@_STL@@@_STL@@QAE@XZ @0x4cae89 (_Destroy at 0x4cae71)
struct BfmeObject544 { public: ~BfmeObject544(); };
template _STL::vector<BfmeObject544>::~vector();

// ??1?$vector@URvaPair004C3D4C@@V?$allocator@URvaPair004C3D4C@@@_STL@@@_STL@@QAE@XZ @0x4c3d4c (_Destroy at 0x32c0ca, stride-identical fold with rowed Rva0032C0CADestroyPairs).
// ElvenWoodSpecialPowerModuleData's +0x7C member: retail destroys the range through the rowed 8-byte AsciiString-keyed DestroyPairs at 0x32C0CA then frees storage via 0x30830 (EH states 0/-1); called by the ElvenWood dtor at 0x004C3EEC plus its Unwind funclet. The 8-byte stride plus key dtor are all this body observes; true element name unproven so the honest RvaPair address name stands in for the 8-byte AsciiString-plus-int layout the retail destroy proves.
class AsciiString { public: ~AsciiString(); private: char *m_data; };
struct RvaPair004C3D4C { AsciiString m_key; int m_value; public: ~RvaPair004C3D4C(); };
template _STL::vector<RvaPair004C3D4C>::~vector();

// ??1?$vector@URvaPair00257544@@V?$allocator@URvaPair00257544@@@_STL@@@_STL@@QAE@XZ @0x00257544 63B.
// StructureCollapseUpdateModuleData +0xA0 member vector: retail destroys the range through the rowed 8-byte AsciiString-keyed DestroyPairs at 0x32C0CA then frees storage via 0x30830 (EH states 0/-1); called by the StructureCollapse dtor at 0x00257B7A plus Unwind funclets at 0xB720EF/0xB7213E. ICF-twin of rowed 0x004C3D4C and 0x0049E274 (same 63B Destroy+free shape). True element name unproven so honest RvaPair address name stands in for the 8-byte AsciiString-plus-int layout the retail destroy proves.
struct RvaPair00257544 { AsciiString m_key; int m_value; public: ~RvaPair00257544(); };
template _STL::vector<RvaPair00257544>::~vector();

// ??1?$vector@UBfmeStringHeadRecord160@@V?$allocator@UBfmeStringHeadRecord160@@@_STL@@@_STL@@QAE@XZ @0x00257583 63B.
// Neighbor vector dtor in same 00257 page: retail destroys the range through pinned _Destroy at 0x00257469 (24B wrapper delegating to matched 0x00256FEA loop stepping 0xA0 via releaseBuffer 0x48BA39) then frees via 0x30830; called at 0x00257CA0 in UNCLAIMED 0x00257C88. Same 63B Destroy+free shape as rowed family members under /O1 /GX flags (EHsc gives 59B missing the or-state). Element is the 160-byte AsciiString-head view already modelled in stlport_asciistring_record_bodies.cpp.
struct BfmeStringHeadRecord160 { AsciiString m_head; int m_tail[39]; public: ~BfmeStringHeadRecord160(); };
template _STL::vector<BfmeStringHeadRecord160>::~vector();

// ??1?$vector@URva0048130E@@V?$allocator@URva0048130E@@@_STL@@@_STL@@QAE@XZ @0x004815AE 63B.
// ProductionQueueHordeContainModuleData +0xD4 member vector: retail destroys the range through the rowed 8-byte filter-plus-string _Destroy at 0x00481595 then frees storage via 0x30830 (EH states 0/-1); called by the ModuleData dtor at 0x004817B6. Element is Rva0048130E whose dtor is rowed at 0x0048130E; size-free per the family rule.
struct Rva0048130E { public: ~Rva0048130E(); };
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
struct Rva00395D77 { public: ~Rva00395D77(); };
template _STL::vector<Rva00395D77>::~vector();

// ??1?$vector@URva000BEDF0Record@@V?$allocator@URva000BEDF0Record@@@_STL@@@_STL@@QAE@XZ @0x000c68c2 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x000c37e6 then frees via 0x30830; called at 0x000c8c74 plus Unwind funclets.
struct Rva000BEDF0Record { public: ~Rva000BEDF0Record(); };
template _STL::vector<Rva000BEDF0Record>::~vector();

// ??1?$vector@VRva001EC349@@V?$allocator@VRva001EC349@@@_STL@@@_STL@@QAE@XZ @0x001ECFDF 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x001ECFC6 then frees via 0x30830; caller at 0x001ED0F9.
class Rva001EC349 { public: ~Rva001EC349(); };
template _STL::vector<Rva001EC349>::~vector();

// ??1?$vector@VRva001ED0DE@@V?$allocator@VRva001ED0DE@@@_STL@@@_STL@@QAE@XZ @0x001ED363 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x001ED34A then frees via 0x30830; caller at 0x001ED446.
class Rva001ED0DE { public: ~Rva001ED0DE(); };
template _STL::vector<Rva001ED0DE>::~vector();

// ??1?$vector@URva00414BDBElement@@V?$allocator@URva00414BDBElement@@@_STL@@@_STL@@QAE@XZ @0x00414721 63B.
// Same 63B Destroy-plus-free shape: destroys the range through pinned
// _Destroy at 0x00414508 then frees via 0x30830; caller at 0x00414B5B in 0x00414B40; unblocks 0x00414B40.
struct Rva00414BDBElement { public: ~Rva00414BDBElement(); };
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


// ??1?$vector@URva005088CEDamageScalar@@V?$allocator@URva005088CEDamageScalar@@@_STL@@@_STL@@QAE@XZ @0x507bd0 (_Destroy at 0x507bb7)
// DamageNugget "DamageScalar" entries (Rva005088CEDamageScalar.cpp); the
// nugget dtor at 0x00508684 calls this for its +0x168 member.
struct Rva005088CEDamageScalar { public: ~Rva005088CEDamageScalar(); };
template _STL::vector<Rva005088CEDamageScalar>::~vector();

// ??1?$vector@UBfmePod216@@V?$allocator@UBfmePod216@@@_STL@@@_STL@@QAE@XZ @0x0021F7A7 63B.
// Same 63B Destroy-plus-free shape: destroys the range through the rowed
// _Destroy at 0x0021F466 then frees via 0x30830; caller at 0x0021F90E in 0x0021F8F3.
// Element is the 216-byte pod in StlportVectorGrowthFootprints.cpp.
struct BfmePod216 { public: ~BfmePod216(); };
template _STL::vector<BfmePod216>::~vector();
