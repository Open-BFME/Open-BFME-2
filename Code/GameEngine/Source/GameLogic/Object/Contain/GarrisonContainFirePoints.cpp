// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// ZH GeneralsMD GarrisonContain.cpp putObjectAtBestGarrisonPoint and the two
// attemptBestFirePointPosition overloads, reviewed through BFME1 reference
// revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 (BFME1 donor
// GarrisonContain_putObjectAtBestGarrisonPoint.cpp).
//
// Target facts: putObjectAtBestGarrisonPoint 0x004785A2 (107 bytes, ret 0xC)
// reads the target's position at Object +0x38 and ID at +0x74, asks the
// full-object vtable slot +0x6C for the occupant's point index, then calls
// findConditionIndex 0x00477E50, findClosestFreeGarrisonPointIndex 0x00478445
// and putObjectAtGarrisonPoint 0x00477DA1. The Object-victim overload
// 0x00478850 and the position overload 0x004788CE (126 bytes each) are entered
// through the Contain interface at +0x20 (vtable 0x00846080 slots 78 and 77),
// remove the source from its point (0x00477E82), place it with the helper
// above and test Weapon::isWithinAttackRange 0x002CB933 / 0x002CB902 with
// 0.0f and 1. Carried from the donor: the method names and the order of the
// sanity tests. The base views follow the sibling GarrisonContain TUs.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectID
{
    INVALID_ID = 0
};

class Object
{
public:
    ObjectID getID() const { return m_id; }
    const Coord3D *getPosition() const { return &m_pos; }
private:
    unsigned char m_pad00[0x38];
    Coord3D m_pos; // +0x38
    unsigned char m_pad44[0x74 - 0x44];
    ObjectID m_id; // +0x74
};

class Weapon
{
public:
    bool isWithinAttackRange(const Object *source, const Object *target, float extra = 0.0f, int flag = 1) const;
    char isWithinAttackRange(Object *source, void *pos, float extra = 0.0f, int flag = 1) const;
};

class B0
{
public:
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
    virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15();
    virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19();
    virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23();
    virtual void b24(); virtual void b25(); virtual void b26();
    virtual int getObjectGarrisonPointIndex(ObjectID id);
    int pad4;
    void *object;
};
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char pad[12]; };
class B3
{
public:
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos);
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);
};
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4,
    public B5, public B6, public B7, public B8
{
public:
    virtual ~OpenContain();
};

class GarrisonContain : public OpenContain
{
public:
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos);
protected:
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *targetPos);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int pointIndex);
    void removeObjectFromGarrisonPoint(Object *obj, int pointIndex);
    void putObjectAtBestGarrisonPoint(Object *obj, Object *target, const Coord3D *targetPos);
};

void GarrisonContain::putObjectAtBestGarrisonPoint(Object *obj, Object *target, const Coord3D *targetPos)
{
    if (obj == 0 || (target == 0 && targetPos == 0))
        return;

    if (target != 0)
        targetPos = target->getPosition();

    if (getObjectGarrisonPointIndex(obj->getID()) != -1)
        return;

    int conditionIndex = findConditionIndex();
    int pointIndex = findClosestFreeGarrisonPointIndex(conditionIndex, targetPos);
    if (pointIndex == -1)
        return;

    putObjectAtGarrisonPoint(obj, target != 0 ? target->getID() : INVALID_ID, conditionIndex, pointIndex);
}

bool GarrisonContain::attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim)
{
    if (!source || !victim || !weapon)
        return false;

    int existingIndex = getObjectGarrisonPointIndex(source->getID());
    if (existingIndex != -1)
        removeObjectFromGarrisonPoint(source, existingIndex);

    putObjectAtBestGarrisonPoint(source, victim, 0);

    if (weapon->isWithinAttackRange((const Object *)source, victim))
        return true;

    existingIndex = getObjectGarrisonPointIndex(source->getID());
    if (existingIndex != -1)
        removeObjectFromGarrisonPoint(source, existingIndex);
    return false;
}

bool GarrisonContain::attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos)
{
    if (!source || !targetPos || !weapon)
        return false;

    int existingIndex = getObjectGarrisonPointIndex(source->getID());
    if (existingIndex != -1)
        removeObjectFromGarrisonPoint(source, existingIndex);

    putObjectAtBestGarrisonPoint(source, 0, targetPos);

    if (weapon->isWithinAttackRange(source, (void *)targetPos))
        return true;

    existingIndex = getObjectGarrisonPointIndex(source->getID());
    if (existingIndex != -1)
        removeObjectFromGarrisonPoint(source, existingIndex);
    return false;
}
