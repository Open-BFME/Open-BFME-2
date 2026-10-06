// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002DBAB9@GameSlot@@QAEAAV1@ABV1@@Z, retail 0x002DBAB9, 225 bytes.
// Copy-assign of the 0x1AC-byte save element: scalars/flags field-by-field,
// UnicodeString at +0x30 and AsciiStrings at +0x34/+0x1A8 via shared
// AsciiString/UnicodeString operator= (inline set 0x37150/0x366F0), 0x140-byte
// member at +0x64 via pinned 0x00409359 (CreateAHeroData assign stashed 0.97,
// pinned as ?Use@Rva005B5C02Entry@@QAEXPAX@Z; declared as pinned spelling),
// byte at +0x1A4, return *this. No self-check in retail. Evidence: layout from
// SaveGameInfoCopyBFME2.cpp (8x0x1AC at +4); base of Rva00382398 (caller
// 0x003824A5) and GameInfo prefix (caller 0x00447B58); callees all rowed/pinned.
#include "ascii_string.h"
#include "unicode_string.h"

struct Rva005B5C02Entry
{
	void Use(void *s);
	unsigned int _pad[0x50];
};
typedef char RvaEntrySizeCheck[sizeof(Rva005B5C02Entry) == 0x140 ? 1 : -1];

class GameSlot {
public:
	virtual ~GameSlot();
	unsigned int word04;
	unsigned char flag08;
	unsigned char flag09;
	unsigned char flag0A;
	unsigned int word0C;
	unsigned int word10;
	unsigned int word14;
	unsigned int word18;
	unsigned int word1C;
	unsigned int word20;
	unsigned int word24;
	unsigned int word28;
	unsigned int word2C;
	UnicodeString text30;
	AsciiString text34;
	unsigned int word38;
	unsigned int word3C;
	unsigned int word40;
	unsigned int word44;
	unsigned char flag48;
	unsigned int word4C;
	unsigned int word50;
	unsigned int word54;
	unsigned int word58;
	unsigned int word5C;
	unsigned char flag60;
	Rva005B5C02Entry hero64;
	unsigned char flag1A4;
	AsciiString text1A8;
	GameSlot &rva002DBAB9(const GameSlot &o);
};
typedef char BfmeSaveElementSizeCheck[sizeof(GameSlot) == 0x1AC ? 1 : -1];

GameSlot &GameSlot::rva002DBAB9(const GameSlot &o)
{
	word04 = o.word04;
	flag08 = o.flag08;
	flag09 = o.flag09;
	flag0A = o.flag0A;
	word0C = o.word0C;
	word10 = o.word10;
	word14 = o.word14;
	word18 = o.word18;
	word1C = o.word1C;
	word20 = o.word20;
	word24 = o.word24;
	word28 = o.word28;
	word2C = o.word2C;
	text30 = o.text30;
	text34 = o.text34;
	word38 = o.word38;
	word3C = o.word3C;
	word40 = o.word40;
	word44 = o.word44;
	flag48 = o.flag48;
	word4C = o.word4C;
	word50 = o.word50;
	word54 = o.word54;
	word58 = o.word58;
	word5C = o.word5C;
	flag60 = o.flag60;
	hero64.Use((void *)&o.hero64);
	flag1A4 = o.flag1A4;
	text1A8 = o.text1A8;
	return *this;
}
