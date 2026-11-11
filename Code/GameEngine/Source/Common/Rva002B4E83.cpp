// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002B4E83@Rva002B4E83@@QAEXPAVRva002E0687@@@Z @0x002B4E83 233B.
// Unlock lane; defeat message: if selection locked and local player use GUI:YouHaveBeenDefeated else GUI:PlayerHasBeenDefeated formatted with player name at +0x1c+8 or the empty wide literal, then InGameUI message at 0x4C plus setMissionHelpText(&msg 8).
// Callees rowed isSelectionLocked 0x4253A rva002E0687 0x2E0687 set 0x37150 releaseBuffer 0x36E70 format 0x6CB660 copyCtor 0x37050 setMissionHelpText 0x29B16A; TheGameText fetch slot 0x3C TheInGameUI VA 0xDFEDF0 empty wide literal VA 0xBBB5C4.
#include "unicode_string.h"

typedef unsigned short WideChar;

#include "../../Include/Common/BfmeSelectionState.h"

class Rva002E0687
{
public:
	bool rva002E0687() const;
private:
	char m_pad[0x1c];
public:
	void *m_1c;
};

#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

#include "../../Include/Common/Rva0029B16A.h"


class Rva002B4E83
{
public:
	void rva002B4E83(Rva002E0687 *p);
};

void Rva002B4E83::rva002B4E83(Rva002E0687 *p)
{
	if (!((BfmeSelectionState *)this)->isSelectionLocked())
		return;
	UnicodeString msg;
	if (p->rva002E0687())
		msg = TheGameText->fetch("GUI:YouHaveBeenDefeated");
	else
	{
		msg = TheGameText->fetch("GUI:PlayerHasBeenDefeated");
		const WideChar *name = (p->m_1c != 0) ? (const WideChar *)((char *)p->m_1c + 8) : (const WideChar *)L"";
		msg.format(&msg, name);
	}
	TheInGameUI->message(msg);
	((Rva0029B16A *)TheInGameUI)->setMissionHelpText((int)&msg, 8);
}
