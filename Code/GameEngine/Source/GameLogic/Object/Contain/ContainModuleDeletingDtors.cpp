// cl: /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// Most minimal declarations emit only wrappers, not complete class layouts.
// CaveContainModuleData uses its canonical base so its table has all 31 slots.
// The other declarations claim no bases, member layout or destructor implementation.
// The noinline empty destructor is an unmatched compilation scaffold; the
// verified wrapper call resolves to the retail destructor through its pin.

// ??_GHordeGarrisonContainModuleData@@UAEPAXI@Z @0x002579E9 28B: slot 0 of vtable 0x00BF4328; calls ??1 at 0x00257A05.
// Owner evidence: vtable 0x00BF4328 installed by ctor 0x0047A251; ctor factory 0x0024BAD1 news 0xD4; dtor 0x00257A05 is 5B jmp to Garrison dtor 0x00257507 (rowed); HordeTransport 5B-jmp precedent.
// The destructor is rowed in HordeGarrisonContainModuleDataDtor.cpp and only
// declared here; the tag constructor (no retail counterpart) makes this TU
// emit the vtable and with it the deleting destructor.
struct EmitVtableTag;
#include "../../../../Include/GameLogic/Module/OpenContainModuleData.h"
#include "../../../../Include/GameLogic/Module/TransportContainModuleData.h"
class HordeGarrisonContainModuleData { public: HordeGarrisonContainModuleData(EmitVtableTag *); virtual ~HordeGarrisonContainModuleData(); };
// ?<HordeGarrisonContainModuleData::HordeGarrisonContainModuleData> absent-from-retail
HordeGarrisonContainModuleData::HordeGarrisonContainModuleData(EmitVtableTag *) {}

// ??_GOpenContain@@UAEPAXI@Z @0x00464B7A 28B: slot 0 of vtable 0x00C435E8; calls ??1 at 0x00464692.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00464775 uses class-name string "OpenContain".
class OpenContain { public: OpenContain(EmitVtableTag *); virtual ~OpenContain(); };
// ?<OpenContain::OpenContain> absent-from-retail
OpenContain::OpenContain(EmitVtableTag *) {}

// ??_GHordeContain@@UAEPAXI@Z @0x004704C8 28B: slot 0 of vtable 0x00C45050; calls ??1 at 0x0046F901.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0046F860 uses class-name string "HordeContain".
class HordeContain { public: HordeContain(EmitVtableTag *); virtual ~HordeContain(); };
// ?<HordeContain::HordeContain> absent-from-retail
HordeContain::HordeContain(EmitVtableTag *) {}

// ??_GHordeTransportContain@@UAEPAXI@Z @0x004771CA 28B: slot 0 of vtable 0x00C45EB8; calls ??1 at 0x004771E6.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00477185 uses class-name string "HordeTransportContain".
class HordeTransportContain { public: HordeTransportContain(EmitVtableTag *); virtual ~HordeTransportContain(); };
// ?<HordeTransportContain::HordeTransportContain> absent-from-retail
HordeTransportContain::HordeTransportContain(EmitVtableTag *) {}

// ??_GHordeTransportContainModuleData@@UAEPAXI@Z @0x00477D73 28B: slot 0 of vtable 0x00C45FB0; calls ??1 at 0x00477D8F.
// Owner evidence (audited 2026-09-26): retail registration HordeTransportContain -> data factory RVA 0x0024BA07 -> ctor RVA 0x00477D61; primary vptr store RVA 0x00477D69.
class HordeTransportContainModuleData { public: HordeTransportContainModuleData(EmitVtableTag *); virtual ~HordeTransportContainModuleData(); };
// ?<HordeTransportContainModuleData::HordeTransportContainModuleData> absent-from-retail
HordeTransportContainModuleData::HordeTransportContainModuleData(EmitVtableTag *) {}

// ??_GHordeGarrisonContain@@UAEPAXI@Z @0x0047A12B 28B: slot 0 of vtable 0x00C46570; calls ??1 at 0x0047A147.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0047A0E6 uses class-name string "HordeGarrisonContain".
class HordeGarrisonContain { public: HordeGarrisonContain(EmitVtableTag *); virtual ~HordeGarrisonContain(); };
// ?<HordeGarrisonContain::HordeGarrisonContain> absent-from-retail
HordeGarrisonContain::HordeGarrisonContain(EmitVtableTag *) {}

