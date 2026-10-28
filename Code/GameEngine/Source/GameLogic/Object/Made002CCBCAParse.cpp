// cl: /DNDEBUG /MD
//
// ?q4Notify002CCBCA@@YAXPAXPAVMade002CCBCA@@HH@Z @0x0050B6F8 (77B).
// HordeAttackNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864DCC with
// index 0, then INI initFromINIMulti. Caller parseHordeAttackNugget
// at 0x002CCC0F. Same tail as q4Notify002CCCF3 precedent.

class Made002CCBCA;

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
struct LookupListRec { const char *name; int value; };
// The retail lookup list at RVA 0x00800698 (5 names and the null terminator).
extern const LookupListRec TheWeaponSlotTypeNamesLookupList[6] = { { "PRIMARY", 0 }, { "SECONDARY", 1 }, { "TERTIARY", 2 }, { "QUATERNARY", 3 }, { "QUINARY", 4 }, { 0, 0 } };
extern "C" {
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00864DCC: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00864DCC[3] = {
	{ "ClosestMemberOnly", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x128 },
	{ "LockWeaponSlot", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponSlotTypeNamesLookupList, 0x12C },
	{ 0, 0, 0, 0 }
};

int __cdecl Rva00507552Get();

class MultiIniFieldParse
{
public:
    MultiIniFieldParse();
    void add(const FieldParse *p, unsigned int u);

    char m_pad[0x84];
};

class INI
{
public:
    void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};

void q4Notify002CCBCA(void *ini, Made002CCBCA *m, int store, int d)
{
    MultiIniFieldParse multiParse;
    multiParse.add((const FieldParse *)Rva00507552Get(), 0);
    multiParse.add(g_00864DCC, 0);
    ((INI *)ini)->initFromINIMulti(m, multiParse);
}
