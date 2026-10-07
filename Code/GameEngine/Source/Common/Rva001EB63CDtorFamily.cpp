// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// EH dtor at 0x00502D03 destroys its three members in reverse declaration
// order: +0x1C, +0x10, then +0x04. Their destructor bodies are rowed elsewhere.
class Rva004FF630Member
{
public:
    ~Rva004FF630Member();
private:
    unsigned char m_pad[4];
};

class Rva00502D48
{
public:
    Rva00502D48();
    ~Rva00502D48();
private:
    char m_opaque[0x0C];
};

class Rva004FFE96
{
public:
    Rva004FFE96();
    ~Rva004FFE96();
private:
    char m_opaque[0x0C];
};

class Rva00502D03
{
public:
    ~Rva00502D03();
private:
    unsigned char m_pad00[0x04];
    Rva00502D48 m_member04;
    Rva004FFE96 m_member10;
    Rva004FF630Member m_member1C;
};

Rva00502D03::~Rva00502D03()
{
}
