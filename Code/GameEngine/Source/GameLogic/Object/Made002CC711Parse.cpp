// cl: /DNDEBUG /MD
//
// ?q4Notify002CC711@@YAXPAXPAVMade002CC711@@HH@Z @0x00508EBF (77B).
// ParalyzeNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864450 with
// index 0, then INI initFromINIMulti. Caller parseParalyzeNugget
// at 0x002CC756. Same tail.

class Made002CC711;

struct FieldParse;
extern const FieldParse ParalyzeFieldTable;

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

void q4Notify002CC711(void *ini, Made002CC711 *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&ParalyzeFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
