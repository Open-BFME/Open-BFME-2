// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
//
// ?rva0008DB18@W3DView@@UAEXXZ, retail 0x0008DB18..0x0008DE1C (772 bytes), a
// W3DView vftable entry (0x007C77E0) with no direct callers. WorldBuilder
// twin 0x0099A350 (unnamed); BFME 1 and Zero Hour have no counterpart, so the
// method keeps an address-derived name.
//
// While the view's slot-115 test passes and the game is not paused, the mouse
// at the left/right screen margins spins the camera (velocity at 0x00DE2044,
// damped, applied through the file-static normAngle 0x000855D1 that takes the
// angle's address in EAX) and the top/bottom margins zoom it (velocity at
// 0x00DE2040, clamped by the zoom limits). Then the camera follows the object
// slot 117 names, flattened to z = 0, and a pending drawable gets its opacity
// back. Outside that mode, mode 4 just rebuilds the camera transform.
//
// Frame: the WB twin keeps the two mouse floats side by side, x below y, and
// initialises both before the margin block; retail packs them, as one
// eight-byte Coord2D, onto the later Coord3D (frame 0x14). Two loose floats
// give a 0x18 frame with every fild temporary moved. The pending drawable is
// file-static here: retail clears it before the opacity store, which cl only
// does when no float store can alias the pointer.

#include "Lib/BaseType.h"

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../../../GameEngine/Include/GameClient/Display.h"
extern Display *TheDisplay;

class Mouse
{
public:
	void rva001EDE9C();
	void _bfme_setEngineVisibility(bool visible);
	char m_pad00[0x4F0C];
	ICoord2D m_pos; // +0x4F0C +0x4F0C
	char m_pad4F14[0xF5];
	Bool m_5009; // +0x5009
};
extern Mouse *TheMouse;

struct BfmeObjectPositionView
{
	char m_pad[0x38];
	Coord3D m_pos;			// +0x38
};

struct BfmeFadeDrawable
{
	char m_pad[0xB0];
	Real m_opacity;			// +0xB0
};
static BfmeFadeDrawable *g_Va00DE2078;

bool g_Va00DB4580 = true;	// retail RVA 0x009B4580 (.data), defined here
extern bool g_bfmeFlagEC;
// Camera-tuning constants this body reads, defined at their retail .data
// values (RVA 0x009B4540..0x009B456C), and two .bss accumulators (0x009E2040/44).
Real g_Va00DB4540 = 0.1f;
Real g_Va00DB4544 = 0.0002f;
Real g_Va00DB4548 = 0.3f;
Real g_Va00DB454C = 0.2f;
Real g_Va00DB4550 = 0.2f;
Real g_Va00DB4560 = 0.4f;
Real g_Va00DB4564 = -0.1f;
Real g_Va00DB4568 = 0.0004f;
Real g_Va00DB456C = 0.4f;
Real g_Va00DE2040;
Real g_Va00DE2044;
extern Real g_Va00DE2020;

#pragma auto_inline(off)
static void normAngle(Real &angle)
{
	if (angle < -10*PI) angle = 0;
	if (angle > 10*PI) angle = 0;
	while (angle < -PI) angle += 2*PI;
	while (angle > PI) angle -= 2*PI;
}
#pragma auto_inline(on)

#define W3DVIEW_UNUSED_8(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3(); \
	virtual void n##4(); virtual void n##5(); virtual void n##6(); virtual void n##7()

