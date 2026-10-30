// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::ChecklistUIImpl (WorldBuilder StrategicHUDChecklistUIImpl.cpp).
//
// Item::Item, retail 0x0057A748 134B (ret 0x14): WB 0x014BAB40 names it
// (assert line 333, *m_listPos == NULL). Target facts: the primary base is
// the rowed 13-byte ctor 0x005D1A6C (vptr plus a zeroed +4); the second base
// at +8 is the ChecklistUIItemMovieClip, constructed by 0x005D4433 (WB
// 0x015A67C0) from the item's last two arguments and the static font
// descriptor at 0x00E06368 (+8 inside g_Va00E06360). Retail's unwind map
// destroys the two bases through 0x0057A23C (state 0) and the movie clip's
// rowed destructor 0x005D40A6 on this+8 (state 1). Own vftables 0x00C6EF0C
// (+0) and 0x00C6EEF8 (+8). Fields: +0x48 owner, +0x4C the list position
// whose node's +8 is set to the item, +0x50 the third argument, +0x54/+0x58
// cleared, +0x5C set. Finally the movie clip's 0x005D3FBD(false) and the
// item's 0x0057A382 run. The field layout agrees with Rva0057AD26 in
// AptWotrPanelCallbacks.cpp (owner +0x48, position +0x4C, observer +0x54).
// Argument types beyond the WB-visible roles stay opaque.
#include "ascii_string.h"

namespace StrategicHUD
{
class ChecklistUIImpl
{
public:
	class Item;
	ChecklistUIImpl(int level, const AsciiString &name);
	virtual ~ChecklistUIImpl();
	void Update();

private:
	unsigned char m_pad004[0x50 - 4];
};
}

struct ChecklistSelectNode
{
	ChecklistSelectNode *next;
	ChecklistSelectNode *prev;
	StrategicHUD::ChecklistUIImpl::Item *item;
};

struct ChecklistIteratorView
{
	ChecklistSelectNode *node;
	ChecklistIteratorView(const ChecklistIteratorView &other) : node(other.node) {}
};

struct ChecklistFontDesc;

extern unsigned g_Va00E06360;

class Rva005D1A6C
{
public:
	Rva005D1A6C();
	virtual ~Rva005D1A6C() {}

private:
	int m_04;
};

class Rva005D40A6
{
public:
	// The rowed constructor 0x005D4433 (Rva005D40A6Dtor.cpp).
	Rva005D40A6(int level, const AsciiString &name, const ChecklistFontDesc &fontDesc);
	virtual ~Rva005D40A6();

private:
	char m_pad04[0x40 - 0x04];
};

class Rva005D3FBD
{
public:
	void rva005D3FBD(bool v);
};

class Rva0057A382
{
public:
	void rva0057A382();
};

struct ItemObserver
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void onItemDestroyed(void *item);
};

namespace StrategicHUD
{
class ChecklistUIImpl::Item : public Rva005D1A6C, public Rva005D40A6
{
public:
	Item(ChecklistUIImpl *owner, ChecklistIteratorView position, int value, void *level,
		const AsciiString &path);
	// Retail 0x0057A2B0 (rowed under the Rva0057A2B0 view): its vptr stores
	// are this constructor's 0x00C6EF0C/0x00C6EEF8.
	virtual ~Item()
	{
		if (m_observer != 0)
			static_cast<ItemObserver *>(m_observer)->onItemDestroyed(this);
	}

private:
	ChecklistUIImpl *m_owner; // +0x48
	ChecklistIteratorView m_listPos; // +0x4C
	int m_value; // +0x50
	void *m_observer; // +0x54
	int m_58;
	bool m_5c;
};
}

StrategicHUD::ChecklistUIImpl::Item::Item(ChecklistUIImpl *owner, ChecklistIteratorView position,
	int value, void *level, const AsciiString &path)
	: Rva005D40A6((int)level, path,
		*reinterpret_cast<const ChecklistFontDesc *>(reinterpret_cast<char *>(&g_Va00E06360) + 8)),
	  m_owner(owner), m_listPos(position), m_value(value), m_observer(0), m_58(0), m_5c(true)
{
	m_listPos.node->item = this;
	reinterpret_cast<Rva005D3FBD *>(static_cast<Rva005D40A6 *>(this))->rva005D3FBD(false);
	reinterpret_cast<Rva0057A382 *>(this)->rva0057A382();
}

// The height query 0x0057ABD0 and spacing 0x0057A24A live with their other
// caller DoCreateNewItem in StrategicHUDChecklistUIImplConstructor.cpp.
