// ?rva005E4BB7@Rva005E4BB7@@QAEPAXPAX@Z
// partial score=0.78 date=2026-10-08
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0x005E4BB7..0x005E4C2F is an int-key tree subscript. Its
// 4-byte refcounted server value and pair construction are independently rowed
// in stlport_map_int_sbserver.cpp. The receiver's original name is unknown.
#include <map>

struct SBServer
{
    void *m_handle;
    SBServer(const SBServer &);
    ~SBServer();
};

// The default value owns a null handle. Keeping its cleanup conditional models
// the native unwind lifetime while allowing the known-null normal cleanup away.
struct Rva005E4BB7Empty
{
    void *const m_handle;
    Rva005E4BB7Empty() : m_handle(0) {}
    __forceinline ~Rva005E4BB7Empty()
    {
        if (m_handle)
            ((SBServer *)this)->SBServer::~SBServer();
    }
};

// The existing hint-insert wrapper has an address-derived view. It only
// forwards the iterator and pair to the rowed int-key insertion at 0x005E46F1;
// that view is not evidence for a short target key or an int target value.
struct Rva005E49E0Element {
    short words[1];
    bool operator<(const Rva005E49E0Element &) const;
};
typedef _STL::map<Rva005E49E0Element, int> InsertView005E49E0;
typedef _STL::pair<const int, int> IntPair005E4BB7;
typedef _STL::_Rb_tree<int, IntPair005E4BB7,
    _STL::_Select1st<IntPair005E4BB7>, _STL::less<int>,
    _STL::allocator<IntPair005E4BB7> > SearchView005E4BB7;
typedef _STL::pair<const int, SBServer> ServerPair005E4BB7;
namespace _STL {
template <> __declspec(noinline) SearchView005E4BB7::_Link_type
SearchView005E4BB7::_M_lower_bound(const int &) const;
}
extern template ServerPair005E4BB7::pair(const int &, const SBServer &);
extern template InsertView005E49E0::iterator InsertView005E49E0::insert(
    InsertView005E49E0::iterator, const InsertView005E49E0::value_type &);

class Rva005E4BB7
{
public:
    void *rva005E4BB7(void *key);
private:
    _STL::_Rb_tree_node_base *m_header;
};

void *Rva005E4BB7::rva005E4BB7(void *key)
{
    SearchView005E4BB7::_Link_type pos =
        (SearchView005E4BB7::_Link_type)((SearchView005E4BB7 *)this)->lower_bound(*(const int *)key)._M_node;
    if (pos == m_header || *(const int *)key < pos->_M_value_field.first) {
        const Rva005E4BB7Empty empty;
        InsertView005E49E0::iterator where;
        where._M_node = pos;
        pos = (SearchView005E4BB7::_Link_type)((InsertView005E49E0 *)this)->insert(
            where, *(const InsertView005E49E0::value_type *)&ServerPair005E4BB7(
                *(const int *)key, *(const SBServer *)&empty))._M_node;
    }
    return (char *)pos + 0x14;
}
