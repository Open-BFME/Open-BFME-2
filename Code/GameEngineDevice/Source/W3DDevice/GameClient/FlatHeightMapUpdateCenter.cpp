// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva000E3CE1@Rva000E3B41@@QAEXABVRva000E3A8D@@H@Z
// retail 0x000E3CE1..0x000E43CE (1773 bytes) thiscall ret 8; its only
// reference is the vtable entry at 0x007CE9A0. It overrides the
// BaseHeightMapRenderObjClass update-list fan-out (rowed 0x00069CE6, which it
// calls with the same two arguments) in the terrain render object whose
// destructor family is rowed under Rva000E3B41 (0x000E3CC5). It is BFME 2's
// tiled (flat) height map update: with the byte at 0x00DFE7A8 set it only
// forwards to the base; otherwise it marks the cameras moved when their
// count or TheGlobalData's +0xEA0 word changed or a camera moved more than
// 20 units (squared length 400) from the position cached in the Vector3
// vector at +0x38C4 (resized through the rowed 0x00082C98 and refilled from
// RenderObjClass::Get_Position), runs the base, copies the camera list to
// +0x38B4 (rowed 0x000E3A8D), clears +0x37D4, updates every 0xD4-byte
// W3DTerrainBackground tile (rowed updateCenter 0x0011234C and 0x00111FBC
// into the 8-byte tile records at +0x3884) while tracking the visible tile
// bounds (+0x3898..+0x38A4), hands each tile its four neighbours' texture
// multipliers and whether any of them is culled (rowed 0x00115DA7), and,
// when +0x38A8 is set, searches the distance (+0x38B0) that keeps the number
// of near visible tiles at the map-derived budget (+0x38AC). WorldBuilder
// twin 0x007B8610 (W3D terrain source, vector3.h asserts) has the same
// statements: the four neighbour indices, the chained zero of the four
// multipliers and the nine edge cases. Names are address-derived.
// Callee spellings: the cached positions are resized with the default
// (uninitialised) Vector3 passed by value (retail reserves 12 bytes with no
// stores), so the placeholder row 0x00082C98 is called as
// ?rva00082C98@Rva00082C98Host@@QAEXIVVector3@@@Z; the neighbour setter
// 0x00115DA7 receives the culled flag as a bool (the whole dword of the byte
// local is pushed), so it is called as
// ?rva00115DA7@Rva00115DA7@@QAEXHHHH_N@Z. Both need pins at those addresses.

#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

class Vector3
{
public:
	Vector3() {}
	Vector3(const Vector3 &vec) { X = vec.X; Y = vec.Y; Z = vec.Z; }
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &vec) { X = vec.X; Y = vec.Y; Z = vec.Z; return *this; }
	Real Length2(void) const { return X * X + Y * Y + Z * Z; }
	friend Vector3 operator-(const Vector3 &a, const Vector3 &b)
	{
		return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}
	Real X, Y, Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position(void) const;
};

// The camera list (a vector of render objects) and its rowed assignment.
class Rva000E3A8D : public _STL::vector<RenderObjClass *>
{
public:
	Rva000E3A8D &rva000E3A8D(const Rva000E3A8D &other);
};

// The cached camera positions: a Vector3 vector whose rowed resize takes
// the fill value by value.
class Rva00082C98Host : public _STL::vector<Vector3>
{
public:
	void rva00082C98(unsigned int newSize, Vector3 value);
};


class Rva00112230CameraGroup;

class W3DTerrainBackground
{
public:
	void updateCenter(const Rva00112230CameraGroup &cameras);

	Bool isCulled(Int camera = -1) const
	{
		if (camera >= 0 && camera < 3)
			return m_cullStatus[camera] == 2;
		for (Int i = 0; i < 3; i++)
		{
			if (m_cullStatus[i] == 1)
				return false;
		}
		return true;
	}

	Int m_cullStatus[3];
	unsigned char m_pad0C[0x64 - 0x0C];
	Real m_distance;	// +0x64
	unsigned char m_pad68[0xD4 - 0x68];
};

class Rva00111F0E
{
public:
	Int rva00111FBC(unsigned char *culled);
};

class Rva00115DA7
{
public:
	void rva00115DA7(Int left, Int down, Int right, Int up, Bool culled);

private:
	unsigned char m_pad00[0xA8];
	Int m_leftA8;
	unsigned char m_padAC[0xB0 - 0xAC];
	Int m_downB0;
	unsigned char m_padB4[0xB8 - 0xB4];
	Int m_rightB8;
	unsigned char m_padBC[0xC0 - 0xBC];
	Int m_upC0;
};

