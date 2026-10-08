// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// GarrisonContain::onRemoving (0x00478D0A, 717 bytes), after the BFME1
// GarrisonContain_onRemoving.cpp donor and the ZH GarrisonContain.cpp body
// (BFME1 reference revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20).
//
// Target facts: slot 23 of the +0x20 Contain interface vtable 0x00846080;
// it saves the rider's position (+0x38), calls OpenContain::onRemoving
// 0x00464D02 and removeObjectFromGarrisonPoint 0x00477E82 (index -1), clears
// bit 0 of the rider's +0x380 word, releases the hold (Object::clearDisabled,
// type 3) and status 0x3A (Object::setStatus 0x0023DB0E). With nothing left
// inside (interface slot +0x114) a teamed structure returns to the team saved
// at +0xFC (TeamFactory::findTeamByID, Object::setTeam), loses status 1, the
// +0x9DD hide flag and model condition 10 (0x0028AE6D refresh); otherwise the
// hide flag drops when the stealth count (slot +0x124) differs from the
// contain count. The rider's +0x428 safe-occlusion frame becomes the logic
// frame (+0x40) plus its template's +0x554 delay, then
// recalcApparentControllingPlayer (slot +0x50) runs. When the 0x00462785 test
// holds and the structure's health (body +0x254 slot +0x10) is at or below
// zero, a structure with bit 61 of the slot +0xB0 mask destroys the rider
// (GameLogic::destroyObject 0x00242C09); otherwise the rider is put back at
// the saved position (Thing::setPosition 0x0030AA80), kicked along its
// transform's first column scaled by GameLogicRandomValue(2, 5) 0x00233FF4
// (physics 0x00390629 then 0x003909FA, with model condition 0x7F) and either
// damaged for 3/4 of its maximum health (KindOf bit 90, DamageInfo 0x00263895,
// type 8, death 0) or killed. The trailing weapon-set pass clears flag 0x14
// (gate 0x0029091E) and re-sets it on every member that the rider's contain
// interface (0x0028C197, slot +0x108) hands out.
//
// Carried from the donor: the method name, the base call and the order of the
// rider and structure updates through the team restore. The occlusion frame,
// the dead-structure ejection and the weapon-set pass have no BFME1/ZH
// counterpart; their shape is read from the target.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include <list>

enum ObjectStatusTypes
{
    OBJECT_STATUS_NONE = 0
};
enum DisabledType
{
    DISABLED_DEFAULT = 0
};
enum WeaponSetType
{
    WEAPONSET_NONE = 0
};
enum DamageType
{
    DAMAGE_UNRESISTABLE = 8
};
enum DeathType
{
    DEATH_NORMAL = 0
};

class Object;
class Team;

struct Rva0046247DPair
{
    void *m00;
    const _STL::list<Object *> *m04;
};

class DamageInfo
{
public:
    DamageInfo();
    char m_lead[0x08];
    unsigned int m_sourceID; // +0x08
    char m_gap0C[0x10 - 0x0C];
    DamageType m_damageType; // +0x10
    char m_gap14[0x1C - 0x14];
    DeathType m_deathType; // +0x1C
    float m_amount; // +0x20
    char m_tail[0x7C - 0x24];
};

class BodyModuleInterface
{
public:
    virtual void attemptDamage(DamageInfo *info);
    virtual void vf04();
    virtual void vf08();
    virtual void vf0C();
    virtual float getHealth() const;
    virtual void vf14();
    virtual float getMaxHealth() const;
};

class PhysicsBehavior
{
public:
    void rva00390629(bool value);
};

class Rva003909FAObj
{
public:
    void consume(void *force, int a, int b);
};

class ContainSlots
{
public:
    virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
    virtual void h04(); virtual void h05(); virtual void h06(); virtual void h07();
    virtual void h08(); virtual void h09(); virtual void h10(); virtual void h11();
    virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
    virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
    virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23();
    virtual void h24(); virtual void h25(); virtual void h26(); virtual void h27();
    virtual void h28(); virtual void h29(); virtual void h30(); virtual void h31();
    virtual void h32(); virtual void h33(); virtual void h34(); virtual void h35();
    virtual void h36(); virtual void h37(); virtual void h38(); virtual void h39();
    virtual void h40(); virtual void h41(); virtual void h42(); virtual void h43();
    virtual void h44(); virtual void h45(); virtual void h46(); virtual void h47();
    virtual void h48(); virtual void h49(); virtual void h50(); virtual void h51();
    virtual void h52(); virtual void h53(); virtual void h54(); virtual void h55();
    virtual void h56(); virtual void h57(); virtual void h58(); virtual void h59();
    virtual void h60(); virtual void h61(); virtual void h62(); virtual void h63();
    virtual void h64(); virtual void h65();
    virtual Rva0046247DPair &slot108(Rva0046247DPair &p);
};

