// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The element is GenericObjectCreationNugget::AnimSet: retail's fill loop calls
// the rowed _Construct<AnimSet> 0x001F06B9 (ObjectCreationList.cpp), which calls
// the rowed AnimSet copy 0x001F0558, with the same 12-byte stride. Sibling of
// StlSweepW5Rva001F06E6.cpp (the AnimSet uninitialized_copy). The copy is declared only here.
class GenericObjectCreationNugget {
public:
    struct AnimSet {
        AnimSet(const AnimSet &);
        ~AnimSet();
        char bytes[12];
    };
};

// Instantiate the recovered operation and its required template dependencies.
template GenericObjectCreationNugget::AnimSet * _STL::__uninitialized_fill_n<GenericObjectCreationNugget::AnimSet *, unsigned int, GenericObjectCreationNugget::AnimSet>(GenericObjectCreationNugget::AnimSet *, unsigned int, GenericObjectCreationNugget::AnimSet const &, _STL::__false_type const &);
