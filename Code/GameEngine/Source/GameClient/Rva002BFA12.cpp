// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002BFA12@Rva002BFA12@@QAEXPAX@Z @0x002BFA12 54B
// Insert-if-absent: hashtable _M_find 0x002888D4 on map at +0x98 with key from arg+0x24,
// on miss ObjectLookupMap::findSlot 0x0041F4E5 on same address then store arg.
// Evidence: retail calls both on ecx+0x98 with same key pointer; caller 0x00539411 passes
// global at 0x00DFEF18 as this and object with key at +0x24; ArmorTemplateMap typedef
// mirrors Rva0035516CArmorFind.cpp so find inlines to rowed _M_find.
#include <hash_map>
#include <vector>
#include <cstddef>

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
	size_t operator()(const T &value) const { return (size_t)value; }	// Zero Hour's rts::hash<NameKeyType>, inline
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Object;

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

class Rva002BFA12
{
public:
	void rva002BFA12(void *obj);

private:
	char m_pad[0x98];
	ArmorTemplateMap m_map;
};

void Rva002BFA12::rva002BFA12(void *obj)
{
	NameKeyType key = *(NameKeyType *)((char *)obj + 0x24);
	if (m_map.find(key) == m_map.end())
	{
		ObjectLookupMap *om = (ObjectLookupMap *)&m_map;
		*om->findSlot((int *)&key) = (Object *)obj;
	}
}

// Target facts: 0x00539411 constructs an object with a 16-byte
// Rva00330757Member subobject at +4, installs vtable VA 0x00C69228, copies
// one pointer and three dwords, then increments and reads the host field at
// +0x88 before registering this object through 0x002BFA12.
// The address-derived class and the meaning of the copied fields remain
// uncertain; the byte gate verifies the constructor body.
struct Rva00539411Primary
{
	int m_vtable;
};

struct Rva00539411Element
{
	float x, y, z, w;
};

class Rva00330757Member
{
public:
	Rva00330757Member();

private:
	_STL::vector<Rva00539411Element> m_items;
	int m_flags;
};

class Rva002D3627Host
{
public:
	__declspec(noinline) int rva002BED69();

private:
	char m_pad[0x88];
	int m_88;
};
extern Rva002D3627Host *g_00DFEF18;

// Target facts: an 11-byte body at 0x002BED69 increments the dword
// field at this+0x88 and returns the updated value. This small provider is
// needed to link the constructor below; its address-derived method name is
// supported by that direct call and the callee bytes.
int Rva002D3627Host::rva002BED69()
{
	int *value = (int *)((char *)this + 0x88);
	return ++*value;
}

class Rva00539411 : public Rva00539411Primary, public Rva00330757Member
{
public:
	Rva00539411(void *arg1, const int *arg2);

private:
	void *m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	char m_28;
};

// The getter pin is direct-call evidence from this body and its callee bytes:
// lea this+0x88; increment the referenced count; return that pointer.
// Address-derived argument labels do not assert class identity.
Rva00539411::Rva00539411(void *arg1, const int *arg2)
	: Rva00330757Member()
{
	const int *data = arg2;
	m_14 = arg1;
	m_vtable = 0x00C69228;
	m_18 = data[0];
	m_1C = data[1];
	m_20 = data[2];
	m_28 = 0;
	m_24 = g_00DFEF18->rva002BED69();
	((Rva002BFA12 *)g_00DFEF18)->rva002BFA12(this);
}
