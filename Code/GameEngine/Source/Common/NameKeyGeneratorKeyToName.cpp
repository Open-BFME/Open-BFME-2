// NameKeyGenerator::keyToName, RVA 0x00148C95..0x00148D00, 107 bytes.
// Completes the banked BFME2 reconstruction at reverse/attempts/0x00148c95.cpp.
// Reference semantics: BFME1 d6db6bfa NameKeyGenerator_keyToName.cpp; BFME2
// replaces the donor socket scan with a reverse key-to-Bucket hash index.
// Target independently proves reference return (ret 4, no hidden result),
// map +0x2BF4C, mutex +0x2BF60, Bucket name +0x0C and empty-string fallback.
// The typed map emits a 47-byte _M_find with no relocations, exactly equal
// to the ArmorTemplate map owner at 0x2888D4. Both inspect the node link/key
// prefix without reading the mapped value; retain the actual Bucket* type.
// Construct the iterator before the scoped key copy and assign the result;
// this preserves retail's iterator table home and argument-slot reuse.
// cl: /Ireference/shims/bfmevector /Ireference/shims/bfmehashtable /Ireference/shims/bfme2_ascii /MD /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /EHs-
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
template <typename T> struct hash;
template <> struct hash<NameKeyType>
{
	size_t operator()(NameKeyType value) const { return (size_t)value; }
};
template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const { return a == b; }
};
}

// The reverse key->Bucket index shares its lookup code with the ArmorTemplate
// map instantiation (retail calls the rowed _M_find at 0x002888D4).
class Bucket;
typedef std::hash_map<NameKeyType, Bucket *, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > KeyToBucketMap;

// Same eight-byte guard ABI as the existing Lock/Unlock owners. Only the
// pointer is needed here; mutex storage and Windows imports belong to them.
class CriticalSection;
class ScopedCriticalSection {
    friend class NameKeyLookupGuard;
    CriticalSection *m_cs;
    bool m_locked;
    void Lock();
    void Unlock();
};
class NameKeyLookupGuard : public ScopedCriticalSection {
public:
    __forceinline NameKeyLookupGuard(CriticalSection *cs) { m_cs=cs; m_locked=false; Lock(); }
    __forceinline ~NameKeyLookupGuard() { if (m_locked) Unlock(); }
};

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
	NameKeyLookupGuard scopedCriticalSection((CriticalSection *)m_mutex);
	KeyToBucketMap::iterator it;
	{
		NameKeyType k = key;
		it = keyToBucketMap().find(k);
	}
	if (it == keyToBucketMap().end())
		return AsciiString::TheEmptyString;
	return (*it).second->m_nameString;
}
