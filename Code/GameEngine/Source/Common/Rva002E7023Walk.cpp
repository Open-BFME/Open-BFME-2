// cl: /O1 /DNDEBUG /MD
//
// ?rva002E7023@Rva004618D4Caller@@QAEXXZ @0x002E7023 68B: global+call list
// walk. Every caller (MineshaftPortalBehaviour, FakePathfindPortalBehaviour,
// DynamicPortalBehaviour) reaches it as a thiscall member on the AI's
// pathfinder pointer; the body never reads this, so the member spelling
// compiles to the same bytes as the earlier free-function view. Loads TheGameLogic (global 0xDFE78C), takes the first
// object via rowed getFirstObject 0x0023CAD2, walks the +0x8C chain; for each
// node with a +0x258 item whose +0x140 view passes rowed 0x00363AD7, invokes
// pinned 0x00269566 on the item. Honest address-derived name; host/type
// identities unproven beyond the call shapes.

class Object;
class Rva003638BA
{
public:
	bool rva00363AD7();
};

// 0x00269566 is rowed as AIUpdateInterface::NotifyPathHasInvalidPortals.
#include "../../Include/GameLogic/Module/AIUpdate.h"

class Rva00269566Owner
{
public:
private:
	char m_pad00[0x140];
	Rva003638BA *m_p140; // +0x140
public:
	Rva003638BA *getView() { return m_p140; }
};

class Object
{
public:
	Object *getNext() { return m_next; }
	Rva00269566Owner *getItem() { return m_p258; }
private:
	char m_pad00[0x8C];
	Object *m_next; // +0x8C
	char m_pad90[0x258 - 0x90];
	Rva00269566Owner *m_p258; // +0x258
};

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

#include "../../Include/Common/Rva004618D4Caller.h"

// ?rva002E7023@Rva004618D4Caller@@QAEXXZ
void Rva004618D4Caller::rva002E7023()
{
	Object *node = TheGameLogic->getFirstObject();
	if (node == 0)
		return;
	do {
		Rva00269566Owner *item = node->getItem();
		if (item != 0) {
			Rva003638BA *view = item->getView();
			if (view != 0 && view->rva00363AD7())
				((AIUpdateInterface *)item)->NotifyPathHasInvalidPortals();
		}
		node = node->getNext();
	} while (node != 0);
}
