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
    void *value;
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

class Rva0039F761Owner
{
public:
    Team *findInstance(void *prototypeKey);
};

class Rva0039FE6COwner
{
public:
    TeamPrototype *findPrototype(const AsciiString &normalized, const AsciiString &name);
};

class TeamPrototype
{
public:
    int countTeamInstances();

    unsigned char pad_0000[0x18];
    unsigned int flags; // +0x18; bit 0 denotes a singleton (target)
    unsigned char pad_001C[0x334 - 0x1C];
    Team *firstInstance; // +0x334
};

class Rva003A3CBBOwner
{
public:
    Team *createInstance(const AsciiString &normalized, const AsciiString &name);
};

class TeamPrototypeNames
{
public:
    unsigned char pad_0000[0x10];
    AsciiString primaryName; // +0x10 (target)
    AsciiString alternateName; // +0x14 (target)
};

class TeamState
{
public:
    Bool active;
    Bool created;

    Bool isActive() { return active; }
    void setActive()
    {
        if (!active) {
            created = 1;
            active = 1;
        }
    }
};

class Team
{
public:

    unsigned char pad_0000[0x30];
    TeamPrototypeNames *prototype; // +0x30 (target)
    unsigned char pad_0034[0x5D - 0x34];
    TeamState status; // +0x5D (target)
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString name, Bool createIfMissing);
    void AppendDebugMessage(const AsciiString &message, Bool forcePause);

private:
    unsigned char pad_0000[0x1A110];
    Team *callingTeam; // +0x1A110 (target)
    unsigned char pad_1A114[4];
    Team *conditionTeam; // +0x1A118 (target)
};

// The TeamFactory singleton; its lookup/create entry points below keep
// address-derived owner names until their identities are recovered.
class TeamFactory;
extern TeamFactory *TheTeamFactory;

extern AsciiString Rva0032B389Join(const AsciiString &, const AsciiString &);

Team *ScriptEngine::getTeamNamed(AsciiString name, Bool createIfMissing)
{
    if (name.compare("<This Team>") == 0) {
        if (callingTeam)
            return callingTeam;
        return conditionTeam;
    }

    AsciiString normalized = ((Rva002046C0Owner *)this)->resolveName(name);

    const AsciiString *emptyName = &AsciiString::TheEmptyString;
    if (callingTeam) {
        TeamPrototypeNames *prototype = callingTeam->prototype;
        const AsciiString *primary = emptyName;
        if (prototype)
            primary = &prototype->primaryName;
        if (primary->compare(normalized) == 0) {
            prototype = callingTeam->prototype;
            const AsciiString *alternate = emptyName;
            if (prototype)
                alternate = &prototype->alternateName;
            if (alternate->compare(name) == 0)
                return callingTeam;
        }
    }

    if (conditionTeam) {
        TeamPrototypeNames *prototype = conditionTeam->prototype;
        const AsciiString *primary = emptyName;
        if (prototype)
            primary = &prototype->primaryName;
        if (primary->compare(normalized) == 0) {
            prototype = conditionTeam->prototype;
            const AsciiString *alternate = emptyName;
            if (prototype)
                alternate = &prototype->alternateName;
            if (alternate->compare(name) == 0)
                return conditionTeam;
        }
    }

    {
        Rva0002C4FD key(*(const StringBase<char> *)&normalized,
                        *(const StringBase<char> *)&name);
        Rva0032C07COwner *map = (Rva0032C07COwner *)((char *)this + 0x190C4);
        TeamMapNode *node = map->find(key);
        if (node != *(TeamMapNode **)map)
            return ((Rva0039F761Owner *)TheTeamFactory)->findInstance(node->value);
    }

    Rva0039FE6COwner *factory = (Rva0039FE6COwner *)TheTeamFactory;
    TeamPrototype *teamPrototype = factory->findPrototype(normalized, name);
    if (teamPrototype) {
        if (teamPrototype->flags & 1) {
            Team *team = teamPrototype->firstInstance;
            if (!team)
                return 0;
            TeamState *status = &team->status;
            if (status->isActive())
                return team;
            if (!createIfMissing)
                return 0;
            status->setActive();
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

        Team *team = teamPrototype->firstInstance;
        if (team)
            return team;
        if (createIfMissing)
            return ((Rva003A3CBBOwner *)TheTeamFactory)->createInstance(normalized, name);
    }
    return 0;
}
