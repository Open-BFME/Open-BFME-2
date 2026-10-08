// cl: /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// These minimal declarations emit the wrappers, not complete class layouts.
// No bases, member layout, or destructor implementation are claimed here.
// The noinline empty destructor is an unmatched compilation scaffold; the
// verified wrapper call resolves to the retail destructor through its pin.

// ??_GHordeGarrisonContainModuleData@@UAEPAXI@Z @0x002579E9 28B: slot 0 of vtable 0x00BF4328; calls ??1 at 0x00257A05.
// Owner evidence: vtable 0x00BF4328 installed by ctor 0x0047A251; ctor factory 0x0024BAD1 news 0xD4; dtor 0x00257A05 is 5B jmp to Garrison dtor 0x00257507 (rowed); HordeTransport 5B-jmp precedent.
// The destructor is rowed in HordeGarrisonContainModuleDataDtor.cpp and only
// declared here; the tag constructor (no retail counterpart) makes this TU
// emit the vtable and with it the deleting destructor.
struct EmitVtableTag;
class HordeGarrisonContainModuleData { public: HordeGarrisonContainModuleData(EmitVtableTag *); virtual ~HordeGarrisonContainModuleData(); };
// ?<HordeGarrisonContainModuleData::HordeGarrisonContainModuleData> absent-from-retail
HordeGarrisonContainModuleData::HordeGarrisonContainModuleData(EmitVtableTag *) {}

// ??_GOpenContain@@UAEPAXI@Z @0x00464B7A 28B: slot 0 of vtable 0x00C435E8; calls ??1 at 0x00464692.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00464775 uses class-name string "OpenContain".
class OpenContain { public: __declspec(noinline) virtual ~OpenContain(); };
// ??1OpenContain@@UAE@XZ present-unmatched
OpenContain::~OpenContain() {}
void OpenContain_Delete(OpenContain *p) { delete p; }

// ??_GTransportContainModuleData@@UAEPAXI@Z @0x004684D5 28B: slot 0 of vtable 0x00C442F8; calls ??1 at 0x004684F1.
// Owner evidence (audited 2026-09-26): vtable 0x00C442F8 installed by ctor 0x00468301; ModuleFactory pairs TransportContain with data factory 0x0024B89C; HordeTransport dtor 0x00477D8F jmps to ??1 here.
class TransportContainModuleData { public: __declspec(noinline) virtual ~TransportContainModuleData(); };
// ??1TransportContainModuleData@@UAE@XZ present-unmatched
TransportContainModuleData::~TransportContainModuleData() {}
void TransportContainModuleData_Delete(TransportContainModuleData *p) { delete p; }

// ??_GHordeContain@@UAEPAXI@Z @0x004704C8 28B: slot 0 of vtable 0x00C45050; calls ??1 at 0x0046F901.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0046F860 uses class-name string "HordeContain".
class HordeContain { public: __declspec(noinline) virtual ~HordeContain(); };
// ??1HordeContain@@UAE@XZ present-unmatched
HordeContain::~HordeContain() {}
void HordeContain_Delete(HordeContain *p) { delete p; }

// ??_GHordeTransportContain@@UAEPAXI@Z @0x004771CA 28B: slot 0 of vtable 0x00C45EB8; calls ??1 at 0x004771E6.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00477185 uses class-name string "HordeTransportContain".
class HordeTransportContain { public: __declspec(noinline) virtual ~HordeTransportContain(); };
// ??1HordeTransportContain@@UAE@XZ present-unmatched
HordeTransportContain::~HordeTransportContain() {}
void HordeTransportContain_Delete(HordeTransportContain *p) { delete p; }

// ??_GHordeTransportContainModuleData@@UAEPAXI@Z @0x00477D73 28B: slot 0 of vtable 0x00C45FB0; calls ??1 at 0x00477D8F.
// Owner evidence (audited 2026-09-26): retail registration HordeTransportContain -> data factory RVA 0x0024BA07 -> ctor RVA 0x00477D61; primary vptr store RVA 0x00477D69.
class HordeTransportContainModuleData { public: __declspec(noinline) virtual ~HordeTransportContainModuleData(); };
// ??1HordeTransportContainModuleData@@UAE@XZ present-unmatched
HordeTransportContainModuleData::~HordeTransportContainModuleData() {}
void HordeTransportContainModuleData_Delete(HordeTransportContainModuleData *p) { delete p; }

// ??_GHordeGarrisonContain@@UAEPAXI@Z @0x0047A12B 28B: slot 0 of vtable 0x00C46570; calls ??1 at 0x0047A147.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0047A0E6 uses class-name string "HordeGarrisonContain".
class HordeGarrisonContain { public: __declspec(noinline) virtual ~HordeGarrisonContain(); };
// ??1HordeGarrisonContain@@UAE@XZ present-unmatched
HordeGarrisonContain::~HordeGarrisonContain() {}
void HordeGarrisonContain_Delete(HordeGarrisonContain *p) { delete p; }

