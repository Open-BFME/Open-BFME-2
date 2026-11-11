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
class RecorderClass; extern RecorderClass *TheRecorder;

#include "../../../Include/GameNetwork/NetWrapperCommandMsg.h"

#include "../../../Include/Common/RecorderClass.h"

#include "../../../Include/GameClient/GameWindowTransitionsHandler.h"
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva001DBB87ZeroSetter
{
public:
	void disable();
};

// Spelled as the data ledger primary ?g_00DFEF18@@3PAVRva002D3627Host@@A (Rva002D3627Check.cpp).
class Rva002D3627Host
{
public:
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
class LivingWorld; extern LivingWorld *TheLivingWorld;

#include "../../../../Libraries/Include/Lib/RGBColor.h"

#include "../../../Include/GameClient/Mouse.h"
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
		if (((NetWrapperCommandMsg *)((Bfme939Helper *)TheRecorder))->getData() == 0)
			TheRecorder->stopRecording();
		TheTransitionHandler->reverse(AsciiString("FadeScreenRegionToMapBlack"));
		((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
		((Rva002D3627Host *)TheLivingWorld)->slot10(1);
		((Rva002D3627Host *)TheLivingWorld)->slot19(3, 0);
	}
	else if (TheTransitionHandler->isFinished())
	{
		result = 3;
		((MouseV4CView *)TheMouse)->v19(1);
		TheMouse->_bfme_setEngineVisibility(true);
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		((Rva002D3627Host *)TheLivingWorld)->slot19(1, 0);
	}
	return result;
}
