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

extern Int TheW3DFrameLengthInMsec;

class ParabolicEase { public: void rva0030E51F(Real easeIn, Real easeOut, Real total); };
class Rva00086E24 { public: void rva00086E24(); };

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

private:
	char m_pad04[0x70 - 4];
	Real m_zoom;			// +0x70
	char m_pad74[0x1E0 - 0x74];
	ZoomCameraInfo m_zcInfo;	// +0x1E0
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