class ThingTemplate
{
public:
    __forceinline bool isKindOf(int t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
    unsigned int getOcclusionDelay() const { return m_occlusionDelay; }
private:
    unsigned char m_pad00[0x108];
    unsigned char m_kindof[32]; // +0x108
    unsigned char m_pad128[0x554 - 0x128];
    unsigned int m_occlusionDelay; // +0x554
};

class Matrix3D
{
public:
    float Row[3][4];
};

class Thing
{
public:
    const ThingTemplate *getTemplate() const { return m_template; }
    void setPosition(const Coord3D *pos);
    const Coord3D *getPosition() const { return &m_pos; }
    const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
    void *m_vtable;
    const ThingTemplate *m_template; // +0x04
    Matrix3D m_transform; // +0x08
    Coord3D m_pos; // +0x38
};

class ConditionBits
{
public:
    unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 31)); }
    void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }
    void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 31)); }
    unsigned int m_words[4];
};

class Object : public Thing
{
public:
    bool clearDisabled(DisabledType type);
    void setStatus(ObjectStatusTypes bit, bool set);
    bool rva0029091E(unsigned int flag) const;
    void setWeaponSetFlag(WeaponSetType type);
    void clearWeaponSetFlag(WeaponSetType type);
    void *rva0028C197() const;
    void setTeam(Team *team);
    Team *getTeam() const { return m_team; }
    void kill(DamageType damageType, DeathType deathType);
    void rva0028AE6D();
    void clearPrivateStatus(unsigned int bits) { m_privateStatus &= ~bits; }
    BodyModuleInterface *getBodyModule() const { return m_body; }
    PhysicsBehavior *getPhysics() const { return m_physics; }
    void setSafeOcclusionFrame(unsigned int frame) { m_safeOcclusionFrame = frame; }
    unsigned char m_pad48[0x10C - 0x44];
    ConditionBits m_conditionBits; // +0x10C
    unsigned char m_pad11C[0x254 - 0x11C];
    BodyModuleInterface *m_body; // +0x254
    unsigned char m_pad258[0x25C - 0x258];
    PhysicsBehavior *m_physics; // +0x25C
    unsigned char m_pad260[0x274 - 0x260];
    void *m_274; // +0x274
    unsigned char m_pad278[0x304 - 0x278];
    Team *m_team; // +0x304
    unsigned char m_pad308[0x380 - 0x308];
    unsigned int m_privateStatus; // +0x380
    unsigned char m_pad384[0x428 - 0x384];
    unsigned int m_safeOcclusionFrame; // +0x428
};

static __forceinline void setCondition(Object *obj, int bit)
{
    if (obj->m_conditionBits.test(bit) == 0)
    {
        obj->m_conditionBits.set(bit);
        obj->rva0028AE6D();
    }
}

static __forceinline void clearCondition(Object *obj, int bit)
{
    ConditionBits *bits = &obj->m_conditionBits;
    if (bits->test(bit))
    {
        bits->clear(bit);
        obj->rva0028AE6D();
    }
}

class Team;
class TeamFactory
{
public:
    Team *findTeamByID(unsigned int id);
};
extern TeamFactory *TheTeamFactory;

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
#define GARRISONCONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\GarrisonContain.cpp"

class Rva00462785
{
public:
    int rva00462785();
};

struct Flags128
{
    bool test(int i) const { return ((m_bits[i >> 5] >> (i & 31)) & 1) != 0; }
    unsigned int m_bits[4];
};

