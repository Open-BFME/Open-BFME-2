// cl: /EHsc /MD
// ??0Rva0018BEC7@@QAE@XZ, retail 0x0018BEC7, 66 bytes.
// Ctor registering "WW3D" via rowed Rva00153565Register; vtable at +0 plus member vtable at +4.
// Evidence: disassembly stores 0x007D5BE4/0x007D5BD4 then calls Register("WW3D", this);
// caller 0x0017414B; empty base arms EH state 0, member with dtor gives state 1.
void __cdecl Rva00153565Register(const char *name, void *obj);

class Rva0018BEC7_EmptyBase {
public:
    Rva0018BEC7_EmptyBase() {}
    ~Rva0018BEC7_EmptyBase();
};

class Rva0018BEC7_Member {
public:
    virtual ~Rva0018BEC7_Member();
};

class Rva0018BEC7 : public Rva0018BEC7_EmptyBase {
public:
    virtual ~Rva0018BEC7();
    Rva0018BEC7();
    Rva0018BEC7_Member m_member;
};

Rva0018BEC7::Rva0018BEC7()
{
    Rva00153565Register("WW3D", this);
}
