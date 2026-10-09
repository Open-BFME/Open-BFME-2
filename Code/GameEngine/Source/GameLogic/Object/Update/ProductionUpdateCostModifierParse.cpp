// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native49D7B3..49D82F ctor and49DE6D..49DEC8 field parser. The field table
// C51380 independently names RequiredUpgrade string0, ModifierFilter4,
// CostMultiplier8, TimeMultiplierC, HeroPurchase10 and HeroRevive11.
// ProductionModifierEntry keeps the already-rowed neutral role name (49D12D),
// and its filter keeps the native8B destructor provider360D26 for unwind.
// Original source identities remain unknown: ZH ProductionUpdate is a subsystem
// lead, but does not contain this BFME2 extension. Existing filter handle,
// fixed-storage copy, INI and four-byte list providers keep their identities.
#include <list>
#include "ascii_string.h"
class INI;
class BfmeFixedStorage0004543D {
    char bytes[28];
public:
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};
template<int N> class BitFlags { unsigned bits[7]; };
extern BitFlags<116> KINDOFMASK_NONE;
void Rva00360CB0Release(int *);
class Rva003623E5Member {
    int index;
public:
    Rva003623E5Member();
    void initFromStorages(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D);

};
class Rva00360D26Member {
    unsigned index;
public:
    Rva00360D26Member();
    ~Rva00360D26Member();
};
struct ProductionModifierEntry {
    AsciiString requiredUpgrade;
    Rva00360D26Member modifierFilter;
    float costMultiplier, timeMultiplier;
    bool heroPurchase, heroRevive;
    ProductionModifierEntry();
    ~ProductionModifierEntry();
};
ProductionModifierEntry::ProductionModifierEntry() {
    reinterpret_cast<Rva003623E5Member *>(&modifierFilter)->initFromStorages(
        reinterpret_cast<const BfmeFixedStorage0004543D &>(KINDOFMASK_NONE),
        reinterpret_cast<const BfmeFixedStorage0004543D &>(KINDOFMASK_NONE));
    costMultiplier = 1.0f;
    timeMultiplier = 1.0f;
    heroPurchase = false;
    heroRevive = false;
}
void Rva0049CBA0_InitObject(INI *, void *, int, int);
struct Rva0049DE6DModuleDataView {
    char prefix[0x3c];
    _STL::list<int> modifiers;
};
void Rva0049DE6DParse(INI *ini, void *instance, void *, const void *) {
    Rva0049DE6DModuleDataView *data = static_cast<Rva0049DE6DModuleDataView *>(instance);
    ProductionModifierEntry *modifier = new ProductionModifierEntry;
    Rva0049CBA0_InitObject(ini, modifier, 0, 0);
    data->modifiers.push_back(reinterpret_cast<const int &>(modifier));
}
