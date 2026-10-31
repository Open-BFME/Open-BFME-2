// ?rva00278C7C@Drawable@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /EHs /EHc-
//
// Drawable::flashAsSelected(const RGBColor *) at retail 0x00278C7C (381B; the
// ledger keeps the pinned address name, whose parameter is the donor's colour
// pointer passed as an int). Reference: BFME1 game/GameEngine/Source/GameClient/
// Drawable.cpp flashAsSelected, extended with the skip-kind early out and the
// recursive group-list path that the retail body adds. Target-derived facts:
// Drawable+0x64 envelope (lazily built by the rowed 0x271826 ctor), Drawable+0xFC
// object, Object+0x1A4 module with getGroup() in slot 31, GlobalData+0xB54
// saturation factor and +0xB58 house-colour flag, the rowed RGBColor::setFromInt
// (0x4EDF), Object::getIndicatorColor (0x28B026) and TintEnvelope::play
// (0x2744F2). The group/module owners are structural views; their names are not
// established. /EHs /EHc- keeps the list destructor's state reset and the throw()
// ctor removes the new-expression EH, as in retail.
//
// Codegen: the colour is computed in two sibling blocks (the call-written
// RGBColor, then a fresh one for the result) so the white fallback stays in
// registers and both objects share retail's single stack slot; the saturation
// half-factor reuses `factor` in place (factor *= 0.5f) as retail's mulss does.
// stlport
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
class Object;
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<Object *> >::deallocate(_List_node<Object *>* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<Object *>*,_List_node<Object *>,allocator<_List_node<Object *> > >::deallocate(_List_node<Object *>* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<_List_node<Object *> >&>(*this),(_List_node<Object *>*)0).deallocate(__p,__n);
}
}

class Drawable;
#include "../Common/Thing/thing.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
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
class GlobalData;
extern GlobalData *TheWritableGlobalData;	// 0x009FE758
struct GlobalDataFlashView
{
 char pad[0xb54];
 float saturation;	// +0xB54
 bool houseColor;	// +0xB58
};
#define FLASH_GD ((const GlobalDataFlashView *)TheWritableGlobalData)
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
  float r,g,b;
  {
   RGBColor c1;
   if (FLASH_GD->houseColor) c1.setFromInt(obj->getIndicatorColor());
   else c1.setFromInt(-1);
   float factor=FLASH_GD->saturation;
   r=c1.red*factor; g=c1.green*factor; b=c1.blue*factor;
   factor*=0.5f;
   r-=factor; g-=factor; b-=factor;
  }
  {
   RGBColor out;
   out.red=r; out.green=g; out.blue=b;
   envelope->play(&out,0,4,1);
  }
 }
}
