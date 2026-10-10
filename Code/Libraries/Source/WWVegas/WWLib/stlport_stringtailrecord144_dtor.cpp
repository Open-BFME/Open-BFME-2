// cl: /Ireference/shims/bfme2_ascii /arch:SSE /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include "ascii_string.h"
class OpaqueRefCounted
{
public:
	void Release_Ref();
};
typedef long Long;
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(Long volatile *addend);
struct BfmePoolHolder88
{
    unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};
class BfmePoolRef08
{
	OpaqueRefCounted *m_target;
public:
	__forceinline ~BfmePoolRef08() { if (m_target != 0) m_target->Release_Ref(); }
};
class BfmePoolRef10
{
    BfmePoolHolder88 *m_target;
public:
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
    BfmePoolRef10(BfmePoolHolder88 *p);
    BfmePoolRef10(const BfmePoolRef10 &other);
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva000519BD();
    void rva00053D26(BfmePoolHolder88 *p);
};
struct OpaqueRefElement4 { OpaqueRefCounted *referent; OpaqueRefElement4 &operator=(const OpaqueRefElement4 &); };
class Rva000A8C9B { public: void clear(); };
struct BfmeEventPositionView {
    float x,y,z;
    // ?BfmeEventPositionView::zero present-unmatched
    __forceinline void zero() { x=0.0f; y=0.0f; z=0.0f; }
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
    float m_f24;
    float m_f28;
    float m_f2C;
    int m_int30;
    int m_int34;
    int m_int38;
    BfmeEventPositionView m_position;
    unsigned char m_b48;
    unsigned char m_b49;
    unsigned char m_b4A;
    unsigned char m_b4B;
    unsigned char m_b4C;
    unsigned char m_b4D;
    unsigned char m_b4E;
    unsigned char m_b4F;
    unsigned char m_b50;
    unsigned char m_b51;
    unsigned char m_b52;
    unsigned char m_b53;
    float m_f54;
    float m_f58;
    float m_f5C;
    float m_f60;
    float m_f64;
    int m_int68;
    int m_int6C;
    int m_int70;
    int m_int74;
    int m_int78;
    int m_int7C;
    int m_int80;
    AsciiString m_string84;
    int m_tail[2];
    void rva002D96D3(const OpaqueRefElement4 &);
};
typedef char VerifyRecordSize[(sizeof(BfmeStringTailRecord144) == 0x90) ? 1 : -1];

// ??1BfmeStringTailRecord144@@UAE@XZ
BfmeStringTailRecord144::~BfmeStringTailRecord144()
{
}
// ??0BfmePoolRef10@@QAE@PAUBfmePoolHolder88@@@Z 0x00051931 31B raw ctor via InterlockedIncrement on holder+0x8c; 2 callers at 0x528A9/0x56A78F; same shape as AudioEventInfoRef ctor at 0x51914 with +0x8c offset
BfmePoolRef10::BfmePoolRef10(BfmePoolHolder88 *p) : m_target(p)
{
    if (m_target)
        InterlockedIncrement((Long *)((char *)m_target + 0x8c));
}
// ??0BfmePoolRef10@@QAE@ABV0@@Z 0x00051950 33B copy ctor via InterlockedIncrement on holder+0x8c; 9 callers incl 0x519F1/0x51C7E; double-deref of source ref
BfmePoolRef10::BfmePoolRef10(const BfmePoolRef10 &other) : m_target(other.m_target)
{
    if (m_target)
        InterlockedIncrement((Long *)((char *)m_target + 0x8c));
}
// Assignment's verified 0x00051971 provider lives in HostClass005C908B.cpp,
// whose caller needs the full visible noinline body for VC7.1 alias analysis.
// ?rva000519BD@BfmePoolRef10@@QAEXXZ 0x000519BD 25B release via pinned 0x50ED3 then and-zero; 7 callers incl 0x53D32/0x599FD/0x2D97C7; address-derived clear on BfmePoolRef10 (dtor already rowed at 0x519AB)
void BfmePoolRef10::rva000519BD()
{
    if (m_target) {
			m_target->m_ref.Release_Ref();
        m_target = 0;
    }
}
// ?rva00053D26@BfmePoolRef10@@QAEXPAUBfmePoolHolder88@@@Z 0x00053D26 41B assign from raw holder via clear at 0x519BD then InterlockedIncrement on holder+0x8c; 10 callers incl 0x59943/0x5B2E9; same family as ctors above
void BfmePoolRef10::rva00053D26(BfmePoolHolder88 *p)
{
    if (p != m_target) {
        rva000519BD();
        m_target = p;
        if (p)
            InterlockedIncrement((Long *)((char *)p + 0x8c));
    }
}

// Common-prefix initializer at 0x002D96D3; native boundary ends at 0x002D97D6.
// Reference lead: GeneralsMD Common/Audio/AudioEventRTS.cpp and its header,
// supplied by open-bfme-1 revision 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// The reference supplies the three-float position and initialization purpose;
// target stores establish each offset and literal. Original field names remain
// unasserted. Canonical AsciiString and existing pool workers supply cleanup.
// Calls at 0x002D97D6 and the radar notification at 0x002AA9C2 use a 0x88-byte
// prefix. The separate vector copy at 0x00051B40 appends a word at +0x88 and
// a byte at +0x8C; allocator 0x00051A79 proves its 0x90-byte wrapper stride.
// This method neither allocates a record nor accesses the wrapper tail.
void BfmeStringTailRecord144::rva002D96D3(const OpaqueRefElement4 &arg)
{
    m_f24 = -1.0f;
    m_f28 = -1.0f;
    m_f2C = 1.0f;
    m_position.zero();

    m_b48 = 0;
    m_int38 = 6;
    m_int30 = 0;
    m_b49 = 0;
    m_string04 = AsciiString::TheEmptyString;
    Rva000A8C9B &holder = *reinterpret_cast<Rva000A8C9B *>(&m_pool08);
    holder.clear();
    m_int68 = -1;
    m_int6C = -1;
    m_f54 = 1.0f;
    m_f58 = 1.0f;
    m_f5C = 1.0f;
    m_f60 = 1.0f;
    m_int0C = 0;
    m_int18 = 0;
    m_f64 = 0.0f;
    m_b4A = 0;
    m_b4B = 0;
    m_b4C = 0;
    m_b4D = 1;
    m_b4E = 0;
    m_b4F = 0;
    m_b50 = 0;
    m_b51 = 0;
    m_b52 = 0;
    m_b53 = 0;
    m_int74 = 0;
    reinterpret_cast<StringBase<char> *>(&m_string1C)->clear();
    reinterpret_cast<StringBase<char> *>(&m_string20)->clear();
    m_int78 = 1;
    reinterpret_cast<StringBase<char> *>(&m_string84)->clear();
    m_int7C = -12345;
    reinterpret_cast<OpaqueRefElement4&>(holder) = arg;
    m_int70 = -1;
    m_int80 = 1;
    m_pool10.rva000519BD();
    m_int14 = 0;
}


