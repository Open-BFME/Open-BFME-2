// cl: /DNDEBUG /MD
//
// ?q4Notify002CC8A4@@YAXPAXPAVMade002CC8A4@@HH@Z @0x00509DAB (77B).
// Field parser: MultiIni tmp, add table from getter 0x00507552
// with index 0, add FieldParse table at 0x00864810 with index 0,
// then INI initFromINIMulti. Same tail as q4Notify002CCBCA precedent.

class Made002CC8A4;

struct FieldParse;
extern const FieldParse FieldTable002CC8A4;

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

void q4Notify002CC8A4(void *ini, Made002CC8A4 *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(&FieldTable002CC8A4, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
