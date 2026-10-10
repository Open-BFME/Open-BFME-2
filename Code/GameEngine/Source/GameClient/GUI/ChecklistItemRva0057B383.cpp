// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0057B383@Rva0057AD26@@QAEXXZ retail 0x0057B383..0x0057B499 (278
// bytes). Removes a StrategicHUD checklist item (the Rva0057AD26 item class
// whose 0x0057AD26 body WorldBuilder names Item::DoSelect; WB twin
// 0x014BAFB0 fires the Apt call "DeleteItem"). The item is held by the
// owning holder released through 0x0057A418 at the end. When it is the
// owner's current item the owner's SetCurrentItem 0x0057AC27 moves to the
// list end and the observer (+0x54) gets slot 0 (deselect). Then the Apt
// "DeleteItem" call (Rva0052519DFire 0x0052519D with the owner's level and
// path and the item's +0x50) the following items move up by the gap
// between the next item's and this item's +0x08 position (float getter
// 0x004987FE and setter 0x005D3FE4) the node is erased from the owner's
// +0x30 list (list<int>::erase 0x00438539) the owner's +0x2C clears when
// the list empties and the scroll bar is refreshed (0x0057B16D).
#include "ascii_string.h"
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef float Real;

struct ChecklistSelectNode;
struct ChecklistIteratorView
{
	ChecklistSelectNode *node;
	ChecklistIteratorView(const ChecklistIteratorView &other) : node(other.node) {}
};

namespace StrategicHUD
{
class ChecklistUIImpl;
}

class StrategicHUD::ChecklistUIImpl
{
public:
	void SetCurrentItem(ChecklistIteratorView iterator);
	void rva0057B16D();

	char m_pad00[0x0C];
	void *m_level; // +0x0C, the movie's Apt level
	AsciiString m_path; // +0x10, the movie's path
	char m_pad14[0x2C - 0x14];
	int m_2c; // +0x2C
	_STL::list<int> items; // +0x30: item pointers
};

struct ChecklistSelectionOwnerView
{
	char prefix[0x30];
	ChecklistIteratorView end; // +0x30
	ChecklistIteratorView current; // +0x34
};

class Rva004987FEFloatField
{
public:
	Real get() const;
};

class Rva005D3FE4
{
public:
	void rva005D3FE4(Real value);
};

class Rva0057AD26;
struct ChecklistSelectObserver
{
	virtual void deselect(Rva0057AD26 *item);
};

struct ChecklistSelectNode
{
	ChecklistSelectNode *next;
	ChecklistSelectNode *prev;
	Rva0057AD26 *item;
};

// The owning holder whose end-of-scope release is the rowed 0x0057A418
// (deletes the held item).
class Rva0057A418
{
public:
	void rva0057A418();
};

struct Rva0057B383Holder
{
	Rva0057B383Holder(Rva0057AD26 *item) : m_item(item) {}
	~Rva0057B383Holder() { reinterpret_cast<Rva0057A418 *>(this)->rva0057A418(); }

	Rva0057AD26 *m_item;
};

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5);

class Rva0057AD26
{
public:
	void rva0057B383();

	char prefix[0x48];
	StrategicHUD::ChecklistUIImpl *owner; // +0x48
	ChecklistIteratorView position; // +0x4C
	int m_50; // +0x50
	ChecklistSelectObserver *observer; // +0x54
};

void Rva0057AD26::rva0057B383()
{
	Rva0057B383Holder self(this);
	ChecklistSelectionOwnerView *state = reinterpret_cast<ChecklistSelectionOwnerView *>(owner);
	if (position.node == state->current.node)
	{
		owner->SetCurrentItem(state->end);
		if (observer)
			observer->deselect(this);
	}

	if (g_bfmeAptWindowManager)
		Rva0052519DFire(g_bfmeAptWindowManager, owner->m_level, owner->m_path.str(), "DeleteItem", &m_50);

	_STL::list<int>::iterator end = owner->items.end();
	_STL::list<int>::iterator it = *reinterpret_cast<_STL::list<int>::iterator *>(&position);
	++it;
	if (it != end)
	{
		Real delta = reinterpret_cast<Rva004987FEFloatField *>((char *)*it + 8)->get()
			- reinterpret_cast<Rva004987FEFloatField *>((char *)this + 8)->get();
		for (; it != end; ++it)
		{
			char *item = (char *)*it;
			reinterpret_cast<Rva005D3FE4 *>(item + 8)->rva005D3FE4(
				reinterpret_cast<Rva004987FEFloatField *>(item + 8)->get() - delta);
		}
	}

	owner->items.erase(*reinterpret_cast<_STL::list<int>::iterator *>(&position));
	if (owner->items.empty())
		owner->m_2c = 0;
	owner->rva0057B16D();
}
