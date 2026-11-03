// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?drawRectClock@W3DDisplay@@UAEXMMMMMI@Z, retail 0x00045B45..0x000463B5 (2160 bytes)
// ?drawRemainingRectClock@W3DDisplay@@UAEXMMMMMI@Z, retail 0x000463B5..0x000465CE (537 bytes)
// Both thiscall RET 0x18.
//
// Identity: W3DDisplay vtable slot +0xEC (absolute reference at 0x007C3D6C),
// next to the rowed drawOpenRect (+0xE0, 0x00044A1A) and the fill-rect slot
// (+0xE4, 0x00044C9A); +0xF0 (0x000463B5) is drawRemainingRectClock. Body is
// Zero Hour's W3DDisplay::drawRectClock (GeneralsMD W3DDisplay.cpp) with BFME
// 2's float coordinates and percent, the +0x168 Render2D's rowed
// Add_Quad(rect, color) 0x000428C7 for Add_Rect and the pinned Add_Tri
// 0x00045708; as in drawOpenRect the Reset/Render calls are gone. WB twin
// 0x00971AF0 (vtable evidence) is unnamed.
//
// drawRemainingRectClock is not Zero Hour's four-quadrant version: BFME draws
// a triangle fan from the top centre, clockwise over the remaining fraction,
// with ceil(max(halfWidth, halfHeight) * remaining * 4) segments. Its shape is
// carried from Open-BFME-1's exact BFME 1 body (lotrbfme.exe 0x006ECA80,
// W3DDisplayDrawRemainingRectClock.cpp, slot +0xCC there); BFME 2's own
// evidence is the +0xF0 slot after drawRectClock, the same Render2D +0x168 /
// +0x48 texturing flag, the pinned Add_Tri, the _sin/_cos thunks and
// __imp__ceil, and the 0/100/0.01/2pi/4.0 constants. WB twin 0x00971EC0
// (vtable evidence, 3355 bytes) is unnamed.
#include <math.h>

typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Int;

#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/wwmath.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"

#define WWMATH_TWO_PI 6.283185307f

#include "../../../../Libraries/Source/WWVegas/WWMath/RectClass.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/Render2DClass.h"

#define W3DDISPLAY_SLOT(n) virtual void slot##n();

class W3DDisplay
{
public:
	W3DDISPLAY_SLOT(00) W3DDISPLAY_SLOT(01) W3DDISPLAY_SLOT(02) W3DDISPLAY_SLOT(03)
	W3DDISPLAY_SLOT(04) W3DDISPLAY_SLOT(05) W3DDISPLAY_SLOT(06) W3DDISPLAY_SLOT(07)
	W3DDISPLAY_SLOT(08) W3DDISPLAY_SLOT(09) W3DDISPLAY_SLOT(10) W3DDISPLAY_SLOT(11)
	W3DDISPLAY_SLOT(12) W3DDISPLAY_SLOT(13) W3DDISPLAY_SLOT(14) W3DDISPLAY_SLOT(15)
	W3DDISPLAY_SLOT(16) W3DDISPLAY_SLOT(17) W3DDISPLAY_SLOT(18) W3DDISPLAY_SLOT(19)
	W3DDISPLAY_SLOT(20) W3DDISPLAY_SLOT(21) W3DDISPLAY_SLOT(22) W3DDISPLAY_SLOT(23)
	W3DDISPLAY_SLOT(24) W3DDISPLAY_SLOT(25) W3DDISPLAY_SLOT(26) W3DDISPLAY_SLOT(27)
	W3DDISPLAY_SLOT(28) W3DDISPLAY_SLOT(29) W3DDISPLAY_SLOT(30) W3DDISPLAY_SLOT(31)
	W3DDISPLAY_SLOT(32) W3DDISPLAY_SLOT(33) W3DDISPLAY_SLOT(34) W3DDISPLAY_SLOT(35)
	W3DDISPLAY_SLOT(36) W3DDISPLAY_SLOT(37) W3DDISPLAY_SLOT(38) W3DDISPLAY_SLOT(39)
	W3DDISPLAY_SLOT(40) W3DDISPLAY_SLOT(41) W3DDISPLAY_SLOT(42) W3DDISPLAY_SLOT(43)
	W3DDISPLAY_SLOT(44) W3DDISPLAY_SLOT(45) W3DDISPLAY_SLOT(46) W3DDISPLAY_SLOT(47)
	W3DDISPLAY_SLOT(48) W3DDISPLAY_SLOT(49) W3DDISPLAY_SLOT(50) W3DDISPLAY_SLOT(51)
	W3DDISPLAY_SLOT(52) W3DDISPLAY_SLOT(53) W3DDISPLAY_SLOT(54) W3DDISPLAY_SLOT(55)
	W3DDISPLAY_SLOT(56) W3DDISPLAY_SLOT(57)
	// +0xE8 (retail 0x00045990).
	virtual void rva00045990(Real startX, Real startY, Real width, Real height, UnsignedInt color);
	// +0xEC (retail 0x00045B45).
	virtual void drawRectClock(Real startX, Real startY, Real width, Real height, Real percent, UnsignedInt color);
	// +0xF0 (retail 0x000463B5).
	virtual void drawRemainingRectClock(Real startX, Real startY, Real width, Real height, Real percent, UnsignedInt color);

private:
	char m_pad004[0x168 - 0x004];
	Render2DClass *m_2DRender;			// +0x168
};