// ??_GSiegeEngineContainModuleData@@UAEPAXI@Z @0x0047C9AF 28B: slot 0 of vtable 0x00C47180; calls ??1 at 0x0047C9CB.
// Owner evidence (audited 2026-09-26): retail registration SiegeEngineContain -> data factory RVA 0x0024BBEF -> ctor RVA 0x0047C927; primary vptr store RVA 0x0047C94A.
class SiegeEngineContainModuleData { public: __declspec(noinline) virtual ~SiegeEngineContainModuleData(); };
// ??1SiegeEngineContainModuleData@@UAE@XZ present-unmatched
SiegeEngineContainModuleData::~SiegeEngineContainModuleData() {}
void SiegeEngineContainModuleData_Delete(SiegeEngineContainModuleData *p) { delete p; }

// ??_GHordeSiegeEngineContainModuleData@@UAEPAXI@Z @0x0047DA7D 28B: slot 0 of vtable 0x00C47520; calls ??1 at 0x0047DA99.
// Owner evidence (audited 2026-09-26): retail registration HordeSiegeEngineContain -> data factory RVA 0x0024BC7E -> ctor RVA 0x0047DA08; primary vptr store RVA 0x0047DA2A.
class HordeSiegeEngineContainModuleData { public: __declspec(noinline) virtual ~HordeSiegeEngineContainModuleData(); };
// ??1HordeSiegeEngineContainModuleData@@UAE@XZ present-unmatched
HordeSiegeEngineContainModuleData::~HordeSiegeEngineContainModuleData() {}
void HordeSiegeEngineContainModuleData_Delete(HordeSiegeEngineContainModuleData *p) { delete p; }

// ??_GRiderChangeContain@@UAEPAXI@Z @0x0047E4FF 28B: slot 0 of vtable 0x00C47A00; calls ??1 at 0x0047E51B.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0047E2E0 uses class-name string "RiderChangeContain".
class RiderChangeContain { public: __declspec(noinline) virtual ~RiderChangeContain(); };
// ??1RiderChangeContain@@UAE@XZ present-unmatched
RiderChangeContain::~RiderChangeContain() {}
void RiderChangeContain_Delete(RiderChangeContain *p) { delete p; }

// ??_GRiderChangeContainModuleData@@UAEPAXI@Z @0x0047EB1A 28B: slot 0 of vtable 0x00C47B00; calls ??1 at 0x0047EB36.
// Owner evidence (audited 2026-09-26): retail registration RiderChangeContain -> data factory RVA 0x0024BD63 -> ctor RVA 0x0047EABC; primary vptr store RVA 0x0047EAEB.
class RiderChangeContainModuleData { public: __declspec(noinline) virtual ~RiderChangeContainModuleData(); };
// ??1RiderChangeContainModuleData@@UAE@XZ present-unmatched
RiderChangeContainModuleData::~RiderChangeContainModuleData() {}
void RiderChangeContainModuleData_Delete(RiderChangeContainModuleData *p) { delete p; }

// ??_GCitadelSlaughterHordeContain@@UAEPAXI@Z @0x004806FC 28B: slot 0 of vtable 0x00C48CC0; calls ??1 at 0x00480718.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00480600 uses class-name string "CitadelSlaughterHordeContain".
class CitadelSlaughterHordeContain { public: __declspec(noinline) virtual ~CitadelSlaughterHordeContain(); };
// ??1CitadelSlaughterHordeContain@@UAE@XZ present-unmatched
CitadelSlaughterHordeContain::~CitadelSlaughterHordeContain() {}
void CitadelSlaughterHordeContain_Delete(CitadelSlaughterHordeContain *p) { delete p; }

// ??_GCitadelSlaughterHordeContainModuleData@@UAEPAXI@Z @0x004811CA 28B: slot 0 of vtable 0x00C48E40; calls ??1 at 0x004811E6.
// Owner evidence (audited 2026-09-26): retail registration CitadelSlaughterHordeContain -> data factory RVA 0x0024C100 -> ctor RVA 0x0048112F; primary vptr store RVA 0x00481155.
class CitadelSlaughterHordeContainModuleData { public: __declspec(noinline) virtual ~CitadelSlaughterHordeContainModuleData(); };
// ??1CitadelSlaughterHordeContainModuleData@@UAE@XZ present-unmatched
CitadelSlaughterHordeContainModuleData::~CitadelSlaughterHordeContainModuleData() {}
void CitadelSlaughterHordeContainModuleData_Delete(CitadelSlaughterHordeContainModuleData *p) { delete p; }

// ??_GGarrisonContainModuleData@@UAEPAXI@Z @0x0047981E 28B: calls ??1 at 0x00257507.
// Owner evidence: retail ctor 0x0047978F installs vtable 0x00C462D8; rowed dtor 0x00257507 is ??1GarrisonContainModuleData@@UAE@XZ; 28B flag-test wrapper calls dtor plus delete 0x0002FD60.
class GarrisonContainModuleData { public: __declspec(noinline) virtual ~GarrisonContainModuleData(); };
// ??1GarrisonContainModuleData@@UAE@XZ present-unmatched
GarrisonContainModuleData::~GarrisonContainModuleData() {}
void GarrisonContainModuleData_Delete(GarrisonContainModuleData *p) { delete p; }
