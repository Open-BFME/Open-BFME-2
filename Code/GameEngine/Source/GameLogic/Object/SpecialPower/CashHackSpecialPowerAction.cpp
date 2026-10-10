// ?doSpecialPowerAtObject@CashHackSpecialPower@@UAEXPAVObject@@I@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// ZH CashHackSpecialPower.cpp at BF1 f98983a7d is the semantic guide.
// Target action starts at4C26D0,430B,ret8; special-power receiver is +10.
// The shared folded selector4C31A8 is owned by the neutral science-word
// selector in OCLSpecialPowerFindOCL.cpp. Its unsigned result is the amount
// payload here; OCL interprets the same proven 32-bit slot as an OCL pointer.
// WB125B700 independently establishes this action's identity and amount use;
// the ZH donor supplies behavior, while Object/Player/UI offsets below come
// from target access and the existing matched money/score providers.
#include "unicode_string.h"
#include "Coord3D.h"
enum ScienceType { SCIENCE_INVALID=-1 };
class Rva0039B795 {};
class Rva0039B7AD {};
class Rva003B0D7C { char pad[4];public:
 unsigned balance;
 unsigned int rva003B0CB3(unsigned,Rva0039B795*,bool);
 void rva003B0D7C(int,Rva0039B7AD*,bool);
 unsigned countMoney()const{return balance;}
};
class Player { public:
 bool hasScience(ScienceType)const;
 Rva003B0D7C *getMoney(){return reinterpret_cast<Rva003B0D7C*>(reinterpret_cast<char*>(this)+0x90);}
 Rva0039B795 *withdrawTracker(){return reinterpret_cast<Rva0039B795*>(reinterpret_cast<char*>(this)+0x3BC);}
 Rva0039B7AD *depositTracker(){return reinterpret_cast<Rva0039B7AD*>(reinterpret_cast<char*>(this)+0x3BC);}
};
struct CashHackScienceEntry {ScienceType science;int amount;};
struct CashHackDataView {char prefix[0x7C];CashHackScienceEntry *begin,*end,*capacity;int fallback;};
template<int N> class BitFlags {public:bool any()const;};
class Object {char pad[0x38];public:Coord3D pos;Player *getControllingPlayer()const;
 bool isDisabled()const{return reinterpret_cast<const BitFlags<11>*>(reinterpret_cast<const char*>(this)+0x1C8)->any();}
 const Coord3D *getPosition()const{return &pos;}
};
class Module {public:virtual ~Module();protected:CashHackDataView *m_data;};
class ObjectModule:public Module {protected:Object *m_object;};
class BehaviorModuleInterface {public:virtual void behaviorSlot0();};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {};
class SpecialPowerModuleInterface {public:
 virtual void doSpecialPower(unsigned)=0;
 virtual void doSpecialPowerAtObject(Object*,unsigned)=0;
 virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned)=0;
 virtual bool rva0049466D(const Coord3D*)=0;
};
class SpecialPowerModule:public BehaviorModule,public SpecialPowerModuleInterface {public:
 virtual void doSpecialPower(unsigned);
 virtual void doSpecialPowerAtObject(Object*,unsigned);
 virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned);
 virtual bool rva0049466D(const Coord3D*);
};
class Rva004C31A8ScienceSelector { public: unsigned select() const; };
class CashHackSpecialPower:public SpecialPowerModule {public:
 virtual void doSpecialPowerAtObject(Object*,unsigned);

};
class CashHackTextView {public:
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
 virtual void slot16();
 virtual const UnicodeString *fetch(const char*,bool*);
};
class GameTextInterface;extern GameTextInterface *TheGameText;
class CashHackUI {public:
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
 virtual void slot16();
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
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
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
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void addFloatingText(const UnicodeString&,const Coord3D*,int);
};
class InGameUI;extern InGameUI *TheInGameUI;
static inline const unsigned &minCash(const unsigned &a,const unsigned &b){return a<b?a:b;}
void CashHackSpecialPower::doSpecialPowerAtObject(Object *victim,unsigned options)
{
 if(m_object->isDisabled())return;
 if(!victim)return;
 SpecialPowerModule::doSpecialPowerAtObject(victim,options);
 Object *self=m_object;
 Rva003B0D7C *targetMoney=victim->getControllingPlayer()->getMoney();
 Rva003B0D7C *selfMoney=self->getControllingPlayer()->getMoney();
 if(targetMoney&&selfMoney){
  unsigned cash=targetMoney->countMoney();
  unsigned desired=((const Rva004C31A8ScienceSelector*)this)->select();
  cash=minCash(desired,cash);
  if(cash>0){
   targetMoney->rva003B0CB3(cash,victim->getControllingPlayer()->withdrawTracker(),true);
   selfMoney->rva003B0D7C(cash,self->getControllingPlayer()->depositTracker(),true);
   UnicodeString moneyString;
   moneyString.format(reinterpret_cast<CashHackTextView*>(TheGameText)->fetch("GUI:AddCash",0),cash);
   Coord3D pos;
   pos.x=self->getPosition()->x;pos.y=self->getPosition()->y;pos.z=self->getPosition()->z;pos.z+=20.0f;
   reinterpret_cast<CashHackUI*>(TheInGameUI)->addFloatingText(moneyString,&pos,0xff00ff00);
   moneyString.format(reinterpret_cast<CashHackTextView*>(TheGameText)->fetch("GUI:LoseCash",0),cash);
   pos.x=victim->getPosition()->x;pos.y=victim->getPosition()->y;pos.z=victim->getPosition()->z;pos.z+=30.0f;
   reinterpret_cast<CashHackUI*>(TheInGameUI)->addFloatingText(moneyString,&pos,0xffff0000);
  }
 }
}

// ZH GameClient/Color.h ARGB helper; this TU now owns its existing31B row.
int GameMakeColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha)
{ return (((alpha << 8) | red) << 8 | green) << 8 | blue; }
