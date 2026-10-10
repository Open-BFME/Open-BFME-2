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
struct ChecklistHeightNode;
class ChecklistUIImpl
{
public:
	class Item;
	float rva0057ABD0() const;
	char prefix[0x30];
	ChecklistHeightNode *items;
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

struct Rva005D4433FontDesc;

extern unsigned g_Va00E06360;

class Rva005D1A6C
{
public:
	Rva005D1A6C();
	virtual ~Rva005D1A6C();

private:
	int m_04;
};

class Rva005D40A6
{
public:
	Rva005D40A6(void *level, const AsciiString &path, const Rva005D4433FontDesc *font);
	virtual ~Rva005D40A6();

private:
	char m_pad04[0x40 - 0x04];
};

class Rva005D3FBD
{
public:
	void rva005D3FBD(bool value);
};

class Rva0057A382
{
public:
	void rva0057A382();
};

class StrategicHUD::ChecklistUIImpl::Item : public Rva005D1A6C, public Rva005D40A6
{
public:
	Item(ChecklistUIImpl *owner, ChecklistIteratorView position, int value, void *level,
		const AsciiString &path);
	virtual ~Item();

private:
	ChecklistUIImpl *m_owner; // +0x48
	ChecklistIteratorView m_listPos; // +0x4C
	int m_value; // +0x50
	void *m_observer; // +0x54
	int m_58;
	bool m_5c;
};

StrategicHUD::ChecklistUIImpl::Item::Item(ChecklistUIImpl *owner, ChecklistIteratorView position,
	int value, void *level, const AsciiString &path)
	: Rva005D40A6(level, path,
		reinterpret_cast<const Rva005D4433FontDesc *>(reinterpret_cast<char *>(&g_Va00E06360) + 8)),
	  m_owner(owner), m_listPos(position), m_value(value), m_observer(0), m_58(0), m_5c(true)
{
	m_listPos.node->item = this;
	reinterpret_cast<Rva005D3FBD *>(static_cast<Rva005D40A6 *>(this))->rva005D3FBD(false);
	reinterpret_cast<Rva0057A382 *>(this)->rva0057A382();
}

// Native57ABD0..57AC0C RET0: unnamed height query. Last item top38 and
// +8 clip height plus shared spacing; empty list returns shared spacing.
// The owned spacing getter remains a real noinline call; visibility closes
// x87 spill scheduling and its emitted22 bytes independently match57A24A.
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct RetObj
{
	char m_pad[4];
	float m_4;
};
struct GlobalObj
{
	virtual ~GlobalObj() {}
	virtual void *d1(); virtual void *d2(); virtual void *d3(); virtual void *d4();
	virtual void *d5(); virtual void *d6(); virtual void *d7(); virtual void *d8();
	virtual void *d9(); virtual void *d10(); virtual void *d11(); virtual void *d12();
	virtual void *d13(); virtual void *d14();
	virtual RetObj *slot15();
};
#define TheGlobal0057A24A (*(GlobalObj **)&g_bfmeAptWindowManager)
class Rva0057A24A
{
public:
	__declspec(noinline) float rva0057A24A() const;
private:
	char m_pad[0x20];
	float m_20;
};

float Rva0057A24A::rva0057A24A() const { return TheGlobal0057A24A->slot15()->m_4 * m_20; }

class Rva004987FEFloatField {public: float get() const;};
namespace StrategicHUD {
struct ChecklistHeightItem {char prefix[0x38];float top;};
struct ChecklistHeightNode {ChecklistHeightNode *next,*prev;ChecklistHeightItem *item;};
}
float StrategicHUD::ChecklistUIImpl::rva0057ABD0() const
{
 if(items->next!=items) {
  ChecklistHeightItem *last=items->prev->item;
  float top=last->top;
  return reinterpret_cast<Rva004987FEFloatField*>(reinterpret_cast<char*>(last)+8)->get()
    + reinterpret_cast<Rva0057A24A*>(&g_Va00E06360)->rva0057A24A() + top;
 }
 return reinterpret_cast<Rva0057A24A*>(&g_Va00E06360)->rva0057A24A();
}
