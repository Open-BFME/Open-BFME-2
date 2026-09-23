// cl: /O1 /MD /D_CRTIMP= /DNDEBUG
// Target cleanup for the shared-reference member at +4; original type unknown.
class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Release_Ref();
private:
    long refs;
};
class Rva002390CB {
    void *unknown00;
    OpaqueRefCounted *owner04;
public:
    ~Rva002390CB();
};
Rva002390CB::~Rva002390CB() {
    if (owner04) owner04->Release_Ref();
}
