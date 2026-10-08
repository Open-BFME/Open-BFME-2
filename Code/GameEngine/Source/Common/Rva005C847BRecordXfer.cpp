// cl: /O1 /EHsc /MD
// Native 0x005C90F1..0x005C9217, called by the rowed range wrapper
// HostClass005C815B::method_005C839B. Its established opaque spelling and
// two-int ABI are retained; the first argument is a transfer interface.
// Native accesses prove ref +8, word +44, byte +46 and low nibble +47.
// WB 0x01569E00 supplies a transfer algorithm lead, not a target class name.
// The exception identity comes from retail throw-info CFFD18 and its rowed
// constructor/copy/destructor, independently of that WB lead.
class OpaqueRefCounted { public: void Release_Ref(); };
struct BfmePoolHolder88 { char m_pad[0x88]; OpaqueRefCounted m_ref; };
class BfmePoolRef10
{
public:
    BfmePoolHolder88 *m_target;
    void rva00053D26(BfmePoolHolder88 *p);
};
struct OpaqueRefElement4
{
    OpaqueRefCounted *referent;
    __forceinline OpaqueRefElement4() : referent(0) {}
    __forceinline ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
};
class Rva0051D93
{
public:
    Rva0051D93(const OpaqueRefElement4 &, int);
private:
    char m_bytes[0x90];
};
class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tag;
};
class Xfer
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3C(); virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual void slot4C(); virtual void slot50();
    virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual void slot60(); virtual void slot64(); virtual void slot68();
    virtual void slot6C(); virtual void slot70(); virtual void slot74();
    virtual void slot78(); virtual void slot7C();
    virtual void slot80(unsigned short *);
    virtual void slot84();
    virtual void slot88(unsigned char *);
    virtual void slot8C();
    virtual void slot90(bool *);
};
class Rva002D9FD9Arg;
class Rva002D9FD9Owner { public: void rva002D9FD9(Rva002D9FD9Arg *); };
class HostClass005C8E0A { public: void method_005C9069(); };
struct Rva005C847BRecord
{
    int m_00, m_04;
    BfmePoolRef10 m_ref;
    char m_unknown0C[0x38];
    unsigned short m_44;
    unsigned char m_46;
    unsigned char m_low : 4;
    unsigned char m_high : 4;
    void method_005C90F1(int a0, int a1);
};
typedef char Verify005C847BRecord[(sizeof(Rva005C847BRecord) == 0x48) ? 1 : -1];

void Rva005C847BRecord::method_005C90F1(int a0, int)
{
    Xfer *xfer = (Xfer *)a0;
    bool hasRef = m_ref.m_target != 0;
    xfer->slot90(&hasRef);
    if (hasRef && !m_ref.m_target)
        m_ref.rva00053D26((BfmePoolHolder88 *)new Rva0051D93(OpaqueRefElement4(), 0));
    if (hasRef) {
        ((Rva002D9FD9Owner *)m_ref.m_target)->rva002D9FD9((Rva002D9FD9Arg *)xfer);
        ((HostClass005C8E0A *)this)->method_005C9069();
    }
    xfer->slot80(&m_44);
    xfer->slot88(&m_46);
    unsigned char count = m_low;
    xfer->slot88(&count);
    m_low = count;
    if (count != m_low)
        throw XferException(0, "Lock count does not fit into 4 bits");
}
