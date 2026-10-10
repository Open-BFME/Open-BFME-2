// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva004160BE@Rva004160BEInfo@@QBE?AVAsciiString@@XZ, retail 0x004160BE
// (133 bytes).  Formats a buddy game record as "%d %d %d PW:%s #HOST:%s"
// from its +0x04, +0x08 and +0x14 words, its +0x10 password and +0x0C host
// strings; 0x0041647A sends the text to the record's +0x00 profile through
// TheGameSpyBuddyMessageQueue (request type 0x0B, the text in the 256-byte
// field the add-buddy request of RequestBuddyAddRva004178C1.cpp uses for its
// message): ?Rva0041647ASend@@YAXPBURva004160BEInfo@@@Z, retail 0x0041647A
// (138 bytes, cdecl).  The record type is not identified (no Zero
// Hour counterpart); field names follow the format string only.
#include <string.h>
#include "ascii_string.h"

class BuddyRequest
{
public:
	int buddyRequestType;	// +0x00
	int id;	// +0x04
	char text[0x100];	// +0x08
	char m_pad108[0x2B8 - 0x108];
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void addRequest(const BuddyRequest &req);	// +0x18
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

struct Rva004160BEInfo
{
	int m_profile;	// +0x00
	int m_04;	// +0x04
	int m_08;	// +0x08
	AsciiString m_host;	// +0x0C
	AsciiString m_password;	// +0x10
	int m_14;	// +0x14

	AsciiString rva004160BE() const;
};

AsciiString Rva004160BEInfo::rva004160BE() const
{
	AsciiString text;
	text.format("%d %d %d PW:%s #HOST:%s", m_04, m_08, m_14, m_password.str(), m_host.str());
	return text;
}

void Rva0041647ASend(const Rva004160BEInfo *info)
{
	BuddyRequest req;
	req.id = info->m_profile;
	req.buddyRequestType = 0x0B;
	AsciiString text = info->rva004160BE();
	strncpy(req.text, text.str(), 0x100);
	req.text[0xFF] = 0;
	TheGameSpyBuddyMessageQueue->addRequest(req);
}
