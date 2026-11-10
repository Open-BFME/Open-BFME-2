// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Native339B9A..339CCA and WB inihelp.cpp prove FX-list vector parser.
// Inline+noinline push_back body follows pinned STLport _vector.h and keeps
// native call while exposing const-reference behavior; five spill deltas close.
// _Construct preserves the retail null-placement check; helper49B is also exact.
// stlport
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVFXList@@V?$allocator@PBVFXList@@@_STL@@@_STL@@IAEXXZ:
// SlowDeathBehavior.cpp owns the kept copy (and _STLP_alloc_proxy::deallocate below is unused once _M_clear is external).
class FXList;
namespace _STL { template <> void vector<const FXList *, allocator<const FXList *> >::_M_clear(); }
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/GameClient/FXListStore.h"
extern FXListStore *TheFXListStore;
namespace _STL {template<> inline __declspec(noinline) void vector<const FXList*>::push_back(const FXList*const& v){
 if(_M_finish!=_M_end_of_storage._M_data){_Construct(_M_finish,v);++_M_finish;}else _M_insert_overflow(_M_finish,v,_IsPODType(),1UL,true);
}}

#include "../debug.h"


extern Debug *theDebug;
template<class T> Debug& operator<<(Debug&,const StringBase<T>&);
inline const StringBase<char>& FilenameBase(const AsciiString& asciiString){return *reinterpret_cast<const StringBase<char>*>(&asciiString);}
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
void iniParseFXListVec(INI *ini,void*,void*store,const void*) {
 _STL::vector<const FXList*>*v=static_cast<_STL::vector<const FXList*>*>(store);
 for(const char *token=ini->getNextToken();token;token=ini->getNextTokenOrNull()) {
  const FXList *fx=TheFXListStore->findFXList(token);
  v->push_back(fx);
  if(!fx && _strcmpi(token,"None"))
   !bfmeRva000387C0() || (_bfme_debugRecordCallsite(1),theDebug->SkipNext(),(theDebug->CrashBegin(0,0,0)<<"Unknown FX list "<<token<<" requested near line "<<static_cast<unsigned int>(ini->getLineNum())<<" of "<<reinterpret_cast<const StringBase<char>&>(ini->getFilename())).CrashDone(2));
 }
}
// bfme link decl-only begin
namespace _STL { template <> void _STLP_alloc_proxy<FXList const * *,FXList const *,_STL::allocator<FXList const *> >::deallocate(FXList const * *,unsigned int); }
namespace _STL { template <> void allocator<FXList const *>::deallocate(FXList const * *,unsigned int) const; }
// bfme link decl-only end
