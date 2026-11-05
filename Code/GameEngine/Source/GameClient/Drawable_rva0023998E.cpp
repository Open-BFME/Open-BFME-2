// cl: /DNDEBUG /MD /EHsc
// ?rva0023998E@Drawable@@QAEXH@Z @0x0023998E 93B.
// Target evidence: indexes the +0xF8 circular-list holders, brackets their
// node callbacks with TheDisplay vslots +0xD4/+0x100, then clears the holder.
// LINK: the callback owner is spelled Rva002796D9Host, as rowed at 0x002796D9 (Rva002796D9.cpp).
// Identity remains address-derived; callback owner and list semantics are inferred.

class Rva002796D9Host
{
public:
	void drawIconLayer(int slot);
};

struct Rva0023998EListNode
{
	Rva0023998EListNode *m_next;
	void *m_prev;
	Rva002796D9Host *m_callback;
};

class Rva00239380Holder
{
public:
	Rva0023998EListNode *m_head;
	void rva00239380();
};

#include "../../Include/GameClient/Display.h"

extern Display *TheDisplay;

class Drawable
{
public:
	virtual void unused();
private:
	unsigned char m_pad[0xF8 - 4];
	Rva00239380Holder m_lists[10];
public:
	void rva0023998E(int slot);
};

void Drawable::rva0023998E(int slot)
{
	if (slot < 0 || slot >= 10)
		return;
	register int slotIndex = slot;
	register Rva00239380Holder *holder = &m_lists[slotIndex];
	if (holder->m_head->m_next == holder->m_head)
		return;
	TheDisplay->slot53();
	for (register Rva0023998EListNode *node = holder->m_head->m_next;
		node != holder->m_head; node = node->m_next)
		node->m_callback->drawIconLayer(slotIndex);
	TheDisplay->slot64();
	holder->rva00239380();
}
