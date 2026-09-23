// cl: /O1 /MD /DNDEBUG
//
// GameMessage scalar-argument appends (retail 0x0030F936 tag 0 and
// 0x0030FA2A tag 10): donor order from
// reference/open-bfme-1/Code/GameEngine/Source/Common/System/message_stream.h
// puts appendIntegerArgument first (Int, tag 0) and appendWideCharArgument
// last (const WideChar &, tag 10, word-sized data). Both feed allocArg
// (rowed at 0x30F8FF) and stamp the tag at +0x18 over the data at +0x08.
// Shard (not a graft into MessageStream.cpp or the twin's struct-args TU)
// so no landed TU recolors.

class GameMessageArgument
{
public:
	unsigned char m_pad[8];
	union
	{
		int m_integer;
		unsigned short m_wideChar;
		unsigned char m_largest[16];
	} m_data;
	int m_type; // +0x18
};

class GameMessage
{
	GameMessageArgument *allocArg();

public:
	void appendIntegerArgument(int arg);
	void appendWideCharArgument(const unsigned short &arg);
};

// ?appendIntegerArgument@GameMessage@@QAEXH@Z @0x0030F936
void GameMessage::appendIntegerArgument(int arg)
{
	GameMessageArgument *a = allocArg();
	a->m_type = 0;
	a->m_data.m_integer = arg;
}

// ?appendWideCharArgument@GameMessage@@QAEXABG@Z @0x0030FA2A
void GameMessage::appendWideCharArgument(const unsigned short &arg)
{
	GameMessageArgument *a = allocArg();
	a->m_data.m_wideChar = arg;
	a->m_type = 10;
}
