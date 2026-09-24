// cl: /O1 /DNDEBUG /MD /EHsc
//
// GlobalData::setTimeOfDay, retail 0x002352BC (86 bytes). Zero Hour's
// GlobalData.cpp body: select one of the five lit times of day and copy its
// three terrain lights into the current ambient/diffuse/position arrays.
// The GlobalData layout below carries only the members this body reaches,
// at the offsets the retail body addresses: m_timeOfDay +0x134, the
// [TIME_OF_DAY_COUNT][MAX_GLOBAL_LIGHTS] TerrainLighting table +0x140
// (0x6C per time of day), and the current arrays +0x8D8/+0x8FC/+0x920.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum TimeOfDay
{
	TIME_OF_DAY_INVALID = 0,
	TIME_OF_DAY_FIRST = 1,
	TIME_OF_DAY_COUNT = 6
};

enum { MAX_GLOBAL_LIGHTS = 3 };

struct RGBColor
{
	Real red, green, blue;
};

struct Coord3D
{
	Real x, y, z;
};

struct TerrainLighting
{
	RGBColor ambient;
	RGBColor diffuse;
	Coord3D lightPos;
};

class GlobalData
{
public:
	Bool setTimeOfDay( TimeOfDay tod );

private:
	unsigned char m_unreconstructed_000[ 0x134 ];
	TimeOfDay m_timeOfDay;
	unsigned char m_unreconstructed_138[ 0x8 ];
	TerrainLighting m_terrainLighting[ TIME_OF_DAY_COUNT ][ MAX_GLOBAL_LIGHTS ];
	unsigned char m_unreconstructed_3c8[ 0x510 ];
	RGBColor m_terrainAmbient[ MAX_GLOBAL_LIGHTS ];
	RGBColor m_terrainDiffuse[ MAX_GLOBAL_LIGHTS ];
	Coord3D m_terrainLightPos[ MAX_GLOBAL_LIGHTS ];
};

// ?setTimeOfDay@GlobalData@@QAE_NW4TimeOfDay@@@Z @0x2352BC
Bool GlobalData::setTimeOfDay( TimeOfDay tod )
{
	if( tod >= TIME_OF_DAY_COUNT || tod < TIME_OF_DAY_FIRST )
	{
		return false;
	}

	m_timeOfDay = tod;
	for (Int i=0; i<MAX_GLOBAL_LIGHTS; i++)
	{	m_terrainAmbient[i] = m_terrainLighting[ tod ][i].ambient;
		m_terrainDiffuse[i] = m_terrainLighting[ tod ][i].diffuse;
		m_terrainLightPos[i] = m_terrainLighting[ tod ][i].lightPos;
	}

	return true;
}
