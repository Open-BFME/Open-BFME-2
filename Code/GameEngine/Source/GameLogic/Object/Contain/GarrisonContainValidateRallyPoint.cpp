// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?validateRallyPoint@GarrisonContain@@IAEXXZ, retail 0x00478141, 240 bytes.
// GarrisonContain::validateRallyPoint: exit rally at +0x9D0, valid flag at +0x9DE.
// Donor BFME1 GarrisonContain_validateRallyPoint plus ZH GarrisonContain.cpp
// validateRallyPoint shape: two PartitionManager::findPositionAround calls
// (pin 0x00285202), flags 8, radius at Object+0xB8 scaled by 1.8. Evidence:
// caller 0x00478231 slot 80 of SlaughterHordeContain vtable, layout from
// GarrisonContainXfer (0x9D0/0x9DE) and dtor array 0x424.

typedef unsigned char Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

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

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	float getBoundingCircleRadius() const
	{
		return *(const float *)((const char *)this + 0xB8);
	}
};

class PartitionManager
{
public:
	static bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);
};

class GarrisonContain
{
public:
	Object *getObject() const { return m_object; }

protected:
	void validateRallyPoint();

private:
	void *m_vtbl;
	void *m_moduleData;
	Object *m_object;
	char m_pad[0x9D0 - 0x0C];
	Coord3D m_exitRallyPoint;
	Bool m_garrisonPointsInitialized;
	Bool m_hideGarrisonedStateFromNonallies;
	Bool m_rallyValid;
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
