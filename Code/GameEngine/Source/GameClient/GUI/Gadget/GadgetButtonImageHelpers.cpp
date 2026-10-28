// cl: /DNDEBUG /MD
// platformsdk

// Gadget push-button image helpers (retail 0x002C0433..0x002C0505, 6x42B).
// Each sets one button image slot and clears two overlay slots. Callees are
// the rowed ?winSetEnabledImage (0x3143B9), ?winSetDisabledImage (0x314421)
// and ?winSetHiliteImage (0x31448F) in GameWindowFields.cpp. The 0/5/6 trio
// serves the main button face; the 1/2/3 trio serves the secondary face.
// Names carry the retail address (no donor defines these BFME2-new slots).
#include <windows.h>

class Image;

class GameWindow
{
public:
	int winSetEnabledImage(int index, const Image *image);
	int winSetDisabledImage(int index, const Image *image);
	int winSetHiliteImage(int index, const Image *image);
};

// ?GadgetButtonSetEnabledImage@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetEnabledImage(GameWindow *win, const Image *image)
{
	win->winSetEnabledImage(0, image);
	win->winSetEnabledImage(5, NULL);
	win->winSetEnabledImage(6, NULL);
}

// ?GadgetButtonSetEnabledSelectedImage@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetEnabledSelectedImage(GameWindow *win, const Image *image)
{
	win->winSetEnabledImage(1, image);
	win->winSetEnabledImage(2, NULL);
	win->winSetEnabledImage(3, NULL);
}

// ?GadgetButtonSetDisabledImage@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetDisabledImage(GameWindow *win, const Image *image)
{
	win->winSetDisabledImage(0, image);
	win->winSetEnabledImage(5, NULL);
	win->winSetEnabledImage(6, NULL);
}

// ?GadgetButtonSetDisabledSelectedImage@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetDisabledSelectedImage(GameWindow *win, const Image *image)
{
	win->winSetDisabledImage(1, image);
	win->winSetEnabledImage(2, NULL);
	win->winSetEnabledImage(3, NULL);
}

// ?GadgetButtonSetHiliteImage@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetHiliteImage(GameWindow *win, const Image *image)
{
	win->winSetHiliteImage(0, image);
	win->winSetEnabledImage(5, NULL);
	win->winSetEnabledImage(6, NULL);
}

// ?GadgetButtonSetHiliteSelectedImage@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetHiliteSelectedImage(GameWindow *win, const Image *image)
{
	win->winSetHiliteImage(1, image);
	win->winSetEnabledImage(2, NULL);
	win->winSetEnabledImage(3, NULL);
}
