// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
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

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}
class INI;
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../../../Include/Common/BitFlagsTemplate.h"
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
