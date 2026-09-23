// cl: /O1 /MD /D_CRTIMP= /DNDEBUG
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
