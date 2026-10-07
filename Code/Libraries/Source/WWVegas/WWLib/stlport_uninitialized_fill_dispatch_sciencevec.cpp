// cl: /O1 /Ob0 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail 0x003399F8: three-argument fill dispatch to rowed 0x00339988.
// Caller 0x0033A0F7 passes finish,count,value; its cleanup proves three arguments.
// The previous copy-backward identity contradicted that call ABI and the callee.
// ScienceType spelling follows the existing fill callee; callers and stride are target facts.
// Algorithm and dispatch type are from STLport 4.5.3 at BFME 1 revision c1bb9ed9.
#include <memory>
#include <vector>
enum ScienceType {SCIENCE_INVALID=-1};
typedef _STL::vector<ScienceType,_STL::allocator<ScienceType> > SciVec;
template SciVec *_STL::uninitialized_fill_n(SciVec*,unsigned int,const SciVec&);
