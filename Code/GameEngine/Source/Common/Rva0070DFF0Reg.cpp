// cl: /MD /EHsc
// ?rva0070DFF0@Rva0070DFF0@@QAEXPAVRva8D0D80Value@@E@Z @0x0070DFF0 107B
// Evidence: EH frame with EAStringC "__INTERFACEs__" local; Table::add pin 0x0070B410
// via this+8; byte flag at this+0x1C from second arg; ret 8 (Value* + uchar);
// caller at 0x0070731F; Table size 0x14 puts flag at +0x1C.
class EAStringC {
public:
    EAStringC(const char *s);
    ~EAStringC();
};
class Rva8D0D80String;
class Rva8D0D80Value;

class Rva8D0D80Table {
    char data[0x14];
public:
    void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

class Rva0070DFF0 {
    char m_pad[8];
    Rva8D0D80Table m_table;
    unsigned char m_flag;
public:
    void rva0070DFF0(Rva8D0D80Value *v, unsigned char b);
};

void Rva0070DFF0::rva0070DFF0(Rva8D0D80Value *v, unsigned char b)
{
    EAStringC name("__INTERFACEs__");
    m_table.add((Rva8D0D80String *)&name, v);
    m_flag = b;
}
