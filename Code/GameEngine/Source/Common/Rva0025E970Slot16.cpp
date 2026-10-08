// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0025E970@Rva0025E4CD@@QAEXH@Z, retail 0x0025E970..0x0025E9DE (110
// bytes, RET 4): slot 16 of Rva0025E4CD's vtable. A state at +0x10 moves from
// 0 to 1; the class's 0x0025E75F step and its own slot 15 (with the
// argument) run; in state 2 the +0x0C ConnectionManager disconnects the local
// player (rowed 0x004D15F7), message 0x1D is posted (with the integer 2
// unless TheGameLogic's +0x114 mode is 3) and the state becomes 3; a non-zero
// argument then runs 0x0025E5F4. 0x0025E75F and 0x0025E5F4 are not yet
// rowed (pinned). WorldBuilder's twin is unnamed.

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);	// rowed 0x0030F936
};

class MessageStream
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
	virtual GameMessage *appendMessage(int type);	// slot 18
};
extern MessageStream *TheMessageStream;

class ConnectionManager
{
public:
	void disconnectLocalPlayer();
};

class Rva0025E4CD
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual void slot15(int arg);
	void rva0025E970(int arg);
	void rva0025E75F();
	void rva0025E5F4();
private:
	unsigned char m_pad04[0x0C - 0x04];
	ConnectionManager *m_0C;
	int m_state10;
};

void Rva0025E4CD::rva0025E970(int arg)
{
	if (m_state10 == 0)
		m_state10 = 1;
	rva0025E75F();
	slot15(arg);
	if (m_state10 == 2)
	{
		m_0C->disconnectLocalPlayer();
		GameMessage *msg = TheMessageStream->appendMessage(0x1D);
		if (TheGameLogic->m_114 != 3)
			msg->appendIntegerArgument(2);
		m_state10 = 3;
	}
	if (arg)
		rva0025E5F4();
}
