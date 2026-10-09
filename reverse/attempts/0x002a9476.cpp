// ?addNewAIForPlayer@Rva002A8F24@@QAEPAXPAVPlayer@@@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// WB E8E070 names SkirmishAIManager::Register. Retail2A9365..2A93F5
// establishes the controller dispatches and unique hero-ID insertion.
// The manager's existing Rva002A8F24 identity and callee spellings are kept
// consistent with its already verified providers and consumers.
// Object +4B0/+74 and template +121 bit10 are native evidence; WB's
// corresponding offsets and flag implementation differ from this target.
#include <vector>
#include <algorithm>
#include <map>
#include <hash_map>
#include <new>

class Player;
class CreateAHeroData;
enum ObjectID { OBJECTID_INVALID = 0 };

struct SkirmishRegisterTemplate
{
    unsigned char prefix00[0x121];
    unsigned char kindOf121;
};
class Object
{
public:
    Player *getControllingPlayer() const;
    void *vtable00;
    SkirmishRegisterTemplate *template04;
    unsigned char gap08[0x6c];
    ObjectID id74;
    unsigned char gap78[0x438];
    unsigned char excluded4b0;
};
struct Rva002A8AB1Record
{
    void rva002C6A3D(Object *);
};
class AIStatCollector
{
public:
    void Register(Object *);
    AIStatCollector(Player *);
    unsigned char nativeStorage[0x38];
};
class Rva002A8F24
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *);
    void *rva002A8F24(Player *);
    void rva002A9365(Object *);
    void findPreSpawnedObjects();
    void *addNewAIForPlayer(Player *);
private:
    unsigned char prefix00[0x908];
    _STL::map<int,int> collectors908;
    _STL::vector<const class ModuleData *> teams914;
    _STL::hash_map<unsigned int,void *> builders920;
    _STL::vector<ObjectID> heroIDs934;
};

void Rva002A8F24::rva002A9365(Object *object)
{
    if (object->excluded4b0)
        return;
    Rva002A8AB1Record *record = rva002A8AB1(object->getControllingPlayer());
    if (record)
        record->rva002C6A3D(object);
    AIStatCollector *collector = static_cast<AIStatCollector *>(rva002A8F24(object->getControllingPlayer()));
    if (collector)
        collector->Register(object);
    if (!(object->template04->kindOf121 & 0x10))
        return;
    ObjectID id = object->id74;
    ObjectID *end = heroIDs934.end();
    CreateAHeroData **found = _STL::find(reinterpret_cast<CreateAHeroData **>(heroIDs934.begin()),
        reinterpret_cast<CreateAHeroData **>(end), reinterpret_cast<CreateAHeroData *&>(id));
    if (reinterpret_cast<ObjectID *>(found) == end)
    {
        ObjectID appendID = object->id74;
        heroIDs934.push_back(appendID);
    }
}

// WB E8D510 and native 2A9411..2A9476: iterate every AI player's default
// team and register its members. The 24-byte iterator ABI is independently
// established by TeamIterateTeamMemberList.cpp; target default team is +2EC.
template<class OBJCLASS> class DLINK_ITERATOR {
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};
class Team {
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class Player {
public:
    bool rva002AA245() const;
    unsigned char prefix00[0x2ec];
    Team *defaultTeam2ec;
};
class PlayerList {
public:
    Player *getNthPlayer(int);
    unsigned char prefix00[0x14];
    int playerCount14;
};
extern PlayerList *ThePlayerList;
void Rva002A8F24::findPreSpawnedObjects() {
    for (int i=0; i<ThePlayerList->playerCount14; ++i) {
        Player *player=ThePlayerList->getNthPlayer(i);
        if (player->rva002AA245()) {
            for (DLINK_ITERATOR<Object> it=player->defaultTeam2ec->iterate_TeamMemberList();
                !it.done(); it.advance())
                rva002A9365(it.cur());
        }
    }
}

// Existing provider spellings preserve independently verified call ownership.
class Rva004E94CA { public: bool rva004E94CA(Player *); };
class Rva004E9823 { public: void rva004E9823(const ModuleData *); };
class Rva004E9600 { public: void *rva004E95D4(void *); };
class Rva004E962A { public: Rva004E962A(); unsigned char nativeStorage[0x28]; };
class AsciiString;
class ArmorTemplate;
class ArmorStore { public: const ArmorTemplate *rva0041F474(const AsciiString &) const; };
extern ArmorStore *g_00E0312C;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva002A9140 { public: AsciiString &rva002A9140(const int &); };
class Rva004EC1CE { public: void rva004EC1CE(const AsciiString &); };

void *Rva002A8F24::addNewAIForPlayer(Player *player) {
    void *ai=0;
    const ModuleData **it=teams914.begin(), **end=teams914.end();
    for (; it!=end; ++it) {
        if (((Rva004E94CA *)*it)->rva004E94CA(player)) {
            ((Rva004E9823 *)*it)->rva004E9823((const ModuleData *)player);
            ai=((Rva004E9600 *)*it)->rva004E95D4(player);
            break;
        }
    }
    if (!ai) {
        Rva004E962A *team=new Rva004E962A;
        ((Rva004E9823 *)team)->rva004E9823((const ModuleData *)player);
        ai=((Rva004E9600 *)team)->rva004E95D4(player);
        teams914.push_back((const ModuleData *&)team);
    }
    const AsciiString &name=*(const AsciiString *)((char *)player+0x58);
    if (g_00E0312C->rva0041F474(name)) {
        int key=TheNameKeyGenerator->nameToKey(name);
        if (builders920.find((const unsigned &)key)!=builders920.end())
            ((Rva004EC1CE *)ai)->rva004EC1CE(((Rva002A9140 *)&builders920)->rva002A9140(key));
    } else {
        *(bool *)((char *)ai+0x168)=true;
    }
    AIStatCollector *collector=new AIStatCollector(player);
    int playerID=*(int *)((char *)player+0x54);
    collectors908[playerID]=(int)collector;
    return ai;
}

// Independent317a trial 2026-10-09: typed player/map formulation emitted326B
// against native323B. Three additional stack bytes and EBX lifetime differ;
// argument-slot reuse emitted332B. Complete alternate trial retained locally
// in build/skirmish-bank-ours.cpp; no recovery or byte-progress claim.
