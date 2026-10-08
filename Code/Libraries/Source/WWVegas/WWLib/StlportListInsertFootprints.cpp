// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 list<T> insert / push_back / push_front forwarders over
// element footprints, dedicated TU. Each element is reduced to its size
// (read from the TU that owns its matched list _M_create_node row) with a
// declared copy ctor and dtor, and _M_create_node is declared as an
// explicit specialization so every node allocation calls that row.
//
// Target evidence: every body is byte-identical with relocations masked at
// an unowned retail caller of its element's matched _M_create_node. The
// masked bytes are the same for every element type; the name of each body
// follows from which element's _M_create_node row its call reads.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// 32-byte element; layout owner stlport_list_create_nodes.cpp.
struct BfmeContainerRecord00462D62 { char m_pad[32]; public: BfmeContainerRecord00462D62(const BfmeContainerRecord00462D62 &); ~BfmeContainerRecord00462D62(); };
// 12-byte element; layout owner stlport_pod_list_bodies.cpp.
struct BfmePod12 { char m_pad[12]; public: BfmePod12(const BfmePod12 &); ~BfmePod12(); };
// 124-byte element; layout owner stlport_pod_list_bodies.cpp.
struct BfmePod124 { char m_pad[124]; public: BfmePod124(const BfmePod124 &); ~BfmePod124(); };
// 60-byte element; layout owner stlport_pod_list_bodies.cpp.
struct BfmePod60 { char m_pad[60]; public: BfmePod60(const BfmePod60 &); ~BfmePod60(); };
// 72-byte element; layout owner stlport_pod_list_bodies.cpp.
struct BfmePod72 { char m_pad[72]; public: BfmePod72(const BfmePod72 &); ~BfmePod72(); };
// 32-byte element; layout owner stlport_list_create_nodes.cpp.
struct BfmeStringRecord000B75AE { char m_pad[32]; public: BfmeStringRecord000B75AE(const BfmeStringRecord000B75AE &); ~BfmeStringRecord000B75AE(); };
// 24-byte element; layout owner stlport_list_create_nodes.cpp.
struct BfmeStringRecord00415F34 { char m_pad[24]; public: BfmeStringRecord00415F34(const BfmeStringRecord00415F34 &); ~BfmeStringRecord00415F34(); };
// 28-byte element; layout owner stlport_list_create_nodes.cpp.
// 12-byte element; layout owner Coord3DListCreateNode.cpp.
struct Coord3D { char m_pad[12]; public: Coord3D(const Coord3D &); ~Coord3D(); };
// 4-byte element; layout owner stlport_list_create_nodes.cpp.
class Rva0036CA00Str { char m_pad[4]; public: Rva0036CA00Str(const Rva0036CA00Str &); ~Rva0036CA00Str(); };
// 12-byte element; layout owner stlport_list_create_nodes.cpp.
class RvaSmartPtr12 { char m_pad[12]; public: RvaSmartPtr12(const RvaSmartPtr12 &); ~RvaSmartPtr12(); };
// 3572-byte element; layout owner stlport_list_treehintopaque_00436e3b.cpp.
struct TreeHintOpaque0043671B { char m_pad[3572]; public: TreeHintOpaque0043671B(const TreeHintOpaque0043671B &); ~TreeHintOpaque0043671B(); };
// 8-byte element; layout owner stlport_list_treekey00242f5e_create_node.cpp.
struct TreeKey00242F5E { char m_pad[8]; public: TreeKey00242F5E(const TreeKey00242F5E &); ~TreeKey00242F5E(); };

template <> _STL::_List_node<BfmeContainerRecord00462D62> *_STL::list<BfmeContainerRecord00462D62>::_M_create_node(const BfmeContainerRecord00462D62 &);
template <> _STL::_List_node<BfmePod12> *_STL::list<BfmePod12>::_M_create_node(const BfmePod12 &);
template <> _STL::_List_node<BfmePod124> *_STL::list<BfmePod124>::_M_create_node(const BfmePod124 &);
template <> _STL::_List_node<BfmePod60> *_STL::list<BfmePod60>::_M_create_node(const BfmePod60 &);
template <> _STL::_List_node<BfmePod72> *_STL::list<BfmePod72>::_M_create_node(const BfmePod72 &);
template <> _STL::_List_node<BfmeStringRecord000B75AE> *_STL::list<BfmeStringRecord000B75AE>::_M_create_node(const BfmeStringRecord000B75AE &);
template <> _STL::_List_node<BfmeStringRecord00415F34> *_STL::list<BfmeStringRecord00415F34>::_M_create_node(const BfmeStringRecord00415F34 &);
template <> _STL::_List_node<Coord3D> *_STL::list<Coord3D>::_M_create_node(const Coord3D &);
template <> _STL::_List_node<Rva0036CA00Str> *_STL::list<Rva0036CA00Str>::_M_create_node(const Rva0036CA00Str &);
template <> _STL::_List_node<RvaSmartPtr12> *_STL::list<RvaSmartPtr12>::_M_create_node(const RvaSmartPtr12 &);
template <> _STL::_List_node<TreeHintOpaque0043671B> *_STL::list<TreeHintOpaque0043671B>::_M_create_node(const TreeHintOpaque0043671B &);
template <> _STL::_List_node<TreeKey00242F5E> *_STL::list<TreeKey00242F5E>::_M_create_node(const TreeKey00242F5E &);

