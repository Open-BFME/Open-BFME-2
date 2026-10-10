// ?rva0043979D@Rva00439E0C@@QAE_NPAVObject@@PAURva004393D6@@@Z
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /Oy- /MD /GX- /D_CRTIMP=
struct Coord3D {float x,y,z;};
class Object {public:int rva002933CD();const Coord3D*getPosition()const{return &pos;}private:char pad[0x38];Coord3D pos;};
class GlobalData {public:char pad[0x11CC];unsigned duration;};extern GlobalData*TheWritableGlobalData;
class GameLogic {public:char pad[0x40];unsigned frame;};extern GameLogic*TheGameLogic;
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
 unsigned frame=TheGameLogic->frame;
 if((unsigned char)obj->rva002933CD()&&frame>=record->refresh)rva00438D58(obj);
 ((Rva0043846D*)this)->rva0043846D(obj);
 return *record->node!=record->node ||frame<record->expiry||frame<record->refresh;
}
