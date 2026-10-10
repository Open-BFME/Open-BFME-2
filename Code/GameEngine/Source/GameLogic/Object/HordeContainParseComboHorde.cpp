// cl: /Ireference/shims/bfme2_ascii /D_CRTIMP= /O1 /Oy- /MD /EHs /Oi- /D_STLP_USE_STATIC_LIB
// stlport
// Native46F39E..46F542420B; ComboHorde Target/Result/InitiateVoice parser.
// BFME1 HordeContainParseSplitResult source provides the related parser pattern;
// this target's16B record comes from new16 + rowed54B ctor469D50.
// Target strings/INI420 separators/vector pointer append prove the record flow.
// Record name remains neutral; typed ModuleData* vector is existing provider ABI.
// Canonical AsciiString/StringBase replaces old private copy. Real throw
// statements replace the old fabricated throw-info anchor; exception extent8.
// The stack slots match because the pushed record pointer reaches vector::push_back through
// the STLport template (its explicit specialization declaration would hide the body from cl,
// which is what lets retail share the 'slot' temporary). Assigning the AsciiString members with
// operator=(const char *) puts the receiver LEA before the argument push as in retail, and the
// 'InitiateVoice' branch shares one trailing 'if (token)' test with the key check.
#include <vector>
extern "C" int __cdecl strcmp(const char *, const char *);
#include "ascii_string.h"
class INI {
public:
    char unknown[0x420];
    const char *sepsColon;
    const char *getNextToken(const char *);
    const char *getNextTokenOrNull(const char *);
};
class ModuleData;

void Rva00339235(const char *token, void *store);
class Rva00469D50
{
public:
	Rva00469D50();
	AsciiString m_00;
	AsciiString m_04;
	char m_08[8];
};
class INIException {public:INIException(int,const char*,...);INIException(const INIException&);~INIException();private:unsigned opaque[2];};
// ?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z
void parseHordeContainComboHorde(INI *ini, void *instance, void *store, const void *userData)
{
    const char *token;
    {
    Rva00469D50 *entry = new Rva00469D50;
    const ModuleData *slot = (const ModuleData *)entry;
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (!token || strcmp(token, "Target") != 0)
        goto invalidTarget2;
    entry->m_00 = ini->getNextToken(ini->sepsColon);
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (!token || strcmp(token, "Result") != 0)
        goto invalidResult2;
    entry->m_04 = ini->getNextToken(ini->sepsColon);
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (token) {
        if (strcmp(token, "InitiateVoice") == 0) {
            const char *voiceToken = ini->getNextToken(ini->sepsColon);
            Rva00339235(voiceToken, (void *)&entry->m_08);
            token = ini->getNextTokenOrNull(ini->sepsColon);
        }
        if (token)
            goto unknownKey;
    }
    ((_STL::vector<const ModuleData *> *)store)->push_back(slot);
    return;
    }
invalidResult2:
    {
        throw INIException(3, "'Result' expected");
    }
invalidTarget2:
    {
        throw INIException(3, "'Target' expected");
    }
unknownKey:
    {
        AsciiString msg("Unknown key '");
        msg+=token;
        msg+="' in HordeContain's ComboHorde line";
        throw INIException(3, msg.str());
    }
}
