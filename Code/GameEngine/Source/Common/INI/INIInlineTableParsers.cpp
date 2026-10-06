// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// Two more FieldParse procs (names address-derived):
//   0x0033A49B 102B FormationPreviewDecal / FormationPreviewItemDecal
//       (0x00DBF888 / 0x00DBF898): fills a {Texture, Width, Height} decal
//       record at the store through initFromINI with a FieldParse table built
//       on the stack (parseAsciiString at +0, parseReal at +4 and +8).
//   0x004BACAF 97B WeaponThatCausesEvacuation (0x00C59DD0): keeps the token
//       as the AsciiString at instance + 8 only when TheWeaponStore knows the
//       weapon (rowed findWeaponTemplate 0x002CB8BF).
//   0x0045A22E 99B Query (0x00C41700): takes the first of six {count, object
//       filter} slots at the store whose count is still negative, parses the
//       count (parseInt) and the filter (rowed iniParseObjectFilter
//       0x00361CA5) into it, and throws INIException "iniParseQuery: Too many
//       queries, can only have %d." when all six are used.

#include "ascii_string.h"

#define NULL 0

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0033A49B_ParseDecal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004BACAF_ParseWeaponName(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0045A22E_ParseQuery(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

class WeaponTemplate;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};
extern WeaponStore *TheWeaponStore;

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

struct Rva0045A22EQuery
{
	int m_count;
	int m_filter;
};

struct Rva004BACAFOwner
{
	unsigned char m_unreconstructed_00[8];
	AsciiString m_weaponName;	// +0x08
};

// ?Rva0033A49B_ParseDecal@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0033A49B_ParseDecal(INI *ini, void *, void *store, const void *)
{
	FieldParse dataFieldParse[] =
	{
		{ "Texture", INI::parseAsciiString, NULL, 0 },
		{ "Width", INI::parseReal, NULL, 4 },
		{ "Height", INI::parseReal, NULL, 8 },
		{ NULL, NULL, NULL, 0 }
	};
	ini->initFromINI(store, dataFieldParse);
}

// ?Rva004BACAF_ParseWeaponName@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004BACAF_ParseWeaponName(INI *ini, void *instance, void *, const void *)
{
	const char *token = ini->getNextToken();
	if (TheWeaponStore->findWeaponTemplate(AsciiString(token)))
		((Rva004BACAFOwner *)instance)->m_weaponName.set(token);
}

// ?Rva0045A22E_ParseQuery@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0045A22E_ParseQuery(INI *ini, void *instance, void *store, const void *userData)
{
	Rva0045A22EQuery *query = (Rva0045A22EQuery *)store;
	for (int i = 0; i < 6; ++i, ++query)
	{
		if (query->m_count < 0)
		{
			INI::parseInt(ini, instance, &query->m_count, userData);
			iniParseObjectFilter(ini, instance, &query->m_filter, userData);
			return;
		}
	}
	throw INIException(1, "iniParseQuery: Too many queries, can only have %d.", 6);
}
