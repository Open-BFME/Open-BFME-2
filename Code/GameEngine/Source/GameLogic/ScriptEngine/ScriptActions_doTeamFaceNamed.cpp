// ?doTeamFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target identity: action-template index 0x135 is TEAM_FACE_NAMED and
// executeAction case 0x135 calls VA 0x007C9A80 (RVA 0x003C9A80), 153 bytes.
// Target body resolves the team, resolves the face target through the opaque
// by-value ScriptEngine helper at 0x358752, obtains the team member iterator,
// then clears each member's waypoint queue, leaves its group and calls
// aiFaceObject with source 1. BFME1 donor establishes the action semantics and
// its linked-list traversal; target-specific helper identities remain pinned
// only where target call evidence supports them.

#include "ascii_string.h"
typedef bool Bool;
class Object;
class AIUpdateInterface;
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
public: void aiFaceObject(Object *, int);
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
class Rva00358752Opaque
{
public:
    Object *lookupUnitByValue(AsciiString);
};
class ScriptActions
{
protected:
    void doTeamFaceNamed(const AsciiString &, const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doTeamFaceNamed(const AsciiString &teamName,
    const AsciiString &faceUnitName)
{
    Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
    if (!team) return;
    Object *faceObject = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(
        (AsciiString &)faceUnitName);
    if (!faceObject) return;
    DLINK_ITERATOR<Object> iter;
    iter = team->iterate_TeamMemberList();
    while (!iter.done()) {
        Object *object = iter.cur();
        AIUpdateInterface *ai = object->getAIUpdateInterface();
        if (ai) {
            ai->clearWaypointQueue();
            object->leaveGroup();
            ai->command.aiFaceObject(faceObject, 1);
        }
        iter.advance();
    }
}
