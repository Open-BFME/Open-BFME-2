// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AIGroup::groupEnter (?groupEnter@AIGroup@@QAEXPAVObject@@W4CommandSourceType@@@Z),
// retail 0x00370198, 127 bytes.
// Pinned name; caller is ScriptActions::doTeamEnterNamed at 0x003BEF8D which
// builds an AIGroup from the named team and calls this with the destination
// Object and command source 1. Donor is ZH GeneralsMD AIGroup.cpp:2384
// AIGroup::groupEnter iterating m_memberList and calling aiEnter, plus BFME1
// AIGroup_groupEnter.cpp which snapshots the STLport list first because
// aiEnter can unlink members. BFME2 layout is Object+0x258 AIUpdate plus
// +0x20 command subobject (pinned Rva0026C347Command at 0x0026C347) plus
// AIGroup+0x04 STLport list<int> holding Object* as int (head at +0x04
// matches retail [edi+4] loads; int instantiation gives rowed List_base
// ctor 0x004EC36C plus push_back 0x0005548F plus base dtor 0x004EC395).
// Flags need bfmelist/bfmealloc shims for base-dtor call plus /EHs for
// or -1 state (GameWindowManager_registerTabList precedent).
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Object;

class AICommandInterface
{
public:
	void rva0026C347(Object *target, CommandSourceType source);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	void groupEnter(Object *obj, CommandSourceType cmdSource);

private:
	char m_pad00[0x04];
	_STL::list<int> m_memberList;
};

void AIGroup::groupEnter(Object *obj, CommandSourceType cmdSource)
{
	_STL::list<int> snapshot;
	for (_STL::list<int>::iterator src = m_memberList.begin(); src != m_memberList.end(); ++src) {
		snapshot.push_back(*src);
	}
	for (_STL::list<int>::iterator it = snapshot.begin(); it != snapshot.end(); ++it) {
		Object *member = (Object *)(*it);
		AIUpdateInterface *ai = member->m_ai;
		if (ai) {
			ai->m_commands.rva0026C347(obj, cmdSource);
		}
	}
}
