// ?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-22
// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z, retail 0x00361CA5, 993 bytes.
// The INI field proc behind every ObjectFilter row (AcceptanceFilter,
// AfraidOf, AllowFilter, ... -- 77 FieldParse rows); its own error strings
// name it iniParseObjectFilter.
//
// Reconstructed from BFME1's body (IniParseObjectFilterShim_run.cpp) with the
// BFME2 changes the bytes show: the tokens are read up front through
// INI::parseAsciiStringVector and then walked; SAME_PLAYER joins the
// relationship keywords (bit 8), EVIL/GOOD set an alignment field without a
// case check, the kind-of bitsets are seven words wide (BitFlags<218>), and
// the compare is msvcr71!_strcmpi through the IAT (0xBBA518) followed by a
// case-sensitive strcmp. The filter record is 0x94 bytes (its dtor is the
// pinned ??1BfmeStringHeadRecord148); the vector it and the token list use is
// the ledger's RvaVecAscii. Field names follow BFME1.

typedef unsigned int UnsignedInt;

class INI;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	~StringBase();

private:
	StringBase(const T *s);

	struct Data
	{
		int m_refCount;
		int m_lengths;
		T m_chars[1];		// +8
	};

protected:
	Data *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	const char *str() const { return m_data ? m_data->m_chars : ""; }
};

struct RvaVecAsciiAlloc
{
	RvaVecAsciiAlloc() {}
};

class RvaVecAsciiBase
{
public:
	RvaVecAsciiBase(const RvaVecAsciiAlloc &alloc);

	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

class RvaVecAscii : public RvaVecAsciiBase
{
public:
	__forceinline RvaVecAscii() : RvaVecAsciiBase(RvaVecAsciiAlloc()) {}
	~RvaVecAscii();
	void push_back(const AsciiString &value);
	AsciiString *begin() { return m_start; }
	AsciiString *end() { return m_finish; }
};

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

struct BfmeStringHeadRecord148
{
	BfmeStringHeadRecord148();
	~BfmeStringHeadRecord148();

	RvaVecAscii m_names;				// +0x00
	RvaVecAscii m_values;				// +0x0C
	RvaVecAscii m_lists[4];				// +0x18
	BfmeAttributeBits m_firstPlain;		// +0x48
	BfmeAttributeBits m_secondPlain;	// +0x64
	UnsignedInt m_kind;					// +0x80
	UnsignedInt m_relationship;			// +0x84
	bool m_enabled;						// +0x88
	unsigned char m_pad89[3];
	UnsignedInt m_useCount;				// +0x8C
	UnsignedInt m_alignment;			// +0x90
};

struct BfmeAttributeHandle
{
	UnsignedInt m_handle;
};

void bfmeReleaseAttributeHandle(BfmeAttributeHandle *handle);
UnsignedInt bfmeInternAttributeEntry(BfmeStringHeadRecord148 *entry);

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

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" int __cdecl strcmp(const char *a, const char *b);

// ?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *)
{
	BfmeStringHeadRecord148 entry;
	BfmeAttributeHandle *handle = (BfmeAttributeHandle *)store;
	if (handle->m_handle != 0xffffffff)
		bfmeReleaseAttributeHandle(handle);

	bool hasRuleset = false;
	RvaVecAscii tokens;
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
				entry.m_firstPlain.m_values[(UnsignedInt)bit >> 5] |= 1 << (bit & 31);
			else
				entry.m_names.push_back(AsciiString(token));
			entry.m_enabled = true;
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
	handle->m_handle = bfmeInternAttributeEntry(&entry);
}
