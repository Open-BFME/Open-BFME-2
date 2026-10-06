// cl: /DNDEBUG /MD
//
// ?q4Notify002CCCF3@@YAXPAXPAVMade002CCCF3@@HH@Z @0x0050BDED (71B).
// FireLogicNugget field parser: MultiIni tmp on stack, static
// buildFieldParse at 0x005088CE, add FieldParse table at 0x00865068
// with index 0, then INI initFromINIMulti. Caller parseFireLogicNugget
// at 0x002CCD38. Same tail as q4Notify002CCC90 precedent.

class Made002CCCF3;

struct FieldParse;
extern const FieldParse FireLogicFieldTable;

class MultiIniFieldParse
{
public:
    MultiIniFieldParse();
    void add(const FieldParse *p, unsigned int u);

    char m_pad[0x84];
};

class Rva005088CE
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
};

class INI
{
public:
    void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};

void q4Notify002CCCF3(void *ini, Made002CCCF3 *m, int c, int d)
{
    MultiIniFieldParse tmp;
    Rva005088CE::buildFieldParse(tmp);
    tmp.add(&FireLogicFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
