// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
//
// ?bfmeGo1001A@BfmeA1001@@QAEXPAX@Z, retail 0x004F33BD, 47 bytes.
// Both callees are named from retail's own REL32 displacements: the call at
// +0x11 lands on 0x00049DC5 (?findObjectByID@GameLogic@@QAEPAVObject@@W4ObjectID@@@Z)
// and the call at +0x1C on 0x0028AFA9 (?getControllingPlayer@Object@@QBEPAVPlayer@@XZ).

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Player;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

// Retail's global read by the body is GameLogic.cpp's `GameLogic *TheGameLogic`.
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class BfmeA1001
{
public:
	void bfmeGo1001A(void *a);

	char m_bfmePad[8];
	int m_bfmeId;
};

void BfmeA1001::bfmeGo1001A(void *a)
{
	int id = m_bfmeId;

	if (!id)
		return;

	Object *x = TheGameLogic->findObjectByID((ObjectID)id);

	if (x && (void *)x->getControllingPlayer() == a)
		return;

	m_bfmeId = 0;
}
