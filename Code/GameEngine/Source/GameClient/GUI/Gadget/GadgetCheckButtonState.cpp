// cl: /DNDEBUG /MD
// ?Rva00327C39Get@@YA_NPAVGameWindow@@@Z @0x00327C39 40B
// Check-button state query: bit 25 or bit 0x80000 of GameWindow status.
// Evidence: two GameWindow::winGetStatus pin 0x0030F45F calls; 5 callers in
// 0x00327E5D push-button input; sibling checked-bit helpers nearby.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class GameWindow
{
public:
	UnsignedInt winGetStatus();
};

Bool Rva00327C39Get(GameWindow *button)
{
	UnsignedInt status = button->winGetStatus();
	Bool flag = (Bool)((status >> 25) & 1);
	if (button->winGetStatus() & 0x80000)
		flag = (Bool)1;
	return flag;
}
