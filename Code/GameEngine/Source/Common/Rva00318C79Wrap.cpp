// cl: /DNDEBUG /MD /EHsc
// Reconstruction of the 20B wrapper at 0x00318C79: call the sibling
// 0x00318C32 body (pinned from the retail call), return its +0x12C word,
// or -1 when it returns null. All names are address-derived.
class Rva00318C32Ret {
public:
    unsigned char pad00[0x12C];
    int m_12c;
};

class Rva00318C79Owner {
public:
    Rva00318C32Ret* rva00318C32();
    int rva00318C79();
    int rva00318F8B();
private:
    char m_pad00[0x2C];
    int m_2c;
    int m_30;
};

int Rva00318C79Owner::rva00318C79()
{
    Rva00318C32Ret* ret = rva00318C32();
    return ret ? ret->m_12c : -1;
}

// ?rva00318F8B@Rva00318C79Owner@@QAEHXZ, retail 0x00318F8B (22B): returns +0x30 when the
// wrapper value 0x00318C79 equals +0x2C, else 0. Address-derived name.
int Rva00318C79Owner::rva00318F8B()
{
    return m_2c == rva00318C79() ? m_30 : 0;
}
