// ?keyToName@NameKeyGenerator@@QAEABVAsciiString@@W4NameKeyType@@@Z
// partial score=0.85 date=2026-10-04
// cl: /Ireference/shims/bfme_namekey /Ireference/shims/bfme2_ascii /MD /O1 /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /EHs-
// stlport
#include <hash_map>
#include <cstddef>
#include "ascii_string.h"

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
	size_t operator()(const T &value) const;
};
template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
};
}

// The reverse key->Bucket index shares its code with the ArmorTemplate map
// instantiation (retail calls that rowed _M_find 0x002888D4); the bucket
// pointer is the first word of the mapped value.
class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};
typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > KeyToBucketMap;

#include <windows.h>
#include "Common/CriticalSection.h"

class Bucket
{
public:
	void *m_vtbl;
	Bucket *m_nextInSocket;
	NameKeyType m_key;
	AsciiString m_nameString; // +0x0C
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
private:
	char m_pad[0x2BF4C];
	KeyToBucketMap &keyToBucketMap() { return *(KeyToBucketMap *)m_keyToBucketStorage; }
	unsigned int m_keyToBucketStorage[5];  // +0x2BF4C
	char m_mutex[1];                       // +0x2BF60 CriticalSection
};

const AsciiString &NameKeyGenerator::keyToName(NameKeyType key)
{
	ScopedCriticalSection scopedCriticalSection((CriticalSection *)m_mutex);
	NameKeyType k = key;
	KeyToBucketMap::iterator it = keyToBucketMap().find(k);
	if (it == keyToBucketMap().end())
		return AsciiString::TheEmptyString;
	return (*(Bucket **)&(*it).second)->m_nameString;
}
