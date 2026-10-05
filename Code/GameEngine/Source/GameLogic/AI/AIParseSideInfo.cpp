// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// ?parseSideInfo@AI@@SAXPAVINI@@PAX1PBX@Z, retail 0x002FE940 (188B). Zero
// Hour's AI::parseSideInfo (AI.cpp): the AI data's side-info list (+0xF4,
// linked through +0x1BC) is searched for the side named by the next token; a
// missing side gets a new 0x1C0-byte record (rowed ctor 0x002FE620, unwound on
// a throwing ctor) pushed at the head; the record then takes the side name
// (+0x04) and is filled through initFromINI with the side-info table at
// VA 0x00C07300. Target evidence: the AI table at 0x00C06650 maps SideInfo
// (0x00C06820) here. The side-info record keeps its address-derived class
// name (Zero Hour's AISideInfo).

#include "ascii_string.h"

#define NULL 0

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern const FieldParse g_00C07300[];

class Rva002FE620
{
public:
	Rva002FE620();
	unsigned char m_unreconstructed_000[4];
	AsciiString m_side;				// +0x004
	unsigned char m_unreconstructed_008[0x1BC - 0x008];
	Rva002FE620 *m_next;				// +0x1BC
};

struct TAiData
{
	unsigned char m_unreconstructed_000[0xF4];
	Rva002FE620 *m_sideInfo;			// +0x0F4

	void addSideInfo(Rva002FE620 *info)
	{
		info->m_next = m_sideInfo;
		m_sideInfo = info;
	}
};

class AI
{
public:
	static void parseSideInfo(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseSideInfo@AI@@SAXPAVINI@@PAX1PBX@Z
void AI::parseSideInfo(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	const char *c = ini->getNextToken();
	AsciiString side(c);

	Rva002FE620 *resourceInfo = ((TAiData *)instance)->m_sideInfo;
	while (resourceInfo)
	{
		if (side == resourceInfo->m_side)
			break;
		resourceInfo = resourceInfo->m_next;
	}
	if (resourceInfo == NULL)
	{
		resourceInfo = new Rva002FE620;
		((TAiData *)instance)->addSideInfo(resourceInfo);
	}
	resourceInfo->m_side = side;
	ini->initFromINI(resourceInfo, g_00C07300);
}
