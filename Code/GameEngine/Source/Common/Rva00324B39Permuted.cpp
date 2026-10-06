// cl: /DNDEBUG /MD
//
// ?Rva00324B39Add@@YAXPAVGameWindow@@F_N@Z, retail 0x00324b39, 86 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Free listbox scroll add: adds delta word to displayPos at +0x44 via rowed
// winGetUserData 0x005C4ACD, clamps with dword field at +0x28 against
// displayHeight at +0x3C and displayPos at +0x44, then refreshes via pinned
// Rva003249D2. Evidence: callers FUN_00725635/FUN_00725fbf push window short
// bool, unblocks 0x00325635, prev/next share /O1 /DNDEBUG /MD.
typedef int Int;
typedef short Short;

class GameWindow
{
public:
	void *winGetUserData();
};

void __cdecl Rva003249D2(GameWindow *window, bool updateSlider);

struct ListboxData00324B39
{
	char pad0[0x18];
	void *rows;
	char pad1C[0x0C];
	int field28;
	short endPosUnused;
	char pad2E[0x0E];
	short displayHeight;
	char pad3E[0x06];
	short displayPos;
};

void __cdecl Rva00324B39Add(GameWindow *window, short delta, bool update)
{
	void *userData = window->winGetUserData();
	*(short *)((char *)userData + 0x44) += delta;
	short height = *(short *)((char *)userData + 0x3C);
	short pos = *(short *)((char *)userData + 0x44);
	int tmp = *(int *)((char *)userData + 0x28) - (int)height;
	tmp++;
	if ((int)pos > tmp)
	{
		short newPos = (short)(*(short *)((char *)userData + 0x28) - height);
		*(short *)((char *)userData + 0x44) = (short)((int)newPos + 1);
	}
	if (*(short *)((char *)userData + 0x44) < 0)
		*(short *)((char *)userData + 0x44) &= 0;
	Rva003249D2(window, update);
}
