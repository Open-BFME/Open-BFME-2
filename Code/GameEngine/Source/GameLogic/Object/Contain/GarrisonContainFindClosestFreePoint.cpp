// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// GarrisonContain::findClosestFreeGarrisonPointIndex (0x00478445, 258 bytes),
// after the ZH GeneralsMD GarrisonContain.cpp body of the same name (BFME1
// reference revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20).
//
// Target facts: thiscall, ret 8, entered on the full object (callers
// putObjectAtBestGarrisonPoint 0x004785A2 and calcBestGarrisonPosition
// 0x00478547). It refuses a null position, a full structure (+0x420 == 40)
// and a structure whose in-use count reaches the condition's point count
// (+0x9C4). A target at the structure's own position (+0x08 object, +0x38)
// takes the first free slot of the 0x14-byte point records at +0x100 (or
// returns the condition index when none is free); otherwise it keeps the
// nearest free point by calcDistSqr 0x00478416 over the condition's 0x0C
// coordinates at +0x424, starting from FLT_MAX (0x00BBB8E0).
//
// Carried from the donor: the method and helper names and the nearest-point
// scan. The same-position shortcut, the per-condition point count and the
// FLT_MAX start differ from ZH and are read from the target. Structural
// inference: retail's register choice needs calcDistSqr's body in this TU,
// as in ZH, where it is an inline that /O1 keeps out of line.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/Thing/thing.h"

typedef float Real;

enum ObjectID { INVALID_ID = 0 };

enum NameKeyType { NK_UNKNOWN = 0 };

// Native trackTargets reads ObjectID at +0x74 and Thing's position at +0x38;
// validateRallyPoint 0x00478141 reads the bounding circle radius at +0xB8.
// Only the accessed Object prefix is represented; its full extent is unknown.
class Object : public Thing
{
public:
    ObjectID getID() const { return m_id; }
    float getBoundingCircleRadius() const { return m_boundingCircleRadius; }
private:
    unsigned char m_pad60[0x74 - 0x60];
    ObjectID m_id;
    unsigned char m_pad78[0xB8 - 0x78];
    float m_boundingCircleRadius;
};


template <typename NUM>
inline NUM sqr(NUM x) { return x * x; }

inline Real calcDistSqr(const Coord3D& a, const Coord3D& b)
{
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

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

class Xfer;

// OpenContain's own virtuals as the bodies call them by name: xfer (primary
// slot 3) and loadPostProcess through explicit OpenContain:: calls, and
// removeAllContained, which the matched 0x00478231 calls on its +0x20
// receiver unchanged.
class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
    friend class Rva004697E1Contain;
public:
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
    virtual NameKeyType getModuleNameKey() const;
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);
protected:
    enum { GARRISON_INDEX_INVALID = -1 };
    virtual void xfer(Xfer *xfer);
    void trackTargets();
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos);
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index);
    void validateRallyPoint();
private:
    unsigned int m_originalTeamID; // +0xFC
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
    int m_garrisonPointsInUse; // +0x420
    Coord3D m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS]; // +0x424
    int m_numGarrisonPoints[MAX_GARRISON_POINT_CONDITIONS]; // +0x9C4
    Coord3D m_exitRallyPoint; // +0x9D0
    bool m_garrisonPointsInitialized; // +0x9DC
    bool m_hideGarrisonedStateFromNonallies; // +0x9DD
    bool m_rallyValid; // +0x9DE
};

int GarrisonContain::findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *targetPos)
{
    if (targetPos == 0 || m_garrisonPointsInUse == MAX_GARRISON_POINTS)
        return GARRISON_INDEX_INVALID;
    if (m_garrisonPointsInUse >= m_numGarrisonPoints[conditionIndex])
        return GARRISON_INDEX_INVALID;

    const Coord3D *pos = getObject()->getPosition();
    if (targetPos->x == pos->x && targetPos->y == pos->y && targetPos->z == pos->z)
    {
        for (int i = 0; i < MAX_GARRISON_POINTS; ++i)
        {
            if (m_garrisonPointData[i].objectID == 0)
                return i;
        }
        return conditionIndex;
    }

    int closestIndex = GARRISON_INDEX_INVALID;
    float closestDistSq = 3.402823466e+38f;
    for (int i = 0; i < m_numGarrisonPoints[conditionIndex]; ++i)
    {
        if (m_garrisonPointData[i].objectID == 0)
        {
            float distSq = calcDistSqr(*targetPos, m_garrisonPoint[conditionIndex][i]);
            if (distSq < closestDistSq)
            {
                closestDistSq = distSq;
                closestIndex = i;
            }
        }
    }
    return closestIndex;
}

