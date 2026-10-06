// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<T> placement copies with an EH frame, 45 bytes each,
// retail 0x0021FA1A and 0x002B8226.
// Evidence: each body is byte-identical with relocations masked to the rowed
// EH-framed _Construct siblings at 0x0021A95D and 0x002B5581
// (StringRecordInlineCopyBFME2.cpp), whose flags this TU mirrors; its only
// call besides __EH_prolog is the defined copy ctor of the T named here.
#include <memory>

class Rva0021F876
{
public:
	Rva0021F876(const Rva0021F876 &other);
};

struct Rva002B72C9
{
	Rva002B72C9(const Rva002B72C9 &other);
};

template void _STL::_Construct<Rva0021F876, Rva0021F876>(Rva0021F876 *, const Rva0021F876 &);
template void _STL::_Construct<Rva002B72C9, Rva002B72C9>(Rva002B72C9 *, const Rva002B72C9 &);
