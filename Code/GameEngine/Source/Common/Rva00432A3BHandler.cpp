// cl: /MD
// ?rva00432A3B@AptTranslator@@QAEXPBVGameMessage@@@Z, retail 0x00432A3B, 103 bytes.
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

#include "../../Include/Common/MessageStream.h"

class Rva0043283CBase
{
public:
	Rva0043283CBase() { }
	~Rva0043283CBase() { }
	// The base table 0x00BDBA74 (the folded 8-byte translator base) starts
	// with __purecall 0x0003B810 (rowed in debug_purecall.cpp) and ends with a
	// deleting destructor; slot 0 is abstract, so declare it pure. The
	// placeholder body was never retail's and left the two vftables
	// referencing the undefined ?rva0043283CSlot0@Rva0043283CBase@@UAEXXZ.
	virtual void rva0043283CSlot0() = 0;
};

struct Rva0043283CEntry
{
	Rva0043283CEntry()
	{
		m_00 = 0;
		m_0C = 0;
		m_10 = 0;
		m_flag14 = 0;
	}
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_flag14 : 1;
};

class AptTranslator : public Rva0043283CBase
{
public:
	AptTranslator();
public:
	~AptTranslator();
private:
	int m_04;
private:
	Rva0043283CEntry m_entries08[0x14];
private:
	int m_1e8;
private:
	bool m_1ec;
private:
	int m_1f0;
private:
	int m_1f4;
private:
	int m_1f8;
private:
	int m_1fc;
private:
	int m_200;
public:
	int rva0043287E();
public:
	void rva00432A3B(const GameMessage *msg);
};

void AptTranslator::rva00432A3B(const GameMessage *msg)
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
	Rva0043283CEntry *e = &m_entries08[type];
	m_1e8 = type;
	e->m_00 = type;
	const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
	e->m_04 = gameMessageArgumentType->pixel.x;
	e->m_08 = gameMessageArgumentType->pixel.y;
	const GameMessageArgumentType *a1 = msg->getArgument(1);
	e->m_0C = a1->integer;
	const GameMessageArgumentType *a2 = msg->getArgument(2);
	e->m_10 = a2->integer;
	e->m_flag14 = 0;
}
