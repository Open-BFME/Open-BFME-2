// cl: /O1 /DNDEBUG /MD
//
// ?rva004649A1@@YAXPAVINI@@PAX1PBX@Z @0x004649A1 (87B).
// The retail FieldParse table at VA 0x00C439C0 pairs the
// "BoneSpecificConditionState" string with this callback pointer. The body
// reads an unsigned key, parses a zero-initialized 0x4C flag set through the
// pinned self-parse at 0x000B937E, then copies it into the map value returned
// by the byte-matched unsigned-key lookup at 0x00464923. The field string and
// callback identity are target evidence; the map's owning class is unknown,
// so the function name stays address-derived. The +0x4C map offset is a direct
// target access, not a recovered class layout.
#include <string.h>

class INI
{
public:
	const char *getNextToken(const char *separators);
	unsigned int scanUnsignedInt(const char *token);
};

class Rva000B937E
{
public:
	void rva000B937E(INI *ini, void *extra);
private:
	unsigned int m_bits[19];
};

class WeaponTemplateSetHead
{
private:
	unsigned int m_bits[19];
};

class Rva00464923
{
public:
	WeaponTemplateSetHead &rva00464923(const unsigned int &key);
};

void rva004649A1(INI *ini, void *instance, void *store, const void *userData)
{
	unsigned int zero = 0;
	unsigned int key = ini->scanUnsignedInt(ini->getNextToken((const char *)zero));
	Rva000B937E flags;
	memset(&flags, (int)zero, 0x4C);
	flags.rva000B937E(ini, (void *)zero);
	WeaponTemplateSetHead &rawEntry = ((Rva00464923 *)((char *)instance + 0x4C))->rva00464923(key);
	Rva000B937E &entry = *(Rva000B937E *)(void *)&rawEntry;
	entry = flags;
}
