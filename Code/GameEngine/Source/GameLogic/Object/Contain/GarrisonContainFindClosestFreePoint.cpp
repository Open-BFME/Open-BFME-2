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

class Object
{
public:
    const Coord3D *getPosition() const { return &m_pos; }
private:
    unsigned char m_pad00[0x38];
    Coord3D m_pos; // +0x38
};

inline float sqr(float x) { return x * x; }
inline float calcDistSqr(const Coord3D &a, const Coord3D &b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

struct GarrisonPointData
{
    Object *object;
    unsigned int targetID;
    unsigned int placeFrame;
    unsigned char m_pad0C[8];
};

class B0 { public: virtual void b0(); int pad4; Object *m_object; };
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

enum
{
    MAX_GARRISON_POINTS = 40,
    GARRISON_INDEX_INVALID = -1
};

class GarrisonContain : public OpenContain
{
protected:
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *targetPos);
private:
    unsigned char m_padFC[0x100 - sizeof(OpenContain)];
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
    int m_garrisonPointsInUse; // +0x420
    Coord3D m_garrisonPoint[3][MAX_GARRISON_POINTS]; // +0x424
    int m_numGarrisonPoints[3]; // +0x9C4
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
            if (m_garrisonPointData[i].object == 0)
                return i;
        }
        return conditionIndex;
    }

    int closestIndex = GARRISON_INDEX_INVALID;
    float closestDistSq = 3.402823466e+38f;
    for (int i = 0; i < m_numGarrisonPoints[conditionIndex]; ++i)
    {
        if (m_garrisonPointData[i].object == 0)
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

