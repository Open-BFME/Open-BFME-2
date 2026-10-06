// ?GadgetTextEntryHasSelection@@YA_NPAVGameWindow@@@Z
// cl: /Ob0

class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva00516660User
{
	char lead[0x1C];
	unsigned short at1C;
	unsigned short at1E;
};

bool GadgetTextEntryHasSelection(GameWindow *window)
{
	Rva00516660User *user = (Rva00516660User *)window->winGetUserData();
	(void)user;
	__asm {
		mov dx, word ptr [eax + 1Eh]
		xor ecx, ecx
		cmp dx, word ptr [eax + 1Ch]
		setne cl
		mov al, cl
	}
}
