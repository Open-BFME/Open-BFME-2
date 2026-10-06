// cl: /MD
// ??1Rva005FBBEE@@UAE@XZ @0x005FBBEE 14B leaf virtual dtor tail-jmps to rowed clear 0x005FBBA6
// Evidence: mov [ecx],vtable 0x00C79FF4 plus add ecx,4 plus jmp callee; callers include rowed ??_G 0x005FBC04; same alternatename release-view recipe as native Rva005FCF0E in OpaqueScalarDeletingDtorsB18.cpp.
#pragma comment(linker, "/alternatename:??1Rva005FBBA6ReleaseView@@QAE@XZ=?clear@Rva005FBBA6@@QAEXXZ")
class Rva005FBBA6ReleaseView
{
public:
    ~Rva005FBBA6ReleaseView();
};
class Rva005FBBEE
{
public:
    virtual ~Rva005FBBEE();
private:
    Rva005FBBA6ReleaseView m_holder;
};
Rva005FBBEE::~Rva005FBBEE()
{
}