// ?rva00045990@W3DDisplay@@UAEXMMMMI@Z, retail 0x00045990 (437 bytes), RET 0x14.
// W3DDisplay vtable slot +0xE8, between the fill-rect slot (+0xE4, 0x00044C9A) and
// drawRectClock (+0xEC). BFME 2 only: a filled ellipse drawn as a triangle fan
// about the box centre, ceil(max(halfWidth, halfHeight) * 4) segments of 2pi / n
// (the whole-circle sibling of drawRemainingRectClock below, which carries its
// shape from the exact BFME 1 body); the closing triangle returns to (halfWidth, 0)
// instead of recomputing cos/sin. Target evidence: slot position and the shared
// Render2D +0x168 / +0x48 texturing flag, Add_Tri 0x00045708, the _cos/_sin
// thunks, __imp__ceil and the 0.5/4.0/2pi constants. The name stays address-derived.
void W3DDisplay::rva00045990(Real startX, Real startY, Real width, Real height, UnsignedInt color)
{
	Int i = 0;
	Real halfWidth = width * 0.5f;
	Real halfHeight = height * 0.5f;
	Real centerX = halfWidth + startX;
	Real centerY = halfHeight + startY;
	m_2DRender->Enable_Texturing(false);
	Vector2 prev(halfWidth, 0.0f);
	Real radius = (halfWidth > halfHeight) ? halfWidth : halfHeight;
	Int segments = WWMath::Float_To_Long(ceil(radius * 4.0f));
	Real step = WWMATH_TWO_PI / (Real)segments;
	Real angle = 0.0f;

	if (segments > 0)
	{
		Vector2 uv2(0, 0);
		Vector2 uv1(0, 0);
		Vector2 uv0(0, 0);
		Vector2 center(centerX, centerY);

		do
		{
			++i;
			Vector2 cur;
			if (i < segments)
			{
				angle += step;
				cur.X = cos((double)angle) * halfWidth;
				cur.Y = sin((double)angle) * halfHeight;
			}
			else
			{
				cur.X = halfWidth;
				cur.Y = 0.0f;
			}
			m_2DRender->Add_Tri(center, Vector2(centerX + prev.X, centerY + prev.Y), Vector2(centerX + cur.X, centerY + cur.Y), uv0, uv1, uv2, color);
			prev = cur;
		} while (i < segments);
	}
}

