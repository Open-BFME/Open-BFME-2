// cl: /O1 /DNDEBUG /MD
// Retail RE: ?parseFlammability@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z @0x0033BC6A (230B).
//
// BFME2-new ThingTemplate Flammability sub-object at +0x314 (788). Target facts
// from retail bytes + checkpoint + string-table (all independently read this round):
// - Main table RVA 0x9BECD8 (VA 0xDBECD8) entry 178 at RVA 0x9BF7F8: token
//   "Flammability" (RVA 0x80ECF4), parse 0x33BC6A, user 0, offset 0x314.
//   Record bytes at 0x9BF7F8 match table entry; source pointer at 0x9BF7FC is
//   entry+4 (code-pointer table evidence).
// - Four registration sites use the same main table: 0x33A552 + 0x33A5A6 +
//   0x33CEFA via matched INI::initFromINI 0x2DE78 (61B, INI_initFromINI.cpp),
//   and 0x33A907 via matched MultiIniFieldParse::add 0x2BC6E (60B).
//   Callers 0x33A50D/0x33A561 are matched ThingTemplate parseAddModule/
//   parseInheritableModule (84B each, /O1) passing esi (ThingTemplate*) + table.
// - Target 0x33BC6A..0x33BD50 230B, single ret at 0x33BD4F, SHA
//   a83e13c47608a6562c9afda85346914fd5c2f39d8be2cd1d8a629477990795b2.
//   Guard dword at RVA 0xA01DD4 (VA 0xE01DD4): test byte,1 / jne skip, or dword,1.
//   Sub-table at RVA 0x9BF8D8 (VA 0xDBF8D8): 5 entries + terminator, decoded
//   from code immediates + file bytes (first entry token/parse preset in file).
// - Sub-table entries (token VA -> string, parse VA, user, off):
//   [0] Fuel (00BFB734) via INI::dup_002EF72 (0x2EF72, 78B max-bounded unsigned)
//       user 0xFFFF off 0; [1] FuelFactor (00810544) via 0x33B677 (197B Ghidra,
//       pinned ?rva0033B677, address-derived ABI only) user instance off 0;
//   [2] MaxBurnRate (007FB774) via dup_002EF72 user 0xFFF off 4;
//   [3] Decay (007DA030) via dup_002EF72 user 0x3FF off 8;
//   [4] Resistance (007FB768) via dup_002EF72 user 0xFF off 12;
//   [5] terminator 0,0,0,0. Delegate: ecx=[esp+4] (INI*), push table,
//   edx=[esp+8]+0x314, call initFromINI, ret.
// - Receiver: ThingTemplate* +0x314 = Flammability object (4 bounded ints +
//   FuelFactor float path via 0x33B677 which reads parent +0x2E4/0x2E8 through
//   matched getNthData 0x33ACE8). ABI void (__cdecl static)
//   (INI*, void* instance, void* store, const void* userData), plain ret.
// Donor-carried (unproven, moderate delta allowed): ZH/BFME1 ThingTemplate.cpp
// (6583b3c1) has no Flammability field or sub-table; the INI callback shape,
// FieldParse layout {token,parse,userData,offset}, and initFromINI delegate
// pattern are carried from ZH parsePrerequisites/parseAddModule family only.
// All Flammability tokens, maxes, offsets, guard/table placement, and the
// instance-capturing FuelFactor userData are BFME2 target facts, not donor.
// No shared-header edits; TU-scoped shims only.

typedef void (__cdecl *ParseProc)(class INI *, void *, void *, const void *);

struct FieldParse
{
	const char *token;
	ParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
	static void __cdecl dup_002EF72(INI *ini, void *instance, void *store, const void *userData);
};

void __cdecl rva0033B677(INI *ini, void *instance, void *store, const void *userData);

static int s_flammabilityInit;
static FieldParse s_flammabilityTable[6] = {
	{ "Fuel", INI::dup_002EF72, 0, 0 },
};

class ThingTemplate
{
protected:
	static void __cdecl parseFlammability(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseFlammability@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseFlammability(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	if (!(s_flammabilityInit & 1)) {
		s_flammabilityInit |= 1;
		s_flammabilityTable[0].userData = (const void *)0xFFFF;
		s_flammabilityTable[0].offset = 0;
		s_flammabilityTable[1].token = "FuelFactor";
		s_flammabilityTable[1].parse = rva0033B677;
		s_flammabilityTable[1].userData = instance;
		s_flammabilityTable[1].offset = 0;
		s_flammabilityTable[2].token = "MaxBurnRate";
		s_flammabilityTable[2].parse = INI::dup_002EF72;
		s_flammabilityTable[2].userData = (const void *)0xFFF;
		s_flammabilityTable[2].offset = 4;
		s_flammabilityTable[3].token = "Decay";
		s_flammabilityTable[3].parse = INI::dup_002EF72;
		s_flammabilityTable[3].userData = (const void *)0x3FF;
		s_flammabilityTable[3].offset = 8;
		s_flammabilityTable[4].token = "Resistance";
		s_flammabilityTable[4].parse = INI::dup_002EF72;
		s_flammabilityTable[4].userData = (const void *)0xFF;
		s_flammabilityTable[4].offset = 12;
		s_flammabilityTable[5].token = 0;
		s_flammabilityTable[5].parse = 0;
		s_flammabilityTable[5].userData = 0;
		s_flammabilityTable[5].offset = 0;
	}
	ini->initFromINI((char *)instance + 0x314, s_flammabilityTable);
}
