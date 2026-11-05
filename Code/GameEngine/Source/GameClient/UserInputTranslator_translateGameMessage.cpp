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

#include "../../Include/GameClient/UserInputTranslator.h"

GameMessageDisposition UserInputTranslator::translateGameMessage(const GameMessage *msg)
{
	switch (msg->getType())
	{
	case 3:
		return (GameMessageDisposition)slot02(msg->getArgument(0)->pixel, msg->getArgument(1)->integer);
	case 4:
		return (GameMessageDisposition)slot03(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 5:
		return (GameMessageDisposition)slot04(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 6:
		return (GameMessageDisposition)slot05(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 8:
		return (GameMessageDisposition)slot06(msg->getArgument(0)->pixel, msg->getArgument(1)->pixel, msg->getArgument(2)->integer);
	case 9:
		return (GameMessageDisposition)slot07(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 10:
		return (GameMessageDisposition)slot08(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 11:
		return (GameMessageDisposition)slot09(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 12:
		return (GameMessageDisposition)slot10(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 13:
		return (GameMessageDisposition)slot11(msg->getArgument(0)->pixel, msg->getArgument(1)->pixel, msg->getArgument(2)->integer);
	case 14:
		return (GameMessageDisposition)slot12(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 15:
		return (GameMessageDisposition)slot13(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 16:
		return (GameMessageDisposition)slot14(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 18:
		return (GameMessageDisposition)slot15(msg->getArgument(0)->pixel, msg->getArgument(1)->pixel, msg->getArgument(2)->integer);
	case 17:
		return (GameMessageDisposition)slot16(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 19:
		return (GameMessageDisposition)slot17(msg->getArgument(0)->pixel, msg->getArgument(1)->integer, msg->getArgument(2)->integer);
	case 23:
		return (GameMessageDisposition)OnMouseLeftClick(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 24:
		return (GameMessageDisposition)slot19(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 25:
		return (GameMessageDisposition)slot20(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 26:
		return (GameMessageDisposition)slot21(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 27:
		return (GameMessageDisposition)slot22(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 28:
		return (GameMessageDisposition)slot23(msg->getArgument(0)->pixelRegion, msg->getArgument(1)->integer);
	case 21:
		return (GameMessageDisposition)slot24(msg->getArgument(0)->integer, msg->getArgument(1)->integer);
	case 22:
		return (GameMessageDisposition)slot25(msg->getArgument(0)->integer, msg->getArgument(1)->integer);
	}
	return KEEP_MESSAGE;
}
