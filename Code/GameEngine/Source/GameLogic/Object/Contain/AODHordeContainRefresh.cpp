// cl: /DNDEBUG /MD
//
// ?refreshTrackedLargeUnit@AODHordeContain@@QAEXXZ, retail 0x0047B2AA, 81 bytes.
// Cached large-unit tracker: looks up m_trackedLargeUnit (+0x318) through
// TheGameLogic->findObjectByID (rowed 0x00049DC5); clears the ID when the
// object is gone, else copies its position (+0x38) to +0x320, sets +0x32C to
// 17.0f and +0x330 from GeometryInfo::getMaxHeightAbovePosition (rowed
// 0x006BD7C0 on the object at +0xA8). Layout from the rowed ctor 0x0047B3DB
// (vector at +0x30C, tracked ID at +0x318, position at +0x320, height pair at
// +0x32C/+0x330, factory news 0x8E0); BFME1 donor
// AODHordeContain_trackLargeUnit.cpp gives the find-clear-copy-height concept
// with 17.0f. Unblocks the 0x0047B628 caller. Identity is the AOD offsets
// plus the donor method name.

enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class GeometryInfo;

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xA8 - 0x44];
	GeometryInfo m_geometry;
};

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AODHordeContain
{
public:
	void refreshTrackedLargeUnit();

private:
	unsigned char m_base[0x30C];
	unsigned char m_vectorPad[12];
	ObjectID m_trackedLargeUnit;
	int m_31C;
	Coord3D m_trackedPosition;
	float m_largeUnitHeightFactor;
	float m_largeUnitHeight;
};

// ?refreshTrackedLargeUnit@AODHordeContain@@QAEXXZ
void AODHordeContain::refreshTrackedLargeUnit()
{
	Object *unit = TheGameLogic->findObjectByID(m_trackedLargeUnit);
	if (unit == 0)
	{
		m_trackedLargeUnit = INVALID_ID;
		return;
	}

	m_trackedPosition = unit->m_position;
	m_largeUnitHeightFactor = 17.0f;
	m_largeUnitHeight = unit->m_geometry.getMaxHeightAbovePosition();
}
