// cl: /DNDEBUG /MD /EHsc
// ?validateRallyPoint@GarrisonContain@@IAEXXZ, retail 0x00478141, 240 bytes.
// GarrisonContain::validateRallyPoint: exit rally at +0x9D0, valid flag at +0x9DE.
// Donor BFME1 GarrisonContain_validateRallyPoint plus ZH GarrisonContain.cpp
// validateRallyPoint shape: two PartitionManager::findPositionAround calls
// (pin 0x00285202), flags 8, radius at Object+0xB8 scaled by 1.8. Evidence:
// caller 0x00478231 slot 80 of SlaughterHordeContain vtable, layout from
// GarrisonContainXfer (0x9D0/0x9DE) and dtor array 0x424.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/Thing/thing.h"

struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}

	unsigned int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	const void *ignoreObject;
	const void *sourceToPathToDest;
	const void *relationshipObject;
};

enum
{
	FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS = 8
};

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


#include "../../../Common/PartitionRangeQueryCallView.h"

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

void GarrisonContain::validateRallyPoint()
{
	if (m_rallyValid == 1)
	{
		Coord3D result;
		FindPositionOptions options;
		options.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS;
		options.minRadius = 0.0f;
		options.maxRadius = 0.0f;
		options.ignoreObject = getObject();
		options.relationshipObject = getObject();
		if (PartitionManager::findPositionAround(&m_exitRallyPoint, &options, &result) == false)
			m_rallyValid = 0;
	}

	if (m_rallyValid == 0)
	{
		FindPositionOptions options;
		options.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS;
		options.minRadius = getObject()->getBoundingCircleRadius();
		options.maxRadius = options.minRadius * 1.8f;
		options.ignoreObject = getObject();
		options.relationshipObject = getObject();
		m_rallyValid = PartitionManager::findPositionAround(getObject()->getPosition(), &options, &m_exitRallyPoint);
	}
}
