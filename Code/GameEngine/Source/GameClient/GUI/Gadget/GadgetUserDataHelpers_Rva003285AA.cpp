// cl: /O1 /Ob0

// ?Rva003285AA@@YAXPAVGameWindow@@H@Z, retail 0x003285AA (42B).
// Dedicated TU.
//
// Twin of Rva0032857F (0x0032857F, landed): same ensure-push-button-data
// shape, but stamps the flag byte at +0x34 and only (re)installs the user
// data on the factory path. There is no null-window guard (retail enters
// straight into winGetUserData). Adjacent bodies (0x32857F+0x2B = 0x3285AA),
// identical prologue rhythm, no direct callers yet; kept servable under its
// address until a caller names it.
//
// BFME2 facts (all retail-measured):
// - null window returns immediately (cmp [esp+4],0 shape).
// - getNewPushButtonData (0x0032843E), winGetUserData (0x005C4ACD) and
//   winSetUserData (0x002B2210, via the existing pin) all resolve from the
//   ledger, so every call stays direct E8.

class GameWindow
{
public:
	void *winGetUserData();
	void winSetUserData(void *data);
};

struct _PushButtonData;
extern _PushButtonData *getNewPushButtonData(void);

#ifndef NULL
#define NULL 0
#endif

struct Rva003285AAData
{
	char m_prefix[0x34];
	unsigned char m_flag;					// +0x34
};

// ?Rva003285AA@@YAXPAVGameWindow@@H@Z
static void Rva003285AA(GameWindow *window, int value)
{
	Rva003285AAData *data;

	data = (Rva003285AAData *)window->winGetUserData();
	if (data == NULL)
	{
		data = (Rva003285AAData *)getNewPushButtonData();
		window->winSetUserData(data);
	}
	data->m_flag = (unsigned char)value;
}

static const void *s_Rva003285AAAnchor = (const void *)Rva003285AA;
