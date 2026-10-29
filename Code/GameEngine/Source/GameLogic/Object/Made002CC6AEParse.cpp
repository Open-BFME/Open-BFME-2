// cl: /DNDEBUG /MD
//
// ?q4Notify002CC6AE@@YAXPAXPAVMade002CC6AE@@HH@Z @0x00508D2F (77B).
// SpecialModelConditionNugget field parser: MultiIni tmp, add table
// from getter 0x00507552 with index 0, add FieldParse table at
// 0x008643D4 with index 0, then INI initFromINIMulti. Caller
// parseSpecialModelConditionNugget at 0x002CC6F3. Same tail.

class Made002CC6AE;

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
    static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
    static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

// The table pushed at 0x00C643D4 (.rdata): 2 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x134. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse SpecialModelConditionFieldTable[] =
{
    { "ModelConditionNames",    &INI::parseAsciiStringVector,    0, 0x128 },
    { "ModelConditionDuration", &INI::parseDurationUnsignedInt,  0, 0x134 },
    { 0, 0, 0, 0 }
};

void q4Notify002CC6AE(void *ini, Made002CC6AE *nugget, int c, int d)
{
    MultiIniFieldParse m_fieldParse;
    m_fieldParse.add((const FieldParse *)Rva00507552Get(), 0);
    m_fieldParse.add(SpecialModelConditionFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(nugget, m_fieldParse);
}
