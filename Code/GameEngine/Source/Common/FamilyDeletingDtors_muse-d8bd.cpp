// cl: /O2 /MD
// ??_GParticleBufferClass@@UAEPAXI@Z @0x001AD190 30B
// Deleting dtor; calls rowed ??1ParticleBufferClass@@UAE@XZ at 0x001A80D0 then global operator delete at 0x0002FD60; vtable 0x007D7200 class of ??1; gap between part_buf rows 0x001AC860 and 0x001AD1B0.
class ParticleBufferClass { public: __declspec(noinline) virtual ~ParticleBufferClass(); private: int m_famgen; };
ParticleBufferClass::~ParticleBufferClass() { m_famgen = 0; }
void famgenDelete(ParticleBufferClass *p) { delete p; }
