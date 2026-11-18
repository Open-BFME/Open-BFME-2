// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?setFadeParameters@W3DView@@UAEXHH@Z, retail 0x00085EC7 (62 bytes, RET 8), W3DView vtable
// 0x007C7530 slot 62. Zero Hour's W3DView::setFadeParameters hands the fade length and
// direction to the screen filters: ScreenBWFilter's inline static setter (0x00DEC1A4..AC),
// the rowed 0x00085553 for the next filter, and the cross-fade filter's frame/direction
// statics (0x00DEBFF8..0x00DEC000, defined in ScreenCrossFadeFilterUpdateFadeLevel.cpp).
#include "../../../../GameEngine/Include/Common/ScalarTypes.h"


class ScreenBWFilter
{
public:
	static void setFadeParameters(Int fadeFrames, Int direction)
	{
		m_curFadeFrame = 0;
		m_fadeFrames = fadeFrames;
		m_fadeDirection = direction;
	}
	static Int m_fadeFrames;
	static Int m_fadeDirection;
	static Int m_curFadeFrame;
};

void Rva00085553Get(int a, int b);

class ScreenCrossFadeFilter
{
public:
	static Int m_fadeFrames;
	static Int m_curFadeFrame;
	static Int m_fadeDirection;
};

class W3DView
{
public:
	virtual void setFadeParameters(Int fadeFrames, Int direction);
};

void W3DView::setFadeParameters(Int fadeFrames, Int direction)
{
	ScreenBWFilter::setFadeParameters(fadeFrames, direction);
	Rva00085553Get(fadeFrames, direction);
	ScreenCrossFadeFilter::m_curFadeFrame = 0;
	ScreenCrossFadeFilter::m_fadeDirection = direction;
	ScreenCrossFadeFilter::m_fadeFrames = fadeFrames;
}
