// ?parseHordeContainRankInfo@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.82 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /GX- /Oi- /D_STLP_USE_STATIC_LIB
// stlport
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <vector>
#include <stdlib.h>

extern "C" int __cdecl strcmp(const char *, const char *);

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

template <class T> class StringBase
{
public:
	void set(const T *text);

private:
	void *m_data;
};

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

struct Rva004DFCB0Element
{
	HordeContainRankInfo *info;
};

namespace _STL
{
template <> void vector<HordeContainRankPosition>::push_back(const HordeContainRankPosition &);
template <> void vector<Rva004DFCB0Element>::push_back(const Rva004DFCB0Element &);
}

typedef _STL::vector<Rva004DFCB0Element> HordeContainRankInfoVector;

void parseHordeContainRankInfo(INI *ini, void *instance, void *store, const void *userData)
{
	HordeContainRankInfo *info = new HordeContainRankInfo;
	Rva004DFCB0Element entry;
	entry.info = info;
	HordeContainRankInfoVector &rankInfos = *(HordeContainRankInfoVector *)store;

	const char *leaderToken;
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
					break;
				}
				else if (strcmp(token, "RevokedWeaponCondition") == 0)
				{
					info->m_hasWeaponConditions = 1;
					Rva002C8C06Parse(ini, 0, &info->m_revokedWeaponCondition, 0);
					break;
				}
				else if (strcmp(token, "Leader") == 0)
				{
					if (info->m_positions.empty())
						throw INIException(3, "'Leader' must be preceded by 'Position'");
					HordeContainRankPosition &position = info->m_positions.back();
					if (position.leaderRank != -1)
						throw INIException(3, "Only one 'Leader' per 'Position'");

					leaderToken = ini->getNextToken();
					if (leaderToken == 0)
						throw INIException(3, "Leader rank expected");
					int rank = atoi(leaderToken);
					position.leaderRank = rank;

					HordeContainRankInfoVector::iterator it;
					for (it = rankInfos.begin(); it != rankInfos.end(); ++it)
					{
						if (it->info->m_rankNumber == rank)
							break;
					}
					if (it == rankInfos.end())
						throw INIException(3, "No RankInfo for specified leader rank '%s'", leaderToken);

					leaderToken = ini->getNextToken();
					if (leaderToken == 0)
						throw INIException(3, "Leader index expected");
					int index = atoi(leaderToken);
					position.leaderIndex = index;
					if (index < 0 || index >= it->info->m_positions.size())
						throw INIException(3, "Invalid leader index '%s' specified, only 0..%i allowed",
							leaderToken, it->info->m_positions.size() - 1);
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
