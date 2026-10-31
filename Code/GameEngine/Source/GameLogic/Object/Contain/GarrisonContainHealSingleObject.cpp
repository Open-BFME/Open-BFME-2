// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// GarrisonContain::healSingleObject: retail 0x004786F8-0x0047876A, 114B.
// Source: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainHealSingleObject.cpp,
// and the canonical ZH healing algorithm. Target sibling 0x00478BE0 walks
// contained objects when the rowed module-data's +0x98 HealObjects flag is set,
// passing +0x9C framesForFullHeal. The constructor is the existing 0x7C
// DamageInfo initializer at 0x00263895. Retail reads body +0x254 and contained
// frame +0x27C, writes damage type 7 / death type 1 / amount at +0x10/+0x1C/+0x20,
// and calls getMaxHealth/attemptHealing through slots +0x18/+0x04. These local
// address-derived views preserve the target ABI without claiming complete layouts.
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva004786F8LogicView { char m_lead[0x40]; unsigned int m_frame; };
class DamageInfo {
public:
    DamageInfo();
    char m_lead[0x10];
    int m_damageType;
    char m_gap[8];
    int m_deathType;
    float m_amount;
    char m_tail[0x7c-0x24];
};
class Rva00263895Member {
public:
    Rva00263895Member();
    char m_lead[0x10];
    int m_damageType;
    char m_gap[8];
    int m_deathType;
    float m_amount;
    char m_tail[0x7c-0x24];
};
class Rva004786F8Body {
public:
    virtual void slot00();
    virtual void attemptHealing(DamageInfo*);
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual float getMaxHealth() const;
};
struct Rva004786F8TemplateView {
    char m_lead[0x111];
    unsigned char m_kindof111;
};
struct Rva004786F8ObjectView {
    char m_lead00[4];
    const Rva004786F8TemplateView* m_template;
    char m_lead08[0x254-8];
    Rva004786F8Body* m_body;
    char m_gap[0x24];
    unsigned int m_containedByFrame;
};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Thing;

enum ObjectID { INVALID_ID = 0 };

enum NameKeyType { NK_UNKNOWN = 0 };

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
// table's slot 2 is onBodyDamageStateChange (0x0047876A).
class B0 { public: virtual void b0(); int m_pad4; Object *m_object; };

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
void GarrisonContain::healSingleObject(Object* object,float framesForFullHeal) {
    Rva00263895Member healInfo;
    healInfo.m_damageType=7;
    healInfo.m_deathType=1;
    Rva004786F8ObjectView* view=(Rva004786F8ObjectView*)object;
    Rva004786F8Body* body=view->m_body;
    if(((Rva004786F8LogicView*)TheGameLogic)->m_frame-view->m_containedByFrame >= framesForFullHeal)
        healInfo.m_amount=body->getMaxHealth();
    else
        healInfo.m_amount=body->getMaxHealth()/framesForFullHeal;
    body->attemptHealing((DamageInfo*)&healInfo);
}
void GarrisonContain::onBodyDamageStateChange(const DamageInfo*, BodyDamageType, BodyDamageType newState) {
    if(newState == BODY_REALLYDAMAGED && !(((const Rva004786F8TemplateView*)((const Rva004786F8ObjectView*)m_object)->m_template)->m_kindof111 & 0x80)) {
        if(getContainCount(0) > 0) {
            cSlot35(2);
            cSlot32(2);
        }
    }
}
