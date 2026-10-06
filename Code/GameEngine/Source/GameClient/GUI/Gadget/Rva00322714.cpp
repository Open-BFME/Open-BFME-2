// cl: /O1 /DNDEBUG /MD
//
// ?Rva00322714@@YAXPAVBfmeKeyLC@@HE@Z, retail 0x00322714, 39 bytes.
// Gadget item-data helper: if arg1 null return; bfmeGo925A(arg1) null return;
// else Rva0032431FSet(bfmeGo result, arg2, arg3). Callees all rowed per packet
// (bfmeGo925A 0x002C0315, Rva0032431FSet 0x0032431F). Evidence: caller
// MpGameSetup 0x00440964 (push 1/esi/ebx), neighbours GadgetComboBox.cpp
// prev 0x00322703 next 0x0032273B same flags, pop-ecx stack clean for size.

class BfmeKeyLC;
class GameWindow;
void * __cdecl bfmeGo925A(BfmeKeyLC *key);
void __cdecl Rva0032431FSet(GameWindow *window, int a, unsigned char b);

void __cdecl Rva00322714(BfmeKeyLC *a, int b, unsigned char c)
{
	if (!a)
		return;
	void *v = bfmeGo925A(a);
	if (!v)
		return;
	Rva0032431FSet((GameWindow *)v, b, c);
}
