// ?rva001EFD9C@Rva001EFD9C@@QAE_NVUnicodeString@@_NPBUSelPair@@@Z
// partial score=0.65 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG
// stlport
//
// ?rva001EFD9C@Rva001EFD9C@@... @0x001EFD9C 554B.
// Private-message sendChat worker on GameSpyInfo's vtable (slot 64 of the
// 0x00C19500 vtable, directly after rowed 0x001EF90E at slot 62, range-mate
// 0x001EF9A0 at slot 63 and the landed tag-0x15 sibling 0x001EFCF7 at slot
// 65). Identity evidence (target facts, all read from game.dat):
// - thiscall: entry uses ecx as this for virtual slot 12, which this same
//   vtable resolves to the joinGroupRoom TU's neighbourhood (slot 12 target
//   0x0008BB81); slots 22/23/29 resolve to the rowed GameSpyInfo methods
//   rva00382CCE (0x00382CCE, find player by name), rva00382D0A (0x00382D0A,
//   find player by profileID) and getLocalName (0x003861BC).
// - ZH Chat.cpp sendChat donor: trim, empty-message false return, PeerRequest
//   through TheGameSpyPeerMessageQueue slot 6, "%s" then ",%s" formats with
//   StringBase concat, tag 2 (PEERREQUEST_MESSAGEPLAYER) for the private path
//   and tag 3 (PEERREQUEST_MESSAGEROOM) for the room path, isAction byte from
//   [ebp+0xC] into the record, nick assignment, true return. Enum values 2/3
//   agree with the nat PeerThread.h donor.
// - BFME2 divergence from the ZH donor (retail facts, kept honest): the third
//   parameter is NOT a GameWindow listbox. Retail reads [param] and [param+4]
//   as a begin/end int-pointer pair (elements feed the Int-taking slot 23),
//   so it is declared here as an unproven-layout selection range; the strict
//   pointee type is not established. Likewise the loop looks players up by
//   profileID and seeds the name from the slot-22 hit instead of ZH's
//   translate/compareNoCase skip.
// Shares the BfmeOpaqueOwnedRecord492 struct, queue view and NullChr global
// spelling with the landed sibling PeerTextRequestValidate.cpp; the union
// gains an honest action-byte member at +8 (record +0x118) for the isAction
// store, which no previous TU addressed.
#include <string>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
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
		struct { int pad0; int pad1; bool action; } msgAction;
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
	virtual void addRequest(BfmeOpaqueOwnedRecord492 *rec);
};

extern PeerRequestQueue6 *TheGameSpyPeerMessageQueue;

// The wide NullChr retail falls back to: established name g_Va007BB5C4
// (defined in Rva00579900Fetch.cpp, placed at VA 0x00BBB5C4).
extern unsigned short g_Va007BB5C4;

// Begin/end int-pointer pair retail threads through the third slot.
// Strict pointee type unproven; elements are consumed as Int profileIDs.
struct SelPair
{
	int *begin;
	int *end;
};

struct PlayerInfo
{
	AsciiString m_name;
};

class Rva001EFD9C
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual int getCurrentGroupRoom();
	virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
	virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
	virtual void d21();
	virtual PlayerInfo *rva00382CCE(const char *name);
	virtual PlayerInfo *rva00382D0A(int profileID);
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28();
	virtual AsciiString getLocalName();
	bool rva001EFD9C(UnicodeString message, bool isAction, const SelPair *sels);
};

extern Rva001EFD9C *TheGameSpyInfo;

bool Rva001EFD9C::rva001EFD9C(UnicodeString message, bool isAction, const SelPair *sels)
{
	bool ok = false;
	getCurrentGroupRoom();
	message.trim();
	const void *bits = *reinterpret_cast<const void * const *>(&message);
	if (bits != 0
		&& *reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(bits) + 4) != 0)
	{
		BfmeOpaqueOwnedRecord492 rec;
		rec.unknown_10 = bits
			? (const unsigned short *)(reinterpret_cast<const char *>(bits) + 8)
			: (const unsigned short *)&g_Va007BB5C4;
		if (sels == 0
			|| (((reinterpret_cast<const char *>(sels->end) - reinterpret_cast<const char *>(sels->begin)) & ~3) == 0))
		{
			rec.unknown_00 = 3;
			rec.msgAction.action = isAction;
			TheGameSpyPeerMessageQueue->addRequest(&rec);
		}
		else
		{
			AsciiString names;
			PlayerInfo *found = TheGameSpyInfo->rva00382CCE(TheGameSpyInfo->getLocalName().str());
			if (found)
				names.format("%s", found->m_name.str());
			else
				names.format("%s", TheGameSpyInfo->getLocalName().str());
			for (int *p = sels->begin; p != sels->end; ++p)
			{
				PlayerInfo *info = TheGameSpyInfo->rva00382D0A(*p);
				if (info)
				{
					AsciiString tmp;
					tmp.format(",%s", info->m_name.str());
					names.concat(tmp);
				}
			}
			if (!names.isEmpty())
			{
				rec.unknown_04 = names.str();
				rec.unknown_00 = 2;
				rec.msgAction.action = isAction;
			TheGameSpyPeerMessageQueue->addRequest(&rec);
			}
			ok = true;
		}
	}
	return ok;
}
