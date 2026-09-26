// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1LaserUpdate@@UAE@XZ, retail 0x00362F64, 95 bytes. Dtor of the LaserUpdate
// class whose ctor is rowed at 0x00362EEE (vtable 0x00C170E0, slot 0 deleting
// dtor at 0x00363177 calls here).
//
// Donor: BFME1 LaserUpdateDestructorAndRadius.cpp and ZH LaserUpdate.cpp
// LaserUpdate::~LaserUpdate destroys the two ParticleSystemIDs at +0x28 and
// +0x2C through TheParticleSystemManager->destroyParticleSystemByID (pinned
// 0x001F5B79); retail then restores the intermediate vtable 0x00C170A4 and
// tail-calls the opaque fold-point base at 0x0049B47C via the Rva0049B47C pin
// (rowed as ??1WindModuleInfo@FXParticleSystem@@UAE@XZ). Layout follows the
// rowed ctor TU (opaque 0x0C base plus derived IDs at +0x28/+0x2C); the
// C170A4 restore is hand-placed so the 95B shape matches with EH states.

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class LaserUpdate : public Rva0049B47C
{
public:
	virtual ~LaserUpdate();

private:
	char m_pad0C[0x28 - 0x0C];
	ParticleSystemID m_particleSystemID;
	ParticleSystemID m_targetParticleSystemID;
	char m_pad30[0x54 - 0x30];
};

LaserUpdate::~LaserUpdate()
{
	if (m_particleSystemID != INVALID_PARTICLE_SYSTEM_ID)
		TheParticleSystemManager->destroyParticleSystemByID(m_particleSystemID);
	if (m_targetParticleSystemID != INVALID_PARTICLE_SYSTEM_ID)
		TheParticleSystemManager->destroyParticleSystemByID(m_targetParticleSystemID);
	*(void **)this = (void *)0x00C170A4;
}
