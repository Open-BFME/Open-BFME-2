// cl: /MD
// ?rva00432A3B@Rva00432A3B@@QAEXPBVGameMessage@@@Z, retail 0x00432A3B, 103 bytes.
// Handler for message types 4/6/14/16: indexes 24B entries at this+8 by type,
// stores type at +0x1E8, extracts pixel (arg0 8B) ints (arg1 arg2) via rowed
// getArgument 0x0030F4EA, clears bit0 at +0x14. Matches emit Rva004328D8Emit
// (pixel+int+time). Precedent Rva005FA91C (/O1 /MD, slot 0x48 create).
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

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;
};

struct Rva00432A3BEntry
{
	int m_type;
	int m_pixX;
	int m_pixY;
	int m_int1;
	int m_int2;
	unsigned char m_flags14;
	char m_pad15[3];
};

class Rva00432A3B
{
public:
	void rva00432A3B(const GameMessage *msg);

private:
	char m_pad0[8];
	Rva00432A3BEntry m_entries[17];
	char m_pad1A0[0x1E8 - 0x1A0];
	int m_1E8;
};

void Rva00432A3B::rva00432A3B(const GameMessage *msg)
{
	int type = *(const int *)((const char *)msg + 0x10);
	switch (type)
	{
	case 4:
	case 6:
	case 14:
	case 16:
		break;
	default:
		return;
	}
	Rva00432A3BEntry *e = &m_entries[type];
	m_1E8 = type;
	e->m_type = type;
	const GameMessageArgumentType *a0 = msg->getArgument(0);
	e->m_pixX = a0->pixel.x;
	e->m_pixY = a0->pixel.y;
	const GameMessageArgumentType *a1 = msg->getArgument(1);
	e->m_int1 = a1->integer;
	const GameMessageArgumentType *a2 = msg->getArgument(2);
	e->m_int2 = a2->integer;
	e->m_flags14 &= ~1;
}
