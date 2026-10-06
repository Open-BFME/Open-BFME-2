// cl: /O1 /EHsc /MD /arch:SSE
// GiveUpgradeUpdate.cpp -- GiveUpgradeUpdate members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes. Releasing the target clears status
// 0x42 on it and on the object it links to (Object 0x002931F5, rowed under a
// placeholder name), then forgets the target id at +0x40.

typedef bool Bool;

enum ObjectID { INVALID_ID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_GIVE_UPGRADE_TARGET = 0x42 };

class Object
{
public:
	void setStatus(ObjectStatusTypes status, Bool set);	// 0x0023DB0E
	Object *rva002931F5(Bool flag);				// 0x002931F5
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);			// 0x00049DC5
};

extern GameLogic *TheGameLogic;

class GiveUpgradeUpdate
{
public:
	void releaseTarget();

private:
	unsigned char m_pad00[0x40];
	ObjectID m_targetID;					// +0x40
};

// GiveUpgradeUpdate::releaseTarget, retail 0x0049C592.
void GiveUpgradeUpdate::releaseTarget()
{
	if (m_targetID != INVALID_ID)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
		{
			target->setStatus(OBJECT_STATUS_GIVE_UPGRADE_TARGET, false);
			Object *linked = target->rva002931F5(false);
			if (linked)
				linked->setStatus(OBJECT_STATUS_GIVE_UPGRADE_TARGET, false);
		}
		m_targetID = INVALID_ID;
	}
}
