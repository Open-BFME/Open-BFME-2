// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva0041F474@ArmorStore@@QBEPBVArmorTemplate@@ABVAsciiString@@@Z @0x0041F474 51B.
// Armor map find by name via NameKey plus hash_map find (inlines to rowed
// _M_find 0x002888D4) returning second.m_ptr via mov [eax+8]. Evidence:
// callers 0x002090F7 0x002A9519 0x003C5EA3 0x004E9840; map at +0x0C; mirrors
// Rva000AA867 at 0x000AA867 (23B key-only) plus NameKey step.
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
class ArmorStore : public SubsystemInterface
{
public:
	const ArmorTemplate *rva0041F474(const AsciiString &name) const;
	void init() { }
	void reset() { }
	void update() { }
private:
	ArmorTemplateMap m_map;
};
const ArmorTemplate *ArmorStore::rva0041F474(const AsciiString &name) const
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::const_iterator it = m_map.find(key);
	return it != m_map.end() ? (const ArmorTemplate *)it->second.m_ptr : 0;
}
