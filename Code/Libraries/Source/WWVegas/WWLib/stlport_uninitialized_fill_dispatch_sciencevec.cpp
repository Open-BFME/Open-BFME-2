// cl: /O1 /Ob0 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail 0x003399F8: three-argument fill dispatch to rowed 0x00339988.
// Caller 0x0033A0F7 passes finish,count,value; its cleanup proves three arguments.
// The previous copy-backward identity contradicted that call ABI and the callee.
// ScienceType spelling follows the existing fill callee; callers and stride are target facts.
// Algorithm and dispatch type are from STLport 4.5.3 at BFME 1 revision c1bb9ed9.
#include <memory>
#include <vector>
#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/ScienceType.h"
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}
typedef _STL::vector<ScienceType,_STL::allocator<ScienceType> > SciVec;
template SciVec *_STL::uninitialized_fill_n(SciVec*,unsigned int,const SciVec&);
// bfme link decl-only begin
namespace _STL { template <> void _Construct<_STL::vector<ScienceType,_STL::allocator<ScienceType> >,_STL::vector<ScienceType,_STL::allocator<ScienceType> > >(_STL::vector<ScienceType,_STL::allocator<ScienceType> > *,_STL::vector<ScienceType,_STL::allocator<ScienceType> > const &); }
namespace _STL { template <> void _Construct<ScienceType,ScienceType>(ScienceType *,ScienceType const &); }
namespace _STL { template <> ScienceType * __uninitialized_copy<ScienceType const *,ScienceType *>(ScienceType const *,ScienceType const *,ScienceType *,_STL::__false_type const &); }
namespace _STL { template <> _Vector_base<ScienceType,_STL::allocator<ScienceType> >::_Vector_base(unsigned int,_STL::allocator<ScienceType> const &); }
namespace _STL { template <> vector<ScienceType,_STL::allocator<ScienceType> >::vector(_STL::vector<ScienceType,_STL::allocator<ScienceType> > const &); }
namespace _STL { template <> ScienceType * _STLP_alloc_proxy<ScienceType *,ScienceType,_STL::allocator<ScienceType> >::allocate(unsigned int); }
// bfme link decl-only end
