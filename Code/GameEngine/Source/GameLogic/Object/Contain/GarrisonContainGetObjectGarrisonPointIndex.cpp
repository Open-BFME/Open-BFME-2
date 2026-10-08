// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// GarrisonContain::getObjectGarrisonPointIndex (0x00479292, 170 bytes, ret 4),
// after Zero Hour's GarrisonContain::getObjectGarrisonPointIndex
// (GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp).
//
// Target facts: BFME 2 takes an ObjectID (full-object vtable slot +0x6C),
// returns -1 for INVALID_ID or when TheGameLogic->findObjectByID (0x00049DC5)
// finds nothing, then walks the 40 0x14-byte garrison point records at +0x100.
// For each pass it reads the object's contain module at Object +0x250; with no
// contain it compares the record's ObjectID; with one it asks contain slot
// +0x7C for the horde interface and, when present, fetches the member pair
// through horde slot +0x108 (the same call GarrisonContain::onRemoving
// 0x00478D0A makes) and returns the first record index whose ObjectID equals
// a member's ID at Object +0x74. Carried from the donor: the method name, the
// record walk and the -1 sentinel. The member list is STLport's
// list<Object *>, whose sentinel the pair's second word points to.
//
// GarrisonContain::redeployOccupants (0x00479395, 157 bytes), slot 18 of the
// primary vtable 0x008461F8, after BFME1's GarrisonContain_redeployOccupants.cpp
// donor and Zero Hour's body. Target facts: it fetches the contained-list pair
// from 0x0046247D on the unadjusted this and, when the STLport list at its
// second word is non-empty, sets model condition 10 on the owner (word +0x10C,
// mask 0x400; notifier 0x0028AE6D when it was clear). It then copies the 40
// garrison records (rep movsd, 0xC8 dwords), calls
// removeInvalidObjectsFromGarrisonPoints 0x0047933C and
// addValidObjectsToGarrisonPoints 0x0047894C, and restores each surviving
// occupant's place frame (+0x08) at the index slot +0x6C now reports. Carried
// from the donor: the method name, the condition refresh and the
// snapshot/remove/add/restore order. 0x0047933C is named from that order (it is
// the call between the snapshot and addValidObjectsToGarrisonPoints, as in the
// donor), and its body walks the records through removeObjectFromGarrisonPoint
// 0x00477E82.
#include "../../../Common/GameLogicObjectLookupView.h"
#include <list>

typedef int Int;

struct Rva0046247DPair
{
    void *m00;
    const _STL::list<Object *> *m04;
};

class Rva0046247D
{
public:
    void rva0046247D(Rva0046247DPair &result);
};

class HordeContainInterface
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
    virtual Rva0046247DPair &slot108(Rva0046247DPair &p); // +0x108
};

class ContainModuleInterface
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
    virtual HordeContainInterface *getHordeContainInterface(); // +0x7C
};

class ConditionBits
{
public:
    unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 31)); }
    void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }
private:
    unsigned int m_words[4];
};

class Object
{
public:
    ObjectID getID() const { return m_id; }
    ContainModuleInterface *getContain() const { return m_contain; }
    void rva0028AE6D();
    ConditionBits *getConditionBits() { return &m_conditionBits; }
private:
    unsigned char m_pad000[0x74];
    ObjectID m_id; // +0x74
    unsigned char m_pad078[0x10C - 0x78];
    ConditionBits m_conditionBits; // +0x10C
    unsigned char m_pad11C[0x250 - 0x11C];
    ContainModuleInterface *m_contain; // +0x250
};

static __forceinline void setCondition(Object *obj, int bit)
{
    ConditionBits *bits = obj->getConditionBits();
    if (bits->test(bit) == 0)
    {
        bits->set(bit);
        obj->rva0028AE6D();
    }
}

extern GameLogic *TheGameLogic;

enum
{
    MAX_GARRISON_POINTS = 40,
    GARRISON_INDEX_INVALID = -1
};

struct GarrisonPointData
{
    ObjectID objectID; // +0x00
    ObjectID targetID; // +0x04
    unsigned int placeFrame; // +0x08
    unsigned int lastEffectFrame; // +0x0C
    void *effect; // +0x10
};

class B0
{
public:
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
    virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15();
    virtual void b16(); virtual void b17();
    virtual void redeployOccupants();
    virtual void b19();
    virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23();
    virtual void b24(); virtual void b25(); virtual void b26();
    virtual Int getObjectGarrisonPointIndex(ObjectID id);
    int pad4;
    Object *m_object;
};
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
    Object *getObject() const { return m_object; }
};

class GarrisonContain : public OpenContain
{
public:
    virtual Int getObjectGarrisonPointIndex(ObjectID id);
protected:
    virtual void redeployOccupants();
    void addValidObjectsToGarrisonPoints();
    void removeInvalidObjectsFromGarrisonPoints();
private:
    ObjectID m_originalTeamID; // +0xFC
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
};

Int GarrisonContain::getObjectGarrisonPointIndex(ObjectID objectID)
{
    if (objectID == INVALID_OBJECT_ID)
        return GARRISON_INDEX_INVALID;

    Object *object = TheGameLogic->findObjectByID(objectID);
    if (object == 0)
        return GARRISON_INDEX_INVALID;

    for (Int i = 0; i < MAX_GARRISON_POINTS; ++i)
    {
        ContainModuleInterface *contain = object->getContain();
        if (contain != 0)
        {
            HordeContainInterface *horde = contain->getHordeContainInterface();
            if (horde != 0)
            {
                Rva0046247DPair members;
                horde->slot108(members);
                for (_STL::list<Object *>::const_iterator it = members.m04->begin(); it != members.m04->end(); ++it)
                {
                    Object *member = *it;
                    for (Int j = 0; j < MAX_GARRISON_POINTS; ++j)
                    {
                        if (m_garrisonPointData[j].objectID == member->getID())
                            return j;
                    }
                }
            }
        }
        else if (m_garrisonPointData[i].objectID == objectID)
        {
            return i;
        }
    }
    return GARRISON_INDEX_INVALID;
}

void GarrisonContain::redeployOccupants()
{
    Rva0046247DPair contained;
    reinterpret_cast<Rva0046247D *>(this)->rva0046247D(contained);
    if (contained.m04->size() > 0)
        setCondition(getObject(), 10);

    GarrisonPointData garrisonPointDataCopy[MAX_GARRISON_POINTS];
    Int i;

    // copy the current set of garrison point data sets
    for (i = 0; i < MAX_GARRISON_POINTS; ++i)
        garrisonPointDataCopy[i] = m_garrisonPointData[i];

    removeInvalidObjectsFromGarrisonPoints();
    addValidObjectsToGarrisonPoints();

    // restore the frame markers that things were recorded as entering their point
    Int index;
    for (i = 0; i < MAX_GARRISON_POINTS; ++i)
    {
        if (garrisonPointDataCopy[i].objectID)
        {
            index = getObjectGarrisonPointIndex(garrisonPointDataCopy[i].objectID);
            if (index != GARRISON_INDEX_INVALID)
                m_garrisonPointData[index].placeFrame = garrisonPointDataCopy[i].placeFrame;
        }
    }
}
