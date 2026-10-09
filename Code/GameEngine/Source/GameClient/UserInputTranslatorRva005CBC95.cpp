// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva005CBC95@Rva005CBC95Call@@QAEHPAX@Z
// retail 0x005CBC95..0x005CC1A0 (1291 bytes) thiscall RET 4; jump table
// 0x005CC1A0 (26 cases) follows the body.
//
// The base input translator's message dispatch. WorldBuilder twin
// 0x015AEA20 UserInputTranslator::translateGameMessage
// (UserInputTranslator.cpp; wb-name-unverified) has the same switch and
// argument shapes. The spelling is the existing pin used by the rowed caller
// 0x00574910; the same address also carries the pin
// ?translateGameMessage@UserInputTranslator@@... used by the rowed overrides
// 0x005771F4 0x00575C15 0x0057667D (vtable slot 0 of the translator).
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

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

union GameMessageArgumentType
{
	int integer;
	ICoord2D pixel;
	IRegion2D pixelRegion;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int index) const;
	int getType() const { return m_type; }

private:
	char m_pad00[0x10];
	int m_type; // +0x10
};

// The handlers' pixel parameter: a copy of the message's pixel argument.
struct Rva005CBC95Pixel
{
	int x;
	int y;
	Rva005CBC95Pixel(const ICoord2D &p) : x(p.x), y(p.y) {}
};

class Rva005CBC95Call
{
public:
	virtual int slot00(void *msg);
	virtual void slot04();
	virtual int slot08(const Rva005CBC95Pixel &pos, int a);
	virtual int slot0C(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot10(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot14(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot18(const Rva005CBC95Pixel &pos, const Rva005CBC95Pixel &anchor, int a);
	virtual int slot1C(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot20(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot24(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot28(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot2C(const Rva005CBC95Pixel &pos, const Rva005CBC95Pixel &anchor, int a);
	virtual int slot30(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot34(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot38(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot3C(const Rva005CBC95Pixel &pos, const Rva005CBC95Pixel &anchor, int a);
	virtual int slot40(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot44(const Rva005CBC95Pixel &pos, int a, int b);
	virtual int slot48(const IRegion2D &region, int a);
	virtual int slot4C(const IRegion2D &region, int a);
	virtual int slot50(const IRegion2D &region, int a);
	virtual int slot54(const IRegion2D &region, int a);
	virtual int slot58(const IRegion2D &region, int a);
	virtual int slot5C(const IRegion2D &region, int a);
	virtual int slot60(int a, int b);
	virtual int slot64(int a, int b);
	int rva005CBC95(void *msg);
};

int Rva005CBC95Call::rva005CBC95(void *message)
{
	const GameMessage *msg = (const GameMessage *)message;
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
	return 0;
}
