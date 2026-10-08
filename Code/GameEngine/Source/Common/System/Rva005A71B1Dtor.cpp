// cl: /EHs /MD

// ??1Rva005A71B1@@UAE@XZ @0x005A71B1 79B: dtor stores vtable 0x00871BF8,
// destroys 0x40-element array at +0x218 via ehvec dtor, frees ptr at +4 via
// _free 0x00030830. Element dtor pointer is 0x005A66B8. Unblocks ??_G at
// 0x005A7200 and 0x005A734B.

extern "C" void __cdecl free(void *block);

class Rva005A66B8Elem
{
public:
    virtual ~Rva005A66B8Elem() {}
private:
    int m_pad[4];
};

class Rva005A71B1Base
{
public:
    ~Rva005A71B1Base() { if (m_ptr) free(m_ptr); }
protected:
    char *m_ptr;
};

class Rva005A71B1 : public Rva005A71B1Base
{
public:
    Rva005A71B1();
    virtual ~Rva005A71B1();
private:
    unsigned char m_pad[0x210];
    Rva005A66B8Elem m_arr[0x40];
};

Rva005A71B1::~Rva005A71B1()
{
}

// 0x005A734B 119B: dtor stores vtable 0x00871BFC, frees 8 pointers at +0x90C
// via operator delete 0x0002FD60, destroys global at 0x00A063B0 via slot0
// with 0 then deletes and nulls it, then destroys Rva005A71B1 at +0x28 via
// rowed 0x005A71B1. Unblocks ??_G at 0x005A73C2.
void __cdecl operator delete(void *block);

struct Rva00A063B0Obj
{
    virtual void *Unknown00(int x);
};

// Named provider: AptOptions::RefreshNat independently accesses this same
// VA 0x00E063B0 as TheFirewallHelper. Preserve the observed slot ABI below.
class FirewallHelperClass;
extern FirewallHelperClass *TheFirewallHelper;

struct Rva005A721CSlot
{
    Rva005A721CSlot() : m_00(0), m_04(0) {}
    int m_00;
    unsigned short m_04;
};
class FirewallHelperClass;
FirewallHelperClass *Rva00595143Get();
void *__cdecl operator new(unsigned int size);

class Rva005A734B
{
public:
    Rva005A734B();
    virtual ~Rva005A734B();
private:
    int m_04, m_08, m_0C, m_10, m_14, m_18, m_1C, m_20;
    bool m_24, m_25;
    Rva005A71B1 m_mid;
    unsigned char m_mid2[0x8E4 - 0x740];
    bool m_8E4[8];
    int m_8EC[8];
    void *m_ptrs[8];
    int m_92C, m_930;
    unsigned short m_934, m_936;
    int m_938, m_93C;
    unsigned short m_940;
    bool m_942, m_943;
    int m_944, m_948, m_94C, m_950, m_954;
    unsigned short m_958;
    int m_95C, m_960, m_964, m_968, m_96C;
    bool m_970;
};

Rva005A734B::~Rva005A734B()
{
    for (int i = 0; i < 8; i++) {
        if (m_ptrs[i])
            operator delete(m_ptrs[i]);
    }
    if (TheFirewallHelper) {
        void *q = reinterpret_cast<Rva00A063B0Obj *>(TheFirewallHelper)->Unknown00(0);
        operator delete(q);
        TheFirewallHelper = 0;
    }
}

// Native 0x005A721C..0x005A734B RET0. WB0x014DA470 has the same
// initializer/store sequence, embedded +0x28 constructor, eight-slot loop
// and firewall factory; its NAT::NAT debug string is a name lead. Zero Hour
// NAT.cpp differs in transport ownership and initialization order, so the
// target supplies every field extent and value below. Existing destructor
// rows prove the owner vtable and embedded/array offsets, not a NAT rename.
Rva005A734B::Rva005A734B()
    : m_04(0), m_08(0), m_0C(8), m_10(0), m_14(0), m_18(0),
      m_1C(0), m_20(0), m_24(false), m_25(false)
{
    m_92C = 0;
    m_930 = 10;
    m_934 = 0x7F00;
    m_936 = 0;
    m_938 = 0;
    m_93C = 0;
    m_940 = 0;
    m_942 = false;
    m_943 = false;
    m_944 = 0;
    m_948 = 0;
    m_94C = 0;
    m_950 = 0;
    m_954 = 0;
    m_958 = 0;
    m_95C = 0;
    m_960 = 0;
    m_964 = 0;
    m_968 = 0;
    m_96C = 0;
    m_970 = true;
    for (int i = 0; i < 8; ++i)
    {
        m_8E4[i] = false;
        m_8EC[i] = 0;
        m_ptrs[i] = new Rva005A721CSlot;
    }
    if (!TheFirewallHelper)
        TheFirewallHelper = Rva00595143Get();
}
