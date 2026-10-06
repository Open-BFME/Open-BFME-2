// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Target Ghidra43-byte body: clear the list header at+0x910, then write
// signed bit pattern-2 to four words at+0x914/+0x918/+0x91C/+0x920.
// The list call uses the already rowed39-byte node-clear implementation.
// list<int> here is an ABI call view: the clear helper frees nodes without
// reading their payload. The target payload type, original class/method,
// scalar meanings and complete object size remain unknown.
#include <list>
namespace _STL { template<> void _List_base<int,allocator<int> >::clear(); }
class Rva0029C138 {
public:
    void rva0029C138();
private:
    unsigned char m_prefix[0x910];
    void* m_listHead910;
    int m_word914,m_word918,m_word91C,m_word920;
};
void Rva0029C138::rva0029C138() {
    reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> >*>(&m_listHead910)->clear();
    m_word914=-2;
    m_word918=-2;
    m_word91C=-2;
    m_word920=-2;
}
