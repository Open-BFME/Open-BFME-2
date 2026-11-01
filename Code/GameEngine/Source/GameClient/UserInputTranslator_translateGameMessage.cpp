// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?translateGameMessage@UserInputTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// retail 0x005CBC95..0x005CC1A0 (1291 bytes) thiscall RET 4; jump table
// 0x005CC1A0 (26 cases) follows the body.
//
// The base input translator's message dispatch. WorldBuilder twin
// 0x015AEA20 UserInputTranslator::translateGameMessage
// (UserInputTranslator.cpp; wb-name-unverified) has the same switch and
// argument shapes. Slot 0 of the translator vtable: the rowed overrides
// 0x00574910 0x005771F4 0x00575C15 0x0057667D defer to it by this name.
// Target evidence: switches on the message type at msg+0x10 (types 3..28;
// 7 and 20 and the rest return 0) and calls this object's own vtable slots
// +0x08..+0x64 with arguments fetched by the rowed GameMessage::getArgument
// 0x0030F4EA: a copied pixel (8 bytes) plus one or two integers; two copied
// pixels plus an integer (slots +0x18 +0x2C +0x3C); the pixel region record
// by reference plus an integer (slots +0x48..+0x5C; +0x48 is the rowed
// CampaignInGameUI ResolveBattlesBehavior OnMouseLeftClick); or two integers
// (+0x60 +0x64). Each slot's result is returned. The pixel copies are
// argument temporaries made before the pushes (WorldBuilder copies the
// second pixel first too); their parameter type here is a view.

#include "../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../Libraries/Include/Lib/IRegion2D.h"

union GameMessageArgumentType
{
	int integer;
	ICoord2D pixel;
	IRegion2D pixelRegion;
};

#include "../../Include/Common/MessageStream.h"

// The handlers' pixel parameter: a copy of the message's pixel argument.
struct Rva005CBC95Pixel
{
	int x;
	int y;
	Rva005CBC95Pixel(const ICoord2D &p) : x(p.x), y(p.y) {}
};

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~UserInputTranslator();
	virtual GameMessageDisposition slot08(const Rva005CBC95Pixel &pos, int a);
	virtual GameMessageDisposition slot0C(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot10(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot14(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot18(const Rva005CBC95Pixel &pos, const Rva005CBC95Pixel &anchor, int a);
	virtual GameMessageDisposition slot1C(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot20(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot24(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot28(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot2C(const Rva005CBC95Pixel &pos, const Rva005CBC95Pixel &anchor, int a);
	virtual GameMessageDisposition slot30(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot34(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot38(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot3C(const Rva005CBC95Pixel &pos, const Rva005CBC95Pixel &anchor, int a);
	virtual GameMessageDisposition slot40(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot44(const Rva005CBC95Pixel &pos, int a, int b);
	virtual GameMessageDisposition slot48(const IRegion2D &region, int a);
	virtual GameMessageDisposition slot4C(const IRegion2D &region, int a);
	virtual GameMessageDisposition slot50(const IRegion2D &region, int a);
	virtual GameMessageDisposition slot54(const IRegion2D &region, int a);
	virtual GameMessageDisposition slot58(const IRegion2D &region, int a);
	virtual GameMessageDisposition slot5C(const IRegion2D &region, int a);
	virtual GameMessageDisposition slot60(int a, int b);
	virtual GameMessageDisposition slot64(int a, int b);
};

GameMessageDisposition UserInputTranslator::translateGameMessage(const GameMessage *msg)
{
	switch (msg->getType())
	{
	case 3:
		return slot08(msg->getArgument(0)->pixel, msg->getArgument(1)->integer);
	case 4:
		return slot0C(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 5:
		return slot10(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 6:
		return slot14(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 8:
		return slot18(msg->getArgument(0)->pixel, msg->getArgument(1)->pixel, msg->getArgument(2)->integer);
	case 9:
		return slot1C(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 10:
		return slot20(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 11:
		return slot24(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 12:
		return slot28(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 13:
		return slot2C(msg->getArgument(0)->pixel, msg->getArgument(1)->pixel, msg->getArgument(2)->integer);
	case 14:
		return slot30(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 15:
		return slot34(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 16:
		return slot38(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 18:
		return slot3C(msg->getArgument(0)->pixel, msg->getArgument(1)->pixel, msg->getArgument(2)->integer);
	case 17:
		return slot40(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 19:
		return slot44(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 23:
		return slot48(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 24:
		return slot4C(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 25:
		return slot50(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 26:
		return slot54(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 27:
		return slot58(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 28:
		return slot5C(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 21:
		return slot60(msg->getArgument(0)->integer, msg->getArgument(1)->integer);
	case 22:
		return slot64(msg->getArgument(0)->integer, msg->getArgument(1)->integer);
	}
	return KEEP_MESSAGE;
}
