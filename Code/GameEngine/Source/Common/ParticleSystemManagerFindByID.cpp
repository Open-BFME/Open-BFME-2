// cl: /MD /EHsc
// ?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z, retail 0x001F5B0A, 111 bytes.
// Port of BFME1 ParticleSystemManager::findParticleSystemByID (game/GameEngine/Source/GameClient/System/ParticleSystemManager_findByID.cpp).
// Evidence: caller 0x001F5B79 (destroyParticleSystemByID) lea ret [ebp-0x18] push ret push ID thiscall; ID at ParticleSystem+0xA8 matches BFME1 donor;
// list sentinel at +0x4C (BFME2 delta from donor +0x80, matches Rva001F58D4/Rva001F5BBE neighbours); double null-check plus Make001FCBD7 fallback
// matches donor operator bool plus operator->; RvaSmartPtr12 copy at 0x0004CC19 is rowed (SmartPtrCopyCtor.cpp) so Bfme copy forwards to it.

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
	RvaSmartPtr12(const RvaSmartPtr12 &that);
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system = 0) :
		m_system(system), m_previous(0), m_next(0) { }
	__forceinline BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that)
	{
		((RvaSmartPtr12 *)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12 *)&that);
	}
	~BfmeParticleSystemHandle();
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	unsigned char m_unmodelled_000[0xA8];
	ParticleSystemID m_id;
};

struct BfmeParticleSystemNode
{
	BfmeParticleSystemNode *m_next;
	BfmeParticleSystemNode *m_previous;
	BfmeParticleSystemHandle m_value;
};

class BfmeParticleSystemIterator
{
public:
	BfmeParticleSystemIterator(BfmeParticleSystemNode *node) : m_node(node) { }
	BfmeParticleSystemHandle &operator*() const { return m_node->m_value; }
	BfmeParticleSystemHandle *operator->() const { return &m_node->m_value; }
	BfmeParticleSystemIterator &operator++()
	{
		m_node = m_node->m_next;
		return *this;
	}
	bool operator!=(const BfmeParticleSystemIterator &that) const
	{
		return m_node != that.m_node;
	}

private:
	BfmeParticleSystemNode *m_node;
};

class BfmeParticleSystemList
{
public:
	BfmeParticleSystemIterator begin()
	{
		return BfmeParticleSystemIterator(m_node->m_next);
	}
	BfmeParticleSystemIterator end()
	{
		return BfmeParticleSystemIterator(m_node);
	}

private:
	BfmeParticleSystemNode *m_node;
};

class ParticleSystemManager
{
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);

	unsigned char m_unmodelled_000[0x4C];
	BfmeParticleSystemList m_systems;
};

BfmeParticleSystemHandle ParticleSystemManager::findParticleSystemByID(
	ParticleSystemID id )
{
	if (id == INVALID_PARTICLE_SYSTEM_ID)
		return 0;

	for (BfmeParticleSystemIterator it = m_systems.begin();
		it != m_systems.end(); ++it)
	{
		if (*it && (*it)->m_id == id)
			return *it;
	}

	return 0;
}
