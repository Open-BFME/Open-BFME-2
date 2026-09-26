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
