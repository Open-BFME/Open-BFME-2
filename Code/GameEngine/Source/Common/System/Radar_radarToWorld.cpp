// cl: /DNDEBUG /MD
//
// ?radarToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z,
// retail 0x002D7744, 133 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// matched 152 bytes there): clamp the radar cell into the 128x128 grid,
// scale by the per-axis world sample, then take the terrain height through
// the height view. BFME2 passes the third (normal) argument by default, as
// BFME1 does; the height query takes float x/y (BFME1 BfmeTerrainHeightView)
// and returns a double in st0, and the x87 float round trip in the tail is
// what MSVC emits for those float args (a double-param decl instead emits
// qword traffic and misses).

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

#define NULL 0

class BfmeTerrainHeightView
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual float getGroundHeight(float x, float y, Coord3D *normal = NULL);
};

extern BfmeTerrainHeightView *TheTerrainLogic;

class Radar
{
public:
	bool radarToWorld(const ICoord2D *radar, Coord3D *world);
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);

private:
	unsigned char m_pad[0x24];
	float m_xSample; // +0x24 (retail-measured)
	float m_ySample; // +0x28 (retail-measured)
};

// ?radarToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z
bool Radar::radarToWorld(const ICoord2D *radar, Coord3D *world)
{
	if (radar == NULL || world == NULL)
		return false;

	int x = radar->x;
	int y = radar->y;
	if (x < 0)
		x = 0;
	if (x >= 128)
		x = 128 - 1;
	if (y < 0)
		y = 0;
	if (y >= 128)
		y = 128 - 1;

	world->x = x * m_xSample;
	world->y = y * m_ySample;

	BfmeTerrainHeightView *terrain = TheTerrainLogic;
	world->z = terrain->getGroundHeight(world->x, world->y);

	return true;
}

bool Radar::worldToRadar(const Coord3D *world, ICoord2D *radar)
{
	if (world == NULL || radar == NULL)
		return false;

	radar->x = (int)(world->x / m_xSample);
	radar->y = (int)(world->y / m_ySample);

	if (radar->x < 0)
		radar->x = 0;
	if (radar->x >= 128)
		radar->x = 128 - 1;
	if (radar->y < 0)
		radar->y = 0;
	if (radar->y >= 128)
		radar->y = 128 - 1;

	return true;
}
// ?TheTerrainLogic@@3PAVBfmeTerrainHeightView@@A: the global at VA 0xdfec50 is ?TheTerrainLogic@@3PAVTerrainLogic@@A.
#pragma comment(linker, "/alternatename:?TheTerrainLogic@@3PAVBfmeTerrainHeightView@@A=?TheTerrainLogic@@3PAVTerrainLogic@@A")
