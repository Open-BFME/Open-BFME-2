// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?SplitUpgrades@@YAHPAXABVAsciiString@@@Z retail 0x0028900A 199 bytes v6.
// Parses upgrade list AsciiString via alloca+strtok, clears vector via rowed
// void* erase, finds each token via TheUpgradeCenter, pushes hits via rowed
// ModuleData push_back, returns count. Evidence: callers 0x0028A551 0x0028A5BC;
// callees rowed erase 0x0031BD55 push_back 0x004DFCB0 findUpgrade 0x0026F26D;
// neighbours CrateCreationEntryList.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>
#include <malloc.h>
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVModuleData@@@_STL@@QBEXPAPBVModuleData@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void allocator<const ModuleData *>::deallocate(const ModuleData **, size_t) const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }
// The retail push_back body is rowed at 0x004DFCB0.
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &); }

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

class ModuleData {};
class UpgradeTemplate : public ModuleData {};
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delim);

int SplitUpgrades(void *vecPtr, const AsciiString &list)
{
	typedef _STL::vector<void *, _STL::allocator<void *> > VoidVec;
	typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ModVec;
	char *buf = (char *)alloca(list.getLength() + 1);
	((VoidVec *)vecPtr)->erase(((VoidVec *)vecPtr)->begin(), ((VoidVec *)vecPtr)->end());
	_mbscpy(buf, list.str());
	// Retail delimiter bytes at RVA 0x007BE7A4, including the trailing NUL.
	char *tok = strtok(buf, " \n\r\t");
	while (tok != 0)
	{
		const ModuleData *ut;
		{
			AsciiString tmp(tok);
			ut = TheUpgradeCenter->findUpgrade(tmp);
		}
		if (ut != 0)
			((ModVec *)vecPtr)->push_back(ut);
		tok = strtok(0, " \n\r\t");
	}
	return (int)((ModVec *)vecPtr)->size();
}
