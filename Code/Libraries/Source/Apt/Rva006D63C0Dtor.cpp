// cl: /DNDEBUG /MD /EHsc
// ??1Rva006D63C0@@QAE@XZ @0x006D63C0 76B. Dtor with hash member at +8 plus base 0x006DE350.
// Evidence: calls pinned ??1Rva0070A840@@QAE@XZ (0x0070A840) then rowed ??1Rva006DE350@@UAE@XZ (0x006DE350);
// 2 derived 11B virtual dtors tail-call it (0x006DE2B0 0x006DE6C0); EH handler 0x007A8838; gap same flags.
// Composition (no vptr store) to match 76B retail; virtual pin opaque unproven.
class Rva0070A840
{
public:
    ~Rva0070A840();
};
struct Rva006DE350
{
    virtual ~Rva006DE350();
    unsigned int m_flags;
};
struct Rva006D63C0
{
    Rva006DE350 m_base;
    Rva0070A840 m_hash;
    ~Rva006D63C0();
};
Rva006D63C0::~Rva006D63C0()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva006D63C0@@UAE@XZ=??1Rva006D63C0@@QAE@XZ")
