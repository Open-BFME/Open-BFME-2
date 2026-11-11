// cl: /DNDEBUG /MD /O1 /G7 /arch:SSE
// Native 0042AF97..0042B038: degenerate pixel-region probe gated by force
// attack mode. ZH CommandXlat selection handling supplies semantic context;
// this BFME2 helper's name is unknown. Measured offsets and virtual slots
// come from this complete 161-byte body. Child/container interpretation of
// +274/+250 is structural, not a recovered target member identity.
// The header inlines below are only expanded here (no reloc to them); the COMDATs this unit still emits are not
// retail's, so they get TU-local names instead of colliding with the rowed bodies.
#define width width_RV
#define height height_RV
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
union GameMessageArgumentType {int integer;IRegion2D pixelRegion;};
#include "../../../Include/Common/MessageStream.h"
enum ObjectStatusTypes;
class Object {public:bool testStatus(ObjectStatusTypes)const;};
#include "../../../Include/GameClient/Drawable.h"
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
#include "../../../Include/GameClient/InGameUI.h"
class TacticalView {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual Drawable*pickDrawable(const ICoord2D*,bool,int);
};
extern InGameUI*TheInGameUI;extern class View*TheTacticalView;extern GameLogic*TheGameLogic;
#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar*TheControlBar;
// Native82B3EA pushes msg then MOV ECX,EDI (CommandTranslator receiver);
// WB E7CBE0 case18 confirms receiver. Body never reads this, so old stdcall
// owner reproduced bytes while removing the caller receiver load.
#include "../../../Include/GameClient/CommandTranslator.h"
void CommandTranslator::rva0042AF97(GameMessage*msg){
 if(TheInGameUI->field8B8)return;
 const IRegion2D&region2D=msg->getArgument(0)->pixelRegion;
 if(region2D.height()!=0||region2D.width()!=0)return;
 Drawable*draw=((TacticalView*)TheTacticalView)->pickDrawable(&region2D.lo,false,4);
 if(!draw)return;
 Object*obj=draw->m_object;if(!obj)return;
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
