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
// addIdleWorker (0x002A3D98, slot +0x1A4) is ZH's: findIdleWorker +0x1C4
// guards a push_back (0x001EC03C) onto the controlling player's list.
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
#include "../Common/Thing/thing.h"
#include <list>

class Object;
// Native Object-pointer nodes use the dedicated freelist provider.
namespace _STL {
template <> _List_node<Object *> *list<Object *, allocator<Object *> >::_M_create_node(Object *const &);
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/GameClient/Bfme2GameWindow.h"

void GadgetButtonSetText(GameWindow *g, UnicodeString text);

enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

#include "../../Include/Common/Player.h"

class PlayerList
{
public:
	// Local implementation name keeps this +0x10 view out of unrelated COMDAT copies.
	Player *idleWorkerLocalPlayer() { return m_local; }
private:
	char m_unknown00[0x10];
	Player *m_local;
};

extern PlayerList *ThePlayerList;

enum ObjectID { INVALID_ID = 0 };

class Drawable;

#include "../../Include/GameClient/Drawable.h"

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	// Retail callers inline this +0x274 load; no external copy is needed.
	__declspec(dllimport) __forceinline Object *getContainedBy() { return m_containedBy; }
private:
	char m_unknown44[0x74 - 0x60];
	ObjectID m_id;
	char m_unknown78[0x274 - 0x78];
	Object *m_containedBy;
};


#include "../../Include/Common/MessageStream.h"


extern class MessageStream *TheMessageStream;

#include "../../Include/GameClient/View.h"

extern View *TheTacticalView;

typedef _STL::list<Object *> ObjectList;
typedef _STL::list<Object *>::iterator ObjectListIt;

enum { MAX_PLAYER_COUNT = 20 };

#include "../../Include/GameClient/InGameUI.h"

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

extern InGameUI *TheInGameUI;

void InGameUI::selectNextIdleWorker(void)
{
	int index = ThePlayerList->idleWorkerLocalPlayer()->getPlayerIndex();
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
		GameMessage *teamMsg = TheMessageStream->appendMessage( GameMessage::MSG_CREATE_SELECTED_GROUP );

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

	m_97C = getIdleWorkerCount();
}

void InGameUI::hideIdleWorkerLayout(void)
{
	if(!m_idleWorkerWin)
		return;
	GadgetButtonSetText(m_idleWorkerWin, UnicodeString::TheEmptyString);
	m_idleWorkerWin->winEnable(false);
	m_97C = -1;
}

void InGameUI::updateIdleWorker(void)
{
	int idleCount = getIdleWorkerCount();

	if(idleCount > 0 && m_97C != idleCount && getInputEnabled())
		showIdleWorkerLayout();

	if((idleCount <= 0 && m_idleWorkerWin) || !getInputEnabled())
		hideIdleWorkerLayout();
}

// ?IdleWorkerSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// retail 0x0029B0A9, 137 bytes; the function lexicon binds it to the name
// "IdleWorkerSystem". Zero Hour's InGameUI.cpp body unchanged: input focus
// is declined and falls through to the button check, whose static key is
// "IdleWorker.wnd:ButtonSelectNextIdleWorker"; selectNextIdleWorker is the
// rowed slot 107 above.
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
typedef bool Bool;
enum { GWM_INPUT_FOCUS = 0x17, GBM_SELECTED = 0x4008 };
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

WindowMsgHandledType IdleWorkerSystem( GameWindow *window, UnsignedInt msg,
																				WindowMsgData mData1, WindowMsgData mData2 )
{
	switch( msg )
	{
		//---------------------------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
		{
			// if we're givin the opportunity to take the keyboard focus we must say we don't want it
			if( mData1 == true )
				*(Bool *)mData2 = false;
		}
		//---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			static NameKeyType buttonSelectID = NAMEKEY( "IdleWorker.wnd:ButtonSelectNextIdleWorker" );
			if (control && control->winGetWindowId() == buttonSelectID)
			{
				TheInGameUI->selectNextIdleWorker( );
			}
			break;

		}  // end button selected

		//---------------------------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}
