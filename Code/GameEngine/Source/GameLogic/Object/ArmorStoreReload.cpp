// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// The Armor store's (vftable 0x00BD9CB0; deleting dtor 0x001D93B2) reload
// pair: slot 4, the "RIF: Armor reloaded" notice 0x001D8FAD (moved from
// ReloadIniFileNotices.cpp, which keeps the other stores' notices), and
// slot 5, 0x001D93CE, which applies the pending armor templates. Both read
// and write the file-static latch byte at VA 0x00DFDBC8, so they share this
// unit; the shared notice shape (slot 2 0x001B5384, TheInGameUI slot 16
// varargs message) is the one ReloadIniFileNotices.cpp documents.

#include <hash_map>
#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

class RifStore
{
public:
	virtual void v00(); virtual void v01();
	virtual bool rva001B5384Slot2();
};

// g_Va00DFDBC8: VA 0x00DFDBC8 (.bss); retail initial byte 00. File-static:
// the Armor store's slot 5 (0x001D93CE) clears it only after loading the
// pending vector's bounds, a store cl could not sink past those loads if
// the byte could alias them.
static bool g_Va00DFDBC8;

// Armor store containers (WB ABCAB0 ArmorStore::parseArmorDefinition fills
// the same +0x0C map and +0x2C vector). Their out-of-line STLport members
// were built in another unit: this unit's own copies of hashtable::erase and
// vector::_M_insert_overflow compile to 155 and 132 bytes against retail's
// 138 and 140, so those calls bind through the spellings the ledger already
// gives the shared bodies (declared, never instantiated here): the lookup-map
// slot view 0x0041F4E5 / 0x0054883B, vector<const ModuleData *>::push_back
// 0x004DFCB0 and vector<void *>::erase 0x0031BD55. find's _M_find 0x002888D4
// has its own pinned ArmorTemplate spelling.
enum NameKeyType { NAMEKEY_INVALID = 0, NAMEKEY_MAX = 1 << 23, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
namespace rts { template <class T> struct hash { size_t operator()(const T &value) const { return (size_t)value; } }; }
// rts::hash<NameKeyType>::operator() otherwise emits a per-TU COMDAT that loses to
// another unit's copy; this explicit dllimport+forceinline specialization keeps it inline.
namespace rts { template <> __declspec(dllimport) __forceinline size_t hash<NameKeyType>::operator()(const NameKeyType &value) const { return (size_t)value; } }
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class ModuleData;
class Object;
#include "../../../Include/Common/ObjectLookupMap.h"
namespace _STL {
template <> void vector<const ModuleData *>::push_back(const ModuleData * const &);
template <> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
// vector<void*> begin/end/size/clear otherwise emit per-TU COMDATs that lose in link
// order; these explicit dllimport+forceinline specializations keep them inline.
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void *const *vector<void *>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline unsigned int vector<void *>::size() const { return (unsigned int)(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void vector<void *>::clear() { erase(begin(), end()); }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}

#include "../../../Include/GameLogic/Armor.h"
typedef _STL::hash_map<NameKeyType, ArmorTemplate *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva001D9670Store : public RifStore
{
public:
	virtual void vslot03();
	virtual bool vslot04(int reason);
	virtual bool vslot05();
private:
	int m_04;
	int m_08;
	ArmorTemplateMap m_armorTemplates;		// +0x0C
	_STL::vector<ArmorTemplate *> m_retired;	// +0x20
	_STL::vector<ArmorTemplate *> m_pending;	// +0x2C
};

bool Rva001D9670Store::vslot04(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: Armor reloaded"));
		g_Va00DFDBC8 = true;
	}
	return g_Va00DFDBC8;
}

// Armor slot 5 (vftable 0x00BD9CB0), retail 0x001D93CE..0x001D9484 RET0;
// WB ABC710 is its debug twin. When the reload byte is set it is cleared and
// every template of the pending vector at +0x2C is keyed by its name (+0x78);
// a template already under that key moves to the vector at +0x20 and leaves
// the NameKeyType map at +0x0C, the pending one takes the key, the pending
// vector is emptied, and the result is whether any template was applied.
bool Rva001D9670Store::vslot05()
{
	if (g_Va00DFDBC8) {
		g_Va00DFDBC8 = false;
		int i;
		for (i = 0; i < m_pending.size(); ++i) {
			NameKeyType key = TheNameKeyGenerator->nameToKey(m_pending[i]->m_name);
			ArmorTemplateMap::const_iterator it = m_armorTemplates.find(key);
			if (it != m_armorTemplates.end()) {
				reinterpret_cast<_STL::vector<const ModuleData *> &>(m_retired).push_back(reinterpret_cast<const ModuleData * const &>((*it).second));
				reinterpret_cast<ObjectLookupMap &>(m_armorTemplates).eraseSlot((int *)&key);
			}
			*reinterpret_cast<ArmorTemplate **>(reinterpret_cast<ObjectLookupMap &>(m_armorTemplates).findSlot((int *)&key)) = m_pending[i];
		}
		reinterpret_cast<_STL::vector<void *> &>(m_pending).clear();
		return i > 0;
	}
	return false;
}

