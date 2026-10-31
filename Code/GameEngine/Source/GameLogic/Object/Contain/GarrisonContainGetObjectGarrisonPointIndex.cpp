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

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef int Int;

struct Rva0046247DPair { void *first; void *second; };

class Rva0046247D { public: void rva0046247D(Rva0046247DPair &result); };

struct Rva0046247DPair;
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

#include "../../../Common/Thing/thing.h"

enum NameKeyType { NK_UNKNOWN = 0 };

class ConditionBits
{
public:
    unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 31)); }
    void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }
private:
    unsigned int m_words[4];
};

class ContainModuleInterface;

// Native trackTargets reads ObjectID at +0x74 and Thing's position at +0x38;
// validateRallyPoint 0x00478141 reads the bounding circle radius at +0xB8;
// redeployOccupants 0x00479395 tests and sets the +0x10C condition bits
// (0x0028AE6D after a set) and getObjectGarrisonPointIndex 0x00479292 reads
// the +0x250 contain interface.
// Only the accessed Object prefix is represented; its full extent is unknown.
class Object : public Thing
{
public:
    ObjectID getID() const { return m_id; }
    float getBoundingCircleRadius() const { return m_boundingCircleRadius; }
    ContainModuleInterface *getContain() const { return m_contain; }
    ConditionBits *getConditionBits() { return &m_conditionBits; }
    void rva0028AE6D();
private:
    unsigned char m_pad60[0x74 - 0x60];
    ObjectID m_id;
    unsigned char m_pad78[0xB8 - 0x78];
    float m_boundingCircleRadius;
    unsigned char m_padBC[0x10C - 0xBC];
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

// One garrison point record: 40 of them at +0x100, 0x14 bytes each (the
// constructor 0x00477F06 zeroes five dwords per record, the matched
// put/remove bodies store the object and target IDs and the place frame).
struct GarrisonPointData
{
	ObjectID objectID;
	ObjectID targetID;
	unsigned int placeFrame;
	unsigned int lastEffectFrame;
	int effect;
};

enum
{
	MAX_GARRISON_POINTS = 40,
	MAX_GARRISON_POINT_CONDITIONS = 3
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

enum BodyDamageType
{
    BODY_PRISTINE = 0,
    BODY_DAMAGED = 1,
    BODY_REALLYDAMAGED = 2,
    BODY_RUBBLE = 3
};

class DamageInfo;

class Weapon;

class ModuleData;

// The garrison point element: a Coord3D with an out-of-line empty ctor and
// dtor (the constructor's __ehvec_ctor and the destructor's vector
// destructor iterator take the ICF-folded 0x0047A6A9 and 0x000B3FD0), unlike
// the plain Coord3D rally point.
struct Rva00477F06GarrisonPoint : public Coord3D
{
	Rva00477F06GarrisonPoint();
	~Rva00477F06GarrisonPoint();
};

// OpenContain's nine vftable-bearing bases, positional. The GarrisonContain
// constructor 0x00477F06 (and the destructor 0x00478067, which restores the
// same tables) stores nine vftables: +0x00 0x00C461F8 (28 slots), +0x0C
// 0x00C43528 (47), +0x10 0x00C46560 (3), +0x20 0x00C46080 (94), +0x24
// 0x00C46064 (6), +0x28 0x00C46F78 (1), +0x2C 0x00C463D8 (4), +0x30
// 0x00C46034 (12) and +0x34 0x00C48B28 (4), and its first own member is
// +0xFC. B0 holds the module's data and object pointers (+0x04, +0x08); B2
// the 12 update bytes before +0x20; B8 OpenContain's data to +0xFC. Only the
// slots a body of this TU needs are declared. The +0x20 table's slot 76 is
// calcBestGarrisonPosition (0x00478547), so B3 introduces it and its
// override is entered with the +0x20 this; the +0x10 table's slot 0 is
// update (0x00479643), so B2 introduces it. B3's unnamed slots are pure
// placeholders (so an emitted table needs no placeholder definition); its
// slots 32 and 35 take the damage-state argument healSingleObject's sibling
// 0x0047876A passes and slot 69 is the contain count it tests. The +0x2C
// table's slot 2 is onBodyDamageStateChange (0x0047876A). The +0x20 table
// holds attemptBestFirePointPosition's position overload 0x004788CE at slot
// 77 and its Object overload 0x00478850 at 78 (overloads go in reverse
// declaration order); the primary table holds redeployOccupants 0x00479395
// at slot 18 and getObjectGarrisonPointIndex 0x00479292 at 27, which
// putObjectAtBestGarrisonPoint 0x004785A2 calls through +0x6C.
class B0
{
public:
    virtual void b0();
    virtual void b01() = 0;
    virtual void b02() = 0;
    virtual void b03() = 0;
    virtual void b04() = 0;
    virtual void b05() = 0;
    virtual void b06() = 0;
    virtual void b07() = 0;
    virtual void b08() = 0;
    virtual void b09() = 0;
    virtual void b10() = 0;
    virtual void b11() = 0;
    virtual void b12() = 0;
    virtual void b13() = 0;
    virtual void b14() = 0;
    virtual void b15() = 0;
    virtual void b16() = 0;
    virtual void b17() = 0;
    virtual void redeployOccupants() = 0;
    virtual void b19() = 0;
    virtual void b20() = 0;
    virtual void b21() = 0;
    virtual void b22() = 0;
    virtual void b23() = 0;
    virtual void b24() = 0;
    virtual void b25() = 0;
    virtual void b26() = 0;
    virtual int getObjectGarrisonPointIndex(ObjectID id) = 0;
    int m_pad4;
    Object *m_object;
};

class B1 { public: virtual void b1(); };

class B2 { public: virtual UpdateSleepTime update() = 0; private: unsigned char m_pad[12]; };

class B3
{
public:
    virtual void c00() = 0;
    virtual void c01() = 0;
    virtual void c02() = 0;
    virtual void c03() = 0;
    virtual void c04() = 0;
    virtual void c05() = 0;
    virtual void c06() = 0;
    virtual void c07() = 0;
    virtual void c08() = 0;
    virtual void c09() = 0;
    virtual void c10() = 0;
    virtual void c11() = 0;
    virtual void c12() = 0;
    virtual void c13() = 0;
    virtual void c14() = 0;
    virtual void c15() = 0;
    virtual void c16() = 0;
    virtual void c17() = 0;
    virtual void c18() = 0;
    virtual void c19() = 0;
    virtual void c20() = 0;
    virtual void c21() = 0;
    virtual void c22() = 0;
    virtual void c23() = 0;
    virtual void c24() = 0;
    virtual void c25() = 0;
    virtual void c26() = 0;
    virtual void c27() = 0;
    virtual void c28() = 0;
    virtual void c29() = 0;
    virtual void c30() = 0;
    virtual void c31() = 0;
    virtual void cSlot32(int) = 0;
    virtual void c33() = 0;
    virtual void c34() = 0;
    virtual void cSlot35(int) = 0;
    virtual void c36() = 0;
    virtual void c37() = 0;
    virtual void c38() = 0;
    virtual void c39() = 0;
    virtual void c40() = 0;
    virtual void c41() = 0;
    virtual void c42() = 0;
    virtual void c43() = 0;
    virtual void c44() = 0;
    virtual void c45() = 0;
    virtual void c46() = 0;
    virtual void c47() = 0;
    virtual void c48() = 0;
    virtual void c49() = 0;
    virtual void c50() = 0;
    virtual void c51() = 0;
    virtual void c52() = 0;
    virtual void c53() = 0;
    virtual void c54() = 0;
    virtual void c55() = 0;
    virtual void c56() = 0;
    virtual void c57() = 0;
    virtual void c58() = 0;
    virtual void c59() = 0;
    virtual void c60() = 0;
    virtual void c61() = 0;
    virtual void c62() = 0;
    virtual void c63() = 0;
    virtual void c64() = 0;
    virtual void c65() = 0;
    virtual void c66() = 0;
    virtual void c67() = 0;
    virtual void c68() = 0;
    virtual unsigned int getContainCount(int unused) const = 0;
    virtual void c70() = 0;
    virtual void c71() = 0;
    virtual void c72() = 0;
    virtual void c73() = 0;
    virtual void c74() = 0;
    virtual void c75() = 0;
    virtual bool calcBestGarrisonPosition(Coord3D *, const Coord3D *);
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos);
};

class B4 { public: virtual void b4(); };

class B5 { public: virtual void b5(); };

class B6
{
public:
    virtual void b6();
    virtual void d01() = 0;
    virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
};

class B7 { public: virtual void b7(); };

class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class Xfer;

// OpenContain's own virtuals as the bodies call them by name: xfer (primary
// slot 3) and loadPostProcess through explicit OpenContain:: calls, and
// removeAllContained, which the matched 0x00478231 calls on its +0x20
// receiver unchanged.
class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
    friend class Rva004697E1Contain;
public:
    OpenContain(Thing *thing, const ModuleData *moduleData);
    virtual ~OpenContain();
    virtual void removeAllContained(bool exposeStealthUnits);
    Object *getObject() const { return m_object; }
protected:
    virtual void xfer(Xfer *xfer);
    virtual void loadPostProcess();
};

