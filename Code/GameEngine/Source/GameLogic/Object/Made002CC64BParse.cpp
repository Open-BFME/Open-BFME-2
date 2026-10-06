// cl: /DNDEBUG /MD
//
// ?q4Notify002CC64B@@YAXPAXPAVMade002CC64B@@HH@Z @0x0050893A (77B).
// AttributeModifierNugget field parser: MultiIni tmp, add table from
// getter 0x00507552 with index 0, add FieldParse table at 0x00864300
// with index 0, then INI initFromINIMulti. Caller
// parseAttributeModifierNugget at 0x002CC690. Same tail as precedent.

class Made002CC64B;

struct FieldParse;
extern const FieldParse AttributeModifierFieldTable;

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

void q4Notify002CC64B(void *ini, Made002CC64B *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&AttributeModifierFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
