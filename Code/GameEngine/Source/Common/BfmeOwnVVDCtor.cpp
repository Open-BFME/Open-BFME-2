// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "GameLogicObjectLookupView.h"
struct LookAtRegion {Coord2D lo,hi;};
struct Rva001EDD80Pair { int x, y; };
class GameMessage;

// Historical BFME1 donor notes follow; their addresses are not BFME2 addresses.
// The BFME2 owner remains BfmeOwnVVD until its complete class/vtable is reconciled.
// Retail layout: 0x005B5470 installs vftable 0x0110DE48, already pinned as
// ??_7BfmeOwnVVD@@6B@ by the landed destructor
// Code/GameEngine/Source/Common/BfmeConv1663.cpp (??1BfmeOwnVVD@@QAE@XZ,
// 0x005B5330), and stores `this` into the singleton at 0x012F4C84, already
// pinned in reverse/symbols.csv both as TheLookAtTranslator and as
// g_bfmeSingletonVVD -- but that name pin is stale for this address: the
// real ??0LookAtTranslator@@QAE@XZ is already matched elsewhere at
// 0x005A6580 (Code/GameEngine/Source/GameClient/MessageStream/
// LookAtTranslator_ctor.cpp, vtable 0x0110D62C), a different class entirely.
// This constructor is therefore address-derived, not LookAtTranslator; the
// BfmeOwnVVD name (shared with the already-landed dtor) is kept for
// consistency with that file. The array-new-with-ctor helper call (element
// size 0x20, count 8) uses the same BfmeElemVVD ctor/dtor pair as that file:
// the dtor is the existing pin ??1BfmeElemVVD@@QAE@XZ,0x0001479A; the ctor
// is newly pinned here as ??0BfmeElemVVD@@QAE@XZ,0x00418A07 (additive; the
// same address already carries an unrelated ??0BfmeS1059@@QAE@XZ pin
// through Code/gen_small/thunks_011.cpp -> FUN_00796AD0).
//
// Retail interleaves two groups of zero-stores around the array
// construction: some fields are zeroed via the (compiler-ordered)
// member-construction phase before the array, and the rest are zeroed by
// ordinary body statements that always run after all member construction
// (including the array) -- exactly the split used here (init-list members
// vs. body-assigned members).

class BfmeElemVVD
{
public:
	BfmeElemVVD();
	~BfmeElemVVD();
	char m_bfmePad00[0x20];
};

class BfmeBaseVVD
{
public:
	BfmeBaseVVD() { }
	~BfmeBaseVVD() { }
	virtual void bfmeSlot0VVD();
};

// ?bfmeSlot0VVD@BfmeBaseVVD@@UAEXXZ present-unmatched
void BfmeBaseVVD::bfmeSlot0VVD() { }

class BfmeOwnVVD : public BfmeBaseVVD
{
public:
	BfmeOwnVVD();
	~BfmeOwnVVD();
 unsigned char Rva0042E8C1();
 void rva0042E804();
 void rva0042E75F(unsigned int);
 int rva0042E9EC(const GameMessage *);

private:
	int m_04;                    // +0x04 body-set
	int m_08;                    // +0x08 body-set
	int m_0c;                    // +0x0c body-set
	int m_10;                    // +0x10 body-set
	int m_14;                    // +0x14 body-set
	int m_18;                    // +0x18 body-set
	unsigned char m_1c;                   // +0x1c init-list
	unsigned char m_pad1d[3];
	int m_20;                    // +0x20 body-set
	int m_24;                    // +0x24 body-set
	int m_28;                    // +0x28 body-set
	int m_2c;                    // +0x2c body-set
	int m_30;                    // +0x30 body-set
	int m_34;                    // +0x34 body-set
	unsigned char m_38;                   // +0x38 init-list
	unsigned char m_39;                   // +0x39 init-list
	unsigned char m_3a;                   // +0x3a init-list
	unsigned char m_3b;                   // +0x3b init-list
	unsigned char m_3c;                   // +0x3c init-list
	unsigned char m_pad3d[3];
	unsigned int m_40;                    // +0x40 init-list
	unsigned int m_44;                    // +0x44 init-list
	BfmeElemVVD m_bfme48[8];              // +0x48 .. +0x148
	unsigned int m_148;                   // +0x148 body-set
	unsigned int m_pad14c;
	unsigned int m_150;                   // +0x150 body-set
	unsigned char m_154;                  // +0x154 body-set
	unsigned char m_155;                  // +0x155 body-set
	unsigned char m_156;                  // +0x156 body-set
	unsigned char m_157;                  // +0x157 body-set
};

