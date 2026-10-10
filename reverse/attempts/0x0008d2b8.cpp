// ?setHeightAboveGround@W3DView@@UAEXM@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?setHeightAboveGround@W3DView@@UAEXM@Z, retail 0x0008D2B8..0x0008D3C1 (265
// bytes, RET 4). Zero Hour's W3DView::setHeightAboveGround in BFME2's form:
// nothing happens while the client is in its locked mode with a limited zoom
// or while any scripted/automatic camera move is running (the six move flags
// and two state words), otherwise the change in height is added to a running
// total (+0x24FC), the height (+0x40) is stored and, for a limited zoom,
// pulled back inside the camera limits object at +0x24C8 (virtual
// getMinimum/getMaximum), every move flag is cleared and the camera transform
// rebuilt (rowed 0x0008BE6B). Field names are descriptive; offsets are read
// from retail.

#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

class GameClient
{
public:
	char m_pad00[0xC0];
	Bool m_flagC0;		// +0xC0
};
extern GameClient *TheGameClient;

struct HeightChangeTotal
{
	Real total;
	void add(Real d) { total += d; }
};

class CameraLimit
{
public:
	virtual Real getMinimum();
	virtual Real getMaximum();
};

class W3DView
{
public:
	virtual void v0();
	virtual void setHeightAboveGround(Real z);

private:
	void setCameraTransform();

	char m_pad04[0x40 - 4];
	Real m_heightAboveGround;	// +0x40
	Bool m_zoomLimited;		// +0x44
	char m_pad45[0x1DC - 0x45];
	Bool m_doing1DC;		// +0x1DC
	char m_pad1DD[0x204 - 0x1DD];
	Bool m_doingZoomCamera;		// +0x204
	char m_pad205[0x228 - 0x205];
	Bool m_doing228;		// +0x228
	char m_pad229[0x27C - 0x229];
	Bool m_doing27C;		// +0x27C
	Bool m_doing27D;		// +0x27D
	char m_pad27E[0x2354 - 0x27E];
	Int m_state2354;		// +0x2354
	char m_pad2358[0x241C - 0x2358];
	Bool m_flag241C;		// +0x241C
	char m_pad241D[0x24C8 - 0x241D];
	CameraLimit m_cameraLimits;	// +0x24C8
	char m_pad24CC[0x24FC - 0x24CC];
	HeightChangeTotal m_totalHeightChange;	// +0x24FC
	char m_pad2500[0x2503 - 0x2500];
	Bool m_flag2503;		// +0x2503
};


void W3DView::setHeightAboveGround(Real z)
{
	if (TheGameClient->m_flagC0 && m_zoomLimited)
		return;
	if (m_flag2503 || m_state2354 || m_doing1DC || m_doingZoomCamera || m_doing228 || m_doing27D || m_doing27C)
		return;

	m_totalHeightChange.add((Real)fabs(z - m_heightAboveGround));
	m_heightAboveGround = z;

	if (m_zoomLimited)
	{
		if (m_heightAboveGround < m_cameraLimits.getMinimum())
			m_heightAboveGround = m_cameraLimits.getMinimum();
		if (m_heightAboveGround > m_cameraLimits.getMaximum())
			m_heightAboveGround = m_cameraLimits.getMaximum();
	}

	m_doing1DC = false;
	m_doingZoomCamera = false;
	m_doing228 = false;
	m_doing27C = false;
	m_doing27D = false;
	m_flag241C = false;
	setCameraTransform();
}
