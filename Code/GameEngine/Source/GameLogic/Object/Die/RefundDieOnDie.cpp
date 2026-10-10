// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// Native4852A8..485416 RET4. Owned RefundDie ctor485262 installs secondary
// Die interface84A64C at complete+10; slot0 is this callback. The neighboring
// Announce primary table84A61C ends before it, correcting the old attribution.
// BF1 clean RefundDieOnDie.cpp at575ba2b04 supplies refund/upgrade/filter and
// cash feedback semantics. Target data38/3C/40, cost324, Money90/stats3BC,
// UI slot1A0 and yellow text+10z are independently read from retail.
// The two-instruction float-to-int helper is the donor's x87 machinery:
// native requires FISTP with the current rounding mode, rather than the
// compiler's __ftol truncation sequence. No retail body is lifted.
#include "unicode_string.h"
#include "Lib/Coord3D.h"
extern "C" __declspec(dllimport) double __cdecl ceil(double);
__forceinline long fast_float2long_round(float value)
{
 long result;
 __asm {
  fld [value]
  fistp [result]
 }
 return result;
}
class DamageInfo;class UpgradeTemplate;class BfmeTab1026;class Rva0039B7AD;
class ObjectFilter {public:bool isValid()const;int index;};
class Rva003B0D7C{public:unsigned pad;unsigned balance;void rva003B0D7C(int,Rva0039B7AD*,bool);};
class Player {public:
 bool rva002AB87D(const UpgradeTemplate*)const;bool rva002AB2D9(BfmeTab1026*,bool)const;
 char pad00[0x90];Rva003B0D7C money;char pad98[0x3BC-0x98];int stats;
};
enum ObjectStatusTypes{status2=2,status19=19};
class Object {public:
 Player *getControllingPlayer()const;bool testStatus(ObjectStatusTypes)const;
 char pad00[0x38];Coord3D pos;char pad44[0x324-0x44];volatile float constructionCost;
};
struct RefundDieModuleData {char pad00[0x38];const UpgradeTemplate *upgradeRequired;volatile float refundPercent;ObjectFilter buildingRequired;};
class DieModule{friend class RefundDie;protected:bool isDieApplicable(const DamageInfo*)const;};
class Rva00484FE2Text {public:
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
virtual const UnicodeString*fetch(const char*,bool*);
};
class GameTextInterface;extern GameTextInterface*TheGameText;
class Rva00484FE2UI {public:
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
virtual void addFloatingText(const UnicodeString&,const Coord3D*,unsigned);
};
class InGameUI;extern InGameUI*TheInGameUI;
class RefundDie{public:virtual void onDie(const DamageInfo*);};
void RefundDie::onDie(const DamageInfo *damage)
{
 char *secondary=(char*)this;
 if(!((const DieModule*)(secondary-0x10))->isDieApplicable(damage))return;
 Object *obj=*(Object**)(secondary-8);
 if(!obj||obj->testStatus(status2)||obj->testStatus(status19))return;
 const RefundDieModuleData *data=*(const RefundDieModuleData**)(secondary-0xC);
 if(!data)return;
 Player *player=obj->getControllingPlayer();
 if(!player)return;
 if(data->upgradeRequired&&!player->rva002AB87D(data->upgradeRequired))return;
 if(data->buildingRequired.isValid()&&!player->rva002AB2D9((BfmeTab1026*)&data->buildingRequired,false))return;
 double cost=obj->constructionCost; float factor=data->refundPercent;
 int refund=fast_float2long_round((float)ceil((double)cost*(double)factor));
 if(refund) {
 player->money.rva003B0D7C(refund,(Rva0039B7AD*)&player->stats,true);
 UnicodeString text;
 text.format(((Rva00484FE2Text*)TheGameText)->fetch("GUI:AddCash",0),refund);
 Coord3D pos;pos.x=obj->pos.x;pos.y=obj->pos.y;pos.z=obj->pos.z+10.f;
 ((Rva00484FE2UI*)TheInGameUI)->addFloatingText(text,&pos,0xFFFFFF00U);
}
}
