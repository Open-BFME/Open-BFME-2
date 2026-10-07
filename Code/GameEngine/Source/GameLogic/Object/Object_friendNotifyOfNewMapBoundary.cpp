// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?friend_notifyOfNewMapBoundary@Object@@QAEXXZ,
// retail 0x0028B5EE, 113 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp,
// Object::friend_notifyOfNewMapBoundary): re-adds itself to the radar
// (Radar::addObject), adds to the pathfind map, refreshes the map extent,
// then sets or clears OFF_MAP from the in-region test. Retail keeps the world
// position at +0x38 and the private status byte at +0x438; the in-region test
// inlines to four SSE compares.

#pragma optimize("y", off)

typedef float Real;
typedef int Int;
typedef unsigned char UnsignedByte;
typedef int Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	__forceinline Bool isInRegionNoZ(const Coord3D *query) const
	{
		return (lo.x < query->x) && (query->x < hi.x)
			&& (lo.y < query->y) && (query->y < hi.y);
	}
};

class Object;

class Radar
{
public:
	void addObject(Object *obj);
};

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad[0x10];
	Pathfinder *m_pathfinder; // +0x10
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void getExtent(Region3D *extent) const = 0;
};

extern Radar *TheRadar;
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	void friend_notifyOfNewMapBoundary();
	__forceinline const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x438 - 0x38 - sizeof(Coord3D)];
	UnsignedByte m_privateStatus; // +0x438
};

enum ObjectPrivateStatus
{
	OFF_MAP = 1 << 3
};

// ?friend_notifyOfNewMapBoundary@Object@@QAEXXZ
void Object::friend_notifyOfNewMapBoundary()
{
	TheRadar->addObject(this);
	TheAI->pathfinder()->AddObjectToPathfindMap(this);

	Region3D mapExtent;
	TheTerrainLogic->getExtent(&mapExtent);
	if (mapExtent.isInRegionNoZ(getPosition()))
		m_privateStatus &= ~OFF_MAP;
	else
		m_privateStatus |= OFF_MAP;
}
