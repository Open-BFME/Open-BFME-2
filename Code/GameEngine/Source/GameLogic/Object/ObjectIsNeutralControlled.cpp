// cl: /DNDEBUG /MD /EHsc

// ?isNeutralControlled@Object@@QBE_NXZ, retail 0x0028B091 (23 bytes).
// Object::isNeutralControlled is `return getControllingPlayer() ==
// ThePlayerList->getNeutralPlayer()`. Retail-measured BFME2 layout:
// PlayerList::m_neutralPlayer is at +0x18 here (local is at +0x10);
// ThePlayerList is 0x00DFEEE8 and bakes to its absolute (no ledger pin).
// Object::getControllingPlayer (0x0028AFA9) is rowed; the decl-only call
// keeps the out-of-line E8. /O1 keeps the sub-neg-sbb-inc bool shape.
// Sibling ?isLocallyControlled@Object@@QBE_NXZ, retail 0x0028B07A (23 bytes):
// same shape via getLocalPlayer (+0x10); BFME1 donor Object.cpp
// isLocallyControlled proves the name; 40-plus raw callers.

class Player;

class PlayerList
{
public:
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
	Player *getLocalPlayer() const { return m_localPlayer; }

private:
	unsigned char m_pad00[ 0x10 ];
	Player *m_localPlayer; // +0x10
	unsigned char m_pad14[ 0x18 - 0x10 - 4 ];
	Player *m_neutralPlayer; // +0x18
};

extern PlayerList *ThePlayerList;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool isNeutralControlled() const;
	bool isLocallyControlled() const;
};

bool Object::isNeutralControlled() const
{
	return getControllingPlayer() == ThePlayerList->getNeutralPlayer();
}

bool Object::isLocallyControlled() const
{
	return getControllingPlayer() == ThePlayerList->getLocalPlayer();
}