// ??_GSiegeEngineContainModuleData@@UAEPAXI@Z @0x0047C9AF 28B: slot 0 of vtable 0x00C47180; calls ??1 at 0x0047C9CB.
// Owner evidence (audited 2026-09-26): retail registration SiegeEngineContain -> data factory RVA 0x0024BBEF -> ctor RVA 0x0047C927; primary vptr store RVA 0x0047C94A.
class SiegeEngineContainModuleData { public: SiegeEngineContainModuleData(EmitVtableTag *); virtual ~SiegeEngineContainModuleData(); };
// ?<SiegeEngineContainModuleData::SiegeEngineContainModuleData> absent-from-retail
SiegeEngineContainModuleData::SiegeEngineContainModuleData(EmitVtableTag *) {}

// ??_GHordeSiegeEngineContainModuleData@@UAEPAXI@Z @0x0047DA7D 28B: slot 0 of vtable 0x00C47520; calls ??1 at 0x0047DA99.
// Owner evidence (audited 2026-09-26): retail registration HordeSiegeEngineContain -> data factory RVA 0x0024BC7E -> ctor RVA 0x0047DA08; primary vptr store RVA 0x0047DA2A.
class HordeSiegeEngineContainModuleData { public: HordeSiegeEngineContainModuleData(EmitVtableTag *); virtual ~HordeSiegeEngineContainModuleData(); };
// ?<HordeSiegeEngineContainModuleData::HordeSiegeEngineContainModuleData> absent-from-retail
HordeSiegeEngineContainModuleData::HordeSiegeEngineContainModuleData(EmitVtableTag *) {}

// ??_GRiderChangeContain@@UAEPAXI@Z @0x0047E4FF 28B: slot 0 of vtable 0x00C47A00; calls ??1 at 0x0047E51B.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0047E2E0 uses class-name string "RiderChangeContain".
class RiderChangeContain { public: RiderChangeContain(EmitVtableTag *); virtual ~RiderChangeContain(); };
// ?<RiderChangeContain::RiderChangeContain> absent-from-retail
RiderChangeContain::RiderChangeContain(EmitVtableTag *) {}

// ??_GRiderChangeContainModuleData@@UAEPAXI@Z @0x0047EB1A 28B: slot 0 of vtable 0x00C47B00; calls ??1 at 0x0047EB36.
// Owner evidence (audited 2026-09-26): retail registration RiderChangeContain -> data factory RVA 0x0024BD63 -> ctor RVA 0x0047EABC; primary vptr store RVA 0x0047EAEB.
class RiderChangeContainModuleData { public: RiderChangeContainModuleData(EmitVtableTag *); virtual ~RiderChangeContainModuleData(); };
// ?<RiderChangeContainModuleData::RiderChangeContainModuleData> absent-from-retail
RiderChangeContainModuleData::RiderChangeContainModuleData(EmitVtableTag *) {}

// ??_GCitadelSlaughterHordeContain@@UAEPAXI@Z @0x004806FC 28B: slot 0 of vtable 0x00C48CC0; calls ??1 at 0x00480718.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00480600 uses class-name string "CitadelSlaughterHordeContain".
class CitadelSlaughterHordeContain { public: CitadelSlaughterHordeContain(EmitVtableTag *); virtual ~CitadelSlaughterHordeContain(); };
// ?<CitadelSlaughterHordeContain::CitadelSlaughterHordeContain> absent-from-retail
CitadelSlaughterHordeContain::CitadelSlaughterHordeContain(EmitVtableTag *) {}

// ??_GGarrisonContainModuleData@@UAEPAXI@Z @0x0047981E 28B: calls ??1 at 0x00257507.
// Owner evidence: retail ctor 0x0047978F installs vtable 0x00C462D8; rowed dtor 0x00257507 is ??1GarrisonContainModuleData@@UAE@XZ; 28B flag-test wrapper calls dtor plus delete 0x0002FD60.
class GarrisonContainModuleData { public: GarrisonContainModuleData(EmitVtableTag *); virtual ~GarrisonContainModuleData(); };
// ?<GarrisonContainModuleData::GarrisonContainModuleData> absent-from-retail
GarrisonContainModuleData::GarrisonContainModuleData(EmitVtableTag *) {}

// ??_GCaveContainModuleData@@UAEPAXI@Z @0x002576F3 28B: slot 0 of vtable 0x00C43F40; calls ??1 at 0x0025770F.
// Owner evidence: vtable 0x00C43F40 installed by ctor 0x00466D37 (rowed ??0CaveContainModuleData); ModuleFactory pairs CaveContain with data factory 0x00257714; dtor 0x0025770F is a 5B jmp to the OpenContainModuleData dtor 0x00257481 (rowed).
class CaveContainModuleData : public OpenContainModuleData
{
public:
    CaveContainModuleData(EmitVtableTag *);
    virtual ~CaveContainModuleData();
private:
    int m_caveIndexData; // +0x98, as in the retail constructor and field parser
};
// ?<CaveContainModuleData::CaveContainModuleData> absent-from-retail
CaveContainModuleData::CaveContainModuleData(EmitVtableTag *) {}