extern BfmeOwnVVD *g_bfmeSingletonVVD;
// g_bfmeSingletonVVD: matched references place it at VA 0xe03214 (zero-filled .bss).
BfmeOwnVVD * g_bfmeSingletonVVD;

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

// ??0BfmeOwnVVD@@QAE@XZ
BfmeOwnVVD::BfmeOwnVVD()
	: m_1c(0), m_38(0), m_39(0), m_3a(0), m_3b(0), m_3c(0), m_40(0), m_44(0)
{
	m_148 = 0;
	m_150 = 0;
	m_154 = 0;
	m_155 = 0;
	m_156 = 0;
	m_157 = 0;
	m_08 = 0;
	m_04 = 0;
	m_18 = 0;
	m_14 = 0;
	m_10 = 0;
	m_0c = 0;
	m_24 = 0;
	m_20 = 0;
	m_34 = 0;
	m_30 = 0;
	m_2c = 0;
	m_28 = 0;

	g_bfmeSingletonVVD = this;
}

// ??1BfmeOwnVVD@@QAE@XZ 0x0042E85C 79B: BFME1 donor BfmeConv1663.cpp; vtable 0x0083C938 base 0x007DBA74; caller 0x0042E9D3; singleton 0x00A03214
BfmeOwnVVD::~BfmeOwnVVD()
{
	if (g_bfmeSingletonVVD == this)
		g_bfmeSingletonVVD = 0;
}

// ?Rva0042E8C1@BfmeOwnVVD@@QAEEXZ 0x0042E8C1 44B: uses m_150 plus globals 0x009FE78C 0x009BA4E4; callers 0x0029F2CF 0x0037A90C
unsigned char BfmeOwnVVD::Rva0042E8C1()
{
	unsigned int &slot = m_150;
	if (slot > TheGameLogic->getFrame())
		slot = 0;
	return slot + g_Va00DBA4E4 >= TheGameLogic->getFrame();
}

// ?rva0042E804@BfmeOwnVVD@@QAEXXZ @0x0042E804 88B evidence: same BfmeOwnVVD layout m_1c m_38 m_39 m_148 callers 0x0042EA56 0x0042ED42 TheInGameUI slot 0xa4 TheTacticalView slot 0x1a4 TheMouse slot 0x4c StatsCollector endScrollTime row
class InGameUI
{
public:
	virtual void i0();
	virtual void i1();
	virtual void i2();
	virtual void i3();
	virtual void i4();
	virtual void i5();
	virtual void i6();
	virtual void i7();
	virtual void i8();
	virtual void i9();
	virtual void i10();
	virtual void i11();
	virtual void i12();
	virtual void i13();
	virtual void i14();
	virtual void i15();
	virtual void __cdecl i16(UnicodeString, ...);
	virtual void i17();
	virtual void i18();
	virtual void i19();
	virtual void i20();
	virtual void i21();
	virtual void i22();
	virtual void i23();
	virtual void i24();
	virtual void i25();
	virtual void i26();
	virtual void i27();
	virtual void i28();
	virtual void i29();
	virtual void i30();
	virtual void i31();
	virtual void i32();
	virtual void i33();
	virtual void i34();
	virtual void i35();
	virtual void i36();
	virtual void i37();
	virtual void i38();
	virtual void i39();
 virtual void i40();
 virtual void i41(int);
 bool getInputEnabled() const {return m_15 && m_16;}
 virtual void i42();
 virtual void i43();
 virtual bool i44();
 char m_pad04[0x11];
 unsigned char m_15;
 unsigned char m_16;
};
extern InGameUI *TheInGameUI;

