// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// ?rva00538F6B@Rva00538F6B@@QAEXPAX000@Z retail 0x00538F6B..0x005390AE
// (323 bytes ret 0x10). Called from 0x003195C9 on its +0x90 subobject with
// four pointers (already pinned under this address name). The receiver has
// the LivingWorldArmyLine layout of allocatePoints 0x005390AE (the next
// body): point count at +0x00 and a 12-byte point array at +0x04. It lays
// the points evenly along the segment from the first argument to the third
// (float pairs) at step 1/(count-1) and sets each height from the terrain
// query on g_00DFEF18: the object query 0x002BF935 against the second
// argument then the fourth and the plain ground query 0x002BF5B0 when both
// miss. The query result is shared across points (zeroed once before the
// loop). Each height is lifted by the float at TheLivingWorldManager+0xFC.
// Nothing is done without points or when the second and fourth arguments
// are the same object. The pinned (void* x4) spelling is kept for the
// existing caller; the class name is address-derived.
#include "Coord2D.h"
#include "Coord3D.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Vector3;

class Rva002BF4F3
{
public:
	bool rva002BF935(void *obj, const Vector3 *pos, Vector3 *result);
	bool rva002BF5B0(const Vector3 *pos, Vector3 *result);
};

class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct Rva00538F6BManagerView
{
	char m_pad[0xFC];
	Real m_heightOffset; // +0xFC
};

class Rva00538F6B
{
public:
	void rva00538F6B(void *a, void *b, void *c, void *d);

private:
	UnsignedInt m_count; // +0x00
	Coord3D *m_points; // +0x04
};

void Rva00538F6B::rva00538F6B(void *a, void *b, void *c, void *d)
{
	if (m_points != 0 && b != d)
	{
		const Coord2D *start = reinterpret_cast<const Coord2D *>(a);
		const Coord2D *end = reinterpret_cast<const Coord2D *>(c);
		Real heightOffset = reinterpret_cast<Rva00538F6BManagerView *>(TheLivingWorldManager)->m_heightOffset;
		Real step = 1.0f / (Real)(m_count - 1);
		Coord3D result;
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;

		for (Int i = 0; i < m_count; ++i)
		{
			Coord2D pos;
			Real t = i * step;
			pos.x = start->x + (end->x - start->x) * t;
			pos.y = start->y + (end->y - start->y) * t;
			m_points[i].x = pos.x;
			m_points[i].y = pos.y;

			if (!reinterpret_cast<Rva002BF4F3 *>(g_00DFEF18)->rva002BF935(b, reinterpret_cast<const Vector3 *>(&pos), reinterpret_cast<Vector3 *>(&result))
				&& !reinterpret_cast<Rva002BF4F3 *>(g_00DFEF18)->rva002BF935(d, reinterpret_cast<const Vector3 *>(&pos), reinterpret_cast<Vector3 *>(&result)))
			{
				reinterpret_cast<Rva002BF4F3 *>(g_00DFEF18)->rva002BF5B0(reinterpret_cast<const Vector3 *>(&pos), reinterpret_cast<Vector3 *>(&result));
			}

			m_points[i].z = result.z;
			m_points[i].z += heightOffset;
		}
	}
}
