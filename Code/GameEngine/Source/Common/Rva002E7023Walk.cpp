// cl: /O1 /DNDEBUG /MD
//
// ?rva002E7023@@YAXXZ @0x002E7023 68B: global+call list walk
// (free cdecl, void). Loads TheGameLogic (global 0xDFE78C), takes the first
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

class Rva00269566Owner
{
public:
	void rva00269566();
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

class GameLogic
{
public:
	Object *getFirstObject();
};
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

// ?rva002E7023@@YAXXZ
void rva002E7023()
{
	Object *node = TheGameLogic->getFirstObject();
	if (node == 0)
		return;
	do {
		Rva00269566Owner *item = node->getItem();
		if (item != 0) {
			Rva003638BA *view = item->getView();
			if (view != 0 && view->rva00363AD7())
				item->rva00269566();
		}
		node = node->getNext();
	} while (node != 0);
}
