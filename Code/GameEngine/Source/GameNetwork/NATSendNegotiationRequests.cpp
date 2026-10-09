// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A7A96@NAT@@QAEXPBV?$vector@URva005A7A96Pair@@V?$allocator@URva005A7A96Pair@@@_STL@@@_STL@@@Z
// @0x005A7A96 518B: NAT port-negotiation request sender (one caller,
// 0x005A90D6).  For every slot pair in the list whose two slots exist and
// both have their +0x8E4 byte gate set, take the next negotiation cookie
// (0x005A671D), format "NEGO%d %d %X" from the pair and cookie, address a
// "NAT/" player UTM to both slot names joined by ',', record the start in
// the PortNegotiationSchema member at +0x28 (0x005DBF8C) and queue the
// request (g_00A02340 slot 6).  An empty translated name abandons the walk.
// Request, queue and NAT layout follow the sibling Rva005A8666BoxNat.cpp
// (NAT::rva005A7974, the "PORT" request); WorldBuilder twin 0x014E30C0 is
// unnamed (string lead) and agrees on the flow.
#include "ascii_string.h"
#include "unicode_string.h"
#include <string>
#include <vector>

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

int Rva005A671DNext();	// 0x005A671D next negotiation cookie

class PortNegotiationSchema
{
public:
	void negotiationStarted(unsigned short a, unsigned short b, int cookie, bool started);	// 0x005DBF8C
};

struct Rva005A7A96Slot
{
	char pad[0x30];
	UnicodeString m_name;	// +0x30
};

struct Rva005A7A96Pair
{
	int m_0;
	unsigned short m_a;	// +0x04 slot index
	unsigned short m_b;	// +0x06 slot index
};

struct NAT
{
	int m_0;
	void *m_04;
	Rva005A7A96Slot **m_8;	// slot list
	char pad0C[0x28 - 0x0C];
	PortNegotiationSchema m_schema;	// +0x28
	char pad29[0x8E4 - 0x29];
	unsigned char m_8E4[8];	// per-slot gate

	void rva005A7A96(const std::vector<Rva005A7A96Pair> *pairs);
};

void NAT::rva005A7A96(const std::vector<Rva005A7A96Pair> *pairs)
{
	PeerRequest req;
	AsciiString options;
	if (pairs->size() == 0)
		return;
	for (std::vector<Rva005A7A96Pair>::const_iterator it = pairs->begin(); it != pairs->end(); ++it)
	{
		if (m_8[it->m_a] == 0 || m_8[it->m_b] == 0 || !m_8E4[it->m_a] || !m_8E4[it->m_b])
			continue;
		AsciiString name;
		int cookie = Rva005A671DNext();
		options.format("NEGO%d %d %X", it->m_a, it->m_b, cookie);
		req.unknown_00 = 0xd;
		req.payload_flag0.value = true;
		req.unknown_34 = "NAT/";
		name.translate(m_8[it->m_a]->m_name);
		if (name.getLength() == 0)
			return;
		req.unknown_04 = name.str();
		name.translate(m_8[it->m_b]->m_name);
		if (name.getLength() == 0)
			return;
		req.unknown_04.append(",");
		req.unknown_04.append(name.str());
		req.unknown_40 = options.str();
		m_schema.negotiationStarted(it->m_a, it->m_b, cookie, true);
		g_00A02340->f6(&req);
	}
}
