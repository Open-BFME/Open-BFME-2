// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport
//
// ?UnRegister@AIStatCollector@@QAEXPAX@Z @0x004E0425 180B.
// Five-pointer dispatch plus name-keyed release. Retail 0x004E0425..0x004E04D9.
// thiscall (void* holder), ret 4. Member evidence from the call sequence:
//   resources(+0C)->UnRegister(holder) true  -> loop(holder,2), any++, done=1
//   structures(+08)->UnRegister(holder) true  -> loop(holder,1), any=1, done=any
//   any != 0                        -> positions(+10)->rva004E02D7(holder)
//   units(+00)->UnRegister(holder) || otherUnits(+04)->rva005960E0(holder) -> loop(holder,4), done=1
//   done != 0 -> key = TheNameKeyGenerator->nameToKey(*(AsciiString*)(*(void**)(holder+4)+0x64));
//                node = counts(+14)._M_find(key); if (node) --*(int*)(node+8)
// Members +0C/+04 are called as AIStatBase (rowed 0x596491/0x5960E0), +08 as
// AIStructureStats (rowed 0x596548). +00 (0x59614B, 139B) and +10 (0x4E02D7,
// 52B) are unrowed: pinned here as honest address-derived candidates.
// counts is called through the rowed Armor NameKeyType _M_find spelling at
// 0x2888D4 (body never reads the mapped type; the decl [node+8] release says
// this instantiation holds a refcount, not an ArmorTemplate -- private view,
// identity unresolved). loop is the rowed 0x4DF9E4 (array at +0x2C).

#include <hash_map>
#include <vector>
#include "ascii_string.h"

class Player;

class Object;

class ModuleData;

class Rva005961D6;

class Rva00596069;

class Rva005965A5;

class AIEconomyStats;

class Rva00283081;

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
	bool UnRegister(void *holder);
};

// Rowed under their own address classes.
class CreateAHeroData;

class Rva004E02D7Owner
{
public:
	void rva004E02D7(CreateAHeroData *value);
	void rva004E00D9();

private:
	char unknown00[4];
	_STL::vector<void *> records;
	_STL::vector<void *> holders;
};

class Rva004E00BAOwner
{
public:
	void addObject(Object *object);

private:
	unsigned int m_opaquePrefix;
	_STL::vector<Object *> m_objects;
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

class AIStatBase;
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

class AIStatCollector;

typedef _STL::pair<const NameKeyType, ArmorTemplate> ArmorHashtablePair;

// This unit reaches one member of the Armor hashtable: the rowed _M_find 0x002888D4, out of line.
namespace _STL
{
template <> class hashtable<ArmorHashtablePair, NameKeyType, rts::hash<NameKeyType>, _Select1st<ArmorHashtablePair>, rts::equal_to<NameKeyType>, allocator<ArmorHashtablePair> >
{
	friend class ::AIStatCollector;
	typedef _Hashtable_node<ArmorHashtablePair> _Node;
private:
	template <class KT> _Node *_M_find(const KT &) const;
};
}

typedef _STL::hashtable<ArmorHashtablePair, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<ArmorHashtablePair>, rts::equal_to<NameKeyType>, _STL::allocator<ArmorHashtablePair> > ArmorHashtable;

class AIStatBase
{
public:
	bool UnRegister(void *holder);
	bool rva005960E0(void *holder);
};

class AIStructureStats
{
public:
	bool Register(Object *holder);
	bool UnRegister(void *holder);
};

class FilterElem;

class Rva004DF9E4
{
public:
	void rva004DF9E4(void *a, int mask);
private:
	char m_pad[0x2c];
	FilterElem **m_begin;
	FilterElem **m_end;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// Constructor 004E030B establishes a 20-byte map, then Player* at
// +28 and the 12-byte listener header at +2C. These methods retain
// their existing lookup bindings and access only the map at +14.
class AIStatCollector {
public: AIStatCollector(Player *);
 void Register(Object *,int);
 void Register(Object *);
 void UnRegister(void *);
 void addInfoReceiver(const ModuleData *);
 bool rva004DFB7E(Object *);
 void rva004DF9B9(void *,int);
private:
 Rva005961D6 *units;
 Rva00596069 *otherUnits;
 Rva005965A5 *structures;
 AIEconomyStats *resources;
 Rva00283081 *positions;
 _STL::hash_map<int,int> counts;
 Player *player;
 _STL::vector<const ModuleData *> listeners;
};

typedef char AIStatCollectorNativeSize[(sizeof(AIStatCollector)==0x38)?1:-1];

// Native 004E01E3..004E02B8 (213 bytes); WB names the callgraph twin
// AIStatCollector::Register. Receiver slots and the template name at
// holder->+4 then +64 agree with the rowed UnRegister below. The +14 map
// stores counts: its rowed find-or-insert body is reached via the existing
// ObjectLookupMap spelling, but its returned four-byte slot holds an int.
void AIStatCollector::Register(Object *holder)
{
	bool done = false;
	unsigned char any = 0;
	if (((Rva0025C061 *)resources)->rva00596472(holder))
	{
		rva004DF9B9(holder, 2);
		++any;
		done = true;
	}
	if (((AIStructureStats *)structures)->Register(holder))
	{
		rva004DF9B9(holder, 1);
		any = 1;
		done = (any != 0);
	}
	if (any != 0 && !rva004DFB7E((Object *)holder))
		((Rva004E00BAOwner *)positions)->addObject(holder);
	if (((AIUnitStats *)units)->Register(holder) || ((Rva0025C061 *)otherUnits)->rva005960C1(holder))
	{
		rva004DF9B9(holder, 4);
		done = true;
	}
	if (done)
	{
		void *inner = *(void **)((char *)holder + 4);
		NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)((char *)inner + 0x64));
		_STL::_Hashtable_node<ArmorHashtablePair> *node =
			((ArmorHashtable *)&counts)->_M_find(key);
		if (node != 0)
			++*(int *)((char *)node + 8);
		else
			*(int *)((ObjectLookupMap *)&counts)->findSlot((int *)&key) = 1;
	}
}

// ?UnRegister@AIStatCollector@@QAEXPAX@Z
void AIStatCollector::UnRegister(void *holder)
{
	bool done = false;
	unsigned char any = 0;
	if (((AIStatBase *)resources)->UnRegister(holder))
	{
		((Rva004DF9E4 *)this)->rva004DF9E4(holder, 2);
		++any;
		done = true;
	}
	if (((AIStructureStats *)structures)->UnRegister(holder))
	{
		((Rva004DF9E4 *)this)->rva004DF9E4(holder, 1);
		any = 1;
		done = (any != 0);
	}
	if (any != 0)
		((Rva004E02D7Owner *)positions)->rva004E02D7((CreateAHeroData *)holder);
	if (((AIUnitStats *)units)->UnRegister(holder) || ((AIStatBase *)otherUnits)->rva005960E0(holder))
	{
		((Rva004DF9E4 *)this)->rva004DF9E4(holder, 4);
		done = true;
	}
	if (done)
	{
		void *inner = *(void **)((char *)holder + 4);
		NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)((char *)inner + 0x64));
		_STL::_Hashtable_node<ArmorHashtablePair> *node =
			((ArmorHashtable *)&counts)->_M_find(key);
		if (node != 0)
			--*(int *)((char *)node + 8);
	}
}
