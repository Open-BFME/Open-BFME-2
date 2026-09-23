// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Cleanup for the record copied at2CF550: string at0 and shared owner at8.
// Tree erase256FB5 calls this body; original record identity is unknown.
class OpaqueRefCounted { public: virtual ~OpaqueRefCounted(); void Release_Ref(); };
class AsciiString { void *p; public: ~AsciiString(); };
class Rva002390CB {
    void *m_unknown;
    OpaqueRefCounted *m_owner;
public:
    ~Rva002390CB() { if (m_owner) m_owner->Release_Ref(); }
};
struct BfmeStringRecord002CF550 { AsciiString text; Rva002390CB ref; ~BfmeStringRecord002CF550(); };
BfmeStringRecord002CF550::~BfmeStringRecord002CF550() {}

typedef char RecordExtent[sizeof(BfmeStringRecord002CF550) == 12 ? 1 : -1];
