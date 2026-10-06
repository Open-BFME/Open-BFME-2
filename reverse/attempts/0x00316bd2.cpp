// ?createWindowStatic@@YAPAVGameWindow@@PADHPAXPAV1@@Z
// partial score=0.5004 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?createWindow@@YAPAVGameWindow@@PADHPAUHINSTANCE__@@PAVGameWindow@@@Z, retail 0x00316BD2, 294 bytes.
// Evidence: caller at 0x316CCE is createWindow per setWindowText TU; called twice from parseWindow FUN_00716e8f; handles USER/TABPANE else createGadget; sets callback strings; text via setWindowText; notify via TheWindowManager 0xec. First attempt.

#include "ascii_string.h"

class GameWindow;
class WinInstanceData;
class GadgetCreateView;

class WinInstanceData
{
public:
	char _pad0[0xd];
	unsigned char m_flagByte;
	char _pad1[0x188 - 0xe];
	AsciiString m_displayString;
};

class GameWindow
{
public:
	virtual ~GameWindow();
	char _pad0[0x2c];
	WinInstanceData *m_instData;
	int winSetInstanceData(WinInstanceData *inst);
	int rva0031404A(int v);
	int getRva0031450A(void);
};

class GameWindowManager
{
public:
	virtual ~GameWindowManager();
	virtual void f01(); virtual void f02(); virtual void f03(); virtual void f04();
	virtual void f05(); virtual void f06(); virtual void f07(); virtual void f08();
	virtual void f09(); virtual void f10(); virtual void f11(); virtual void f12();
	virtual void f13(); virtual void f14(); virtual void f15(); virtual void f16();
	virtual void f17(); virtual void f18(); virtual void f19(); virtual void f20();
	virtual void f21(); virtual void f22(); virtual void f23(); virtual void f24();
	virtual void f25(); virtual void f26(); virtual void f27(); virtual void f28();
	virtual void f29(); virtual void f30(); virtual void f31(); virtual void f32();
	virtual void f33();
	virtual GameWindow *v88(void *parent);
	virtual void g35(); virtual void g36(); virtual void g37(); virtual void g38();
	virtual void g39(); virtual void g40(); virtual void g41(); virtual void g42();
	virtual void g43(); virtual void g44(); virtual void g45(); virtual void g46();
	virtual void g47(); virtual void g48(); virtual void g49(); virtual void g50();
	virtual void g51(); virtual void g52(); virtual void g53(); virtual void g54();
	virtual void g55(); virtual void g56(); virtual void g57(); virtual void g58();
	virtual void vEC(GameWindow *a, int b, int c, int d);
};

extern GameWindowManager *TheWindowManager;
extern "C" int __cdecl strcmp(const char *a, const char *b);

GameWindow *peekWindow(void);
GameWindow *createGadget(char *type, void *data, GadgetCreateView *view, GameWindow *parent);
void setWindowText(GameWindow *window, AsciiString text);

extern AsciiString g_systemCallbackName;
extern "C" AsciiString theInputString;
extern "C" AsciiString theTooltipString;
extern "C" AsciiString theDrawString;

struct WinCallbackStrings
{
	AsciiString m_system;
	AsciiString m_input;
	AsciiString m_tooltip;
	AsciiString m_draw;
};

// ?Rva00316BD2Create@@YAPAVGameWindow@@PADHPAXPAV1@@Z present-unmatched
__declspec(noinline) static GameWindow *createWindowStatic(char *type, int id, void *data, GameWindow *parent)
{
	GameWindow *peek = peekWindow();
	GameWindow *window;
	WinCallbackStrings *cb;
	if (strcmp(type, "USER") == 0)
	{
		window = TheWindowManager->v88(parent);
		if (window == NULL)
			return NULL;
		parent->m_instData->m_flagByte |= 2;
		goto haveWindow;
	}
	if (strcmp(type, "TABPANE") == 0)
	{
		window = TheWindowManager->v88(parent);
		if (window == NULL)
			return NULL;
		parent->m_instData->m_flagByte |= 0x40;
		window->winSetInstanceData(parent->m_instData);
		goto haveWindow;
	}
	window = createGadget(type, data, (GadgetCreateView *)parent, NULL);
	if (window == NULL)
		return NULL;
haveWindow:
	window->rva0031404A(id);
	cb = (WinCallbackStrings *)window->getRva0031450A();
	if (cb)
	{
		cb->m_system.set(g_systemCallbackName);
		cb->m_input.set(theInputString);
		cb->m_tooltip.set(theTooltipString);
		cb->m_draw.set(theDrawString);
		setWindowText(window, parent->m_instData->m_displayString);
	}
	if (peek)
	{
		TheWindowManager->vEC(peek, 0x16, id, 0);
	}
	return window;
}

// Codegen scaffold: retail passes the global base in EDI (custom static-call).
// A visible caller forces MSVC's private ABI like setWindowTextCaller precedent.
// ?createWindowCaller absent-from-retail
GameWindow *createWindowCaller(char *type, int id, void *data, GameWindow *parent)
{
	return createWindowStatic(type, id, data, parent);
}
