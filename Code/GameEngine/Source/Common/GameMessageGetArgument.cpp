// cl: /DNDEBUG /MD
//
// ?getArgument@GameMessage@@QBEPBTGameMessageArgumentType@@H@Z retail 0x0030F4EA 34 bytes.
// GameMessage::getArgument from ZH MessageStream.cpp donor verbatim: walks
// m_argList at +0x1C via m_next at +4 counting edx; on edx==index returns
// &a->m_data at +8; else returns static junk at 0x0086BB18.
// Layout matches GameMessageAllocArg.cpp (m_argCount byte at +0x18 m_argList
// at +0x1C) and GameMessageIntWideArgs.cpp (m_data at +0x08 m_type at +0x18
// total 0x1C). DEBUG_CRASH compiles out under DNDEBUG leaving the 34B loop.
// Evidence: donor MessageStream.cpp getArgument; 40+ callers passing indices;
// junk global 0x0086BB18; prev/next both MessageStreamListCtors.cpp.

typedef unsigned char UnsignedByte;

union GameMessageArgumentType
{
	int integer;
	float real;
	int boolean;
	int objectID;
	int drawableID;
	unsigned int teamID;
	struct Loc { float x; float y; float z; } location;
	struct Pix { int x; int y; } pixel;
	struct PixReg { int loX; int loY; int hiX; int hiY; } pixelRegion;
	unsigned int timestamp;
	unsigned short wChar;
};

class GameMessageArgument
{
public:
	virtual ~GameMessageArgument();
	GameMessageArgument *m_next; // +0x04
	GameMessageArgumentType m_data; // +0x08
	int m_type; // +0x18
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;

private:
	char m_slice_pad[0x18];
	UnsignedByte m_argCount; // +0x18
	char m_slice_padB[0x1C - 0x19];
	GameMessageArgument *m_argList; // +0x1C
	GameMessageArgument *m_argTail;
};

const GameMessageArgumentType *GameMessage::getArgument(int argIndex) const
{
	static const GameMessageArgumentType junk = { 0 };

	int i = 0;
	for (GameMessageArgument *a = m_argList; a; a = a->m_next, i++)
		if (i == argIndex)
			return &a->m_data;

	return &junk;
}