class TacticalView
{
public:
	virtual void t0();
	virtual void t1();
	virtual void t2();
	virtual void t3();
	virtual void t4();
	virtual void t5();
	virtual void t6();
	virtual void t7();
	virtual void t8();
	virtual void t9();
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14();
	virtual void t15();
	virtual void t16();
	virtual void t17();
	virtual void t18();
	virtual void t19();
	virtual void t20();
	virtual void t21();
	virtual void t22();
	virtual void t23();
	virtual void t24();
	virtual void t25();
	virtual void t26();
	virtual void t27();
	virtual void t28();
	virtual void t29(int);
	virtual void t30();
	virtual void t31();
	virtual void t32();
	virtual void t33();
	virtual void t34();
	virtual void t35();
	virtual void t36();
	virtual void t37();
	virtual void t38();
	virtual void t39();
	virtual void t40();
	virtual void t41();
	virtual void t42();
	virtual void t43();
	virtual void t44();
	virtual void t45();
	virtual void t46();
	virtual void t47();
	virtual void t48();
	virtual void t49();
	virtual void t50(int,int,float,float);
	virtual void t51();
	virtual void t52();
	virtual void t53();
	virtual void t54();
	virtual void t55();
	virtual void t56();
	virtual void t57();
	virtual void t58();
	virtual void t59();
	virtual void t60();
	virtual void t61();
	virtual void t62();
	virtual void t63(float);
	virtual float t64();
	virtual void t65(float);
	virtual float t66();
	virtual void t67();
	virtual void t68();
	virtual void t69();
	virtual void t70();
	virtual void t71();
	virtual void t72();
	virtual void t73();
	virtual void t74();
	virtual void t75();
	virtual void t76();
	virtual void t77();
	virtual void t78();
	virtual void t79();
	virtual void t80();
	virtual void t81();
	virtual void t82();
	virtual void t83();
	virtual void t84();
	virtual void t85();
	virtual void t86();
	virtual void t87();
	virtual void t88();
	virtual void t89();
	virtual void t90();
	virtual void t91();
	virtual void t92(void *);
	virtual void t93(const void *);
	virtual void t94();
	virtual void t95();
	virtual void t96();
	virtual void t97();
	virtual void t98();
	virtual void t99();
	virtual void t100();
	virtual void t101();
	virtual void t102();
	virtual void t103();
 virtual void t104();
 virtual void t105(int);
 virtual void t106();
 virtual void t107();
 virtual void t108();
 virtual void t109();
 virtual void t110();
 virtual void t111();
 virtual void t112();
 virtual void t113();
 virtual void t114();
 virtual bool t115();
 virtual void t116();
 virtual void t117();
 virtual void t118();
 virtual void t119();
 virtual void t120();
 virtual void t121();
 virtual void t122();
 virtual void t123();
 virtual void t124(float);
 virtual void t125();
 virtual float t126();
};
extern TacticalView *TheTacticalView;

class Mouse
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6();
	virtual void m7();
	virtual void m8();
	virtual void m9();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
 virtual void m18();
 virtual void m19(void *p);
 bool rva001EDD80(const Rva001EDD80Pair *, const Rva001EDD80Pair *);
 void rva001EDFF7(float *) const;
 char m_pad04[0x4f0c - 4];
 struct MouseStatus { int x, y; char pad08[0x10]; int event; } m_status;
 char m_pad4f28[0x4fa4 - 0x4f28];
 void *m_4fa4;
};
extern Mouse *TheMouse;

class ClientFrameSubsystem
{
public:
 char m_pad[0xc0];
 unsigned char m_c0;
};
class GameClient { public:
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();
virtual void c26();
virtual void c27();
virtual void c28();
virtual void c29();
virtual void c30();
virtual unsigned int c31();
};
extern GameClient *TheGameClient;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class StatsCollector
{
public:
 void endScrollTime();
 void startScrollTime();
};
extern StatsCollector *g_00E032F8;
extern void *g_00DC8874;
StatsCollector *g_00E032F8;
void *g_00DC8874;

void BfmeOwnVVD::rva0042E804()
{
 m_38 = 0;
 m_1c = 0;
 TheInGameUI->i41(0);
 if (m_39 == 0)
  TheTacticalView->t105(0);
 TheMouse->m19(g_00DC8874);
 m_148 = 0;
 if (g_00E032F8 == 0)
  return;
 return g_00E032F8->endScrollTime();
}

// ?rva0042E75F@BfmeOwnVVD@@QAEXI@Z @0x0042E75F 165B evidence: same BfmeOwnVVD layout m_38 m_39 m_148 callers 0x0042EBEC 0x0042ED6E 0x0042F187 TheInGameUI +0x15 +0x16 slot 0xa4 TheTacticalView slot 0x1cc 0x1a4 TheGameClient +0xc0 TheMouse +0x4fa4 StatsCollector startScrollTime row timeGetTime IAT
void BfmeOwnVVD::rva0042E75F(unsigned int arg)
{
 if (TheInGameUI->m_15 == 0)
  return;
 if (TheInGameUI->m_16 == 0)
  return;
 if (TheTacticalView->t115())
  return;
 if (((ClientFrameSubsystem *)TheGameClient)->m_c0 != 0)
  return;
 void *tmp = TheMouse->m_4fa4;
 m_38 = 1;
 g_00DC8874 = tmp;
 TheInGameUI->i41(1);
 if (m_39 == 0)
  TheTacticalView->t105(1);
 if (arg != m_148)
 {
  m_148 = arg;
  m_pad14c = timeGetTime();
 }
 if (g_00E032F8 == 0)
  return;
 g_00E032F8->startScrollTime();
}


