// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva002E9442@Pathfinder@@QAE_NABVVector3@@0PAV2@@Z retail
// 0x002E9442..0x002E9871 (1071 bytes thiscall ret 0xC). The pathfinder half
// of the bridge pick: TerrainLogic::pickBridge 0x00281ECA falls back to it
// on TheAI+0x10 with its (from to pos) arguments. It keeps the nearest
// pick (WWMath Vector3::Quick_Length of hit minus from with its min = mid
// swap slip; constants 11/32 and 1/4) over three sources: the bridges on
// the +0x5C list (Bridge::pickBridge 0x0027FBFE; next at +4); the ray at
// each of the +0x1BEB8 heights in +0x1BEBC whose ground cell
// (rva001E3647Pos 0x001E3647 layer 1) is clear with the 6-bit field at
// cell +0xC bit 4 equal to the index plus 0x11; and the ray at the integer
// height of each live layer 2..15 (0x40-byte records; flag at record +0 /
// height at +4 from +0x118) whose cell in that layer is clear and tagged
// with the layer. Returns whether anything was picked. Field names are not
// recovered.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

struct WWMath
{
	static __forceinline float Fabs(float val)
	{
		int value = *(int *)&val;
		value &= 0x7fffffff;
		return *(float *)&value;
	}
};

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}

	__forceinline float Quick_Length() const
	{
		// Graphics Gems 1 approximation, +/- 8%
		float max = WWMath::Fabs(X);
		float mid = WWMath::Fabs(Y);
		float min = WWMath::Fabs(Z);
		float tmp;

		if (max < mid) { tmp = max; max = mid; mid = tmp; }
		if (max < min) { tmp = max; max = min; min = tmp; }
		if (mid < min) { tmp = mid; mid = min; min = mid; }

		return max + (11.0f / 32.0f) * mid + (1.0f / 4.0f) * min;
	}

	float X;
	float Y;
	float Z;
};

__forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b) { return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }
__forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z); }
__forceinline Vector3 operator*(const Vector3 &a, float k) { return Vector3(a.X * k, a.Y * k, a.Z * k); }

class Bridge
{
public:
	Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	Bridge *getNext() const { return m_next; }

private:
	void *m_00;
	Bridge *m_next; // +0x04
};

struct Rva002E9442Cell
{
	char m_pad00[0xc];
	unsigned int m_type : 4; // +0x0C bits 0..3
	unsigned int m_tag : 6; // +0x0C bits 4..9
};

struct Rva002E9442Layer
{
	void *m_live; // +0x00
	Int m_height; // +0x04
	char m_pad08[0x40 - 8];
};

class Pathfinder
{
public:
	Bool rva002E9442(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	void *rva001E3647Pos(int layer, const Coord3D *pos);

private:
	char m_pad00[0x5c];
	Bridge *m_bridges; // +0x5C
	char m_pad60[0x98 - 0x60];
	Rva002E9442Layer m_layers[16]; // +0x98
	char m_pad498[0x1beb8 - 0x498];
	Int m_heightCount; // +0x1BEB8
	Real m_heights[1]; // +0x1BEBC
};

Bool Pathfinder::rva002E9442(const Vector3 &from, const Vector3 &to, Vector3 *pos)
{
	Real bestDist = 3.4028234663852886e+38f;
	Bridge *bridge;
	for (bridge = m_bridges; bridge; bridge = bridge->getNext())
	{
		Vector3 hit;
		if (bridge->pickBridge(from, to, &hit))
		{
			Real dist = (hit - from).Quick_Length();
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hit;
			}
		}
	}

	Int i;
	for (i = 0; i < m_heightCount; ++i)
	{
		Vector3 delta = to - from;
		Real t = (m_heights[i] - from.Z) / delta.Z;
		Vector3 hit = from + delta * t;
		Coord3D cellPos;
		cellPos.x = hit.X;
		cellPos.y = hit.Y;
		cellPos.z = hit.Z;
		Rva002E9442Cell *cell = static_cast<Rva002E9442Cell *>(rva001E3647Pos(1, &cellPos));
		if (cell && cell->m_tag == i + 0x11 && cell->m_type == 0)
		{
			Real dist = (hit - from).Quick_Length();
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hit;
			}
		}
	}

	for (i = 2; i <= 15; ++i)
	{
		if (m_layers[i].m_live == 0)
			continue;
		Vector3 delta = to - from;
		Real t = ((Real)m_layers[i].m_height - from.Z) / delta.Z;
		Vector3 hit = from + delta * t;
		Coord3D cellPos;
		cellPos.x = hit.X;
		cellPos.y = hit.Y;
		cellPos.z = hit.Z;
		Rva002E9442Cell *cell = static_cast<Rva002E9442Cell *>(rva001E3647Pos(i, &cellPos));
		if (cell && cell->m_tag == i && cell->m_type == 0)
		{
			Real dist = (hit - from).Quick_Length();
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hit;
			}
		}
	}
	return bestDist < 3.4028234663852886e+38f;
}
