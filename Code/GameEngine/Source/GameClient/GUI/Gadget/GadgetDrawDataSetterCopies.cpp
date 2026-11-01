// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG
// Out-of-line copies of gadget draw-data setters (Zero Hour's Gadget*.h
// inline helpers such as GadgetButtonSetEnabledImage have this shape): each
// cdecl wrapper forwards a color or image to one of GameWindow's rowed
// winSet{Enabled,Disabled,Hilite}{Image,Color,BorderColor} setters with a
// fixed draw-data index. Retail bytes fix the setter and index of each copy;
// which gadget helper each one is is not recovered, so each keeps its
// address.
class Image;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

// 0x002C0343 (16B): winSetEnabledColor at index 4.
int Rva002C0343(GameWindow *window, int color)
{
	return window->winSetEnabledColor(4, color);
}

// 0x002C0353 (16B): winSetEnabledBorderColor at index 4.
int Rva002C0353(GameWindow *window, int color)
{
	return window->winSetEnabledBorderColor(4, color);
}

// 0x002C0363 (16B): winSetEnabledImage at index 5.
int Rva002C0363(GameWindow *window, const Image *image)
{
	return window->winSetEnabledImage(5, image);
}

// 0x002C0373 (16B): winSetEnabledImage at index 6.
int Rva002C0373(GameWindow *window, const Image *image)
{
	return window->winSetEnabledImage(6, image);
}

// 0x002C0383 (16B): winSetEnabledImage at index 7.
int Rva002C0383(GameWindow *window, const Image *image)
{
	return window->winSetEnabledImage(7, image);
}

// 0x002C0393 (16B): winSetDisabledColor at index 4.
int Rva002C0393(GameWindow *window, int color)
{
	return window->winSetDisabledColor(4, color);
}

// 0x002C03A3 (16B): winSetDisabledBorderColor at index 4.
int Rva002C03A3(GameWindow *window, int color)
{
	return window->winSetDisabledBorderColor(4, color);
}

// 0x002C03B3 (16B): winSetDisabledImage at index 5.
int Rva002C03B3(GameWindow *window, const Image *image)
{
	return window->winSetDisabledImage(5, image);
}

// 0x002C03C3 (16B): winSetDisabledImage at index 6.
int Rva002C03C3(GameWindow *window, const Image *image)
{
	return window->winSetDisabledImage(6, image);
}

// 0x002C03D3 (16B): winSetDisabledImage at index 7.
int Rva002C03D3(GameWindow *window, const Image *image)
{
	return window->winSetDisabledImage(7, image);
}

// 0x002C03E3 (16B): winSetHiliteColor at index 4.
int Rva002C03E3(GameWindow *window, int color)
{
	return window->winSetHiliteColor(4, color);
}

// 0x002C03F3 (16B): winSetHiliteBorderColor at index 4.
int Rva002C03F3(GameWindow *window, int color)
{
	return window->winSetHiliteBorderColor(4, color);
}

// 0x002C0403 (16B): winSetHiliteImage at index 5.
int Rva002C0403(GameWindow *window, const Image *image)
{
	return window->winSetHiliteImage(5, image);
}

// 0x002C0413 (16B): winSetHiliteImage at index 6.
int Rva002C0413(GameWindow *window, const Image *image)
{
	return window->winSetHiliteImage(6, image);
}

// 0x002C0423 (16B): winSetHiliteImage at index 7.
int Rva002C0423(GameWindow *window, const Image *image)
{
	return window->winSetHiliteImage(7, image);
}

// 0x002C073F (16B): winSetEnabledImage at index 0.
int Rva002C073F(GameWindow *window, const Image *image)
{
	return window->winSetEnabledImage(0, image);
}

// 0x002C075F (16B): winSetEnabledBorderColor at index 0.
int Rva002C075F(GameWindow *window, int color)
{
	return window->winSetEnabledBorderColor(0, color);
}

// 0x002C076F (16B): winSetEnabledImage at index 1.
int Rva002C076F(GameWindow *window, const Image *image)
{
	return window->winSetEnabledImage(1, image);
}

// 0x002C077F (16B): winSetEnabledColor at index 1.
int Rva002C077F(GameWindow *window, int color)
{
	return window->winSetEnabledColor(1, color);
}

