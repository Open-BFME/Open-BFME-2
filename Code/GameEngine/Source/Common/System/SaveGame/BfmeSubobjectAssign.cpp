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

struct BfmeSaveElement002295D7
{
	virtual ~BfmeSaveElement002295D7();
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
	BfmeSaveElement002295D7 &rva002DBAB9(const BfmeSaveElement002295D7 &o);
};

struct BfmeSubobject00229875
{
	virtual ~BfmeSubobject00229875();
	BfmeSaveElement002295D7 elements[8];
	unsigned char blockD64[0x10];
	unsigned int blockD74[10];
	unsigned char flagD9C;
	unsigned int wordDA0;
	BfmeSubobject00229875 &rva002DBC1F(const BfmeSubobject00229875 &o);
};
typedef char BfmeSubobjectSizeCheck[sizeof(BfmeSubobject00229875) == 0xDA4 ? 1 : -1];

BfmeSubobject00229875 &BfmeSubobject00229875::rva002DBC1F(const BfmeSubobject00229875 &o)
{
	for (int i = 0; i < 8; ++i)
		elements[i].rva002DBAB9(o.elements[i]);
	for (int i = 0; i < 0x10; ++i)
		blockD64[i] = o.blockD64[i];
	for (int i = 0; i < 10; ++i)
		blockD74[i] = o.blockD74[i];
	flagD9C = o.flagD9C;
	wordDA0 = o.wordDA0;
	return *this;
}
