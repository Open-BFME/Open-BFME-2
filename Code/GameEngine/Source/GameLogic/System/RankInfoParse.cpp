// cl: /DNDEBUG /MD /GX- /Oi- /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?friend_parseRankDefinition@RankInfoStore@@SAXPAVINI@@@Z,
// retail 0x0020038E, 269 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/System/RankInfoParse.cpp,
// RankInfoStore::friend_parseRankDefinition, static): parse one Rank block.
// The retail body follows the reference source exactly: null-store guard,
// rank number through getNextToken plus the token-to-int member, override
// versus monotonic path on the load type, per-rank bounds checks, fresh
// RankInfo through operator new plus the constructor, final-override chase,
// copy, next-override link, override mark, field-table parse, and vector
// push-back on the new path. Throws funnel through the INIException filler
// plus CxxThrow. Member names come from the reference Overridable layout
// (m_nextOverride +0x04, m_isAllocatedOverride +0x08); the three string
// literals and the field-table address are retail-measured.

// Use the CRT placement operations inline without exporting this optimized
// copy over retail's separately compiled provider. No placement cleanup
// import is referenced: this unit disables C++ EH.
#define __PLACEMENT_NEW_INLINE
__declspec(dllimport) __forceinline void *operator new(unsigned int, void *where) throw() { return where; }
__declspec(dllimport) __forceinline void operator delete(void *, void *) throw() {}

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

typedef int Int;

#define NULL 0

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/Overridable.h"

// Retail inlines markAsOverride here (the outline is 0x00248D08).
__forceinline void Overridable::markAsOverride()
{
	m_isOverride = true;
}

class RankInfo : public Overridable
{
public:
	RankInfo();
	RankInfo &operator=(const RankInfo &that);

private:
	// +0x10..+0x43: retail-measured but unmapped (UnicodeString assigned at
	// +0x10, nine ints +0x14..+0x34, vector at +0x38 per the operator= body).
	// Only the total size (0x44) is consumed here.
	unsigned char m_pad[0x44 - 0x10];
};

class RankInfoStore
{
public:
	static void friend_parseRankDefinition(INI *ini);

private:
	unsigned char m_pad[0x0C];
	_STL::vector<RankInfo *> m_rankInfos; // +0x0C
};

extern RankInfoStore *TheRankInfoStore;

#include "../../../Include/Common/INI/FieldParse.h"

// The rank block's field table, read from retail: every token, parser and offset
// is retail's (it was a 1-byte zero placeholder, so a linked game parsed no Rank
// field).
// Retail VA 0x00BE2870: 11 fields and the zero sentinel.
extern const FieldParse g_00BE2870[] = {
	{ "RankName", &INI::parseAndTranslateLabel, 0, 0x10 },
	{ "SkillPointsNeededDefault", &INI::parseInt, 0, 0x14 },
	{ "SkillPointsNeededCampaign", &INI::parseInt, 0, 0x18 },
	{ "SkillPointsNeededMen", &INI::parseInt, 0, 0x1C },
	{ "SkillPointsNeededElves", &INI::parseInt, 0, 0x20 },
	{ "SkillPointsNeededDwarves", &INI::parseInt, 0, 0x24 },
	{ "SkillPointsNeededIsengard", &INI::parseInt, 0, 0x28 },
	{ "SkillPointsNeededMordor", &INI::parseInt, 0, 0x2C },
	{ "SkillPointsNeededWild", &INI::parseInt, 0, 0x30 },
	{ "SciencesGranted", &INI::parseScienceVector, 0, 0x38 },
	{ "SciencePurchasePointsGranted", &INI::parseUnsignedInt, 0, 0x34 },
	{ 0, 0, 0, 0 }
};

// ?friend_parseRankDefinition@RankInfoStore@@SAXPAVINI@@@Z
void RankInfoStore::friend_parseRankDefinition(INI *ini)
{
	if (TheRankInfoStore)
	{
		Int rank = ini->scanInt(ini->getNextToken(NULL));

		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		{
			// we aren't allowed to add ranks in overrides, only to override existing ones.
			// NOTE: unsigned comparison against size() (retail ja, not jg).
			if (rank < 1 || (unsigned int)rank > TheRankInfoStore->m_rankInfos.size())
			{
				throw INIException(3, "Rank not found in map.ini");
			}

			RankInfo *info = TheRankInfoStore->m_rankInfos[rank - 1];
			if (!info)
			{
				throw INIException(3, "Rank not found in map.ini");
			}

			RankInfo *newInfo = new RankInfo;

			// copy data from final override to 'newInfo' as a set of initial default values
			Overridable *nextOverride = info->friend_getNextOverride();
			if (nextOverride)
				info = (RankInfo *)nextOverride->friend_getFinalOverride();

			*newInfo = *info;
			info->setNextOverride(newInfo);
			newInfo->markAsOverride(); // must do AFTER the copy

			ini->initFromINI(newInfo, reinterpret_cast<const FieldParse *>((unsigned int)&g_00BE2870));
			//TheRankInfoStore->m_rankInfos.push_back(newInfo);	// NO, BAD, WRONG -- don't add in this case.
		}
		else
		{
			if (rank != (Int)TheRankInfoStore->m_rankInfos.size() + 1)
			{
				throw INIException(3, "Ranks must increase monotonically");
			}
			// NOTE: the push_back argument rides a copy, not `info` itself.
			// `info` stays register-held (push eax, xor-eax null path) while
			// the copy's home store sinks below the initFromINI argument
			// setup (push TABLE, push eax, mov ecx) to just before the call.
			// Passing `info` directly homes it up front in both new-arms
			// instead (verified by probe grid v1-v11: a defining store for
			// an address-taken variable pins early, a copy sinks late).
			RankInfo *info = new RankInfo;
			RankInfo *const storedInfo = info;
			ini->initFromINI(info, reinterpret_cast<const FieldParse *>((unsigned int)&g_00BE2870));
			TheRankInfoStore->m_rankInfos.push_back(storedInfo);		}
	}
}

// ?TheRankInfoStore@@3PAVRankInfoStore@@A: matched references place it at VA 0xdfe0ec.
RankInfoStore * TheRankInfoStore = 0;
