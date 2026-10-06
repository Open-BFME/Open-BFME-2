// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00383784@Rva00386374@@UAEXVGameSpyStagingRoom@@@Z 0x00383784 79B
// Evidence: vslot 44 offset 0xB0 of vtable 0x00C19500 class Rva00386374; forwards by-value StagingRoom to slot 0xAC; copy 0x3835F4 builds outgoing arg then slot 0xAC then dtor 0x382C4A of incoming; ret 0x1020.
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

class Rva00386374
{
public:
	virtual ~Rva00386374();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void slot43(GameSpyStagingRoom room);
	virtual void rva00383784(GameSpyStagingRoom room);
};

void Rva00386374::rva00383784(GameSpyStagingRoom room)
{
	slot43(room);
}
