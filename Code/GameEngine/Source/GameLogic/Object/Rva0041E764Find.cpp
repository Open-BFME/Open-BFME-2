// cl: /MD
// ?rva0041E764@Rva0041E764@@QAEPAVArmorTemplate@@W4NameKeyType@@@Z @0x0041E764 27B: Hashtable find over the +0xC ArmorTemplate pointer table via ICF twin of rowed _M_find plus node second load. Evidence: calls 0x002888D4 caller 0x005AE16E unlocks 0x005AE0AD.
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva0041E764;

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
	friend class ::Rva0041E764;
	typedef _Hashtable_node<Val> _Node;
private:
	template <class KT> _Node *_M_find(const KT &) const;
};
}

class Rva0041E764;
typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate *>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate *> >, rts::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate *> > > ArmorHashtable;

class Rva0041E764
{
	char m_pad[0x0C];
	ArmorHashtable m_ht0C;
public:
	ArmorTemplate *rva0041E764(NameKeyType key);
};

ArmorTemplate *Rva0041E764::rva0041E764(NameKeyType key)
{
	_STL::_Hashtable_node<_STL::pair<const NameKeyType, ArmorTemplate *> > *node = m_ht0C._M_find(key);
	if (node != 0)
		return node->_M_val.second;
	return 0;
}
