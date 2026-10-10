// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?zoomCamera@W3DView@@UAEXMHMM@Z, retail 0x00088FF6..0x0008907A (132 bytes,
// RET 0x10). Zero Hour's W3DView::zoomCamera in BFME2's form: the duration is
// clamped to one millisecond, the frame count is that over the render frame
// length (TheW3DFrameLengthInMsec) kept at least 1, the zoom-camera state at
// +0x1E0 (frames, current frame, start zoom from +0x70, end zoom) is armed,
// the ParabolicEase (+0x1FC) gets its in/out times and the duration, and a
// one-millisecond request runs the first step at once (rowed 0x00086E24).

typedef int Int;
typedef float Real;
#include "../../../../Libraries/Include/Lib/Coord3D.h"

extern Int TheW3DFrameLengthInMsec;

class ParabolicEase { public: void rva0030E51F(Real easeIn, Real easeOut, Real total); };
class Rva00086E24 { public: void rva00086E24(); };
class Rva00086EBD { public: void rva00086EBD(); };

// The pitch-camera state at +0x258 has the zoom state's shape.
struct PitchCameraInfo
{
	Int numFrames;		// +0x258
	Int curFrame;		// +0x25C
	Int m_pad8;		// +0x260
	Real startPitch;	// +0x264
	Real endPitch;		// +0x268
	char m_pad26C[8];	// +0x26C
	ParabolicEase ease;	// +0x274
	char m_pad275[7];
	bool doingPitchCamera;	// +0x27C
	bool m_flag27D;		// +0x27D, the W3DView camera flag cleared with it
};

struct ZoomCameraInfo
{
	Int numFrames;		// +0x1E0
	Int curFrame;		// +0x1E4
	Int m_pad8;		// +0x1E8
	Real startZoom;		// +0x1EC
	Real endZoom;		// +0x1F0
	char m_pad1F4[8];	// +0x1F4
	ParabolicEase ease;	// +0x1FC
	char m_pad1FD[7];
	bool doingZoomCamera;	// +0x204
};

class W3DView
{
public:
	virtual void zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut);
	virtual void pitchCamera(Real finalPitch, Int milliseconds, Real easeIn, Real easeOut);
	virtual void setAngle(Real angle);

private:
	void setCameraTransform();
	void rva000860AF(Coord3D *pos);

	char m_pad04[0x0C - 4];
	Coord3D m_pos;			// +0x0C
	char m_pad18[0x30 - 0x18];
	Real m_pitchAngle;		// +0x30
	char m_pad34[0x44 - 0x34];
	bool m_flag44;			// +0x44
	char m_pad45[0x70 - 0x45];
	Real m_zoom;			// +0x70
	char m_pad74[0x1DC - 0x74];
	bool m_flag1DC;			// +0x1DC
	char m_pad1DD[0x1E0 - 0x1DD];
	ZoomCameraInfo m_zcInfo;	// +0x1E0
	char m_pad208[0x228 - 0x208];
	bool m_flag228;			// +0x228
	char m_pad229[0x258 - 0x229];
	PitchCameraInfo m_pcInfo;	// +0x258
	char m_pad280[0x24F8 - 0x280];
	Real m_angleTravelled;		// +0x24F8
	char m_pad24FC[0x2502 - 0x24FC];
	bool m_flag2502;		// +0x2502
};

void W3DView::zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut)
{
	if (milliseconds < 1) milliseconds = 1;
	m_zcInfo.numFrames = milliseconds / TheW3DFrameLengthInMsec;
	if (m_zcInfo.numFrames < 1) {
		m_zcInfo.numFrames = 1;
	}
	m_zcInfo.curFrame = 0;
	m_zcInfo.doingZoomCamera = true;
	m_zcInfo.startZoom = m_zoom;
	m_zcInfo.endZoom = finalZoom;
	m_zcInfo.ease.rva0030E51F(easeIn, easeOut, (Real)milliseconds);
	if (milliseconds == 1)
		((Rva00086E24 *)this)->rva00086E24();
}

