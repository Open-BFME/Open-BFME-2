// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native1E311E..1E323B RET8; WBAD4730 BuffNugget::doFXObj provides
// purpose and selection order. Existing BF2 constructor/table establish
// the BuffNuggetFXNugget spelling, eight template strings and field offsets.
// BF1@575ba2b BuffNuggetFXNuggetConstructor.cpp is the family/layout lead;
// target adds ship/monster choices. Retain the existing class spelling.
// Retail vtable7DD9B4 slot2 names this complete285B implementation.
// All called providers already exist; no original name is asserted for
// the neutral Drawable buff call views. Object+4 is the measured template
// pointer; the flags view claims only the seven accessed words, not the
// complete ThingTemplate ABI. The secondary Object argument is unused.
#include "ascii_string.h"
struct RGBColor {float red,green,blue;};
class Drawable;
class Object {public:Drawable*getDrawable()const;};
class ThingTemplate;
class ThingFactory {public:const ThingTemplate*findTemplate(const AsciiString&);};
extern ThingFactory *TheThingFactory;
class Rva00271BCC {public:void rva00271BCC(int,int);};
class Rva00271B5C {public:void rva00271B5C(int,void*,int,int,float);};
struct BuffTemplateKindView {char prefix[0x108];unsigned flags[7];};
class BuffNuggetFXNugget {public:
 virtual ~BuffNuggetFXNugget();virtual void slot4();
 virtual void doFXObj(const Object*,const Object*)const;
 char prefix[0x144];int type;bool complex;char gap[3];unsigned lifeTime;
 AsciiString generic,orc,infantry,cavalry,troll,mumakil,ship,monster;
 float extrusion;RGBColor color;
};
void BuffNuggetFXNugget::doFXObj(const Object*primary,const Object*)const{
 if(!primary)return;
 Drawable *drawable=primary->getDrawable();if(!drawable)return;
 if((int)lifeTime<=0){((Rva00271BCC*)drawable)->rva00271BCC(type,0);return;}
 if(complex){
  ((Rva00271B5C*)drawable)->rva00271B5C(type,0,(int)lifeTime,(int)&color,extrusion);return;
 }
 const ThingTemplate *buff;
 {
  const BuffTemplateKindView *thing=*(const BuffTemplateKindView* const*)((const char*)primary+4);
  if(thing->flags[3]&(1U<<13))return;
  const AsciiString *name;
  if(thing->flags[0]&(1U<<9))name=&cavalry;
  else if(thing->flags[3]&(1U<<12))name=&orc;
  else if(thing->flags[0]&(1U<<8))name=&infantry;
  else if(thing->flags[5]&(1U<<16))name=&troll;
  else if(thing->flags[5]&(1U<<25))name=&mumakil;
  else if(thing->flags[5]&(1U<<31))name=&ship;
  else if(thing->flags[0]&(1U<<10))name=&monster;
  else name=&generic;
  buff=TheThingFactory->findTemplate(*name);if(!buff)return;
 }
 ((Rva00271B5C*)drawable)->rva00271B5C(type,(void*)buff,(int)lifeTime,(int)&color,extrusion);
}
