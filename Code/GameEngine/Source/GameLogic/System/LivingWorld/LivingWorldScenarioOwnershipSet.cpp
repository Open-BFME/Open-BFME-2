// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <algorithm>
class Rva002104B6 { public: void *rva002104B6(void *); };
struct Rva0059E647Arg { char unknown00[0x40]; int value40; };
// Native 0x002DFA43..0x002DFA7A RET4, called by OwnershipSet's building loop
// and the existing template-store export helpers. The original predicate name
// is unknown; retain the existing admitted Rva0059E647Entry::Check spelling.
// Empty key ranges at +3C/+40 accept every key; otherwise search four-byte keys.
struct Rva0059E647Entry
{
    unsigned char unknown00[0x3c];
    int *begin;
    int *end;
    bool Check(int key);
};

class AsciiString;
class Rva00056F61;
#include "../../../../Include/GameClient/Rva0041534BIter.h"
#include "../../../../Include/GameClient/Rva00056F61.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
class ArmorTemplate;
class Rva002B6498
{
public:
    ArmorTemplate *rva002B6498(NameKeyType);
};
struct Rva0059E647Factory
{
    unsigned char unknown00[0x24];
    Rva00056F61 names;
    Rva0059E647Entry *Lookup(int *);
};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
struct Rva0059E647World { void Apply(Rva0059E647Entry *,void *,Rva0059E647Arg *); };
struct Rva002B8660Army;
struct Rva002B8660Player;
struct LivingWorldArmy;
struct Rva002B6A04Player;
struct Rva003F0F13Elem {float a,b;};
#include "../../../../Include/GameLogic/LivingWorldRegion.h"
// Use the Snapshot slot-3 spelling already selected by LivingWorldRegion.
#define xfer DoXfer
#include "../../../../Include/Common/SpawnArmy.h"
#undef xfer
struct Rva004FAFF2 {Rva004FAFF2 &rva004FAFF2(const Rva004FAFF2 &);};
#include "../../../../Include/GameLogic/LivingWorldLogic.h"
struct OwnershipBuildingRegion {
 int word00; int *begin; int *end; int *capacity; int name;
};
#include "../../../../Include/Common/LivingWorldScenario.h"
class LivingWorldScenario::OwnershipSet {
public:
 void spawnBuildingsInRegionsForPlayer(Rva0059E647Arg *);
 void spawnArmiesInRegionsForPlayer(Rva0059E647Arg *);
private:
 int word00; OwnershipBuildingRegion **begin; OwnershipBuildingRegion **end;
 OwnershipBuildingRegion **capacity;
 OwnershipBuildingRegion **armyBegin;OwnershipBuildingRegion **armyEnd;OwnershipBuildingRegion **armyCapacity;
};
// WB 0x014D8350 names this method with source assertions at lines 262..274.
// Native 0x0059E647..0x0059E6D3 RET4: set ranges +4/+8; each entry's
// template-token range +4/+8 and region name +10; player eligibility key +40.
// The entry and player views retain the existing pinned ABI's opaque names.
// Apply's target ignores ECX; its existing member-call pin preserves retail's
// otherwise dead world load before the three-argument call.
void LivingWorldScenario::OwnershipSet::spawnBuildingsInRegionsForPlayer(Rva0059E647Arg *player)
{
    OwnershipBuildingRegion **it = begin;
    OwnershipBuildingRegion **finish = end;
    for (; it != finish; ++it)
    {
        LivingWorldLogic *world = TheLivingWorldLogic;
        OwnershipBuildingRegion *entry = *it;
        Rva002104B6 *lookup = (Rva002104B6 *)world->fieldB0;
        void *region = lookup->rva002104B6(&entry->name);
        if (region)
        {
            int *token = entry->begin;
            int *last = entry->end;
            for (; token != last; ++token)
            {
                Rva0059E647Entry *templ = ((Rva0059E647Factory *)TheLivingWorldBuildingTemplateStore)->Lookup(token);
                if (templ && templ->Check(player->value40))
                    ((Rva0059E647World *)TheLivingWorldLogic)->Apply(templ, region, player);
            }
        }
    }
}

// Native 0x002B931C..0x002B9349 RET4 and WB 0x00D7E760 (unnamed).
// The store's +24 name table maps the four-byte AsciiString handle to a
// NameKeyType at node+8, then the owned 2B6498 lookup returns its template.
// Preserve the existing admitted signature; the caller's int* spelling is
// an opaque four-byte name-handle view, not evidence of an integer lookup.
Rva0059E647Entry *Rva0059E647Factory::Lookup(int *key)
{
    Rva0041534BIter found = names.rva0041534B((const AsciiString *)key);
    if (!found.m_node)
        return 0;
    return (Rva0059E647Entry *)((Rva002B6498 *)this)->rva002B6498(
        *(NameKeyType *)((char *)found.m_node + 8));
}

// Native 59E752..59E81F RET4, 205B; WB14D8560 names the method and
// assertions at304..319. The +10/+14 list and entry +4/+8 token range
// are target accesses; each token is a four-byte name handle passed by
// ADDRESS (not its value) through the established integer-width provider
// signature. The existing 88B SpawnArmy constructor/assignment/destructor
// establish the temporary extent, with its position at20/24. Save the
// region manager separately to preserve the native load/call scheduling.
// All seven retail call targets have their existing whole-body owners;
// earlier spawn-worker deferral was closed by verified2B65B7 recovery.
void LivingWorldScenario::OwnershipSet::spawnArmiesInRegionsForPlayer(Rva0059E647Arg *player) {
 OwnershipBuildingRegion **it=armyBegin;
 OwnershipBuildingRegion **finish=armyEnd;
 for(;it!=finish;++it) {
  LivingWorldLogic *world=TheLivingWorldLogic;
  OwnershipBuildingRegion *entry=*it;
  Rva002104B6 *lookup=(Rva002104B6 *)world->fieldB0;
  LivingWorldRegion *region=(LivingWorldRegion *)lookup->rva002104B6(&entry->name);
  if(region) {
   Rva003F0F13Elem spot;
   region->GetGarrisonArmyPlacementSpot(&spot);
   int *token=entry->begin;
   int *last=entry->end;
   for(;token!=last;++token) {
    Rva002B8660Army *found=TheLivingWorldLogic->UseGenericSpawnArmyForPlayer((int)token,(Rva002B8660Player *)player);
    if(found) {
     SpawnArmy army(0);
     ((Rva004FAFF2 *)&army)->rva004FAFF2(*(const Rva004FAFF2 *)found);
     *reinterpret_cast<Rva003F0F13Elem *>(&army.m_20)=spot;
     TheLivingWorldLogic->spawnArmy(&army,(Rva002B6A04Player *)player,true);
    }
   }
  }
 }
}

// Defined beside its retail OwnershipSet consumer so the predicate retains
// /Oy- without changing the tooltip unit's canonical string wrappers.
bool Rva0059E647Entry::Check(int key)
{
    // Retail observes the range again after the empty-range branch.
    if (*(int *volatile *)&begin == *(int *volatile *)&end)
        return true;
    int value = key;
    // Preserve retail's independent load and store of the outgoing search key.
    *(volatile int *)&key = value;
    int *last = end;
    return _STL::find(begin, last, key) != last;
}
