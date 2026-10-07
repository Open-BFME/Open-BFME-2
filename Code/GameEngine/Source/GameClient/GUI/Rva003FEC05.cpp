// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"

// ?Rva003FEC05FadeScreenRegionToMapBlack@@YAHH_N@Z @0x003FEC05 197B. Free __cdecl step
// returning 1 or 3 from bool start (second arg, first int unused), same family as
// rva00565170 (FadeScreenToBlack): on start, NetWrapper check + stopRecording,
// reverse("FadeScreenRegionToMapBlack"), disable, host slots 0x28(1) and 0x4c(3,0);
// on !start, if isFinished then mouse 0x4c(1), setEngineVisibility(true),
// tooltip(Empty,-1,0,1.0f), host 0x4c(1,0). Evidence: callers as constants at
// 0x0021206C and 0x0051EE4B; literals FadeScreenRegionToMapBlack and TheEmptyString.

struct Bfme939Helper;
extern Bfme939Helper *g_bfme939Helper;

class NetWrapperCommandMsg
{
public:
	unsigned char *getData();
};

class RecorderClass
{
public:
	void stopRecording();
};

class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString s);
	bool isFinished();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva001DBB87ZeroSetter
{
public:
	void disable();
};

struct Rva003FEC05Host
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void slot10(int a);
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void slot19(int a, int b);
};
extern Rva003FEC05Host *g_00DFEF18;

struct RGBColor
{
	float red, green, blue;
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool on);
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};
extern Mouse *TheMouse;

struct MouseV4CView
{
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6();
	virtual void m7();
	virtual void m8();
	virtual void m9();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual void m18();
	virtual void v19(int a);
};

int Rva003FEC05FadeScreenRegionToMapBlack(int, bool start)
{
	int result = 1;
	if (start)
	{
		if (((NetWrapperCommandMsg *)g_bfme939Helper)->getData() == 0)
			((RecorderClass *)g_bfme939Helper)->stopRecording();
		TheTransitionHandler->reverse(AsciiString("FadeScreenRegionToMapBlack"));
		((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
		g_00DFEF18->slot10(1);
		g_00DFEF18->slot19(3, 0);
	}
	else if (TheTransitionHandler->isFinished())
	{
		result = 3;
		((MouseV4CView *)TheMouse)->v19(1);
		TheMouse->_bfme_setEngineVisibility(true);
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		g_00DFEF18->slot19(1, 0);
	}
	return result;
}
