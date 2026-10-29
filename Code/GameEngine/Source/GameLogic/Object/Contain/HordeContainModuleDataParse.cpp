// cl: /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /O1 /arch:SSE /G7 /DNDEBUG /MD /GX- /Oi- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
//
// HordeContainModuleData parse-unit.
//
// ?buildFieldParse@HordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00475927, 27 bytes. Chained on the rowed
// TransportContainModuleData base proc at 0x4689DF, then the own table
// at 0x00C45530, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "HordeContain". Row supersedes the parse pin.

class INI;
class MultiIniFieldParse;
struct FieldParse { const char *token; void (*parse)(class INI *, void *, void *, const void *); const void *userData; int offset; };

extern const FieldParse s_hordeContainFieldTable[];
class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class TransportContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class HordeContainModuleData
{
public:
	static void parseRankInfo(INI *, void *, void *, const void *);
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00475927
void HordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(s_hordeContainFieldTable), 0);
}

// RankInfo callback at native table C45530; WB10AF2A0 names parseRankInfo.
// Target47414D..474430 is739 bytes; ctor46F12A confirms the56-byte rank-entry layout.
// The final pointer push_back and its true growth chain must remain visible:
// opaque declarations give a separate pointer home and swap INI throw homes.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
// Keep vector growth's unsigned comparison local. Its standalone template
// copy differs from retail; all uses in this unit are already inlined.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include <stdlib.h>
#include <string.h>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getSepsColon() const { return m_sepsColon; }
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unknown[0x420];
	const char *m_sepsColon;
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

#include "ascii_string.h"

struct BfmeFloat4Record00469C61
{
	float x;
	float y;
	int leaderRank;
	int leaderIndex;
};
typedef BfmeFloat4Record00469C61 HordeContainRankPosition;

struct HordeContainConditionBits
{
	unsigned long m_words[4];
};

void Rva002C8C06Parse(INI *ini, void *instance, void *store, const void *userData);

class HordeContainRankInfo
{
public:
	HordeContainRankInfo();

	int m_rankNumber;
	StringBase<char> m_unitType;
	_STL::vector<HordeContainRankPosition> m_positions;
	HordeContainConditionBits m_grantedWeaponCondition;
	HordeContainConditionBits m_revokedWeaponCondition;
	unsigned char m_hasWeaponConditions;
};

// Native stores and the WB parser establish a vector of rank-entry pointers.
// Its typed helpers fold with the existing pointer-vector providers.

void __cdecl Rva00030830GameFree(void*);
namespace _STL
{
// Game allocations use the native direct free wrapper even though the INI
// parser imports its CRT conversion routines. Preserve that distinction here.
template<> inline void allocator<HordeContainRankInfo*>::deallocate(
    HordeContainRankInfo **p, unsigned int) const
{
    if (p) Rva00030830GameFree(p);
}
template <> void vector<HordeContainRankPosition>::push_back(const HordeContainRankPosition &);

}

typedef _STL::vector<HordeContainRankInfo*> HordeContainRankInfoVector;

void HordeContainModuleData::parseRankInfo(INI *ini, void *instance, void *store, const void *userData)
{
	HordeContainRankInfo *info = new HordeContainRankInfo;
	HordeContainRankInfo *entry=(HordeContainRankInfo*)info;
	HordeContainRankInfoVector &rankInfos = *(HordeContainRankInfoVector *)store;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0 && strcmp(token, "RankNumber") == 0)
	{
		info->m_rankNumber = atoi(ini->getNextToken(ini->getSepsColon()));

		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (token != 0 && strcmp(token, "UnitType") == 0)
		{
			info->m_unitType.set(ini->getNextToken(ini->getSepsColon()));

			token = ini->getNextTokenOrNull(ini->getSepsColon());
			while (token != 0)
			{
				if (strcmp(token, "Position") == 0)
				{
					HordeContainRankPosition position;
					position.leaderRank = -1;
					INI::parseCoord2D(ini, 0, &position, 0);
					info->m_positions.push_back(position);
					token = ini->getNextTokenOrNull(ini->getSepsColon());
					if (token != 0 && strcmp(token, "Z") == 0)
						token = ini->getNextTokenOrNull(ini->getSepsColon());
					continue;
				}
				else if (strcmp(token, "Facing") == 0)
				{
					throw INIException(3, "The Facing field is not supported.");
				}
				else if (strcmp(token, "GrantedWeaponCondition") == 0)
				{
					info->m_hasWeaponConditions = 1;
					Rva002C8C06Parse(ini, 0, &info->m_grantedWeaponCondition, 0);
					token = 0;
					continue;
				}
				else if (strcmp(token, "RevokedWeaponCondition") == 0)
				{
					info->m_hasWeaponConditions = 1;
					Rva002C8C06Parse(ini, 0, &info->m_revokedWeaponCondition, 0);
					token = 0;
					continue;
				}
				else if (strcmp(token, "Leader") == 0)
				{
					if (info->m_positions.empty())
						throw INIException(3, "'Leader' must be preceded by 'Position'");
					HordeContainRankPosition &position = info->m_positions.back();
					if (position.leaderRank != -1)
						throw INIException(3, "Only one 'Leader' per 'Position'");

					token = ini->getNextToken();
					if (token == 0)
						throw INIException(3, "Leader rank expected");
					int rank = atoi(token);
					position.leaderRank = rank;

					HordeContainRankInfoVector::iterator it;
					for (it = rankInfos.begin(); it != rankInfos.end(); ++it)
					{
						if (((HordeContainRankInfo*)*it)->m_rankNumber == rank)
							break;
					}
					if (it == rankInfos.end())
						throw INIException(3, "No RankInfo for specified leader rank '%s'", token);

					token = ini->getNextToken();
					if (token == 0)
						throw INIException(3, "Leader index expected");
					int index = atoi(token);
					position.leaderIndex = index;
					if (index < 0 || index >= ((HordeContainRankInfo*)*it)->m_positions.size())
						throw INIException(3, "Invalid leader index '%s' specified, only 0..%i allowed",
							token, ((HordeContainRankInfo*)*it)->m_positions.size() - 1);
				}
				else
				{
					throw INIException(3, "'Position' expected");
				}

				token = ini->getNextTokenOrNull(ini->getSepsColon());
			}
			rankInfos.push_back(entry);
		}
		else
		{
			throw INIException(3, "UnitType expected");
		}
	}
	else
	{
		throw INIException(3, "RankNumber expected");
	}
}
