// ??A?$map@HUSBServer@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHUSBServer@@@_STL@@@3@@_STL@@QAEAAUSBServer@@ABH@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
struct SBServer {
 void *m_handle;
 SBServer():m_handle(0) {}
 __declspec(noinline) SBServer(const SBServer&);
 __declspec(noinline) ~SBServer();
};
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
typedef _STL::map<int,SBServer> ServerMap;
template SBServer& ServerMap::operator[](const int&);
