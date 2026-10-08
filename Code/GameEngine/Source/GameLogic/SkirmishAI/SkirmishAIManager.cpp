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
};
class Rva002A8F24
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *);
    void *rva002A8F24(Player *);
    void rva002A9365(Object *);
private:
    unsigned char prefix00[0x934];
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
