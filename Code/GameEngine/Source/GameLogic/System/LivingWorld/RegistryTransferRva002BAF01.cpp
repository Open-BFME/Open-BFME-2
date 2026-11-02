// cl: /O1 /Oy- /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 002BAF01..002BAF5D, 92B, RET8. Owner identity unresolved.
// The first argument supplies the +12C integer key of the tree at this+130.
// Native _M_find 388F63 is the existing int-key lookup; header0 and node14
// match that row's STLport tree representation. The mapped pointer is the
// receiver of rowed registry contains4FBEAB and mark4FBDCC (flag+1C).
// Complete callee2B9B42, 117B RET12, reads argument1+12C and enqueues the
// three words {argument2; key; argument3} into the vector at this+148.
// Its original method name and the mapped record's class remain unknown.

class CreateAHeroData;

struct Rva002BAF01Region
{
    char unknown00[0x12C];
    int key;
};
struct Rva002BAF01Record
{
    char unknown00[0x14];
    int value14;
    char unknown18[4];
    bool marked;
};
struct Rva002BAF01Node
{
    char unknown00[0x14];
    Rva002BAF01Record *record;
};
struct Rva002BAF01Tree
{
    void *header;
};
class Rva002BAF01;
namespace _STL {
template <class T1, class T2> struct pair { T1 first; T2 second; };
template <class P> struct _Select1st {};
template <class T> struct less {};
template <class T> class allocator {};
template <class V> struct _Rb_tree_node;
template <class K, class V, class KOV, class Cmp, class Alloc> class _Rb_tree
{
    friend class ::Rva002BAF01;
    typedef _Rb_tree_node<V> *_Link_type;
private:
    template <class KT> _Link_type _M_find(const KT &) const;
};
}
typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;
class Rva004FBEAB
{
public:
    bool rva004FBEAB(CreateAHeroData *value);
};
class Rva004FBDCC
{
public:
    void rva004FBDCC();
};

// 0x002B9B42 is matched as the private LivingWorldLogic::AddDelayedRegionVictory.
class Rva003F287F;
#include "../../../../Include/GameLogic/LivingWorldLogic.h"

class Rva002BAF01
{
public:
    void rva002BAF01(Rva002BAF01Region *region, CreateAHeroData *value);
private:
    char unknown00[0x130];
    Rva002BAF01Tree tree;
};

void Rva002BAF01::rva002BAF01(Rva002BAF01Region *region, CreateAHeroData *value)
{
    int key = region->key;
    void *node = reinterpret_cast<MapIntIntTree *>(&tree)->_M_find(key);
    if (node != tree.header)
    {
        Rva002BAF01Record *record = static_cast<Rva002BAF01Node *>(node)->record;
        if (reinterpret_cast<Rva004FBEAB *>(record)->rva004FBEAB(value)
            && !record->marked)
        {
            reinterpret_cast<Rva004FBDCC *>(record)->rva004FBDCC();
            ((LivingWorldLogic *)this)->AddDelayedRegionVictory((Rva003F287F *)region, (int)value, record->value14);
        }
    }
}
