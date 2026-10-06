// cl: /DNDEBUG /MD
//
// ?q4Notify002CC774@@YAXPAXPAVMade002CC774@@HH@Z @0x00509379 (77B).
// DamageFieldNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x008644F0 with
// index 0, then INI initFromINIMulti. Caller parseDamageFieldNugget
// at 0x002CC7B9. Same tail as q4Notify002CCBCA precedent.

class Made002CC774;

struct FieldParse;
extern const FieldParse DamageFieldTable;

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

void q4Notify002CC774(void *ini, Made002CC774 *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&DamageFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
