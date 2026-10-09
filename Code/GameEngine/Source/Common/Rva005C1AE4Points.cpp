// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ?rva005C1AE4@Rva005C1A36@@QAEHH@Z @0x005C1AE4 73B
// Slot 2 of Rva005C1A36's vtable 0x008743DC: the Points value for a faction
// index. Builds a by-value AsciiString from the faction table 0x009BE9B0,
// fetches the UserPreferences from the object held at +0x2C through its
// slot 2 (0x08), and calls the rowed Points getter 0x005358C3.
// Retail keeps the argument temporary live (state 0) across the slot-2 call
// and disarms it only before the final call. A direct `m_held->v2()->...`
// disarms before the slot-2 call (the banked 0.90 attempt); an inline
// accessor gives retail's order. Retail also keeps that accessor out of line
// at 0x005C1A85 (8B, `mov ecx,[ecx+0x2c]; mov eax,[ecx]; jmp [eax+8]`, no
// references).
#include "ascii_string.h"
#include "unicode_string.h"


class Rva005DDE01;
class UserPreferences
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12)
#undef V
	// Slot 13 takes the current user name (0x005C1ABA).
	virtual void v13(const UnicodeString &name);

	int rva005358C3(AsciiString arg);

AsciiString rva0053755A(AsciiString);
AsciiString rva00537616(AsciiString);
int rva00535CE4(AsciiString);
int rva00535FBA();
int rva00535BF6(AsciiString);
int rva00535C40();
int rva00535D75(AsciiString);
int rva00535E06(AsciiString);
int rva00535E97(AsciiString);
int rva00535F28(AsciiString);
float rva0053590D(AsciiString);
float rva005359A9(AsciiString);
float rva00535A45(AsciiString);
float rva00535AE1(AsciiString);
int rva005373AF();
int rva0053734E(AsciiString);
int rva00536CA8(AsciiString);
int rva00536D39(AsciiString);
int rva00536DCA(AsciiString);
int rva00536E5B(AsciiString);
int rva00536EEC(AsciiString);
int rva00536F7D(AsciiString);
int rva00537305();
int rva0053604B();
int rva005360DC();
int rva0053616D();
int rva005362B2(AsciiString);
int rva00536343(AsciiString);
int rva005363D4(AsciiString);
int rva00536465(AsciiString);
int rva005364F6(AsciiString);
int rva00536587(AsciiString);
int rva00536618(AsciiString);
int rva005366A9(AsciiString);
int rva0053673A(AsciiString);
int rva005367CB(AsciiString);
int rva00536815(AsciiString);
int rva005368A6(AsciiString);
int rva00536937(AsciiString);
int rva00536A64(AsciiString);
float rva005369CC(AsciiString);
int rva00536AF5(AsciiString);
int rva00536B86(AsciiString);
int rva00536C17(AsciiString);
int rva0053700F();
int rva005370D2();
AsciiString rva005376D2();AsciiString rva005377B6();
};

class Holder
{
public:
	virtual void v0();
	virtual void v1(void *owner);
	virtual UserPreferences *v2();
};

class Rva005C1A36
{
public:
	virtual void v0();
	virtual void v1();
	virtual int v2(int idx);
	virtual int rva005C1AE4(int idx);
	void rva005C1ABA(const UnicodeString &name);
	// Unrowed 0x005DD48C (353 bytes), pinned by address.
	void rva005DD48C();
	UserPreferences *prefs() { return m_held->v2(); }
private:
	char m_pad[0x28];
	Holder *m_held;
};

static const char *kFactions[] = { "Men", "Elves", "Dwarves", "Isengard", "Mordor", "Wild" };

int Rva005C1A36::rva005C1AE4(int idx)
{
	return prefs()->rva005358C3(AsciiString(kFactions[idx]));
}

// ?rva005C1ABA@Rva005C1A36@@QAEXABVUnicodeString@@@Z @0x005C1ABA 42B
// (pinned so far as Rva005C1ABA): the skirmish screen's +0x668 member takes
// the new current user name: the held object's preferences get it (slot
// 13), the holder is told (slot 1, with this) and 0x005DD48C refreshes.
void Rva005C1A36::rva005C1ABA(const UnicodeString &name)
{
	m_held->v2()->v13(name);
	m_held->v1(this);
	rva005DD48C();
}

// Native5C1B2D..5C1BDE, complete177B cdecl hidden UnicodeString return.
// WB1592B10 and SIDE: key prove faction-label lookup with wide dash fallback.
// Canonical strings reproduce hidden-return construction flag and four EH
// lifetime states; fetch uses witnessed virtual slot38. Original name unknown.
class GameTextInterface {public:
#define V(n) virtual void s##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
virtual UnicodeString fetch(const AsciiString&,bool*);
};
extern GameTextInterface *TheGameText;
UnicodeString Rva005C1B2D(const AsciiString &faction){
 UnicodeString result((const unsigned short*)L"-");
 if(!((const StringBase<char>*)&faction)->isEmpty()){
  AsciiString label("SIDE:");label+=faction;
  result=TheGameText->fetch(label,0);
 }
 return result;
}