// ?Rva00115DA7::rva00115DA7 present-unmatched
// Retail 0x00115DA7 (37B body, 43B extent): stores the four edge ints;
// the culled flag is accepted for the ret-0x14 ABI but not stored. This
// HHHH_N spelling is what FlatHeightMapUpdateCenter's rowed caller
// references (a Bool fifth arg widens to the same dword, but spelling it
// Int reshapes the caller's frame, so the reference must keep this
// spelling). The identical body is rowed as HHHHH from Rva00115DA7.cpp;
// the two COMDATs fold at link. Verified exact via explain_mismatch.
void Rva00115DA7::rva00115DA7(Int left, Int down, Int right, Int up, Bool culled)
{
	m_leftA8 = left;
	m_downB0 = down;
	m_rightB8 = right;
	m_upC0 = up;
}

struct TileRecord
{
	Int m_texMultiplier;
	Bool m_culled;
};

class WorldHeightMap
{
public:
	unsigned char m_pad0[0x120E8];
	Int m_width;	// +0x120E8
	Int m_height;	// +0x120EC
};

class BaseHeightMapRenderObjClass
{
public:
	void rva00069CE6(const Rva000E3A8D &cameras, Int arg);
};

class GlobalData
{
public:
	unsigned char m_pad0[0xEA0];
	Int m_ea0;	// +0xEA0
};
extern GlobalData *TheWritableGlobalData;

extern unsigned char g_00DFE7A8;

class Rva000E3B41
{
public:
	void rva000E3CE1(const Rva000E3A8D &cameras, Int arg);

private:
	unsigned char m_pad0000[0x37C0];
	WorldHeightMap *m_map;	// +0x37C0
	unsigned char m_pad37C4[0x37D4 - 0x37C4];
	Bool m_needFullUpdate;	// +0x37D4
	unsigned char m_pad37D5[0x3884 - 0x37D5];
	TileRecord *m_tileRecords;	// +0x3884
	W3DTerrainBackground *m_tiles;	// +0x3888
	Int m_numTiles;	// +0x388C
	Int m_tilesWidth;	// +0x3890
	Int m_tilesHeight;	// +0x3894
	Int m_minX;	// +0x3898
	Int m_minY;	// +0x389C
	Int m_maxX;	// +0x38A0
	Int m_maxY;	// +0x38A4
	Bool m_limitTiles;	// +0x38A8
	Int m_tileBudget;	// +0x38AC
	Real m_tileDistance;	// +0x38B0
	Rva000E3A8D m_cameras;	// +0x38B4
	Bool m_camerasMoved;	// +0x38C0
	Rva00082C98Host m_cameraPositions;	// +0x38C4
	unsigned char m_pad38D0[0x3934 - 0x38D0];
	Int m_updateState;	// +0x3934
};

