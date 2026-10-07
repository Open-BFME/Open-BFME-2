// cl: /DNDEBUG /MD
// ?Rva00327E0EGet@@YA_NPAVGameWindow@@@Z @0x00327E0E 20B
// Push-button user-data flag reader: returns the byte at +0x34 of the
// window's user data, false when there is none. Unlike its neighbours
// 0x00327DD8 and 0x00327DF6 it does not test the window for NULL.
// Evidence: GameWindow::winGetUserData row 0x005C4ACD; the next body,
// 0x00327E22, is the rowed _PushButtonData constructor; caller
// W3DGadgetPushButtonImageDrawOne 0x000A56ED, which picks the 0xFF808080
// colour multiplier for a grayscale-drawn disabled button when it is set.

typedef bool Bool;

class GameWindow
{
public:
	void *winGetUserData();
};

struct Rva00327E0EHolder
{
	char m_pad[0x34];
	Bool m_flag;
};

Bool Rva00327E0EGet(GameWindow *button)
{
	Rva00327E0EHolder *holder = (Rva00327E0EHolder *)button->winGetUserData();
	if (holder)
		return holder->m_flag;
	return false;
}
