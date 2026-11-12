// ?rva0052E4C9@Pathfinder@@QAEXPAVObject@@_N@Z
// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

typedef float Real;
typedef int Int;
typedef bool Bool;

#define PATHFIND_CELL_SIZE_F 10.0f

float Cos(float);
float Sin(float);
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>

#include "Coord3D.h"

#include "../../Include/Common/In002E6BA1.h"

#include "ICoord2D.h"
#include "IRegion2D.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad00[4];
	Overridable *m_override;
};

class ThingTemplateFence : public Overridable
{
public:
	char m_pad08[0x4a0 - 8];
	float m_fenceWidth;
	float m_fenceXOffset;
};

class Object
{
public:
	char m_pad00[4];
	ThingTemplateFence *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_position;
	float m_orientation;
	char m_pad48[0x74 - 0x48];
	unsigned int m_id;
};

struct Rva003F7380Argument
{
	unsigned char m_padding[0x74];
	int m_value;
};

class Rva003F7380State
{
public:
	void resetIfMatching(const Rva003F7380Argument *argument);
};

#include "../../Include/GameLogic/PathfindCell.h"

#include "../../Include/GameLogic/PathfindZoneManager.h"

static __forceinline int RealToIntFloor(float v)
{
	float t = floorf(v);
	int i;
	__asm fld t
	__asm fistp i
	return i;
}

static __forceinline int RealToIntCeil(float v)
{
	float t = ceilf(v);
	int i;
	__asm fld t
	__asm fistp i
	return i;
}

#include "../../Include/GameLogic/AIPathfind.h"

// ?rva0052E4C9@Pathfinder@@QAEXPAVObject@@_N@Z
void Pathfinder::rva0052E4C9(Object *fenceObject, Bool insertFence)
{
	const Coord3D *fencePosition = &fenceObject->m_position;
	Real angle=fenceObject->m_orientation;
	Real fenceWidth=fenceObject->m_template->m_fenceWidth;
	Real fenceOffset=fenceObject->m_template->m_fenceXOffset;
 Real halfsizeY=1.0f;
	Real c = Cos(angle);
	Real s = Sin(angle);

	const Real STEP_SIZE = PATHFIND_CELL_SIZE_F * 0.5f;
	Real ydx = s * STEP_SIZE;
	Real ydy = -c * STEP_SIZE;
	Real xdx = c * STEP_SIZE;
	Real xdy = s * STEP_SIZE;

	Int numStepsX = RealToIntCeil((fenceWidth*0.5f)/2.5f);
	Int numStepsY = RealToIntCeil(2.0f * halfsizeY / STEP_SIZE);

	Real tl_x = fencePosition->x - fenceOffset * c - halfsizeY * s;
	Real tl_y = fencePosition->y + halfsizeY * c - fenceOffset * s;


	for (Int iy = numStepsY; 0 < iy; --iy, tl_x += ydx, tl_y += ydy)
	{
		Real x = tl_x;
		Real y = tl_y;
		for (Int ix = numStepsX; 0 < ix; --ix, x += xdx, y += xdy)
		{
			Int cx = RealToIntFloor((x + 0.5f) / PATHFIND_CELL_SIZE_F);
			Int cy = RealToIntFloor((y + 0.5f) / PATHFIND_CELL_SIZE_F);

			if (cx >= 0 && cy >= 0 && cx < m_extent.hi.x && cy < m_extent.hi.y)
			{
				if (insertFence) {
					In002E6BA1 cellPos={cx,cy};
					if(m_map[cx][cy].rva0052DEEF((const Rva0052DEEFArg *)fenceObject,true,&cellPos))
						m_zoneManager.MarkDirty(cx,cy);
				} else {
					if(m_map[cx][cy].rva0052DFB1((const Rva0052DFB1Arg *)fenceObject))
						m_zoneManager.MarkDirty(cx,cy);
				}
			}
		}
	}

}

// Native0052E4C9..0052E6E6 RET8, fence traversal semantic identity from
// clean BFME1 PathfinderClassifyFence.cpp at575ba2b047 and ZH AIPathfind4007.
// Original BFME2 spelling unproven; native width4A0 offset4A4 angle44,
// map10 extent1C/20 manager460 and per-changed-cell MarkDirty are target facts.
// Retain donor floor/ceil FISTP helper for established x87 rounding shape.
