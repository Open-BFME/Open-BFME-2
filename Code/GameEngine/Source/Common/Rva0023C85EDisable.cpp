// cl: /DNDEBUG /MD
//
// ?Rva0023C85EDisable@@YAXXZ @0x0023C85E, 29B.
// Free helper disabling the main window close item: GetSystemMenu on the
// window at 0x00DDE024 then EnableMenuItem with SC_CLOSE 0xF060.
// Evidence: callers 0x00248767 (lea ecx,[ebp+8] ignores return) and
// 0x00048DAE; window global proven by rowed ?clipCursorToClient@@YAXXZ
// (W3DDisplayClipCursor.cpp) which uses the same 0x00DDE024 handle;
// imports GetSystemMenu/EnableMenuItem are IAT (FF 15) so dllimport.
// No // stlport, no EH frame.

extern void *ApplicationHWnd;

extern "C" __declspec(dllimport) void *__stdcall GetSystemMenu(void *wnd, int revert);
extern "C" __declspec(dllimport) int __stdcall EnableMenuItem(void *menu, unsigned id, unsigned flags);

void Rva0023C85EDisable()
{
	void *menu = GetSystemMenu(ApplicationHWnd, 0);
	EnableMenuItem(menu, 0xF060, 0);
}
