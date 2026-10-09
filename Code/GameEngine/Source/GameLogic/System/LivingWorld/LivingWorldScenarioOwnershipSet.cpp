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
