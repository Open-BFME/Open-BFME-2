// cl: /DNDEBUG /MD /EHsc
// ?rva002C108F@Rva0008FF12Host@@QAEXXZ, retail 0x002C108F, 185B: slot 41 of vtable 0x007FF658.
// Evidence: vslot slot 41; pin Rva0008FF12Host; caller jmp 0x0008FF1D; callee drawWindow 0x002C0FC9; TheTransitionHandler (DIR32 0x00DFDC14, the
// GameWindowTransitionsHandler global; TheAudio is the distinct pointer at 0x00DFE6E8).

#include "../../Include/GameClient/Bfme2GameWindow.h"

class GameWindowManager
{
protected:
	int drawWindow(GameWindow *window);
	friend class Rva0008FF12Host;
};

template <int N> class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0>
{
};

class GameWindowTransitionsHandler : public BfmeVirtualSlots<12>
{
public:
	virtual void slot12();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva0008FF12Host
{
public:
	void rva002C108F();
	void rva00118A90();
private:
	unsigned char m_pad00[0x10];
	GameWindow *m_head; // +0x10
	unsigned char m_pad14[0x3C - 0x14];
	int m_3C; // +0x3C
};

void Rva0008FF12Host::rva002C108F()
{
	const unsigned int hidden = 0x8000000;
	GameWindow *gameWindow = m_head;
	if (gameWindow != 0)
	{
		do
		{
			int v = gameWindow->m_bfmeCallbackExtra2;
			GameWindow *next = gameWindow->m_prev;
			if (v == m_3C)
			{
				unsigned int f = gameWindow->m_status;
				if ((f & hidden) == 0 && (f & 0x40) != 0)
					((GameWindowManager *)this)->drawWindow(gameWindow);
			}
			gameWindow = next;
		} while (gameWindow != 0);
	}
	gameWindow = m_head;
	if (gameWindow != 0)
	{
		do
		{
			int v = gameWindow->m_bfmeCallbackExtra2;
			GameWindow *next = gameWindow->m_prev;
			if (v == m_3C)
			{
				unsigned int f = gameWindow->m_status;
				if ((f & hidden) == 0 && (f & 0x60) == 0)
					((GameWindowManager *)this)->drawWindow(gameWindow);
			}
			gameWindow = next;
		} while (gameWindow != 0);
	}
	gameWindow = m_head;
	if (gameWindow != 0)
	{
		do
		{
			int v = gameWindow->m_bfmeCallbackExtra2;
			GameWindow *next = gameWindow->m_prev;
			if (v == m_3C)
			{
				unsigned int f = gameWindow->m_status;
				if ((f & hidden) == 0 && (f & 0x20) != 0)
					((GameWindowManager *)this)->drawWindow(gameWindow);
			}
			gameWindow = next;
		} while (gameWindow != 0);
	}
	if (m_3C != 1)
		return;
	GameWindowTransitionsHandler *handler = TheTransitionHandler;
	if (handler != 0)
		handler->slot12();
}
