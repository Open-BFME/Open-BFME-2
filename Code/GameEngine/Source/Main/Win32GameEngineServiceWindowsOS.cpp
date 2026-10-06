// cl: /DNDEBUG /MD /EHsc
// ?rva00042121@Win32GameEngine@@UAEXXZ @0x00042121 163B
// Win32 message pump with WM_TIMER audio notify. Evidence: vtable 0x007C2530
// slot 23 of Win32GameEngine; TheMessageTime 0x009E1B20; Peek/Get/Translate/
// Dispatch user32 IAT; WM_TIMER 0x113 double-check calling rowed
// ?rva00041D22 then ?rva00041D03; donor BFME1
// Win32GameEngine_update.cpp serviceWindowsOS plus ZH Win32GameEngine.cpp.
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned int UINT;
typedef long LPARAM;
typedef unsigned int WPARAM;
typedef void *HWND;
struct POINT { long x; long y; };
struct MSG {
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	POINT pt;
};
extern "C" {
__declspec(dllimport) BOOL __stdcall PeekMessageA(MSG *, HWND, UINT, UINT, UINT);
__declspec(dllimport) BOOL __stdcall GetMessageA(MSG *, HWND, UINT, UINT);
__declspec(dllimport) BOOL __stdcall TranslateMessage(const MSG *);
__declspec(dllimport) long __stdcall DispatchMessageA(const MSG *);
}
extern DWORD TheMessageTime;
class Rva00041D03
{
public:
	Rva00041D03() { m_flag = false; }
	~Rva00041D03() { rva00041D03(); }
	void rva00041D03();
	void rva00041D22();
private:
	bool m_flag;
};
class Win32GameEngine
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void rva00042121();
};
void Win32GameEngine::rva00042121()
{
	MSG msg;
	while (PeekMessageA(&msg, 0, 0, 0, 0)) {
		Rva00041D03 guard;
		GetMessageA(&msg, 0, 0, 0);
		if (msg.message == 0x113)
			guard.rva00041D22();
		TheMessageTime = msg.time;
		TranslateMessage(&msg);
		if (msg.message == 0x113)
			guard.rva00041D22();
		DispatchMessageA(&msg);
		TheMessageTime = 0;
	}
}
