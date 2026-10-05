// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi-
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

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed without a frame pointer, then restore this unit's flags.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
#pragma optimize("y", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	void initFromINI(void *what, const FieldParse *table);
	INILoadType getLoadType() const { return m_loadType; }

private:
	unsigned char m_pad[8];
	INILoadType m_loadType; // +0x08
};

class Overridable
{
public:
	virtual void overridableAnchor();
	Overridable *friend_getFinalOverride();

public:
	Overridable *m_nextOverride; // +0x04
	unsigned char m_isAllocatedOverride; // +0x08
};

class RankInfo : public Overridable
{
public:
	RankInfo();
	RankInfo &operator=(const RankInfo &that);
	void setNextOverride(RankInfo *o) { m_nextOverride = o; }
	void markAsOverride() { m_isAllocatedOverride = true; }

private:
	// +0x0C..+0x43: retail-measured but unmapped (int -1 at +0x0C in the ctor;
	// UnicodeString assigned at +0x10, nine ints +0x14..+0x34, vector at +0x38
	// per the operator= body). Only the total size (0x44) is consumed here.
	unsigned char m_pad[0x44 - 0x0C];
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

class INIException
{
public:
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
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
			Overridable *nextOverride = info->m_nextOverride;
			if (nextOverride)
				info = (RankInfo *)nextOverride->friend_getFinalOverride();

			*newInfo = *info;
			info->setNextOverride(newInfo);
			newInfo->markAsOverride(); // must do AFTER the copy

			ini->initFromINI(newInfo, reinterpret_cast<const FieldParse *>(0x00BE2870));
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
			ini->initFromINI(info, reinterpret_cast<const FieldParse *>(0x00BE2870));
			TheRankInfoStore->m_rankInfos.push_back(storedInfo);		}
	}
}

// ?TheRankInfoStore@@3PAVRankInfoStore@@A: matched references place it at VA 0xdfe0ec; also referenced as ?Va00DFE0ECStore@@3PAVRva002000D7Store@@A.
RankInfoStore * TheRankInfoStore = 0;
#pragma comment(linker, "/alternatename:?Va00DFE0ECStore@@3PAVRva002000D7Store@@A=?TheRankInfoStore@@3PAVRankInfoStore@@A")
