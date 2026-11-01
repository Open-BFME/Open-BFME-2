// cl: /DNDEBUG /MD
//
// GameMessage::allocArg, retail 0x0030F8FF, 55 bytes.
// Dedicated TU so MessageStream.cpp cannot see this body.
// Argument is 0x1C with vptr then m_next; m_argCount is a byte at +0x18.

typedef unsigned char UnsignedByte;

extern "C" const void *const __identifier("??_7BfmeNetGameMessageArgument@@6B@")[];

class GameMessageArgument
{
public:
	GameMessageArgument() { m_vptr = __identifier("??_7BfmeNetGameMessageArgument@@6B@"); }
	const void *m_vptr;
	GameMessageArgument *m_next;
	char m_bfme_body[0x1C - 0x08];
};

#include "../../Include/Common/MessageStream.h"

GameMessageArgument *GameMessage::allocArg(void)
{
	GameMessageArgument *gameMessageArgument = new GameMessageArgument;

	if (m_argTail)
		m_argTail->m_next = gameMessageArgument;
	else
	{
		m_argList = gameMessageArgument;
		m_argTail = gameMessageArgument;
	}

	gameMessageArgument->m_next = 0;
	m_argTail = gameMessageArgument;

	m_argCount++;

	return gameMessageArgument;
}

