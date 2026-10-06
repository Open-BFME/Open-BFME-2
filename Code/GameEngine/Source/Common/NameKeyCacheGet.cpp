// cl: /DNDEBUG /MD
//
// ?get@Rva00148F5ECache@@QAE?AW4NameKeyType@@XZ, retail 0x00148F5E, 32 bytes.
// Lazily-resolved NameKey cache: struct holds a key at +0 and a name string
// at +4; when the key is 0 and TheNameKeyGenerator (global 0xDF36A4) exists,
// resolve via the rowed nameToKey at 0x00148E1A and cache it. Evidence: body
// pushes [esi+4] into the rowed nameToKey with ecx from 0xDF36A4; 40+ callers
// are static-init jmp stubs like 0x0045EE2C caching class strings.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00148F5ECache
{
public:
	NameKeyType get();

private:
	NameKeyType m_key;
	const char *m_name;
};

NameKeyType Rva00148F5ECache::get()
{
	if (m_key == NAMEKEY_INVALID)
	{
		if (TheNameKeyGenerator != 0)
			m_key = TheNameKeyGenerator->nameToKey(m_name);
	}
	return m_key;
}
