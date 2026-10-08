// ?removeInvalidObjectsFromGarrisonPoints@GarrisonContain@@IAEXXZ
// partial score=0.97 date=2026-10-08
// 0x0047933C removeInvalidObjectsFromGarrisonPoints, 89 bytes: 7 diffs, point
// pointer and occupant swap edi/esi (retail point edi, obj esi). The ObjectID
// local fixes this=ebx (without it this/point/obj rotate, 18 diffs). Tried:
// do-while/for/while, pointer walk, function-scope locals, nested/continue
// ifs, inline/forceinline weapon predicate, duplicated remove arm, flags.
// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
enum ObjectID { INVALID_ID = 0 };
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
class GameLogic
{
public:
    Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct GarrisonPointData
{
    ObjectID objectID;
    ObjectID targetID;
    unsigned int placeFrame;
    unsigned int lastEffectFrame;
    void *effect;
};

class B0 { public: virtual void b0(); int pad4; void *object; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char pad[12]; };
class B3 { public: virtual void b3(); };
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
protected:
    void removeObjectFromGarrisonPoint(Object *obj, int pointIndex);
    void removeInvalidObjectsFromGarrisonPoints();
    static bool removable(Object *obj) { const Weapon *weapon = obj->getCurrentWeapon(0); return weapon && weapon->getTemplate()->get(); }
private:
    unsigned char m_padFC100[0x100 - 0xFC];
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
