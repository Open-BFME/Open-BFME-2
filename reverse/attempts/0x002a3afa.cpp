// ?selectMatchingAcrossRegion@InGameUI@@UAEHPAUIRegion2D@@@Z
// partial score=0.93 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "unicode_string.h"
#include "ascii_string.h"
#include <list>
#include <set>
class Object;
namespace _STL {
template<> _List_base<const Object*,allocator<const Object*> >::_List_base(const allocator<const Object*>&);
template<> _List_base<const Object*,allocator<const Object*> >::~_List_base();
}
class Object;
class Drawable;
enum ObjectID { INVALID_ID=0 };
enum ObjectStatusTypes { STATUS_ZERO=0 };
class ThingTemplate {
public:
 bool isEquivalentTo(const ThingTemplate *) const;
 char unknown000[0x110]; unsigned kind110; unsigned kind114;
};
class SelectionContain {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void __cdecl message(UnicodeString,...);
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual SelectionContain *slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void selectDrawable(Drawable *);
 virtual void slot67(_STL::list<const Object*> *);
};
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 bool isLocallyControlled() const;
 bool rva00292FAC() const;
 Drawable *getDrawable() const;
 void *vptr;
 ThingTemplate *m_template;
 char unknown008[0x74-8]; ObjectID id; ObjectID guardID;
 char unknown07c[0x250-0x7c]; SelectionContain *contain;
 char unknown254[0x274-0x254]; Object *containedBy;
};
class Drawable {
public:
 char unknown000[0xfc]; Object *object;
 char unknown100[4]; Drawable *next; char unknown108[0x43c-0x108]; bool selected;
};
class GameLogic { public: Object *findObjectByID(ObjectID); };
extern GameLogic *TheGameLogic;
class GameTextInterface {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual UnicodeString fetch(const char *,bool *exists=0);
 virtual UnicodeString fetch(const AsciiString &,bool *exists=0);
};
extern GameTextInterface *TheGameText;
class InGameUI {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void __cdecl message(UnicodeString,...);
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void selectDrawable(Drawable *);
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual int getSelectCount() const;
 virtual int getMaxSelectCount() const;
 virtual void slot72();
 virtual const _STL::list<Drawable*> *getAllSelectedDrawables() const;
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual int selectMatchingAcrossRegion(struct IRegion2D*);
 virtual void slot101();
 virtual bool getDisplayedMaxWarning() const;
 virtual void setDisplayedMaxWarning(bool);
};
extern InGameUI *TheInGameUI;


struct IRegion2D;
struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target*> TemplatePointerSet;
namespace _STL {
template<> TemplatePointerSet::set();

}
class Rva0029B667 : public TemplatePointerSet { public: ~Rva0029B667(); };
class DrawableList : public _STL::list<Drawable*> {public: ~DrawableList() throw();};
class Rva002A1B07 {public: Rva002A1B07(); const ThingTemplate *type; DrawableList selected; bool includeContained;};
int Rva002A1EF5(Drawable*,void*);
class View {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
#undef V
 virtual int iterateDrawablesInRegion(IRegion2D*,int(*)(Drawable*,void*),void*);
};
extern View *TheTacticalView;
class GameClient {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
 virtual Drawable *firstDrawable();
};
extern GameClient *TheGameClient;
class GameMessage { public:
 enum Type {CREATE_GROUP=0x3ea};
 void appendBooleanArgument(bool);
 void appendObjectIDArgument(ObjectID);
};
class MessageStream { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
 virtual GameMessage *appendMessage(GameMessage::Type);
};
extern MessageStream *TheMessageStream;
int InGameUI::selectMatchingAcrossRegion(IRegion2D *region) {
 const _STL::list<Drawable*> *selected=getAllSelectedDrawables();
 Rva0029B667 templates;
 Rva0029B667 containedTemplates;
 Rva001408C0Target *templateName;
 for(_STL::list<Drawable*>::const_iterator it=selected->begin();it!=selected->end();++it) {
  const Drawable *draw=*it;
  if(draw) {
   Object *object=draw->object;
   if(object && object->isLocallyControlled()) {
   templateName=reinterpret_cast<Rva001408C0Target*>(object->m_template);
   templates.insert(templateName);
   if(object->m_template->kind114&0x2000) {
    SelectionContain *contain=object->contain;
    if(contain) {
     SelectionContain *contained=contain->slot31();
     if(contained) {
      _STL::list<const Object*> units;
      contained->slot67(&units);
      for(_STL::list<const Object*>::const_iterator child=units.begin();child!=units.end();++child) {
       const Object *unit=*child;
       if(unit && !(unit->m_template->kind110&0x8000000)){templateName=reinterpret_cast<Rva001408C0Target*>(unit->m_template);containedTemplates.insert(templateName);}
      }
     }
    }
   }
  }
 }
 }
 if(templates.size()==0 && containedTemplates.size()==0)return -1;
 Rva002A1B07 data;
 int newSelectionCount=0;
 for(TemplatePointerSet::iterator it=templates.begin();it!=templates.end();++it) {
  data.type=reinterpret_cast<const ThingTemplate*>(*it);data.includeContained=false;
  if(region)newSelectionCount+=TheTacticalView->iterateDrawablesInRegion(region,Rva002A1EF5,&data);
  else {
   Drawable *temp=TheGameClient->firstDrawable();
   while(temp) {newSelectionCount+=Rva002A1EF5(temp,&data);temp=temp->next;}
  }
  setDisplayedMaxWarning(false);
 }
 for(TemplatePointerSet::iterator it=containedTemplates.begin();it!=containedTemplates.end();++it) {
  data.type=reinterpret_cast<const ThingTemplate*>(*it);data.includeContained=true;
  if(region)newSelectionCount+=TheTacticalView->iterateDrawablesInRegion(region,Rva002A1EF5,&data);
  else {
   Drawable *temp=TheGameClient->firstDrawable();
   while(temp) {newSelectionCount+=Rva002A1EF5(temp,&data);temp=temp->next;}
  }
  setDisplayedMaxWarning(false);
 }
 if(newSelectionCount>0) {
  GameMessage *teamMsg=TheMessageStream->appendMessage(GameMessage::CREATE_GROUP);
  teamMsg->appendBooleanArgument(false);
  for(_STL::list<Drawable*>::const_iterator it=data.selected.begin();it!=data.selected.end();++it) {
   const Drawable *draw=*it;
   if(draw && draw->object)teamMsg->appendObjectIDArgument(draw->object->id);
  }
 }
 return newSelectionCount;
}
