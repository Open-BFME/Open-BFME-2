// cl: /O1 /DNDEBUG /MD
//
// ?GadgetComboDisableEntry@@YAXPAVBfmeKeyLC@@HE@Z, retail 0x00322714, 39 bytes.
// Gadget item-data helper: if arg1 null return; bfmeGo925A(arg1) null return;
// else GadgetListBoxDisableEntry(bfmeGo result, arg2, arg3). Callees all rowed per packet
// (bfmeGo925A 0x002C0315, Rva0032431FSet 0x0032431F). Evidence: caller
// MpGameSetup 0x00440964 (push 1/esi/ebx), neighbours GadgetComboBox.cpp
// prev 0x00322703 next 0x0032273B same flags, pop-ecx stack clean for size.

class BfmeKeyLC;
class GameWindow;
void * __cdecl bfmeGo925A(BfmeKeyLC *key);
void __cdecl GadgetListBoxDisableEntry(GameWindow *window, int a, unsigned char b);

// WorldBuilder GadgetComboDisableEntry, WB VA 0x013AD4E0 (align lead, score 1.0).
void __cdecl GadgetComboDisableEntry(BfmeKeyLC *comboBox, int b, unsigned char disabled)
{
	if (!comboBox)
		return;
	void *listBox = bfmeGo925A(comboBox);
	if (!listBox)
		return;
	GadgetListBoxDisableEntry((GameWindow *)listBox, b, disabled);
}
