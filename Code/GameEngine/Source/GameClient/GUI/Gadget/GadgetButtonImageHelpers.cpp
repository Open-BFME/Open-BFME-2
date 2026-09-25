// cl: /O1 /DNDEBUG /MD

// Gadget push-button image helpers (retail 0x002C0433..0x002C0505, 6x42B).
// Each sets one button image slot and clears two overlay slots. Callees are
// the rowed ?winSetEnabledImage (0x3143B9), ?winSetDisabledImage (0x314421)
// and ?winSetHiliteImage (0x31448F) in GameWindowFields.cpp. The 0/5/6 trio
// serves the main button face; the 1/2/3 trio serves the secondary face.
// Names carry the retail address (no donor defines these BFME2-new slots).
class Image;

class GameWindow
{
public:
	int winSetEnabledImage(int index, const Image *image);
	int winSetDisabledImage(int index, const Image *image);
	int winSetHiliteImage(int index, const Image *image);
};

#ifndef NULL
#define NULL 0
#endif

// ?GadgetButtonSetEnabledImage_Rva002C0433@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *win, const Image *image)
{
	win->winSetEnabledImage(0, image);
	win->winSetEnabledImage(5, NULL);
	win->winSetEnabledImage(6, NULL);
}

// ?GadgetButtonSetEnabledImage123_Rva002C045D@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetEnabledImage123_Rva002C045D(GameWindow *win, const Image *image)
{
	win->winSetEnabledImage(1, image);
	win->winSetEnabledImage(2, NULL);
	win->winSetEnabledImage(3, NULL);
}

// ?GadgetButtonSetDisabledImage_Rva002C0487@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetDisabledImage_Rva002C0487(GameWindow *win, const Image *image)
{
	win->winSetDisabledImage(0, image);
	win->winSetEnabledImage(5, NULL);
	win->winSetEnabledImage(6, NULL);
}

// ?GadgetButtonSetDisabledImage123_Rva002C04B1@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetDisabledImage123_Rva002C04B1(GameWindow *win, const Image *image)
{
	win->winSetDisabledImage(1, image);
	win->winSetEnabledImage(2, NULL);
	win->winSetEnabledImage(3, NULL);
}

// ?GadgetButtonSetHiliteImage_Rva002C04DB@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetHiliteImage_Rva002C04DB(GameWindow *win, const Image *image)
{
	win->winSetHiliteImage(0, image);
	win->winSetEnabledImage(5, NULL);
	win->winSetEnabledImage(6, NULL);
}

// ?GadgetButtonSetHiliteImage123_Rva002C0505@@YAXPAVGameWindow@@PBVImage@@@Z
void GadgetButtonSetHiliteImage123_Rva002C0505(GameWindow *win, const Image *image)
{
	win->winSetHiliteImage(1, image);
	win->winSetEnabledImage(2, NULL);
	win->winSetEnabledImage(3, NULL);
}
