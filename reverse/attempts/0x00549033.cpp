// ?rva00549033@@YAXXZ
// partial score=0.7 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// ?RotateFormationOffset@@YAXPBUCoord3D@@0PAVCoord2D@@@Z  Native 0x00549033..0x005490AE (123 bytes)
// AIGroup formation helper: builds the XY direction from the first point to
// the second (z cleared) and normalizes it with Coord3D::normalize 0x000035B6
// then rotates the formation offset into that frame (x along the direction
// and y along its perpendicular). WB twin 0x013BAB60 copies the second point
// subtracts the first clears z normalizes negates y builds the perpendicular
// (-y x 0) and scales and adds; retail inlines the scale and add.
// The only retail caller is AIGroup::createFormation 0x005494A0 (two call
// sites) which passes the points in ECX/EAX and the offset in ESI: a private
// convention of this static helper.
// NEAR (11 of 35 instructions differ): size and entry match; after the
// normalize call cl swaps xmm3/xmm4 (dir.x vs the ox copy) and schedules the
// oy*perp.y product into the oy register where retail reuses dir.x. The dummy caller below is marked
// absent-from-retail and only gives cl the call sites.
#include "Coord3D.h"
#include "Coord2D.h"

static void RotateFormationOffset(const Coord3D *from, const Coord3D *to, Coord2D *offset)
{
	Coord3D dir;
	dir.x = to->x; dir.y = to->y; dir.z = to->z;
	dir.x -= from->x; dir.y -= from->y; dir.z -= from->z;
	dir.z = 0.0f;
	dir.normalize();
	dir.y = -dir.y;
	Coord3D perp;
	perp.x = -dir.y; perp.y = dir.x; perp.z = 0.0f;
	float ox = offset->x;
	dir.x *= ox; dir.y *= ox;
	float oy = offset->y;
	perp.x *= oy; perp.y *= oy;
	dir.x += perp.x; dir.y += perp.y;
	offset->x = dir.x; offset->y = dir.y;
}

// ?RotateFormationOffsetCaller absent-from-retail
void RotateFormationOffsetCaller(const Coord3D *points, int count, Coord2D *offsets)
{
	for (int i = 0; i < count; ++i)
	{
		Coord2D a = offsets[i];
		RotateFormationOffset(&points[i], &points[i + 1], &a);
		offsets[i] = a;
	}
}