// Native5C1BDE..5C259B code plus26 DWORD switch entries through5C2603.
// WB15916B0 callgraph and recovered integer/ratio/time display records
// guide the37-row/six-faction persistent-table builder. Its original receiver
// class is unknown; do not infer it from the adjacent Rva005C1A36 methods.
// Native LEA EDI,[ECX+8] establishes the used preferences subobject only.
// Receiver embeds
// UserPreferences at8; original builder name is unknown.
struct BfmeStringRecord005DDD40{UnicodeString text;unsigned int word;};
class Rva005DD822:public BfmeStringRecord005DDD40 {public:Rva005DD822(unsigned int);};
class Rva005DD8E0:public BfmeStringRecord005DDD40 {public:Rva005DD8E0(float,float);};
class Rva005DDED5:public BfmeStringRecord005DDD40 {public:Rva005DDED5(unsigned int);};
class Rva005DD772:public BfmeStringRecord005DDD40 {public:Rva005DD772(const UnicodeString&,float);};
class Rva005DDE01{public:void rva005DDE01(unsigned int,unsigned int,const BfmeStringRecord005DDD40&,bool);};
class GameStats{public:class Persistent{public:void CalculateTotalColumn(float);};};
static __forceinline float ScaleCounts(int a,int b){float sum=(float)a;sum+=(float)b;return sum*100.0f;}
class Rva005C1BDEView {public:void call(Rva005DDE01*);};
void Rva005C1BDEView::call(Rva005DDE01*table){
float total=0;UserPreferences*prefs=(UserPreferences*)((char*)this+8);
for(int side=0;side<6;++side){AsciiString faction(kFactions[side]);int wins=prefs->rva00535BF6(faction);int losses=prefs->rva00535CE4(faction);for(int row=0;row<37;++row){switch(row){
case 0:{table->rva005DDE01(0,side,Rva005DD822(prefs->rva00535D75(faction)),true);break;}
case 1:{table->rva005DDE01(1,side,Rva005DD822(prefs->rva00535E06(faction)),true);break;}
case 2:{table->rva005DDE01(2,side,Rva005DD822(prefs->rva00535E97(faction)),true);break;}
case 3:{table->rva005DDE01(3,side,Rva005DD822(prefs->rva00535F28(faction)),true);break;}
case 4:{table->rva005DDE01(4,side,Rva005DD822(wins),true);break;}
case 5:{table->rva005DDE01(5,side,Rva005DD822(losses),true);break;}
case 6:{table->rva005DDE01(6,side,Rva005DD8E0((float)wins,(float)losses),true);break;}
case 7:{table->rva005DDE01(7,side,Rva005DD822(wins+losses),true);break;}
case 8:{table->rva005DDE01(8,side,Rva005DDED5((unsigned int)prefs->rva00535AE1(faction)),true);break;}
case 9:{table->rva005DDE01(9,side,Rva005DDED5((unsigned int)prefs->rva005359A9(faction)),true);break;}
case 10:{table->rva005DDE01(10,side,Rva005DDED5((unsigned int)prefs->rva00535A45(faction)),true);break;}
case 11:{table->rva005DDE01(11,side,Rva005DDED5((unsigned int)prefs->rva0053590D(faction)),true);break;}
case 12:{UnicodeString label=Rva005C1B2D(prefs->rva0053755A(faction));table->rva005DDE01(12,side,Rva005DD772(label,0),true);break;}
case 13:{UnicodeString label=Rva005C1B2D(prefs->rva00537616(faction));table->rva005DDE01(13,side,Rva005DD772(label,0),true);break;}
case 14:{table->rva005DDE01(14,side,Rva005DD822(prefs->rva005362B2(faction)),true);break;}
case 15:{table->rva005DDE01(15,side,Rva005DD822(prefs->rva00536343(faction)),true);break;}
case 16:{table->rva005DDE01(16,side,Rva005DD822(prefs->rva005363D4(faction)),true);break;}
case 17:{table->rva005DDE01(17,side,Rva005DD822(prefs->rva00536465(faction)),true);break;}
case 18:{table->rva005DDE01(18,side,Rva005DD822(prefs->rva005364F6(faction)),true);break;}
case 19:{float numerator=(float)prefs->rva00536587(faction);float denominator=(float)prefs->rva005364F6(faction);table->rva005DDE01(19,side,Rva005DD8E0(numerator,denominator),true);break;}
case 20:{table->rva005DDE01(20,side,Rva005DD822(prefs->rva00536587(faction)),true);break;}
case 21:{table->rva005DDE01(21,side,Rva005DD822(prefs->rva00536618(faction)),true);break;}
case 22:{float denominator=(float)prefs->rva005366A9(faction);if(denominator<0)denominator=(float)prefs->rva00536618(faction);total+=denominator;int countA=prefs->rva00536587(faction);int countB=prefs->rva005363D4(faction);table->rva005DDE01(22,side,Rva005DD8E0(ScaleCounts(countA,countB),denominator),true);break;}
case 23:{float denominator=(float)prefs->rva005364F6(faction);float numerator=(float)prefs->rva00536465(faction);table->rva005DDE01(23,side,Rva005DD8E0(numerator,denominator),true);break;}
case 24:{table->rva005DDE01(24,side,Rva005DD822(prefs->rva0053673A(faction)),true);break;}
case 25:{table->rva005DDE01(25,side,Rva005DD822(prefs->rva005367CB(faction)),true);break;}
}}}
((GameStats::Persistent*)table)->CalculateTotalColumn(total);
table->rva005DDE01(12,6,Rva005DD772(Rva005C1B2D(prefs->rva005376D2()),0),true);
table->rva005DDE01(13,6,Rva005DD772(Rva005C1B2D(prefs->rva005377B6()),0),true);
table->rva005DDE01(1,6,Rva005DD822(prefs->rva005360DC()),true);
table->rva005DDE01(0,6,Rva005DD822(prefs->rva00535FBA()),true);
table->rva005DDE01(2,6,Rva005DD822(prefs->rva0053604B()),true);
table->rva005DDE01(3,6,Rva005DD822(prefs->rva0053616D()),true);
}
