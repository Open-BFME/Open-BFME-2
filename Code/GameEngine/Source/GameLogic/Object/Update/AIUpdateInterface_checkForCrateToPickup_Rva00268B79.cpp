// cl: /O1 /DNDEBUG /MD
//
// ?checkForCrateToPickup@AIUpdateInterface@@QAEPAVObject@@XZ
// retail 0x00268B79, 92 bytes (Ghidra FUN_00668b79), pinned under this name.
//
// Donor: GeneralsMD AIUpdate.cpp checkForCrateToPickup. In BFME 2 the crate
// ID (+0x238) is cleared before the lookup reads it, so retail asks
// findObjectByID for ID 0 (the earlier "dead loop" verdict); the scan is
// otherwise Zero Hour's: walk the crate's behavior modules (+0x244), take
// each one's collide interface (behavior interface at +0x0C, slot 1) and
// return the crate if it would like to collide with our object (slot 1).

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class CollideModuleInterface
{
public:
	virtual void slot00();
	virtual bool wouldLikeToCollideWith(const Object *other);
};

class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual CollideModuleInterface *getCollide();
};

class BehaviorModuleHead
{
public:
	virtual ~BehaviorModuleHead();
private:
	int m_04;
	int m_08;
};

class BehaviorModule : public BehaviorModuleHead, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
private:
	unsigned char m_pad00[0x244];
	BehaviorModule **m_behaviors;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	Object *checkForCrateToPickup();
private:
	Object *getObject() const { return m_object; }

	void *m_vtable;
	unsigned char m_pad04[0x08 - 0x04];
	Object *m_object;
	unsigned char m_pad0C[0x238 - 0x0C];
	ObjectID m_crateCreated;
};

Object *AIUpdateInterface::checkForCrateToPickup()
{
	if (m_crateCreated != INVALID_ID)
	{
		m_crateCreated = INVALID_ID;
		Object *crate = TheGameLogic->findObjectByID(m_crateCreated);
		if (crate)
		{
			for (BehaviorModule **i = crate->getBehaviorModules(); *i; ++i)
			{
				CollideModuleInterface *collide = (*i)->getCollide();
				if (!collide)
					continue;
				if (collide->wouldLikeToCollideWith(getObject()))
					return crate;
			}
		}
	}
	return 0;
}
