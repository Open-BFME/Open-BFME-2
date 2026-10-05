// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport 4.5.3 _Rb_tree::insert_unique(value) (134 bytes) and _M_insert
// (136 bytes) for int-keyed maps whose pair sits unclaimed in retail, under
// the flags of stlport_map_int_int_os.cpp.  Neither body depends on the mapped
// type beyond the node it creates, so each tree is instantiated with an
// int-like key and a mapped placeholder named after its insert_unique address;
// _M_create_node is pinned at the address each retail _M_insert calls.  The
// first tree is ScienceStore's map<ScienceType, bool>: its insert_unique sits
// beside the map's constructor 0x001FFA00 and _Rb_tree constructor 0x001FF84B
// (ScienceStoreRootPrereqs.cpp), so it keeps those types.  No other identity
// is claimed.
//
//   insert_unique  _M_insert   _M_create_node
//   0x001FF875     0x001FF791  0x001FF703
//   0x0032EB87     0x0032EAD6  0x0032EA7F
//   0x00439AAA     0x00439A22  0x00439943
//   0x004F90FF     0x004F9077  0x004F8CE0
//   0x00502861     0x005027D9  0x00502645
//   0x00502BCD     0x00502B45  0x005028E7
//   0x00559076     0x00558FEE  0x00558E9C

#include <map>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

struct Rva0032EB87Mapped { int a; };
struct Rva00439AAAMapped { int a; };
struct Rva004F90FFMapped { int a; };
struct Rva00502861Mapped { int a; };
struct Rva00502BCDMapped { int a; };
struct Rva00559076Mapped { int a; };

template class _STL::_Rb_tree<ScienceType, _STL::pair<const ScienceType, bool>, _STL::_Select1st<_STL::pair<const ScienceType, bool> >, _STL::less<ScienceType>, _STL::allocator<_STL::pair<const ScienceType, bool> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva0032EB87Mapped>, _STL::_Select1st<_STL::pair<const int, Rva0032EB87Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva0032EB87Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00439AAAMapped>, _STL::_Select1st<_STL::pair<const int, Rva00439AAAMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00439AAAMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva004F90FFMapped>, _STL::_Select1st<_STL::pair<const int, Rva004F90FFMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva004F90FFMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00502861Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00502861Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502861Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00502BCDMapped>, _STL::_Select1st<_STL::pair<const int, Rva00502BCDMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502BCDMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00559076Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00559076Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00559076Mapped> > >;

// Multimap trees: insert_equal(value) (59 bytes) and insert_equal(hint,
// value) (250 bytes) over the same int-keyed _M_insert shape, three more
// trees whose bodies sit unclaimed; mapped placeholders are named after the
// insert_equal address and _M_create_node is pinned per tree.
//
//   insert_equal  hint        _M_insert   _M_create_node
//   0x002F1DA1    -           0x002F0D4E  0x002EF239
//   0x00501130    0x00501374  0x005010A8  0x00501086
//   0x00502FAE    0x00503554  0x00502F26  0x00502EA4

struct Rva002F1DA1Mapped { int a; };
struct Rva00501130Mapped { int a; };
struct Rva00502FAEMapped { int a; };
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva002F1DA1Mapped>, _STL::_Select1st<_STL::pair<const int, Rva002F1DA1Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva002F1DA1Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00501130Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00501130Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501130Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00502FAEMapped>, _STL::_Select1st<_STL::pair<const int, Rva00502FAEMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502FAEMapped> > >;
