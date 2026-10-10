// ?rva001F4E2D@Rva001F4E2D@@QAE_NXZ
// Native1F4E2D..1F4E82 full85B RET0; existing neutral predicate pin
// is called by Streak55FD6B and Default6 renderer55C478. Primary guide:
// BF1 clean ParticleIsInvisible.cpp donor575ba2b04; its dispatch purpose
// and particle type labels are carried source facts. Target independently
// proves handle3C renderObject8C controller94/98 and slot4 boolean callback.
// Owner stays address-derived because WB B0D730 is unnamed.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
typedef bool Bool;

enum ParticleType
{
	PARTICLE = 1,
	DRAWABLE = 2,
	STREAK = 3,
	VOLUME_PARTICLE = 4,
	SMUDGE = 5,
	TYPE6 = 6,
	TYPE7 = 7
};

class ParticleSystem
{
public:
	ParticleType getParticleType() const { return m_particleType; }

	unsigned char m_unmodelled_000[0x08];
	ParticleType m_particleType;
};

ParticleSystem *Make001FCBD7();

class ParticleSystemHandle
{
public:
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}

private:
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class ParticleVisibilityModule
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual Bool isInvisible(ParticleType type);
};

static __forceinline Bool callParticleInvisible(ParticleVisibilityModule *module,
	ParticleType type)
{
	return module->isInvisible(type);
}

class Rva001F4E2D
{
public:
	Bool rva001F4E2D();

private:
	unsigned char m_unmodelled_000[0x3C];
	ParticleSystemHandle m_system;
	unsigned char m_unmodelled_048[0x44];
	void *m_renderObject;
	unsigned char m_unmodelled_090[4];
	ParticleVisibilityModule *m_defaultModule;
	ParticleVisibilityModule *m_specialModule;
};

Bool Rva001F4E2D::rva001F4E2D()
{
	if (m_renderObject)
		return false;

	ParticleType type = m_system.operator->()->m_particleType;
	switch (type)
	{
		case PARTICLE:
		case DRAWABLE:
		case SMUDGE:
		case TYPE6:
			if (m_defaultModule)
				return callParticleInvisible(m_defaultModule, type);
			return false;

		case STREAK:
		case VOLUME_PARTICLE:
		case TYPE7:
			if (m_specialModule)
				return callParticleInvisible(m_specialModule, type);
			return false;
	}

	return true;
}
