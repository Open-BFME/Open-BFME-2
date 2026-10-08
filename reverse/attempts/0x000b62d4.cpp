// ?parseModelConditionFlags@@YAXPAVINI@@PAVWeaponTemplateSetHead@@1@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Oi-
// Banked exact157B shape, native B62D4..B6371. Reference semantic guide:
// Open-BFME-1@34f59164f6d1efd413c5fd37f4894ec834c3c0fe
// game/GameEngine/Source/Common/parseModelConditionFlags.cpp.
// Target proves two76-byte masks, NOT_ handling, unsigned one-bit indexing,
// existing INI member token/lookup calls and actual signed-index B3FA5 setter.
// BFME2 differs from BFME1 in mask size, member INI lookup and positive mask
// update call. /Oi- preserves the two real memset calls; all157bytes match.
// ModelConditionNames is already defined in RiderChangeContainParseRiderInfo.
// Landing requires real B3FA5/43 provider and normal whole-source LINK proof;
// its existing pin is only a lead, not a linkable definition.
#include <string.h>
class WeaponTemplateSetHead {
public:
    unsigned words[19];
    void clear() { memset(words,0,sizeof words); }
    void set(unsigned index) { words[index >> 5] |= 1u << (index & 31); }
    void rva000B3FA5(int, int);
};
class INI {
public:
    const char *getNextTokenOrNull(const char * = 0);
    int scanIndexList(const char *, const char *const *);
};
extern const char *const ModelConditionNames[];
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *,const char *,unsigned);
void parseModelConditionFlags(INI *ini, WeaponTemplateSetHead *all, WeaponTemplateSetHead *positive)
{
    all->clear();
    positive->clear();
    for (const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull()) {
        bool notCondition = _strnicmp(token,"NOT_",4) == 0;
        const char *name = token + (notCondition ? 4 : 0);
        int index = ini->scanIndexList(name,ModelConditionNames);
        all->set(index);
        positive->rva000B3FA5(index,!notCondition);
    }
}
