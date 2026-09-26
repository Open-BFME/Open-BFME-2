// cl: /O1 /MD
// ??_GFXListAtBonePosFXNugget@@UAEPAXI@Z @0x001E107A 28B
// Deleting dtor slot 0 of vtable 0x007DD8F4; calls rowed ??1 at 0x001E1096 then rowed operator delete at 0x0002FD60.
class FXListAtBonePosFXNugget { public: __declspec(noinline) virtual ~FXListAtBonePosFXNugget(); private: int m_famgen; };
FXListAtBonePosFXNugget::~FXListAtBonePosFXNugget() { m_famgen = 0; }
void famgenDelete(FXListAtBonePosFXNugget *p) { delete p; }

// ??_GParticleSystemFXNugget@@UAEPAXI@Z @0x001E10CE 28B
// Deleting dtor slot 0 of vtable 0x007DD908; calls rowed ??1 at 0x001E10EA then rowed operator delete at 0x0002FD60.
class ParticleSystemFXNugget { public: __declspec(noinline) virtual ~ParticleSystemFXNugget(); private: int m_famgen; };
ParticleSystemFXNugget::~ParticleSystemFXNugget() { m_famgen = 0; }
void famgenDelete(ParticleSystemFXNugget *p) { delete p; }

// ??_GBuffNuggetFXNugget@@UAEPAXI@Z @0x001E32B7 28B
// Deleting dtor slot 0 of vtable 0x007DD9B4; calls rowed ??1 at 0x001E32D3 then rowed operator delete at 0x0002FD60.
class BuffNuggetFXNugget { public: __declspec(noinline) virtual ~BuffNuggetFXNugget(); private: int m_famgen; };
BuffNuggetFXNugget::~BuffNuggetFXNugget() { m_famgen = 0; }
void famgenDelete(BuffNuggetFXNugget *p) { delete p; }

// ??_GW3DLaserDrawModuleData@@UAEPAXI@Z @0x000C9CC9 28B
// Deleting dtor slot 0 of vtable 0x007CB960; calls rowed ??1 at 0x000C9AE7 then rowed operator delete at 0x0002FD60.
class W3DLaserDrawModuleData { public: __declspec(noinline) virtual ~W3DLaserDrawModuleData(); private: int m_famgen; };
W3DLaserDrawModuleData::~W3DLaserDrawModuleData() { m_famgen = 0; }
void famgenDelete(W3DLaserDrawModuleData *p) { delete p; }

// ??_GCaveContain@@MAEPAXI@Z @0x004666AD 28B
// Deleting dtor slot 0 of vtable 0x00843CB8; calls rowed ??1 at 0x004663B2 then rowed operator delete at 0x0002FD60.
class CaveContain { protected: __declspec(noinline) virtual ~CaveContain(); private: int m_famgen;
  friend void famgenDelete(CaveContain *p); };
CaveContain::~CaveContain() { m_famgen = 0; }
void famgenDelete(CaveContain *p) { delete p; }
