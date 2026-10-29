// cl: /O1 /EHsc /MD /DNDEBUG /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/moduledata /I. /Ireference/shims/bfmealloc
// W7-G1 r6: exact. Frame levers: BFME2's DLINK_ITERATOR is {m_cur; 4 unused bytes; member pointer} = 16 B for
// Team (24 B for Object), driven by the ZH iterate_TeamInstanceList()/done()/cur()/advance() loop shape as in the
// matched sibling onUpgradeCompleted (PlayerRva002AD93A.cpp); with that iterator the retail frame (this -10, vector -1C,
// iterator -2C, member iterator -44) follows from cl's size-ascending slot ranking. Register roles: an equal-arm on
// the prototype receiver ((science ? p : p)->iterate...) moves proto to EBX and the contained pointer to EDI.
// stlport
//
// ?addScience@Player@@AAE_NW4ScienceType@@@Z, retail 0x002AD661, 392 bytes.
// Player::addScience (private; grantScience 0x002AD85E calls it, and the pin
// names this address): false when the science is already held; otherwise it
// pushes the science to the +0x2F0 vector, walks the +0x32C team-prototype
// list granting it to every contained object whose AI lists it, flags the
// +0x28 byte of the object at TheControlBar, notifies the script engine with
// the +0x54 index, and returns true.
//
// Views: the team walk (member-function pointer 0x9C4AF5, +0x334 head) and
// the DLINK member iterator follow the matched sibling onUpgradeRemoved in
// PlayerRva002AD93A.cpp; the ScienceType find spelling follows the matched
// hasScience in PlayerHasScience.cpp; the +0x244 contained-object array, the
// +0x0C holder/AI virtuals (+0x18 provider, +0x1C grant, +0x20 int sink,
// +0x3C float sink), the +0x114/+0x40 GameLogic words and the +0x28 byte are
// retail facts whose application identities stay unresolved.
// Keep vector growth inline without a competing unused max<unsigned> body.
#include <stl/_algobase.h>
namespace _STL {
template <> __declspec(dllimport) __forceinline
const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Common/Snapshot.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL {
	// Preserve STLport's inline cleanup; suppress its unused external copy.
	template <> __declspec(dllimport) __forceinline
	_Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
	{
		if (_M_start != 0)
			_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
	}

	template <class _InputIter, class _Tp>
	_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

#include "../../../Include/Common/MemoryPoolObject.h"

class Object;
class Team;

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS *m_cur;
	void *m_unusedAbi; // BFME 2: 4 bytes between the cursor and the member pointer (iterator 16 B for Team, 24 B for Object)
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_head334, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_head334; // +0x334
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class Rva0029FCB4
{
public:
	_STL::vector<ScienceType> rva0029FCB4();
};

class Rva002AD661AI
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Rva0029FCB4 *getScienceProvider(); // +0x18
	virtual void grantScienceToObject(); // +0x1C
	virtual void setIntSink(int value); // +0x20
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void setFloatSink(float value); // +0x3C
};

class Rva002AD661Holder
{
public:
	virtual void h00();
	virtual void h04();
	virtual void h08();
	virtual void h0C();
	virtual void h10();
	virtual void h14();
	virtual void h18();
	virtual void h1C();
	virtual Rva002AD661AI *getAI(); // +0x20
};

class Object
{
public:
	char m_pad00[0x0C];
	Rva002AD661Holder m_holder0C; // +0x0C
	char m_pad10[0x244 - 0x10];
	Object **m_contained244; // +0x244
};

extern GameLogic *TheGameLogic;
// View of the two words this body reads: the frame counter at +0x40 and
// the mode word at +0x114 (both proven by the canonical header above as
// m_frame/m_114, but m_frame is private there, so this TU reads them
// through its own offset view).
struct Rva002AD661LogicView
{
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
	unsigned char m_pad44[0x114 - 0x44];
	int m_gameMode; // +0x114
};

class ScriptEngine
{
public:
	void notifyOfAcquiredScience(int playerIndex, ScienceType science);
};
extern ScriptEngine *TheScriptEngine;

class ControlBar;
extern ControlBar *TheControlBar;
class Rva002AD661ControlBarView
{
public:
	char m_pad00[0x28];
	unsigned char m_flag28; // +0x28
};

class Player
{
public:
	bool hasScience(ScienceType science) const;
private:
	bool addScience(ScienceType science);
	char m_pad00[0x54];
	int m_index54; // +0x54
	char m_pad58[0x2F0 - 0x58];
	_STL::vector<ScienceType> m_sciences2F0; // +0x2F0
	char m_pad2FC[0x32C - 0x2FC];
	PlayerTeamNode *m_teamProtos32C; // +0x32C
};

bool Player::addScience(ScienceType science)
{
	if (hasScience(science))
		return false;
	m_sciences2F0.push_back(science);
	for (PlayerTeamNode *proto = m_teamProtos32C->m_next; proto != m_teamProtos32C; proto = proto->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = (science ? proto->m_value : proto->m_value)->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (team == 0)
				continue;
			for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance())
			{
				Object **pp = it.cur()->m_contained244;
				Object *obj = *pp;
				if (obj != 0)
				{
					do
					{
						Rva002AD661AI *ai = (&obj->m_holder0C)->getAI();
						if (ai != 0)
						{
							Rva0029FCB4 *provider = ai->getScienceProvider();
							_STL::vector<ScienceType> sciences = provider->rva0029FCB4();
							if (!sciences.empty() && _STL::find(sciences.begin(), sciences.end(), science) != sciences.end())
							{
								ai->grantScienceToObject();
								if (((const Rva002AD661LogicView *)TheGameLogic)->m_gameMode != 3)
									ai->setFloatSink(1.0f);
								else
								{
									int frame = ((const Rva002AD661LogicView *)TheGameLogic)->m_frame;
									ai->setIntSink(frame);
								}
							}
						}
						++pp;
						obj = *pp;
					} while (obj != 0);
				}
			}
		}
		((Rva002AD661ControlBarView *)TheControlBar)->m_flag28 = 1;
	}
	if (TheScriptEngine != 0)
		TheScriptEngine->notifyOfAcquiredScience(m_index54, science);
	return true;
}
