// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?setSlot@GameInfo@@QAEXHVGameSlot@@@Z, retail 0x003FFDFA, 87 bytes.
// GameInfo::setSlot: index at [ebp+8] with 0..8 range check via +0x18
// pointer array, null check, slot-0 flag tweak (word04==6 sets flag08/flag09)
// then rowed 0x002DBAB9 assign and rowed 0x002294FD dtor of by-value 0x1AC
// element (ret 0x1B0 = 4+0x1AC). Layout from BfmeSaveElementAssign.cpp and
// GameInfoClearSlotList.cpp (pad 0x18 plus 8 slots). Evidence: chain caller
// of 0x002DBAB9; unblocks 0x00448423 0x00382623 0x0040052C; prev 0x003FFDB7
// next 0x003FFEF5; callers include 0x002300D7 0x003826FB.
#include "ascii_string.h"
#include "unicode_string.h"

struct Rva005B5C02Entry {
	void Use(void *s);
	unsigned int _pad[0x50];
};

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

struct GameInfo {
	char _pad[0x18];
	GameSlot *m_slot[8];
	void setSlot(int index, GameSlot elem);
};

void GameInfo::setSlot(int index, GameSlot elem)
{
	if (index < 0 || index >= 8)
		return;
	GameSlot *slot = m_slot[index];
	if (!slot)
		return;
	if (index == 0) {
		elem.flag08 = 1;
		if (elem.word04 == 6)
			elem.flag09 = 1;
	}
	slot->rva002DBAB9(elem);
}
