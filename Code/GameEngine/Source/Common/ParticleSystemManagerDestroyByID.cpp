// cl: /O1 /MD /arch:SSE /EHsc
//
// ParticleSystemManager::destroyParticleSystemByID, retail 0x001F5B79 (69
// bytes), after Zero Hour's GameEngine/Source/GameClient/System/
// ParticleSys.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): find the system and destroy it.
// BFME 2 (target evidence) finds it through the rowed findParticleSystemByID
// 0x001F5B0A, which returns a 12-byte handle by value (see
// ParticleSystemManagerFindByID.cpp); the temporary is released only when it
// holds a system, through the rowed handle release 0x0004CBC0 (the
// RvaSmartPtr12 view other units use for the same handle: W3DTruckDrawDtor,
// Rva0056224FCtor), and ParticleSystem::destroy is the rowed 0x001F462C.
enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem
{
public:
	void destroy();
};

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle() throw();
	void *m_system;
	void *m_prev;
	void *m_next;
};

struct RvaSmartPtr12
{
	~RvaSmartPtr12() throw()
	{
		BfmeParticleSystemHandle *p = (BfmeParticleSystemHandle *)this;
		if (p->m_system != 0)
			p->~BfmeParticleSystemHandle();
	}
	ParticleSystem *get() const { return (ParticleSystem *)m_ptr; }
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
private:
	RvaSmartPtr12 findParticleSystemByID(ParticleSystemID id);
};

// ------------------------------------------------------------------------------------------------
void ParticleSystemManager::destroyParticleSystemByID(ParticleSystemID id)
{
	RvaSmartPtr12 sys = findParticleSystemByID(id);
	if (sys.get())
		sys.get()->destroy();
}
