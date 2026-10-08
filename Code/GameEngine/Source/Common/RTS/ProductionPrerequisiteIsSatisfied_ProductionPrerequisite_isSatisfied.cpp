// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/GameEngine/Source/Common/RTS
//
// ?isSatisfied@ProductionPrerequisite@@QBE_NPBVPlayer@@@Z
// retail 0x004F4CE5, 219 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/RTS/ProductionPrerequisiteIsSatisfied.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport

#include <vector>

#include "unicode_string.h"

class Player;
class AsciiString;

// Only the display name is modelled: retail reads it at +0x30 of the
// template (getRequiresList passes unit+0x30 to the wide set 0x00037150).
class ThingTemplate
{
public:
    const UnicodeString &getDisplayName() const
    {
        return m_displayName;
    }

private:
    char m_unmodelled[0x30];
    UnicodeString m_displayName;
};

// fetch(const char *) is called through vtable+0x3C; the AsciiString overload
// sits at +0x38 (DownloadManagerOnStatusUpdate.cpp). MSVC7.1 assigns
// same-name overloaded virtuals in reverse declaration order.
class GameTextInterface
{
public:
    virtual ~GameTextInterface() {}
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
    virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

enum ScienceType
{
};

enum UpgradeType
{

    UPGRADE_TYPE_PLAYER,
    UPGRADE_TYPE_OBJECT
};

class UpgradeTemplate
{
public:
    virtual ~UpgradeTemplate();

    UpgradeType getUpgradeType() const
    {
        return m_type;
    }

private:
    UpgradeType m_type;
};

class ProductionPrerequisite
{
public:
    UnicodeString getRequiresList(const Player *player) const;
    bool isSatisfied(const Player *player) const;

private:
    enum
    {
        UNIT_OR_WITH_PREV = 0x01
    };

    enum
    {
        MAX_PREREQ = 32
    };

    struct PrereqUnitRec
    {
        const ThingTemplate *unit;
        int flags;
        void *name;
    };

    int calcNumPrereqUnitsOwned(const Player *player, int counts[32]) const;

    std::vector<PrereqUnitRec> m_prereqUnits;
    std::vector<ScienceType> m_prereqSciences;
    std::vector<UpgradeTemplate *> m_prereqUpgrades;
};

class Player
{
public:
    bool hasScience(ScienceType science) const;
    bool hasUpgradeComplete(const UpgradeTemplate *upgrade);
};

bool ProductionPrerequisite::isSatisfied(const Player *player) const
{
    int i;

    if (!player)
        return false;

    for (i = 0; i < m_prereqSciences.size(); i++)
    {
        if (!player->hasScience(m_prereqSciences[i]))
            return false;
    }

    for (i = 0; i < m_prereqUpgrades.size(); i++)
    {
        const UpgradeTemplate *upgrade = m_prereqUpgrades[i];
        if (upgrade->getUpgradeType() != UPGRADE_TYPE_PLAYER)
            return false;
        if (!const_cast<Player *>(player)->hasUpgradeComplete(upgrade))
            return false;
    }

    int ownCount[32];
    int cnt = calcNumPrereqUnitsOwned(player, ownCount);

    for (i = 1; i < cnt; i++)
    {
        if (m_prereqUnits[i].flags & 1)
        {
            ownCount[i] += ownCount[i - 1];
            ownCount[i - 1] = -1;
        }
    }

    for (i = 0; i < cnt; i++)
    {
        if (ownCount[i] == -1)
            continue;
        if (ownCount[i] == 0)
            return false;
    }

    return true;
}

UnicodeString ProductionPrerequisite::getRequiresList(const Player *player) const
{
    if (!player)
        return UnicodeString::TheEmptyString;

    UnicodeString requiresList = UnicodeString::TheEmptyString;

    int ownCount[MAX_PREREQ];
    int cnt = calcNumPrereqUnitsOwned(player, ownCount);
    int i;

    bool orRequirements[MAX_PREREQ];
    for (i = 0; i < MAX_PREREQ; i++)
    {
        orRequirements[i] = false;
    }

    for (i = 1; i < cnt; i++)
    {
        if (m_prereqUnits[i].flags & UNIT_OR_WITH_PREV)
        {
            orRequirements[i] = true;
            ownCount[i] += ownCount[i - 1];
            ownCount[i - 1] = -1;
        }
    }

    const ThingTemplate *unit;
    UnicodeString unitName;
    bool firstRequirement = true;
    for (i = 0; i < cnt; i++)
    {
        if (ownCount[i] == 0)
        {
            if (orRequirements[i])
            {
                unit = m_prereqUnits[i - 1].unit;
                unitName = unit->getDisplayName();
                unitName.concat(L" ");
                unitName.concat(TheGameText->fetch("CONTROLBAR:OrRequirement", 0));
                unitName.concat(L" ");
                requiresList.concat(unitName);
            }

            unit = m_prereqUnits[i].unit;
            unitName = unit->getDisplayName();

            if (firstRequirement)
                firstRequirement = false;
            else
                unitName.concat(L"\n");

            requiresList.concat(unitName);
        }
    }

    bool hasSciences = true;
    for (i = 0; i < m_prereqSciences.size(); i++)
    {
        if (!player->hasScience(m_prereqSciences[i]))
            hasSciences = false;
    }

    if (hasSciences == false)
    {
        if (firstRequirement)
            firstRequirement = false;
        else
            unitName.concat(L"\n");
        requiresList.concat(TheGameText->fetch("CONTROLBAR:GeneralsPromotion", 0));
    }

    bool hasUpgrades = true;
    for (i = 0; i < m_prereqUpgrades.size(); i++)
    {
        if (!const_cast<Player *>(player)->hasUpgradeComplete(m_prereqUpgrades[i]))
            hasUpgrades = false;
    }

    if (hasUpgrades == false)
    {
        if (firstRequirement)
            firstRequirement = false;
        else
            unitName.concat(L"\n");
        requiresList.concat(TheGameText->fetch("CONTROLBAR:UpgradeRequired", 0));
    }

    return requiresList;
}
