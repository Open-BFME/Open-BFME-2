// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00359032Record {
 Rva00359032Record(); Rva00359032Record(const Rva00359032Record&);
 ~Rva00359032Record(); Rva00359032Record&operator=(const Rva00359032Record&);
 char bytes[8];
};
bool operator<(const Rva00359032Record&,const Rva00359032Record&);


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::pair<_STL::_Rb_tree_iterator<Rva00359032Record, _STL::_Nonconst_traits<Rva00359032Record> >, bool> _STL::_Rb_tree<Rva00359032Record, Rva00359032Record, _STL::_Identity<Rva00359032Record>, _STL::less<Rva00359032Record>, _STL::allocator<Rva00359032Record> >::insert_unique(Rva00359032Record const &);
