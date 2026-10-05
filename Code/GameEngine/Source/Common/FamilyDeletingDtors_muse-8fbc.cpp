// cl: /O1 /MD
// ??_GW3DBufferManager@@QAEPAXI@Z @0x000F0956 28B; calls rowed ??1W3DBufferManager@@QAE@XZ @0x001163E7 then operator delete 0x0002FD60.
// Evidence: retail push esi/mov esi,ecx/call/test [esp+8],1 pop-ecx shape; QAE non-virtual dtor so QAEPAXI; rowed dtor in W3DBufferManager.cpp.
// ??_GW3DBufferManager@@QAEPAXI@Z @0x000F0956
class W3DBufferManager { public: ~W3DBufferManager(); };
void famgenDelete(W3DBufferManager *p) { delete p; }

// ??_GBfmeStringRecord00204A30@@QAEPAXI@Z @0x00204B4E 28B; calls rowed ??1BfmeStringRecord00204A30@@QAE@XZ @0x00204848 then delete 0x0002FD60.
class BfmeStringRecord00204A30 { public: ~BfmeStringRecord00204A30(); };
void famgenDelete(BfmeStringRecord00204A30 *p) { delete p; }

// ??_GGpuDrawModuleInfo@FXParticleSystem@@UAEPAXI@Z @0x003A9DC2 28B; calls rowed ??1GpuDrawModuleInfo@FXParticleSystem@@UAE@XZ @0x003A9D43 then delete.
namespace FXParticleSystem { class GpuDrawModuleInfo { public: __declspec(noinline) virtual ~GpuDrawModuleInfo(); private: int m_famgen; }; }
FXParticleSystem::GpuDrawModuleInfo::~GpuDrawModuleInfo() { m_famgen = 0; }
void famgenDelete(FXParticleSystem::GpuDrawModuleInfo *p) { delete p; }

// ??_GRva004DC9EDEntry@@QAEPAXI@Z @0x00426313 28B; calls rowed ??1Rva004DC9EDEntry@@QAE@XZ @0x004DC9ED then delete.
class Rva004DC9EDEntry { public: ~Rva004DC9EDEntry(); };
void famgenDelete(Rva004DC9EDEntry *p) { delete p; }

// ??_GOpenContainModuleData@@UAEPAXI@Z @0x00465221 28B; calls rowed ??1OpenContainModuleData@@UAE@XZ @0x00257481 then delete. Slot0 of vtable 0x00C43658 per ledger.
class OpenContainModuleData { public: __declspec(noinline) virtual ~OpenContainModuleData(); private: int m_famgen; };
OpenContainModuleData::~OpenContainModuleData() { m_famgen = 0; }
void famgenDelete(OpenContainModuleData *p) { delete p; }

// ??_GSpecialPowerModuleData@@UAEPAXI@Z @0x00493333 28B; calls rowed ??1SpecialPowerModuleData@@UAE@XZ @0x0049334F then delete.
class SpecialPowerModuleData { public: __declspec(noinline) virtual ~SpecialPowerModuleData(); private: int m_famgen; };
SpecialPowerModuleData::~SpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(SpecialPowerModuleData *p) { delete p; }
