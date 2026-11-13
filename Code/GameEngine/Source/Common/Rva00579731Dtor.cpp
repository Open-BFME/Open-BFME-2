// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void vector<AsciiString, allocator<AsciiString> >::reserve(unsigned int); }
// bfme link decl-only end

#include "../../Include/Common/INI/INI.h"

// The table's native record. Its vector retains the ledger's BfmeE16 storage
// identity; only the field accesses use this parser view of the 16 bytes.
#include "../../Include/Common/INI/FieldParse.h"
extern const int g_emptyFieldParseTable[4];

// The narrow "text + text" node, as WinMainPairUnicode.cpp and
// RegistryAsciiPath.cpp view it.
#include "../../Include/Common/Rva000B3F84Pair.h"
#include "../../Include/Common/WinMainTitlePair.h"
Rva000B3F84Pair Rva00108B93Make(const char *src);
WinMainTitlePair operator+(const Rva000B3F84Pair &left, const char *right);

// The stat hint handed to the stats display's tooltip: a reference-counted
// object (count at +4, released through the rowed 0x0007DEEF) built by the
// pinned 0x005398CD from a title and a help text, as InGameHotSpotSimpleHelp
// builds it.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);


class InGameSimpleHelp
{
public:
	InGameSimpleHelp(const UnicodeString &first, const UnicodeString &second);

private:
	char m_opaque[12];
};

#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

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
	TreeHintRef00217D4C rva00579770(int stat);
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
	FieldParse field;
	field.offset = 0;
	field.parse = parseStatString;
	for (int i = 0; i < 6; i++)
	{
		names.push_back(Rva00108B93Make(s_statNames[i]) + "RowTitle");
		field.token = names.back().str();
		field.userData = &m_at8[i].m_title;
		table.push_back(*(const BfmeE16 *)&field);
		names.push_back(Rva00108B93Make(s_statNames[i]) + "RowHelp");
		field.token = names.back().str();
		field.userData = &m_at8[i].m_help;
		table.push_back(*(const BfmeE16 *)&field);
	}
	table.push_back(*(const BfmeE16 *)g_emptyFieldParseTable);
	ini->initFromINI(this, (const FieldParse *)&table[0]);
}
// ?rva00579770@Rva00579731@@QAE?AUTreeHintRef00217D4C@@H@Z @0x00579770 248B:
// the hint for one stat line, from the localized title and help labels the
// INI block gave it (an empty label leaves its text empty). Caller the stats
// display's OnStatRollOver 0x00579B81 on this global (0x00E0631C).
TreeHintRef00217D4C Rva00579731::rva00579770(int stat)
{
	const Rva005796FC &row = m_at8[stat];
	UnicodeString title;
	if (!((const StringBase<char> *)&row.m_title)->isEmpty())
		title = TheGameText->fetch(row.m_title);
	UnicodeString help;
	if (!((const StringBase<char> *)&row.m_help)->isEmpty())
		help = TheGameText->fetch(row.m_help);
	return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title, help));
}

// ??1Rva005796FC@@QAE@XZ: rowed in stlport_vector_stringrecord_b94d2_allocate_copy.cpp but that TU emits ??1BfmeStringRecord000B94D2@@QAE@XZ; bind this spelling.
#pragma comment(linker, "/alternatename:??1Rva005796FC@@QAE@XZ=??1BfmeStringRecord000B94D2@@QAE@XZ")
// ??0Rva005796FC@@QAE@XZ: the pair ctor 0x0007E81F is ICF-folded; the ledger compiles it as ??0DataChunkInfo@@QAE@XZ.
#pragma comment(linker, "/alternatename:??0Rva005796FC@@QAE@XZ=??0DataChunkInfo@@QAE@XZ")
