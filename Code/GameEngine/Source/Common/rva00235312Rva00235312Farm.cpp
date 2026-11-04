// ?rva00235312@GlobalData@@QAE_NW4TimeOfDay@@0M@Z
// ?rva00235312@GlobalData@@QAE_NW4TimeOfDay@@0M@Z
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// GlobalData blend between two lit times of day; GlobalData::setTimeOfDay
// (0x002352BC) is rowed in GlobalDataSetTimeOfDay.cpp and supplies the
// table/copy guide.
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
	TIME_OF_DAY_INTERPOLATE = 5,
	TIME_OF_DAY_COUNT = 6
};

enum { MAX_GLOBAL_LIGHTS = 3 };
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

struct TerrainLighting
{
	RGBColor ambient;
	RGBColor diffuse;
	Coord3D lightPos;
};

#include "../../Include/Common/GlobalData.h"

// Target1060 blend uses native erroneous red/blue stores; the setTimeOfDay
// donor supplies the table/copy guide only. Original method name is unknown.
Bool GlobalData::rva00235312(TimeOfDay from, TimeOfDay to, Real t)
{
	if (from >= TIME_OF_DAY_COUNT || from < TIME_OF_DAY_FIRST)
		return false;
	if (to >= TIME_OF_DAY_COUNT || to < TIME_OF_DAY_FIRST)
		return false;

	Real inv = (Real)(1.0 - (double)t);
	Int i;
	for (i = 0; i < 3; i++)
	{
		TerrainLighting &terrainLighting = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][0];
		const TerrainLighting &a = m_terrainLighting[from][i];
		const TerrainLighting &b = m_terrainLighting[to][i];
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].ambient.red = a.ambient.red * inv + b.ambient.red * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].ambient.green = a.ambient.green * inv + b.ambient.green * t;
		const volatile Real *blueFrom = &a.ambient.blue;
		const volatile Real *blueTo = &b.ambient.blue;
		Real blueFromValue = *blueFrom;
		Real blueToValue = *blueTo;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].ambient.red = blueFromValue * inv + blueToValue * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = a.diffuse.red * inv + b.diffuse.red * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.green = a.diffuse.green * inv + b.diffuse.green * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = a.diffuse.blue * inv + b.diffuse.blue * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos.x = a.lightPos.x * inv + b.lightPos.x * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos.y = a.lightPos.y * inv + b.lightPos.y * t;
		Real sourceZ = a.lightPos.z;
		Real blendedZ = sourceZ * inv + b.lightPos.z * t;
		m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos.z = blendedZ;

		{
		const TerrainLighting &oa = m_terrainObjectsLighting[from][i];
		const TerrainLighting &ob = m_terrainObjectsLighting[to][i];
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = inv * oa.diffuse.red + t * ob.diffuse.red;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.green = inv * oa.diffuse.green + t * ob.diffuse.green;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = inv * oa.diffuse.blue + t * ob.diffuse.blue;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = inv * oa.diffuse.red + t * ob.diffuse.red;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.green = inv * oa.diffuse.green + t * ob.diffuse.green;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = inv * oa.diffuse.blue + t * ob.diffuse.blue;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos.x = oa.lightPos.x * inv + ob.lightPos.x * t;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos.y = oa.lightPos.y * inv + ob.lightPos.y * t;
		m_terrainObjectsLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos.z = oa.lightPos.z * inv + ob.lightPos.z * t;
		}

		{
		const TerrainLighting &ua = field0650[from][i];
		const TerrainLighting &ub = field0650[to][i];
		field0650[TIME_OF_DAY_INTERPOLATE][i].ambient.red = ua.ambient.red * inv + ub.ambient.red * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].ambient.green = ua.ambient.green * inv + ub.ambient.green * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].ambient.red = ua.ambient.blue * inv + ub.ambient.blue * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = ua.diffuse.red * inv + ub.diffuse.red * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].diffuse.green = ua.diffuse.green * inv + ub.diffuse.green * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].diffuse.red = ua.diffuse.blue * inv + ub.diffuse.blue * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].lightPos.x = ua.lightPos.x * inv + ub.lightPos.x * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].lightPos.y = ua.lightPos.y * inv + ub.lightPos.y * t;
		field0650[TIME_OF_DAY_INTERPOLATE][i].lightPos.z = ua.lightPos.z * inv + ub.lightPos.z * t;
		}
	}

	m_timeOfDay = TIME_OF_DAY_INTERPOLATE;
	for (i = 0; i < MAX_GLOBAL_LIGHTS; i++)
	{
		m_terrainAmbient[i] = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].ambient;
		m_terrainDiffuse[i] = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse;
		m_terrainLightPos[i] = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos;
	}
	return true;
}
