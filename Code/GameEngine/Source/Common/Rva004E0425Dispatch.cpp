// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// ?rva004E0425@Rva004E0425@@QAEXPAX@Z @0x004E0425 180B.
// Five-pointer dispatch plus name-keyed release. Retail 0x004E0425..0x004E04D9.
// thiscall (void* holder), ret 4. Member evidence from the call sequence:
//   m_0C->rva00596491(holder) true  -> loop(holder,2), any++, done=1
//   m_08->rva00596548(holder) true  -> loop(holder,1), any=1, done=any
//   any != 0                        -> m_10->rva004E02D7(holder)
//   m_00->rva0059614B(holder) || m_04->rva005960E0(holder) -> loop(holder,4), done=1
//   done != 0 -> key = TheNameKeyGenerator->nameToKey(*(AsciiString*)(*(void**)(holder+4)+0x64));
//                node = map14._M_find(key); if (node) --*(int*)(node+8)
// Members m_0C/m_04 are Rva0025BF8C (rowed 0x596491/0x5960E0), m_08 is
// Rva00596548 (rowed 0x596548). m_00 (0x59614B, 139B) and m_10 (0x4E02D7,
// 52B) are unrowed: pinned here as honest address-derived candidates.
// map14 is called through the rowed Armor NameKeyType _M_find spelling at
// 0x2888D4 (body never reads the mapped type; the decl [node+8] release says
// this instantiation holds a refcount, not an ArmorTemplate -- private view,
// identity unresolved). loop is the rowed 0x4DF9E4 (array at +0x2C).

#include "ascii_string.h"

class Rva004E0425;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva0025BF8C;
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
	friend class ::Rva004E0425;
	typedef _Hashtable_node<Val> _Node;
private:
	template <class KT> _Node *_M_find(const KT &) const;
};
}

typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, rts::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashtable;

class Rva0025BF8C
{
public:
	bool rva00596491(void *holder);
	bool rva005960E0(void *holder);
};

class Rva00596548
{
public:
	bool rva00596548(void *holder);
};

class Rva0059614B
{
public:
	bool rva0059614B(void *holder);
};

class Rva004E02D7
{
public:
	void rva004E02D7(void *holder);
};

class Rva004DF9E4
{
public:
	void rva004DF9E4(void *holder, int mask);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004E0425 : private Rva004DF9E4
{
public:
	void rva004E0425(void *holder);

private:
	Rva0059614B *m_00;
	Rva0025BF8C *m_04;
	Rva00596548 *m_08;
	Rva0025BF8C *m_0C;
	Rva004E02D7 *m_10;
	char m_map14[0x18];
};

// ?rva004E0425@Rva004E0425@@QAEXPAX@Z
void Rva004E0425::rva004E0425(void *holder)
{
	bool done = false;
	unsigned char any = 0;
	if (m_0C->rva00596491(holder))
	{
		Rva004DF9E4::rva004DF9E4(holder, 2);
		++any;
		done = true;
	}
	if (m_08->rva00596548(holder))
	{
		Rva004DF9E4::rva004DF9E4(holder, 1);
		any = 1;
		done = (any != 0);
	}
	if (any != 0)
		m_10->rva004E02D7(holder);
	if (m_00->rva0059614B(holder) || m_04->rva005960E0(holder))
	{
		Rva004DF9E4::rva004DF9E4(holder, 4);
		done = true;
	}
	if (done)
	{
		void *inner = *(void **)((char *)holder + 4);
		NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)((char *)inner + 0x64));
		_STL::_Hashtable_node<_STL::pair<const NameKeyType, ArmorTemplate> > *node =
			((ArmorHashtable *)m_map14)->_M_find(key);
		if (node != 0)
			--*(int *)((char *)node + 8);
	}
}
