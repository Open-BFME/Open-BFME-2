// cl: /MD /D_CRTIMP= /DNDEBUG
// Target owning-reference view; original class names are unknown.
// The referent has a virtual destructor and an atomic LONG count at +4.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

class OpaqueRefCounted
{
public:
    virtual ~OpaqueRefCounted();
    void Add_Ref() { InterlockedIncrement(&refs); }
    bool rva00050EFA();
    void Release_Ref();
private:
    long refs;
};

// ?rva00050EFA@OpaqueRefCounted@@QAE_NXZ, retail 0x00050EFA, 31B.
// Atomically acquires a reference only while the prior count is positive;
// on a dead object it undoes the increment and returns false. Class identity
// and the count offset are established by the adjacent ownership methods.
bool OpaqueRefCounted::rva00050EFA()
{
    long count = InterlockedIncrement(&refs);
    if (count <= 1) {
        InterlockedDecrement(&refs);
        return false;
    }
    return true;
}

void OpaqueRefCounted::Release_Ref()
{
    if (InterlockedDecrement(&refs) <= 0)
        ::delete this;
}

struct OpaqueRefElement4
{
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4();
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
    OpaqueRefElement4 &rva00239057(const OpaqueRefElement4 *other);
};

OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
    if (this != &other) {
        if (other.referent)
            other.referent->Add_Ref();
        if (referent)
            referent->Release_Ref();
        referent = other.referent;
    }
    return *this;
}
OpaqueRefElement4 &OpaqueRefElement4::rva00239057(const OpaqueRefElement4 *other)
{
    if (other->referent)
        other->referent->Add_Ref();
    if (referent)
        referent->Release_Ref();
    referent = other->referent;
    return *this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva0050ED3@PoolMember@@QAEXXZ=?Release_Ref@OpaqueRefCounted@@QAEXXZ")
