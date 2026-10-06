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
};

int Rva00318C79Owner::rva00318C79()
{
    Rva00318C32Ret* ret = rva00318C32();
    return ret ? ret->m_12c : -1;
}
