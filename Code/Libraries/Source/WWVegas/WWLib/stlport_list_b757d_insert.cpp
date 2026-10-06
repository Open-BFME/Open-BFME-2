// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@UBfmeStringRecord000B757D@@V?$allocator@UBfmeStringRecord000B757D@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord000B757D@@U?$_Nonconst_traits@UBfmeStringRecord000B757D@@@_STL@@@2@U32@ABUBfmeStringRecord000B757D@@@Z retail 0x000BC1E8 37B
// List insert for the 20-byte B757D record (node 0x1c via rowed create_node
// 0x000BB6EE); same 37B shape as the Pod32 insert pin at 0x000BC180.
// Evidence: callee 0x000BB6EE plus waiters 0x000BCFC3 0x000BCFDF.
class AsciiString { public: AsciiString(const AsciiString &); AsciiString &operator=(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord000B757D {
    unsigned int word0, word1; AsciiString text; unsigned int word2; unsigned char tail;
    BfmeStringRecord000B757D();
    BfmeStringRecord000B757D(const BfmeStringRecord000B757D &o);
};
inline bool operator==(const BfmeStringRecord000B757D &x, const BfmeStringRecord000B757D &y) { return x.word0 == y.word0; }
inline bool operator<(const BfmeStringRecord000B757D &x, const BfmeStringRecord000B757D &y) { return x.word0 < y.word0; };
#include <list>
namespace _STL {
template <> _List_node<BfmeStringRecord000B757D> *list<BfmeStringRecord000B757D, allocator<BfmeStringRecord000B757D> >::_M_create_node(BfmeStringRecord000B757D const &);
}
template class _STL::list<BfmeStringRecord000B757D, _STL::allocator<BfmeStringRecord000B757D> >;
