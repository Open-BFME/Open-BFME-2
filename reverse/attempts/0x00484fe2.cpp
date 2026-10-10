// ?rva00484FE2@PillageModule@@UAEXHPAVObject@@@Z
// partial score=0.9115285181 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// Native484FE2..485123323B RET8; vtable84A514 slot0 at Pillage+10.
// Pillage class identity and amount/event/filter fields from owned ctor and
// parse table. Original callback name and first argument meaning unknown.
// Target transfers victim money to owner after filter/threshold, then emits
// GUI:AddCash at owner position plus GeometryInfo height. The money and
// feedback skeleton is shared with owned CashHack and TerrainResource units;
// no clean BF1/ZH Pillage callback donor was found. Native offsets/ABI above
// are target facts; callback semantics are inferred from those calls.
// Volatile cached-data operand restores its native spill and owner-player
// register; remaining frame14 vs10 and string/coordinate slot differences.
#include "unicode_string.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "Lib/Coord3D.h"
class Object;class Player;
class Rva2225E0Filter {public:bool accepts(Object*,Player*);char data[4];};
struct PillageModuleData {char pad[8];unsigned amount,eventThreshold;Rva2225E0Filter filter;};
class Rva0039B795;class Rva0039B7AD;
class Rva003B0D7C {public:unsigned pad;unsigned balance;unsigned rva003B0CB3(unsigned,Rva0039B795*,bool);void rva003B0D7C(int,Rva0039B7AD*,bool);};
class Player {public:char pad[0x90];Rva003B0D7C money;char pad98[0x280-0x98];unsigned color;char pad284[0x3bc-0x284];unsigned stats;};
class GeometryInfo {public:float getMaxHeightAbovePosition()const;};
class Object {public:Player*getControllingPlayer()const;char pad[0x38];Coord3D pos;char pad44[0xa8-0x44];GeometryInfo geometry;};
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
class PillageModule {public:
virtual void rva00484FE2(int,Object*);
char pad[4];unsigned events;
const PillageModuleData*data()const{return *(const PillageModuleData*const*)((const char*)this-0xc);}
Object*owner()const{return *(Object*const*)((const char*)this-8);}
};
void PillageModule::rva00484FE2(int,Object*victim)
{
 const PillageModuleData*d=data();
 const PillageModuleData *volatile saved=d;
 if(!d)return;
 Object*self=owner();
 if(!self)return;
 if(!((Rva2225E0Filter*)&d->filter)->accepts(victim,0))return;
 ++events;
 if(events<d->eventThreshold)return;
 events=0;
 Player*targetPlayer=victim->getControllingPlayer();
 Player*selfPlayer=self->getControllingPlayer();
 unsigned maxAmount=saved->amount;_ReadWriteBarrier();
 unsigned amount=maxAmount<targetPlayer->money.balance?maxAmount:targetPlayer->money.balance;
 unsigned cash=targetPlayer->money.rva003B0CB3(amount,(Rva0039B795*)&targetPlayer->stats,true);
 if(cash==0)return;
 selfPlayer->money.rva003B0D7C(cash,(Rva0039B7AD*)&selfPlayer->stats,true);
 UnicodeString text;
 text.format(((Rva00484FE2Text*)TheGameText)->fetch("GUI:AddCash",0),cash);
 Coord3D pos;pos.x=self->pos.x;pos.y=self->pos.y;pos.z=self->pos.z;
 pos.z+=self->geometry.getMaxHeightAbovePosition();
 unsigned color=self->getControllingPlayer()->color|0xe6000000;
 ((Rva00484FE2UI*)TheInGameUI)->addFloatingText(text,&pos,color);
}
