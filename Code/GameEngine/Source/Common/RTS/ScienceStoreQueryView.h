#ifndef BFME2_SCIENCE_STORE_QUERY_VIEW_H
#define BFME2_SCIENCE_STORE_QUERY_VIEW_H

#include "unicode_string.h"

// Shared declarations for the query and purchase-cost consumers, preserving their target
// accesses. The opaque bytes do not assert a complete ScienceInfo layout.
enum ScienceType { SCIENCE_INVALID = -1 };
class AsciiString;
class Player;
class Rva0043D3A8;

// Existing name-key operations used by the two inverse query consumers.
enum NameKeyType { NAMEKEY_INVALID = -1 };
class NameKeyGenerator
{
public:
    const AsciiString &keyToName(NameKeyType key);
    NameKeyType nameToKey(const AsciiString &str);
};

class ScienceInfo
{
    char m_opaque00[0x14];
public:
    UnicodeString m_name; // +0x14
    UnicodeString m_description; // +0x18
private:
    char m_opaque1c[0x28 - 0x1c];
public:
    int m_sciencePurchasePointCost; // +0x28
    int m_sciencePurchasePointCostMP; // +0x2c
    bool m_grantable; // +0x30
};

class ScienceStore
{
    const ScienceInfo *findScienceInfo(ScienceType st) const;
    bool rva000E7C20SciencePrereqMemo(const Player *player, ScienceType st,
        void *memo) const;
public:
    bool isScienceGrantable(ScienceType st) const;
    bool playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType science) const;
    int getSciencePurchaseCost(ScienceType science) const;
    bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
    bool isValidScience(ScienceType st) const;
    AsciiString getInternalNameForScience(ScienceType science) const;
    bool playerHasRootPrereqsForScience(const Player *player, ScienceType st) const;
    bool getNameAndDescription(ScienceType st, UnicodeString &name,
        UnicodeString &description) const;
    ScienceType getScienceFromInternalName(const AsciiString &name) const;
};

#endif
