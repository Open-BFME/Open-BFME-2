// cl: /DNDEBUG /MD
//
// ?q4Notify002CC841@@YAXPAXPAVMade002CC841@@HH@Z @0x00509780 (77B).
// ProjectileNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864640 with
// index 0, then INI initFromINIMulti. Caller parseProjectileNugget
// at 0x002CC886. Same tail as q4Notify002CCBCA precedent.

class Made002CC841;

struct FieldParse;
extern const FieldParse ProjectileFieldTable;

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

void q4Notify002CC841(void *ini, Made002CC841 *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&ProjectileFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
