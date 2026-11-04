// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva002CA82CElement { short words[4]; bool operator<(const Rva002CA82CElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002CA82CElement&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Construct<_STL::pair<Rva002CA82CElement const, int>, _STL::pair<Rva002CA82CElement const, int> >(_STL::pair<Rva002CA82CElement const, int> *, _STL::pair<Rva002CA82CElement const, int> const &);

// The ArmorTemplateSet set's _M_create_node (stlport_rb_tree_create_nodes2.cpp)
// calls _Construct out of line; retail's call lands on this same folded body.
// ArmorTemplateSet: types bit flags, armor template and damage FX pointers.
class ArmorTemplateSet {
public:
    // Retail's 0x002CA82C copies the three words one by one: a user-declared
    // (memberwise) copy, as STLport's pair has; inferred from those bytes.
    ArmorTemplateSet(const ArmorTemplateSet &o) : m_types(o.m_types), m_template(o.m_template), m_fx(o.m_fx) {}
    unsigned int m_types; const void *m_template; const void *m_fx;
};
template void _STL::_Construct<ArmorTemplateSet, ArmorTemplateSet>(ArmorTemplateSet *, ArmorTemplateSet const &);
