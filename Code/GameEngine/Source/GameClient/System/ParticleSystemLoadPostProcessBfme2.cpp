// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-
// Clean BF1 donor575ba2b04743f190f069805fbdc59936123c45da:
// game/GameEngine/Source/GameClient/System/ParticleSystem_loadPostProcess.cpp.
// Donor/ZH supply saved-slave/master reconnection and validation semantics.
// Native001F628F..001F636C complete221B and WB B134D0 independently support
// the post-load identity and two tracking-handle operations. Existing target
// ParticleSystem owner spelling is retained. Target slave15C/ID168,
// master16C/ID178 and destroyed1A4 replace donor160/16C/170/17C/1A8.
// Existing RvaSmartPtr12 assignment and inline null-guard cleanup view from
// ParticleSystemManagerFindByID preserve the target handle12 ABI. No new
// provider aliases or pins: rva0004CBC0 already belongs to that call view.
// Native CFFD18 throw info and85B constructor identify XferException(5,0).
class XferException{public:XferException(int,const char*,...);XferException(const XferException&);~XferException();char *text;int tag;};
enum ParticleSystemID
{
	PARTICLE_SYSTEM_ID_NONE = 0
};

class ParticleSystem;

ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &other);
	void rva0004CBC0()throw();
	operator bool() const { return m_ptr != 0; }
	ParticleSystem *operator->() const
	{
		if (m_ptr == 0)
			return Make001FCBD7();
		return m_ptr;
	}

	ParticleSystem *m_ptr;
	unsigned char m_pad[0x08];
};

class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	~BfmeParticleSystemHandle(){if(m_ptr)rva0004CBC0();}
};

class ParticleSystemManager
{
	friend class ParticleSystem;

	private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class ParticleSystem
{
protected:
	virtual void loadPostProcess(void);

private:
	unsigned char m_pad4[0x15C - 0x04];
	RvaSmartPtr12 m_slaveSystem;
	ParticleSystemID m_slaveSystemID;
	RvaSmartPtr12 m_masterSystem;
	ParticleSystemID m_masterSystemID;
	unsigned char m_pad180[0x1A4 - 0x17C];

public:
	unsigned char m_isDestroyed;
};

// ?loadPostProcess@ParticleSystem@@MAEXXZ
void ParticleSystem::loadPostProcess(void)
{
	if (m_slaveSystemID)
	{
		if (m_slaveSystem.m_ptr != 0)
		{
			throw XferException(5,0);
		}

		m_slaveSystem = TheParticleSystemManager->findParticleSystemByID(m_slaveSystemID);

		if (m_slaveSystem.m_ptr == 0 || m_slaveSystem->m_isDestroyed == 1)
		{
			throw XferException(5,0);
		}
	}

	if (m_masterSystemID)
	{
		if (m_masterSystem.m_ptr != 0)
		{
			throw XferException(5,0);
		}

		m_masterSystem = TheParticleSystemManager->findParticleSystemByID(m_masterSystemID);

		if (m_masterSystem.m_ptr == 0 || m_masterSystem->m_isDestroyed == 1)
		{
			throw XferException(5,0);
		}
	}
}
