// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc
class Rva002104B6 { public: void *rva002104B6(void *); };
struct Rva0059E647Arg { char unknown00[0x40]; int value40; };
struct Rva0059E647Entry { bool Check(int); };
class AsciiString;
class Rva00056F61;
struct Rva0041534BIter
{
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *, Rva00056F61 *);
};
class Rva00056F61
{
public:
    Rva0041534BIter rva0041534B(const AsciiString *);
};
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
class LivingWorldRegion {public:void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *);};
class Rva004E3184 {
public:
 Rva004E3184(int);
 virtual ~Rva004E3184();
 unsigned char beforePos[0x20-4];
 Rva003F0F13Elem pos;
 unsigned char afterPos[0x58-0x28];
};
struct Rva004FAFF2 {Rva004FAFF2 &rva004FAFF2(const Rva004FAFF2 &);};
class LivingWorldLogic {public:
 Rva002B8660Army *UseGenericSpawnArmyForPlayer(int,Rva002B8660Player *);
 LivingWorldArmy *spawnArmy(Rva004E3184 *,Rva002B6A04Player *,bool);
 char unknown00[0xb0]; Rva002104B6 *regions;
};
extern LivingWorldLogic *TheLivingWorldLogic;
struct OwnershipBuildingRegion {
 int word00; int *begin; int *end; int *capacity; int name;
};
class LivingWorldScenario { public: class OwnershipSet; };
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
  Rva002104B6 *lookup=world->regions;
  LivingWorldRegion *region=(LivingWorldRegion *)lookup->rva002104B6(&entry->name);
  if(region) {
   Rva003F0F13Elem spot;
   region->GetGarrisonArmyPlacementSpot(&spot);
   int *token=entry->begin;
   int *last=entry->end;
   for(;token!=last;++token) {
    Rva002B8660Army *found=TheLivingWorldLogic->UseGenericSpawnArmyForPlayer((int)token,(Rva002B8660Player *)player);
    if(found) {
     Rva004E3184 army(0);
     ((Rva004FAFF2 *)&army)->rva004FAFF2(*(const Rva004FAFF2 *)found);
     army.pos=spot;
     TheLivingWorldLogic->spawnArmy(&army,(Rva002B6A04Player *)player,true);
    }
   }
  }
 }
}
