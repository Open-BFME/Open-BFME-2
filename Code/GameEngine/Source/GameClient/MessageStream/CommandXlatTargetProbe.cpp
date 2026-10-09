// cl: /DNDEBUG /MD /O1 /G7 /arch:SSE
// Native 0042AF97..0042B038: degenerate pixel-region probe gated by force
// attack mode. ZH CommandXlat selection handling supplies semantic context;
// this BFME2 helper's name is unknown. Measured offsets and virtual slots
// come from this complete 161-byte body. Child/container interpretation of
// +274/+250 is structural, not a recovered target member identity.
#include "../../Common/GameLogicObjectLookupView.h"
struct ICoord2D {int x,y;};
struct IRegion2D {ICoord2D lo,hi;int width()const{return hi.x-lo.x;}int height()const{return hi.y-lo.y;}};
union GameMessageArgumentType {int integer;IRegion2D pixelRegion;};
class GameMessage {public:const GameMessageArgumentType*getArgument(int)const;};
enum ObjectStatusTypes;
class Object {public:bool testStatus(ObjectStatusTypes)const;};
class Drawable {public:char gap0[0xfc];Object*object;};
class Rva0042AF97Container {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();
 virtual void s12();virtual void s13();virtual void s14();virtual void s15();
 virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void s20();virtual void s21();virtual void s22();virtual void s23();
 virtual void s24();virtual void s25();virtual void s26();virtual void s27();
 virtual void s28();virtual void s29();virtual void s30();virtual int s31();
};
struct Rva0042AF97ObjectFields {char gap0[0x78];ObjectID linkedID;char gap7c[0x250-0x7c];Rva0042AF97Container*container;char gap254[0x274-0x254];Object*linked;};
class InGameUI {public:char gap0[0x8b8];bool forceAttack;};
class TacticalView {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual Drawable*pickDrawable(const ICoord2D*,bool,int);
};
extern InGameUI*TheInGameUI;extern TacticalView*TheTacticalView;extern GameLogic*TheGameLogic;
class ControlBar {public:int rva005399D0Check(Object*);};
extern ControlBar*TheControlBar;
void __stdcall Rva0042AF97Handle(GameMessage*msg){
 if(TheInGameUI->forceAttack)return;
 const IRegion2D&r=msg->getArgument(0)->pixelRegion;
 if(r.height()!=0||r.width()!=0)return;
 Drawable*draw=TheTacticalView->pickDrawable(&r.lo,false,4);
 if(!draw)return;
 Object*obj=draw->object;if(!obj)return;
 if(obj->testStatus((ObjectStatusTypes)38)){
  Rva0042AF97ObjectFields*fields=reinterpret_cast<Rva0042AF97ObjectFields*>(obj);
  Object*linked=fields->linked;
  if(!linked){linked=TheGameLogic->findObjectByID(fields->linkedID);if(!linked)return;}
  Rva0042AF97Container*container=reinterpret_cast<Rva0042AF97ObjectFields*>(linked)->container;
  int accepts=container?container->s31():0;if(!accepts)return;
  obj=linked;
 }
 TheControlBar->rva005399D0Check(obj);
}
