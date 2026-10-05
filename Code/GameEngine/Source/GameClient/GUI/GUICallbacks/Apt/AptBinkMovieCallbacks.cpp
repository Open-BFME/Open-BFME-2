// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BFME2's Bink movie window Apt callback "_CallOnLastFrame", a free
// function bound by that name through the holder 0x0023E8D8 by the movie
// registration 0x0056D7A4; that binding is its only reference.

#include "ascii_string.h"

class GameWindow;

// Rva00222547Get.cpp's 0x00222547: the window whose Apt movie this one
// plays in.
GameWindow *Rva00222547Get(GameWindow *window);

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The movie window: the rowed getter 0x0056D653 answers its +0x258 name;
// +0x26C names the Apt function to run on the last frame.
class Rva0056D653AsciiField
{
public:
	AsciiString get() const;
};

struct AptBinkMovieWindow
{
	unsigned char m_pad000[0x26C];
	AsciiString m_onLastFrame; // +0x26C
};

// Retail 0x0056D6CE, 123 bytes: "_CallOnLastFrame" runs the window's
// last-frame Apt function in its movie with the window's name.
void __cdecl _CallOnLastFrame(GameWindow *window)
{
	if (!window)
		return;
	GameWindow *movie = Rva00222547Get(window);
	TheRva00222A8BTarget->invoke(movie, ((AptBinkMovieWindow *)window)->m_onLastFrame.str(), 1,
		((Rva0056D653AsciiField *)window)->get().str(), 0, 0, 0, 0);
}
