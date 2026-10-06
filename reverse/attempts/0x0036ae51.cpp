// ?rva0036AE51@Rva0036AE51View@@QAE?AV?$list@HV?$allocator@H@_STL@@@_STL@@XZ
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfmelist /Ivendor/stlport /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Scratch only: list<int> is a compiler-shape surrogate for proven one-word list elements, not original type evidence.
#include <list>
typedef _STL::list<int,_STL::allocator<int> > ListInt;
extern unsigned g_Va00E0362C;
struct Rva0036AE51View {
 void* context;
 const ListInt* source;
 ListInt rva0036AE51();
};
ListInt Rva0036AE51View::rva0036AE51() {
 if(context) {
  context=0;
  return ListInt(*source);
 }
 return ListInt(*reinterpret_cast<const ListInt*>(&g_Va00E0362C));
}
