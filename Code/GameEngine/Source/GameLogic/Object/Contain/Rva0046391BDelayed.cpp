// cl: /O1 /Oy- /G7 /MD /DNDEBUG /ICode/GameEngine/Source/Common
// Native46391B..4639D5 RET0; rowed release4640BE calls helper on this minus10 and established pin owns void argless ABI. Countdown E4 EC and reporter E8; notice secondary20 slotA4 then rowed Drawable hide report294D61 Object list find29B694 and GameLogic destroy242C09. Explicit search value copy preserves native register and home lifetimes; full186 exact and no new pins. Purpose and full class remain address-derived; t=4 model=gpt-6.1-sol
// stlport
#include <list>
#include <algorithm>
class Object;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Drawable {public:void setDrawableHidden(bool);};
class Object {public:Drawable *getDrawable() const;};
class Rva00294D61 {public:void report(Object*,int);};
namespace _STL {template<> list<Object*>::iterator find(list<Object*>::iterator,list<Object*>::iterator,Object *const&);}
#define V(n) virtual void s##n()=0;
class Rva0046391BNotice {public:
V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) 
virtual void sA4(Object*,int)=0;
};
#undef V
class Rva00463A81 {public:
 void rva0046391B();
 char p00[0x54]; _STL::list<Object*> objects;
 char p58[0xE4-0x58];ObjectID pending;ObjectID reporter;int frames;
};
void Rva00463A81::rva0046391B(){
 if(pending && frames>0 && --frames==0){
 Object *object=TheGameLogic->findObjectByID(pending);
 Object *search=object;
 if(object){
 ((Rva0046391BNotice*)((char*)this+0x20))->sA4(object,0);
 object->getDrawable()->setDrawableHidden(true);
 Object *other=TheGameLogic->findObjectByID(reporter);
 if(other)((Rva00294D61*)other)->report(object,1);
 if(_STL::find(objects.begin(),objects.end(),search)==objects.end())
 TheGameLogic->destroyObject(search);
 }
 }
}
