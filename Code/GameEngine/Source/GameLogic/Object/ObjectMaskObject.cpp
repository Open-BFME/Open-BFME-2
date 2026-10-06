// cl: /DNDEBUG /MD
//
// Object::maskObject, retail 0x0028B7E2, 60 bytes.
// Identity: ZH Object.cpp defines maskObject immediately before
// isUsingAirborneLocomotor, and retail places this body directly before the
// matched isUsingAirborneLocomotor at 0x0028B81E; the BFME1 donor
// Object_maskObject.cpp has the same set/deselect/clear shape.
// Target facts: the masked bit is bit 1 of the status byte at +0x439, the
// controlling player comes from the rowed Object::getControllingPlayer
// 0x0028AFA9, the player mask is 1 << (player +0x54), and the deselect goes
// through the rowed GameLogic::deselectObject 0x0023C9F8 with force TRUE.
// Callers 0x0046016B 0x004833B3 0x004838D4 0x004A415D.

typedef bool Bool;
typedef unsigned int PlayerMaskType;

class Player
{
public:
	PlayerMaskType getPlayerMask() const { return 1 << m_playerIndex; }

private:
	unsigned char m_pad[0x54];
	int m_playerIndex; // +0x54
};

class Object;

class GameLogic
{
public:
	void deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
	void maskObject(Bool mask);

private:
	unsigned char m_pad[0x439];
	unsigned char m_privateStatus; // +0x439
};

void Object::maskObject(Bool mask)
{
	if (mask)
	{
		m_privateStatus |= 2;
		TheGameLogic->deselectObject(this, ~getControllingPlayer()->getPlayerMask(), true);
	}
	else
	{
		m_privateStatus &= ~2;
	}
}
