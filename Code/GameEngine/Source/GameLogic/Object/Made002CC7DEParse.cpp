// cl: /DNDEBUG /MD
//
// ?q4Notify002CC7DE@@YAXPAXPAVMade002CC7DE@@HH@Z @0x005095AE (77B).
// WeaponOCLNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864568 with
// index 0, then INI initFromINIMulti. Caller parseWeaponOCLNugget
// at 0x002CC823. Same tail as q4Notify002CCBCA precedent.

class Made002CC7DE;

struct FieldParse;
extern const FieldParse WeaponOCLFieldTable;

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

void q4Notify002CC7DE(void *ini, Made002CC7DE *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&WeaponOCLFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
