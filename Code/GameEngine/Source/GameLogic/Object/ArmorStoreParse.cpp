// cl: /Ireference/shims/bfmealloc /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// platformsdk
// stlport
// WB ABCAB0 names ArmorStore::parseArmorDefinition; native1D9484..1D9611
// supplies override/new/template layout and the exact four-entry field table.
// ZH and BFME1 ba7ddda7 Armor.cpp support INI/Armor identity; BF1 donor place0.
// The inline volatile load-type getter restores the native single load/test,
// complete 397-byte extent and 126-instruction stream. Remaining homes differ:
// key -20 versus -10; conversion bitmap -14 versus -18; heap temps -18/-10
// versus -14/-1C. Actual pointer-container operator[]63 and push_back49 still
// need complete byte-and-relocation fold proof. No trial bindings are pins.
// claude-opus-5-5 2026-10-20: rts::hash defined inline and no iterator padding or volatile
// getter; only the operator[] call (fold pin to 0x0041F4E5) is unresolved. See
// reverse/attempt_support/0x001d9484_20261020_visible_hash.md.
// ArmorStore::parseArmorDefinition (retail 0x001D9484, 397 bytes), right after the store's
// slot-5 reload 0x001D93CE; WB ABCAB0 names it. The map at +0x0C and the pending vector at
// +0x2C are the containers ArmorStoreReload.cpp drains.

#include <windows.h>
#include <hash_map>
#include <vector>
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ??R?$less@I@_STL@@QBE_NABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<unsigned int>::operator()(unsigned int const &,unsigned int const &) const; }
// Suppress this TU's non-retail copy of ?get_allocator@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBE?AV?$allocator@PAX@2@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> allocator<void *> vector<void *,allocator<void *> >::get_allocator() const; }
// Suppress this TU's non-retail copy of ?begin@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * vector<void *,allocator<void *> >::begin(); }
// Suppress this TU's non-retail copy of ?begin@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEPBQAXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * const * vector<void *,allocator<void *> >::begin() const; }
// The const subscript is emitted through that suppressed begin(), so its copy
// carries a call retail's does not (the 29-copy majority reads _M_start).
// dllimport keeps this TU from emitting a copy; forceinline keeps the shape.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const & vector<void *,allocator<void *> >::operator[](unsigned int __n) const { return _M_start[__n]; } }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEAAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * & vector<void *,allocator<void *> >::operator[](unsigned int); }
// Suppress this TU's non-retail copy of ?size@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEIXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned int vector<void *,allocator<void *> >::size() const; }

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{
// Inline: retail's _M_find 0x002888D4 reads the key straight into the bucket divide.
template <class T> struct hash
{
	size_t operator()(const T &value) const { return (size_t)value; }
};
}

class INI;

#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleData;

#include "../../../Include/GameLogic/Armor.h"

// Retail inlines the empty destructor here (the discarded local's name string
// is released directly); the out-of-line copy lives in ArmorTemplateParse.cpp.
inline ArmorTemplate::~ArmorTemplate()
{
}

typedef _STL::hash_map<NameKeyType, ArmorTemplate *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > ArmorTemplateMap;

class ArmorStore
{
public:
	static void parseArmorDefinition(INI *ini);

private:
	char m_pad00[0x0C];
	ArmorTemplateMap m_armorTemplates; // +0x0C
	_STL::vector<ArmorTemplate *> m_retired; // +0x20
	_STL::vector<ArmorTemplate *> m_pending; // +0x2C
};
extern ArmorStore *TheArmorStore;

// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// Load type 5 replaces a known armor with a new pending template; any other
// repeat parses into a discarded local.
/*static*/ void ArmorStore::parseArmorDefinition(INI *ini)
{
	static const FieldParse myFieldParse[] =
	{
		{ "DamageScalar", ArmorTemplate::parseDamageScalar, NULL, 0 },
		{ "FlankedPenalty", INI::parsePercentToReal, NULL, 0 },
		{ "Armor", ArmorTemplate::parseArmorCoefficients, NULL, 0 },
		{ NULL, NULL, NULL, 0 }
	};

	const char *armorName = ini->getNextToken(NULL);
	NameKeyType key = TheNameKeyGenerator->nameToKey(armorName);
	ArmorTemplate *armorTmpl;
	ArmorTemplateMap::const_iterator it = TheArmorStore->m_armorTemplates.find(key);
	if (it != TheArmorStore->m_armorTemplates.end())
	{
		armorTmpl = it->second;
		if (ini->getLoadType() == 5)
		{
			armorTmpl->m_field74 = 1;
			armorTmpl = new ArmorTemplate(armorName);
			armorTmpl->m_field74 = 0;
			// Pointer-vector push_back through the rowed four-byte provider 0x004DFCB0.
			reinterpret_cast<_STL::vector<const ModuleData *> &>(TheArmorStore->m_pending).push_back(reinterpret_cast<const ModuleData * const &>(armorTmpl));
		}
		else
		{
			ArmorTemplate temp(armorName);
			ini->initFromINI(&temp, myFieldParse);
			return;
		}
	}
	else
	{
		armorTmpl = new ArmorTemplate(armorName);
		TheArmorStore->m_armorTemplates[key] = armorTmpl;
	}
	ini->initFromINI(armorTmpl, myFieldParse);
}
