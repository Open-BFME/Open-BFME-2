// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// PlayerTemplateStore::rva001FD4E1, retail 0x001FD4E1 (153 B EH; the WB
// unnamed slot after the rowed 0x001FD4A2 override clear). Linear search
// over the store's template vector at +0x0C (stride 0x1DC, the same vector
// 0x001FD4A2 clears and PlayerTemplate.cpp lookups read): for each element
// the PlayerTemplate name key at +0x10 is resolved through the pinned
// NameKeyGenerator::keyToName 0x00148C95 into an AsciiString temporary and
// compared, and on a match the index is written to the out parameter. The
// temporary is only kept for the keyToName side effect/destruction; the
// comparison itself is on the key word. The method and element names are
// address-derived.
#include "ascii_string.h"
#include <vector>

enum NameKeyType
{
	NAMEKEY_INVALID = -1
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Overridable
{
public:
	Overridable *deleteOverrides();		// 0x001E35ED
};

struct PlayerTemplateOverrideView : public Overridable
{
public:
	char m_pad00[0x10];
	NameKeyType m_nameKey; // +0x10 +0x10
	char m_rest[0x1DC - 0x14]; // +0x14
};

class PlayerTemplateStore
{
public:
	bool rva001FD4E1(NameKeyType key, int *index);

private:
	char m_pad00[0x0C];
	_STL::vector<PlayerTemplateOverrideView> m_playerTemplates;	// +0x0C
};

bool PlayerTemplateStore::rva001FD4E1(NameKeyType key, int *index)
{
	for (unsigned int i = 0; i < m_playerTemplates.size(); ++i)
	{
		AsciiString name = TheNameKeyGenerator->keyToName(m_playerTemplates[i].m_nameKey);
		if (m_playerTemplates[i].m_nameKey == key)
		{
			*index = i;
			return true;
		}
	}
	return false;
}
