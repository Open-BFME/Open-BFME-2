// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Cleanup for the record copied at2CF550: string at0 and shared owner at8.
// Tree erase256FB5 calls this body; original record identity is unknown.
class OpaqueRefCounted { public: virtual ~OpaqueRefCounted(); void Release_Ref(); };
template <class T> class StringBase
{
	friend class AsciiString;
	void releaseBuffer();
public:
	void *p;
};
class AsciiString : public StringBase<char>
{
public:
	~AsciiString() { releaseBuffer(); }
};
class Rva002390CB {
    void *m_unknown;
    OpaqueRefCounted *m_owner;
public:
    ~Rva002390CB() { if (m_owner) m_owner->Release_Ref(); }
};
struct BfmeStringRecord002CF550 { AsciiString text; Rva002390CB ref; ~BfmeStringRecord002CF550(); };
inline BfmeStringRecord002CF550::~BfmeStringRecord002CF550() {}

typedef char RecordExtent[sizeof(BfmeStringRecord002CF550) == 12 ? 1 : -1];

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeStringRecord002CF550InlineAnchor@@YAXPAVBfmeStringRecord002CF550@@@Z absent-from-retail
void _bfmeBfmeStringRecord002CF550InlineAnchor(BfmeStringRecord002CF550 *p)
{
    p->BfmeStringRecord002CF550::~BfmeStringRecord002CF550();
}
#pragma inline_depth()

// ??1BfmeStringRecord0033B1DE@@QAE@XZ, retail 0x0033B1DE, 57 bytes: the same
// cleanup (owner reference released, then the string) for another record of this
// layout. Only the EH handler record differs from ~BfmeStringRecord002CF550's
// bytes. No other unit emits it, so it is defined plainly. Identity unknown.
struct BfmeStringRecord0033B1DE { AsciiString text; Rva002390CB ref; ~BfmeStringRecord0033B1DE(); };
BfmeStringRecord0033B1DE::~BfmeStringRecord0033B1DE() {}
