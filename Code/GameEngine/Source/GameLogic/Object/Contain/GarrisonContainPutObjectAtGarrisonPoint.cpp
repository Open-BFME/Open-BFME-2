// cl: /DNDEBUG /MD /EHsc
// ?putObjectAtGarrisonPoint@GarrisonContain@@IAEXPAVObject@@W4ObjectID@@HH@Z @0x00477DA1 175B.
// GarrisonContain placement sibling of removeObjectFromGarrisonPoint 0x00477E82.
// Evidence: BFME1 donor GarrisonContain.cpp putObjectAtGarrisonPoint same
// null plus 0x28 plus 3 bounds plus occupied check plus points[cond][point]
// copy plus setPosition row plus ID stores plus TheGameLogic frame plus inc;
// layout plus-0x100 data plus-0x420 count plus-0x424 points from remove TU.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/Thing/thing.h"
enum ObjectID { INVALID_ID = 0 };

enum NameKeyType { NK_UNKNOWN = 0 };

// Native trackTargets reads ObjectID at +0x74 and Thing's position at +0x38.
// Only the accessed Object prefix is represented; its full extent is unknown.
class Object : public Thing
{
public:
    ObjectID getID() const { return m_id; }
private:
    unsigned char m_pad60[0x74 - 0x60];
    ObjectID m_id;
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicFrameView
{
    char m_pad[0x40];
    unsigned int m_frame;
};
// One garrison point record: 40 of them at +0x100, 0x14 bytes each (the
// constructor 0x00477F06 zeroes five dwords per record, the matched
// put/remove bodies store the object and target IDs and the place frame).
struct GarrisonPointData
{
	ObjectID objectID;
	ObjectID targetID;
	unsigned int placeFrame;
	unsigned int lastEffectFrame;
	void *effect;
};

enum
{
	MAX_GARRISON_POINTS = 40,
	MAX_GARRISON_POINT_CONDITIONS = 3
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
// override is entered with the +0x20 this.
class B0 { public: virtual void b0(); int m_pad4; Object *m_object; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual bool calcBestGarrisonPosition(Coord3D *, const Coord3D *); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
    friend class Rva004697E1Contain;
public:
    virtual ~OpenContain();
protected:
    virtual void loadPostProcess();
};

// GarrisonContain over the 0xFC-byte OpenContain. Offsets from the matched
// bodies: +0xFC original team id (xfer 0x00478260), +0x100 point records,
// +0x420 points in use, +0x424 the 3x40 garrison points (put 0x00477DA1,
// remove 0x00477E82, calcBestGarrisonPosition 0x00478547). The primary
// table 0x00C461F8 holds the pool key at slot 4 (0x0047801C).
class GarrisonContain : public OpenContain
{
public:
    virtual NameKeyType getModuleNameKey() const;
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);
protected:
    enum { GARRISON_INDEX_INVALID = -1 };
    void trackTargets();
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos);
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index);
private:
    unsigned int m_originalTeamID; // +0xFC
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
    int m_garrisonPointsInUse; // +0x420
    Coord3D m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS]; // +0x424
};
void GarrisonContain::putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int pointIndex)
{
    if (obj == 0 || pointIndex < 0 || pointIndex >= MAX_GARRISON_POINTS
        || conditionIndex < 0 || conditionIndex >= MAX_GARRISON_POINT_CONDITIONS) {
        return;
    }
    if (m_garrisonPointData[pointIndex].objectID != 0) {
        return;
    }
    const Coord3D &pt = m_garrisonPoint[conditionIndex][pointIndex];
    Coord3D pos;
    pos.x = pt.x;
    pos.y = pt.y;
    pos.z = pt.z;
    obj->setPosition(&pos);
    m_garrisonPointData[pointIndex].objectID = (ObjectID)obj->getID();
    m_garrisonPointData[pointIndex].targetID = targetID;
    m_garrisonPointData[pointIndex].placeFrame = ((GameLogicFrameView *)TheGameLogic)->m_frame;
    ++m_garrisonPointsInUse;
}
