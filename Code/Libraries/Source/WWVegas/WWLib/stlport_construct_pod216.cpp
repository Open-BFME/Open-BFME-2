// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@VCreateAHeroSubClass@CreateAHeroManager@@V12@@_STL@@YAXPAVCreateAHeroSubClass@CreateAHeroManager@@ABV12@@Z @0x0021EF66 45B: placement copy of the 216B CreateAHeroManager::CreateAHeroSubClass via rowed Rva0021E85A copy ctor 0x0021E85A. Callers in stlport_pod_vector_bodies.cpp (__uninitialized_copy/fill_n/push_back).
#include <new>
#include <vector>
class CreateAHeroManager
{
public:
    class CreateAHeroSubClass { public: int a[54]; };
};
class Rva0021E85A
{
public:
	Rva0021E85A(const Rva0021E85A &o);
};
namespace _STL {
template <> inline void _Construct<CreateAHeroManager::CreateAHeroSubClass, CreateAHeroManager::CreateAHeroSubClass>(CreateAHeroManager::CreateAHeroSubClass *__p, const CreateAHeroManager::CreateAHeroSubClass &__val)
{
	new ((void *)__p) Rva0021E85A((const Rva0021E85A &)__val);
}
}

#pragma inline_depth(0)
// ?bfmeEmitPod216Construct@@YAXPAVCreateAHeroSubClass@CreateAHeroManager@@ABV12@@Z present-unmatched
void bfmeEmitPod216Construct(CreateAHeroManager::CreateAHeroSubClass *p, const CreateAHeroManager::CreateAHeroSubClass &q)
{
	_STL::_Construct<CreateAHeroManager::CreateAHeroSubClass, CreateAHeroManager::CreateAHeroSubClass>(p, q);
}
#pragma inline_depth()
