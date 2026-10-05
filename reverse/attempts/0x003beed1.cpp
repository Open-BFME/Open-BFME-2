// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z
// partial score=0.96 date=2026-10-05
// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z
// Retail RVA 0x003BEED1, 79 bytes.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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
// Target-layout facts from the retail bytes: iterate_TeamMemberList 0x00263864
// stores the team member list head at offset 0 of its 24-byte sret temp, and
// DLINK advance 0x00263526 rewrites that same offset 0 with its result, so the
// current object is the offset-0 member the shim names m_cur.
// Loop shape: retail rotates the loop, jumping from just after the iterator
// factory straight to the bottom test (jmp 0x003BEF15), and its test loads the
// current object into ecx and reuses that register as the setStatus this-
// pointer. Reproducing that needs the test's load to stay live into the body;
// with the iterator addressed through a pointer variable MSVC 7.1 /O1 keeps the
// exact 79-byte extent but still folds the test to a direct compare.

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

class Object;
class Team;

enum ObjectStatusTypes { OBJECT_STATUS_REPULSOR = 8 };

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

// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doTeamSetRepulsor(const AsciiString &teamName, Bool repulsor)
{
    Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName, false);
    if (!theSrcTeam) {
        return;
    }
    DLINK_ITERATOR<Object> local = theSrcTeam->iterate_TeamMemberList();
    DLINK_ITERATOR<Object> *iter = &local;
    do {
        Object *obj = iter->cur();
        obj->setStatus(OBJECT_STATUS_REPULSOR, repulsor);
        iter->advance();
    } while (iter->cur() != 0);
}