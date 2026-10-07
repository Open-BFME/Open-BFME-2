// ?refresh@Rva00264069ObserverPrefix@@QAEXXZ
// partial score=0.98 date=2026-10-07
// Native 264069..26412B complete RET. Accepted runtime caller 26A05D.
// Target proves receiver+8 object pointer and cached 76B/16B headers at
// +290/+2DC, object headers +10C/+94, GameLogic frame word +40, rowed
// copy/equality helpers, and LuaScriptEngine dispatch of old/new headers.
// Borrowed prefix names avoid asserting the original observer/field identities.
// 194B compiled; sole unresolved REL32 is unlanded 33605B. No new pin/global.
// Banked only: that dependency's ctor/dtor aliases and invoke are not linkable.
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "Object872.h"
class Rva00264069ObjectPrefix {public: char pad00[0x94]; BfmeObject872Header tag94; char padA4[0x10c-0xa4]; WeaponTemplateSetHead weapons10C;};
class Rva00264069LogicPrefix {public: char pad00[0x40]; unsigned frame40;};
class GameLogic;
extern GameLogic *TheGameLogic;
struct BfmeObjectEventDispatch {
 void rva00335FE1(const WeaponTemplateSetHead *,const WeaponTemplateSetHead *,void *);
 void rva0033605B(const BfmeObject872Header *,const BfmeObject872Header *,void *);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
bool Rva00045473Equal(const void *,const void *);
bool Rva002634E0Equal(const void *,const void *);
class Rva00264069ObserverPrefix {
public: void refresh();
private:
 char pad00[8]; Rva00264069ObjectPrefix *object08;
 char pad0C[0x290-0xc]; WeaponTemplateSetHead previousWeapons;
 BfmeObject872Header previousTag;
};
void Rva00264069ObserverPrefix::refresh() {
 Rva00264069ObjectPrefix *object=object08;
 if(((Rva00264069LogicPrefix *)TheGameLogic)->frame40<2) {
  previousWeapons=object->weapons10C;
  previousTag=object->tag94;
 }else {
  WeaponTemplateSetHead weapons(object->weapons10C);
  BfmeObject872Header tag(object->tag94);
  if(!Rva00045473Equal(&previousWeapons,&weapons)) {
   ((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva00335FE1(&weapons,&previousWeapons,object);
   previousWeapons=weapons;
  }
  if(!Rva002634E0Equal(&previousTag,&tag)) {
   ((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva0033605B(&tag,&previousTag,object);
   previousTag=tag;
  }
 }
}
