// cl: /O1 /DNDEBUG /MD
//
// GameMessage::allocArg, retail 0x0030F8FF, 55 bytes.
// Dedicated TU so MessageStream.cpp cannot see this body.
// Argument is 0x1C with vptr then m_next; m_argCount is a byte at +0x18.

typedef unsigned char UnsignedByte;

class GameMessageArgument
{
public:
	virtual ~GameMessageArgument();
	GameMessageArgument *m_next;
	char m_bfme_body[0x1C - 0x08];
};

class GameMessage
{
	GameMessageArgument *allocArg(void);

	char m_slice_pad[0x18];
	UnsignedByte m_argCount;
	char m_slice_padB[0x1C - 0x19];
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};

GameMessageArgument *GameMessage::allocArg(void)
{
	GameMessageArgument *arg = new GameMessageArgument;

	if (m_argTail)
		m_argTail->m_next = arg;
	else
	{
		m_argList = arg;
		m_argTail = arg;
	}

	arg->m_next = 0;
	m_argTail = arg;

	m_argCount++;

	return arg;
}
