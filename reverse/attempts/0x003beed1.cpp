// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z
// partial score=0.9 date=2026-10-05
// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptActions::doTeamSetRepulsor, retail 0x003BEED1, 79 bytes.
// Target identity: initActionTemplates names action index 0xEC (236)
// TEAM_SET_REPULSOR; executeAction's case 0xEC calls VA 0x007BEED1.
// Target body: copies the team name onto the stack, calls the matched
// getTeamNamed at 0x003584E9 with it by value (copy ctor 0x000365F0 plus the
// unwind store for the destructor-scoped temporary), obtains the 24-byte
// member iterator through the matched 0x00263864, sets status 8
// (OBJECT_STATUS_REPULSOR) on the current object via 0x0023DB0E, advances via
// the matched 0x00263526, and repeats until cur() is null.
// Donor facts: BFME1 ScriptActions.cpp maps this action to doTeamSetRepulsor
// and iterates Team::iterate_TeamMemberList() to set OBJECT_STATUS_REPULSOR.
// The iteration idiom and the iterator shape are taken from the matched
// doTeamGuard body in ScriptActions_doUnitGuardForFramecount.cpp.
// Remaining delta: retail encodes the bottom test as
//   mov ecx,[ebp-0x1c] ; test ecx,ecx ; jne
// where MSVC 7.1 /O1 folds the same loop to
//   cmp dword ptr [ebp-0x1c],0 ; jne
// Every other instruction in the 79-byte body is byte-identical.

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

class Object;
class Team;

enum ObjectStatusTypes { OBJECT_STATUS_REPULSOR = 8 };

// The 24-byte DLINK_ITERATOR<Object> (head plus the 3-part virtual-inheritance
// member pointer) that Team::iterate_TeamMemberList returns at 0x00263864.
template<class OBJ> class DLINK_ITERATOR
{
public:
    void advance();                  // 0x00263526
    bool done() const { return m_cur == 0; }
    OBJ *cur() const { return m_cur; }
private:
    OBJ *m_cur;
    char m_pad[20];
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString name, Bool exact);  // 0x003584E9
};
extern ScriptEngine *TheScriptEngine;

class Object
{
public:
    void setStatus(ObjectStatusTypes bit, Bool set);  // 0x0023DB0E
};

class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;  // 0x00263864
};

class ScriptActions
{
protected:
    void doTeamSetRepulsor(const AsciiString &, Bool);
};

void ScriptActions::doTeamSetRepulsor(const AsciiString &teamName, Bool repulsor)
{
    Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName, false);
    if (!theSrcTeam) {
        return;
    }
    for (DLINK_ITERATOR<Object> iter = theSrcTeam->iterate_TeamMemberList();
         iter.cur(); iter.advance()) {
        iter.cur()->setStatus(OBJECT_STATUS_REPULSOR, repulsor);
    }
}