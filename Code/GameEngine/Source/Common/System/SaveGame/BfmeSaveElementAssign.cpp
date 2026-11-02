// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002DBAB9@GameSlot@@QAEAAV1@ABV1@@Z, retail 0x002DBAB9, 225 bytes.
// Copy-assign of the 0x1AC-byte save element: scalars/flags field-by-field,
// UnicodeString at +0x30 and AsciiStrings at +0x34/+0x1A8 via shared
// AsciiString/UnicodeString operator= (inline set 0x37150/0x366F0), 0x140-byte
// member at +0x64 via the rowed CreateAHeroData assignment at 0x00409359,
// byte at +0x1A4, return *this. No self-check in retail. Evidence: layout from
// SaveGameInfoCopyBFME2.cpp (8x0x1AC at +4); base of Rva00382398 (caller
// 0x003824A5) and GameInfo prefix (caller 0x00447B58); callees all rowed/pinned.
#include "ascii_string.h"
#include "unicode_string.h"

struct Rva005B5C02Entry
{
	unsigned int _pad[0x50];
};
typedef char RvaEntrySizeCheck[sizeof(Rva005B5C02Entry) == 0x140 ? 1 : -1];

#include "../../../../Include/GameLogic/CreateAHeroData.h"

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

GameSlot &GameSlot::rva002DBAB9(const GameSlot &gameSlot)
{
	word04 = gameSlot.word04;
	flag08 = gameSlot.flag08;
	flag09 = gameSlot.flag09;
	flag0A = gameSlot.flag0A;
	word0C = gameSlot.word0C;
	word10 = gameSlot.word10;
	word14 = gameSlot.word14;
	word18 = gameSlot.word18;
	word1C = gameSlot.word1C;
	word20 = gameSlot.word20;
	word24 = gameSlot.word24;
	word28 = gameSlot.word28;
	word2C = gameSlot.word2C;
	text30 = gameSlot.text30;
	text34 = gameSlot.text34;
	word38 = gameSlot.word38;
	word3C = gameSlot.word3C;
	word40 = gameSlot.word40;
	word44 = gameSlot.word44;
	flag48 = gameSlot.flag48;
	word4C = gameSlot.word4C;
	word50 = gameSlot.word50;
	word54 = gameSlot.word54;
	word58 = gameSlot.word58;
	word5C = gameSlot.word5C;
	flag60 = gameSlot.flag60;
	*reinterpret_cast<CreateAHeroData *>(&hero64) = *reinterpret_cast<const CreateAHeroData *>(&gameSlot.hero64);
	flag1A4 = gameSlot.flag1A4;
	text1A8 = gameSlot.text1A8;
	return *this;
}
