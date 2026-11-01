// cl: /DNDEBUG /MD
// ?rva00323674@Rva00323674@@QBEHXZ @0x00323674 (44B) __thiscall getter:
// null-check this+0, read user-data +8 as GameWindow*, call rowed
// GadgetListBoxGetSelected (0x00324773) with a stack -1, return it.
#include "../../../../Include/GameClient/Bfme2GameWindow.h"
void GadgetListBoxGetSelected(GameWindow *win, int *sel);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct UserData00323674
{
	char m_pad[8];
	GameWindow *m_8;
};
class Rva00323674
{
public:
	Rva00323674(GameWindow *window);
	~Rva00323674();
	int rva00323674() const;
private:
	GameWindow *m_0;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline int Rva00323674::rva00323674() const
{
	GameWindow *win = m_0;
	if (win == 0)
		return -1;
	int sel = -1;
	UserData00323674 *user = reinterpret_cast<UserData00323674 *>(win->winGetUserData());
	GameWindow *listWin = user->m_8;
	_ReadWriteBarrier();
	GadgetListBoxGetSelected(listWin, &sel);
	return sel;
}

// ?bfmeAnchorRva00323674 absent-from-retail
int bfmeAnchorRva00323674(const Rva00323674 *p)
{
	return p->rva00323674();
}


// ??0Rva00323674@@QAE@PAVGameWindow@@@Z and ??1Rva00323674@@QAE@XZ: the
// wrapper's out-of-line constructor (store the window, return this) and
// empty destructor. Retail W3DGadgetImageComboBoxDraw (0x000A24BA) calls
// both by address inside an EH state, so neither body was visible to it;
// ICF folded them into the shared one-pointer store 0x0007B719 and the
// shared RET 0x000B3FD0.
Rva00323674::Rva00323674(GameWindow *window) : m_0(window)
{
}

Rva00323674::~Rva00323674()
{
}

// ?bfmeAnchorWindowWrapperSelected absent-from-retail
int bfmeAnchorWindowWrapperSelected(const Rva00323674 *wrapper)
{
    return wrapper->rva00323674();
}
