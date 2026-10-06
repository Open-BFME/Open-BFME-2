// cl: /GX-
// ?Rva00380705Free@@YAXXZ @0x00380705 25B. Free virtual result or null via global.
// evidence: reads VA 0x00E032FC via extern g_Va00E032FC; virtual slot0 with 0 arg; rowed delete 0x0002FD60; caller 0x00380763.
extern int g_Va00E032FC;
void __cdecl operator delete(void *);
class Rva00380705Iface
{
public:
    virtual void *virt0(int);
};
void __cdecl Rva00380705Free()
{
    void *p = *(void **)&g_Va00E032FC;
    void *r = 0;
    if (p)
        r = ((Rva00380705Iface *)p)->virt0((int)r);
    ::operator delete(r);
}
