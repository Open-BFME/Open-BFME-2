// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva004182D3@Rva004182F8@@QAEPAXPBVRva004181F5@@@Z @0x004182D3 37B
// Allocates 0x20 via byte allocator 0x000307F0, zeroes first dword, constructs
// Rva004181F5 at +4 via rowed Construct 0x0041826B, returns new wrapper.
// Target evidence: ret 4 with one argument, and its only caller 0x004182F8
// loads ecx with its own this (mov ecx,esi at 0x0041833C) before the call, so
// this is a thiscall member of the 0x004182F8 table that ignores this (the
// earlier row typed it __stdcall). /O1 gives and-zero plus direct push.
#include <memory>
class Rva004181F5 {
public:
    Rva004181F5(const Rva004181F5 &other);
private:
    char m_pad[0x1c];
};
void __cdecl Rva0041826BConstruct(Rva004181F5 *dst, const Rva004181F5 *src);
struct Wrapper004182D3 {
    int m_0;
    Rva004181F5 m_4;
};
class Rva004182F8 {
public:
    void *rva004182D3(const Rva004181F5 *src);
};
void *Rva004182F8::rva004182D3(const Rva004181F5 *src)
{
    char *buf = _STL::allocator<char>::allocate(0x20, 0);
    Wrapper004182D3 *w = (Wrapper004182D3 *)buf;
    w->m_0 = 0;
    Rva0041826BConstruct(&w->m_4, src);
    return w;
}
