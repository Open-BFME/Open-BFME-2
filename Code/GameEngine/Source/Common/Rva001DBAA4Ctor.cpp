// cl: /MD
// ??0Rva001DBAA4@@QAE@XZ @ 0x001DBAA4 31B: opaque base ctor for Rva001DBAC3 family.
// Vtable 0x007DBC10 shared with base dtor 0x001DBAC3; 12 callers in 0x0035Dxxx-0x0035Fxxx
// (e.g. 0x0035E2E9) call it first as base construct; member init +4=1 +8=0 +9=1 +0xA=0 +0xC=0.
// Identity unproven so address-derived name; TU beside FamilyTailDtors1DBAC3.cpp.
class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    int m_C;
};
Rva001DBAA4::Rva001DBAA4() : m_4(1), m_8(false), m_9(true), m_A(false), m_C(0) {}

// Native destructor 0x001DBAC3 reinstalls the same 0x007DBC10 vptr as
// the verified constructor and deleting destructor. The caller at 0x003603D4
// tail-destroys this base after restoring its derived vptr; keep the opaque
// class identity and emit its real destructor rather than a setter alias.
Rva001DBAA4::~Rva001DBAA4() {}
