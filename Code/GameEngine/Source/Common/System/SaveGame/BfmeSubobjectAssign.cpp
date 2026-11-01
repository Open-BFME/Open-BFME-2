// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002DBC1F@BfmeSubobject00229875@@QAEAAU1@ABU1@@Z, retail 0x002DBC1F, 120 bytes.
// Copy-assign of BfmeSubobject00229875: eight 0x1AC elements at +4 via rowed
// 0x002DBAB9 assign, 0x10 bytes at +0xD64, ten dwords at +0xD74, byte +0xD9C
// and dword +0xDA0. Layout from SaveGameInfoCopyBFME2.cpp and Clear
// BfmeSubobject00229875Clear.cpp. Evidence: chain caller of just-landed
// 0x002DBAB9; unblocks 0x002DDC76.
#include "ascii_string.h"
#include "unicode_string.h"

struct Rva005B5C02Entry
{
	void Use(void *s);
	unsigned int _pad[0x50];
};

#include "../../../../Include/GameNetwork/GameInfo.h"

struct BfmeSubobject00229875
{
	virtual ~BfmeSubobject00229875();
	GameSlot elements[8];
	unsigned char blockD64[0x10];
	unsigned int blockD74[10];
	unsigned char flagD9C;
	unsigned int wordDA0;
	BfmeSubobject00229875 &rva002DBC1F(const BfmeSubobject00229875 &other);
};
typedef char BfmeSubobjectSizeCheck[sizeof(BfmeSubobject00229875) == 0xDA4 ? 1 : -1];

BfmeSubobject00229875 &BfmeSubobject00229875::rva002DBC1F(const BfmeSubobject00229875 &other)
{
	for (int i = 0; i < 8; ++i)
		elements[i].rva002DBAB9(other.elements[i]);
	for (int i = 0; i < 0x10; ++i)
		blockD64[i] = other.blockD64[i];
	for (int i = 0; i < 10; ++i)
		blockD74[i] = other.blockD74[i];
	flagD9C = other.flagD9C;
	wordDA0 = other.wordDA0;
	return *this;
}
