// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// ZH GeneralsMD GarrisonContain.cpp::calcBestGarrisonPosition, reviewed
// through BFME1 reference revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20.
// Target 0x00478547..0x004785A2: ret 8, incoming Contain interface at
// +0x20, findConditionIndex 0x00477E50 and closest-free query 0x00478445.
// The coordinate array is at full-object +0x424 with 40 points per condition.
// Source supplies the purpose/name; native calls, copy and offsets establish
// this target's ABI and layout. The base views follow the verified condition
// query's TU; only the interface method used here is declared in B3.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

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

bool GarrisonContain::calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos)
{
    if (!sourcePos || !targetPos)
        return false;
    int conditionIndex = findConditionIndex();
    int placeIndex = findClosestFreeGarrisonPointIndex(conditionIndex, targetPos);
    if (placeIndex == -1)
        return false;
    // The target copies the three words without floating-point arithmetic.
    // Keep the sequential word stores, including their possible overlap.
    const unsigned *point = (const unsigned *)&m_garrisonPoint[conditionIndex][placeIndex];
    unsigned *out = (unsigned *)sourcePos;
    out[0] = point[0];
    out[1] = point[1];
    out[2] = point[2];
    return true;
}
