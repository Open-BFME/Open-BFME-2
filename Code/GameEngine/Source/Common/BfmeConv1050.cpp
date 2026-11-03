// Open-BFME5 conversions.

class PartitionManagerImpl
{
public:
	void *GetClosestObject(int position, float radius, int bounds, int distType, int filters);
};

class BfmeC1050
{
public:
	void bfmeGo1050C(int positionAddress, int b, int radiusBits, int distanceType, int filtersAddress);
	void bfmeGo009F26D0(int positionAddress, int b, int radiusBits, int distanceType);

	char m_bfmePad[0x10]; // BFME2 target at 0x625390 loads this pointer at +0x10.
	PartitionManagerImpl *m_bfmeP;
};

void BfmeC1050::bfmeGo1050C(int positionAddress, int b, int radiusBits, int distanceType, int filtersAddress)
{
	m_bfmeP->GetClosestObject(positionAddress, *(const float *)&radiusBits, b, distanceType, filtersAddress);
}

struct Coord3D;
class Object;
class Rva000421C8;	// the partition filter base (ctor 0x000421C8)

// ThePartitionManager (0x00DFE748): 26 matched callers reference this
// method by name. BFME1 retail 0x009F26A0 is the same four-argument
// wrapper with an explicit 0 in the third slot.
class PartitionManager
{
	char m_pad[0x10];
	PartitionManagerImpl *m_impl;

public:
	Object *getClosestObject(const Coord3D *position, float radius, int distanceType,
		Rva000421C8 *filters);
};

Object *PartitionManager::getClosestObject(const Coord3D *position, float radius, int distanceType,
	Rva000421C8 *filters)
{
	return (Object *)m_impl->GetClosestObject((int)position, radius, 0, distanceType, (int)filters);
}

void BfmeC1050::bfmeGo009F26D0(int positionAddress, int b, int radiusBits, int distanceType)
{
	m_bfmeP->GetClosestObject(positionAddress, *(const float *)&radiusBits, b, distanceType, 0);
}

// 0x0013C740 is GridEnvironmentMapperClass(const INIClass &, const char *, unsigned),
// rowed from vertmaterial.cpp, whose inline ctor copy is retail's.
