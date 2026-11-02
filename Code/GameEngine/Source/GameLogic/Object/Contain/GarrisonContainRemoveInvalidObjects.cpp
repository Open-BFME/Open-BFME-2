// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// ?removeInvalidObjectsFromGarrisonPoints@GarrisonContain@@IAEXXZ @0x0047933C (89B):
// GarrisonContain::removeInvalidObjectsFromGarrisonPoints, BFME 2's form of the
// Zero Hour member (GarrisonContain.cpp) that drops garrisoned objects whose
// current weapon no longer qualifies.
// Target47933C..479395: argless40-slot sweep, skips when count420 is zero.
// Slot array100/stride14 and ObjectID lookup49DC5, weapon28AEBD,
// template+4/get2C9400, removal477E82 are independently native evidence.
// Method purpose agrees with GarrisonContain donor; original wrong three-arg
// attemptBestFirePointPosition identity is retired. Unknown root100 is opaque,
// replacing the old invented B0..B8 bases. Uses the canonical GameLogic header.
// The lookup chain (ObjectIdMap::find 0x002888D4 and GameLogic::findObjectByID
// 0x00049DC5, rowed COMDAT copies, as in AIDozerManager.cpp) is visible in
// this unit; with it cl gives the slot pointer and the object retail's ESI/EDI.
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
class Object;
class Rva002C9400ByteField { public: unsigned char get() const; };
class Weapon
{
public:
    const Rva002C9400ByteField *getTemplate() const { return m_template; }
private:
    void *m_vtable;
    const Rva002C9400ByteField *m_template;
};
#include "../object.h"
#include "../../../Common/GameLogicObjectLookupView.h"
struct VisLookupNode { VisLookupNode *next; ObjectID key; Object *object; };
struct VisLookupBuckets {
 VisLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 VisLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct VisLookupMap { unsigned char hashEqual[4]; VisLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 VisLookupMap *map=(VisLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 VisLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}
extern GameLogic *TheGameLogic;

struct GarrisonPointData
{
    ObjectID objectID;
    ObjectID targetID;
    unsigned int placeFrame;
    unsigned int lastEffectFrame;
    void *effect;
};

class GarrisonContain
{
protected:
    void removeObjectFromGarrisonPoint(Object *obj, int pointIndex);
    void removeInvalidObjectsFromGarrisonPoints();
private:
    unsigned char prefix100[0x100];
    GarrisonPointData m_garrisonPointData[40];
    int m_garrisonPointsInUse;
};

void GarrisonContain::removeInvalidObjectsFromGarrisonPoints()
{
    if (m_garrisonPointsInUse == 0)
        return;
    for (int i = 0; i < 40; ++i)
    {
        ObjectID id = m_garrisonPointData[i].objectID;
        Object *obj = TheGameLogic->findObjectByID(id);
        if (obj)
        {
            const Weapon *weapon = obj->getCurrentWeapon(0);
            if (weapon && weapon->getTemplate()->get())
                removeObjectFromGarrisonPoint(obj, i);
        }
    }
}
