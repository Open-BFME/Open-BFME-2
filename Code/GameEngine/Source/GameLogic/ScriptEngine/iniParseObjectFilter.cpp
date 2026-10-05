// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z, retail 0x00361CA5, 993 bytes.
// The INI field proc behind every ObjectFilter FieldParse row; its own error
// strings name it iniParseObjectFilter. Reconstructed from BFME1's body
// (reference/open-bfme-1 game/.../ScriptEngine/IniParseObjectFilterShim_run.cpp)
// with the BFME2 changes the bytes show: the tokens are read up front through
// INI::parseAsciiStringVector and then walked; SAME_PLAYER joins the
// relationship keywords (bit 8), EVIL/GOOD set an alignment field without a
// case check, the kind-of bitsets are seven words wide, and the compare is
// msvcr71!_strcmpi through the IAT followed by a case-sensitive strcmp.
//
// The record is the 0x94-byte Rva00360F55 (ctor 0x00360F55, dtor 0x00360FDB);
// the handle is released through Rva00360CB0Release and re-interned through
// Rva00361790. Field names follow BFME1. With the real STLport
// vector<AsciiString> the allocator temp lands in the top byte of the store
// slot ([ebp+0x13]) as retail's does; a hand-rolled vector view gives it a
// frame slot and shifts every local by 4. The '+' arm's duplicated
// m_enabled store is what puts the push_back block after the shared tail.
//
// string.h (via the STL headers below) declares _strcmpi without dllimport
// because this TU builds with /D_CRTIMP=; rename that decl away so the real
// import decl after the includes is the only _strcmpi the TU sees.
#define _strcmpi _stlport_hides_strcmpi
#include <vector>
#include "ascii_string.h"
#undef _strcmpi
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

typedef unsigned int UnsignedInt;
class INI;
typedef _STL::vector<AsciiString> AsciiStringVector;

template <int NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

struct BfmeAttributeBits
{
	UnsignedInt m_values[7];	// BitFlags<218>
};

class Rva00360F55
{
public:
	Rva00360F55();
	~Rva00360F55();

	AsciiStringVector m_names;			// +0x00
	AsciiStringVector m_values;			// +0x0C
	AsciiStringVector m_lists[4];		// +0x18
	BfmeAttributeBits m_firstPlain;		// +0x48
	BfmeAttributeBits m_secondPlain;	// +0x64
	UnsignedInt m_kind;					// +0x80
	UnsignedInt m_relationship;			// +0x84
	bool m_enabled;						// +0x88
	unsigned char m_pad89[3];
	UnsignedInt m_useCount;				// +0x8C
	UnsignedInt m_alignment;			// +0x90
};

void Rva00360CB0Release(int *indexHolder);
int Rva00361790(Rva00360F55 *entry);

class INI
{
public:
	static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

	char *mFailureMessage;
	int m_argumentCount;
};


// ?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *)
{
	Rva00360F55 entry;
	int *handle = (int *)store;
	if (*handle != -1)
		Rva00360CB0Release(handle);

	bool hasRuleset = false;
	AsciiStringVector tokens;
	INI::parseAsciiStringVector(ini, instance, &tokens, 0);

	bool first = true;
	for (AsciiString *it = tokens.begin(); it != tokens.end(); ++it)
	{
		const char *token = it->str();
		if (_strcmpi(token, "ALL") == 0)
		{
			if (!first)
				throw INIException(3, "When using ALL in iniParseObjectFilter, ALL must be the first entry.");
			if (strcmp(token, "ALL") != 0)
				throw INIException(3, "iniParseObjectFilter ALL keyword is case sensitive. You specified %s.", token);
			entry.m_kind = 3;
			entry.m_enabled = true;
			hasRuleset = true;
		}
		else if (_strcmpi(token, "ANY") == 0)
		{
			if (!first)
				throw INIException(3, "When using ANY in iniParseObjectFilter, ANY must be the first entry.");
			if (strcmp(token, "ANY") != 0)
				throw INIException(3, "iniParseObjectFilter ANY keyword is case sensitive. You specified %s.", token);
			entry.m_kind = 2;
			entry.m_enabled = true;
			hasRuleset = true;
		}
		else if (_strcmpi(token, "NONE") == 0)
		{
			if (!first)
				throw INIException(3, "When using NONE in iniParseObjectFilter, NONE must be the first entry.");
			if (strcmp(token, "NONE") != 0)
				throw INIException(3, "iniParseObjectFilter NONE keyword is case sensitive. You specified %s.", token);
			entry.m_kind = 1;
			entry.m_enabled = false;
			hasRuleset = true;
		}
		else if (_strcmpi(token, "ALLIES") == 0)
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "ALLIES") != 0)
				throw INIException(3, "iniParseObjectFilter ALLIES keyword is case sensitive. You specified %s.", token);
			entry.m_relationship |= 1;
		}
		else if (_strcmpi(token, "ENEMIES") == 0)
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "ENEMIES") != 0)
				throw INIException(3, "iniParseObjectFilter ENEMIES keyword is case sensitive. You specified %s.", token);
			entry.m_relationship |= 2;
		}
		else if (_strcmpi(token, "NEUTRAL") == 0)
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "NEUTRAL") != 0)
				throw INIException(3, "iniParseObjectFilter NEUTRAL keyword is case sensitive. You specified %s.", token);
			entry.m_relationship |= 4;
		}
		else if (_strcmpi(token, "SAME_PLAYER") == 0)
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "SAME_PLAYER") != 0)
				throw INIException(3, "iniParseObjectFilter SAME_PLAYER keyword is case sensitive. You specified %s.", token);
			entry.m_relationship |= 8;
		}
		else if (_strcmpi(token, "EVIL") == 0)
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			entry.m_alignment = 1;
		}
		else if (_strcmpi(token, "GOOD") == 0)
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			entry.m_alignment = 2;
		}
		else if (token[0] == '+')
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (entry.m_kind == 3)
				throw INIException(3, "ALL is specified for iniParseObjectFilter, so adding %s has no effect. Please remove entry.", token);
			++token;
			int bit = BitFlags<218>::getSingleBitFromName(token);
			if (bit != -1)
			{
				entry.m_firstPlain.m_values[(UnsignedInt)bit >> 5] |= 1 << (bit & 31);
				entry.m_enabled = true;
			}
			else
			{
				entry.m_names.push_back(AsciiString(token));
				entry.m_enabled = true;
			}
		}
		else if (token[0] == '-')
		{
			if (!hasRuleset)
				throw INIException(3, "iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			++token;
			int bit = BitFlags<218>::getSingleBitFromName(token);
			if (bit != -1)
				entry.m_secondPlain.m_values[(UnsignedInt)bit >> 5] |= 1 << (bit & 31);
			else
				entry.m_values.push_back(AsciiString(token));
		}
		else
		{
			throw INIException(3, "iniParseObjectFilter expecting a + or - token as it is required for classification. Instead it found %s", token);
		}
		first = false;
	}
	*handle = Rva00361790(&entry);
}
