// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A7974@NAT@@QAEXGPAX@Z @0x005A7974 290B: NAT PORT request builder.
// Target evidence: byte gates m_24=1 plus m_04/m_25 plus Consume 0x004D51ED pin,
// format "PORT%d %d %08X %X" 0x00871C50 plus "NAT/" plus translate 0x00038220,
// empty fallback g_Rva0107301CEmptyString, OwnedRecord ctor 0x001EF661/dtor
// 0x001EF723, queue global g_00A02340 slot 6; layout from Rva005A8666Box.cpp.
#include "ascii_string.h"
#include "unicode_string.h"
#include <string>
#include <vector>


__forceinline const char *GetStr005A7974(const AsciiString &s)
{
	char *t = *(char * *)(const void *)&s;
	return t ? t + 8 : "";
}

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union
	{
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
	};
};

struct Global003EF728V6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6(PeerRequest *rec);
};

extern Global003EF728V6 *g_00A02340;

struct Rva005A8666Sub04
{
	void Consume(int i, void *p);
};

struct Rva005A8666Obj
{
	char pad[0x40];
	unsigned char m_40;
};

struct Rva005A8666Ptr
{
	int m_0;
	short m_4;
};

struct NAT
{
	int m_0;
	Rva005A8666Sub04 *m_04;
	Rva005A8666Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	unsigned char m_25;
	char pad2[0x90c - 0x26];
	Rva005A8666Ptr *m_90C[8];
	void rva005A7974(unsigned short port, void *info);
};

void NAT::rva005A7974(unsigned short port, void *info)
{
	m_24 = 1;
	if (m_04 != 0 && m_25 != 0)
		m_04->Consume(m_18, m_90C[m_18]);
	PeerRequest req;
	AsciiString portStr;
	portStr.format("PORT%d %d %08X %X", m_14, port, m_1C, m_20);
	req.unknown_00 = 0xd;
	req.payload_flag0.value = true;
	req.unknown_34 = "NAT/";
	AsciiString uniStr;
	uniStr.translate(*(const UnicodeString *)((const char *)info + 0x30));
	req.unknown_04 = GetStr005A7974(uniStr);
	req.unknown_40 = GetStr005A7974(portStr);
	g_00A02340->f6(&req);
}
