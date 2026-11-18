// cl: /O1 /MD /DNDEBUG /G7
//
// ?rva002A99FA@Player@@QAEXXZ, retail 0x002A99FA, 30 bytes (pinned: the
// PlayerList slot 16 loop calls it on each of the twenty players). It
// forwards the player index (+0x54) and the bool at +0x1BC of the object
// behind +0x34 (false when there is none) to Command::Init 0x002A71BC on
// the Command at +0x60 (Command.cpp). This method's name is unknown; kept
// under its address. Retail pushes the
// argument inside each branch (mov al; push eax / push 0) with a bare byte,
// which an if/else over two calls gives under /G7 (cl merges the calls).

#include "../../../Include/Common/ScalarTypes.h"

struct Rva002A99FASource
{
	unsigned char m_pad000[0x1BC];
	Bool m_flag;
};

class Command
{
public:
	void Init(int playerIndex, Bool isHero);
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
	Command m_60;
};

void Player::rva002A99FA()
{
	if (m_34)
		m_60.Init(m_playerIndex, m_34->m_flag);
	else
		m_60.Init(m_playerIndex, false);
}