void Rva000E3B41::rva000E3CE1(const Rva000E3A8D &cameras, Int arg)
{
	if (g_00DFE7A8)
	{
		((BaseHeightMapRenderObjClass *)this)->rva00069CE6(cameras, arg);
	}
	else
	{
	if (cameras.size() != m_cameraPositions.size() || TheWritableGlobalData->m_ea0 != 0)
	{
		m_camerasMoved = true;
	}
	else
	{
		for (unsigned int cameraIndex = 0; cameraIndex < cameras.size() && !m_camerasMoved; cameraIndex++)
		{
			Vector3 oldPos = m_cameraPositions[cameraIndex];
			RenderObjClass *camera = cameras[cameraIndex];
			if ((oldPos - camera->Get_Position()).Length2() > 400.0f)
				m_camerasMoved = true;
		}
	}

	m_cameraPositions.rva00082C98(cameras.size(), Vector3());
	for (unsigned int cameraIndex = 0; cameraIndex < cameras.size(); cameraIndex++)
	{
		RenderObjClass *camera = cameras[cameraIndex];
		m_cameraPositions[cameraIndex] = camera->Get_Position();
	}

	((BaseHeightMapRenderObjClass *)this)->rva00069CE6(cameras, arg);
	m_cameras.rva000E3A8D(cameras);

	m_needFullUpdate = false;
	m_maxX = 0;
	m_maxY = 0;
	m_minX = m_tilesWidth * 16;
	m_minY = m_tilesHeight * 16;

	Int i, j;
	for (i = 0; i < m_tilesWidth; i++)
	{
		for (j = 0; j < m_tilesHeight; j++)
		{
			W3DTerrainBackground *tile = m_tiles + j * m_tilesWidth + i;
			tile->updateCenter(*(const Rva00112230CameraGroup *)&cameras);
			Bool culled;
			Int texMultiplier = ((Rva00111F0E *)tile)->rva00111FBC((unsigned char *)&culled);
			m_tileRecords[j * m_tilesWidth + i].m_texMultiplier = texMultiplier;
			m_tileRecords[j * m_tilesWidth + i].m_culled = culled;
			if (!tile->isCulled())
			{
				Int minX = i * 16;
				Int maxX = minX + 16;
				Int minY = j * 16;
				Int maxY = minY + 16;
				if (m_maxX < maxX)
					m_maxX = maxX;
				if (m_maxY < maxY)
					m_maxY = maxY;
				if (m_minX > minX)
					m_minX = minX;
				if (m_minY > minY)
					m_minY = minY;
			}
		}
	}

	for (i = 0; i < m_tilesWidth; i++)
	{
		for (j = 0; j < m_tilesHeight; j++)
		{
			W3DTerrainBackground *tile = m_tiles + j * m_tilesWidth + i;
			Int leftIdx = j * m_tilesWidth + i - 1;
			Int downIdx = (j + 1) * m_tilesWidth + i;
			Int rightIdx = j * m_tilesWidth + i + 1;
			Int upIdx = (j - 1) * m_tilesWidth + i;
			Int left, down, right, up;
			left = down = right = up = 0;
			Bool culled = false;
			if (i == 0)
			{
				if (j == 0)
				{
					down = m_tileRecords[downIdx].m_texMultiplier;
					right = m_tileRecords[rightIdx].m_texMultiplier;
					culled = m_tileRecords[downIdx].m_culled || m_tileRecords[rightIdx].m_culled;
				}
				else if (j == m_tilesHeight - 1)
				{
					right = m_tileRecords[rightIdx].m_texMultiplier;
					up = m_tileRecords[upIdx].m_texMultiplier;
					culled = m_tileRecords[rightIdx].m_culled || m_tileRecords[upIdx].m_culled;
				}
				else
				{
					down = m_tileRecords[downIdx].m_texMultiplier;
					right = m_tileRecords[rightIdx].m_texMultiplier;
					up = m_tileRecords[upIdx].m_texMultiplier;
					culled = m_tileRecords[downIdx].m_culled || m_tileRecords[rightIdx].m_culled || m_tileRecords[upIdx].m_culled;
				}
			}
			else if (i == m_tilesWidth - 1)
			{
				if (j == 0)
				{
					left = m_tileRecords[leftIdx].m_texMultiplier;
					down = m_tileRecords[downIdx].m_texMultiplier;
					culled = m_tileRecords[leftIdx].m_culled || m_tileRecords[downIdx].m_culled;
				}
				else if (j == m_tilesHeight - 1)
				{
					left = m_tileRecords[leftIdx].m_texMultiplier;
					up = m_tileRecords[upIdx].m_texMultiplier;
					culled = m_tileRecords[leftIdx].m_culled || m_tileRecords[upIdx].m_culled;
				}
				else
				{
					left = m_tileRecords[leftIdx].m_texMultiplier;
					down = m_tileRecords[downIdx].m_texMultiplier;
					up = m_tileRecords[upIdx].m_texMultiplier;
					culled = m_tileRecords[leftIdx].m_culled || m_tileRecords[downIdx].m_culled || m_tileRecords[upIdx].m_culled;
				}
			}
			else
			{
				if (j == 0)
				{
					left = m_tileRecords[leftIdx].m_texMultiplier;
					down = m_tileRecords[downIdx].m_texMultiplier;
					right = m_tileRecords[rightIdx].m_texMultiplier;
					culled = m_tileRecords[leftIdx].m_culled || m_tileRecords[downIdx].m_culled || m_tileRecords[rightIdx].m_culled;
				}
				else if (j == m_tilesHeight - 1)
				{
					left = m_tileRecords[leftIdx].m_texMultiplier;
					right = m_tileRecords[rightIdx].m_texMultiplier;
					up = m_tileRecords[upIdx].m_texMultiplier;
					culled = m_tileRecords[leftIdx].m_culled || m_tileRecords[rightIdx].m_culled || m_tileRecords[upIdx].m_culled;
				}
				else
				{
					left = m_tileRecords[leftIdx].m_texMultiplier;
					down = m_tileRecords[downIdx].m_texMultiplier;
					right = m_tileRecords[rightIdx].m_texMultiplier;
					up = m_tileRecords[upIdx].m_texMultiplier;
					culled = m_tileRecords[leftIdx].m_culled || m_tileRecords[downIdx].m_culled || m_tileRecords[rightIdx].m_culled || m_tileRecords[upIdx].m_culled;
				}
			}
			((Rva00115DA7 *)tile)->rva00115DA7(left, down, right, up, culled);
		}
	}

	if (m_limitTiles)
	{
		Int budget = (m_map->m_width / 16) * m_map->m_height / 16;
		Int needed = (m_map->m_width / 16 + 1) * (m_map->m_height / 16 + 1);
		if (needed < m_numTiles)
		{
			m_tileBudget = budget;
			Real nearDist = 0;
			Real farDist = 500.0f;
			Int inRange = 0;
			Int visible = 0;
			do
			{
				W3DTerrainBackground *tile = m_tiles;
				inRange = 0;
				visible = 0;
				for (Int k = m_numTiles; k > 0; k--)
				{
					if (!tile->isCulled())
					{
						visible++;
						if (tile->m_distance < farDist)
							inRange++;
					}
					tile++;
				}
				if (visible < m_tileBudget)
				{
					m_tileBudget = m_numTiles;
					break;
				}
				if (inRange < m_tileBudget)
				{
					nearDist = farDist;
					farDist *= 2.0f;
				}
			} while (inRange < m_tileBudget);
			if (m_tileBudget < m_numTiles)
			{
				m_tileDistance = nearDist;
				for (Int iter = 0; iter < 20; iter++)
				{
					inRange = 0;
					Real dist = (nearDist + farDist) / 2.0f;
					W3DTerrainBackground *tile = m_tiles;
					for (Int k = m_numTiles; k > 0; k--)
					{
						if (!tile->isCulled() && tile->m_distance < dist)
							inRange++;
						tile++;
					}
					if (inRange == m_tileBudget)
					{
						m_tileDistance = dist;
						break;
					}
					if (inRange > m_tileBudget)
					{
						farDist = dist;
					}
					else
					{
						nearDist = dist;
						m_tileDistance = dist;
					}
				}
			}
		}
		else
		{
			m_tileBudget = m_numTiles;
		}
	}

	m_updateState = 3;
	}
}

