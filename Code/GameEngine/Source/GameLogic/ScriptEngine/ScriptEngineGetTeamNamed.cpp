// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?getTeamNamed@ScriptEngine@@QAEPAVTeam@@VAsciiString@@_N@Z
// Target: 0x003584E9, 617 bytes (Ghidra boundary). The existing retail pin
// and the dispatcher callers establish the identity and by-value ABI. Target
// disassembly establishes the "<This Team>" branch, ScriptEngine fields +0x1A110
// / +0x1A118, the team-prototype fields, and the create-if-missing flag.
// Donor: ZH ScriptEngine.cpp:5957-5994 supplies the named-team lookup,
// current/condition-team fallback, singleton/instance handling, and warning
// semantics. BFME2 diverges: it normalizes a name, checks a pair-keyed map,
// and can activate/create an instance; those are represented by target-RVA
// facades below until their independent identities are recovered.
// Shape notes: the singleton branch keeps its own Team* so the instance lives
// in ESI with the status byte in AL, and every null result funnels to one
// trailing "return 0" (the whole lookup sits inside if (teamPrototype)).

#include "ascii_string.h"
#include <utility>

typedef bool Bool;

class Team;
class TeamPrototype;

typedef _STL::pair<const AsciiString, AsciiString> TeamNameKeyPair;

struct Rva0002C4FD
{
    char storage[sizeof(TeamNameKeyPair)];
    Rva0002C4FD(const StringBase<char> &, const StringBase<char> &);
    ~Rva0002C4FD()
    {
        ((TeamNameKeyPair *)this)->~TeamNameKeyPair();
    }
};

struct TeamMapNode
{
    unsigned char pad[0x18];
    unsigned int value; // team id
};

class Rva0032C07COwner
{
public:
    TeamMapNode *find(Rva0002C4FD &key);
};

class Rva002046C0Owner
{
public:
    AsciiString resolveName(const AsciiString &name);
};

#include "../../../Include/Common/TeamFactory.h"

#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/Common/Team.h"

class Rva003A3CBBOwner
{
public:
    Team *createInstance(const AsciiString &normalized, const AsciiString &name);
};




#include "../../../Include/GameLogic/ScriptEngine.h"
// Retail .CRT$XCU 0x007AEC1A is this unit's Drawable.h copy (static 0x00E01E24).
#include "../../../Include/GameClient/Drawable.h"

// The TeamFactory singleton; its lookup/create entry points below keep
// address-derived owner names until their identities are recovered.
class TeamFactory;
extern TeamFactory *TheTeamFactory;

extern AsciiString Rva0032B389Join(const AsciiString &, const AsciiString &);

Team *ScriptEngine::getTeamNamed(AsciiString name, Bool createIfMissing)
{
    if (name.compare("<This Team>") == 0) {
        if (m_callingTeam)
            return m_callingTeam;
        return m_conditionTeam;
    }

    AsciiString normalized = ((Rva002046C0Owner *)this)->resolveName(name);

    const AsciiString *emptyName = &AsciiString::TheEmptyString;
    if (m_callingTeam) {
        TeamPrototype *prototype = m_callingTeam->m_proto;
        const AsciiString *primary = emptyName;
        if (prototype)
            primary = &prototype->m_10;
        if (primary->compare(normalized) == 0) {
            prototype = m_callingTeam->m_proto;
            const AsciiString *alternate = emptyName;
            if (prototype)
                alternate = &prototype->m_name;
            if (alternate->compare(name) == 0)
                return m_callingTeam;
        }
    }

    if (m_conditionTeam) {
        TeamPrototype *prototype = m_conditionTeam->m_proto;
        const AsciiString *primary = emptyName;
        if (prototype)
            primary = &prototype->m_10;
        if (primary->compare(normalized) == 0) {
            prototype = m_conditionTeam->m_proto;
            const AsciiString *alternate = emptyName;
            if (prototype)
                alternate = &prototype->m_name;
            if (alternate->compare(name) == 0)
                return m_conditionTeam;
        }
    }

    {
        Rva0002C4FD key(*(const StringBase<char> *)&normalized,
                        *(const StringBase<char> *)&name);
        Rva0032C07COwner *map = (Rva0032C07COwner *)((char *)this + 0x190C4);
        TeamMapNode *node = map->find(key);
        if (node != *(TeamMapNode **)map)
            return TheTeamFactory->findTeamByID(node->value);
    }

    TeamFactory *factory = TheTeamFactory;
    TeamPrototype *teamPrototype = factory->findTeamPrototype(normalized, name);
    if (teamPrototype) {
        if (teamPrototype->m_flags & 1) {
            Team *team = teamPrototype->m_dlinkhead_TeamInstanceList;
            if (!team)
                return 0;
            if (team->isActive())
                return team;
            if (!createIfMissing)
                return 0;
            team->setActive();
            return team;
        }

        if (teamPrototype->countTeamInstances() > 1) {
            static int warnCount;
            if (warnCount < 10) {
                ++warnCount;
                AppendDebugMessage(
                    AsciiString("***Referencing multiple team by unspecific instance:***"), false);
                AppendDebugMessage(Rva0032B389Join(normalized, name), false);
            }
        }

        Team *team = teamPrototype->m_dlinkhead_TeamInstanceList;
        if (team)
            return team;
        if (createIfMissing)
            return ((Rva003A3CBBOwner *)TheTeamFactory)->createInstance(normalized, name);
    }
    return 0;
}
