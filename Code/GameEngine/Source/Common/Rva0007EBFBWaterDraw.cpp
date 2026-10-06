// cl: /EHsc /MD
// ??0Rva0007EBFB@@QAE@XZ @0x0007EBFB 73B WaterDraw registering ctor with vtable plus two members.
// Evidence: stores 0x007C6F80/5C/64 then Register WaterDraw; empty base arms EH state 0. Precedents Rva000E6350Ctor.cpp Rva0018BEC7Ctor.cpp.
void __cdecl Rva00153565Register(const char *name, void *obj);

class Rva0007EBFB_EmptyBase {
public:
    Rva0007EBFB_EmptyBase() {}
    ~Rva0007EBFB_EmptyBase();
};

class Rva0007EBFB_Member0 {
public:
    virtual ~Rva0007EBFB_Member0();
};

class Rva0007EBFB_Member1 {
public:
    virtual ~Rva0007EBFB_Member1();
};

class Rva0007EBFB : public Rva0007EBFB_EmptyBase {
public:
    virtual ~Rva0007EBFB();
    Rva0007EBFB();
    Rva0007EBFB_Member0 m_04;
    Rva0007EBFB_Member1 m_08;
};

Rva0007EBFB::Rva0007EBFB()
{
    Rva00153565Register("WaterDraw", this);
}
