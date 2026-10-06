// cl: /MD
// ?rva005FBE82@Rva005FBE82@@QAEXPBDP81@AEXH@Z@Z @0x005FBE82 56B: leaf __thiscall with (char const*, callback). Evidence: reads ecx as this, ret 8, isdigit+atoi range 0-4 then ecx=[this] push idx call [second arg].
class Rva005FBE82
{
public:
    typedef void (Rva005FBE82::*Cb)(int);
    void rva005FBE82(char const *s, Cb cb);
private:
    Rva005FBE82 *m_p;
};
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
void Rva005FBE82::rva005FBE82(char const *s, Cb cb)
{
    if (!s)
        return;
    if (!isdigit(*s))
        return;
    int v = atoi(s);
    if (v < 0 || v >= 5)
        return;
    (m_p->*cb)(v);
}
