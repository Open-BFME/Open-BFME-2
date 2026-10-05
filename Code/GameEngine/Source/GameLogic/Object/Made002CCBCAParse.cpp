// cl: /O1 /DNDEBUG /MD
//
// ?q4Notify002CCBCA@@YAXPAXPAVMade002CCBCA@@HH@Z @0x0050B6F8 (77B).
// HordeAttackNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864DCC with
// index 0, then INI initFromINIMulti. Caller parseHordeAttackNugget
// at 0x002CCC0F. Same tail as q4Notify002CCCF3 precedent.

class Made002CCBCA;

struct FieldParse;
extern const FieldParse g_00864DCC;

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

void q4Notify002CCBCA(void *ini, Made002CCBCA *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&g_00864DCC, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
