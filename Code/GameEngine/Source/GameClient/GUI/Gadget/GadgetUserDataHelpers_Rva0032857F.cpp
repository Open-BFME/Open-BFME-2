// cl: /O1 /Ob0

// ?Rva0032857F@@YAXPAVGameWindow@@H@Z, retail 0x0032857F (43B).
// Dedicated TU.
//
// Slider-thumb user-data helper in the GadgetUserDataHelpers family (see
// Rva004BCB20 at 0x00328543 in GadgetUserDataHelpers.cpp for the founding
// member and the GameWindow/winGetUserData/winSetUserData idiom reused
// here). Called from the two slider arms of createGadget (retail
// 0x00316518) when the thumb window carries extra data: ensures the thumb
// has push-button user data, stamps the flag byte at +0x20 and (re)installs
// it. Unlike Rva004BCB20 this body always reinstalls, even when the data
// was already present.
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

#ifndef NULL
#define NULL 0
#endif

struct _PushButtonData;
extern _PushButtonData *getNewPushButtonData(void);

struct Rva0032857FData
{
	char m_prefix[0x20];
	unsigned char m_flag;					// +0x20
};

// ?Rva0032857F@@YAXPAVGameWindow@@H@Z
static void Rva0032857F(GameWindow *window, int value)
{
	Rva0032857FData *data;

	if (window == NULL)
		return;

	data = (Rva0032857FData *)window->winGetUserData();
	if (data == NULL)
		data = (Rva0032857FData *)getNewPushButtonData();
	data->m_flag = (unsigned char)value;
	window->winSetUserData(data);
}

static const void *s_Rva0032857FAnchor = (const void *)Rva0032857F;
