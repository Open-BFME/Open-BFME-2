// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?remove@Rva003ED2A3Manager@@QAEXABVAsciiString@@PAX@Z @0x003ED2A3 (62B):
// manager remove-by-name (erases hash_map entry when _M_find hits; second
// arg ignored but kept for ret-8 parity with the add twin 0x003ED265).
// Called once from the heap-object unregister helper 0x003ECDB7. Callees
// are the rowed AsciiString nameToKey 0x0009FA65 plus the rowed Armor
// hashtable _M_find 0x002888D4 plus the rowed hash_map erase 0x001E2861.
// Layout mirrors ArmorStore (SubsystemInterface base 0x0C plus map at
// +0x0C) so the +0x0C hashtable calls match. No donor name claimed.
#include <hash_map>
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

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfme04[8];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva003ED2A3Manager : public SubsystemInterface
{
public:
	void remove(const AsciiString &name, void *unused);
	void add(const AsciiString &name, void *obj);
	void init() { }
	void reset() { }
	void update() { }

private:
	ArmorTemplateMap m_map;
};

class Object;

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

void Rva003ED2A3Manager::remove(const AsciiString &name, void *unused)
{
	(void)unused;
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::iterator it = m_map.find(key);
	if (it != m_map.end())
		m_map.erase(it);
}

void Rva003ED2A3Manager::add(const AsciiString &name, void *obj)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::iterator it = m_map.find(key);
	if (it == m_map.end())
	{
		Object **slot = ((ObjectLookupMap *)&m_map)->findSlot((int *)&key);
		*slot = (Object *)obj;
	}
}
