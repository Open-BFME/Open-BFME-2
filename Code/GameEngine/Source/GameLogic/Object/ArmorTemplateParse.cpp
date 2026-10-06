// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// BFME2 ArmorTemplate, retail-measured from game.dat (NOT the ZH layout:
// Zero Hour carries 38 coefficients and a scalar at +0x5C; BFME2 carries 27
// coefficients starting at +0x04, the scalar at +0x70, a flag at +0x74 and the
// template name at +0x78 for 0x7C bytes, which is also what the retail
// operator-new site in parseArmorDefinition allocates):
//   +0x00 float m_head (FP-zeroed by clear; carries the heap instance after parse)
//   +0x04 float m_damageCoefficient[27] (rep stosd 27 from +0x04 in clear)
//   +0x70 float m_damageScalar (parseDamageScalar stores here)
//   +0x74 int m_flag (clear ors -1; parse sets 1 or ands 0)
//   +0x78 AsciiString m_name (op=/dtor at 0x366F0/0x36410)
//
// The "Armor" INI block node in .data points its parse slot at 0x001D9484,
// which is ArmorStore::parseArmorDefinition below; its field table names the
// DamageScalar verb (0x001D8F02) whose body is a tokenize-scale-store one-liner.

// string.h (via the STL headers below) declares _strcmpi without dllimport
// because this TU builds with /D_CRTIMP=; rename that decl away so the real
// import decl after the includes is the only _strcmpi the TU sees.
#define _strcmpi _stlport_hides_strcmpi
#include <hash_map>
#include <vector>
#include <cstddef>
#undef _strcmpi

#define NULL 0

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

}

#include "ascii_string.h"

extern AsciiString TheDefaultArmorTemplateName; // zeroed static at 0x009E0878

// msvcr71!_strcmpi through the IAT (retail slot 0xBBA518), not _stricmp.
// The STL headers above declare it without dllimport, so the shield at the
// top renamed that decl away and this import decl is the only one in force.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// Retail damage-name table at 0x009B8968 (27 entries: FORCE, CRUSH, SLASH,
// PIERCE, SIEGE, STRUCTURAL, FLAME, HEALING, UNRESISTABLE, WATER, PENALTY,
// FALLING, TOPPLING, REFLECTED, PASSENGER, MAGIC, CHOP, HERO, SPECIALIST,
// URUK, HERO_RANGED, FLY_INTO, UNDEFINED, LOGICAL_FIRE, CAVALRY,
// CAVALRY_RANGED, POISON); the push is DIR32-masked, so only the reference
// matters, never the address.
extern const char *TheDamageNames[];

class INI
{
public:
	const char *getNextToken(const char *seps);
	float dup_002EE10(const char *token);
	int scanIndexList(const char *token, const char *const *nameList);
};

// BFME2 carries 27 damage coefficients (retail rep stosd count 0x1B).
enum
{
	ARMOR_DAMAGE_TYPES = 27
};

class ArmorTemplate
{
public:
	ArmorTemplate(const AsciiString &name);
	~ArmorTemplate();
	static void parseArmorCoefficients(INI *ini, void *instance, void *store, const void *userData);
	static void parseDamageScalar(INI *ini, void *instance, void *store, const void *userData);
	void clear();

private:
	float m_head; // +0x00
	float m_damageCoefficient[ARMOR_DAMAGE_TYPES]; // +0x04
	float m_damageScalar; // +0x70
	int m_flag; // +0x74
	AsciiString m_name; // +0x78
};

typedef char AssertArmorTemplateSize[sizeof(ArmorTemplate) == 0x7C ? 1 : -1];

// ??0ArmorTemplate@@QAE@ABVAsciiString@@@Z
ArmorTemplate::ArmorTemplate(const AsciiString &name) : m_name()
{
	clear();
	m_name = name;
}

// ??1ArmorTemplate@@QAE@XZ
// Empty body: the compiler tails into the member name dtor at 0x36410.
ArmorTemplate::~ArmorTemplate()
{
}

// ?parseArmorCoefficients@ArmorTemplate@@SAXPAVINI@@PAX1PBX@Z
// One line of an Armor block: "<DamageType> <Percent>%". "Default" fills
// every coefficient; anything else is looked up positionally in
// TheDamageNames and overwrites that one slot.
/*static*/ void ArmorTemplate::parseArmorCoefficients(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	ArmorTemplate *self = (ArmorTemplate *)instance;

	const char *damageName = ini->getNextToken(NULL);
	float pct = ini->dup_002EE10(ini->getNextToken(NULL));

	if (_strcmpi(damageName, "Default") == 0)
	{
		for (int i = 0; i < ARMOR_DAMAGE_TYPES; i++)
		{
			self->m_damageCoefficient[i] = pct;
		}
		return;
	}

	int dt = ini->scanIndexList(damageName, TheDamageNames);
	self->m_damageCoefficient[dt] = pct;
}

// ?parseDamageScalar@ArmorTemplate@@SAXPAVINI@@PAX1PBX@Z
void ArmorTemplate::parseDamageScalar(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	ArmorTemplate *self = (ArmorTemplate *)instance;
	self->m_damageScalar = ini->dup_002EE10(ini->getNextToken(NULL));
}

void ArmorTemplate::clear()
{
	for (int i = 0; i < ARMOR_DAMAGE_TYPES; ++i)
	{
		m_damageCoefficient[i] = 1.0f;
	}
	m_flag |= -1;
	m_damageScalar = 1.0f;
	m_head = 0.0f;
	m_name = TheDefaultArmorTemplateName;
}
// ?TheDefaultArmorTemplateName@@3VAsciiString@@A: the global at VA 0xde0878 is ?TheEmptyString@AsciiString@@2V1@B.
#pragma comment(linker, "/alternatename:?TheDefaultArmorTemplateName@@3VAsciiString@@A=?TheEmptyString@AsciiString@@2V1@B")
