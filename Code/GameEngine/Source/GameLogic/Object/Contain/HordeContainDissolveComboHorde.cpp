// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G6
// stlport
//
// HordeContain::dissolveComboHordeIfNeeded, retail 0x0046AD8B (391 bytes).
// The name and the WorldBuilder twin come from the WB debug build (its assert
// text names the function); layouts are retail evidence:
// - The interface at +0x11C (vtable installed by the HordeContain ctor
//   0x0046F543): slot 67 (+0x10C) fills a member list, slot 126 (+0x1F8) takes
//   a vector<int> by reference, slot 127 (+0x1FC) is a bool query.
// - The contained-list descriptor 0x0046247D returns Rva0036AE51ListView by
//   value; WB clears a conditional-temporary cleanup flag at entry and tests it
//   after the condition. Retail keeps only the entry clear ([ebp-0x14] = 0):
//   the view's destructor is empty in release (ContainmentListView.h).
// - Object +0x264 and its +0x24 int are read through by-value getters (WB keeps
//   both results in temporaries; retail loads them into ebx).
// - Object +0x04 template, ThingTemplate +0x114 kind-of bits (kind 68).
// /G6: the member count loop uses inc, not /G7's add.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Include/GameLogic/ContainmentListView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include <list>
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper
// (retail keeps one _List_iterator_base::operator!=; BfmeAptScreenLanLobbyOnInitGadget.cpp pattern).
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>
#include <vector>

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum EvaEventID
{
	EVA_EVENT_NONE = 0
};

#include "../../../../Include/Common/ThingTemplate.h"

struct Rva00469689Body
{
	unsigned char m_pad00[0x24];
	int m_currentLevel; // +0x24
	int getLevel24() const { return m_currentLevel; }
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	const Coord3D *getPosition() const { return &m_position; }
	const Rva00469689Body *getBody264() const { return m_264; }
	__forceinline unsigned int templateKindOfBits(int kind) const
	{
		return (m_template->m_kindof + 3)[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x264 - 0x44];
	const Rva00469689Body *m_264; // +0x264
};

#include "../../../../Include/GameClient/Eva.h"
extern Eva *TheEva;
extern GameLogic *TheGameLogic;

class Rva0046247DDescriptor
{
public:
	Rva0036AE51ListView rva0046247D();
};

// Vtable padding: Pad<B, N> appends N pure virtual slots to B.
template <class B, int N> class Rva0046AD8BPad : public Rva0046AD8BPad<B, N - 1>
{
public:
	virtual void pad(B *, char (*)[N]) = 0;
};
template <class B> class Rva0046AD8BPad<B, 0> : public B
{
};
class Rva0046AD8BNoSlots
{
};
class HordeContainIface67 : public Rva0046AD8BPad<Rva0046AD8BNoSlots, 67>
{
public:
	virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; // slot 67
};
class HordeContainIface11C : public Rva0046AD8BPad<HordeContainIface67, 126 - 68>
{
public:
	virtual void slot126(const _STL::vector<int> &v) = 0; // slot 126
	virtual bool rva004698BC() = 0; // slot 127
};

struct HordeContainModuleDataFields
{
	unsigned char m_pad000[0x248];
	int m_248; // +0x248 (Eva event)
	unsigned char m_pad24C[0x250 - 0x24C];
	int m_250; // +0x250 (member count threshold)
};

class HordeContainBase
{
public:
	virtual ~HordeContainBase();
protected:
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad00C[0x11C - 0x0C];
};

class HordeContain : public HordeContainBase, public HordeContainIface11C
{
public:
	bool dissolveComboHordeIfNeeded();
private:
	const HordeContainModuleDataFields *fields() const { return (const HordeContainModuleDataFields *)m_moduleData; }
	unsigned char m_pad120[0x170 - 0x120];
	_STL::set<int> m_170; // +0x170 (Object IDs)
};

bool HordeContain::dissolveComboHordeIfNeeded()
{
	bool dissolved = false;
	Object *obj = m_object;
	if (!obj->testStatus((ObjectStatusTypes)2)
		&& ((Rva0046247DDescriptor *)(HordeContainBase *)this)->rva0046247D().b->empty()
		&& m_170.empty())
	{
		TheEva->reportEvaEvent((EvaEventID)fields()->m_248, obj->getPosition(), 0);
		TheGameLogic->destroyObject(obj);
	}
	else if (rva004698BC() && obj->getBody264()->getLevel24() <= 1)
	{
		_STL::list<const Object *> members;
		rva0046D1F7(members);
		unsigned int count = members.size();
		if (0 < fields()->m_250)
		{
			if (count <= (unsigned int)fields()->m_250)
			{
				_STL::vector<int> none;
				slot126(none);
				dissolved = true;
			}
		}
		else if (count > 0)
		{
			bool same = true;
			const ThingTemplate *first = 0;
			for (_STL::list<const Object *>::iterator it = members.begin(); it != members.end(); ++it)
			{
				const Object *member = *it;
				if (member == 0)
					continue;
				if (member->templateKindOfBits(68))
					continue;
				const ThingTemplate *thingTemplate = member->m_template;
				if (!first)
					first = thingTemplate;
				else if (thingTemplate && !first->isEquivalentTo(thingTemplate))
				{
					same = false;
					break;
				}
			}
			if (same)
			{
				_STL::vector<int> none;
				slot126(none);
				dissolved = true;
			}
		}
	}
	return dissolved;

	// Dead; keeps the EH shape of the WB debug-macro path (without it cl
	// duplicates the vector tail and grows the frame to 0x20).
	if (0) throw 1;
}
