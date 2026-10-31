// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 0x003E7E54..0x003E7F3A, RET16; ECX is unused on entry. A ScriptConditions
// member (the condition dispatcher 0x003EA9AF reloads ECX = this for the call).
// Four Parameter pointers have native modes at +8, float values at +C,
// and strings at +10, consistent with the adjacent rowed condition helpers.
// A named team is resolved through verified getTeamNamed(AsciiString,false),
// then the independently rowed Team::rva003A3736 float result is compared
// against the threshold using the six native modes. The Team metric and
// this condition's original spelling remain unknown.
// Source guide: ZH ScriptConditions.cpp's six Parameter comparison cases;
// the target's full branches, parameter order and callees establish this body.
#include "ascii_string.h"
class ScriptConditions;
class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};
#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/ScriptConditions.h"
bool ScriptConditions::evaluateTeamCachedFloatCompare(Parameter *teamName,Parameter *comparison,Parameter *threshold,Parameter *input)
{
    if (!teamName || !input || !comparison || !threshold)
        return false;
    Team *team=TheScriptEngine->getTeamNamed(teamName->m_string,false);
    if (!team) return false;
    float m_real=team->rva003A3736(input->m_real);
    switch(comparison->m_int) {
    case 0: return m_real<threshold->m_real;
    case 1: return m_real<=threshold->m_real;
    case 2: return m_real==threshold->m_real;
    case 3: return m_real>=threshold->m_real;
    case 4: return m_real>threshold->m_real;
    case 5: return m_real!=threshold->m_real;
    }
    return false;
}
