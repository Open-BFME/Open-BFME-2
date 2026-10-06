// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_bkt_num_key@?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@2@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@ABEIABW4NameKeyType@@@Z @0x00053EA8 22B
// Armor hash_map 1-arg bucket helper. Evidence: pin from REL32 at placed
// hashtable erase 0x00054C44 in ArmorHashMapErase.cpp; callers at 0x00054BCF
// 0x00054C56 0x00054CA0 0x00054DD3; callee is rowed Mod at 0x00051B89;
// bucket vector at +4/+8 gives size via finish-minus-start shr 2.
unsigned __stdcall Rva00051B89Mod(void *p, unsigned div);

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

namespace rts
{

template <class T> struct hash
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

template <class T> struct _Select1st
{
};

template <class T> struct equal_to
{
};

template <class T> class allocator
{
};

template <class Val, class Key, class HF, class ExK, class EqK, class All>
class hashtable
{
private:
	typedef unsigned int size_type;
	size_type _M_bkt_num_key(const Key &key) const;
private:
	char m_pad[4];
	void **_M_start;
	void **_M_finish;
	void **_M_end;
	unsigned int _M_num_elements;
};

template <class Val, class Key, class HF, class ExK, class EqK, class All>
typename hashtable<Val, Key, HF, ExK, EqK, All>::size_type hashtable<Val, Key, HF, ExK, EqK, All>::_M_bkt_num_key(const Key &key) const
{
	unsigned int n = (unsigned int)(_M_finish - _M_start);
	return Rva00051B89Mod((void *)&key, n);
}

}

typedef _STL::pair<const NameKeyType, ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<ArmorPair>, _STL::equal_to<NameKeyType>, _STL::allocator<ArmorPair> > ArmorTable;

template _STL::hashtable<ArmorPair, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<ArmorPair>, _STL::equal_to<NameKeyType>, _STL::allocator<ArmorPair> >::size_type _STL::hashtable<ArmorPair, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<ArmorPair>, _STL::equal_to<NameKeyType>, _STL::allocator<ArmorPair> >::_M_bkt_num_key(const NameKeyType &) const;
