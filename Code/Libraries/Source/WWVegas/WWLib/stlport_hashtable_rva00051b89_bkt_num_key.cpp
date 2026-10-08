// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// hashtable<Rva00051B89Keyed*>::_M_bkt_num_key(const key&) const @0x00053EA8 22B
// 1-arg bucket helper. Target evidence: REL32 from the placed hashtable
// erase 0x00054C44 (stlport_hashtable_rva00051b89_erase.cpp); callers at
// 0x00054BCF 0x00054C56 0x00054CA0 0x00054DD3; callee is the rowed 2-arg
// helper at 0x00051B89 (ecx left as this, &key and bucket count pushed);
// bucket vector at +4/+8 gives size via finish-minus-start shr 2. The row
// was formerly named for hash_map<NameKeyType, ArmorTemplate>; retail's
// Armor table hashes inline (0x002888D4, 0x000557BB), so the key here is a
// different, pointer type. Type names are placeholders.
unsigned __stdcall Rva00051B89Mod(void *p, unsigned div);

struct Rva00051B89Keyed;

struct Rva00051B89Hash
{
};

namespace _STL
{

template <class T> struct _Identity
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

typedef _STL::hashtable<Rva00051B89Keyed *, Rva00051B89Keyed *, Rva00051B89Hash, _STL::_Identity<Rva00051B89Keyed *>, _STL::equal_to<Rva00051B89Keyed *>, _STL::allocator<Rva00051B89Keyed *> > Rva00051B89Table;

template Rva00051B89Table::size_type Rva00051B89Table::_M_bkt_num_key(Rva00051B89Keyed *const &) const;
