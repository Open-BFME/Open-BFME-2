// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native3F9DE2..3F9EC8 complete230B RET4 is eye-tower vtableC375F0 slot3.
// WB1059AD0 corroborates Version1/int count/8B points/clear/rebuild and save
// paths; point scalar identities remain opaque. Native vector+3C uses the
// established Pod8 range-erase3FA4DB and E8 push_back539A2E providers.
// Loading rethrows in GameLogic modes5/1 then rebuilds in the FP scope.
// The existing guard body4224C must stay visible: it does not access its
// receiver, allowing its empty local to share saved-this slot[-10]. This
// reproduces the exact frame without a barrier or synthetic local union.
// EH handlerB843BF -> FuncInfoD30564: one state, unwindD3055C -> B843B7
// LEA[-10] JMP guard dtor42262. Guard depth is GameLogic+1B4.
// The method keeps an address-derived name: WB does not name this body.
#include <vector>
struct BfmeE8
{
public:
	unsigned int a; // +0x00
	unsigned int b; // +0x04
};
struct BfmePod8 {int a[2];};
namespace _STL {
template<> BfmePod8 *vector<BfmePod8>::erase(BfmePod8*,BfmePod8*);
template<> void vector<BfmeE8>::push_back(const BfmeE8&);
}
#include "../../Common/System/XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"
class GameLogic;extern GameLogic *TheGameLogic;
struct TowerGameLogicView {char pad[0x110];int mode;char gap[0x1b4-0x114];int fpDepth;};
#include "../../../Include/GameLogic/Rva000421FD.h"
class Rva0004224C {public:
 __declspec(noinline) Rva0004224C *rva0004224C(){if(TheGameLogic)((Rva000421FD*)TheGameLogic)->rva000421FD();return this;}
 __declspec(noinline) Rva0004224C(){if(TheGameLogic)((Rva000421FD*)TheGameLogic)->rva000421FD();}
 ~Rva0004224C(){if(TheGameLogic)--((TowerGameLogicView*)TheGameLogic)->fpDepth;}
};
class TowerPoints:public _STL::vector<BfmeE8> {public:
 void clear(){((_STL::vector<BfmePod8>*)this)->erase((BfmePod8*)begin(),(BfmePod8*)end());}
};
class LivingWorldEyeTower {public:
 void xfer(Xfer*);
 void rva003F9B5A();
 char prefix[0x3c];TowerPoints points;
};
void LivingWorldEyeTower::xfer(Xfer*xfer) {
 xfer->Version1();
 int count=points.size();
 *xfer == count;
 if(xfer->IsLoading()) {
  points.clear();
  for(int i=0;i<count;++i) {
   BfmeE8 point;
   *xfer == reinterpret_cast<Coord2D &>(point);
   points.push_back(point);
  }
  if(TheGameLogic && (((TowerGameLogicView*)TheGameLogic)->mode==5 || ((TowerGameLogicView*)TheGameLogic)->mode==1)) throw;
  Rva0004224C guard;
  rva003F9B5A();
 } else {
  for(int i=0;i<count;++i) *xfer == reinterpret_cast<Coord2D &>(points[i]);
 }
}
