// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// GarrisonContain::onContaining (0x00478C2C, 222 bytes), after the BFME1
// GarrisonContain_onContaining.cpp donor and the ZH GarrisonContain.cpp body
// (BFME1 reference revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20).
//
// Target facts: slot 22 of the +0x20 Contain interface vtable 0x00846080;
// it first calls OpenContain::onContaining 0x00463097 (slot 22 of the
// OpenContain interface vtable 0x008433B0). The rider is held
// (Object::setDisabled 0x00291C9B, type 3) and gets status 0x3A, the
// structure gets status 1 (Object::setStatus 0x0023DB0E), the rider's +0x380
// word gets bit 0 and the rider moves to the structure's position (+0x38,
// Thing::setPosition 0x0030AA80). When bit 61 of the 16-byte mask from
// interface slot +0xB0 is set the rider's drawable (0x005508E2) is hidden
// (0x00271601). After recalcApparentControllingPlayer (slot +0x50), a rider
// passing the 0x14 gate 0x0029091E gets weapon set flag 0x14
// (Object::setWeaponSetFlag 0x00290963), and so does every member of the list
// that its contain interface (0x0028C197, slot +0x108) hands out.
//
// Carried from the donor: the method name, the base call and the order of the
// rider and structure updates. The weapon-set pass has no BFME1/ZH
// counterpart; its shape is read from the target.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
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

class Object;

struct Rva0046247DPair
{
    void *m00;
    const _STL::list<Object *> *m04;
};

class Drawable
{
public:
    void setDrawableHidden(bool hidden);
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

class Thing
{
public:
    Drawable *getDrawable() const;
    void setPosition(const Coord3D *pos);
    const Coord3D *getPosition() const { return &m_pos; }
private:
    unsigned char m_pad00[0x38];
    Coord3D m_pos; // +0x38
};

class Object : public Thing
{
public:
    void setDisabled(DisabledType type);
    void setStatus(ObjectStatusTypes bit, bool set);
    bool rva0029091E(unsigned int flag) const;
    void setWeaponSetFlag(WeaponSetType type);
    void *rva0028C197() const;
    void setPrivateStatus(unsigned int bits) { m_privateStatus |= bits; }
private:
    unsigned char m_pad44[0x380 - 0x44];
    unsigned int m_privateStatus; // +0x380
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
    virtual void onContaining(Object *obj, bool wasSelected);
};

void GarrisonContain::onContaining(Object *obj, bool wasSelected)
{
    OpenContain::onContaining(obj, wasSelected);

    Object *structure = getObject();
    obj->setDisabled((DisabledType)3);
    obj->setStatus((ObjectStatusTypes)0x3A, true);
    structure->setStatus((ObjectStatusTypes)1, true);
    obj->setPrivateStatus(1);
    obj->setPosition(structure->getPosition());

    if (getFlags(0).test(61))
        obj->getDrawable()->setDrawableHidden(true);

    recalcApparentControllingPlayer();

    if (obj->rva0029091E(0x14))
    {
        obj->setWeaponSetFlag((WeaponSetType)0x14);
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

