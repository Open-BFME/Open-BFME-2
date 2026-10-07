// cl: /O1 /arch:SSE /G7 /MD /Oy- /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Ghidra FUN_0075a292: 74B. Existing callers 0x00482134/0x00482152
// pin this member of TheGameLogic's +0x170 object as (int, float).
// The first word is dereferenced at +0x74, Object's established ID offset.
// The owner's purpose and the float's meaning remain unresolved.
#include <list>

namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

struct Rva0035A292ObjectView
{
    char unknown[0x74];
    int id;
};

class Rva0035A292
{
public:
    void rva0035A292(int objectWord, float value);
    void rva0035A005(int objectWord, float value);
private:
    char unknown[0x14];
    _STL::list<int, _STL::allocator<int> > ids;
};

void Rva0035A292::rva0035A292(int objectWord, float value)
{
    typedef _STL::list<int, _STL::allocator<int> > IdList;
    for (IdList::iterator it = ids.begin(); it != ids.end(); ++it)
    {
        if (*it == reinterpret_cast<Rva0035A292ObjectView *>(objectWord)->id)
        {
            ids.erase(it);
            rva0035A005(objectWord, value);
            break;
        }
    }
}
