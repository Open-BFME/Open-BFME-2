// cl: /DNDEBUG /MD
//
// ?q4Notify002CCC2D@@YAXPAXPAVMade002CCC2D@@HH@Z @0x0050B8DB (77B).
// SpawnAndFadeNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00C64E70 with
// index 0, then INI initFromINIMulti. Caller parseSpawnAndFadeNugget
// at 0x002CCC72. Same two-add shape as q4Notify002CCBCA precedent.

class Made002CCC2D;

struct FieldParse;
extern const FieldParse SpawnAndFadeFieldTable;

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

void q4Notify002CCC2D(void *ini, Made002CCC2D *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&SpawnAndFadeFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
