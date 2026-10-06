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
    void Release_Ref();
private:
    long refs;
};

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
#pragma comment(linker, "/alternatename:?assign@Rva0036CA00Str@@QAEXABV1@@Z=??4OpaqueRefElement4@@QAEAAU0@ABU0@@Z")
#pragma comment(linker, "/alternatename:?Rva0050ED3@PoolMember@@QAEXXZ=?Release_Ref@OpaqueRefCounted@@QAEXXZ")
