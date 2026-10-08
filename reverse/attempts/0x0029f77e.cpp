// ?removeIdleWorker@InGameUI@@UAEXPAVObject@@H@Z
// partial score=0.95 date=2026-10-08
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
//
// selectNextIdleWorker (0x0029D64F, slot +0x1AC) is ZH's body: the local
// player (ThePlayerList +0x10) indexes the lists, getSelectCount +0x118 is
// asked twice, TheInGameUI's getFirstSelectedDrawable +0x12C gives the
// drawable whose object (+0xFC) is searched for, the container at Object
// +0x274 replaces a contained worker, then deselectAllDrawables +0x110,
// MSG_CREATE_SELECTED_GROUP (0x3E9) with appendBoolean 0x0030F963 and
// appendObjectID 0x0030F979 (Object +0x74), selectDrawable +0x108 on
// Thing::getDrawable 0x005508E2 and TheTacticalView lookAt +0x54 on the
// position at +0x38.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

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

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	char m_unknown00[0x10];
	Player *m_local;
};

extern PlayerList *ThePlayerList;

enum ObjectID { INVALID_ID = 0 };

class Drawable;

class Thing
{
public:
	Drawable *getDrawable() const;
	const Coord3D *getPosition() const { return &m_cachedPos; }
private:
	char m_unknown00[0x38];
	Coord3D m_cachedPos;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() { return m_containedBy; }
private:
	char m_unknown44[0x74 - 0x44];
	ObjectID m_id;
	char m_unknown78[0x274 - 0x78];
	Object *m_containedBy;
};

class Drawable
{
public:
	Object *getObject() { return m_object; }
private:
	char m_unknown00[0xFC];
	Object *m_object;
};

class GameMessage
{
public:
	enum Type { MSG_CREATE_SELECTED_GROUP = 0x3E9 };
	void appendBooleanArgument(bool arg);
	void appendObjectIDArgument(ObjectID arg);
};

class MessageStream
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17)
#undef V
	virtual GameMessage *appendMessage(GameMessage::Type type) = 0;
};

extern MessageStream *MessageStreamSubsystem;

class View
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20)
#undef V
	virtual void lookAt(const Coord3D *o) = 0;
};

extern View *TheTacticalView;

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
	V(64) V(65)
#undef V
	virtual void selectDrawable(Drawable *draw);
	virtual void r67() = 0;
	virtual void deselectAllDrawables();
	virtual void r69() = 0;
	virtual int getSelectCount();
#define V(n) virtual void r##n() = 0;
	V(71) V(72) V(73) V(74)
#undef V
	virtual Drawable *getFirstSelectedDrawable();
#define V(n) virtual void r##n() = 0;
	V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	V(88) V(89) V(90) V(91) V(92) V(93) V(94) V(95)
	V(96) V(97) V(98) V(99) V(100) V(101) V(102) V(103)
	V(104)
#undef V
	virtual void addIdleWorker(Object *obj);
	virtual void removeIdleWorker(Object *obj, int playerNumber);
	virtual void selectNextIdleWorker(void);
#define V(n) virtual void r##n() = 0;
	V(108) V(109) V(110) V(111)
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

void InGameUI::addIdleWorker(Object *obj)
{
	if(!obj)
		return;

	if(findIdleWorker(obj))
		return;

	m_idleWorkers[obj->getControllingPlayer()->getPlayerIndex()].push_back(obj);
}

void InGameUI::removeIdleWorker(Object *obj, int playerNumber)
{
	if(!obj || playerNumber < 0 || playerNumber >= MAX_PLAYER_COUNT)
		return;

	if(m_idleWorkers[playerNumber].empty())
		return;

	ObjectListIt it = m_idleWorkers[playerNumber].begin();
	while(it != m_idleWorkers[playerNumber].end())
	{
		if(*it == obj)
		{
			m_idleWorkers[playerNumber].erase(it);
			return;
		}
		++it;
	}
}

extern InGameUI *TheInGameUI;

void InGameUI::selectNextIdleWorker(void)
{
	int index = ThePlayerList->getLocalPlayer()->getPlayerIndex();
	if(m_idleWorkers[index].empty())
		return;
	Object *selectThisObject = 0;

	if(getSelectCount() == 0 || getSelectCount() > 1)
	{
		selectThisObject = *m_idleWorkers[index].begin();
	}
	else
	{
		Drawable *selectedDrawable = TheInGameUI->getFirstSelectedDrawable();

		ObjectListIt it = m_idleWorkers[index].begin();
		while(it != m_idleWorkers[index].end())
		{
			Object *itObj = *it;
			if(itObj == selectedDrawable->getObject())
			{
				++it;
				if(it != m_idleWorkers[index].end())
					selectThisObject = *it;
				else
					selectThisObject = *m_idleWorkers[index].begin();
				break;
			}
			++it;
		}
		// if we had something selected that wasn't a worker, we'll get here
		if(!selectThisObject)
			selectThisObject = *m_idleWorkers[index].begin();
	}
	if(selectThisObject)
	{
		// If our idle worker is contained by anything, we need to select the container instead.
		Object *containedBy = selectThisObject->getContainedBy();
		if( containedBy )
		{
			selectThisObject = containedBy;
		}

		deselectAllDrawables();
		GameMessage *teamMsg = MessageStreamSubsystem->appendMessage( GameMessage::MSG_CREATE_SELECTED_GROUP );

		// New group or add to group? Passed in value is true if we are creating a new group.
		teamMsg->appendBooleanArgument( true );

		teamMsg->appendObjectIDArgument( selectThisObject->getID() );

		selectDrawable( selectThisObject->getDrawable() );

		// center on the unit
		TheTacticalView->lookAt(selectThisObject->getPosition());
	}
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
