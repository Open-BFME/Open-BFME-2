// cl: /DNDEBUG /MD
// ?CallPlayerGiveMoney@GameLogic@@QAEXHHH@Z, retail 0x0023D793, 241 bytes.
// Player index pair transfer with Money withdraw/deposit and tracker adds.
// Evidence: leaf lane; callees canPlayersTransferMoneyYet getNthPlayer Rva002AA22AByteField MoneyRva003B0D7C Rva0039B795; caller 0x0037AB1B.
bool canPlayersTransferMoneyYet();
class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;
class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};
class Rva0039B795
{
public:
	void rva0039B795(int delta);
	void rva0039B7CB(int delta);
	void rva0039B7E3(int delta);
};
class Rva0039B7AD
{
public:
	void rva0039B7AD(int delta);
};
class Rva003B0D7C
{
public:
	unsigned int withdraw(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
public:
	char m_pad00[4];
	unsigned int m_val04;
	int m_val08;
};
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;
	char m_pad58[0x90 - 0x58];
	Rva003B0D7C m_money;
	char m_pad9C[0x3BC - 0x9C];
	char m_track[0x14];
};
#include "../../Common/GameLogicObjectLookupView.h"

void GameLogic::CallPlayerGiveMoney(int fromPlayerIndex, int toPlayerIndex, int amount)
{
	if (!canPlayersTransferMoneyYet())
		return;
	if (fromPlayerIndex < 0 || fromPlayerIndex >= 20)
		return;
	if (toPlayerIndex < 0 || toPlayerIndex >= 20)
		return;
	Player *player = 0;
	Player *fromPlayer = 0;
	for (int i = 0; i < 20; i++) {
		Player *p = ThePlayerList->getNthPlayer(i);
		if (p == 0)
			continue;
		if (p->m_playerIndex == fromPlayerIndex)
			fromPlayer = p;
		else if (p->m_playerIndex == toPlayerIndex)
			player = p;
		if (fromPlayer == 0)
			continue;
		if (player == 0)
			continue;
		break;
	}
	if (fromPlayer == 0 || player == 0)
		return;
	if (((Rva002AA22AByteField *)fromPlayer)->get() != 0)
		return;
	if (((Rva002AA22AByteField *)player)->get() != 0)
		return;
	Rva003B0D7C *fromMoney = &fromPlayer->m_money;
	if (fromMoney == 0)
		return;
	unsigned int reqSlot = amount;
	unsigned int balSlot = fromMoney->m_val04;
	unsigned int *pmin = (balSlot < reqSlot) ? &balSlot : &reqSlot;
	Rva0039B795 *fromTrack = (Rva0039B795 *)fromPlayer->m_track;
	unsigned int got = fromMoney->withdraw(*pmin, fromTrack, true);
	Rva0039B795 *toTrack = (Rva0039B795 *)player->m_track;
	Rva003B0D7C *toMoney = &player->m_money;
	toMoney->rva003B0D7C((int)got, (Rva0039B7AD *)toTrack, true);
	fromTrack->rva0039B7E3((int)got);
	toTrack->rva0039B7CB((int)got);
}
