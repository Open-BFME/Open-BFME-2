// ?rva00278C7C@Drawable@@QAEXH@Z
// partial score=0.9302 date=2026-10-05
// cl: /O1 /arch:SSE  /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /EHs /EHc-
// Target 0x00278C7C has inventory extent381B and is called recursively plus
// by matched Drawable selected-flag helper0x2796B8. Primary reference:
// BFME1 6583b3c1 game/GameEngine/Source/GameClient/Drawable.cpp flashAsSelected,
// extended from native evidence with skip-kind and recursive group list paths.
// The known getter/pool/ctor/play calls and member offsets are target-derived;
// opaque virtual owners are structural views, not asserted authentic names.
// Best trial396B: all instructions align except redundant3x5B white-color
// stores just before the saturation global load. /EHs /EHc- is necessary for
// the list destructor state reset; ctor throw() removes the new-expression EH.
// The inline RGBColor setter is fully exact76B at0x4EDF. No new pins landed
// for this attempted body; list<Object*> base dtor and indicator color need
// independently checked aliases before landing. Parent's int parameter is
// address-named and interpreted here as the donor RGBColor pointer.
// stlport
#include <list>
class Object;
class Drawable;
class Thing { public: Drawable *getDrawable() const; };
struct RGBColor { float red, green, blue; void setFromInt(int); };
inline void RGBColor::setFromInt(int color)
{
 const float scale = 1.0f / 255.0f;
 red = (float)((color >> 16) & 0xFF) * scale;
 green = (float)((color >> 8) & 0xFF) * scale;
 blue = (float)(color & 0xFF) * scale;
}
class TintEnvelope { public: void play(const RGBColor *,unsigned int,unsigned int,unsigned int); };
class Rva00271826 { public: Rva00271826() throw(); private: char body[0x50]; };
struct BfmeFlashTemplate { char pad[0x10c]; unsigned int bits10c; char pad110[4];unsigned int bits114; };
class BfmeFlashGroup
{
public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
virtual void slot74();
virtual void slot78();
virtual void slot7C();
virtual void slot80();
virtual void slot84();
virtual void slot88();
virtual void slot8C();
virtual void slot90();
virtual void slot94();
virtual void slot98();
virtual void slot9C();
virtual void slotA0();
virtual void slotA4();
virtual void slotA8();
virtual void slotAC();
virtual void slotB0();
virtual void slotB4();
virtual void slotB8();
virtual void slotBC();
virtual void slotC0();
virtual void slotC4();
virtual void slotC8();
virtual void slotCC();
virtual void slotD0();
virtual void slotD4();
virtual void slotD8();
virtual void slotDC();
virtual void slotE0();
virtual void slotE4();
virtual void slotE8();
virtual void slotEC();
virtual void slotF0();
virtual void slotF4();
virtual void slotF8();
virtual void slotFC();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void fillObjects(_STL::list<Object *> *);
};
class BfmeFlashModule
{
public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
virtual void slot74();
virtual void slot78();
virtual BfmeFlashGroup *getGroup();
};
class Object
{
public:
 int getIndicatorColor() const;
 void *vtable;
 BfmeFlashTemplate *m_template;
 char pad008[0x248];
 BfmeFlashModule *module;
};
class GlobalData
{
public:
 char pad[0xb54]; float saturation; bool houseColor;
};
extern const GlobalData *TheGlobalData;
class Drawable
{
public:
 void rva00278C7C(int colorArg);
 void *vtable;
 BfmeFlashTemplate *m_template;
 char pad008[0x5c];
 TintEnvelope *envelope;
 char pad068[0x94];
 Object *object;
};
void Drawable::rva00278C7C(int colorArg)
{
 if (m_template->bits10c & 0x10000000) return;
 Object *obj=object;
 BfmeFlashModule *module;
 if (obj && (obj->m_template->bits114 & 0x2000) && (module=obj->module)!=0)
 {
  BfmeFlashGroup *group=module->getGroup();
  if (group)
  {
   _STL::list<Object *> objects;
   group->fillObjects(&objects);
   _STL::list<Object *>::iterator end=objects.end();
   for (_STL::list<Object *>::iterator it=objects.begin();it!=end;++it)
   {
    if (*it)
    {
     Drawable *draw=((Thing *)*it)->getDrawable();
     if(draw) draw->rva00278C7C(colorArg);
    }
   }
   return;
  }
 }
 if (!envelope) envelope=(TintEnvelope *)new Rva00271826;
 const RGBColor *color=(const RGBColor *)colorArg;
 if (color)
  envelope->play(color,0,4,1);
 else if (obj)
 {
  RGBColor temp;
  if (TheGlobalData->houseColor) temp.setFromInt(obj->getIndicatorColor());
  else temp.setFromInt(-1);
  float factor=TheGlobalData->saturation;
  temp.red*=factor; temp.green*=factor;temp.blue*=factor;
  float half=factor*0.5f;
  temp.red-=half;temp.green-=half;temp.blue-=half;
  envelope->play(&temp,0,4,1);
 }
}
