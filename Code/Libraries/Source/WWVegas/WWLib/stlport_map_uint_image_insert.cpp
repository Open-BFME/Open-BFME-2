// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?_M_insert@?$_Rb_tree@IU?$pair@$$CBIPAVImage@@@_STL@@U?$_Select1st@U?$pair@$$CBIPAVImage@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAVImage@@@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIPAVImage@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIPAVImage@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBIPAVImage@@@2@0@Z
// retail 0x004D9C49 136B. _Rb_tree<unsigned Image*>::_M_insert (hinted insert
// worker). Target uses unsigned jb at +0x20 where the signed int-int twin at
// 0x0038341E uses jl; both call the 24B node factory at 0x00382B7F.
// Evidence: called twice by the 294B insert_unique-hint worker at 0x0020673B
// (via 0x002067A5) and by the 134B insert_unique worker at 0x004D795B
// (via 0x004D79BD); that chain feeds the shared ImageSubscriptMap
// operator[] worker at 0x002077D6 through 0x00358211. ImageNameMap is
// map<unsigned Image*> per Code/GameEngine/Source/GameClient/System/ImageCollectionFindImage.cpp.
// The PAVImage _M_create_node spelling is an ICF twin of the rowed HH node at
// 0x00382B7F (34B exact modulo relocs under bfmealloc NO_EXCEPTIONS); pinned
// in the same landing. _Rebalance resolves through its matched row at
// 0x00025490. Flags copy the signed int-int _M_insert TU
// stlport_map_int_int_os.cpp which gives the same 136B/59-insn shape.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Image;

template class _STL::map<unsigned, Image *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > >;

typedef _STL::map<unsigned, Image *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > ImageNameMap;

// ImageSubscriptMap shared worker (retail 0x002077D6 69B). Declaration-only
// view over ImageNameMap per ImageCollectionFindImage.cpp; retail folds every
// unsigned-key pointer-map operator[] into this worker which drives the rowed
// PAX lower_bound at 0x4FF3B6 (ICF twin of the PAVImage spelling pinned here)
// and the rowed PAVImage hint insert at 0x00358211.
class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
private:
	ImageNameMap m_map;
};

Image *&ImageSubscriptMap::operator[](const unsigned int &key)
{
	ImageNameMap::iterator i = m_map.lower_bound(key);
	if (i == m_map.end() || m_map.key_comp()(key, (*i).first))
		i = m_map.insert(i, ImageNameMap::value_type(key, (Image *)0));
	return (*i).second;
}
