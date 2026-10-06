// cl: /DNDEBUG /MD
// ?Rva00327DD8Get@@YAPAXPAVGameWindow@@@Z @0x00327DD8 30B
// Null-guarded user-data field reader: returns the pointer at +0x2C when the
// flag byte at +0x28 is set. Evidence: GameWindow::winGetUserData row 0x005C4ACD;
// sibling ?GadgetButtonGetData@@YAPAXPAVGameWindow@@@Z at 0x00327D56.

typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class GameWindow
{
public:
	void *winGetUserData();
};

struct Rva00327DD8Holder
{
	char m_pad[0x28];
	Bool m_flag;
	char m_pad2[3];
	void *m_ptr;
};

void *Rva00327DD8Get(GameWindow *button)
{
	if (button == NULL)
		return NULL;
	void *userData = button->winGetUserData();
	if (userData == NULL)
		return NULL;
	Rva00327DD8Holder *holder = (Rva00327DD8Holder *)userData;
	if (holder->m_flag)
		return holder->m_ptr;
	return NULL;
}
