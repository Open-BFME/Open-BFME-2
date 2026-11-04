// cl: /DNDEBUG /MD
//
// ?update@FakePathfindPortalBehaviour@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x00461DC7, 118 bytes. The update-interface slot (this is the +0x10
// subobject): sleeps forever unless the owner's controlling player has a
// record in the rowed TheSkirmishAIManager lookup (0x002A8AB1) and the +0x34 target
// is cached (rowed finder 0x00498725). An unregistered portal (+0x30 clear)
// runs the rowed gate 0x00461DB5 first; then, with +0x32 set, a target
// answering its slot 6 is unregistered (0x004618D4), and without it a target
// that does not answer registers the waypoints (0x004618AB). Only the layout
// this body touches is modelled.

class Player;
#include "../object.h"

struct Rva002A8AB1Record;
#include "../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

void *Rva00498725Find(void *object);

class Rva00461DB5Owner
{
public:
	void rva00461DB5();
	char m_pad00[0x30];
private:
	bool flag30; // +0x30
	bool flag31; // +0x31
};

class FakePathfindPortalTarget
{
public:
	virtual void t00(); virtual void t01(); virtual void t02();
	virtual void t03(); virtual void t04(); virtual void t05();
	virtual bool isActive();	// slot 6 (+0x18)
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

struct FakePathfindPortalModule
{
	virtual void m00();
	const void *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
	unsigned char m_unmodelled0C[0x10 - 0x0C];
};

struct FakePathfindPortalUpdateInterface
{
	virtual UpdateSleepTime update();
};

class FakePathfindPortalBehaviour : public FakePathfindPortalModule, public FakePathfindPortalUpdateInterface
{
public:
	virtual UpdateSleepTime update();
	void rva004618D4();

private:
	void regWaypointsWithPathfinder();

	unsigned char m_unmodelled14[0x30 - 0x14];
	bool m_registered;	// +0x30
	bool m_unmodelled31;
	bool m_unregisterWhenActive;	// +0x32
	FakePathfindPortalTarget *m_target;	// +0x34
};

// ?update@FakePathfindPortalBehaviour@@UAE?AW4UpdateSleepTime@@XZ @0x00461DC7
UpdateSleepTime FakePathfindPortalBehaviour::update()
{
	if (TheSkirmishAIManager->rva002A8AB1(m_object->getControllingPlayer()) != 0)
	{
		if (m_target == 0)
			m_target = (FakePathfindPortalTarget *)Rva00498725Find(m_object);
		if (m_target != 0)
		{
		if (!m_registered)
			((Rva00461DB5Owner *)this)->rva00461DB5();
		if (m_unregisterWhenActive)
		{
			if (m_target->isActive())
				rva004618D4();
		}
		else if (!m_target->isActive())
			regWaypointsWithPathfinder();
		return UPDATE_SLEEP_NONE;
		}
	}
	return UPDATE_SLEEP_FOREVER;
}
