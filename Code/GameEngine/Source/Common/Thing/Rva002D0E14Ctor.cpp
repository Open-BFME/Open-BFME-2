// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// ??0Rva002D0E14@@QAE@XZ @0x002D0E14 85B: SubsystemInterface base via 0x001B4E63 vtable 0x00C0233C member Rva002D0C71 at +0x14 plus +0xC zero plus +0x10 one plus reserve 0x3000 via pinned rva00212858. Evidence: caller 0x0004CA01 revtables to 0x007C4858; calls baseConstruct and hashtable ctor.
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{
template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};
}

namespace Rva002D0C71Twin
{
template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
};
}

#include "../../../Include/GameLogic/Armor.h"

typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, Rva002D0C71Twin::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHt002D0C71;

class Rva002D0C71
{
public:
	Rva002D0C71();
private:
	ArmorHt002D0C71 m_ht;
};

#include "../../../Include/GameLogic/Rva000427195.h"

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva002D0E14 : public SubsystemInterface
{
public:
	Rva002D0E14();
	void init() { }
	void reset() { }
	void update() { }
private:
	int m_unk0C;
	unsigned short m_unk10;
	char m_pad12[2];
	Rva002D0C71 m_thing;
};

// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> hashtable<_STL::pair<NameKeyType const,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<_STL::pair<NameKeyType const,ArmorTemplate> >,Rva002D0C71Twin::equal_to<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,ArmorTemplate> > >::~hashtable(); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::~vector(); }
namespace _STL { template <> void hashtable<_STL::pair<NameKeyType const,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<_STL::pair<NameKeyType const,ArmorTemplate> >,Rva002D0C71Twin::equal_to<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,ArmorTemplate> > >::clear(); }
// bfme link decl-only end
Rva002D0E14::Rva002D0E14()
{
	m_unk0C = 0;
	m_unk10 = 1;
	((Rva000427195 *)&m_thing)->rva00212858(0x3000);
}
