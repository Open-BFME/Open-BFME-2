// cl: /DNDEBUG /MD
//
// ?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ,
// retail 0x00268D71, 23 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:4231): INVALID_ID-guarded TheGameLogic->findObjectByID lookup.
// m_currentVictimID lives at +0x40.

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
	char m_pad[0x40];
	ObjectID m_currentVictimID;

public:
	Object *getCurrentVictim() const;
};

// ?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ
Object *AIUpdateInterface::getCurrentVictim() const
{
	if (m_currentVictimID != INVALID_ID)
		return TheGameLogic->findObjectByID(m_currentVictimID);

	return 0;
}
