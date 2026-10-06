// cl: /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva00579731@@UAE@XZ, retail 0x00579731 63B.
// Evidence: chain lane calls just-landed 0x0022167C plus element dtor 0x005796FC with size 8 count 6 at this+8; callers 0x00579CBB 0x007B94CD.
// Rva0022167C is 8B polymorphic holder from Rva0022161BClear.cpp; element is 8B BfmeStringRecord000B94D2 pair.
//
// The class is StrategicHUD's StatsDisplay: its ctor 0x00579C52 builds the
// base 0x00221635 from AsciiString("StatsDisplay"), stores vtable 0x00C6ED9C
// (slot0 the deleting dtor 0x00579CB8, slot1 the INI parse 0x0057A09F) and
// constructs the six pairs at +8 through 0x0007E81F. The global instance at
// 0x00E0631C is destroyed by the atexit thunk 0x007B94C8. The destructor
// resets no vptr, so it is the implicit one, virtual through the base.
#include "ascii_string.h"
#include <vector>

class INI
{
public:
	void initFromINI(void *what, const struct FieldParse *parseTable);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
};

// The 16-byte FieldParse record the table vector holds, under the element
// name the ledger gives the shared vector<BfmeE16> helpers.
struct BfmeE16
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};
extern const int g_emptyFieldParseTable[4];

// The narrow "text + text" node, as WinMainPairUnicode.cpp and
// RegistryAsciiPath.cpp view it.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}

	const char *m_ptr;
	int m_len;
};
struct WinMainTitlePair : Rva000B3F84Pair
{
	operator AsciiString();

	Rva000B3F84Pair m_secondPair;
};
Rva000B3F84Pair Rva00108B93Make(const char *src);
WinMainTitlePair operator+(const Rva000B3F84Pair &left, const char *right);

class Rva0022167C {
public:
	Rva0022167C(const AsciiString &name);
	virtual ~Rva0022167C();
private:
	void *m_at4;
};
struct Rva005796FC {
	Rva005796FC();
	~Rva005796FC();

	AsciiString m_title;
	AsciiString m_help;
};
class Rva00579731 : public Rva0022167C {
public:
	Rva00579731();
	virtual void rva0057A09F(INI *ini);
private:
	Rva005796FC m_at8[6];
};

// ??0Rva00579731@@QAE@XZ @0x00579C52 102B
Rva00579731::Rva00579731() : Rva0022167C(AsciiString("StatsDisplay"))
{
}

// ?parseStatString@@YAXPAVINI@@PAX1PBX@Z @0x0057965D 23B: the field's
// userData is the AsciiString itself.
static void parseStatString(INI *ini, void *instance, void *store, const void *userData)
{
	INI::parseAsciiString(ini, (void *)userData, (void *)userData, 0);
}

// ?rva0057A09F@Rva00579731@@UAEXPAVINI@@@Z @0x0057A09F 406B: builds
// <Stat>RowTitle and <Stat>RowHelp fields for the six stat lines and parses
// the block into them.
void Rva00579731::rva0057A09F(INI *ini)
{
	static const char *const s_statNames[] = {
		"CommandPoints", "AttackBonus", "DefenseBonus",
		"ExperienceBonus", "ResourceMultiplier", "PowerPoints",
	};
	_STL::vector<AsciiString> names;
	names.reserve(12);
	_STL::vector<BfmeE16> table;
	table.reserve(13);
	BfmeE16 field;
	field.offset = 0;
	field.parse = parseStatString;
	for (int i = 0; i < 6; i++)
	{
		names.push_back(Rva00108B93Make(s_statNames[i]) + "RowTitle");
		field.token = names.back().str();
		field.userData = &m_at8[i].m_title;
		table.push_back(field);
		names.push_back(Rva00108B93Make(s_statNames[i]) + "RowHelp");
		field.token = names.back().str();
		field.userData = &m_at8[i].m_help;
		table.push_back(field);
	}
	table.push_back(*(const BfmeE16 *)g_emptyFieldParseTable);
	ini->initFromINI(this, (const FieldParse *)&table[0]);
}
// ??1Rva005796FC@@QAE@XZ: rowed in stlport_vector_stringrecord_b94d2_allocate_copy.cpp but that TU emits ??1BfmeStringRecord000B94D2@@QAE@XZ; bind this spelling.
#pragma comment(linker, "/alternatename:??1Rva005796FC@@QAE@XZ=??1BfmeStringRecord000B94D2@@QAE@XZ")
// ??0Rva005796FC@@QAE@XZ: the pair ctor 0x0007E81F is ICF-folded; the ledger compiles it as ??0DataChunkInfo@@QAE@XZ.
#pragma comment(linker, "/alternatename:??0Rva005796FC@@QAE@XZ=??0DataChunkInfo@@QAE@XZ")
