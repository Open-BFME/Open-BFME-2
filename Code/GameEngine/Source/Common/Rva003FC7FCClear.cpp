// cl: /DNDEBUG /MD
// ?rva003FC7FC@Rva003FC7FC@@QAEXXZ @0x003FC7FC 48B:
// Clear particle handle at +0x1C and ID at +0x28: if handle.m_system then
// destroy by ID via TheParticleSystemManager then dtor handle and clear
// both to 0. Callees rowed handle dtor 0x0004CBC0 plus pinned destroy
// 0x001F5B79. Callers 0x002118C2 and 0x003FCD71. Owner unproven.
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
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_previous;
	void *m_next;
};
class RvaSmartPtr12
{
	public: void rva0004CBC0(); // 0x0004CBC0, the unlink the inline dtor null test calls
private:

public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
};

class ParticleSystem
{
public:
	char m_pad00[0xA8];
	int m_idA8;
};

ParticleSystem *Make001FCBD7(void);

class Rva003FC7FC
{
public:
	void rva003FC7FC(void);
	void rva003FC7C7(const RvaSmartPtr12 &src);
private:
	unsigned char m_pad[0x1C];
	BfmeParticleSystemHandle m_handle;
	ParticleSystemID m_id;
};

void Rva003FC7FC::rva003FC7FC(void)
{
	if (m_handle.m_system != 0)
	{
		TheParticleSystemManager->destroyParticleSystemByID(m_id);
		if (m_handle.m_system != 0)
		{
			reinterpret_cast<RvaSmartPtr12 *>(&m_handle)->rva0004CBC0();
			m_handle.m_system = 0;
		}
		m_id = INVALID_PARTICLE_SYSTEM_ID;
	}
}

void Rva003FC7FC::rva003FC7C7(const RvaSmartPtr12 &src)
{
	if (*(void * const *)&src != 0)
	{
		((RvaSmartPtr12 *)&m_handle)->operator=(src);
		ParticleSystem *p = *(ParticleSystem * const *)&m_handle;
		ParticleSystem *q;
		if (p == 0)
			q = Make001FCBD7();
		else
			q = p;
		m_id = (ParticleSystemID)q->m_idA8;
	}
}
