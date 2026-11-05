// ?parseFXListDefinition@FXListStore@@SAXPAVINI@@@Z
// cl: /Ireference/shims/bfmealloc /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// BFME1 cee35b7d8 FXListStoreParse.cpp and ZH FXList.cpp identify the parser.
// Native1E2CAE..1E2DB3 independently proves the pointer map at0C and override
// vector20 plus the 40-byte named record and full 19-entry field table7DC720.
// The retail override branch reads the saved node after the erase call; keep
// that order rather than replacing it with the BFME1 value-map clear path.
// Native constructor1E2747 owns the record class; its original spelling is
// uncertain. No payload-type claim is made by the pointer-vector ABI view.
// Keep the inlined unsigned comparison without emitting a nonretail
// external max template. The overload preserves reference-return semantics.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
#include <hash_map>
#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}

namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
#include "ascii_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline vector<void *,allocator<void *> >::~vector() { _Destroy(this->_M_start, this->_M_finish); } }
// Bind to the kept retail copy instead of emitting this unit's own.
// Bind to the kept retail copy instead of emitting this unit's own.
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
// bfme link decl-only end
struct FieldParse;class INI;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
enum NameKeyType{NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff};
namespace rts {template<class T>struct hash {size_t operator()(const T&x)const{return (size_t)x;}};}
#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator*TheNameKeyGenerator;
class FXList {public:static void parseCullingInfo(INI*,void*,void*,const void*);};
class Rva001E2747:public FXList {public:Rva001E2747(const AsciiString&);virtual ~Rva001E2747();char opaque04[0x20];bool override24;};
class SoundFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class EvaEventFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class RayEffectFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class LightPulseFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class CameraShakerVolumeFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class ViewShakeFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class AttachedModelFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class TerrainScorchFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class ParticleSystemFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class FXListAtBonePosFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class CursorParticleSystemFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class DynamicDecalFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class LaserFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class TintDrawableFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class BuffNuggetFXNugget{public:static void parse(INI*,void*,void*,const void*);};
void Rva001E1890Parse(INI*,void*,void*,const void*);
// Canonical table owner, following BFME1's extern FieldParse declaration.
extern const FieldParse TheFXListFieldParse[]={
{"Sound",SoundFXNugget::parse,0,0},
{"EvaEvent",EvaEventFXNugget::parse,0,0},
{"RayEffect",RayEffectFXNugget::parse,0,0},
{"LightPulse",LightPulseFXNugget::parse,0,0},
{"CameraShakerVolume",CameraShakerVolumeFXNugget::parse,0,0},
{"ViewShake",ViewShakeFXNugget::parse,0,0},
{"AttachedModel",AttachedModelFXNugget::parse,0,0},
{"TerrainScorch",TerrainScorchFXNugget::parse,0,0},
{"ParticleSystem",ParticleSystemFXNugget::parse,0,0},
{"ParticleSysBone",Rva001E1890Parse,0,0},
{"FXListAtBonePos",FXListAtBonePosFXNugget::parse,0,0},
{"CursorParticleSystem",CursorParticleSystemFXNugget::parse,0,0},
{"DynamicDecal",DynamicDecalFXNugget::parse,0,0},
{"Laser",LaserFXNugget::parse,0,0},
{"CullingInfo",FXList::parseCullingInfo,0,0},
{"TintDrawable",TintDrawableFXNugget::parse,0,0},
{"BuffNugget",BuffNuggetFXNugget::parse,0,0},
{"PlayEvenIfShrouded",INI::parseBool,0,0x10},
{0,0,0,0}};
class ModuleData;
typedef _STL::hash_map<NameKeyType,Rva001E2747*,rts::hash<NameKeyType>,_STL::equal_to<NameKeyType> > FXListMap;
class FXListStore{public:static void parseFXListDefinition(INI*);char opaque00[0xc];FXListMap fxmap;_STL::vector<Rva001E2747*> overrides;};extern FXListStore*TheFXListStore;
void FXListStore::parseFXListDefinition(INI*ini){
 const char*c=ini->getNextToken(0);
 NameKeyType key=TheNameKeyGenerator->nameToKey(c);
 FXListMap::iterator it=TheFXListStore->fxmap.find(key);
 if(it!=TheFXListStore->fxmap.end()&&ini->m_loadType==5){
  TheFXListStore->fxmap.erase(it);
  Rva001E2747*old=it->second;
  // Retail uses the existing four-byte pointer-vector provider. It accesses
  // only pointer storage; the stored object remains the target FX-list record.
  if(old){old->override24=true;((_STL::vector<const ModuleData*>*)&TheFXListStore->overrides)->push_back(*(const ModuleData**)&old);}
 }
 Rva001E2747*fxl=new Rva001E2747(c);
 TheFXListStore->fxmap[key]=fxl;
 ini->initFromINI(fxl,TheFXListFieldParse);
}
