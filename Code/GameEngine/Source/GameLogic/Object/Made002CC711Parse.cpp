// cl: /DNDEBUG /MD
//
// ?q4Notify002CC711@@YAXPAXPAVMade002CC711@@HH@Z @0x00508EBF (77B).
// ParalyzeNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864450 with
// index 0, then INI initFromINIMulti. Caller parseParalyzeNugget
// at 0x002CC756. Same tail.

class Made002CC711;

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
    static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
    static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
    static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
    static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// The table pushed at 0x00C64450 (.rdata): 4 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x134. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse ParalyzeFieldTable[] =
{
    { "Radius",     &INI::parseReal,                 0, 0x128 },
    { "Duration",   &INI::parseDurationUnsignedInt,  0, 0x12C },
    { "DamageArc",  &INI::parseAngleReal,            0, 0x130 },
    { "ParalyzeFX", &INI::parseFXList,               0, 0x134 },
    { 0, 0, 0, 0 }
};

void q4Notify002CC711(void *ini, Made002CC711 *nugget, int store, int d)
{
    MultiIniFieldParse m_fieldParse;
    m_fieldParse.add((const FieldParse *)Rva00507552Get(), 0);
    m_fieldParse.add(ParalyzeFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(nugget, m_fieldParse);
}
