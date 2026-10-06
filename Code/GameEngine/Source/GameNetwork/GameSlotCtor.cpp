// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD
// GameSlot::GameSlot, native 0x003FFB4C..0x003FFBB4 (104B).
// Identity: the pin names it, and the body installs the GameSlot vftable
// 0x00BE7420, the same 0x1AC-byte layout whose copy constructor 0x002295D7
// and destructor 0x002294FD are matched in SaveGameInfoCopyBFME2.cpp.
// Zero Hour's GameSlot() only calls reset(); BFME2 additionally constructs
// its owning members: the strings at +0x30/+0x34/+0x1A8, the dword/word pair
// at +0x38/+0x3C, and the CreateAHeroData at +0x64. That member's constructor
// 0x00409C3D takes (0, 0, 0, UnicodeString::TheEmptyString, -1, 0xFF707070,
// -1), the same arguments CreateAHero's loader 0x0021F47E passes to a fresh
// 0x140-byte block, so they are its default arguments. reset() is the
// unrowed 0x003FF50C. Field names past the Zero Hour spellings are offsets.
#include "ascii_string.h"
#include "unicode_string.h"

class Xfer;

class Rva0022CE19SnapshotBase
{
public:
	inline virtual ~Rva0022CE19SnapshotBase() {}
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
};

class CreateAHeroData : public Rva0022CE19SnapshotBase
{
	unsigned char fields[0x13C];

public:
	CreateAHeroData(int a = 0, int b = 0, int c = 0,
		const UnicodeString &name = UnicodeString::TheEmptyString,
		int d = -1, int color = 0xFF707070, int e = -1);
	virtual ~CreateAHeroData();
	CreateAHeroData &operator=(const CreateAHeroData &that);
};

// The 8-byte connection record at +0x38: a dword address and a word port,
// zeroed by its constructor; the padding word is never written.
struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_ip(0), m_port(0) {}
	unsigned int m_ip;
	unsigned short m_port;
};

class GameSlot : public Rva0022CE19SnapshotBase
{
public:
	GameSlot();
	virtual void reset();

private:
	unsigned int word04;
	unsigned char flag08, flag09, flag0A;
	unsigned int word0C, word10, word14, word18, word1C, word20, word24, word28, word2C;
	UnicodeString text30;
	AsciiString text34;
	GameSlotConnectInfo connect38;
	unsigned int word40, word44;
	unsigned char flag48;
	unsigned int word4C, word50, word54, word58, word5C;
	unsigned char flag60;
	CreateAHeroData hero64;
	unsigned char flag1A4;
	AsciiString text1A8;
};

typedef char GameSlotSizeCheck[sizeof(GameSlot) == 0x1AC ? 1 : -1];

GameSlot::GameSlot()
{
	reset();
}

// GameSlot::reset, native 0x003FF50C (230B), vtable slot 4 (+0x10, the
// virtual call setState makes). Zero Hour's reset() order: state CLOSED,
// accepted false, hasMap true, muted false, color/startPos -1, template -2
// (BFME2: observer), team -1, then the orig* trio at -1 after one zeroed
// dword. BFME2 then clears both strings, the connection record, the
// +0x40..+0x60 block, reassigns a default CreateAHeroData through its
// assignment 0x00409359, sets the +0x1A4 occupancy byte and empties +0x1A8.
void GameSlot::reset()
{
	word04 = 1;
	flag08 = false;
	flag09 = true;
	flag0A = false;
	word0C = -1;
	word10 = -1;
	word14 = -1;
	word18 = -2;
	word1C = -1;
	word20 = 0;
	word24 = -1;
	word28 = -1;
	word2C = -1;
	text30.clear();
	text34.clear();
	connect38 = GameSlotConnectInfo();
	word40 = 1;
	word44 = 0;
	flag48 = false;
	word4C = -1;
	word50 = 0;
	word54 = 0;
	word58 = 0;
	word5C = -1;
	flag60 = false;
	CreateAHeroData defaultHero;
	hero64 = defaultHero;
	flag1A4 = true;
	text1A8 = AsciiString::TheEmptyString;
}
