// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// ??0GameSpyStagingRoom@@QAE@ABV0@@Z @0x003835F4 345B: GameSpyStagingRoom's
// memberwise copy constructor (callers 0x003837A9 0x00385815 0x005AF87D
// 0x005AF892 0x005AF8E1). Rowed base copy Rva00382FA7 (0x00382FA7), then the
// vtable 0x00C19440 (the GameSpyStagingRoom vtable: slot 0 is the rowed
// ??_GGameSpyStagingRoom 0x00383768, slots 12..14 are the rowed ZH
// amIHost/getLocalSlotNum/resetAccepted), the 8x0x1E0 slot array through the
// EH vector copy helper with the rowed Rva00382398 copy/dtor, then the four
// AsciiStrings and plain fields up to +0x101C. Layout follows
// GameSpyStagingRoomDtor.cpp; field meanings are not recovered.

#include "ascii_string.h"

struct Rva00382FA7
{
	Rva00382FA7(const Rva00382FA7 &other);
	virtual ~Rva00382FA7();
	char m_pad[0xDC - 4];
};

class Rva00382398
{
public:
	Rva00382398(const Rva00382398 &other);
	virtual ~Rva00382398();

private:
	char m_pad[0x1E0 - 4];
};

class GameSpyStagingRoom : public Rva00382FA7
{
public:
	virtual ~GameSpyStagingRoom();

private:
	Rva00382398 m_items[8];
	AsciiString m_fdc;
	int m_fe0;
	int m_fe4;
	AsciiString m_fe8;
	char m_fec;
	char m_fed;
	int m_ff0;
	char m_ff4;
	int m_ff8;
	AsciiString m_ffc;
	AsciiString m_1000;
	int m_1004;
	short m_1008;
	int m_100c;
	int m_1010;
	int m_1014;
	int m_1018;
	int m_101c;
};

// The copy constructor is the implicitly defined one (an array member is
// copied through the EH vector copy helper); this placement copy is the use
// that makes the compiler emit it out of line.
inline void *operator new(unsigned int, void *where) { return where; }

// ?Rva003835F4Use@@YAXPAXABVGameSpyStagingRoom@@@Z present-unmatched (emission use only)
void Rva003835F4Use(void *where, const GameSpyStagingRoom &other)
{
	new (where) GameSpyStagingRoom(other);
}
