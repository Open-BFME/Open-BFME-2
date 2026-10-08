// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?rva0057B16D@ChecklistUIImpl@StrategicHUD@@QAEXXZ @0x0057B16D 170B
// Refreshes the scroll bar from the item list height (unrowed 0x0057ABD0)
// and the +0x3C visible height through the rowed ratio setters 0x005D4BAE
// and 0x005D4BC1 and rowed visibility 0x005D49D5. Called by rowed
// OnScrollBarLoaded 0x0057B4F9 and three unrowed callers. Class named
// StrategicHUD::ChecklistUIImpl by WorldBuilder for OnScrollBarLoaded.
#include "ascii_string.h"

// The scroll bar holder at +0x28.
class Rva000AD6F4
{
public:
	void clear();

	void *m_ptr;
};

// The scroll bar's ratio setters (rowed 0x005D4BAE/0x005D4BC1) and visibility
// (rowed SetVisible 0x005D49D5).
class Rva005D4BAE
{
public:
	void rva005D4BAE(float v);
};

class Rva005D4BC1
{
public:
	void rva005D4BC1(float v);
};

class Rva005D49CD
{
public:
	void rva005D49D5(bool v);
};

// The checklist's items: sentinel node at +0x30. Only the next link is
// read here; the item payload lives at node +8.
struct Rva0057B499Item;

struct Rva0057B499Node
{
	Rva0057B499Node *m_next;
	Rva0057B499Node *m_prev;
	Rva0057B499Item *m_item;
};

// The checklist's three vftables, stored by its constructor 0x0057B5AA:
// 0x00C6F118 at +0, 0x00C6F0FC at +4 and, at +8, the scroll bar listener's
// 0x00C6F0F4.
class Rva0057AF2EBase
{
public:
	virtual void slot00();
};

class Rva0057A83CBase
{
public:
	virtual void slot00();
};

class Rva0057AC8FScrollListener
{
public:
	virtual void slot00(int);
	virtual void rva0057AC8F(int unused, float position);
};

namespace StrategicHUD {
class ChecklistUIImpl;
}

class StrategicHUD::ChecklistUIImpl : public Rva0057AF2EBase, public Rva0057A83CBase, public Rva0057AC8FScrollListener
{
public:
	// Unrowed 0x0057B16D (170 bytes), pinned by address.
	void rva0057B16D();
	// The item list's height (unrowed 0x0057ABD0, pinned by address).
	float rva0057ABD0() const;

private:
	void *m_level; // +0x0C, the movie's Apt level
	AsciiString m_path; // +0x10, the movie's path
	int m_state; // +0x14
	unsigned char m_pad18[0x26 - 0x18];
	bool m_26; // +0x26: expand once closed
	unsigned char m_pad27;
	Rva000AD6F4 m_scrollBar; // +0x28
	unsigned char m_pad2c[0x30 - 0x2C];
	Rva0057B499Node *m_items; // +0x30
	unsigned char m_pad34[0x38 - 0x34];
	bool m_38; // +0x38: rva0057B217 pending
	unsigned char m_pad39[0x3C - 0x39];
	float m_3C; // +0x3C: visible height the scroll bar scales against
};

// Retail 0x0057B16D, 170 bytes. Name pinned by address
// (?rva0057B16D@ChecklistUIImpl@StrategicHUD@@QAEXXZ): refreshes the scroll
// bar from the item list height (unrowed 0x0057ABD0) and the +0x3C visible
// height; called by OnScrollBarLoaded and three unrowed callers.
void StrategicHUD::ChecklistUIImpl::rva0057B16D()
{
	if (m_scrollBar.m_ptr == 0)
		return;
	float total = rva0057ABD0();
	if (m_3C > total)
		total = m_3C;
	((Rva005D4BAE *)m_scrollBar.m_ptr)->rva005D4BAE(m_3C / total);
	float inv;
	if (m_items->m_next != m_items)
	{
		Rva0057B499Node *end = m_items;
		Rva0057B499Node *node = m_items->m_next;
		unsigned int count = 0;
		for (; node != end; node = node->m_next)
			++count;
		inv = 1.0f / (float)count;
	}
	else
		inv = 0.0f;
	((Rva005D4BC1 *)m_scrollBar.m_ptr)->rva005D4BC1(inv);
	((Rva005D49CD *)m_scrollBar.m_ptr)->rva005D49D5(total > m_3C);
}
