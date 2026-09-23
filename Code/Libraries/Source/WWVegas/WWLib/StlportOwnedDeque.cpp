// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME 1 STLport deque algorithms, instantiated for the target-supported 4-byte
// owning-reference element view; original class names are unknown. Its release and assignment members are defined in
// OpaqueRefOwnership.cpp; this TU provides the inline target-observed destructor.
#include <deque>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref();
private:
    long refs;
};
struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
template class _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> >;