// Reference: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameClient/MessageStream/LookAtXlat.cpp.
// WB 0x012C30D0 names translateGameMessage; retail 0x0042E9EC/2087
// uses this class's already recovered scrolling helpers and fields.
// Target-specific mouse locking, drag detection, alternate camera controls,
// bookmark fetchPtr and key flags are established by the native body.
union GameMessageArgumentType {
 int integer; float real; int boolean, objectID, drawableID;
 unsigned int teamID;
 struct Loc {float x,y,z;} location;
 Rva001EDD80Pair pixel;
 struct PixReg {int loX,loY,hiX,hiY;} pixelRegion;
 unsigned int timestamp; unsigned short wChar;
};
class GameMessage { public:
 const GameMessageArgumentType *getArgument(int) const;
 char pad00[0x10]; int m_type;
};
class Display {public:
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual unsigned int d16();
virtual unsigned int d17();
};
extern Display *TheDisplay;
class GlobalData {public: char pad00[0x2c]; bool m_windowed;};
extern GlobalData *TheGlobalData;
class Shell {public: char pad00[0x5c]; bool m_active;};
extern Shell *TheShell;
class GameTextInterface {public:
virtual void g0();
virtual void g1();
virtual void g2();
virtual void g3();
virtual void g4();
virtual void g5();
virtual void g6();
virtual void g7();
virtual void g8();
virtual void g9();
virtual void g10();
virtual void g11();
virtual void g12();
virtual void g13();
virtual void g14();
virtual void g15();
virtual void g16();
virtual UnicodeString *fetchPtr(const char *, bool *);
};
extern GameTextInterface *TheGameText;
static bool scrollDir[4];

