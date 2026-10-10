// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva005254C5@Rva005254C5@@QAEXH@Z, retail 0x005254C5..0x0052557E (185
// bytes, ret 4; the int argument is unused). Reached only through the rowed
// forwarder 0x005259B1 on its +0x08 member. WorldBuilder places the twin in
// InGameHeroSelectInterface.cpp (assert heroID != INVALID_ID at line 555).
//
// The member holds the hero select data at +0x00 and the current slot index
// at +0x04; the 0x18-byte slots start at +0x48 of the data. When the current
// slot's flag (+0x16) is set it looks up the "NonCommand_SelectNearestBuilder"
// command button (a function-local static AsciiString) on TheControlBar and,
// if found, runs it through the rowed 0x00405DBC. Otherwise, when the slot's
// STLport list iterator (+0x00) is not end() of the list at +0x10 of the object at
// data+0x10, it shows the hero (iterator value +0x08) through the message
// temporary of vftable 0x00BFD010 (the Rva004E7392 copy ctor's class, fields
// +4/+8, as in 0x00529F3D) passed to the pinned ControlBar::bfmeShowDN
// 0x00405C04. findCommandButton 0x0031BE3C is rowed.

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

typedef int Int;

class CommandButton;
class GameWindow;
struct BfmeMsgDN;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void rva004C1B60(GameWindow *window, void *button);
	void bfmeShowDN(BfmeMsgDN *msg);
};

extern ControlBar *TheControlBar;

struct Rva004E7392
{
	Rva004E7392(int a, int b)
	{
		m_04 = a;
		m_08 = b;
	}
	virtual ~Rva004E7392() {}
	int m_04;
	int m_08;
};

struct Rva005254C5HeroEntry
{
	Int m_heroID; // node +0x08
};

typedef _STL::list<Rva005254C5HeroEntry> Rva005254C5HeroList;

struct Rva005254C5HeroOwner
{
	unsigned char m_pad00[0x10];
	Rva005254C5HeroList m_heroes; // +0x10
};

struct Rva005254C5Slot
{
	Rva005254C5HeroList::iterator m_hero; // +0x00
	unsigned char m_pad04[0x16 - 0x04];
	bool m_selectBuilder; // +0x16
	unsigned char m_pad17;
};

struct Rva005254C5Data
{
	unsigned char m_pad00[0x10];
	Rva005254C5HeroOwner *m_owner; // +0x10
	unsigned char m_pad14[0x48 - 0x14];
	Rva005254C5Slot m_slots[1]; // +0x48
};

class Rva005254C5
{
public:
	void rva005254C5(Int unused);

private:
	Rva005254C5Data *m_data; // +0x00
	Int m_current; // +0x04
};

void Rva005254C5::rva005254C5(Int unused)
{
	Rva005254C5Slot *slot = &m_data->m_slots[m_current];
	if (slot->m_selectBuilder) {
		static AsciiString s_buttonName("NonCommand_SelectNearestBuilder");
		const CommandButton *button = TheControlBar->findCommandButton(s_buttonName);
		if (button)
			TheControlBar->rva004C1B60(0, (void *)button);
	} else if (slot->m_hero != m_data->m_owner->m_heroes.end()) {
		Rva004E7392 msg((*slot->m_hero).m_heroID, 0);
		TheControlBar->bfmeShowDN(reinterpret_cast<BfmeMsgDN *>(&msg));
	}
}
