// cl: /I. /O1 /G7 /Oy- /MD /GX- /D_CRTIMP=
// Rva00439E0C (invisibility manager view, TheGameLogic->getManager178()) per-object update, retail
// 0x0043979D..0x0043985D (192B), caller of 0x00439CF7 (WB InvisibilityManager add path). Evidence: native bytes
// and the callee rows 0x00438389 (info clear) 0x004389DB (record add) 0x0043822E (expiry max) 0x00438D58
// (local-player audio cue) 0x0043846D (post update); 0x0043966A and 0x00438E5B are unrowed members pinned by
// address. 0x0043822E and 0x00438D58 are ECX-preserving members of this class (renamed from free stdcall rows,
// bytes unchanged). Field names beyond the offsets in use are neutral.
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Object {public:int rva002933CD();const Coord3D*getPosition()const{return &pos;}private:char pad[0x38];Coord3D pos;};
class GlobalData {public:char pad[0x11CC];unsigned duration;};extern GlobalData*TheWritableGlobalData;
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Rva00438389 {public:Rva00438389&rva00438389();};
struct Rva004389DBInfo {unsigned detector;char pad[32];};
struct Rva004393D6 {void**node;unsigned expiry,refresh,other;};
class Rva0043846D {public:void rva0043846D(Object*);};
class Rva00439E0C {public:bool rva0043979D(Object*,Rva004393D6*);int rva0043966A(Object*,const Coord3D*,Rva004393D6*,Rva004389DBInfo*);bool rva00438E5B(Object*,int,Rva004393D6*,Rva004389DBInfo*,unsigned);void rva004389DB(Object*,Rva004389DBInfo*,int);void rva0043822E(Rva004393D6*,unsigned);void rva00438D58(Object*);};
bool Rva00439E0C::rva0043979D(Object*obj,Rva004393D6*record){
 Rva004389DBInfo info;((Rva00438389*)&info)->rva00438389();
 int result=rva0043966A(obj,obj->getPosition(),record,&info);
 if(rva00438E5B(obj,result,record,&info,TheWritableGlobalData->duration)){
  rva004389DB(obj,&info,(info.detector!=0)+1);
  rva0043822E(record,TheWritableGlobalData->duration);
 }
 unsigned frame=TheGameLogic->getFrame();
 if((unsigned char)obj->rva002933CD()&&frame>=record->refresh)rva00438D58(obj);
 ((Rva0043846D*)this)->rva0043846D(obj);
 return *record->node!=record->node ||frame<record->expiry||frame<record->refresh;
}