// ?pitchCamera@W3DView@@UAEXMHMM@Z, retail 0x0008907A..0x000890FE (132 bytes,
// RET 0x10), the View slot after zoomCamera: the same arming over the pitch
// state at +0x258 (start from the view pitch +0x30), first step 0x00086EBD.
void W3DView::pitchCamera(Real finalPitch, Int milliseconds, Real easeIn, Real easeOut)
{
	if (milliseconds < 1) milliseconds = 1;
	m_pcInfo.numFrames = milliseconds / TheW3DFrameLengthInMsec;
	if (m_pcInfo.numFrames < 1) {
		m_pcInfo.numFrames = 1;
	}
	m_pcInfo.curFrame = 0;
	m_pcInfo.doingPitchCamera = true;
	m_pcInfo.startPitch = m_pitchAngle;
	m_pcInfo.endPitch = finalPitch;
	m_pcInfo.ease.rva0030E51F(easeIn, easeOut, (Real)milliseconds);
	if (milliseconds == 1)
		((Rva00086EBD *)this)->rva00086EBD();
}

// ?setAngle@W3DView@@UAEXM@Z, retail 0x0008D139..0x0008D1DD (164 bytes, RET 4),
// the View slot before getAngle/setPitch. Zero Hour's W3DView::setAngle with
// BFME 2's additions: it is ignored while the view field +0x44 is set and
// either game-client flag +0xC0/+0xC1 is up, or while +0x2502 is set; the
// absolute change against getAngle (vtable +0x100) accumulates at +0x24F8;
// after the camera transform the position is re-constrained (0x000860AF).
// normAngle is the file static rowed at 0x000855D1 (address passed in EAX).
#pragma auto_inline(off)
static void normAngle(Real &angle)
{
	if (angle < -10*3.14159265359f) {
		angle = 0;
	}
	if (angle > 10*3.14159265359f) {
		angle = 0;
	}
	while (angle < -3.14159265359f) {
		angle += 2*3.14159265359f;
	}
	while (angle > 3.14159265359f) {
		angle -= 2*3.14159265359f;
	}
}
#pragma auto_inline(on)

extern "C" double __cdecl fabs(double);
class GameClient;
extern GameClient *TheGameClient;
struct GameClientCameraLocks { char m_pad00[0xC0]; bool m_lockC0; bool m_lockC1; };
class View { public: virtual void setAngle(Real angle); };
#define W3DVIEW_UNUSED_8(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3(); 	virtual void n##4(); virtual void n##5(); virtual void n##6(); virtual void n##7()
struct W3DViewAngleSlots
{
	W3DVIEW_UNUSED_8(s00); W3DVIEW_UNUSED_8(s20); W3DVIEW_UNUSED_8(s40); W3DVIEW_UNUSED_8(s60);
	W3DVIEW_UNUSED_8(s80); W3DVIEW_UNUSED_8(sA0); W3DVIEW_UNUSED_8(sC0); W3DVIEW_UNUSED_8(sE0);
	virtual Real getAngle();	// +0x100
};
#undef W3DVIEW_UNUSED_8

void W3DView::setAngle(Real angle)
{
	const GameClientCameraLocks *locks = reinterpret_cast<const GameClientCameraLocks *>(TheGameClient);
	if (locks->m_lockC0 && m_flag44)
		return;
	if (locks->m_lockC1 && m_flag44)
		return;
	if (m_flag2502)
		return;
	normAngle(angle);
	Real delta = angle - reinterpret_cast<W3DViewAngleSlots *>(this)->getAngle();
	m_angleTravelled += (Real)fabs(delta);
	reinterpret_cast<View *>(this)->View::setAngle(angle);
	m_flag1DC = false;
	m_zcInfo.doingZoomCamera = false;
	m_pcInfo.doingPitchCamera = false;
	m_flag228 = false;
	m_pcInfo.m_flag27D = false;
	setCameraTransform();
	rva000860AF(&m_pos);
}
