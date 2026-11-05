// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// InGameUI removeIdleWorker, guided by the Zero Hour method.
// Native29F77E..29F7C8 supplies bounds, layout, full RET8 boundary and
// iterator ABI. The pool-specific36B helper29DFC5 is independently
// recovered with an honest address-derived member name; this is not the
// differently allocated Object-list erase body438539.
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

#include "../../Include/GameClient/Bfme2GameWindow.h"

void GadgetButtonSetText(GameWindow *g, UnicodeString text);

enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

enum ObjectID { INVALID_ID = 0 };

class Drawable;

#include "../Common/Thing/thing.h"

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

#include "../../Include/GameClient/Drawable.h"

#include "../../Include/Common/MessageStream.h"


extern MessageStream *TheMessageStream;

#include "../../Include/GameClient/View.h"

extern View *TheTacticalView;

typedef _STL::list<Object *> ObjectList;
typedef _STL::list<Object *>::iterator ObjectListIt;

enum { MAX_PLAYER_COUNT = 20 };

#include "../../Include/GameClient/InGameUI.h"

class Rva0029DFC5List { public: ObjectListIt rva0029DFC5(ObjectListIt); };
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
			reinterpret_cast<Rva0029DFC5List*>(&m_idleWorkers[playerNumber])->rva0029DFC5(it);
			return;
		}
		++it;
	}
}

int InGameUI::getIdleWorkerCount(void)
{
	return m_idleWorkers[ThePlayerList->getLocalPlayer()->getPlayerIndex()].size();
}


