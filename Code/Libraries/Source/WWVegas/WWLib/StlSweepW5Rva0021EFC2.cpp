// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

// Retail's loop calls _Construct<CreateAHeroManager::CreateAHeroSubClass> (0x0021EF66,
// stlport_construct_pod216.cpp), so the 216-byte element is that class.
#include "../../../../GameEngine/Include/GameLogic/CreateAHeroManager.h"
class CreateAHeroManager::CreateAHeroSubClass { public: int a[54]; };
// bfme link decl-only begin
namespace _STL { template <> void _Construct<CreateAHeroManager::CreateAHeroSubClass, CreateAHeroManager::CreateAHeroSubClass>(CreateAHeroManager::CreateAHeroSubClass *, CreateAHeroManager::CreateAHeroSubClass const &); }
// bfme link decl-only end

// Instantiate the recovered operation and its required template dependencies.
template CreateAHeroManager::CreateAHeroSubClass * _STL::__uninitialized_fill_n<CreateAHeroManager::CreateAHeroSubClass *, unsigned int, CreateAHeroManager::CreateAHeroSubClass>(CreateAHeroManager::CreateAHeroSubClass *, unsigned int, CreateAHeroManager::CreateAHeroSubClass const &, _STL::__false_type const &);
