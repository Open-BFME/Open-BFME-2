// ?rva002A99FA@Player@@QAEXXZ
// partial score=0.8 date=2026-10-05
// cl: /O1 /MD /DNDEBUG
//
// ?rva002A99FA@Player@@QAEXXZ, retail 0x002A99FA, 30 bytes (pinned: the
// PlayerList slot 16 loop calls it on each of the twenty players). It
// forwards the player index (+0x54) and the bool at +0x1BC of the object
// behind +0x34 (false when there is none) to 0x002A71BC on the member at
// +0x60. Names unknown; kept under their addresses.

typedef bool Bool;

struct Rva002A99FASource
{
	unsigned char m_pad000[0x1BC];
	Bool m_flag;
};

class Rva002A71BC
{
public:
	void rva002A71BC(int playerIndex, Bool flag);
private:
	unsigned char m_pad[4];
};

class Player
{
public:
	void rva002A99FA();
private:
	unsigned char m_pad00[0x34];
	Rva002A99FASource *m_34;
	unsigned char m_pad38[0x54 - 0x38];
	int m_playerIndex;
	unsigned char m_pad58[0x60 - 0x58];
	Rva002A71BC m_60;
};

void Player::rva002A99FA()
{
	m_60.rva002A71BC(m_playerIndex, m_34 ? m_34->m_flag : false);
}
