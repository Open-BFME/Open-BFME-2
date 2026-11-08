// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0WeaponStore@@QAE@XZ @0x002CC20E 47B evidence: baseConstruct 0x001B4E63 plus vtable 0x00C02114 plus 2x Vector_base 0x00211E58 at +0x0C +0x18 plus caller 0x0022EB76; same pattern as Rva00426402Ctor with 3 vectors.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"


// Retail table at VA 0x00C02114 is Rva002CCD56's compiler table (Rva002CCD56Dtor.cpp
// emits it; the data ledger binds the name there).
extern "C" const void *const __identifier("??_7Rva002CCD56@@6B@")[];

class __declspec(novtable) Rva002CC20EBase
{
public:
    Rva002CC20EBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
    virtual void unused();
    char m_flag;
    int m_value;
};


class __declspec(novtable) WeaponStore : public Rva002CC20EBase
{
public:
    WeaponStore();
private:
    _STL::vector<BfmeE16> m_vec0C;
    _STL::vector<BfmeE16> m_vec18;
};

WeaponStore::WeaponStore()
    : m_vec0C((*(const void *const **)this = __identifier("??_7Rva002CCD56@@6B@"), _STL::allocator<BfmeE16>()))
    , m_vec18()
{
}
