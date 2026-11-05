// cl: /Ireference/shims/bfme2_ascii /D_CRTIMP= /O1 /MD /EHs /Oi- /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS /Ireference/shims/bfmealloc
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
#include <string.h>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
#include "../../../Include/Common/INI/INI.h"
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
#include "../../../Include/Common/INI/FieldParse.h"
// ?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z
void parseHordeContainComboHorde(INI *ini, void *instance, void *store, const void *userData)
{
    const char *token;
    {
    Rva00469D50 *entry = new Rva00469D50;
    const ModuleData *slot = (const ModuleData *)entry;
    token = ini->getNextTokenOrNull(ini->m_sepsColon);
    if (!token || strcmp(token, "Target") != 0)
        goto invalidTarget2;
    entry->m_00 = ini->getNextToken(ini->m_sepsColon);
    token = ini->getNextTokenOrNull(ini->m_sepsColon);
    if (!token || strcmp(token, "Result") != 0)
        goto invalidResult2;
    entry->m_04 = ini->getNextToken(ini->m_sepsColon);
    token = ini->getNextTokenOrNull(ini->m_sepsColon);
    if (token) {
        if (strcmp(token, "InitiateVoice") == 0) {
            const char *voiceToken = ini->getNextToken(ini->m_sepsColon);
            Rva00339235(voiceToken, (void *)&entry->m_08);
            token = ini->getNextTokenOrNull(ini->m_sepsColon);
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