class B0
{
public:
    virtual void b00();
    int pad4;
    Object *m_object;
};
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char pad[12]; };
class B3
{
public:
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void recalcApparentControllingPlayer();
    virtual void c21();
    virtual void onContaining(Object *obj, bool wasSelected);
    virtual void onRemoving(Object *obj);
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28(); virtual void c29(); virtual void c30(); virtual void c31();
    virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
    virtual void c36(); virtual void c37(); virtual void c38(); virtual void c39();
    virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
    virtual Flags128 getFlags(int unused);
    virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
    virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67();
    virtual void d68();
    virtual unsigned int getContainCount(int unused) const;
    virtual void d70(); virtual void d71(); virtual void d72();
    virtual unsigned int getStealthUnitsContained() const;
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
    virtual void onContaining(Object *obj, bool wasSelected);
    virtual void onRemoving(Object *obj);
    Object *getObject() const { return m_object; }
};

class GarrisonContain : public OpenContain
{
public:
    virtual void onRemoving(Object *obj);
protected:
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    unsigned int m_originalTeamID; // +0xFC
    unsigned char m_pad100[0x9DD - 0x100];
    bool m_hideGarrisonedStateFromNonallies; // +0x9DD
};

void GarrisonContain::onRemoving(Object *obj)
{
    const Coord3D *p = obj->getPosition();
    Coord3D pos;
    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;
    OpenContain::onRemoving(obj);
    removeObjectFromGarrisonPoint(obj, -1);
    obj->clearPrivateStatus(1);
    obj->clearDisabled((DisabledType)3);
    obj->setStatus((ObjectStatusTypes)0x3A, false);

    if (getContainCount(0) == 0)
    {
        if (getObject()->getTeam())
        {
            Team *team = TheTeamFactory->findTeamByID(m_originalTeamID);
            if (team)
                getObject()->setTeam(team);
            m_originalTeamID = 0;
        }
        getObject()->setStatus((ObjectStatusTypes)1, false);
        m_hideGarrisonedStateFromNonallies = false;
        clearCondition(getObject(), 10);
    }
    else if (getStealthUnitsContained() != getContainCount(0))
    {
        m_hideGarrisonedStateFromNonallies = false;
    }

    obj->setSafeOcclusionFrame(TheGameLogic->getFrame() + obj->getTemplate()->getOcclusionDelay());

    recalcApparentControllingPlayer();

    if ((unsigned char)((Rva00462785 *)this)->rva00462785() && getObject()->getBodyModule()->getHealth() <= 0.0f)
    {
        if (getFlags(0).test(61))
        {
            TheGameLogic->destroyObject(obj);
        }
        else
        {
            PhysicsBehavior *physics = obj->getPhysics();
            obj->m_274 = 0;
            if (physics)
            {
                obj->setPosition(&pos);
                Coord3D dir;
                dir.x = obj->getTransformMatrix()->Row[0][0];
                dir.y = obj->getTransformMatrix()->Row[1][0];
                int r = GetGameLogicRandomValue(2, 5, GARRISONCONTAIN_SOURCE_FILE, 1626);
                dir.x *= r;
                dir.y *= r;
                dir.z = r;
                physics->rva00390629(true);
                setCondition(obj, 0x7F);
                Coord3D force;
                force.x = dir.x;
                force.y = dir.y;
                force.z = dir.z;
                ((Rva003909FAObj *)physics)->consume(&force, 0, 0);
            }
            if (obj->getTemplate()->isKindOf(90))
            {
                DamageInfo info;
                info.m_damageType = DAMAGE_UNRESISTABLE;
                info.m_deathType = DEATH_NORMAL;
                info.m_sourceID = 0;
                info.m_amount = obj->getBodyModule()->getMaxHealth() * 0.75f;
                obj->getBodyModule()->attemptDamage(&info);
            }
            else
            {
                obj->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
            }
        }
    }

    if (obj->rva0029091E(0x14))
    {
        obj->clearWeaponSetFlag((WeaponSetType)0x14);
        if (ContainSlots *contain = (ContainSlots *)obj->rva0028C197())
        {
            Rva0046247DPair members;
            contain->slot108(members);
            for (_STL::list<Object *>::const_iterator it = members.m04->begin(); it != members.m04->end(); ++it)
            {
                Object *member = *it;
                if (member->rva0029091E(0x14))
                    member->setWeaponSetFlag((WeaponSetType)0x14);
            }
        }
    }
}

