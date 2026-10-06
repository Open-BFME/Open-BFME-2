// cl: /DNDEBUG /MD
//
// ?setCurrentVictim@AIUpdateInterface@@QAEXPBVObject@@@Z,
// retail 0x00268D1F, 82 bytes. Dedicated TU.
// Verbatim ZH logic (GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:4193): NULL clears m_currentVictimID at +0x40 after removing self
// from the old victim's targeter list; else stores victim->getID().
// BFME2 layout (retail-proven): m_object at +0x08, m_currentVictimID at +0x40,
// Object id at +0x74, AI at +0x258, addTargeter at vtable slot 0x204.
// Sibling getCurrentVictim 0x00268D71 proves the class and +0x40.

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

enum ObjectID
{
	INVALID_ID = 0
};

typedef bool Bool;

class AIUpdateInterface;

class Object
{
	char m_pad0[0x74];
	ObjectID m_id;
	char m_pad1[0x258 - 0x78];
	AIUpdateInterface *m_ai;

public:
	AIUpdateInterface *getAI() const { return m_ai; }
	ObjectID getID() const { return m_id; }
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface : public BfmeVirtualSlots<129>
{
	char m_pad04[4];
	Object *m_object;
	char m_pad0C[0x40 - 0x0C];
	ObjectID m_currentVictimID;

public:
	virtual void addTargeter(ObjectID id, Bool add);
	void setCurrentVictim(const Object *victim);
};

// ?setCurrentVictim@AIUpdateInterface@@QAEXPBVObject@@@Z
void AIUpdateInterface::setCurrentVictim(const Object *victim)
{
	if (victim == 0)
	{
		if (m_currentVictimID != INVALID_ID)
		{
			Object *self = m_object;
			Object *target = TheGameLogic->findObjectByID(m_currentVictimID);
			if (self != 0 && target != 0)
			{
				AIUpdateInterface *targetAI = target->getAI();
				if (targetAI)
				{
					targetAI->addTargeter(self->getID(), false);
				}
			}
		}

		m_currentVictimID = INVALID_ID;
	}
	else
	{
		m_currentVictimID = victim->getID();
	}
}
