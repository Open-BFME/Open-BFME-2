// ??$_S_sort@HV?$allocator@H@_STL@@VRva004CEAB7@@@_STL@@YAXAAV?$list@HV?$allocator@H@_STL@@@0@VRva004CEAB7@@@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmelist /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
class Rva004CEAB7 {
public: bool rva004CEAB7(void *,void *);
float x,y,z;
Rva004CEAB7(const Rva004CEAB7& a):x(a.x),y(a.y),z(a.z){}
bool operator()(int a,int b) {return rva004CEAB7((void*)a,(void*)b);}
};
void Rva004CEB76(_STL::list<int> &that,Rva004CEAB7 comp) {
_STL::_S_sort(that,comp);
}
