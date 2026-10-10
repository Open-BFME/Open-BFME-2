// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// Semantic donor: BF1 575ba2b04 VictorySystemConstructor.cpp; target native
// 4054E1..40559F fixes canonical12B subsystem plus SnapshotC, twenty player
// indices28,168B root78 and parameter vector120, grid pointers12C/130.
// The initializer405475C is a measured37B leaf of zero stores and cannot throw.
// The root/member operation names remain address-derived. Native1.0f is a
// compiler literal, not an address-bound global. Vector storage owns the
// existing63B cleanup405350; generic default base initialization is an exact
// byte-and-relocation twin of the existing211E58 constructor.
#include <vector>
typedef int Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva00404781 {public:__forceinline Rva00404781(){rva0040475C();}__declspec(nothrow) void rva0040475C();float first[20],second[20];unsigned flags0,flags1;};
struct Rva0040538FElement {char bytes[24];};
namespace _STL {template<>Rva0040538FElement*vector<Rva0040538FElement>::erase(Rva0040538FElement*,Rva0040538FElement*);}
typedef _STL::_Vector_base<Rva0040538FElement,_STL::allocator<Rva0040538FElement> > VictoryParameterBase;
struct Rva00405350:public VictoryParameterBase {__forceinline Rva00405350():VictoryParameterBase(_STL::allocator<Rva0040538FElement>()){}~Rva00405350();Rva0040538FElement*first(){return _M_start;}Rva0040538FElement*last(){return _M_finish;}};
class CellGrid;
class VictorySystem:public SubsystemInterface,public Snapshot {
public:VictorySystem();virtual ~VictorySystem();virtual void init();virtual void reset();virtual void update();virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const{return "VictorySystem";}virtual void xfer(Xfer*);virtual void rva00404DE5();
 float cellSize10;unsigned field14;float firstScale18,secondScale1c,field20,field24;
 int playerParameterIndex28[20];Rva00404781 root78;Rva00405350 parameters120;
 CellGrid*grids12c[2];bool initialized134;unsigned activeGrid138,currentPlayer13c;
};
VictorySystem::VictorySystem():cellSize10(0),field14(0),firstScale18(0),secondScale1c(0),field20(0),field24(1.0f),initialized134(false),activeGrid138(0),currentPlayer13c(2){
 for(int g=0;g<2;++g)grids12c[g]=0;
 for(int p=0;p<20;++p)playerParameterIndex28[p]=0;
 _STL::vector<Rva0040538FElement>*p=reinterpret_cast<_STL::vector<Rva0040538FElement>*>(&parameters120);p->erase(p->begin(),p->end());
}
