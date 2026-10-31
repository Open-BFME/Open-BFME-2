// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The element is GenericObjectCreationNugget::AnimSet: retail's copy loop calls
// the rowed _Construct<AnimSet> 0x001F06B9 (ObjectCreationList.cpp), which calls
// the rowed AnimSet copy 0x001F0558, which is declared only here.
class GenericObjectCreationNugget {
public:
    struct AnimSet {
        AnimSet(const AnimSet &);
        ~AnimSet();
        char bytes[12];
    };
};

// Instantiate the recovered operation and its required template dependencies.
template GenericObjectCreationNugget::AnimSet * _STL::__uninitialized_copy<GenericObjectCreationNugget::AnimSet const *, GenericObjectCreationNugget::AnimSet *>(GenericObjectCreationNugget::AnimSet const *, GenericObjectCreationNugget::AnimSet const *, GenericObjectCreationNugget::AnimSet *, _STL::__false_type const &);
