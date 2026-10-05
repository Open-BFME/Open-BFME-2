// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?setPlayerLeaveStatus@GameLogic@@QAEXHABVAsciiString@@H@Z @0x23D1A5 (62B):
// GameLogic player-leave-status slot setter called once per slot from
// GameLogic::bfmePopulateGameReport at 0x247672. Retail bounds-checks the
// slot, clears the slot's not-present flag, copies the slot display name and
// records the human status. The BFME1 donor
// (GameLogicPopulateGameReport.cpp) inlines these three stores in its slot
// loop over statusName-8 (not-present), statusName->set (name) and
// statusName-4 (human); BFME2 outlines them here. The entry stride is 0x1C
// with the name at +0x18, so AsciiString is the 4-byte pooled handle here.
typedef bool Bool;

#include "ascii_string.h"

struct PlayerLeaveStatus
{
	int m_status;
	int m_quitFrame;
	int m_defeatFrame;
	int m_victoryFrame;
	Bool m_notPresent;
	unsigned char m_unknown11[3];
	int m_isHuman;
	AsciiString m_playerName;
};

class GameLogic
{
public:
	void setPlayerLeaveStatus(int slotIndex, const AsciiString &playerName, int isHuman);
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);
	void rva0023D17D();
	void rva0023D201(int slotIndex, int status);
private:
	unsigned char m_unknown00[0x40];
	int m_frame40;
	unsigned char m_unknown44[0x1C4 - 0x44];
	PlayerLeaveStatus m_playerLeaveStatus[8];
};

// ?setPlayerLeaveStatus@GameLogic@@QAEXHABVAsciiString@@H@Z
void GameLogic::setPlayerLeaveStatus(int slotIndex, const AsciiString &playerName, int isHuman)
{
	if (slotIndex < 0 || slotIndex >= 8)
		return;
	m_playerLeaveStatus[slotIndex].m_notPresent = false;
	((StringBase<char> *)&m_playerLeaveStatus[slotIndex].m_playerName)->set(*(const StringBase<char> *)&playerName);
	m_playerLeaveStatus[slotIndex].m_isHuman = isHuman;
}

// ?getPlayerLeaveStatus@GameLogic@@QAEPAUPlayerLeaveStatus@@H@Z
PlayerLeaveStatus *GameLogic::getPlayerLeaveStatus(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 8)
		return &m_playerLeaveStatus[playerIndex];
	return 0;
}
void GameLogic::rva0023D17D()
{
	for (int i = 0; i < 8; ++i) {
		m_playerLeaveStatus[i].m_notPresent = true;
		m_playerLeaveStatus[i].m_quitFrame = 0;
		m_playerLeaveStatus[i].m_defeatFrame = 0;
		m_playerLeaveStatus[i].m_victoryFrame = 0;
		m_playerLeaveStatus[i].m_status = 0;
		m_playerLeaveStatus[i].m_isHuman = 0xff;
	}
}
// ?rva0023D201@GameLogic@@QAEXHH@Z @0x0023D201 40B: range-checks slot 0-7, stores arg2 to entry+0 and this+0x40 frame to entry+4 with stride 0x1C. Same PlayerLeaveStatus array at +0x1C4 as neighbours. Callers at 0x0025E22B and 0x0025E6D6.
void GameLogic::rva0023D201(int slotIndex, int status)
{
	if (slotIndex < 0 || slotIndex >= 8)
		return;
	m_playerLeaveStatus[slotIndex].m_status = status;
	m_playerLeaveStatus[slotIndex].m_quitFrame = m_frame40;
}
