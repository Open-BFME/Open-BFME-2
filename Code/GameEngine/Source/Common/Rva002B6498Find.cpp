// cl: /MD /Oy-
//
// ?rva002B6498@Rva002B6498@@QAEPAVArmorTemplate@@W4NameKeyType@@@Z @0x002B6498 32B
// Hashtable find over the +0x10 ArmorTemplate table via rowed _M_find
// 0x002888D4 (rts::hash plus rts::equal_to) with node+8 value return.
// Evidence: calls 0x002888D4; callers 0x002B6F42 0x002B933F 0x002BDD49
// 0x002E3570 0x003F1BE2 0x003F2287 0x004FBA17 0x0050306A; same map as
// Rva003ED2A3ManagerRemove.cpp; minimal _STL forward declares (no <hash_map>
// to avoid private-inheritance macro breakage and generic emission).
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva002B6498;

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

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
template <class T> struct less
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
	friend class ::Rva002B6498;
	typedef _Hashtable_node<Val> _Node;
private:
	template <class KT> _Node *_M_find(const KT &) const;
};
}

class Rva002B6498;
typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, rts::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashtable;

class Rva002B6498
{
	char m_pad[0x10];
	ArmorHashtable m_ht10;
public:
	ArmorTemplate *rva002B6498(NameKeyType key);
};

ArmorTemplate *Rva002B6498::rva002B6498(NameKeyType key)
{
	NameKeyType tmp = key;
	_STL::_Hashtable_node<_STL::pair<const NameKeyType, ArmorTemplate> > *node = m_ht10._M_find(tmp);
	if (node == 0)
		return 0;
	return (ArmorTemplate *)((char *)node + 8);
}