// Rowed-var linkage for the resize callee: the erase/fillInsert the Clamp
// twin (Rva00082C98Clamp.cpp, rowed IHHH 73B at this same address) calls.
// vector<Coord3D> is layout-identical to this TU's vector<Vector3> (three
// pointers over 12-byte trivial elements), so the calls bind the rowed
// 0x00081A24/0x00082719 bodies. Both callees are declared-only (no
// definition visible, so nothing instantiates and no __copy is emitted).
class Rva00082719Vector
{
public:
	void fillInsert(Coord3D *, unsigned int, const Coord3D &);
};

// Declare-only explicit specialization: the erase call below binds the
// rowed 0x00081A24 primary-template instantiation without emitting a local
// copy (and without its __copy) in this TU. Same effect as the Clamp twin's
// fake template, but coexists with the real <vector> this TU also uses.
namespace _STL
{
	template <>
	class vector<Coord3D, allocator<Coord3D> >
	{
	public:
		Coord3D *erase(Coord3D *first, Coord3D *last);
	};
}

struct VecBase
{
	void *m_begin;
	void *m_end;
	void *m_cap;
};

void Rva00082C98Host::rva00082C98(unsigned int newSize, Vector3 value)
{
	unsigned int count = (unsigned int)(((char *)((VecBase *)this)->m_end - (char *)((VecBase *)this)->m_begin) / 12);
	if (newSize < count)
	{
		char *newEnd = (char *)((VecBase *)this)->m_begin + newSize * 12;
		((_STL::vector<Coord3D, _STL::allocator<Coord3D> > *)this)->erase((Coord3D *)newEnd, (Coord3D *)((VecBase *)this)->m_end);
	}
	else
	{
		((Rva00082719Vector *)this)->fillInsert((Coord3D *)((VecBase *)this)->m_end, newSize - (unsigned int)(((char *)((VecBase *)this)->m_end - (char *)((VecBase *)this)->m_begin) / 12), *(const Coord3D *)&value);
	}
}
