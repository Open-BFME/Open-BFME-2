// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva005C9BE3@Rva005C9BE3Call@@QAEHPAX@Z, retail 0x005C9BE3..0x005C9CC2 (223
// bytes, RET 4): the message dispatch the rowed 0x00574910 runs on its +0x28
// member. By the message's +0x10 type it hands the first argument's pixel
// pair (copied to a local) and the second argument (rowed
// GameMessage::getArgument) to the rowed handlers in Rva005C9AB4.cpp: type 3
// to 0x005C9ADD, types 0x17-0x18 / 0x19-0x1A / 0x1B-0x1C to 0x005C9B31 with
// 0 / 1 / 2. Any other type answers 0. Each case copies into its own
// function-scope local, as retail's four frame slots show.

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

union GameMessageArgumentType
{
	int integer;
	ICoord2D pixel;
};

#include "../../../Include/Common/MessageStream.h"

class Rva005C9B76
{
public:
	int rva005C9ADD(int v, int);
};

#include "../../../Include/GameLogic/Module/Obj005C9B0C.h"

#include "../../../Include/GameClient/Rva005C9BE3Call.h"

int Rva005C9BE3Call::rva005C9BE3(void *arg)
{
	const GameMessage *msg = (const GameMessage *)arg;
	ICoord2D press, drag0, drag1, drag2;
	switch (msg->getType())
	{
	case 3:
		press = msg->getArgument(0)->pixel;
		return reinterpret_cast<Rva005C9B76 *>(this)->rva005C9ADD((int)&press, msg->getArgument(1)->integer);
	case 0x17:
	case 0x18:
		drag0 = msg->getArgument(0)->pixel;
		return reinterpret_cast<Obj005C9B0C *>(this)->rva005C9B31((int)&drag0, msg->getArgument(1)->integer, 0);
	case 0x19:
	case 0x1A:
		drag1 = msg->getArgument(0)->pixel;
		return reinterpret_cast<Obj005C9B0C *>(this)->rva005C9B31((int)&drag1, msg->getArgument(1)->integer, 1);
	case 0x1B:
	case 0x1C:
		drag2 = msg->getArgument(0)->pixel;
		return reinterpret_cast<Obj005C9B0C *>(this)->rva005C9B31((int)&drag2, msg->getArgument(1)->integer, 2);
	}
	return 0;
}