int BfmeOwnVVD::rva0042E9EC(const GameMessage *msg)
{
 int disp=0;
 int t=msg->m_type;
 switch(t) {
 case 21: case 22: {
  unsigned char key=msg->getArgument(0)->integer;
  unsigned char state=msg->getArgument(1)->integer;
  bool pressed=!(state&1);
  if(TheShell && TheShell->m_active) break;
  switch(key) {
  case 72:m_156=pressed;break; case 75:m_154=pressed;break;
  case 77:m_155=pressed;break; case 80:m_157=pressed;break;
  case 200:scrollDir[0]=pressed;break; case 208:scrollDir[1]=pressed;break;
  case 203:scrollDir[2]=pressed;break; case 205:scrollDir[3]=pressed;break;
  }
  if(TheInGameUI->i44() || (m_38 && m_148!=2)) break;
  int n=0;for(int i=0;i<4;++i) if(scrollDir[i]) ++n;
  if(n && !m_38) rva0042E75F(2);
  else if(!n && m_38) rva0042E804();
  break;
 }
 case 14: {
  m_150=TheGameLogic->getFrame();
  const Rva001EDD80Pair &p=msg->getArgument(0)->pixel;
  m_14=p.x; m_18=p.y; m_04=m_14; m_08=m_18;
  if(!TheInGameUI->i44() && !m_38) m_1c=1;
  break;
 }
 case 16:
  m_150=TheGameLogic->getFrame(); m_1c=0;
  if(m_148==1) rva0042E804();
  break;
 case 10: {
  m_150=TheGameLogic->getFrame(); m_39=1;
  const Rva001EDD80Pair &a=msg->getArgument(0)->pixel; m_20=a.x; m_24=a.y;
  const Rva001EDD80Pair &b=msg->getArgument(0)->pixel; m_28=b.x; m_2c=b.y;
  const Rva001EDD80Pair &c=msg->getArgument(0)->pixel; m_30=c.x; m_34=c.y;
  m_40=TheGameClient->c31();
  if(!m_38) TheTacticalView->t105(1);
  break;
 }
 case 12: {
  if(m_39 && !m_38) TheTacticalView->t105(0);
  m_150=TheGameLogic->getFrame(); m_39=0;
  int dx=m_30-m_28; if(dx<0) dx=-dx;
  int dy=m_34-m_2c;
  bool moved=(unsigned int)dx>5 || (unsigned int)dy>5;
  if(!moved && TheGameClient->c31()-m_40<5) TheTacticalView->t50(0,0,0,0);
  break;
 }
 case 3: {
  if(m_1c && !m_38) {
   Rva001EDD80Pair p=msg->getArgument(0)->pixel;
   if(TheMouse->rva001EDD80((const Rva001EDD80Pair *)&m_04,&p)) rva0042E75F(1);
  }
  if(!TheTacticalView->t115()) {
   if(m_14!=msg->getArgument(0)->pixel.x || m_18!=msg->getArgument(0)->pixel.y)
    m_150=TheGameLogic->getFrame();
   if(m_39) {
    m_3a=1; const Rva001EDD80Pair &p=msg->getArgument(0)->pixel; m_30=p.x;m_34=p.y;
   } else if(m_3a && m_148==1) {
    int dx=m_04-m_14,dy=m_08-m_18;
    const Rva001EDD80Pair &p=msg->getArgument(0)->pixel; m_14=p.x;m_18=p.y;
    m_04=m_14+dx;m_08=m_18+dy;m_3a=0;
   } else {const Rva001EDD80Pair &p=msg->getArgument(0)->pixel;m_14=p.x;m_18=p.y;}
   unsigned int height=TheDisplay->d17(),width=TheDisplay->d16();
   if(TheInGameUI->getInputEnabled()==false) {if(m_38) rva0042E804();break;}
   bool selecting=TheInGameUI->i44();
   if(selecting) {
    Mouse::MouseStatus *s=&TheMouse->m_status;
    if(s && s->event!=1) selecting=false;
   }
   if(!TheGlobalData->m_windowed && !selecting) {
    if(m_38) {
     if(m_148==3 && m_14>=3 && m_18>=3 && (unsigned)m_18<height-3 && (unsigned)m_14<width-3) rva0042E804();
    } else if(m_14<3 || m_18<3 || (unsigned)m_18>=height-3 || (unsigned)m_14>=width-3) rva0042E75F(3);
   }
   if(m_39) {
    float angle=.005f*(m_30-m_20);
    TheTacticalView->t63(TheTacticalView->t64()+angle);
    const Rva001EDD80Pair &p=msg->getArgument(0)->pixel;m_20=p.x;m_24=p.y;
   }
  } else {
   LookAtRegion r;TheMouse->rva001EDFF7((float *)&r);
   Coord2D mouse;mouse.x=(float)TheMouse->m_status.x;mouse.y=(float)TheMouse->m_status.y;
   r.lo.x+=15; r.hi.x-=15; r.lo.y+=15; r.hi.y-=15;
   bool rotated=false;
   if(mouse.x<=r.lo.x) {TheTacticalView->t63(TheTacticalView->t64()+.046f);rotated=true;}
   else if(mouse.x>=r.hi.x) {TheTacticalView->t63(TheTacticalView->t64()-.046f);rotated=true;}
   if(rotated) {
    float factor=.03f;
    float height=r.hi.y-r.lo.y;
    mouse.y-=height*.5f;
    factor=(mouse.y/height+mouse.y/height)*factor;
    TheTacticalView->t124(TheTacticalView->t126()+factor);
   } else if(mouse.y<=r.lo.y) TheTacticalView->t124(TheTacticalView->t126()-.02f);
   else if(mouse.y>=r.hi.y) TheTacticalView->t124(TheTacticalView->t126()+.02f);
   if(m_39) {
    float angle=.001f*(m_30-m_20);
    TheTacticalView->t63(TheTacticalView->t64()+angle);
    const Rva001EDD80Pair &p=msg->getArgument(0)->pixel; m_20=p.x; m_24=p.y;
   }
   if(m_3b) {
    float angle=.01f*(m_18-m_08);
    TheTacticalView->t65(TheTacticalView->t66()+angle);
    const Rva001EDD80Pair &p=msg->getArgument(0)->pixel; m_04=p.x; m_08=p.y;
   }

  }
  break;
 }
 case 19: {
  m_150=TheGameLogic->getFrame();
  int spin=msg->getArgument(1)->integer;
  if(spin>0) {for(;spin>0;--spin) TheTacticalView->t77();}
  else {for(;spin<0;++spin) TheTacticalView->t78();}
  break;
 }
 case 112:rva0042E804();break;
 case 36:case 37:case 38:case 39:case 40:case 41:case 42:case 43: {
  int slot=t-35;
  if(slot>0 && slot<=8) {
   TheTacticalView->t92(&m_bfme48[slot-1]);
   UnicodeString text;text.format(TheGameText->fetchPtr("GUI:BookmarkXSet",0),slot);
   TheInGameUI->i16(text);
  }
  disp=1;break;
 }
 case 44:case 45:case 46:case 47:case 48:case 49:case 50:case 51: {
  if(TheInGameUI->getInputEnabled()==false) break;
  int slot=t-43;
  if(slot>0 && slot<=8) TheTacticalView->t93(&m_bfme48[slot-1]);
  disp=1;break;
 }
 case 1106:{int mode=msg->getArgument(0)->integer;TheTacticalView->t29(mode);break;}
 }
 return disp;
}
