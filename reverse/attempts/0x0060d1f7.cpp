// ??0XferSave@@QAE@XZ
// partial score=1.0 date=2026-10-04
// cl: /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// Target body evidence for the XferSave destructor at 0x0060D0B3/87B: the
// matched scalar deleting wrapper calls it and installs vtable 0x00C7B010.
// Matched XferEnum/endBlock bodies establish m_stream +4, flag +8 and
// vector start/end at +0x0C/+0x10. Target constructor 0x0060D1F7 calls the
// empty vector-base constructor at +0x0C; capacity at +0x14 is inferred from
// that layout. Target constructor and destructor bytes establish two further
// subobjects at +0x18 and +0x2C; their types stay
// opaque and their helper identities are address-named. The dtor frees the
// vector start and the final vptr 0x00BBB910 is established by rowed Xfer
// ctor/dtor at 0x53DE/0x53E7.
// Structural inference: this models the destructor as a derived Xfer object.
// The XferSave class spelling is carried by the existing wrapper and remains
// donor-derived rather than a target-proven class name.

// ??_GXferSave@@UAEPAXI@Z @0x0060D24D 28B: slot 0 of vtable 0x00C7B010; calls ??1 at 0x0060D0B3.
// Owner evidence (audited 2026-09-26): BFME1 reconstructed donor slots 6/38 at RVAs 0x0060CA26/0x0060C935 implement save-side block finalization and stream writes; ctor/dtor RVAs 0x0060D1F7/0x0060D0B3 share this primary vptr; class spelling remains donor-derived.
class Rva00BBB910Base { public: virtual ~Rva00BBB910Base() {} };
extern "C" void __cdecl free(void *);
struct BfmePositionAllocator { BfmePositionAllocator() {} };
struct BfmePositionVectorBase {
    BfmePositionVectorBase(const BfmePositionAllocator &);
    int *m_begin;
    int *m_end;
    int *m_capacity;
};
struct BfmePositionVector : public BfmePositionVectorBase {
    __forceinline BfmePositionVector() : BfmePositionVectorBase(BfmePositionAllocator()) {}
    __forceinline ~BfmePositionVector() { if (m_begin) free(m_begin); }
};
struct Rva0060D031Member { unsigned int opaque[5]; Rva0060D031Member(); __declspec(noinline) ~Rva0060D031Member(); };
struct Rva0060CC99Member { unsigned int opaque[5]; Rva0060CC99Member(); __declspec(noinline) ~Rva0060CC99Member(); };
class XferSave : public Rva00BBB910Base {
public:
    XferSave();
    __declspec(noinline) virtual ~XferSave();
private:
    void * volatile m_stream;
    bool m_flag;
    unsigned char m_pad[3];
    BfmePositionVector m_positions;
    Rva0060D031Member m_at18;
    Rva0060CC99Member m_at2c;
};
XferSave::~XferSave() {}
void XferSave_Delete(XferSave *p) { delete p; }

// BFME1 donor1281192f68 BfmeConv881/O1; Ghidra0060D1F7/86B.
// Target vptrC7B010 matches the existing ctor/dtor/wrapper ownership audit;
// member construction at+C,+18,+2C and zero stores+4/+8 are target facts.
// Opaque member initializer0060D06A/31B remains pending recovery.
XferSave::XferSave() : m_stream(0), m_flag(false) {}
