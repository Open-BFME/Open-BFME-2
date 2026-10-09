// ?removeInvalidObjectsFromGarrisonPoints@GarrisonContain@@IAEXXZ
// partial score=0.97 date=2026-10-09
// ?removeInvalidObjectsFromGarrisonPoints@GarrisonContain@@IAEXXZ
// cl: /ICode/GameEngine/Source/Common /O1 /arch:SSE /G7 /MD /DNDEBUG
// Target47933C..479395: argless40-slot sweep, skips when count420 is zero.
// Slot array100/stride14 and ObjectID lookup49DC5, weapon28AEBD,
// template+4/get2C9400, removal477E82 are independently native evidence.
// Method purpose agrees with GarrisonContain donor; original wrong three-arg
// attemptBestFirePointPosition identity is retired. Unknown root100 is opaque,
// replacing the old invented B0..B8 bases. Use canonical GameLogic header.
// Full89B and all calls resolve; seven register bytes still swap point/object
// ESI/EDI. Whole-check helper scope also unchanged. No Code edit or new pin.
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
class Object
{
public:
    const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};
#include "GameLogicObjectLookupView.h"
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
    static bool removable(Object *obj) { const Weapon *weapon = obj->getCurrentWeapon(0); return weapon && weapon->getTemplate()->get(); }
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
