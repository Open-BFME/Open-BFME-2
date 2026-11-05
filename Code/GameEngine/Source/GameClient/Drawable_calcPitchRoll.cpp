// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?calcPitchRoll@Drawable@@QAE_NPAX000HH@Z
// retail 0x00270276..0x00270619 (931 bytes) thiscall RET 0x18; this unused.
//
// Identity (WorldBuilder): the WB twin at 0x00CA2560 is
// Drawable::calcPitchRoll (Drawable.cpp; uninitialised-math asserts on pos
// and dir at lines 1373/1374) with the same callee graph. Retail callers are
// the matched calcPhysicsXformWheels unit and 0x00276B32; the row keeps
// the callers' void*/int argument views.
// When the locomotor template flag +0xED is set it samples the terrain under
// three corners of the object's footprint (box radii at object +0xCC/+0xD0
// along the unit direction and its left perpendicular) through
// TheTerrainLogic slot 7 (getLayerHeight on the object's layer 0x0028B511);
// if no corner height is more than half the summed radii from the object's
// position z (+0x40) the normal of the corner plane (normalize 0x000035B6)
// gives the pitch and roll through ASin 0x00711AC0. Otherwise (or with the
// flag clear) the terrain normal at the position is used. Returns true.
// Target facts: the corner array is built and torn down through the eh
// vector iterators (0x00629512/0x00629110) with the out-of-line empty
// Coord3D constructor 0x0047A6A9 and destructor 0x000B3FD0; fabs is the CRT
// call 0x00629210 on the double promotion; one frame slot (ebp-0x20) holds
// the half-width offset and later the plane normal, so one Coord3D carries
// both here (WB keeps two locals). Field and flag meanings are inferred.

#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

Real ASin(Real x);

struct LocomotorTemplate
{
	char m_pad00[0xED];
	Bool m_flagED;
};

class Locomotor
{
public:
	Bool getFlagED() const { return m_template->m_flagED; }
private:
	void *m_vtable;
	const LocomotorTemplate *m_template;	// +0x04
};

class Object
{
public:
	Int rva0028B511() const;		// layer
	const Coord3D *getPosition() const { return &m_pos; }
	Real getBoxMajorRadius() const { return m_boxMajorRadius; }
	Real getBoxMinorRadius() const { return m_boxMinorRadius; }

private:
	char m_pad000[0x38];
	Coord3D m_pos;				// +0x38
	char m_pad044[0xCC - 0x44];
	Real m_boxMajorRadius;			// +0xCC
	Real m_boxMinorRadius;			// +0xD0
};

#include "../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../Include/GameClient/Drawable.h"

Bool Drawable::calcPitchRoll(void *objArg, void *locomotorArg, void *posArg, void *dirArg, Int pitchArg, Int rollArg)
{
	Object *obj = (Object *)objArg;
	const Locomotor *locomotor = (const Locomotor *)locomotorArg;
	const Coord3D *pos = (const Coord3D *)posArg;
	const Coord3D *dir = (const Coord3D *)dirArg;
	Real *pitch = (Real *)pitchArg;
	Real *roll = (Real *)rollArg;

	Coord3D perp;
	perp.x = -dir->y;
	perp.y = dir->x;
	perp.z = 0;

	if (locomotor->getFlagED())
	{
		Real length = obj->getBoxMajorRadius();
		Real width = obj->getBoxMinorRadius();
		Coord3D halfLength;
		halfLength.x = dir->x * 0.5 * length;
		halfLength.y = (length * dir->y) * 0.5;
		halfLength.z = 0;
		// Half-width offset first; reused below for the corner-plane normal.
		Coord3D vec;
		vec.x = perp.x * 0.5 * width;
		vec.y = perp.y * 0.5 * width;

		Coord3D corners[4];
		corners[0].x = pos->x - halfLength.x + vec.x;
		corners[0].y = pos->y - halfLength.y + vec.y;
		corners[0].z = pos->z;
		corners[1].x = pos->x - halfLength.x - vec.x;
		corners[1].y = pos->y - halfLength.y - vec.y;
		corners[1].z = pos->z;
		corners[2].x = halfLength.x + pos->x + vec.x;
		corners[2].y = halfLength.y + pos->y + vec.y;
		corners[2].z = pos->z;

		Bool tooSteep = false;
		Real heights[3];
		for (Int i = 0; i < 3; ++i)
		{
			heights[i] = TheTerrainLogic->getLayerHeight(corners[i].x, corners[i].y, (PathfindLayerEnum)obj->rva0028B511(), 0, true);
			if (fabs(heights[i] - obj->getPosition()->z) > (length + width) * 0.5f)
				tooSteep = true;
		}

		if (!tooSteep)
		{
			Coord3D widthEdge;
			widthEdge.x = corners[1].x - corners[0].x;
			widthEdge.y = corners[1].y - corners[0].y;
			widthEdge.z = heights[1] - heights[0];
			Coord3D lengthEdge;
			lengthEdge.x = corners[2].x - corners[0].x;
			lengthEdge.y = corners[2].y - corners[0].y;
			lengthEdge.z = heights[2] - heights[0];
			vec.x = widthEdge.y * lengthEdge.z - widthEdge.z * lengthEdge.y;
			vec.y = widthEdge.z * lengthEdge.x - widthEdge.x * lengthEdge.z;
			vec.z = widthEdge.x * lengthEdge.y - widthEdge.y * lengthEdge.x;
			vec.normalize();
			Real s = vec.x * dir->x + vec.y * dir->y + vec.z * dir->z;
			*pitch = ASin(s);
			s = vec.x * perp.x + vec.y * perp.y + vec.z * perp.z;
			*roll = ASin(s);
			return true;
		}
	}

	Coord3D normal;
	normal.x = 0;
	normal.y = 0;
	normal.z = 1.0f;
	TheTerrainLogic->getLayerHeight(pos->x, pos->y, (PathfindLayerEnum)obj->rva0028B511(), &normal, true);
	Real s = normal.x * dir->x + normal.y * dir->y;
	*pitch = ASin(s);
	s = normal.x * perp.x + normal.y * perp.y;
	*roll = ASin(s);
	return true;
}
