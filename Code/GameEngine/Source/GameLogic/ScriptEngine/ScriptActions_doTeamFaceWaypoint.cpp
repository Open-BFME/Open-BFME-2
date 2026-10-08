// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target identity: action-template index 0x136 is TEAM_FACE_WAYPOINT and
// executeAction case 0x136 calls VA 0x007C9B19 (RVA 0x003C9B19), 148 bytes.
// Target body resolves the team and named waypoint, obtains the team member
// iterator, then clears each member's waypoint queue, leaves its group and
// calls aiFacePosition with Waypoint+0x0C and source 1. BFME1 donor establishes
// the action semantics and linked-list traversal; target iterator ABI is
// represented with an opaque 24-byte local matching the helper at 0x263864.

#include "ascii_string.h"
typedef bool Bool;
class Object;
class AIUpdateInterface;
struct Coord3D { float x, y, z; };
enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};
class Waypoint
{
public:
    const Coord3D *location() const
    {
        return (const Coord3D *)((const char *)this + 0x0c);
    }
};
template<class OBJCLASS> class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    Bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};

class Object
{
public:
    void leaveGroup();
    AIUpdateInterface *getAIUpdateInterface() const
    {
        return *(AIUpdateInterface **)((const char *)this + 0x258);
    }
};

class AICommandInterface
{
public: void aiFacePosition(const Coord3D *, int);
	void rva003C76B8(int value, CommandSourceType cmdSource);
};
class AIUpdateInterface
{
public:
    unsigned char pad[0x20];
    AICommandInterface command;
    void clearWaypointQueue();
};
class Team
{
    void *m_vptr;
    void *m_prototype;
    void *m_id;
    Object *m_head;
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, Bool);
};
class TerrainLogicByValue
{
public:
    virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
    virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
    virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
    virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
    virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
    virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
    virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
    virtual void _28()=0; virtual void _29()=0; virtual void _30()=0; virtual void _31()=0;
    virtual void _32()=0; virtual void _33()=0;
    virtual Waypoint *getWaypointByName(const AsciiString &) = 0;
};
class ScriptActions
{
protected:
    void doTeamFaceWaypoint(const AsciiString &, const AsciiString &);
    void rva003C9BAD(const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

void ScriptActions::doTeamFaceWaypoint(const AsciiString &teamName,
    const AsciiString &waypointName)
{
    Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
    if (!team) return;
    Waypoint *waypoint = TheTerrainLogic->getWaypointByName(waypointName);
    if (!waypoint) return;
    DLINK_ITERATOR<Object> iter;
    iter = team->iterate_TeamMemberList();
    while (!iter.done()) {
        Object *object = iter.cur();
        AIUpdateInterface *ai = object->getAIUpdateInterface();
        if (ai) {
            ai->clearWaypointQueue();
            object->leaveGroup();
            ai->command.aiFacePosition(waypoint->location(), 1);
        }
        iter.advance();
    }
}

// ?rva003C9BAD@ScriptActions@@IAEXABVAsciiString@@@Z @0x003C9BAD 93B
// Evidence: gap 0x003C9B19+148=0x003C9BAD in this TU; team lookup plus per-member rva003C76B8 with 0 plus 1.
// Chain via landed 0x003C76B8; caller at 0x003CDA49.
void ScriptActions::rva003C9BAD(const AsciiString &teamName)
{
    Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
    if (!team) return;
    DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
    while (!iter.done()) {
        Object *object = iter.cur();
        AIUpdateInterface *ai = object->getAIUpdateInterface();
        if (ai) {
            ai->command.rva003C76B8(0, CMD_FROM_SCRIPT);
        }
        iter.advance();
    }
}

// ?TheTerrainLogic@@3PAVTerrainLogicByValue@@A: the global at this VA is ?TheTerrainLogic@@3PAVTerrainLogic@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?TheTerrainLogic@@3PAVTerrainLogicByValue@@A=?TheTerrainLogic@@3PAVTerrainLogic@@A")
#pragma comment(linker, "/alternatename:?TheTerrainLogic@@3PAVBfmeTerrainHeightView@@A=?TheTerrainLogic@@3PAVTerrainLogic@@A")
#pragma comment(linker, "/alternatename:?TheTerrainLogic@@3PAUTerrainLogicMirror@@A=?TheTerrainLogic@@3PAVTerrainLogic@@A")
// ?TheTerrainLogic@@3PAVTerrainLogicByValue@@A: the global at VA 0xdfec50 is ?TheTerrainLogic@@3PAVTerrainLogic@@A.
#pragma comment(linker, "/alternatename:?TheTerrainLogic@@3PAVTerrainLogicByValue@@A=?TheTerrainLogic@@3PAVTerrainLogic@@A")
