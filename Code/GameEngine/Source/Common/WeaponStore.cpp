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

extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_GRva002CCD56@@UAEPAXI@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")();
void __identifier("?postProcessLoad@WeaponStore@@UAEXXZ")();
void __identifier("?reset@WeaponStore@@UAEXXZ")();
void __identifier("?rva002C941C@Rva002C941C@@QAEXH@Z")();
void __identifier("?rva002CAE34@Rva002CCD56@@QAE_NH@Z")();
void __identifier("?rva002CAE6C@Rva002CCD56@@QAE_NXZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
}

// Retail table at VA 0x00C02114, each slot the ledger row at the native address.
extern "C" const void *const g_weaponStoreTable[14] = {
	(const void *)&__identifier("??_GRva002CCD56@@UAEPAXI@Z"), // slot 0, RVA 0x002CD5E0
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&__identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ"), // slot 2, RVA 0x001B5384
	(const void *)&__identifier("?postProcessLoad@WeaponStore@@UAEXXZ"), // slot 3, RVA 0x002CADFA
	(const void *)&__identifier("?rva002CAE34@Rva002CCD56@@QAE_NH@Z"), // slot 4, RVA 0x002CAE34
	(const void *)&__identifier("?rva002CAE6C@Rva002CCD56@@QAE_NXZ"), // slot 5, RVA 0x002CAE6C
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 6, RVA 0x000D43D0
	(const void *)&__identifier("?rva002C941C@Rva002C941C@@QAEXH@Z"), // slot 7, RVA 0x002C941C
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 8, RVA 0x000B3FD0
	(const void *)&__identifier("?reset@WeaponStore@@UAEXXZ"), // slot 9, RVA 0x002C9A34
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 10, RVA 0x000B3FD0
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 11, RVA 0x005CB9FF
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 12, RVA 0x000B3FD0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 13, RVA 0x0047A69C
};

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
    : m_vec0C((*(const void *const **)this = g_weaponStoreTable, _STL::allocator<BfmeE16>()))
    , m_vec18()
{
}
