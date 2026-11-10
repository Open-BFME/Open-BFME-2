// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
//
// ?rva00047D04@W3DDisplay@@QAEXH@Z, retail 0x00047D04..0x00047F79 (629 bytes,
// thiscall RET 4): the static-image frame pass of W3DDisplay. Under the DX8
// device mutex it prepares the frame, begins a render with a black clear
// colour and, for mode 3, only flushes the window manager singleton and ends
// the render; for every other mode it draws the static images 0, 1 and 2
// around the clipped title region, ticks the fade (rowed 0x0025D205), shows the
// optional "Frame %d" counter and broadcasts the surface size to the view's
// owner before it ends the render.
// WorldBuilder 0x00975B20 is the (unnamed) debug twin: it gives the statement
// order, retail the stack/EH shape. The original method name is not proven.
// Begin_Render is called once in each arm of the mode test, as in the debug
// twin (retail's optimiser cross-jumps them; the duplicated calls also give the
// constant 1 enough uses for the compiler to hoist it into EDI at entry).
// Layout facts (retail-measured): the display's vptr at +0, the view object at
// +0x38 (its slot +0x20 returns the frame, +0x3C takes the four region floats
// at +0xFC..+0x108 and an id, owner pointer at +0x08 -> +0x18), virtual slot
// +0x104 takes that result, +0x40/+0x44 are the unsigned width/height getters
// (the sibling Reset_D3D_Device view). The three function statics are the
// retail data cells 0x009E1B44 (frame-counter switch), 0x009E1B48 (counter
// display string) and 0x009E1C6C/0x009E1C78 (black colour and its guard word).
#include "../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);

class DX8DeviceGuard
{
public:
	DX8DeviceGuard(void)
	{
		BFME_DX8_Thread_Lock();
	}

	~DX8DeviceGuard(void)
	{
		BFME_DX8_Thread_Assert();
	}
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

extern void *ApplicationHWnd;

class GameFont;

class DisplayString
{
public:
	virtual void v00();
	virtual void setText(UnicodeString text);	// +0x04
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void setFont(GameFont *font);		// +0x18
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void slot28(int a, int b);		// +0x28
	virtual void v2C();
	virtual void v30();
	virtual void draw(int x, int y);		// +0x34
};

#include "../../../../GameEngine/Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;

#include "../../../../GameEngine/Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;

class Rva0081D520Owner
{
public:
	void broadcast(int h, float a, float b, float c, float d);
};

// The window manager singleton at 0x009FE4CC and the transition/audio cell at
// 0x009FDC14: each is only entered through its virtual slot +0x30.
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameWindowTransitionsHandler
{
public:
	virtual void a0();
	virtual void a1();
	virtual void a2();
	virtual void a3();
	virtual void a4();
	virtual void a5();
	virtual void a6();
	virtual void a7();
	virtual void a8();
	virtual void a9();
	virtual void a10();
	virtual void a11();
	virtual void slot30();				// +0x30
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva00047D04Inner
{
public:
	char m_pad00[0x18];
	Rva0081D520Owner *m_18;
};

class Rva00047D04View
{
public:
	virtual void a0();
	virtual void a1();
	virtual void a2();
	virtual void a3();
	virtual void a4();
	virtual void a5();
	virtual void a6();
	virtual void a7();
	virtual int getFrame();						// +0x20
	virtual void a9();
	virtual void a10();
	virtual void a11();
	virtual void a12();
	virtual void a13();
	virtual void a14();
	virtual int selectRegion(float x, float y, float w, float h, int id);	// +0x3C
	char m_pad04[4];
	Rva00047D04Inner *m_08;
};

#include "../../../../GameEngine/Include/GameClient/Display.h"

#include "../../../../GameEngine/Include/Common/Rva000B3FD0.h"

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
#define V16(a) V4(a##0) V4(a##1) V4(a##2) V4(a##3)

class W3DDisplay
{
public:
	V16(a)							// +0x00..+0x3C
	virtual unsigned int getWidth();			// +0x40
	virtual unsigned int getHeight();			// +0x44
	V16(b) V16(c) V4(d) V4(e) V4(f) virtual void g0(); virtual void g1(); virtual void g2();	// +0x48..+0x100
	virtual void slot104(int id);				// +0x104
	void rva00047D04(int mode);
	void rva0025D205();
private:
	char m_pad04[0x34];
	Rva00047D04View *m_38;
	char m_pad3c[0xC0];
	float m_fc;
	float m_100;
	float m_104;
	float m_108;
};

void W3DDisplay::rva00047D04(int mode)
{
	static Vector3 clearColor(0.0f, 0.0f, 0.0f);
	static bool showFrame;
	static DisplayString *frameString;

	if (ApplicationHWnd && IsIconic((HWND)ApplicationHWnd))
		return;
	DX8DeviceGuard guard;
	if (!WW3D::Prepare_Render_New_Frame())
		return;
	if (mode == 3)
	{
		if (WW3D::Begin_Render(true, false, clearColor, 0.0f) == true)
		{
			g_bfmeAptWindowManager->vslot12();
			WW3D::End_Render(true);
		}
	}
	else if (WW3D::Begin_Render(true, false, clearColor, 0.0f) == true)
	{
		((Display *)this)->DrawStaticImage(0, 1);
		((Display *)this)->DrawStaticImage(1, 1);
		slot104(m_38->selectRegion(m_fc, m_100, m_104, m_108, -1));
		((Display *)this)->DrawStaticImage(2, 1);
		rva0025D205();
		((Rva000B3FD0 *)this)->rva000B3FD0();
		Rva0081D520Owner *owner = m_38->m_08->m_18;
		if (showFrame)
		{
			if (!frameString)
			{
				frameString = TheDisplayStringManager->newDisplayString();
				{
					AsciiString fontName("FixedSys");
					frameString->setFont(TheFontLibrary->getFont(&fontName, 12.0f, false));
				}
				frameString->slot28(-1, 0);
			}
			UnicodeString text;
			text.format(L"Frame %d", m_38->getFrame());
			frameString->setText(text);
			frameString->draw(0x28, 0x28);
		}
		if (owner)
			owner->broadcast(m_38->getFrame(), 0.0f, 0.0f, (float)getWidth(), (float)getHeight());
		TheTransitionHandler->slot30();
		WW3D::End_Render(true);
	}
}
