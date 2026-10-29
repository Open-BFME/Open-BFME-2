// cl: /DNDEBUG /MD
//
// ?q4Notify002CC774@@YAXPAXPAVMade002CC774@@HH@Z @0x00509379 (77B).
// DamageFieldNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x008644F0 with
// index 0, then INI initFromINIMulti. Caller parseDamageFieldNugget
// at 0x002CC7B9. Same tail as q4Notify002CCBCA precedent.

class Made002CC774;

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
    static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

// The table pushed at 0x00C644F0 (.rdata): 2 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x12C-0x130. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse DamageFieldTable[] =
{
    { "WeaponTemplateName", &INI::parseAsciiString,          0, 0x130 },
    { "Duration",           &INI::parseDurationUnsignedInt,  0, 0x12C },
    { 0, 0, 0, 0 }
};

void q4Notify002CC774(void *ini, Made002CC774 *nugget, int c, int d)
{
    MultiIniFieldParse m_fieldParse;
    m_fieldParse.add((const FieldParse *)Rva00507552Get(), 0);
    m_fieldParse.add(DamageFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(nugget, m_fieldParse);
}
