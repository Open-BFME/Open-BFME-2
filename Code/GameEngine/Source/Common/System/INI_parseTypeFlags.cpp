// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// Reference-first: BFME1 Common/INI/ini.cpp parseDamageTypeFlags, itself from
// GeneralsMD Common/INI/INI.cpp. PC deltas: member scanIndexList and the
// established INIException filler/throw ABI. PC FieldParse DamageTypes and
// DamageFXTypes callbacks identify this full 192-byte body at RVA 0x338CD0.
// BFME2DamageTypeNames is a descriptive alias of the verified FORCE..POISON
// pointer array at VA 0xDBE858, not fabricated source data. Exception throwinfo
// anchor denotes the existing INIException chain at VA 0xCFE2FC.
#include "../../../Include/Common/INI/INI.h"
extern const char *TheVeterancyNames[];
// Owned here: parseDamageTypeFlags (0x338CD0) is the only reader of the .data table at VA 0x00DBE858
// (retail's entries and NULL terminator, transcribed from the image).
extern const char *const BFME2DamageTypeNames[] = {
    "FORCE",
    "CRUSH",
    "SLASH",
    "PIERCE",
    "SIEGE",
    "STRUCTURAL",
    "FLAME",
    "HEALING",
    "UNRESISTABLE",
    "WATER",
    "PENALTY",
    "FALLING",
    "TOPPLING",
    "REFLECTED",
    "PASSENGER",
    "MAGIC",
    "CHOP",
    "HERO",
    "SPECIALIST",
    "URUK",
    "HERO_RANGED",
    "FLY_INTO",
    "UNDEFINED",
    "LOGICAL_FIRE",
    "CAVALRY",
    "CAVALRY_RANGED",
    "POISON",
    0
};
// Owned here: parseDeathTypeFlags (0x338D91) is the only reader of the .data table at VA 0x00DBE8D8
// (retail's entries and NULL terminator, transcribed from the image).
extern const char *const BFME2DeathTypeNames[] = {
    "NORMAL",
    "NONE",
    "CRUSHED",
    "BURNED",
    "EXPLODED",
    "POISONED",
    "TOPPLED",
    "FLOODED",
    "SUICIDED",
    "LASERED",
    "DETONATED",
    "SPLATTED",
    "POISONED_BETA",
    "EXTRA_2",
    "EXTRA_3",
    "EXTRA_4",
    "EXTRA_5",
    "EXTRA_6",
    "EXTRA_7",
    "EXTRA_8",
    "KNOCKBACK",
    "SUPERNATURAL",
    "FADED",
    "SLAUGHTERED",
    0
};
#include <string.h>
#include "../../../Include/Common/INI/FieldParse.h"

// PC RVA 0x338C0F, directly before parseDamageTypeFlags as in GeneralsMD INI.cpp:
// the same 192 bytes over TheVeterancyNames (VA 0xDBA4C0, the table Upgrade.cpp
// reads) with the same exception text.
void INI::parseVeterancyLevelFlags(INI *ini, void *, void *store, const void *)
{
    unsigned int flags = 0xFFFFFFFF;
    for (const char *token=ini->getNextToken(0); token; token=ini->getNextTokenOrNull(0)) {
        if (_strcmpi(token,"ALL")==0) { flags=0xFFFFFFFF; continue; }
        if (_strcmpi(token,"NONE")==0) { flags=0; continue; }
        if (token[0]=='+') {
            int bit=ini->scanIndexList(token+1,TheVeterancyNames);
            flags |= 1 << (bit-1);
            continue;
        }
        if (token[0]=='-') {
            int bit=ini->scanIndexList(token+1,TheVeterancyNames);
            flags &= ~(1 << (bit-1));
            continue;
        }
        throw INIException(5,"ALL, NONE, + or - expected");
    }
    *(unsigned int *)store=flags;
}

void INI::parseDamageTypeFlags(INI *ini, void *, void *store, const void *)
{
    unsigned int flags = 0xFFFFFFFF;
    for (const char *token=ini->getNextToken(0); token; token=ini->getNextTokenOrNull(0)) {
        if (_strcmpi(token,"ALL")==0) { flags=0xFFFFFFFF; continue; }
        if (_strcmpi(token,"NONE")==0) { flags=0; continue; }
        if (token[0]=='+') {
            int bit=ini->scanIndexList(token+1,BFME2DamageTypeNames);
            flags |= 1 << (bit-1);
            continue;
        }
        if (token[0]=='-') {
            int bit=ini->scanIndexList(token+1,BFME2DamageTypeNames);
            flags &= ~(1 << (bit-1));
            continue;
        }
        throw INIException(5,"ALL, NONE, + or - expected");
    }
    *(unsigned int *)store=flags;
}

// PC RVA 0x338D91; DeathTypes table and NORMAL..SLAUGHTERED names at VA 0xDBE8D8.
void INI::parseDeathTypeFlags(INI *ini, void *, void *store, const void *)
{
    unsigned int flags = 0xFFFFFFFF;
    for (const char *token=ini->getNextToken(0); token; token=ini->getNextTokenOrNull(0)) {
        if (_strcmpi(token,"ALL")==0) { flags=0xFFFFFFFF; continue; }
        if (_strcmpi(token,"NONE")==0) { flags=0; continue; }
        if (token[0]=='+') {
            int bit=ini->scanIndexList(token+1,BFME2DeathTypeNames);
            flags |= 1 << (bit-1);
            continue;
        }
        if (token[0]=='-') {
            int bit=ini->scanIndexList(token+1,BFME2DeathTypeNames);
            flags &= ~(1 << (bit-1));
            continue;
        }
        throw INIException(5,"ALL, NONE, +, or - expected");
    }
    *(unsigned int *)store=flags;
}
