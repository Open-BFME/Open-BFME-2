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
#include <vector>

// Keep STLport's signed comparison inline without emitting another
// conflicting external copy; stlport_list_int.cpp owns the retail body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
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
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
enum ObjectStatusTypes { OBJECT_STATUS_5=5, OBJECT_STATUS_79=79 };
enum DamageType { DAMAGE_8=8 };
enum DeathType { DEATH_0=0 };
class Rva003979FB;
class Rva00399959;
class AsciiString;
struct Coord3D;
class Team;
class Object
{
protected:
	friend class CastleBehavior;
private:
	friend class Rva003979FB;
protected:
	friend class Rva00399959;
	friend void Rva00396BC5SetCastleId(_STL::vector<ObjectID>*,ObjectID);
public:
	const AsciiString &getName() const { return *(const AsciiString *)((const char *)this + 0x58); }
protected:
	Module *findModule(NameKeyType) const;
public:
	void rva0028CFB2(const int*,const int*);
	float getCastleValue() const { return *(const float*)((const char*)this+0x324); }
	float GetRelativeAngle(const Coord3D*) const;
	Coord3D* getPlanarDirectionTo(Coord3D*,const Object*) const;
	float getBoundingCircleRadius() const { return *(const float*)((const char*)this+0xb8); }
	Relationship getRelationship(const Object*) const;
	int rva0028B511() const;
	bool testStatus(ObjectStatusTypes) const;
	Object* rva002931F5(bool);
	void* rva0028C197() const;
	void teleportTo(const Coord3D*,bool);
	void* rva0028BCF4() const;
	void kill(DamageType,DeathType);
	void rva0028D282(void*);
	Player* getControllingPlayer() const;
	void setStatus(ObjectStatusTypes,bool);
	void setTeam(Team*);
	void rva0028BAC0();
	void rva0028DCC4();
	void rva0028D253();
	void rva0028AE6D();
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

template<class T> inline T& field(void* p,int n) { return *(T*)((char*)p+n); }

#include "../../../Include/Common/TeamBFME2.h"
class W3DBridge;
class Player
{
public:
	Relationship getRelationship(const Team *) const;
	int getPlayerIndex() const { return *(const int *)((const char *)this + 0x54); }
	W3DBridge* getBuildControl() { return (W3DBridge*)((char*)this+0x3bc); }
};
class PlayerList
{
public:
	Player *getLocalPlayer() const { return local; }
	Player* getNthPlayer(int);
	char m_pad00[0x10];
private:
	Player *local; // +0x10
};
extern PlayerList *ThePlayerList;
enum EvaEventID { EVA_NONE = 0 };
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

class Xfer;
class FoundationAIUpdate { protected: virtual void xfer(Xfer*); private: void rva0045527A(ObjectID); friend class CastleBehavior;
 friend class Rva00399959; char native04[0x2c]; };
class CastleBehaviorInterface {
public:
 virtual void slot0()=0;
 virtual void rva00395DAC()=0;
 virtual void slot2()=0;
 virtual bool slot3()=0;
};
class PolygonTrigger;
class BuildListInfo;
class ThingTemplate;
class CastleBehavior : public FoundationAIUpdate, public CastleBehaviorInterface
{
public:
	void playEvaEventsForCastlePacking();
	virtual void rva00395DAC();
	void rva0039865E(PolygonTrigger*);
	Object* buildCastleStructure(BuildListInfo*,bool);
	void* GetArmyIDFromClosestObject();
	Object* createOwnedObject(void*);
	void rva003993F2(bool);
	void teleportStragglersFromWallToGround(bool);
	void registerOwnedObject(Object*);
	bool checkForAutoPack();
	bool checkForInstantUnPack();
	void rva00397B03(ObjectStatusTypes,bool);
	void rva00399370();
	void rva0039792B();
	void initiateUnpack(bool,const ThingTemplate*);
	virtual void DoXfer(Xfer*);
};

static __forceinline void reportCastlePackingEva(CastleBehavior *behavior, Object *self, Team *team,
    Player *controllingPlayer, Player *localPlayer, Object *object, CastleMemberBehaviorModule *module)
{

    if (controllingPlayer == localPlayer) {
        if (!((Rva003962E7 *)behavior)->rva003962E7(controllingPlayer->getPlayerIndex(), TheEva->timeout88)) return;
        int event = module ? module->getData()->localEvent : 9;
        const Coord3D *position = object ? (Coord3D *)((char *)object + 0x38) : (Coord3D *)((char *)self + 0x38);
        TheEva->reportEvaEvent((EvaEventID)event, position, 0);
        return;
    }
    Relationship relationship = localPlayer->getRelationship(team);
    if (relationship == ALLIES) {
        if (!((Rva003962E7 *)behavior)->rva003962E7(controllingPlayer->getPlayerIndex(), TheEva->timeout88)) return;
        int event = module ? module->getData()->allyEvent : 10;
        const Coord3D *position = object ? (Coord3D *)((char *)object + 0x38) : (Coord3D *)((char *)self + 0x38);
        TheEva->reportEvaEvent((EvaEventID)event, position, 0);
        return;
    }
    if (relationship != ENEMIES) return;
    int playerKey = field<int>(localPlayer, 0x54);
    _STL::map<int, int> &map = field<_STL::map<int, int> >(behavior, 0xa0);
    _STL::map<int, int>::iterator it = map.find(playerKey);
    if (it == map.end()) return;
    if (TheEva->timeout84 + (unsigned)it->second < TheGameLogic->getFrame()) return;
    int event = module ? module->getData()->enemyEvent : 8;
    const Coord3D *position = object ? (Coord3D *)((char *)object + 0x38) : (Coord3D *)((char *)self + 0x38);
    TheEva->reportEvaEvent((EvaEventID)event, position, 0);
}

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
    Object *object = TheGameLogic->findObjectByID(field<ObjectID>(this, 0x38));
    CastleMemberBehaviorModule *module;
    if (object) {
        static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
        module = (CastleMemberBehaviorModule *)object->findModule(key);
    } else module = 0;
    reportCastlePackingEva(this, self, team, controllingPlayer, localPlayer, object, module);
}
