// cl: /O1 /G6 /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WorldBuilder callgraph lead: LivingWorldScenario::TeamVictoryCondition::
// hasTeamAchievedVictory. Native 0x004FCEB5..0x004FD013 is 350 bytes, RET 4.
// Target evidence: team membership at player+34; required region count at
// condition+10; four-byte name entries at +14/+18; required duration at +20;
// logic turn at +FC minus region+134. Field names express that inferred role.
// The player/manager helpers retain their existing address-derived owners.
// STLport reserve/push folds and their recursive callees are proven against
// every retail owner by pin_admission. The native allocation/copy helper is
// the 40-byte form without the STLport catch wrapper; ordinary C++ EH remains
// enabled for this predicate's temporary-vector destruction on every return.
#include <vector>
#include "ascii_string.h"

class Rva002E1001 { public: int rva002E1001(); };
class Rva002E2903Player { public: char pad[0x34]; int team; };
class Rva002BA8F1Logic { public: Rva002E2903Player *rva002B52A8(int index); };
class Rva002104B6 { public: void *rva002104B6(void *name); };
class LivingWorldLogic {
public:
    char pad0[0x8c];
    Rva002E2903Player **playersBegin;
    Rva002E2903Player **playersEnd;
    char pad94[0xb0 - 0x94];
    Rva002104B6 *regions;
    char padb4[0xfc - 0xb4];
    int turn;
};
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldRegion {
public:
    bool IsOwnedByTeam(int team) const;
    char pad[0x12c];
    int regionID;
    int word130;
    int lastOwnershipTurn;
};
class LivingWorldScenario { public: class TeamVictoryCondition; };
class LivingWorldScenario::TeamVictoryCondition {
public:
    virtual ~TeamVictoryCondition();
    bool hasTeamAchievedVictory(int team);
    void QueryRegionsAndNumbers(int team, _STL::vector<const LivingWorldRegion *> *out, int *maxOut);
private:
    _STL::vector<int> teams;
    int requiredRegionCount;
    _STL::vector<AsciiString> regionNames;
    int requiredTurns;
};

bool LivingWorldScenario::TeamVictoryCondition::hasTeamAchievedVictory(int team)
{
    char *players = (char *)TheLivingWorldLogic + 0x8c;
    int count = (*(int *)(players + 4) - *(int *)players) >> 2;
    int total = 0;
    for (int i = 0; i < count; ++i) {
        Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(i);
        if (player->team == team)
            total += ((Rva002E1001 *)player)->rva002E1001();
    }
    if (total < requiredRegionCount)
        return false;
    _STL::vector<const LivingWorldRegion *> heldRegions;
    for (unsigned int i = 0; i < regionNames.size(); ++i) {
        AsciiString *names = &regionNames[0];
        Rva002104B6 *manager = TheLivingWorldLogic->regions;
        const LivingWorldRegion *region = (const LivingWorldRegion *)manager->rva002104B6(&names[i]);
        if (!region)
            continue;
        if (!region->IsOwnedByTeam(team))
            return false;
        if (requiredTurns > 0) {
            heldRegions.reserve(regionNames.size());
            heldRegions.push_back(region);
        }
    }
    if (requiredTurns > 0) {
        for (unsigned int i = 0; i < heldRegions.size(); ++i) {
            int lastTurn = heldRegions[i]->lastOwnershipTurn;
            if (TheLivingWorldLogic->turn - lastTurn < requiredTurns)
                return false;
        }
    }
    return true;
}

// WorldBuilder's same named method and native 4FD013..4FD0DA, RET 12.
// Retail deduplicates by the region's +12C word, then appends its pointer;
// maxOut is updated from condition+10. Keep the otherwise unused temporary
// vector: its construction and EH cleanup are present in both target builds.
void LivingWorldScenario::TeamVictoryCondition::QueryRegionsAndNumbers(
    int team, _STL::vector<const LivingWorldRegion *> *out, int *maxOut)
{
    (void)team;
    _STL::vector<const LivingWorldRegion *> unusedRegions;
    for (unsigned int i = 0; i < regionNames.size(); ++i) {
        AsciiString *names = &regionNames[0];
        Rva002104B6 *manager = TheLivingWorldLogic->regions;
        const LivingWorldRegion *region = (const LivingWorldRegion *)manager->rva002104B6(&names[i]);
        if (!region)
            continue;
        for (unsigned int j = 0; j < out->size(); ++j) {
            if ((*out)[j]->regionID == region->regionID)
                goto next;
        }
        out->push_back(region);
    next:;
    }
    if (*maxOut < requiredRegionCount)
        *maxOut = requiredRegionCount;
}
