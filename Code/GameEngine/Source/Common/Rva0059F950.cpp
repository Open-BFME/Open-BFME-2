// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// stlport
// ?rva0059F950@Rva0059F950@@QAEXXZ, retail 0x0059F950, 135 bytes.
// Save prefs from GameSpy slot: getLocalSlotNum slot13, getGameSpySlot, three
// GameModePreferences int setters from slot +0xC +0x18 +0x5C, amIHost slot12,
// getMap to AsciiString setter, tail virtual slot3. Evidence: rowed 0x0044DCB9
// 0x0044DD1E 0x0044DC54 0x0044DD83 0x0023E943, pin 0x004FDA3D, donor
// WOLGameSetupMenu savePlayerInfo, callers 0x0059FC5C 0x005A10C2.
#include "ascii_string.h"

class GameSpyGameSlot
{
public:
	char m_pad0[0xC];
	int m_C;
	char m_pad18[0x18 - 0xC - 4];
	int m_18;
	char m_pad5C[0x5C - 0x18 - 4];
	int m_5C;
};

#include "../../Include/Common/GameModePreferences.h"

#include "../../Include/GameNetwork/GameInfo.h"

#include "../../Include/GameNetwork/GameSpyStagingRoom.h"

extern GameSpyStagingRoom *TheGameSpyGame;	// retail RVA 0x00A02324, defined in CreateAHeroManagerList.cpp

class Rva0059F950
{
public:
	void rva0059F950();
private:
	char m_pad[0x46C];
	GameModePreferences m_prefs;
};

void Rva0059F950::rva0059F950()
{
	if (!TheGameSpyGame)
		return;
	int slotNum = TheGameSpyGame->getLocalSlotNum();
	if (slotNum < 0)
		return;
	GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(slotNum);
	if (!slot)
		return;
	m_prefs.rva0044DCB9(slot->m_C);
	m_prefs.rva0044DD1E(slot->m_18);
	m_prefs.rva0044DC54(slot->m_5C);
	if (TheGameSpyGame->amIHost())
		m_prefs.rva0044DD83(TheGameSpyGame->getMap());
	m_prefs.write();
}

struct Member70
{
	virtual ~Member70();
	virtual void slot01();
};

struct Ret53Obj
{
	virtual void gap00();
	virtual void gap01();
	virtual void gap02();
	virtual void gap03();
	virtual void gap04();
	virtual void gap05();
	virtual void gap06();
	virtual void gap07();
	virtual void gap08();
	virtual void gap09();
	virtual void slot10();
};

#include "../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

// AptOnlineCustomMatch::OnBttnCancel, retail 0x0059FC45 (90B): WorldBuilder
// name (AptOnlineCustomMatch.cpp line 1890). State 8 only clears +0x333;
// otherwise it saves the slot preferences (0x0059F950 on the same this),
// leaves the GameSpy room, notifies the +0x70 member and resets the state.
class AptOnlineCustomMatch
{
public:
	void OnBttnCancel(int unused);
};

void AptOnlineCustomMatch::OnBttnCancel(int)
{
	if (*(int *)((char *)this + 0x488) == 8) {
		*(bool *)((char *)this + 0x333) = false;
		return;
	}
	((Rva0059F950 *)this)->rva0059F950();
	if (TheGameSpyInfo) {
		Ret53Obj *ret = (Ret53Obj *)TheGameSpyInfo->getCurrentStagingRoom();
		if (ret)
			ret->slot10();
		TheGameSpyInfo->leaveStagingRoom();
	}
	((Member70 *)((char *)this + 0x70))->slot01();
	*(int *)((char *)this + 0x488) = 0;
}
