// cl: /O1
// ?rva005EB87A@Rva005EB87A@@QAE_NXZ @0x005EB87A 21B
// Predicate returning field08 neither 0 nor 4. Evidence: callers 0x005CFFE8 0x005CFF0F 0x005D1129 test al; no callees.
struct Rva005EB87AInner {
    char m_pad[8];
    int m_field08;
};
class Rva005EB87A {
public:
    Rva005EB87AInner *m_ptr;
    bool rva005EB87A();
};
bool Rva005EB87A::rva005EB87A()
{
    int v = m_ptr->m_field08;
    return v != 0 && v != 4;
}
