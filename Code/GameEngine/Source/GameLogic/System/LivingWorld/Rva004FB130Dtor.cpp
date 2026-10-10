// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1Rva004FB130@@UAE@XZ
// retail 0x004FB130..0x004FB1FD (205 bytes), thiscall, EH frame.
//
// The virtual destructor of the class built by the rowed ctor 0x004FADF4
// (vftables 0x00863438 and 0x008633FC; called by the rowed scalar deleting
// destructor 0x004FB1FD).  Layout from that ctor: a Snapshot-derived primary
// base (vptr plus two words; the word at +0x08 is the registry searched by
// rowed 0x004FB0C7) a listener-list base at +0x0C (pinned dtor 0x004FAC80
// SecondaryBase) and a vector of words at +0x20.  The body asks the rowed
// LivingWorldBuildingNuggetSpawnArmy::getOwningPlayer 0x004FA5F8 for the
// owner; with one it builds a SpawnArmy temporary (rowed int-ctor 0x004E30D5
// and dtor 0x004E3184) and for every queued id the registry fills hands it
// to the rowed LivingWorldPlayer::OnUnitDequeued 0x002E0764.  It then
// notifies the listeners through rowed 0x004FA978 with the slot-0 vcall
// thunk (pinned 0x001FF3A9) and the secondary base as argument; the rest is
// compiler-generated member and base destruction (EH unwind map: Snapshot
// dtor 0x0049B47C / 0x004FAC80 / vector dtor 0x0007FAB3 / 0x004E3184).
// WorldBuilder twin 0x01309C80 (unnamed) has the same owner and registry loop.
// The sibling Rva005C48E5Dtor.cpp shows the same notify-then-destroy shape.

#include <vector>
#include "Common/Snapshot.h"

struct Rva004FAFF2;
class Rva00319CED;
class Rva002E2903Player;

class Rva004FB0C7Registry
{
public:
	bool rva004FB0C7(int key, Rva004FAFF2 *out);
};

class LivingWorldPlayer
{
public:
	void OnUnitDequeued(Rva00319CED *unit);
};

class LivingWorldBuildingNuggetSpawnArmy
{
public:
	Rva002E2903Player *getOwningPlayer();
};

// SpawnArmy: 88-byte record (LivingWorldCampaignObjects.cpp).
class Rva004E3184
{
public:
	Rva004E3184(int index);
	virtual ~Rva004E3184();

	char m_pad04[0x58 - 0x04];
};

class Rva004FA935Listener
{
public:
	virtual void notify(void *);
};

class Rva004FA978
{
public:
	void rva004FA978(void (Rva004FA935Listener::*notify)(void *), void *arg);
};

class Rva0059B7CB : public Snapshot
{
public:
	inline virtual ~Rva0059B7CB() {}

	unsigned int m_04;
	Rva004FB0C7Registry *m_registry;	// +0x08
};

class SecondaryBase
{
public:
	virtual ~SecondaryBase();

	char m_pad04[0x14 - 0x04];
};

class Rva004FB130 : public Rva0059B7CB, public SecondaryBase
{
public:
	virtual ~Rva004FB130();

	_STL::vector<int> m_ids;	// +0x20
	int m_2c;			// +0x2C
};

Rva004FB130::~Rva004FB130()
{
	Rva002E2903Player *owner = ((LivingWorldBuildingNuggetSpawnArmy *)this)->getOwningPlayer();
	if (owner)
	{
		Rva004E3184 army(0);
		for (unsigned int i = 0; i < m_ids.size(); ++i)
		{
			int id = m_ids[i];
			Rva004FB0C7Registry *registry = m_registry;
			if (registry->rva004FB0C7(id, (Rva004FAFF2 *)&army))
				((LivingWorldPlayer *)owner)->OnUnitDequeued((Rva00319CED *)&army);
		}
	}
	((Rva004FA978 *)static_cast<SecondaryBase *>(this))->rva004FA978(&Rva004FA935Listener::notify, static_cast<SecondaryBase *>(this));
}
