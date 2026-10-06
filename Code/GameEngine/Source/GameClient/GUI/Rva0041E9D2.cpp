// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0041E9D2@Rva0041E9D2@@QAE_NW4NameKeyType@@PBVModuleData@@@Z @0x0041E9D2 53B: Armor find plus ObjectLookup slot plus Rva0041E875 push wrapper. Evidence: callees rowed M_find 0x002888D4 plus findSlot 0x0041F4E5 plus 0x0041E8E6 caller 0x0041EEB3 unlocks 0x0041ED84.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

class Rva0041E9D2;

namespace rts
{
template <class T> struct hash
{
};
template <> struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &key) const;
};
template <class T> struct equal_to
{
};
}

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class P> struct _Select1st
{
};
template <class T> class allocator
{
};
template <class V> struct _Hashtable_node
{
	_Hashtable_node<V> *_M_next;
	V _M_val;
};
template <class Val, class Key, class HF, class ExK, class EqK, class All> class hashtable
{
	friend class ::Rva0041E9D2;
	typedef _Hashtable_node<Val> _Node;
private:
	template <class KT> _Node *_M_find(const KT &) const;
};
}

typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, rts::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashtable;

class Object;

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

class ModuleData;

class Rva0041E875
{
public:
	void rva0041E8E6(const ModuleData *arg);
};

class Rva0041E9D2
{
public:
	bool rva0041E9D2(NameKeyType key, const ModuleData *md);
private:
	char m_pad[12];
};

bool Rva0041E9D2::rva0041E9D2(NameKeyType key, const ModuleData *md)
{
	ArmorHashtable *ht = (ArmorHashtable *)((char *)this + 12);
	ObjectLookupMap *om = (ObjectLookupMap *)((char *)this + 12);
	_STL::_Hashtable_node<_STL::pair<const NameKeyType, ArmorTemplate> > *node = ht->_M_find(key);
	if (node != 0)
	{
		Object **slot = om->findSlot((int *)&key);
		Object *obj = *slot;
		((Rva0041E875 *)obj)->rva0041E8E6(md);
		return true;
	}
	return false;
}
