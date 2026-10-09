// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
class Rva002104B6 { public: void *rva002104B6(void *); };
struct Rva0059E647Arg { char unknown00[0x40]; int value40; };
struct Rva0059E647Entry { bool Check(int); };
struct Rva0059E647Factory { Rva0059E647Entry *Lookup(int *); };
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
struct Rva0059E647World { void Apply(Rva0059E647Entry *,void *,Rva0059E647Arg *); };
class LivingWorldLogic { public: char unknown00[0xb0]; Rva002104B6 *regions; };
extern LivingWorldLogic *TheLivingWorldLogic;
struct OwnershipBuildingRegion {
 int word00; int *begin; int *end; int *capacity; int name;
};
class LivingWorldScenario { public: class OwnershipSet; };
class LivingWorldScenario::OwnershipSet {
public:
 void spawnBuildingsInRegionsForPlayer(Rva0059E647Arg *);
private:
 int word00; OwnershipBuildingRegion **begin; OwnershipBuildingRegion **end;
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
        Rva002104B6 *lookup = world->regions;
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
