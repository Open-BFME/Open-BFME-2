// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00355155@Rva00355B61@@QBEPBVArmorTemplate@@W4NameKeyType@@@Z @0x00355155 23B: finds ArmorTemplate in map at +0x10 via rowed hashtable _M_find 0x002888D4.
// Evidence: retail lea eax [esp+4] push eax add ecx 0x10 call _M_find then mov eax [eax+8]; same shape as rowed 0x0035516C find at +0x24; unblocks 9 callers.

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
	void *m_ptr;
	char m_pad4[4];
	int m_check;
	char m_padC[0x70];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

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

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
};

class Rva00355B61 : public SubsystemInterface, public SnapshotBase
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
private:
	ArmorTemplateMap m_map1;
	ArmorTemplateMap m_map2;
};

const ArmorTemplate *Rva00355B61::rva00355155(NameKeyType key) const
{
	ArmorTemplateMap::const_iterator it = m_map1.find(key);
	if (it == m_map1.end())
		return 0;
	return (const ArmorTemplate *)it->second.m_ptr;
}