// 0x002C078F (16B): winSetEnabledBorderColor at index 1.
int Rva002C078F(GameWindow *window, int color)
{
	return window->winSetEnabledBorderColor(1, color);
}

// 0x002C079F (16B): winSetEnabledImage at index 2.
int Rva002C079F(GameWindow *window, const Image *image)
{
	return window->winSetEnabledImage(2, image);
}

// 0x002C07AF (16B): winSetEnabledColor at index 2.
int Rva002C07AF(GameWindow *window, int color)
{
	return window->winSetEnabledColor(2, color);
}

// 0x002C07BF (16B): winSetEnabledBorderColor at index 2.
int Rva002C07BF(GameWindow *window, int color)
{
	return window->winSetEnabledBorderColor(2, color);
}

// 0x002C07CF (16B): winSetDisabledImage at index 0.
int Rva002C07CF(GameWindow *window, const Image *image)
{
	return window->winSetDisabledImage(0, image);
}

// 0x002C07DF (16B): winSetDisabledColor at index 0.
int Rva002C07DF(GameWindow *window, int color)
{
	return window->winSetDisabledColor(0, color);
}

// 0x002C07EF (16B): winSetDisabledBorderColor at index 0.
int Rva002C07EF(GameWindow *window, int color)
{
	return window->winSetDisabledBorderColor(0, color);
}

// 0x002C07FF (16B): winSetDisabledImage at index 1.
int Rva002C07FF(GameWindow *window, const Image *image)
{
	return window->winSetDisabledImage(1, image);
}

// 0x002C080F (16B): winSetDisabledColor at index 1.
int Rva002C080F(GameWindow *window, int color)
{
	return window->winSetDisabledColor(1, color);
}

// 0x002C081F (16B): winSetDisabledBorderColor at index 1.
int Rva002C081F(GameWindow *window, int color)
{
	return window->winSetDisabledBorderColor(1, color);
}

// 0x002C082F (16B): winSetDisabledImage at index 2.
int Rva002C082F(GameWindow *window, const Image *image)
{
	return window->winSetDisabledImage(2, image);
}

// 0x002C083F (16B): winSetDisabledColor at index 2.
int Rva002C083F(GameWindow *window, int color)
{
	return window->winSetDisabledColor(2, color);
}

// 0x002C084F (16B): winSetDisabledBorderColor at index 2.
int Rva002C084F(GameWindow *window, int color)
{
	return window->winSetDisabledBorderColor(2, color);
}

// 0x002C085F (16B): winSetHiliteImage at index 0.
int Rva002C085F(GameWindow *window, const Image *image)
{
	return window->winSetHiliteImage(0, image);
}

// 0x002C086F (16B): winSetHiliteColor at index 0.
int Rva002C086F(GameWindow *window, int color)
{
	return window->winSetHiliteColor(0, color);
}

// 0x002C087F (16B): winSetHiliteBorderColor at index 0.
int Rva002C087F(GameWindow *window, int color)
{
	return window->winSetHiliteBorderColor(0, color);
}

// 0x002C088F (16B): winSetHiliteImage at index 1.
int Rva002C088F(GameWindow *window, const Image *image)
{
	return window->winSetHiliteImage(1, image);
}

// 0x002C089F (16B): winSetHiliteColor at index 1.
int Rva002C089F(GameWindow *window, int color)
{
	return window->winSetHiliteColor(1, color);
}

// 0x002C08AF (16B): winSetHiliteBorderColor at index 1.
int Rva002C08AF(GameWindow *window, int color)
{
	return window->winSetHiliteBorderColor(1, color);
}

// 0x002C08BF (16B): winSetHiliteImage at index 2.
int Rva002C08BF(GameWindow *window, const Image *image)
{
	return window->winSetHiliteImage(2, image);
}

// 0x002C08CF (16B): winSetHiliteColor at index 2.
int Rva002C08CF(GameWindow *window, int color)
{
	return window->winSetHiliteColor(2, color);
}

// 0x002C08DF (16B): winSetHiliteBorderColor at index 2.
int Rva002C08DF(GameWindow *window, int color)
{
	return window->winSetHiliteBorderColor(2, color);
}
