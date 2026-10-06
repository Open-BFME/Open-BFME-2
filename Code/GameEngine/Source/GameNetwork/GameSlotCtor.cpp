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
};

class GameSlot : public Rva0022CE19SnapshotBase
{
public:
	GameSlot();
	void reset();

private:
	unsigned int word04;
	unsigned char flag08, flag09, flag0A;
	unsigned int word0C, word10, word14, word18, word1C, word20, word24, word28, word2C;
	UnicodeString text30;
	AsciiString text34;
	unsigned int word38;
	unsigned short short3C;
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
	: word38(0), short3C(0)
{
	reset();
}
