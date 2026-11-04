// cl: /MD
// AptOnlineCustomMatch (WorldBuilder names 0x0059EEE2 UpdateHostStartGameButton,
// AptOnlineCustomMatch.cpp lines 4429..4432, which calls 0x0059EE96 on the same this).
// ?rva0059EE96 @0x0059EE96 76B: guarded Enable/Disable AptCall.
// If force a1 is clear and flag +0x4C1 already equals value a0 return; else
// store flag, pick literal EnableButtonPlayGame vs DisableButtonPlayGame by a0,
// get prefix via virtual slot 0x28, load level via m58 plus 0x274, then rowed
// 0x00524EF4 AptCall with TheRva00222A8BTarget.
// Evidence: retail cmp/je early plus test/je string select plus call-indirect
// plus three pushes to 0x00524EF4, neighbours Disp32Clearer plus Rva0059EF62Set,
// callers 0x0059EF29 0x005A27DC 0x005A62CF 0x005A655B.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

#include "../../Include/GameNetwork/GameInfo.h"


#include "../../Include/GameNetwork/GameSpyStagingRoom.h"
#include "../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

struct Mid0059EE96
{
	char m_pad00[0x274];
	void *m_level274;
};

class AptOnlineCustomMatch
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual const char *f10();
	void rva0059EE96(unsigned char enable, unsigned char force);
	void UpdateHostStartGameButton();
private:
	char m_pad04[0x58 - 4];
	Mid0059EE96 *m_mid58;
	char m_pad5C[0x4C1 - 0x5C];
	unsigned char m_flag4C1;
};

void AptOnlineCustomMatch::rva0059EE96(unsigned char enable, unsigned char force)
{
	if (!force)
	{
		if (m_flag4C1 == enable)
			return;
	}
	m_flag4C1 = enable;
	void *lvl;
	if (enable)
	{
		lvl = m_mid58->m_level274;
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), lvl, f10(), "EnableButtonPlayGame");
	}
	else
	{
		lvl = m_mid58->m_level274;
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), lvl, f10(), "DisableButtonPlayGame");
	}
}

void AptOnlineCustomMatch::UpdateHostStartGameButton()
{
	if (!TheGameSpyInfo)
		return;
	GameInfo *gi = TheGameSpyInfo->getCurrentStagingRoom();
	if (!gi)
		return;
	int human = 0;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = gi->getSlot(i);
		if (slot->isHuman())
			++human;
	}
	rva0059EE96(human >= 2, 0);
}
