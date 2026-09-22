// ?winSetStatus@GameWindow@@QAEXI@Z
// partial score=0.93 date=2026-09-22
// cl: /O2 /Ob0

// ?Rva004BCB20@@YAXPAVGameWindow@@H@Z, retail 0x00328543 (60B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetUserDataHelpers.cpp
// (BFME1 0x004BCB20). The one gadget helper that CREATES the user data: a
// window with none gets fresh push-button data before the field is written.
// Trimmed TU: only this body is defined here; the donor's four unplaced
// siblings stay out so the unmatched gate has nothing to refuse.

class GameWindow
{
public:
	void *winGetUserData(void);
	void winSetUserData(void *data);
	void winSetStatus(unsigned int status);

private:
	char m_pad[8];
	unsigned int m_status;
};

// Push-button data: the same accessor, a different record.
struct _PushButtonData
{
};

extern _PushButtonData *getNewPushButtonData(void);

struct Rva004BCB20Data
{
	char m_prefix[0x24];
	int m_value;						// +0x24
};

// ?Rva004BCB20@@YAXPAVGameWindow@@H@Z
void Rva004BCB20(GameWindow *window, int value)
{
	if (window != 0)
	{
		Rva004BCB20Data *data =
			(Rva004BCB20Data *)window->winGetUserData();
		if (data == 0)
		{
			data = (Rva004BCB20Data *)getNewPushButtonData();
			window->winSetUserData(data);
		}
		data->m_value = value;
		window->winSetStatus(0x02000000);
	}
}

// ?winSetStatus@GameWindow@@QAEXI@Z @0x00313CE3
void GameWindow::winSetStatus(unsigned int status)
{
	m_status = status | m_status;
}
