// cl: /I. /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CastleBehavior::playEvaEventsForCastlePacking, retail 0x00396F2C (443B).
// Identity: WorldBuilder 0x00EB9F20 names this method in CastleSystem.cpp;
// native initiate-packing 0x0039A62B calls it before changing the state.
// Retail layouts: Object team +0x304, Player index +0x54, Castle object ID
// +0x38 and event-history map +0xA0, module data event IDs +8/+C/+10.
// The typed module-data getter preserves retail's EDI module / EBX player
// allocation. The inline reporting helper preserves the pointer homes and
// the guard's lifetime across every report and early return. The native EH
// table has guard cleanup followed by rollback of the local-static key.
// The source split is a code-generation choice; it asserts no extra retail
// function. All callees already have verified owners; no pins are added.
#include <map>

// Keep STLport's signed comparison inline without emitting another
// conflicting external copy; stlport_list_int.cpp owns the retail body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
}
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

class Player;
struct CastleEvaData
{
    char pad[8];
    int localEvent, allyEvent, enemyEvent;
};
#include "../../../Include/Common/Module.h"
class CastleMemberBehaviorModule : public Module
{
public:
    const CastleEvaData *getData() const { return reinterpret_cast<const CastleEvaData *>(getModuleData()); }
};
class Object
{
protected:
    Module *findModule(NameKeyType) const;
    friend class CastleBehavior;
};
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

template<class T> inline T &field(void *p, int n)
{
    return *(T *)((char *)p + n);
}
class Team;

class Team
{
public:
    Player *getControllingPlayer() const;
};
enum Relationship { REL_ENEMY = 0, REL_NEUTRAL = 1, REL_ALLY = 2 };
class Player
{
public:
    Relationship getRelationship(const Team *) const;
    int getPlayerIndex() const { return *(const int *)((const char *)this + 0x54); }
};
class PlayerList
{
    char pad[0x10];
    Player *local;
public:
    Player *getLocalPlayer() const { return local; }
};
extern PlayerList *ThePlayerList;
enum EvaEventID { EVA_NONE = 0 };
struct Coord3D;
class Eva
{
public:
    char pad[0x84];
    unsigned timeout84;
    int timeout88;
    bool reportEvaEvent(EvaEventID, const Coord3D *, const Coord3D *);
};
extern Eva *TheEva;
class Rva003962E7
{
public:
    bool rva003962E7(int, int);
};
class Rva00395561
{
    int count;
public:
    Rva00395561();
    ~Rva00395561();
};

class CastleBehavior
{
public:
    void playEvaEventsForCastlePacking();

    __forceinline void reportPackingEvaEvents(Object *self, Team *team,
        Player *controllingPlayer, Player *localPlayer)
    {
        Object *object = TheGameLogic->findObjectByID(field<ObjectID>(this, 0x38));
        CastleMemberBehaviorModule *module;
        if (object) {
            static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
            module = (CastleMemberBehaviorModule *)object->findModule(key);
        } else module = 0;

        if (controllingPlayer == localPlayer) {
            if (!((Rva003962E7 *)this)->rva003962E7(controllingPlayer->getPlayerIndex(), TheEva->timeout88)) return;
            int event = module ? module->getData()->localEvent : 9;
            const Coord3D *position = object ? (Coord3D *)((char *)object + 0x38) : (Coord3D *)((char *)self + 0x38);
            TheEva->reportEvaEvent((EvaEventID)event, position, 0);
            return;
        }
        Relationship relationship = localPlayer->getRelationship(team);
        if (relationship == REL_ALLY) {
            if (!((Rva003962E7 *)this)->rva003962E7(controllingPlayer->getPlayerIndex(), TheEva->timeout88)) return;
            int event = module ? module->getData()->allyEvent : 10;
            const Coord3D *position = object ? (Coord3D *)((char *)object + 0x38) : (Coord3D *)((char *)self + 0x38);
            TheEva->reportEvaEvent((EvaEventID)event, position, 0);
            return;
        }
        if (relationship != REL_ENEMY) return;
        int playerKey = field<int>(localPlayer, 0x54);
        _STL::map<int, int> &map = field<_STL::map<int, int> >(this, 0xa0);
        _STL::map<int, int>::iterator it = map.find(playerKey);
        if (it == map.end()) return;
        if (TheEva->timeout84 + (unsigned)it->second < TheGameLogic->getFrame()) return;
        int event = module ? module->getData()->enemyEvent : 8;
        const Coord3D *position = object ? (Coord3D *)((char *)object + 0x38) : (Coord3D *)((char *)self + 0x38);
        TheEva->reportEvaEvent((EvaEventID)event, position, 0);
    }
};

void CastleBehavior::playEvaEventsForCastlePacking()
{
    Object *self = field<Object *>(this, 8);
    Team *team = field<Team *>(self, 0x304);
    if (!team) return;
    Player *controllingPlayer = team->getControllingPlayer();
    if (!controllingPlayer) return;
    Rva00395561 guard;
    Player *localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer() : 0;
    if (!localPlayer) return;
    reportPackingEvaEvents(self, team, controllingPlayer, localPlayer);
}
