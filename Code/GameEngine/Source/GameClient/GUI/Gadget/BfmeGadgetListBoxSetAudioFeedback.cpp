// cl: /DNDEBUG /MD
// Retail RVA 0x0032497D, 21 bytes.
// BfmeGadgetListBoxSetAudioFeedback, the BFME listbox audio-feedback flag.
// Ported from Open-BFME-1 AptScreenFactories.cpp; the flag is the byte at
// +0x10 of the listbox user data. Dedicated TU so the GadgetListBox.cpp
// file-unit (twin-owned) stays untouched. The TU defines only this body.

typedef int Int;
typedef bool Bool;
typedef short Short;

class GameWindow
{
public:
	void *winGetUserData(void);
};

void BfmeGadgetListBoxSetAudioFeedback(GameWindow *listBox, Bool enabled)
{
	if (listBox)
	{
		unsigned char *userData = (unsigned char *)listBox->winGetUserData();
		userData[0x10] = (unsigned char)enabled;
	}
}
