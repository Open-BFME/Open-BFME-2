// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WorldBuilder 016371B0: StrategicInGameUIBattlePromptArmyPanelBase.cpp:122.
// The helper's original name is unknown. Native 005FEF11..005FEF65 installs
// C7A460 (slot 005FED99), zeros eight counts and visits the panel's summary.
#include "../../../Common/BattlePromptCounterView.h"
#include "string_base.h"

Rva005FED61::Rva005FED61(const Rva005FEF11Input *panel)
{
    Rva0040CFC7 *summary = panel->m_78;
    for (int *current = m_counts04; current != m_counts04 + 8; ++current)
        *current = 0;
    summary->rva0040CFC7(this);
    rva005FEE8C(panel);
}

// C7A460's only virtual slot. The constructor proves the virtual ABI of the
// already recovered callback and its relationship to the count-adder.
bool Rva005FED61::rva005FED99(const Rva005FED99Arg *arg)
{
    rva005FED61((const AsciiString *)arg->m_04, arg->m_90);
    return true;
}

// WorldBuilder 016373F0, assertions at ArmyPanelBase.cpp:59/67/70/78,
// native 005FEE09..005FEE8C. Static linkage lets MSVC pass the region in EDI,
// as retail does; the ordinary C++ loop counts eligible type-6 buildings.
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
extern class ThingFactory *TheThingFactory;
struct CounterTemplate { char pad[0x5C4]; int index; };
struct CounterKey { char pad[0xC]; StringBase<char> key; };
struct CounterBuilding { char pad[0x28]; CounterKey *key; };
struct CounterPlot {
    char pad[0x20]; CounterBuilding *building;
    char pad24[0x34-0x24]; bool excluded;
};
class Rva00318C32Ret {
public:
    char pad[0x11C]; bool flag;
    char pad11D[0x13C-0x11D]; int owner;
    char pad140[0x170-0x140]; CounterPlot **begin; CounterPlot **end;
};
class Rva00318C79Owner { public: Rva00318C32Ret *rva00318C32(); };
struct CounterPanel {
    char pad[0x18]; StringBase<char> key;
    char pad1C[0x54-0x1C]; int owner;
};
static int rva005FEE09(Rva00318C32Ret *region)
{
    int count = 0;
    int length = region->end - region->begin;
    for (int i = 0; i < length; ++i) {
        CounterPlot *plot = region->begin[i];
        if (!plot->building || plot->excluded) continue;
        StringBase<char> *key = &plot->building->key->key;
        if (key->isEmpty()) continue;
        CounterTemplate *value = (CounterTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)key);
        if (value && value->index == 6) ++count;
    }
    if (region->flag) ++count;
    return count;
}
void Rva005FED61::rva005FEE8C(const Rva005FEF11Input *input)
{
    const CounterPanel *panel = (const CounterPanel *)input;
    if (!panel->key.isEmpty()) return;
    Rva00318C32Ret *region = ((Rva00318C79Owner *)input)->rva00318C32();
    if (!region || panel->owner != region->owner) return;
    m_counts04[6] += rva005FEE09(region);
}
