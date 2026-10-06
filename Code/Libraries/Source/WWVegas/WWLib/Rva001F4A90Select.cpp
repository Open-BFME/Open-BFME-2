// cl: /O1 /MD /Oi-
// ?rva001F4A90@Rva001F4A90Host@@QAEXPBDHH@Z @0x001F4A90 113B
// Property-name dispatch over Draw/Physics/Update: parses src via rowed
// 0x001530E9 into a 76B parts block, compares its name via import _strcmpi
// (IAT 0xBBA518, combined add esp,0x10 cleanup), selects the embedded member
// at +4/+8/+0xC by lea (objects, not pointers) and runs its vtable slot 1
// with (m_ext, a2, a3). Members are address-derived; slot 0 unproven but
// required to place slot 1 at +4.
struct Rva001530E9Parts {
    char m_name[64];
    bool m_hasStar;
    bool m_hasBracket;
    char m_pad[2];
    int m_index;
    const char *m_ext;
};
void __cdecl Rva001530E9Parse(const char *src, void *volatile dstRaw);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
struct Rva001F4A90Sel {
    virtual void v0();
    virtual void v1(const char *ext, int a2, int a3);
};
class Rva001F4A90Host {
public:
    void rva001F4A90(const char *src, int a2, int a3);
private:
    int m_pad0;
    Rva001F4A90Sel m_draw4;
    Rva001F4A90Sel m_phys8;
    Rva001F4A90Sel m_updC;
};
void Rva001F4A90Host::rva001F4A90(const char *src, int a2, int a3)
{
    Rva001530E9Parts parts;
    Rva001530E9Parse(src, (void *volatile)&parts);
    Rva001F4A90Sel *sel;
    if (_strcmpi(parts.m_name, "Draw") == 0)
        sel = &m_draw4;
    else if (_strcmpi(parts.m_name, "Physics") == 0)
        sel = &m_phys8;
    else if (_strcmpi(parts.m_name, "Update") == 0)
        sel = &m_updC;
    else
        return;
    sel->v1(parts.m_ext, a2, a3);
}
