// cl: /O1 /MD /arch:SSE2 /EHs
// WB va 0xb0d8f0 FXParticleSystem::CPUParticle::LoadPostProcess
// GameClient/System/FXParticleSystem.cpp:1070
typedef unsigned int UnsignedInt;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem;
class ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
	void rva0004CBC0() throw();
	ParticleSystem *m_ptr;
	int m_pad04;
	int m_pad08;
};

class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	~BfmeParticleSystemHandle() throw()
	{
		if (m_ptr)
			rva0004CBC0();
	}
	ParticleSystem *operator->() const
	{
		return m_ptr ? m_ptr : Make001FCBD7();
	}
};

class ParticleSystem
{
public:
	unsigned char m_pad00[0xA8];
	ParticleSystemID m_id;
	unsigned char m_padAC[0x19C - 0xAC];
	void *m_owner;
};

namespace FXParticleSystem
{
class CPUParticle;
}

class ParticleSystemManager
{
	friend class FXParticleSystem::CPUParticle;
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class XferException
{
public:
	XferException(int, const char *, ...);
	XferException(const XferException &);
	~XferException();
	char *text;
	int tag;
};

namespace FXParticleSystem
{
class CPUParticle
{
public:
	void LoadPostProcess();
private:
	unsigned char m_pad00[0x78];
	RvaSmartPtr12 m_smart;
	ParticleSystemID m_id;
};

void CPUParticle::LoadPostProcess()
{
	if (m_id == INVALID_PARTICLE_SYSTEM_ID)
		return;
	BfmeParticleSystemHandle h = TheParticleSystemManager->findParticleSystemByID(m_id);
	h->m_owner = this;
	m_smart = *(const RvaSmartPtr12 *)&h;
	if (m_id == INVALID_PARTICLE_SYSTEM_ID)
	{
		throw XferException(5, 0);
	}
}
}
