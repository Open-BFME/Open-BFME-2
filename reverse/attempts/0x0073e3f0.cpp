// ??1ShroudManagerImpl@@QAE@XZ
// partial score=0.97 date=2026-10-10
// cl: /O2 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
struct BfmeE32 {int a[8];};
namespace _STL {template<> deque<BfmeE32>::~deque();}
class BfmeThingCDE {public:void bfmeDtorCDE();};
class ShroudManagerImpl008FBA40Element {
 char storage[0xA8];
public:__declspec(noinline) ~ShroudManagerImpl008FBA40Element(){}
};
class ShroudManagerImpl {
 char prefix[0x2C];
 ShroudManagerImpl008FBA40Element *elements;
 BfmeThingCDE *nodes;
 char unknown34[8];
 _STL::deque<BfmeE32> records;
public:~ShroudManagerImpl();
};
ShroudManagerImpl::~ShroudManagerImpl() {
 while(nodes){BfmeThingCDE *node=nodes;node->bfmeDtorCDE();::operator delete(node);}
 delete[] elements;
}
