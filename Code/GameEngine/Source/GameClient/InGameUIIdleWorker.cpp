// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// InGameUI idle-worker virtuals, ported from ZH InGameUI.cpp.
//
// Target evidence: the InGameUI vftable (0x007C7A88; class string "InGameUI"
// right after it) holds six adjacent slots at +0x1C0..+0x1D4. updateIdleWorker
// (slot +0x1D0, 0x0029AFFC) calls +0x1C0 for the count, +0x1C8 to show and
// tail-jumps +0x1CC to hide, exactly ZH's getIdleWorkerCount /
// showIdleWorkerLayout / hideIdleWorkerLayout order (findIdleWorker between
// them at +0x1C4). The bodies carry ZH's string "ControlBar.wnd:ButtonIdleWorker",
// the winEnable(TRUE/FALSE) pair and GadgetButtonSetText with
// UnicodeString::TheEmptyString; +0x1D4 is the reset rowed as
// Rva0029D777Clear.cpp (same +0x978 window, +0x97C display, 20 lists at +0x928).
//
// Retail layout read from the bodies: m_idleWorkers[20] at +0x928,
// m_idleWorkerWin +0x978, m_currentIdleWorkerDisplay +0x97C. getInputEnabled()
// tests both +0x15 (setEngineInputEnabled's flag) and +0x16
// (setInputEnabled's flag). Player index at Player +0x54.
#include <list>
#include "unicode_string.h"

class GameWindow
{
public:
	int winEnable(bool enable);
};

void GadgetButtonSetText(GameWindow *g, UnicodeString text);

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59)
#undef V
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id) = 0;
};

extern GameWindowManager *TheWindowManager;

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_unknown00[0x54];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

typedef _STL::list<Object *> ObjectList;
typedef _STL::list<Object *>::iterator ObjectListIt;

enum { MAX_PLAYER_COUNT = 20 };

class InGameUI
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	V(88) V(89) V(90) V(91) V(92) V(93) V(94) V(95)
	V(96) V(97) V(98) V(99) V(100) V(101) V(102) V(103)
	V(104) V(105) V(106) V(107) V(108) V(109) V(110) V(111)
#undef V

	bool getInputEnabled() { return m_engineInputEnabled && m_inputEnabled; }

private:
	virtual int getIdleWorkerCount(void);
	virtual Object *findIdleWorker(Object *obj);
	virtual void showIdleWorkerLayout(void);
	virtual void hideIdleWorkerLayout(void);
	virtual void updateIdleWorker(void);

	char m_unknown04[0x15 - 4];
	bool m_engineInputEnabled;
	bool m_inputEnabled;
	char m_unknown17[0x928 - 0x17];
	ObjectList m_idleWorkers[MAX_PLAYER_COUNT];
	GameWindow *m_idleWorkerWin;
	int m_currentIdleWorkerDisplay;
};

Object *InGameUI::findIdleWorker(Object *obj)
{
	if(!obj)
		return 0;

	int index = obj->getControllingPlayer()->getPlayerIndex();
	if(m_idleWorkers[index].empty())
		return 0;

	ObjectListIt it = m_idleWorkers[index].begin();
	while(it != m_idleWorkers[index].end())
	{
		Object *itObj = *it;
		if(itObj == obj)
		{
			return itObj;
		}
		++it;
	}
	return 0;
}

void InGameUI::showIdleWorkerLayout(void)
{
	if (!m_idleWorkerWin)
	{
		m_idleWorkerWin = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker"));
		return;
	}

	m_idleWorkerWin->winEnable(true);

	m_currentIdleWorkerDisplay = getIdleWorkerCount();
}

void InGameUI::hideIdleWorkerLayout(void)
{
	if(!m_idleWorkerWin)
		return;
	GadgetButtonSetText(m_idleWorkerWin, UnicodeString::TheEmptyString);
	m_idleWorkerWin->winEnable(false);
	m_currentIdleWorkerDisplay = -1;
}

void InGameUI::updateIdleWorker(void)
{
	int idleCount = getIdleWorkerCount();

	if(idleCount > 0 && m_currentIdleWorkerDisplay != idleCount && getInputEnabled())
		showIdleWorkerLayout();

	if((idleCount <= 0 && m_idleWorkerWin) || !getInputEnabled())
		hideIdleWorkerLayout();
}
