// cl: /O1 /DNDEBUG /MD
//
// GadgetSlider selected-thumb border-color getters, retail 0x00323DB4 (26B)
// and 0x00323DE8 (26B). Shard TU mirroring the twin-owned
// GadgetListBox.cpp model for ?GadgetSliderGetEnabledSelectedThumbBorderColor
// (retail 0x00323D86): the thumb child via winGetChild, its border color at
// the state-specific offset, else 0x00FFFFFF. BFME1 originals at 0x004B6950
// (Disabled, +0xC4) and 0x004B6990 (Hilite, +0x130). The winGetChild calls
// resolve through the existing ?winGetChild pin at 0x003140C8; no new pins.

typedef int Int;

class GameWindow
{
public:
	GameWindow *winGetChild(void);
};

// ?GadgetSliderGetDisabledSelectedThumbBorderColor@@YAHPAVGameWindow@@@Z, retail 0x00323DB4 (26B).
Int GadgetSliderGetDisabledSelectedThumbBorderColor(GameWindow *slider)
{
	GameWindow *thumb = slider->winGetChild();
	if (thumb)
		return *(Int *)((char *)thumb + 0xc4);

	return 0x00FFFFFF;
}

// ?GadgetSliderGetHiliteSelectedThumbBorderColor@@YAHPAVGameWindow@@@Z, retail 0x00323DE8 (26B).
Int GadgetSliderGetHiliteSelectedThumbBorderColor(GameWindow *slider)
{
	GameWindow *thumb = slider->winGetChild();
	if (thumb)
		return *(Int *)((char *)thumb + 0x130);

	return 0x00FFFFFF;
}
