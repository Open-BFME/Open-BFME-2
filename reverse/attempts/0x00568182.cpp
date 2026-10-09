// ??0?$vector@VRva00567BD7@@V?$allocator@VRva00567BD7@@@_STL@@@_STL@@QAE@I@Z
// partial score=0.85 date=2026-10-09
// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include <vector>
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva00567BD7 {
public:
 int action; bool flag; TargetRef00217D4C *ref; bool active;
 Rva00567BD7():action(0),ref(0),active(false){}
 Rva00567BD7(const Rva00567BD7 &);

};
namespace _STL {
 template<> Rva00567BD7 *uninitialized_fill_n<Rva00567BD7*,unsigned,Rva00567BD7>(Rva00567BD7*,unsigned,const Rva00567BD7 &);
}
template _STL::vector<Rva00567BD7>::vector(unsigned);
