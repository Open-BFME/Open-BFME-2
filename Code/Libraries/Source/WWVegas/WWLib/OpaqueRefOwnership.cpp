// cl: /MD /D_CRTIMP= /DNDEBUG
// platformsdk
// Target owning-reference view; original class names are unknown.
// The referent has a virtual destructor and an atomic LONG count at +4.

#include <windows.h>

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

struct OpaqueRefElement4
{
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4();
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
    OpaqueRefElement4 &rva00239057(const OpaqueRefElement4 *other);
};

// Select-any like MilesAudioIsMusicAlreadyLoaded.cpp's identical copy (an
// exclusive definition would duplicate it at link time); nothing here calls
// it, so the anchor after it keeps the noinline body emitted.
inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
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
// ?bfmeAnchorOpaqueRefElement4Assign absent-from-retail
OpaqueRefElement4 &bfmeAnchorOpaqueRefElement4Assign(OpaqueRefElement4 *to, const OpaqueRefElement4 &from)
{
    return *to = from;
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
