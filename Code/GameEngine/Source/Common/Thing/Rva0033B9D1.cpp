// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0033B9D1@Rva0033B9D1@@QAEXXZ @ 0x0033B9D1 117B.
// Map/vector locomotor resolution: if m_3b0 is set walk the map at m_3ac via
// _M_increment; for each node walk the void* vector at +0x14; entries with
// cond >= 1 at +0xc resolve name at +0x10 through TheLocomotorStore
// (TheLocomotorStore); missing templates erase the slot. Unlocks 0x002CF1C9.
// Evidence: callees 0x001E7010 0x00024250 0x001FF51F rows caller 0x002CF1D1 prev/next flags.
#include "ascii_string.h"

class LocomotorTemplate;

class LocomotorStore
{
public:
    LocomotorTemplate *findLocomotorTemplate(const AsciiString &name);
};

extern LocomotorStore *TheLocomotorStore;

namespace _STL
{
struct _Rb_tree_node_base;
template <class T> struct _Rb_global
{
    static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
template <class T> class allocator;
template <class T, class A> class vector
{
public:
    void **erase(void **);
};
}

struct Elem0033B9D1
{
    char m_pad0[0xc];
    int m_cond;
    AsciiString m_name;
};

struct Vec0033B9D1
{
    void **m_begin;
    void **m_end;
};

struct MapNode0033B9D1
{
    char m_pad0[0x14];
    Vec0033B9D1 m_vec;
};

struct Map0033B9D1
{
    char m_pad0[8];
    MapNode0033B9D1 *m_first;
};

class Rva0033B9D1
{
public:
    void rva0033B9D1();
private:
    char m_pad0[0x3ac];
    Map0033B9D1 *m_3ac;
    int m_3b0;
};

void Rva0033B9D1::rva0033B9D1()
{
    if (m_3b0 == 0)
        return;
    MapNode0033B9D1 *node = ((Map0033B9D1 *)m_3ac)->m_first;
    if (node == (MapNode0033B9D1 *)m_3ac)
        return;
    for (;;) {
        Vec0033B9D1 *vec = &node->m_vec;
        void **slot = vec->m_begin;
        while (slot != vec->m_end) {
            Elem0033B9D1 *elem = (Elem0033B9D1 *)*slot;
            if (elem != 0 && elem->m_cond >= 1) {
                LocomotorTemplate *t = TheLocomotorStore->findLocomotorTemplate(elem->m_name);
                if (t != 0) {
                    *slot = t;
                    ++slot;
                } else {
                    slot = ((_STL::vector<void *, _STL::allocator<void *> > *)vec)->erase(slot);
                }
            } else {
                ++slot;
            }
        }
        node = (MapNode0033B9D1 *)_STL::_Rb_global<bool>::_M_increment(
            (_STL::_Rb_tree_node_base *)node);
        if (node == (MapNode0033B9D1 *)m_3ac)
            return;
    }
}
