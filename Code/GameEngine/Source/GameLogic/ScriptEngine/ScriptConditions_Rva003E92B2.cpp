// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateGameModeActive@ScriptConditions@@IAE_NPAVParameter@@@Z @0x003E92B2 45B
// Target evidence: ret 4 free __stdcall, Parameter+0x10 string via rowed
// compareNoCase 0x00037980 against "ringheroes", then TheGameInfo null or
// +0x68==1. Caller 0x003EC2A0 in unclaimed dispatch.
#include "ascii_string.h"

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
	unsigned char m_afterString[8];
};

class GameInfo
{
public:
	unsigned char m_pad[0x68];
	int m_68;
};
extern GameInfo *TheGameInfo;

class ScriptConditions
{
protected:
	bool evaluateGameModeActive(Parameter *p);
};

bool ScriptConditions::evaluateGameModeActive(Parameter *p)
{
	if (p->getString().compareNoCase("ringheroes") == 0) {
		GameInfo *info = TheGameInfo;
		if (info == 0 || info->m_68 == 1)
			return true;
	}
	return false;
}
