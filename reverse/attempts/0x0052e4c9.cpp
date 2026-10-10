// ?rva0052E4C9@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.8926492984108162 date=2026-10-10
// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

typedef float Real;
typedef int Int;
typedef bool Bool;

#define PATHFIND_CELL_SIZE_F 10.0f

float Cos(float);
float Sin(float);
extern "C" __declspec(dllimport) double floor(double x);
extern "C" __declspec(dllimport) double ceil(double x);

#include "Coord3D.h"

struct In002E6BA1 { Int x,y; };

struct IRegion2D
{
	Int loX, loY, hiX, hiY;
};

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

class PathfindCell
{
public:
	Bool rva0052DEEF(const struct Rva0052DEEFArg *,Bool,In002E6BA1 *);
	Bool rva0052DFB1(const struct Rva0052DFB1Arg *);

private:
	char m_pad[16];
};

class PathfindZoneManager
{
public:
	void MarkDirty(Int x,Int y);

private:
	Bool m_bfmeDirty;
};

static __forceinline int RealToIntFloor(float v)
{
	float t = (float)floor((double)v);
	int i;
	__asm fld t
	__asm fistp i
	return i;
}

static __forceinline int RealToIntCeil(float v)
{
	float t = (float)ceil((double)v);
	int i;
	__asm fld t
	__asm fistp i
	return i;
}

class Pathfinder
{
public:
	void rva0052E4C9(Object *fenceObject, Bool insertFence);

private:
	char m_pad00[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	char m_pad24[0x460 - 0x24];
	PathfindZoneManager m_zoneManager;
};

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


	for (Int iy = numStepsY; iy > 0; --iy, tl_x += ydx, tl_y += ydy)
	{
		Real x = tl_x;
		Real y = tl_y;
		for (Int ix = numStepsX; ix > 0; --ix, x += xdx, y += xdy)
		{
			Int cx = RealToIntFloor((x + 0.5f) / PATHFIND_CELL_SIZE_F);
			Int cy = RealToIntFloor((y + 0.5f) / PATHFIND_CELL_SIZE_F);

			if (cx >= 0 && cy >= 0 && cx < m_extent.hiX && cy < m_extent.hiY)
			{
				Bool changed;
				if (insertFence) {
					In002E6BA1 cellPos={cx,cy};
					changed=m_map[cx][cy].rva0052DEEF((const Rva0052DEEFArg *)fenceObject,true,&cellPos);
				} else changed=m_map[cx][cy].rva0052DFB1((const Rva0052DFB1Arg *)fenceObject);
				if(changed)m_zoneManager.MarkDirty(cx,cy);
			}
		}
	}

}

// Native0052E4C9..0052E6E6 RET8, fence traversal semantic identity from
// clean BFME1 PathfinderClassifyFence.cpp at575ba2b047 and ZH AIPathfind4007.
// Original BFME2 spelling unproven; native width4A0 offset4A4 angle44,
// map10 extent1C/20 manager460 and per-changed-cell MarkDirty are target facts.
// Retain donor floor/ceil FISTP helper for established x87 rounding shape.
