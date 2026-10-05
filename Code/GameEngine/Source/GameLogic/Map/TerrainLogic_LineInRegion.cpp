// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ZH donor: GeneralsMD GameLogic/Map/TerrainLogic.cpp LineInRegion, verbatim.
// ?LineInRegion@@YA_NPBUCoord2D@@0PBURegion2D@@@Z retail 0x0027C4F4 680B:
// a Zero Hour engine sweep built /O1 /G7 /arch:SSE places the body uniquely in
// TerrainLogic's retail range; its callers there (0x0027C906, 0x0027C94A, ...)
// and in the pathfinder (0x002FA081, 0x002FA130) are the bridge and cell
// clipping tests that call it in Zero Hour.

typedef float Real;
typedef int Int;
typedef bool Bool;
#define TRUE true
#define FALSE false

struct Coord2D
{
	Real x, y;
};

struct Region2D
{
	Coord2D lo, hi;
};


/*-------------------------------------------------------------------------------------------------
/** Clip a floating point line to the region provided.  The source line runs from p1 to p2, and is clipped
	* using the clipRegion.  
	*
	* Return values: 
	*				TRUE  - Line intersects the region
	*				FALSE - Line does not intersect the region
	*/
//-------------------------------------------------------------------------------------------------
Bool LineInRegion( const Coord2D *p1, const Coord2D *p2, const Region2D *clipRegion )
{
	enum { CLIP_LEFT  = 0x01,
				CLIP_RIGHT  = 0x02,
				CLIP_BOTTOM = 0x04,
				CLIP_TOP	  = 0x08 };
	Real x1, y1, x2, y2;
	Real clipLeft;
	Real clipRight;
	Real clipTop;
	Real clipBottom;
	Int clipCode1;
	Int clipCode2;
	Real diff;

	// Use clip window that includes bottom right pixel
	clipLeft = clipRegion->lo.x;
	clipRight = clipRegion->hi.x;
	clipTop = clipRegion->lo.y;
	clipBottom = clipRegion->hi.y;

	x1 = p1->x;
	y1 = p1->y;
	x2 = p2->x;
	y2 = p2->y;
		
	// Test first point
	clipCode1 = 0;

	if (x1 < clipLeft)
		clipCode1 = CLIP_LEFT;
	else
	if (x1 > clipRight)
		clipCode1 = CLIP_RIGHT;

	if (y1 < clipTop)
		clipCode1 |= CLIP_TOP;
	else
	if (y1 > clipBottom)
		clipCode1 |= CLIP_BOTTOM;


	// Test second point
	clipCode2 = 0;

	if (x2 < clipLeft)
		clipCode2 = CLIP_LEFT;
	else
	if (x2 > clipRight)
		clipCode2 = CLIP_RIGHT;

	if (y2 < clipTop)
		clipCode2 |= CLIP_TOP;
	else
	if (y2 > clipBottom)
		clipCode2 |= CLIP_BOTTOM;


	// Both points inside window?
	if ((clipCode1 | clipCode2) == 0)
	{
		return TRUE;
	}  // end if

	// Both points outside window?
	if (clipCode1 & clipCode2)
		return FALSE;

	// First point outside window?
	if (clipCode1)
	{
		if (clipCode1 & CLIP_TOP)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x1 += (x2 - x1) * (clipTop - y1) / diff;
			y1 = clipTop;
		}
		else
		if (clipCode1 & CLIP_BOTTOM)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x1 += (x2 - x1) * (clipBottom - y1) / diff;
			y1 = clipBottom;
		}

		if (x1 > clipRight)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y1 += (y2 - y1) * (clipRight - x1) / diff;
			x1 = clipRight;
		}
		else
		if (x1 < clipLeft)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y1 += (y2 - y1) * (clipLeft - x1) / diff;
			x1 = clipLeft;
		}
	}

	// Second point outside window?
	if (clipCode2)
	{
		if (clipCode2 & CLIP_TOP)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x2 += (x2 - x1) * (clipTop - y2) / diff;
			y2 = clipTop;
		}
		else
		if (clipCode2 & CLIP_BOTTOM)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x2 += (x2 - x1) * (clipBottom - y2) / diff;
			y2 = clipBottom;
		}

		if (x2 > clipRight)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y2 += (y2 - y1) * (clipRight - x2) / diff;
			x2 = clipRight;
		}
		else
		if (x2 < clipLeft)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y2 += (y2 - y1) * (clipLeft - x2) / diff;
			x2 = clipLeft;
		}
	}

	// Line is visible
	return (x1 >= clipLeft && x1 <= clipRight &&
		    y1 >= clipTop && y1 <= clipBottom &&
			x2 >= clipLeft && x2 <= clipRight &&
			y2 >= clipTop && y2 <= clipBottom);

}  // end LineInRegion