class W3DView
{
public:
	W3DVIEW_UNUSED_8(s00); W3DVIEW_UNUSED_8(s08); W3DVIEW_UNUSED_8(s10);
	virtual void s18(); virtual void s19(); virtual void s1A(); virtual void s1B();
	virtual void s1C(Bool flag);	// +0x70
	virtual void s1D(); virtual void s1E(); virtual void s1F();
	W3DVIEW_UNUSED_8(s20); W3DVIEW_UNUSED_8(s28); W3DVIEW_UNUSED_8(s30);
	W3DVIEW_UNUSED_8(s38); W3DVIEW_UNUSED_8(s40); W3DVIEW_UNUSED_8(s48);
	W3DVIEW_UNUSED_8(s50); W3DVIEW_UNUSED_8(s58); W3DVIEW_UNUSED_8(s60);
	W3DVIEW_UNUSED_8(s68);
	virtual void s70(); virtual void s71(); virtual void s72();
	virtual Bool s73();			// +0x1CC
	virtual void s74();
	virtual ObjectID s75();		// +0x1D4
	virtual void rva0008DB18();
private:
	void setCameraTransform();

	char m_pad004[0x0C - 4];
	Coord3D m_pos;				// +0x0C
	char m_pad018[0x28 - 0x18];
	Real m_angle;				// +0x28
	char m_pad02C[0x70 - 0x2C];
	Real m_zoom;				// +0x70
	char m_pad074[0x1DC - 0x74];
	Bool m_doingRotateCamera;		// +0x1DC
	char m_pad1DD[0x27D - 0x1DD];
	Bool m_flag27D;				// +0x27D
	char m_pad27E[0x2354 - 0x27E];
	Int m_doingMoveCameraOnWaypointPath;	// +0x2354
	char m_pad2358[0x24A0 - 0x2358];
	Int m_mode;				// +0x24A0
};

#undef W3DVIEW_UNUSED_8

void W3DView::rva0008DB18()
{
	if (s73() && !TheGameLogic->isGamePaused()) {
		if (!g_Va00DB4580) {
			Coord2D mouse;
			if (!g_bfmeFlagEC) {
				Real margin = TheDisplay->getWidth() * g_Va00DB4540;
				mouse.x = (Real)TheMouse->m_pos.x;
				Real delta = mouse.x - margin;
				if (delta > 0) {
					delta = mouse.x - (TheDisplay->getWidth() - margin);
					if (delta < 0) delta = 0;
				}
				g_Va00DE2044 -= delta * g_Va00DB4544;
				g_Va00DE2044 -= g_Va00DE2044 * g_Va00DB4548;
				Real rotation = g_Va00DE2044;
				if (rotation != 0) {
					if (!g_bfmeFlagEC) {
						m_angle += g_Va00DE2020;
						g_Va00DE2020 = 0;
					}
					m_angle += rotation;
					normAngle(m_angle);
				}
			}
			Real top = TheDisplay->getHeight() * g_Va00DB454C;
			Real bottom = TheDisplay->getHeight() * g_Va00DB4550;
			mouse.y = (Real)TheMouse->m_pos.y;
			Real delta = mouse.y - top;
			if (delta > 0) {
				delta = mouse.y - (TheDisplay->getHeight() - bottom);
				if (delta < 0) delta = 0;
			}
			if ((delta > 0 && m_zoom < g_Va00DB4560) || (delta < 0 && m_zoom > g_Va00DB4564))
				g_Va00DE2040 += delta * g_Va00DB4568;
			g_Va00DE2040 -= g_Va00DE2040 * g_Va00DB456C;
			if (g_Va00DE2040 != 0) m_zoom += g_Va00DE2040;
		}
		Object *obj = TheGameLogic->findObjectByID(s75());
		if (obj && !g_bfmeFlagEC) {
			const BfmeObjectPositionView *fields = (const BfmeObjectPositionView *)obj;
			Coord3D pos = { fields->m_pos.x, fields->m_pos.y, 0 };
			m_doingMoveCameraOnWaypointPath = 0;
			m_pos = pos;
			m_doingRotateCamera = false;
			s1C(false);
			m_flag27D = false;
			setCameraTransform();
		}
		if (g_Va00DE2078) {
			g_Va00DE2078->m_opacity = 1;
			g_Va00DE2078 = 0;
		}
		TheDisplay->getWidth();
		TheDisplay->getHeight();
	} else if (m_mode == 4) {
		setCameraTransform();
	}
}