// GarrisonContain over the 0xFC-byte OpenContain. Offsets from the matched
// bodies: +0xFC original team id (xfer 0x00478260), +0x100 point records,
// +0x420 points in use, +0x424 the 3x40 garrison points (put 0x00477DA1,
// remove 0x00477E82, calcBestGarrisonPosition 0x00478547), +0x9C4 the
// per-condition point counts (findClosestFreeGarrisonPointIndex 0x00478445),
// +0x9D0 the exit rally point and the +0x9DC/+0x9DD/+0x9DE flags (xfer,
// validateRallyPoint 0x00478141). The primary table 0x00C461F8 holds the
// pool key at slot 4 (0x0047801C).
class GarrisonContain : public OpenContain
{
    friend class Rva00478231;
public:
    GarrisonContain(Thing *thing, const ModuleData *moduleData);
    virtual ~GarrisonContain();
    virtual UpdateSleepTime update();
    virtual NameKeyType getModuleNameKey() const;
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);
    virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);
    virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos);
    virtual int getObjectGarrisonPointIndex(ObjectID id);
protected:
    enum { GARRISON_INDEX_INVALID = -1 };
    virtual void xfer(Xfer *xfer);
    void trackTargets();
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos);
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index);
    void validateRallyPoint();
    void healSingleObject(Object *obj, float framesForFullHeal);
    void putObjectAtBestGarrisonPoint(Object *obj, Object *target, const Coord3D *targetPos);
    virtual void redeployOccupants();
    void addValidObjectsToGarrisonPoints();
    void removeInvalidObjectsFromGarrisonPoints();
private:
    unsigned int m_originalTeamID; // +0xFC
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
    int m_garrisonPointsInUse; // +0x420
    Rva00477F06GarrisonPoint m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS]; // +0x424
    int m_numGarrisonPoints[MAX_GARRISON_POINT_CONDITIONS]; // +0x9C4
    Coord3D m_exitRallyPoint; // +0x9D0
    bool m_garrisonPointsInitialized; // +0x9DC
    bool m_hideGarrisonedStateFromNonallies; // +0x9DD
    bool m_rallyValid; // +0x9DE
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
                for (_STL::list<Object *>::const_iterator it = ((const _STL::list<Object *> *)members.second)->begin(); it != ((const _STL::list<Object *> *)members.second)->end(); ++it)
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
    if (((const _STL::list<Object *> *)contained.second)->size() > 0)
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
