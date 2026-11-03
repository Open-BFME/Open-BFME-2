// ??1ShroudManagerImpl@@QAE@XZ
// cl: /O2 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
struct BfmeE32 {int a[8];};
namespace _STL {template<> deque<BfmeE32>::~deque();}
class BfmeThingCDE {public:void bfmeDtorCDE();};
#include "../../../../GameEngine/Include/Common/ShroudManagerCell.h"
class ShroudManagerImpl {
 char prefix[0x2C];
 ShroudManagerCell *elements;
 BfmeThingCDE *nodes;
 char unknown34[8];
 _STL::deque<BfmeE32> records;
public:~ShroudManagerImpl();
};
ShroudManagerImpl::~ShroudManagerImpl() {
 while(nodes){if(nodes!=0){BfmeThingCDE *node=nodes;node->bfmeDtorCDE();::operator delete(node);}}
 delete[] elements;
}
