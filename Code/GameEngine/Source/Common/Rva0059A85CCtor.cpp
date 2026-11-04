// cl: /DBFME_ASCII_DTOR_DECL /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// Fix over the banked 0.97 attempt, from the retail unwind map: state 0
// destroys the Rva00506B1B base through its 7-byte vptr setter 0x00506B28, so
// the base declares a virtual destructor; that restores the missing state-0
// store and the state numbering of the vector (+0x08) and set (+0x18).
// stlport
// ??0Rva0059A85C@@QAE@PAX@Z @0x0059A85C (123B)
// Derived ctor calls base Rva00506B1B then vector BfmeE16 at +8 then sets
// vtable g_00C70DE4 then set AsciiString at +0x18. Stores void arg to +0x14
// then walks circular list at arg+0x32c calling rowed registerTeamPrototype on each
// node+8 value. Ret 4. Caller 0x004EC430. Evidence chain lane calls just
// landed 0x0059A71C plus EH prolog plus vector_base set rows.
#include <vector>
#include <set>
class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void v1();
	bool m_04;
};
#include "../../../Libraries/Include/Lib/BfmeE16.h"
#include "ascii_string.h"
#include "../../Include/GameLogic/Rva002EE9B7.h"
struct Arg;
class Team;
class TeamPrototype;
struct Coord3D;
class Object;
struct AITeamRequirementView;
struct AITargetView;
class Player;
class AITeamBuilder
{
public:
	void recruitPreDefined(Team*,int*,TeamPrototype*);
	bool defineUnitsNormal_old(TeamPrototype*);
	void recruitUnDefined(Team*,int*);
	void distanceSortUnits(void*,const void*,const Coord3D*);
	void registerTeamPrototype(Arg *);
	int getCurNumUnits(Team *);
	int doesTeamMeetThreat(Team *);
	bool rva0059A01C(Object*,const AITeamRequirementView*,const AITargetView*);
	void checkIdleTeams();
	void update();
	void rva0059ABC9(void *);
	void rva0059AC4D(void *);
	Team *rva00599F74(TeamPrototype *);
	void rva0059A153(TeamPrototype *);
	char prefix[8]; // +0x00
	_STL::vector<TeamPrototype *> prototypes; // +0x08
	Player * owner14; // +0x14
	_STL::set<int> busy; // +0x18
};
struct Rva0059A85CNode
{
	Rva0059A85CNode *m_next;
	char m_pad[4];
	Arg *m_val;
};
struct Rva0059A85COuter
{
	char m_pad[0x32c];
	Rva0059A85CNode *m_head;
};
// The set at +0x18 is the shared Rva002EE9B7 tree (ctor 0x000D3A71, dtor
// 0x002F0B52), the view AITeamBuilder.cpp's destructor uses.
class Rva0059A85C : public Rva00506B1B
{
public:
	Rva0059A85C(void *outer);
	virtual ~Rva0059A85C();	// rowed in AITeamBuilder.cpp; declared so this unit binds to it
	virtual void v1();	// retail slot 2 (0x0059A46F, rowed in AITeamBuilder.cpp)
private:
	_STL::vector<BfmeE16> m_vec;
	void *m_outer;
	Rva002EE9B7 m_set;
};
// ??0Rva0059A85C@@QAE@PAX@Z @0x0059A85C
Rva0059A85C::Rva0059A85C(void *outer) : m_vec(), m_outer(outer), m_set()
{
	Rva0059A85CNode *sent = ((Rva0059A85COuter *)m_outer)->m_head;
	Rva0059A85CNode *cur = *(Rva0059A85CNode **)sent;
	if (cur == sent)
		return;
	do {
		((AITeamBuilder *)this)->registerTeamPrototype(cur->m_val);
		cur = cur->m_next;
	} while (cur != ((Rva0059A85COuter *)m_outer)->m_head);
}
