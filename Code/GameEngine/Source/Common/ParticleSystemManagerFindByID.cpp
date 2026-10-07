// cl: /MD /EHsc
// ?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z, retail 0x001F5B0A, 111 bytes.
// Port of BFME1 ParticleSystemManager::findParticleSystemByID (game/GameEngine/Source/GameClient/System/ParticleSystemManager_findByID.cpp).
// Evidence: caller 0x001F5B79 (destroyParticleSystemByID) lea ret [ebp-0x18] push ret push ID thiscall; ID at ParticleSystem+0xA8 matches BFME1 donor;
// list sentinel at +0x4C (BFME2 delta from donor +0x80, matches Rva001F58D4/Rva001F5BBE neighbours); double null-check plus Make001FCBD7 fallback
// matches donor operator bool plus operator->; RvaSmartPtr12 copy at 0x0004CC19 is rowed (SmartPtrCopyCtor.cpp) so Bfme copy forwards to it.
//
// ?createParticleSystem@ParticleSystemManager@@QAE?AVBfmeParticleSystemHandle@@PBVParticleSystemTemplate@@_N@Z,
// retail 0x001F5A6A, 58 bytes, and the cdecl factory it forwards to, retail 0x001F50BC, 81 bytes (placeholder name).
// Identity: this is TheParticleSystemManager (VA 0x00DFDD04, findTemplate's object) at the SlavedUpdate welding,
// W3DTankTruckDraw emitter and 0x0009873C call sites, each passing a findTemplate result and TRUE; the body is Zero
// Hour's createParticleSystem (null template -> empty, ++m_uniqueSystemID at +0x48, new ParticleSystem(template, id,
// createSlaves)) with BFME's handle return; BFME 1 pins the same spelling. The factory news 0x1DC bytes and runs the
// pinned ParticleSystem constructor 0x001FC701, then wraps the pointer with the rowed raw-pointer constructor 0x0004CBF7
// (no unwind state around it: it cannot throw). Returning the handle by value under /EHsc is what keeps retail's
// zeroed but never-read return-object flag at [ebp-4]; both empty returns use the inline default constructor.

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
	RvaSmartPtr12(void *system) throw();
	RvaSmartPtr12(const RvaSmartPtr12 &that);
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) { }
	__forceinline BfmeParticleSystemHandle(ParticleSystem *system)
	{
		((RvaSmartPtr12 *)this)->RvaSmartPtr12::RvaSmartPtr12(system);
	}
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

namespace FXParticleSystem
{
	class ParticleSystemTemplate;
}

class ParticleSystem
{
public:
	ParticleSystem(const FXParticleSystem::ParticleSystemTemplate *sysTemplate,
		ParticleSystemID id, bool createSlaves);

	unsigned char m_unmodelled_000[0xA8];
	ParticleSystemID m_id;
	unsigned char m_unmodelled_0AC[0x1DC - 0xAC];
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

class ParticleSystemTemplate;

// The cdecl factory at 0x001F50BC: a new ParticleSystem wrapped in a handle.
BfmeParticleSystemHandle __cdecl rva001F50BC(const ParticleSystemTemplate *sysTemplate,
	ParticleSystemID id, bool createSlaves)
{
	return BfmeParticleSystemHandle(new ParticleSystem(
		(const FXParticleSystem::ParticleSystemTemplate *)sysTemplate, id, createSlaves));
}

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate,
		bool createSlaves);
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);

	unsigned char m_unmodelled_000[0x48];
	ParticleSystemID m_uniqueSystemID;
	BfmeParticleSystemList m_systems;
};

BfmeParticleSystemHandle ParticleSystemManager::findParticleSystemByID(
	ParticleSystemID id )
{
	if (id == INVALID_PARTICLE_SYSTEM_ID)
		return BfmeParticleSystemHandle();

	for (BfmeParticleSystemIterator it = m_systems.begin();
		it != m_systems.end(); ++it)
	{
		if (*it && (*it)->m_id == id)
			return *it;
	}

	return BfmeParticleSystemHandle();
}

BfmeParticleSystemHandle ParticleSystemManager::createParticleSystem(
	const ParticleSystemTemplate *sysTemplate, bool createSlaves )
{
	if (sysTemplate == 0)
		return BfmeParticleSystemHandle();

	m_uniqueSystemID = (ParticleSystemID)((UnsignedInt)m_uniqueSystemID + 1);
	return rva001F50BC(sysTemplate, m_uniqueSystemID, createSlaves);
}
