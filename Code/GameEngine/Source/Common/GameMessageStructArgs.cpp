// cl: /MD /DNDEBUG
//
// GameMessage struct-argument appends (retail 0x0030F9BB..0x0030FA13): the
// rowed MessageStream TU carries these two functions but compiles them to
// unrolled dword moves (40B/46B) under its /G7 flags, while retail uses the
// size-favoring rep-movsd lowering (29B/30B, /O1-proven) — so they live in
// this shard TU instead of touching the landed TU's flags. Identity is the
// donor order plus struct sizes plus type tags: appendLocationArgument
// takes Coord3D (12B, 3x movsd, tag 6) and sits where the donor puts it
// between TeamID and Pixel, and appendPixelRegionArgument takes IRegion2D
// (16B, 4x movsd, tag 8) between Pixel and Timestamp. Both feed allocArg
// (rowed at 0x30F8FF) and stamp the tag at +0x18 over the data at +0x08.

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"

class GameMessageArgument
{
public:
	unsigned char m_pad[8];
	union
	{
		Coord3D m_location;
		IRegion2D m_pixelRegion;
	} m_data;
	int m_type; // +0x18
};

#include "../../Include/Common/MessageStream.h"

// ?appendLocationArgument@GameMessage@@QAEXABUCoord3D@@@Z @0x0030F9BB
void GameMessage::appendLocationArgument(const Coord3D &arg)
{
	GameMessageArgument *gameMessageArgument = allocArg();
	gameMessageArgument->m_data.m_location = arg;
	gameMessageArgument->m_type = 6;
}

// ?appendPixelRegionArgument@GameMessage@@QAEXABUIRegion2D@@@Z @0x0030F9F6
void GameMessage::appendPixelRegionArgument(const IRegion2D &region2D)
{
	GameMessageArgument *gameMessageArgument = allocArg();
	gameMessageArgument->m_data.m_pixelRegion = region2D;
	gameMessageArgument->m_type = 8;
}