// Retail 0x00055475 (26B).
template void _STL::list<Rva0036CA00Str>::push_back(const Rva0036CA00Str &);
// Retail 0x000BC180 (37B).
template _STL::list<BfmeStringRecord000B75AE>::iterator _STL::list<BfmeStringRecord000B75AE>::insert(_STL::list<BfmeStringRecord000B75AE>::iterator, const BfmeStringRecord000B75AE &);
// Retail 0x001B4CAB (37B).
template _STL::list<BfmePod72>::iterator _STL::list<BfmePod72>::insert(_STL::list<BfmePod72>::iterator, const BfmePod72 &);
// Retail 0x001F640B (37B).
template _STL::list<RvaSmartPtr12>::iterator _STL::list<RvaSmartPtr12>::insert(_STL::list<RvaSmartPtr12>::iterator, const RvaSmartPtr12 &);
// Retail 0x00293461 (37B).
template _STL::list<BfmePod124>::iterator _STL::list<BfmePod124>::insert(_STL::list<BfmePod124>::iterator, const BfmePod124 &);
// Retail 0x002A3F93 (28B).
template void _STL::list<TreeKey00242F5E>::push_front(const TreeKey00242F5E &);
// Retail 0x0030127B (26B).
template void _STL::list<Coord3D>::push_back(const Coord3D &);
// Retail 0x0041691F (26B).
template void _STL::list<BfmeStringRecord00415F34>::push_back(const BfmeStringRecord00415F34 &);
// Retail 0x0043620F (37B).
template _STL::list<TreeHintOpaque0043671B>::iterator _STL::list<TreeHintOpaque0043671B>::insert(_STL::list<TreeHintOpaque0043671B>::iterator, const TreeHintOpaque0043671B &);
// Retail 0x00463DE4 (37B).
template _STL::list<BfmeContainerRecord00462D62>::iterator _STL::list<BfmeContainerRecord00462D62>::insert(_STL::list<BfmeContainerRecord00462D62>::iterator, const BfmeContainerRecord00462D62 &);
// Retail 0x004E54C8 (37B).
template _STL::list<BfmePod60>::iterator _STL::list<BfmePod60>::insert(_STL::list<BfmePod60>::iterator, const BfmePod60 &);
// Retail 0x004E7B49 (37B).
template _STL::list<BfmePod12>::iterator _STL::list<BfmePod12>::insert(_STL::list<BfmePod12>::iterator, const BfmePod12 &);
// Retail 0x001B4CEF (26B).
template void _STL::list<BfmePod72>::push_back(const BfmePod72 &);
// Retail 0x001F81D2 (26B).
template void _STL::list<RvaSmartPtr12>::push_back(const RvaSmartPtr12 &);
// Retail 0x002947D6 (26B).
template void _STL::list<BfmePod124>::push_back(const BfmePod124 &);
// Retail 0x00359BCC (28B).
template void _STL::list<BfmePod12>::push_front(const BfmePod12 &);
// Retail 0x00420DF3 (26B).
template void _STL::list<BfmePod12>::push_back(const BfmePod12 &);
// Retail 0x00436701 (26B).
template void _STL::list<TreeHintOpaque0043671B>::push_back(const TreeHintOpaque0043671B &);
// Retail 0x004643CE (26B).
template void _STL::list<BfmeContainerRecord00462D62>::push_back(const BfmeContainerRecord00462D62 &);
// Retail 0x004E5526 (28B).
template void _STL::list<BfmePod60>::push_front(const BfmePod60 &);

// Retail 0x001F6852 (48B): range insert dispatch looping over the insert above.
template void _STL::list<RvaSmartPtr12>::_M_insert_dispatch<_STL::_List_iterator<RvaSmartPtr12, _STL::_Const_traits<RvaSmartPtr12> > >(
    _STL::list<RvaSmartPtr12>::iterator, _STL::_List_iterator<RvaSmartPtr12, _STL::_Const_traits<RvaSmartPtr12> >, _STL::_List_iterator<RvaSmartPtr12, _STL::_Const_traits<RvaSmartPtr12> >, const _STL::__false_type &);

// Retail 0x001F8347 (30B): the range insert that forwards to the dispatch above.
template void _STL::list<RvaSmartPtr12>::insert<_STL::_List_iterator<RvaSmartPtr12, _STL::_Const_traits<RvaSmartPtr12> > >(
    _STL::list<RvaSmartPtr12>::iterator, _STL::_List_iterator<RvaSmartPtr12, _STL::_Const_traits<RvaSmartPtr12> >, _STL::_List_iterator<RvaSmartPtr12, _STL::_Const_traits<RvaSmartPtr12> >);

// Retail 0x001F88CA (88B): the list copy ctor built on the range insert above.
template _STL::list<RvaSmartPtr12>::list(const _STL::list<RvaSmartPtr12> &);

class Rva001B4CD8
{
public:
	void rva001B4CD8();
};

class Rva001B4D09
{
public:
	void rva001B4D09();
};

void Rva001B4D09::rva001B4D09()
{
	((Rva001B4CD8 *)this)->rva001B4CD8();
}

class Rva001F81EC
{
public:
	void rva001F81EC();
};

class Rva001F8922
{
public:
	void rva001F8922();
};

void Rva001F8922::rva001F8922()
{
	((Rva001F81EC *)this)->rva001F81EC();
}

