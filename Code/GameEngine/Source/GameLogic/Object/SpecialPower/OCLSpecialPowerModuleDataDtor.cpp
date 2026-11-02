// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??1OCLSpecialPowerModuleData@@UAE@XZ @0x004C37C0 92B
// OCL power data dtor over the matched ctor 0x004C32BC layout (0x7C base
// plus UpgradeOCL vector at +0x7C plus ints at +0x88/+0x8C plus UpgradeName
// vector at +0x90 plus NearestSecondaryObjectFilter at +0x9C for 0xAC total):
// destroys the filter at +0x9C through rowed 0x360D26 then the string vector
// at +0x90 through rowed 0x2CC70 then frees the POD vector buffer at +0x7C
// through rowed _free 0x30830 then the SpecialPowerModuleData base through rowed
// 0x49334F. Identity: vtable 0x00C5CCB0 slot 0 caller ??_G at 0x004C37A4 plus
// ctor vptr store 0x004C32E3 plus factory 0x00251B8A plus table 0x00C5CDC0.
// Shape follows CashHackSpecialPowerModuleDataDtor (same base plus POD vector
// free plus base) with DominateEnemy filter-plus-base teardown for +0x9C.
// BFME1 OCLSpecialPower.cpp proves member names and order.
#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#include "ascii_string.h"

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

struct OCLUpgradePair
{
	int m_science;
	int m_ocl;
};

class __declspec(novtable) OCLSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~OCLSpecialPowerModuleData();

private:
	_STL::vector<OCLUpgradePair> m_upgradeOCL;
	int m_defaultOCL;
	int m_createLoc;
	_STL::vector<AsciiString> m_upgradeName;
	Rva00360D26Member m_nearestSecondaryObjectFilter;
};

OCLSpecialPowerModuleData::~OCLSpecialPowerModuleData()
{
}
