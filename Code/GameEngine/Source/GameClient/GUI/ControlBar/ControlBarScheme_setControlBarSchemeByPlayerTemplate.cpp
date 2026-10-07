// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?setControlBarSchemeByPlayerTemplate@ControlBarSchemeManager@@QAEXPBVPlayerTemplate@@_N@Z @0x0031FD0D 316B unlock: ControlBarSchemeManager side selection by PlayerTemplate side
// Evidence: donor BFME1/ZH ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate (Small/Observer/Default literals, compare vs compareNoCase, Display width/height over res, findControlBarScheme Default fallback, init tail); callers at 0x31ADF9 0x31C5E7; unblocks 0x31C5C8; layout m_currentScheme+0 m_multiplyer+4 list+0xC from ControlBarScheme init TU; callees rowed StringBase copy/concat/compare/compareNoCase/set/releaseBuffer init find.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"

struct ICoord2D
{
	int x;
	int y;
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class ControlBarScheme
{
public:
	void init();
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;
};

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }
private:
	char m_pad[0x18];
	AsciiString m_side;
};

class Display
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
};

extern Display *TheDisplay;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59)
#undef V
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
};

extern GameWindowManager *TheWindowManager;

class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void rva0031B641(GameWindow *window, const CommandButton *button);
};

extern ControlBar *TheControlBar;

class RecorderClass
{
public:
	bool isMultiplayer();
};

struct Bfme939Helper : public RecorderClass
{
};

extern Bfme939Helper *g_bfme939Helper;

class Player
{
public:
	const AsciiString &getSide() const { return m_side; }
private:
	char m_pad[0x58];
	AsciiString m_side;
};

#include "ControlBarSchemeManagerView.h"

void ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, bool useSmall)
{
	if (!pt)
		return;
	AsciiString side = pt->getSide();
	if (useSmall)
		side.concat("Small");
	if (m_currentScheme && m_currentScheme->m_side.compare(side) == 0)
	{
		m_currentScheme->init();
		return;
	}
	if (side.isEmpty())
		side.set("Observer");
	ControlBarScheme *tempScheme = 0;
	for (ControlBarSchemeList::iterator it = m_schemeList.begin(); it != m_schemeList.end(); ++it)
	{
		ControlBarScheme *scheme = *it;
		if (!scheme)
			continue;
		if (scheme->m_side.compareNoCase(side) == 0)
		{
			if (!tempScheme || tempScheme->m_ScreenCreationRes.x < scheme->m_ScreenCreationRes.x)
				tempScheme = scheme;
		}
	}
	if (tempScheme)
	{
		m_multiplyer.x = TheDisplay->getWidth() / (float)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (float)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		m_currentScheme = findControlBarScheme("Default");
	}
	if (m_currentScheme)
		m_currentScheme->init();
}

void ControlBarSchemeManager::setControlBarSchemeByPlayer(Player *p)
{
	GameWindow *communicatorButton = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:PopupCommunicator"));
	if (communicatorButton && TheControlBar)
	{
		if (g_bfme939Helper->isMultiplayer())
			TheControlBar->rva0031B641(communicatorButton, TheControlBar->findCommandButton("NonCommand_Communicator"));
		else
			TheControlBar->rva0031B641(communicatorButton, TheControlBar->findCommandButton("NonCommand_BriefingHistory"));
	}
	if (!p)
		return;
	AsciiString side = p->getSide();
	if (m_currentScheme && m_currentScheme->m_side.compare(side) == 0)
	{
		m_currentScheme->init();
		return;
	}
	if (side.isEmpty())
		side.set("Observer");
	ControlBarScheme *tempScheme = 0;
	for (ControlBarSchemeList::iterator it = m_schemeList.begin(); it != m_schemeList.end(); ++it)
	{
		ControlBarScheme *scheme = *it;
		if (!scheme)
			continue;
		if (scheme->m_side.compareNoCase(side) == 0)
		{
			if (!tempScheme || tempScheme->m_ScreenCreationRes.x < scheme->m_ScreenCreationRes.x)
				tempScheme = scheme;
		}
	}
	if (tempScheme)
	{
		m_multiplyer.x = TheDisplay->getWidth() / (float)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (float)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		m_currentScheme = findControlBarScheme("Default");
	}
	if (m_currentScheme)
		m_currentScheme->init();
}
