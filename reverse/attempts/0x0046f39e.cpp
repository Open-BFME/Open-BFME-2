// ?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.98 date=2026-10-04
// Provenance: adapted from reference/open-bfme-1/Code/GameEngine/Source/
// GameLogic/Object/Contain/HordeContainParseSplitResult.cpp. Donor names are
// descriptive, not recovered PC symbols. PC table C45530 has SplitHorde at
// member +1A4 and callback 46F288. Target allocates 12 bytes; string handles
// are +0/+4 and rank +8. StringBase<char>::set is the matched body at 55F5.
// The append is a 4-byte pointer slot; ModuleData below is only the matched
// vector row's spelling, not a claim about the pointed-to record's identity.
// The called vector push_back at 4DFCB0 is independently verified over all
// 49 bytes: three-pointer vector layout, dword construct, +4 end increment,
// overflow 2DFCF6 (140 bytes; dword-distance sizing and copying).
// Error labels end the pointer-slot lifetime before constructing INIException;
// this permits the same stack-slot reuse visible in the 277-byte PC body.
// The throw-info object below is an address anchor only, following the matched
// INI_parsePositiveNonZeroReal.cpp convention; its data is not reconstructed.
// cl: /O1 /Oy- /MD /EHs /Oi- /D_STLP_USE_STATIC_LIB
// stlport
// BFME1 HordeContainParseSplitResult.cpp semantic donor. PC table C45530
// SplitHorde -> 46F288; INI colon separators +420; 12-byte split record.
#include <vector>
extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
template<class T> class StringBase {
public:
    void *m_data;
    StringBase() { m_data = 0; }
    void set(const T *);
    void concat(const T *);
    ~StringBase();
private:
    StringBase(const T *s);
    friend void parseHordeContainComboHorde(class INI *ini, void *instance, void *store, const void *userData);
};
class INI {
public:
    char unknown[0x420];
    const char *sepsColon;
    const char *getNextToken(const char *);
    const char *getNextTokenOrNull(const char *);
};
class HordeContainSplitEntry {
public:
    StringBase<char> splitResult;
    StringBase<char> unitType;
    int rankNumber;
};
class ModuleData;
namespace _STL {
template <> void vector<const ModuleData *>::push_back(const ModuleData * const &);
}
void Rva00339235(const char *token, void *store);
class Rva00469D50
{
public:
	Rva00469D50();
	StringBase<char> m_00;
	StringBase<char> m_04;
	char m_08[8];
};
extern const char g_Rva0107301CEmptyString[];
struct INIException { char *message; int code; INIException(int argCount, const char *format, ...); };
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct SplitThrowInfoAnchor { int a,b,c,d; };
static const SplitThrowInfoAnchor splitThrowInfoAnchor = {0,0,0,0};
void parseHordeContainSplitResult(INI *ini, void *instance, void *store, const void *userData)
{
  {
    HordeContainSplitEntry *entry = new HordeContainSplitEntry;
    const ModuleData *slot = (const ModuleData *)entry;
    const char *token = ini->getNextTokenOrNull(ini->sepsColon);
    if (!token || strcmp(token, "SplitResult") != 0) goto invalidTarget;
    entry->splitResult.set(ini->getNextToken(ini->sepsColon));
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (!token || strcmp(token, "UnitType") != 0) goto invalidResult;
    entry->unitType.set(ini->getNextToken(ini->sepsColon));
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (token && strcmp(token, "RankNumber") == 0)
        entry->rankNumber = atoi(ini->getNextToken(ini->sepsColon));
    else
        entry->rankNumber = 0;
    ((_STL::vector<const ModuleData *> *)store)->push_back(slot);
    return;
  }
invalidResult:
    {
        INIException e(3, "'Result' expected");
        _CxxThrowException(&e, (const _s__ThrowInfo *)&splitThrowInfoAnchor); __assume(0);
    }
invalidTarget:
    {
        INIException e(3, "'Target' expected");
        _CxxThrowException(&e, (const _s__ThrowInfo *)&splitThrowInfoAnchor); __assume(0);
    }
}
// ?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z present-unmatched
void parseHordeContainComboHorde(INI *ini, void *instance, void *store, const void *userData)
{
    Rva00469D50 *entry = new Rva00469D50;
    const ModuleData *slot = (const ModuleData *)entry;
    const char *token = ini->getNextTokenOrNull(ini->sepsColon);
    if (!token || strcmp(token, "Target") != 0)
        goto invalidTarget2;
    entry->m_00.set(ini->getNextToken(ini->sepsColon));
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (!token || strcmp(token, "Result") != 0)
        goto invalidResult2;
    entry->m_04.set(ini->getNextToken(ini->sepsColon));
    token = ini->getNextTokenOrNull(ini->sepsColon);
    if (token) {
        if (strcmp(token, "InitiateVoice") != 0)
            goto unknownKey;
        Rva00339235(ini->getNextToken(ini->sepsColon), (void *)&entry->m_08);
        token = ini->getNextTokenOrNull(ini->sepsColon);
        if (token)
            goto unknownKey;
    }
    ((_STL::vector<const ModuleData *> *)store)->push_back(slot);
    return;
unknownKey:
    {
        StringBase<char> msg("Unknown key '");
        msg.concat(token);
        msg.concat("' in HordeContain's ComboHorde line");
        INIException e(3, msg.m_data ? (const char *)msg.m_data + 8 : g_Rva0107301CEmptyString);
        _CxxThrowException(&e, (const _s__ThrowInfo *)&splitThrowInfoAnchor); __assume(0);
    }
invalidResult2:
    {
        INIException e(3, "'Result' expected");
        _CxxThrowException(&e, (const _s__ThrowInfo *)&splitThrowInfoAnchor); __assume(0);
    }
invalidTarget2:
    {
        INIException e(3, "'Target' expected");
        _CxxThrowException(&e, (const _s__ThrowInfo *)&splitThrowInfoAnchor); __assume(0);
    }
}
