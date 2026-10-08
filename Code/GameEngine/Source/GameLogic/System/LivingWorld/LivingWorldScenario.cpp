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
#include "../../../../../../reference/shims/bfme_stlport_unsigned_max_link/unsigned_max.h"
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
// The target output element is a four-byte region ID, not ScienceType.
// This local ABI tag makes no claim about the original enum spelling.
enum Rva004FD8B8RegionID { RVA004FD8B8_REGION_ZERO = 0 };
class Rva0020F442 { public: AsciiString *rva0020F442(const AsciiString &name); };
class Rva00210390 { public: void *rva00210390(const AsciiString *name); };
class Rva004FD6F9 { public: bool rva004FD6F9(const StringBase<char> &name); };
class LivingWorldScenario { public: class TeamVictoryCondition; class PlayerDefeatCondition; class TeamDefeatCondition; class Scenario; };
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

// Native 4FC8B3..4FC8D6, RET4. Scenario::ParseINI 4FD94E passes the
// newly constructed scenario to this receiver. WB130EA40 confirms pointer
// ownership at +1C. Retail globally deletes the previous pointer: virtual
// destructor slot0 receives flag0, followed by operator delete even if null.
// Both view names and replaceScenario describe the consumed role only;
// the original owner class and method spelling remain unidentified.
class ScenarioOwnedObjectView { public: virtual ~ScenarioOwnedObjectView(); };
class ScenarioOwnerView {
    unsigned char unknown[0x1C];
    ScenarioOwnedObjectView *owned;
public:
    void replaceScenario(ScenarioOwnedObjectView *);
};
void ScenarioOwnerView::replaceScenario(ScenarioOwnedObjectView *scenario) {
    ::delete owned;
    owned = scenario;
}

// Native 4FC8D6..4FC91D, 71 bytes, RET4. WorldBuilder's named body and
// home-region ownership check establish the method identity. The existing
// address-derived player ABI view is retained; original reference and const
// qualifications are not claimed by this source spelling.
class LivingWorldScenario::PlayerDefeatCondition {
public:
    virtual ~PlayerDefeatCondition();
    bool isPlayerDefeated(Rva002E1001 *player);
private:
    _STL::vector<int> teams;
    int requiredRegionCount;
    bool requireHome;
};
bool LivingWorldScenario::PlayerDefeatCondition::isPlayerDefeated(Rva002E1001 *player)
{
    if (requireHome) {
        Rva002104B6 *manager = TheLivingWorldLogic->regions;
        void *region = manager->rva002104B6((char *)player + 0x2c);
        if (region && *(int *)((char *)region + 0x13c) != *(int *)((char *)player + 0x14))
            return true;
    }
    bool defeated = player->rva002E1001() <= requiredRegionCount;
    return defeated;
}

// Native 4FC970..4FC9CE, 94 bytes, RET4. WB TeamDefeatCondition's
// callgraph and team-membership assertion establish identity. The target
// sums owned-region counts for that team and fails above condition+10.
class LivingWorldScenario::TeamDefeatCondition {
public:
    virtual ~TeamDefeatCondition();
    bool isTeamDefeated(int team);
private:
    _STL::vector<int> teams;
    int requiredRegionCount;
};
bool LivingWorldScenario::TeamDefeatCondition::isTeamDefeated(int team)
{
    char *players = (char *)TheLivingWorldLogic + 0x8c;
    int count = (*(int *)(players + 4) - *(int *)players) >> 2;
    int total = 0;
    for (int i = 0; i < count; ++i) {
        Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(i);
        if (player->team != team)
            continue;
        total += ((Rva002E1001 *)player)->rva002E1001();
        if (total > requiredRegionCount)
            return false;
    }
    return true;
}

class LivingWorldScenario::Scenario {
public:
    void getDefaultStartSpots(const AsciiString &campaignName, _STL::vector<Rva004FD8B8RegionID> &out);
private:
    char pad[0x44];
    _STL::vector<AsciiString> defaultStartRegions;
};
// Native 4FD8B8..4FD94E, 150 bytes, RET8. WB assertions at lines825..836
// name regionCampaign, default-start names and allowsStartInRegion; native
// confirms the +44 name vector, +12C output ID and each lookup/filter call.
// The lookups and restriction helper keep their existing ABI views.
void LivingWorldScenario::Scenario::getDefaultStartSpots(const AsciiString &campaignName, _STL::vector<Rva004FD8B8RegionID> &out)
{
    out.erase(out.begin(), out.end());
    if (defaultStartRegions.empty())
        return;
    AsciiString *campaign = ((Rva0020F442 *)TheLivingWorldLogic->regions)->rva0020F442(campaignName);
    if (!campaign)
        return;
    for (unsigned int i = 0; i < defaultStartRegions.size(); ++i) {
        void *region = ((Rva00210390 *)campaign)->rva00210390(&defaultStartRegions[i]);
        if (!region)
            continue;
        if (!((Rva004FD6F9 *)this)->rva004FD6F9(reinterpret_cast<const StringBase<char> &>(defaultStartRegions[i])))
            continue;
        Rva004FD8B8RegionID id = (Rva004FD8B8RegionID)*(int *)((char *)region + 0x12c);
        out.push_back(id);
    }
}
