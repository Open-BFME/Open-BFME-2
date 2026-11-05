// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
// platformsdk
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

#include <windows.h>
#include "ascii_string.h"

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/INI/FieldParse.h"
#include "../../../Include/GameLogic/AI.h"

// Retail's own nine-record side-info table, transcribed from .rdata at RVA
// 0x00807300 (VA 0x00C07300, file offset 0x00806700): the three gatherer
// counts with INI::parseInt at +4/+0xC/+0x10, BaseDefenseStructure1 with
// INI::parseAsciiString at +0x1B8, and the five skill sets with
// AI::parseSkillSet at +0x14, +0x68, +0xBC, +0x110 and +0x164, then the zero
// terminator. Every parse target is a rowed body, and the preceding extern keeps
// the table external.
extern const FieldParse g_00C07300[];
const FieldParse g_00C07300[] =
{
	{ "ResourceGatherersEasy", &INI::parseInt, 0, 8 },
	{ "ResourceGatherersNormal", &INI::parseInt, 0, 12 },
	{ "ResourceGatherersHard", &INI::parseInt, 0, 16 },
	{ "BaseDefenseStructure1", &INI::parseAsciiString, 0, 440 },
	{ "SkillSet1", &AI::parseSkillSet, 0, 20 },
	{ "SkillSet2", &AI::parseSkillSet, 0, 104 },
	{ "SkillSet3", &AI::parseSkillSet, 0, 188 },
	{ "SkillSet4", &AI::parseSkillSet, 0, 272 },
	{ "SkillSet5", &AI::parseSkillSet, 0, 356 },
	{ 0, 0, 0, 0 }
};

class Rva002FE620
{
public:
	Rva002FE620();
	unsigned char m_unreconstructed_000[4];
	AsciiString m_side;				// +0x004
	unsigned char m_unreconstructed_008[0x1BC - 0x008];
	Rva002FE620 *m_next;				// +0x1BC
};

#include "../../../Include/GameLogic/TAiData.h"

inline void TAiData::addSideInfo(Rva002FE620 *info)
{
	info->m_next = m_sideInfo;
	m_sideInfo = info;
}

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
