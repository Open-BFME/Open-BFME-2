// cl: /O1 /DNDEBUG /MD /GX-
//
// WeaponStore::findWeaponTemplate, retail 0x002CB8BF, 67 bytes.
//
// Returns NULL for the "None" name (via _strcmpi against the inline
// str() with empty-string fallback), otherwise looks the template up
// by NameKeyType through the Rva002CADBE key search (0x002CADBE,
// pinned; 0.85 partial banked for the body itself).
//
// Modeling notes: AsciiString is the 4-byte m_data spelling whose str()
// is m_data + 8 with the "" fallback (TerrainTypes precedent); the key
// conversion is the rowed NameKeyGenerator::nameToKey (0x009FA65)
// through the 0xDF36A4 global; _strcmpi rides its msvcr71 IAT slot.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString
{
public:
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }

private:
	void *m_data;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class WeaponTemplate
{
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;

private:
	const WeaponTemplate *Rva002CADBE(int key) const;
};

// ?findWeaponTemplate@WeaponStore@@QBEPBVWeaponTemplate@@ABVAsciiString@@@Z
const WeaponTemplate *WeaponStore::findWeaponTemplate(const AsciiString &name) const
{
	if (_strcmpi(name.str(), "None") == 0)
		return 0;
	return Rva002CADBE(TheNameKeyGenerator->nameToKey(name));
}
