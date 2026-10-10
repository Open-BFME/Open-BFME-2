// stlport
// cl: /O1 /MD /EHsc /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Typed erase copies used by native HeroSelectData removal5259B9.
// Hero12B id/unknown/flash comes from the matched hero interface views;
// Builder12B id/used/float comes from matched append525D9A.
// Each complete32B emission is a relocation twin of list<int> at438539.
#include <list>
struct HeroButtonInfo {int id,unknown,flash;};
struct BuilderButtonInfo {int id;bool used;char pad[3];float value;};
template _STL::list<HeroButtonInfo>::iterator _STL::list<HeroButtonInfo>::erase(_STL::list<HeroButtonInfo>::iterator);
template _STL::list<BuilderButtonInfo>::iterator _STL::list<BuilderButtonInfo>::erase(_STL::list<BuilderButtonInfo>::iterator);
