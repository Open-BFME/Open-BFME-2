// cl: /DNDEBUG /MD /EHsc
// ?Rva0056866ALess@@YG_NPBX0@Z @0x0056866A 71B. Stdcall 10-byte key ordering
// for the 0x00568xxx RB-tree family (2 floats + word at +8). Retail compares
// floats with comiss/ja (greater-true) and word with sbb/neg (less-true).
// Evidence: callees none (leaf); callers are tree find 0x00568A41 and insert
// 0x00569295 which both pass node key at +0x10 and search key; /arch:SSE gives
// movss/comiss, /O1 gives pop-free ret-8 shape like sibling Less 0x006038D4.
// ?Rva00568A9DCopy@@YAXPAXPBX@Z @0x00568A9D 31B. Cdecl 10-byte key copy
// (4+4+2) with null-dest guard. Evidence: sole caller is node create
// 0x00568D95 which allocates 0x1c and copies input key to node+0x10; no
// callees; matches with /O1 (same flags as neighbour stlport_lower_bound).
// ?Rva00568D95CreateNode@@YGPAXPBX@Z @0x00568D95 34B. Stdcall node creator
// allocating 0x1c via rowed byte allocator 0x000307F0 then copying the
// 10-byte key to node+0x10 via the rowed copy above. Evidence: callees now
// all rowed; callers are insert 0x00568FE4 (two sites); ret-4 single-arg
// shape matches sibling _M_create_node 0x00382B7F 34B.
namespace _STL {
template <class T> class allocator;
template <> class allocator<char> {
public:
    static char *allocate(unsigned int n, const void *hint);
};
}
struct Rva0056866AKey {
    float x;
    float y;
    unsigned short w;
};
bool __stdcall Rva0056866ALess(const void *a_, const void *b_)
{
    const Rva0056866AKey *a = (const Rva0056866AKey *)a_;
    const Rva0056866AKey *b = (const Rva0056866AKey *)b_;
    if (a->x < b->x)
        return false;
    if (a->x > b->x)
        return true;
    if (a->y < b->y)
        return false;
    if (a->y > b->y)
        return true;
    return a->w < b->w;
}
void __cdecl Rva00568A9DCopy(void *dest, const void *src)
{
    if (!dest)
        return;
    *(unsigned int *)dest = *(const unsigned int *)src;
    *((unsigned int *)dest + 1) = *((const unsigned int *)src + 1);
    *(unsigned short *)((unsigned char *)dest + 8) = *(const unsigned short *)((const unsigned char *)src + 8);
}
void *__stdcall Rva00568D95CreateNode(const void *src)
{
    char *node = _STL::allocator<char>::allocate(0x1c, 0);
    Rva00568A9DCopy(node + 0x10, src);
    return node;
}
