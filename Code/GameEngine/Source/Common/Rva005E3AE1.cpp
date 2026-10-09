// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native5E3AE1..5E3B1A57B constructs the second interface's primary vptr,
// vbptr4 and shared virtual counted base8. Destructor5F4AA3..5F4AB922B
// receives the fixed standalone virtual-base bias8 and restores the same pair.
// Parent5E4F6D and teardown5E5018 independently establish this constructor
// and destructor ABI. Replaces the former manually written vptr helper views.
struct RvaSmallVtableZeroBase { void *m_04; };
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
    Rva0007DF07() { m_04 = 0; }
    virtual ~Rva0007DF07() {}
};
class Rva005E3AE1 : public virtual Rva0007DF07
{
public:
    Rva005E3AE1();
    virtual void slot0() = 0;
    virtual ~Rva005E3AE1();
};

Rva005E3AE1::Rva005E3AE1() {}
Rva005E3AE1::~Rva005E3AE1() {}
