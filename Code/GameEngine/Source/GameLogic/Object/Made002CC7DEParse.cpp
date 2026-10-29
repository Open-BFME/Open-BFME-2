// cl: /DNDEBUG /MD
//
// ?q4Notify002CC7DE@@YAXPAXPAVMade002CC7DE@@HH@Z @0x005095AE (77B).
// WeaponOCLNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864568 with
// index 0, then INI initFromINIMulti. Caller parseWeaponOCLNugget
// at 0x002CC823. Same tail as q4Notify002CCBCA precedent.

class Made002CC7DE;

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
};

// The table pushed at 0x00C64568 (.rdata): 1 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x12C-0x12C. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse WeaponOCLFieldTable[] =
{
    { "WeaponOCLName", &INI::parseAsciiString,  0, 0x12C },
    { 0, 0, 0, 0 }
};

void q4Notify002CC7DE(void *ini, Made002CC7DE *m, int c, int d)
{
    MultiIniFieldParse m_fieldParse;
    m_fieldParse.add((const FieldParse *)Rva00507552Get(), 0);
    m_fieldParse.add(WeaponOCLFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, m_fieldParse);
}