void W3DDisplay::drawRectClock(Real startX, Real startY, Real width, Real height, Real percent, UnsignedInt color)
{
	// sanity
	if(percent < 1 || percent > 100)
		return;

	m_2DRender->Enable_Texturing( false );

// The rectanges are numberd as follows
//(x,y)	|---------|
//			| 4  | 1  |
//			|----+----|
//			| 3  | 2  |
//			|---------| (x + width, y + width)
//	
	// we're done, lets just draw one rectangle for it all.
	if(percent == 100)
	{
		m_2DRender->Add_Quad(RectClass( startX, startY, 
																		startX + width, startY + height), color);
	}
	else if( percent> 75)
	{
		//rectangle #1 & 2
		m_2DRender->Add_Quad(RectClass( startX + width/2, startY, 
																		startX + width, startY + height), color);
		// rectangle #3
		m_2DRender->Add_Quad(RectClass( startX, startY + height/2, 
																		startX + width/2, startY + height), color);
		// draw the part of rectangle 4
		Real remain = percent - 75;
		if(remain > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX, startY), 
													Vector2(startX, startY + height/2),
													Vector2(startX + width/2, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (remain - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX, startY), 
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + (width/2 * percentDraw), startY),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (remain)/ 12;
			m_2DRender->Add_Tri(Vector2(startX, startY + height/2 - (height/2 * percentDraw)), 
													Vector2(startX, startY + height/2),
													Vector2(startX + width/2, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}

	}
	else if( percent > 50)
	{
		//rectangle #1 & 2
		m_2DRender->Add_Quad(RectClass( startX + width/2, startY, 
																		startX + width, startY + height), color);
		// draw the part of rectangle 3
		Real remain = percent - 50;
		if(remain > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height/2), 
													Vector2(startX, startY + height),
													Vector2(startX + width/2, startY + height),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (remain - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX, startY + height - (height/2 * percentDraw)), 
													Vector2(startX, startY + height),
													Vector2(startX + width/2, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (remain)/ 12;
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height),  
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width/2 - ( width/2 * percentDraw), startY + height),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
	}
	else if(percent > 25)
	{
		// rectangel #1
		m_2DRender->Add_Quad(RectClass( startX + width/2, startY, 
																		startX + width, startY + height/2), color);
		// draw the part of rectangle 2
		Real remain = percent - 25;
		if(remain > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height/2), 
													Vector2(startX + width, startY + height),
													Vector2(startX + width, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (remain - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height/2), 
													Vector2(startX + width - (width/2 * percentDraw), startY + height),
													Vector2(startX + width, startY + height),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (remain)/ 12;
			m_2DRender->Add_Tri(Vector2(startX + width, startY + height/2),  
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width, startY + height/2 + ( height/2 * percentDraw)),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
	}
	else
	{
				// draw the part of rectangle 1
		
		if(percent > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY), 
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width, startY),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (percent - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX + width, startY),
													Vector2(startX + width/2, startY + height/2), 
													Vector2(startX + width, startY + (height/2 * percentDraw)),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (percent)/ 12;
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY),  
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width/2 + (width/2 * percentDraw), startY ),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
	}
}

void W3DDisplay::drawRemainingRectClock(Real startX, Real startY, Real width, Real height, Real percent, UnsignedInt color)
{
	if (percent < 0.0f)
		percent = 0.0f;
	else if (percent > 100.0f)
		percent = 100.0f;

	Real halfWidth = width * 0.5f;
	Real halfHeight = height * 0.5f;
	Real centerX = halfWidth + startX;
	Real centerY = halfHeight + startY;
	Vector2 prev(0.0f, -halfHeight);
	m_2DRender->Enable_Texturing(false);
	percent = 1.0f - (0.01f * percent);
	Real sweep = percent * WWMATH_TWO_PI;
	Real radius = (halfWidth > halfHeight) ? halfWidth : halfHeight;
	Int segments = WWMath::Float_To_Long(ceil(radius * percent * 4.0f));
	Real step = sweep / (Real)segments;
	Real angle = 0.0f;

	if (segments > 0)
	{
		Vector2 uv2(0, 0);
		Vector2 uv1(0, 0);
		Vector2 uv0(0, 0);
		Vector2 center(centerX, centerY);

		Int i = segments;
		do
		{
			angle += step;
			Vector2 cur;
			if (angle > 0.0f && angle < WWMATH_TWO_PI)
			{
				cur.X = -(sin((double)angle) * halfWidth);
				cur.Y = -(cos((double)angle) * halfHeight);
			}
			else
			{
				cur.X = 0.0f;
				cur.Y = -halfHeight;
			}
			m_2DRender->Add_Tri(center, Vector2(centerX + prev.X, centerY + prev.Y), Vector2(centerX + cur.X, centerY + cur.Y), uv0, uv1, uv2, color);
			prev = cur;
		} while (--i);
	}
}
