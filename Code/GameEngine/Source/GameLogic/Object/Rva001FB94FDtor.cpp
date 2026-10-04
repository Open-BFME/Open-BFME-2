// cl: /O1 /MD
// ??1Rva001FB94F@@QAE@XZ @0x001FB94F 59B
// Non-virtual dtor with EH prolog: second base Sub005CD540Outer at +4 then
// inlined first-base cleanup calling rowed rva001F4206. Evidence: null-checked
// this+4 adjustment proves second base (BigChainBaseDtors donor comment);
// callees rowed 0x001FA95A SubOuter and 0x001F4206 rva001F4206; caller
// 0x001FBAEE becomes ready; neighbours Rva001FA584Ctor/Rva001FB912Init /O1 /MD;
// honest Rva names; probe p2/p3 byte-exact.
class Rva001F4206
{
public:
    void rva001F4206();
};
class Sub005CD540Outer
{
public:
    ~Sub005CD540Outer();
};
class Rva001FB94FFirst
{
public:
    int m_00;
    ~Rva001FB94FFirst();
};
// ??1Rva001FB94FFirst@@QAE@XZ present-unmatched
inline Rva001FB94FFirst::~Rva001FB94FFirst()
{
    ((Rva001F4206 *)this)->rva001F4206();
}
class Rva001FB94F : public Rva001FB94FFirst, public Sub005CD540Outer
{
public:
    ~Rva001FB94F();
};
Rva001FB94F::~Rva001FB94F()
{
}
class Rva001FBAEE : public Rva001FB94FFirst, public Rva001FB94F
{
public:
    ~Rva001FBAEE();
};
Rva001FBAEE::~Rva001FBAEE()
{
}
