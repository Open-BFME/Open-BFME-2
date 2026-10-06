// cl: /DNDEBUG /MD
//
// ?rva0023C83B@Rva0023C83B@@QAEPAV1@XZ @0x0023C83B, 35B.
// Window close enabler returning this: GetSystemMenu on 0x00DDE024 then
// EnableMenuItem with SC_CLOSE 0xF060 flags 1, return this for chaining.
// Retail: push esi; push 0; push [0xDDE024]; mov esi,ecx; call GetSystemMenu;
// push 1; push 0xF060; push eax; call EnableMenuItem; mov eax,esi; pop esi; ret.
// Evidence: sole caller 0x00248581 (lea ecx,[ebp+8] ignores return); window
// global proven by rowed ?clipCursorToClient@@YAXXZ; pair of free disable
// ?Rva0023C85EDisable@@YAXXZ at 0x0023C85E (flags 0 vs 1). Imports are IAT
// so dllimport. Owner unproven so Rva class returning own pointer.

extern void *ApplicationHWnd;

extern "C" __declspec(dllimport) void *__stdcall GetSystemMenu(void *wnd, int revert);
extern "C" __declspec(dllimport) int __stdcall EnableMenuItem(void *menu, unsigned id, unsigned flags);

class Rva0023C83B
{
public:
	Rva0023C83B *rva0023C83B();
};

Rva0023C83B *Rva0023C83B::rva0023C83B()
{
	void *menu = GetSystemMenu(ApplicationHWnd, 0);
	EnableMenuItem(menu, 0xF060, 1);
	return this;
}
