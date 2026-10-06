// cl: /DNDEBUG /MD
//
// ?q4Notify002CC6AE@@YAXPAXPAVMade002CC6AE@@HH@Z @0x00508D2F (77B).
// SpecialModelConditionNugget field parser: MultiIni tmp, add table
// from getter 0x00507552 with index 0, add FieldParse table at
// 0x008643D4 with index 0, then INI initFromINIMulti. Caller
// parseSpecialModelConditionNugget at 0x002CC6F3. Same tail.

class Made002CC6AE;

struct FieldParse;
extern const FieldParse SpecialModelConditionFieldTable;

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

void q4Notify002CC6AE(void *ini, Made002CC6AE *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&SpecialModelConditionFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
