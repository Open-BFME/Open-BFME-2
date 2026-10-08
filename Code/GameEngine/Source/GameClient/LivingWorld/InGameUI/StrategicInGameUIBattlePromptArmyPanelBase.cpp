// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// WorldBuilder 016371B0: StrategicInGameUIBattlePromptArmyPanelBase.cpp:122.
// The helper's original name is unknown. Native 005FEF11..005FEF65 installs
// C7A460 (slot 005FED99), zeros eight counts and visits the panel's summary.
#include "../../../Common/BattlePromptArmyPanelView.h"
#include "unicode_string.h"
// stlport
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

// WB 01637AB0 names BattlePromptArmyPanelBase and asserts lines 283-321.
// Native 005FEFCC..005FF0F6 constructs the clip, counts at most six positive
// categories and populates their icons. Scope ends before the name temporary.
class Image;
class Rva005FF4C5 { public: void rva005FF4C5(const Image*); };
class Rva005FFA4E { public: void rva005FFA4E(int); };
class Rva005FF5B8 { public: void rva005FF5B8(int,const Image*,int); };
class Rva005FF5EE { public: void rva005FF5EE(const UnicodeString &); };
struct Rva005D2355In;
const Image *Rva005F031DGet(Rva005D2355In *);
const Image *Rva005F01C7Get(int);
UnicodeString Rva005C94C8Get(void *);
struct CounterWords { void *vptr; int counts[8]; };
Rva005FEF65::Rva005FEF65(int a,int b,const Rva005FEF11Input **source)
 : m_08((int)this,a,b), m_input14(*source), m_selected24(7)
{
    Rva005FED61 counter(m_input14);
    {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        if (counter.m_counts04[i] > 0 && ++count >= 6) break;
    }
    ((Rva005FF4C5 *)&m_08)->rva005FF4C5(Rva005F031DGet((Rva005D2355In *)m_input14));
    ((Rva005FFA4E *)&m_08)->rva005FFA4E(count);
    m_types18.reserve(count);
    for (int i = 0; i < 8; ++i) {
        if (counter.m_counts04[i] > 0) {
            int slot = m_types18.size();
            ((Rva005FF5B8 *)&m_08)->rva005FF5B8(slot,Rva005F01C7Get(i),counter.m_counts04[i]);
            m_types18.push_back((const ScienceType &)i);
            if (m_types18.size() >= 6) break;
        }
    }
    }
    ((Rva005FF5EE *)&m_08)->rva005FF5EE(Rva005C94C8Get((void *)m_input14));
}
