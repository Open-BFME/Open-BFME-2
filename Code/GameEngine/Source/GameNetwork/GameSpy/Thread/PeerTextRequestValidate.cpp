// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG
// stlport
// ?Rva001EFCF7@@YG_NVUnicodeString@@@Z @0x001EFCF7 165B
// Peer text-request validator: trims a by-value UnicodeString, and when it
// is non-empty files a PeerRequest (tag 0x15) carrying its text through
// TheGameSpyPeerMessageQueue->addRequest (slot 6), returning true. Evidence:
// - record lifetime is rowed 0x001EF661/0x001EF723 (PeerRequest,
//   the record PeerThread.cpp constructs there); the struct below is
//   copied identically from Rva0059FF9DDo.cpp, which files the sibling tag
//   0x19 request through the same slot-6 call on the same queue global.
// - wstring member +0x10 takes the +8-or-NullChr text (0x00BBB5C4 fallback)
//   through rowed 0x001EFCD7 (PeerThread.cpp's PBG assign); trim is rowed
//   0x00037F70; the emptiness test is the explicit m_data null + length
//   word pair (no isEmpty call in retail), read through the same pun idiom
//   as Mouse::compareCursorName since StringBase keeps m_data private.
// - the queue global uses its true name (defined once in PeerThread.cpp);
//   the TU-local slot view keeps addRequest at proven slot 6 per
//   PeerThreadRetail.h's interface order. DIR32 global refs are masked by
//   the gate, as in the sibling TUs.
#include <string>
#include <vector>

#include "unicode_string.h"

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

struct PeerRequestQueue6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void addRequest(PeerRequest *rec);
};

extern PeerRequestQueue6 *TheGameSpyPeerMessageQueue;


bool __stdcall Rva001EFCF7(UnicodeString str)
{
	PeerRequest rec;
	const void *bits = *reinterpret_cast<const void * const *>(&str);
	rec.unknown_10 = bits
		? (const unsigned short *)(reinterpret_cast<const char *>(bits) + 8)
		: (const unsigned short *)L"";
	str.trim();
	const void *check = *reinterpret_cast<const void * const *>(&str);
	bool ok;
	if (check == 0
		|| *reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(check) + 4) == 0)
		ok = false;
	else
	{
		rec.unknown_00 = 0x15;
		TheGameSpyPeerMessageQueue->addRequest(&rec);
		ok = true;
	}
	return ok;
}
