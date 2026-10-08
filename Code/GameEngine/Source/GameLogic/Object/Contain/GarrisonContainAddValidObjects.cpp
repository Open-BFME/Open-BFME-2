// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// GarrisonContain::addValidObjectsToGarrisonPoints (0x0047894C, 399 bytes),
// after the BFME1/ZH GarrisonContain.cpp body (BFME1 reference revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20).
//
// Target facts: the contain list comes from the pair helper 0x0046247D (its
// second word points at the STLport list, re-read for every end test); an
// empty list returns before the callee-saved pushes. Each occupant with status
// 0x25 (Object::testStatus 0x0004E536) is skipped. An occupant whose +0x250
// contain module answers vtable slot +0x7C with an interface has that
// interface's slot +0x108 fill a second pair, and every member of that list
// with a current weapon (0x0028AEBD) whose +4 field's byte getter (0x002C9400)
// is zero and with an AI at +0x258 is placed: at its current victim
// (0x00268D71), else at its victim position (0x00264E93), else at its own
// position (+0x38) unless bit 61 of the 16-byte mask returned by slot +0xB0 of
// the Contain interface at +0x20 is set (tested twice, through two
// temporaries). An occupant without a contain module is placed the same way
// from its own AI with one mask test. Placement is putObjectAtBestGarrisonPoint
// 0x004785A2.
//
// Carried from the donor: the method name and the victim / victim-position
// order. Structural inference: the twice-tested mask is written as two
// else-if arms with the same placement; the merged-call form allocates the
// zero constant and the member to the registers retail uses, the single
// "a || b" condition swaps them.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <list>

enum ObjectID
{
    INVALID_ID = 0
};
enum ObjectStatusTypes
{
    OBJECT_STATUS_NONE = 0
};
enum WeaponSlotType
{
    PRIMARY_WEAPON = 0
};

class Object;

struct Rva0046247DPair
{
    void *m00;
    const _STL::list<Object *> *m04;
};
class Rva0046247D
{
public:
    void rva0046247D(Rva0046247DPair &p);
};

class Rva002C9400ByteField
{
public:
    unsigned char get() const;
};

class Weapon
{
public:
    bool isWithinAttackRange(const Object *source, const Object *target, float extra = 0.0f, int flag = 1) const;
    char isWithinAttackRange(Object *source, void *pos, float extra = 0.0f, int flag = 1) const;
    Rva002C9400ByteField *getTemplate() const { return m_template; }
private:
    void *m_vt;
    Rva002C9400ByteField *m_template; // +4
};

class AIUpdateInterface
{
public:
    Object *getCurrentVictim() const;
};
class Rva00264E93
{
public:
    void *rva00264E93();
};

class Slot7CIface
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

class ContainIface
{
public:
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28(); virtual void c29(); virtual void c30();
    virtual Slot7CIface *slot7C();
};

class Object
{
public:
    ObjectID getID() const { return m_id; }
    const Coord3D *getPosition() const { return &m_pos; }
    bool testStatus(ObjectStatusTypes bit) const;
    const Weapon *getCurrentWeapon(WeaponSlotType *slot = 0) const;
    ContainIface *getContain() const { return m_contain; }
    AIUpdateInterface *getAI() const { return m_ai; }
private:
    unsigned char m_pad00[0x38];
    Coord3D m_pos; // +0x38
    unsigned char m_pad44[0x74 - 0x44];
    ObjectID m_id; // +0x74
    unsigned char m_pad78[0x250 - 0x78];
    ContainIface *m_contain; // +0x250
    void *m_pad254;
    AIUpdateInterface *m_ai; // +0x258
};

struct Flags128
{
    bool test(int i) const { return ((m_bits[i >> 5] >> (i & 31)) & 1) != 0; }
    unsigned int m_bits[4];
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
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual Flags128 getFlags(int unused);
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
protected:
    void putObjectAtBestGarrisonPoint(Object *obj, Object *target, const Coord3D *targetPos);
    void addValidObjectsToGarrisonPoints();
};

void GarrisonContain::addValidObjectsToGarrisonPoints()
{
    Rva0046247DPair pair;
    ((Rva0046247D *)this)->rva0046247D(pair);
    if (pair.m04->empty())
        return;
    for (_STL::list<Object *>::const_iterator it = pair.m04->begin(); it != pair.m04->end(); ++it)
    {
        Object *obj = *it;
        if (obj->testStatus((ObjectStatusTypes)0x25))
            continue;
        if (ContainIface *contain = obj->getContain())
        {
            Slot7CIface *iface = contain->slot7C();
            if (!iface)
                continue;
            Rva0046247DPair members;
            iface->slot108(members);
            for (_STL::list<Object *>::const_iterator it2 = members.m04->begin(); it2 != members.m04->end(); ++it2)
            {
                Object *member = *it2;
                const Weapon *weapon = member->getCurrentWeapon();
                if (!weapon || weapon->getTemplate()->get())
                    continue;
                AIUpdateInterface *ai = member->getAI();
                if (!ai)
                    continue;
                Object *victim = ai->getCurrentVictim();
                const Coord3D *victimPos = (const Coord3D *)((Rva00264E93 *)ai)->rva00264E93();
                if (victim)
                    putObjectAtBestGarrisonPoint(member, victim, 0);
                else if (victimPos)
                    putObjectAtBestGarrisonPoint(member, 0, victimPos);
                else if (!getFlags(0).test(61))
                    putObjectAtBestGarrisonPoint(member, 0, member->getPosition());
                else if (!getFlags(0).test(61))
                    putObjectAtBestGarrisonPoint(member, 0, member->getPosition());
            }
        }
        else
        {
            AIUpdateInterface *ai = obj->getAI();
            if (!ai)
                continue;
            Object *victim = ai->getCurrentVictim();
            const Coord3D *victimPos = (const Coord3D *)((Rva00264E93 *)ai)->rva00264E93();
            if (victim)
                putObjectAtBestGarrisonPoint(obj, victim, 0);
            else if (victimPos)
                putObjectAtBestGarrisonPoint(obj, 0, victimPos);
            else if (!getFlags(0).test(61))
                putObjectAtBestGarrisonPoint(obj, 0, obj->getPosition());
        }
    }
}

