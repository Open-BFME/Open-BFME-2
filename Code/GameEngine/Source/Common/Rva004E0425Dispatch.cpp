// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?UnRegister@AIStatCollector@@QAEXPAX@Z @0x004E0425 180B.
// Five-pointer dispatch plus name-keyed release. Retail 0x004E0425..0x004E04D9.
// thiscall (void* holder), ret 4. Member evidence from the call sequence:
//   m_0C->rva00596491(holder) true  -> loop(holder,2), any++, done=1
//   m_08->UnRegister(holder) true  -> loop(holder,1), any=1, done=any
//   any != 0                        -> m_10->rva004E02D7(holder)
//   m_00->rva0059614B(holder) || m_04->rva005960E0(holder) -> loop(holder,4), done=1
//   done != 0 -> key = TheNameKeyGenerator->nameToKey(*(AsciiString*)(*(void**)(holder+4)+0x64));
//                node = map14._M_find(key); if (node) --*(int*)(node+8)
// Members m_0C/m_04 are Rva0025BF8C (rowed 0x596491/0x5960E0), m_08 is
// AIStructureStats (rowed 0x596548). m_00 (0x59614B, 139B) and m_10 (0x4E02D7,
// 52B) are unrowed: pinned here as honest address-derived candidates.
// map14 is called through the rowed Armor NameKeyType _M_find spelling at
// 0x2888D4 (body never reads the mapped type; the decl [node+8] release says
// this instantiation holds a refcount, not an ArmorTemplate -- private view,
// identity unresolved). loop is the rowed 0x4DF9E4 (array at +0x2C).

#include "ascii_string.h"

class AIStatCollector;
class Object;

class Rva0025C061
{
public:
	bool rva00596472(void *holder);
	bool rva005960C1(void *holder);
};

class AIUnitStats
{
public:
	bool Register(void *holder);
};

class Rva004E00BAOwner
{
public:
	void rva004E00BA(Object *holder);
};

class Rva004DF9B9
{
public:
	void rva004DF9B9(void *holder, int mask);
};

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

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
	friend class ::AIStatCollector;
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

class AIStructureStats
{
public:
	bool Register(Object *holder);
	bool UnRegister(void *holder);
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

class AIStatCollector : private Rva004DF9E4
{
public:
	void Register(Object *holder);
	bool rva004DFB7E(void *holder);
	void UnRegister(void *holder);

private:
	Rva0059614B *m_00;
	Rva0025BF8C *m_04;
	AIStructureStats *m_08;
	Rva0025BF8C *m_0C;
	Rva004E02D7 *m_10;
	char m_map14[0x18];
};

// Native 004E01E3..004E02B8 (213 bytes); WB names the callgraph twin
// AIStatCollector::Register. Receiver slots and the template name at
// holder->+4 then +64 agree with the rowed UnRegister below. The +14 map
// stores counts: its rowed find-or-insert body is reached via the existing
// ObjectLookupMap spelling, but its returned four-byte slot holds an int.
void AIStatCollector::Register(Object *holder)
{
	bool done = false;
	unsigned char any = 0;
	if (((Rva0025C061 *)m_0C)->rva00596472(holder))
	{
		((Rva004DF9B9 *)this)->rva004DF9B9(holder, 2);
		++any;
		done = true;
	}
	if (m_08->Register(holder))
	{
		((Rva004DF9B9 *)this)->rva004DF9B9(holder, 1);
		any = 1;
		done = (any != 0);
	}
	if (any != 0 && !rva004DFB7E(holder))
		((Rva004E00BAOwner *)m_10)->rva004E00BA(holder);
	if (((AIUnitStats *)m_00)->Register(holder) || ((Rva0025C061 *)m_04)->rva005960C1(holder))
	{
		((Rva004DF9B9 *)this)->rva004DF9B9(holder, 4);
		done = true;
	}
	if (done)
	{
		void *inner = *(void **)((char *)holder + 4);
		NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)((char *)inner + 0x64));
		_STL::_Hashtable_node<_STL::pair<const NameKeyType, ArmorTemplate> > *node =
			((ArmorHashtable *)m_map14)->_M_find(key);
		if (node != 0)
			++*(int *)((char *)node + 8);
		else
			*(int *)((ObjectLookupMap *)m_map14)->findSlot((int *)&key) = 1;
	}
}

// ?UnRegister@AIStatCollector@@QAEXPAX@Z
void AIStatCollector::UnRegister(void *holder)
{
	bool done = false;
	unsigned char any = 0;
	if (m_0C->rva00596491(holder))
	{
		Rva004DF9E4::rva004DF9E4(holder, 2);
		++any;
		done = true;
	}
	if (m_08->UnRegister(holder))
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
