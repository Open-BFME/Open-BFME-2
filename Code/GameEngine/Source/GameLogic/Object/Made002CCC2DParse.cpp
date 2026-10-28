// cl: /DNDEBUG /MD
//
// ?q4Notify002CCC2D@@YAXPAXPAVMade002CCC2D@@HH@Z @0x0050B8DB (77B).
// SpawnAndFadeNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00C64E70 with
// index 0, then INI initFromINIMulti. Caller parseSpawnAndFadeNugget
// at 0x002CCC72. Same two-add shape as q4Notify002CCBCA precedent.

class Made002CCC2D;

class INI;

struct FieldParse
{
    const char *token;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    int offset;
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
    static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
    static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

// The table pushed at 0x00C64E70 (.rdata): 3 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x130. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse SpawnAndFadeFieldTable[] =
{
    { "ObjectTargetFilter", &iniParseObjectFilter,   0, 0x128 },
    { "SpawnedObjectName",  &INI::parseAsciiString,  0, 0x12C },
    { "SpawnOffset",        &INI::parseCoord3D,      0, 0x130 },
    { 0, 0, 0, 0 }
};

void q4Notify002CCC2D(void *ini, Made002CCC2D *m, int store, int d)
{
    MultiIniFieldParse parseTables;
    parseTables.add((const FieldParse *)Rva00507552Get(), 0);
    parseTables.add(SpawnAndFadeFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, parseTables);
}
