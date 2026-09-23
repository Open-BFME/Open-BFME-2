// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1BfmeStringTailRecord144@@UAE@XZ: 128B EH destructor of the 144-byte
// tail record at 0x2D9A43, reloc-named by the single-element Destroy call
// site in stlport_asciistring_record_bodies.cpp (that TU keeps its flat
// placeholder, so the vector Destroy path there still calls the dtor
// directly; the scalar-deleting-dtor at vtable slot0 0x2DA070 proves this
// destructor itself is virtual, hence the UAE spelling and the real vtable
// here). Layout cross-proven by the installing constructors at
// 0x2D97D6/0x2D982A/0x2D9893: AsciiString members at +0x04/+0x1C/+0x20/+0x84
// (each destroyed through the 0x36410 fold), two refcounted-pointer members
// released through the pinned PoolMember::Rva0050ED3 at 0x50ED3 (same
// spelling as Rva004E18A2Dtor.cpp), and ints elsewhere. The +0x10 member's
// release runs against pointee+0x88, hence the holder; the holder's own
// layout past the release slot is unproven. Destruction runs
// +0x84/+0x20/+0x1C/+0x10/+0x08/+0x04, plain reverse declaration order under
// an empty dtor body. Zero new pins.
template<class T> class StringBase {
    void *m_data;
    void releaseBuffer();
public:
    StringBase();
    StringBase(const StringBase &);
    StringBase &operator=(const StringBase &);
protected:
    __forceinline ~StringBase() { releaseBuffer(); }
};
class AsciiString : private StringBase<char> {
public:
    __forceinline AsciiString() {}
    __forceinline AsciiString(const AsciiString &o) : StringBase<char>(o) {}
    ~AsciiString();
    AsciiString &operator=(const AsciiString &);
};
class PoolMember
{
public:
    void Rva0050ED3();
};
struct BfmePoolHolder88
{
    unsigned char m_pad[0x88];
    PoolMember m_ref;
};
class BfmePoolRef08
{
    PoolMember *m_target;
public:
    __forceinline ~BfmePoolRef08() { if (m_target != 0) m_target->Rva0050ED3(); }
};
class BfmePoolRef10
{
    BfmePoolHolder88 *m_target;
public:
    __forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Rva0050ED3(); }
};
struct BfmeStringTailRecord144
{
    virtual ~BfmeStringTailRecord144();
    AsciiString m_string04;
    BfmePoolRef08 m_pool08;
    int m_int0C;
    BfmePoolRef10 m_pool10;
    int m_int14;
    int m_int18;
    AsciiString m_string1C;
    AsciiString m_string20;
    int m_data[24];
    AsciiString m_string84;
    int m_tail[2];
};
// ??1BfmeStringTailRecord144@@UAE@XZ
BfmeStringTailRecord144::~BfmeStringTailRecord144()
{
}
