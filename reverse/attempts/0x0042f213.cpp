// ?rva0042F213@BfmeOwnVVD@@QAEXXZ
// partial score=0.99 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
#include "../Code/Libraries/Include/Lib/Coord3D.h"
// SCRATCH-ONLY: test the nontrivial copy/dtor ABI witnessed in retail frame calls.
// The canonical Coord2D contract must be reconciled before this can be admitted.
class Coord2D {public:float x,y;
 __forceinline Coord2D() {}
 __forceinline Coord2D(float a,float b):x(a),y(b) {}
 __forceinline Coord2D(const Coord2D &c):x(c.x),y(c.y) {}
 __forceinline ~Coord2D() {}
 void normalize();float length() const;
};
struct ICoord2D {int x,y;};
// SCRATCH: canonical GameLogic view plus proposed predicate declaration.


// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class Drawable;
class Rva00439E0C;
class AsciiString;
class CommandButton;
class WindowLayout;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

// The network code reads the command timestamp at +0x38 and Zero Hour's
// frame counter at +0x40 (ConnectionManager::update 0x004D342A, among others).
// StealthUpdate::disguiseAsObject (0x00373DF0) reads the manager at +0x178
// whose call 0x00439E0C takes the disguised object. The spell store's show
// (finishShowPurchaseScience 0x0043CB48) reads the end flag at +0x6D and
// the game mode at +0x110.
// InGameUI::addFloatingText (0x002A0D19) gates on the byte at +0x9A, Zero
// Hour's getDrawIconUI.
// The object list head is at +0xAC: getFirstObject (0x0023CAD2) returns it and
// prepareLogicForObjectLoad (0x00242C86) walks it inline.
// ScoreKeeper::addObjectLost (0x0039CF73) tests the scoring byte at +0x98
// first, as Zero Hour's isScoringEnabled does.
// GameClient::update (0x0023BEE8) reads the byte at +0x125, next to the pause
// byte isGamePaused (0x0023CD97) returns from +0x124, and skips the drawable,
// terrain and display updates while it is set.
class GameLogic
{
	char pad[0x38];
	unsigned int m_timestamp;
	char pad3C[0x40 - 0x3C];
	unsigned int m_frame;
	char pad44[0x6D - 0x44];

public:
	bool m_6d; // +0x6D

private:
	char pad6E[0x98 - 0x6E];
	bool m_isScoringEnabled; // +0x98
	char pad99[0x9A - 0x99];
	bool m_drawIconUI; // +0x9A
	char pad9B[0xAC - 0x9B];
	Object *m_firstObject; // +0xAC, the head getFirstObject returns
	char padB0[0xB4 - 0xB0];
	ObjectIdMap m_map;
	char padB5[0x110 - 0xB5];

public:
	int m_110; // +0x110

	// Native AIUnitBuilder598052 and listener239457 compare this word.
	int m_114; // +0x114; precise mode meaning remains unresolved

private:
	char pad118[0x125 - 0x118];
	bool m_flag125;
	char pad126[0x178 - 0x126];
	Rva00439E0C *m_manager178;
	char pad17C[0x1B8 - 0x17C];
	// Window cleanup 0x00376D49 owns this layout and clears the pending byte.
	// BFME1's closeWindows supplies its purpose; offsets are native BFME2.
	WindowLayout *m_background; // +0x1B8
	bool m_backgroundPending; // +0x1BC

public:
	int rva0023C666(); // proposed owner correction; existing body returns EAX 0/1
	bool isInMultiplayerGame();	// 0x00042235
	bool rva0042219();	// 0x00042219, mode gate rejecting 9, 4 and 7
	bool rva001DCD1C();	// 0x001DCD1C, mode 8 or mode 9 with +0x114 != 3
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);	// 0x0023CD9E
	Object *findObjectByID(ObjectID id);
	void rva0023D033(); // 0x0023D033, native +0x184 cleanup forwarder
	int rva0023D08B(int value);	// 0x0023D08B, existing +0x184 forwarder
	void rva0023D0C2(Object *obj, int handle);	// 0x0023D0C2
	Object *getFirstObject();	// 0x0023CAD2
	void destroyObject(Object *obj);	// 0x00242C09
	void deselectObject(Object *obj, unsigned int playerMask, bool affectClient);	// 0x0023C9F8
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void rva00376E92(bool first, bool second);	// 0x00376E92
	void rva00376D49();	// 0x00376D49, window cleanup, donor closeWindows
	void rva00248558(bool fromSave);	// 0x00248558, verified new-game/load pass
	unsigned char isGamePaused();	// 0x0023CD97
	void deleteLoadScreen();	// 0x002423E3
	void processDestroyList();	// 0x002413DF
	void prepareLogicForObjectLoad();	// 0x00242C86
	void setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton);	// 0x0024792F
	bool isScoringEnabled() const { return m_isScoringEnabled; }
	bool getFlag125() const { return m_flag125; }
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	bool getDrawIconUI() const { return m_drawIconUI; }
	Rva00439E0C *getManager178() const { return m_manager178; }
};

struct LookAtRegion {Coord2D lo,hi;};
struct Rva001EDD80Pair { int x, y; };
class GameMessage;

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
 void rva0042F213();

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
 virtual bool i42();
 virtual void i43();
 virtual bool i44();
virtual void i45(Coord2D);
virtual void i46();
virtual void i47();
virtual void i48();
virtual void i49();
virtual void i50();
virtual bool i51();
virtual void i52();
virtual void i53();
virtual void i54();
virtual void i55();
virtual void i56();
virtual void i57();
virtual void i58();
virtual void i59();
virtual void i60();
virtual void i61();
virtual void i62();
virtual void i63();
virtual void i64();
virtual void i65();
virtual void i66();
virtual void i67();
virtual void i68();
virtual void i69();
virtual void i70();
virtual void i71();
virtual void i72();
virtual void i73();
virtual void i74();
virtual void i75();
virtual void i76();
virtual void i77();
virtual void i78();
virtual void i79();
virtual void i80();
virtual void i81();
virtual void i82();
virtual void i83();
virtual void i84();
virtual void i85();
virtual void i86();
virtual void i87();
virtual void i88();
virtual void i89();
virtual void i90();
virtual void i91();
virtual void i92();
virtual void i93();
virtual void i94();
virtual bool i95();
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
	virtual unsigned int t23(const Coord2D *);
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
 void *rva001EDFE9() const;
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
 void appendLocationArgument(const Coord3D &);
 void appendRealArgument(float);
 void appendIntegerArgument(int);
 void appendPixelArgument(const ICoord2D &);
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
class GlobalData {public:
 char pad00[0x2c]; bool m_windowed;
 char pad2d[0xa9c-0x2d];float horizontal,vertical,edgeFactor;int edgeTime;
 char padAAC[0xaf8-0xaac];float keyboardFactor;
 char padAFC[0xb70-0xafc];bool saveReplay;
 char padB71[0xc2c-0xb71];float rotateSpeed;
};
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

class Keyboard {public:bool rva00232643(unsigned char);};
extern Keyboard *TheKeyboard;
class GameEngine {friend class BfmeOwnVVD;bool rva00225D38();};
extern GameEngine *TheGameEngine;
class MessageStream {public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual GameMessage *appendMessage(int);
};
extern MessageStream *TheMessageStream;
class Rva002D3627Host {public:
virtual void r0();
virtual void r1();
virtual void r2();
virtual void r3();
virtual void r4();
virtual void r5();
virtual void r6();
virtual void r7();
virtual void r8();
virtual void r9();
virtual void r10();
virtual void r11(const Coord2D *,float);
 char pad04[0x18-4];bool enabled;
};
extern Rva002D3627Host *g_00DFEF18;
extern "C" double __cdecl fabs(double);
struct ViewLocation {
 bool valid;Coord3D position;float angle,pitch,zoom,real1C;
 __forceinline ViewLocation() {
  valid=false;position.x=0;position.y=0;position.z=0;
  angle=pitch=zoom=real1C=0;
 }
};
// WB 0x012C4A70/3015 and native 0x0042F213/1958. Native GameClient::update
// calls this through g_bfmeSingletonVVD. Reference frame-tick algorithm is
// LookAtXlat.cpp at BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705.
// BFME2 adds living-world scroll dispatch, border-anchor repair, camera keys,
// and one additional replay-camera real field at ViewLocation+0x1C.
void BfmeOwnVVD::rva0042F213()
{
 Coord2D offset(0,0);
 if(m_38 && (!TheInGameUI->i42() || TheInGameUI->i95())) {
  TheInGameUI->i45(offset);rva0042E804();
 } else if(m_38) {
  switch(m_148) {
  case 1: {
   if(TheInGameUI->i51()) {TheInGameUI->i45(offset);rva0042E804();break;}
   Rva001EDD80Pair p=*(const Rva001EDD80Pair *)TheMouse->rva001EDFE9();
   int dx=m_14-p.x,dy=m_18-p.y;
   // The target has an asymmetric fourth clamp: its comparison uses dy.
   if(*(const bool *)((const char *)TheInGameUI+0x8c4)) {
    int maxX=TheDisplay->d16()/2,maxY=TheDisplay->d17()/2;
    if(m_14+maxX<m_04)m_04=m_14+maxX;else if(m_14-maxX>m_04)m_04=m_14-maxX;
    if(m_18+maxY<m_08)m_08=m_18+maxY;else if(dy-maxY>m_08)m_08=m_18-maxY;
   }
   offset.x=TheGlobalData->horizontal*(m_14-m_04);
   offset.y=TheGlobalData->vertical*(m_18-m_08);
   {Coord2D vec;vec.x=offset.x;vec.y=offset.y;vec.normalize();
   offset.x+=TheGlobalData->horizontal*TheGlobalData->keyboardFactor*TheGlobalData->keyboardFactor*vec.x;
   offset.y+=TheGlobalData->vertical*TheGlobalData->keyboardFactor*TheGlobalData->keyboardFactor*vec.y;}
   break;
  }
  case 2:
   if(scrollDir[0])offset.y-=TheGlobalData->vertical*100*TheGlobalData->keyboardFactor;
   if(scrollDir[1])offset.y+=TheGlobalData->vertical*100*TheGlobalData->keyboardFactor;
   if(scrollDir[2])offset.x-=TheGlobalData->horizontal*100*TheGlobalData->keyboardFactor;
   if(scrollDir[3])offset.x+=TheGlobalData->horizontal*100*TheGlobalData->keyboardFactor;
   break;
  case 3: {
   int duration=timeGetTime()-m_pad14c;
   int percent=duration>TheGlobalData->edgeTime?100:(100*duration)/TheGlobalData->edgeTime;
   unsigned height=TheDisplay->d17(),width=TheDisplay->d16();
   if(m_18<3)offset.y-=percent*(TheGlobalData->keyboardFactor*TheGlobalData->edgeFactor*TheGlobalData->vertical);
   if((unsigned)m_18>=height-3)offset.y+=percent*(TheGlobalData->keyboardFactor*TheGlobalData->edgeFactor*TheGlobalData->vertical);
   if(m_14<3)offset.x-=percent*(TheGlobalData->keyboardFactor*TheGlobalData->edgeFactor*TheGlobalData->horizontal);
   if((unsigned)m_14>=width-3)offset.x+=percent*(TheGlobalData->keyboardFactor*TheGlobalData->edgeFactor*TheGlobalData->horizontal);
   break;
  }
  }
  if(g_00DFEF18 && g_00DFEF18->enabled)g_00DFEF18->r11(&offset,0);
  else {
   TheInGameUI->i45(offset);
   unsigned flags=TheTacticalView->t23(&offset);
   if(flags && m_148==1) {
    float angle=(float)fabs(TheTacticalView->t64());
    bool sideways=false;
    if(angle>.7853982f && angle<2.3561945f)sideways=true;
    if(flags&3) {if(sideways)m_08=m_18;else m_04=m_14;}
    if(flags&12) {if(sideways)m_04=m_14;else m_08=m_18;}
   }
  }
 } else TheInGameUI->i45(offset);
 if(TheInGameUI->getInputEnabled()) {
  if(m_154)TheTacticalView->t63(TheTacticalView->t64()-TheGlobalData->rotateSpeed);
  if(m_155)TheTacticalView->t63(TheTacticalView->t64()+TheGlobalData->rotateSpeed);
  if(m_156)TheTacticalView->t77();
  if(m_157)TheTacticalView->t78();
 }
 if(TheGlobalData->saveReplay && TheGameEngine->rva00225D38() &&
   ((unsigned char)TheGameLogic->rva0023C666() || TheGameLogic->m_110==2 || TheGameLogic->isInMultiplayerGame())) {
  ViewLocation view;TheTacticalView->t92(&view);
  GameMessage *msg=TheMessageStream->appendMessage(1095);
  msg->appendLocationArgument(view.position);
  msg->appendRealArgument(view.angle);msg->appendRealArgument(view.pitch);
  msg->appendRealArgument(view.zoom);msg->appendRealArgument(view.real1C);
  msg->appendIntegerArgument((int)TheMouse->m_4fa4);
  msg->appendPixelArgument(*(const ICoord2D *)&m_14);
 }
 if(m_38) {
  if(!TheKeyboard->rva00232643(200))scrollDir[0]=false;
  if(!TheKeyboard->rva00232643(208))scrollDir[1]=false;
  if(!TheKeyboard->rva00232643(203))scrollDir[2]=false;
  if(!TheKeyboard->rva00232643(205))scrollDir[3]=false;
  if(!scrollDir[0] && !scrollDir[1] && !scrollDir[2] && !scrollDir[3] && m_148==2)rva0042E804();
 }
 if(m_154 && !TheKeyboard->rva00232643(75))m_154=false;
 if(m_155 && !TheKeyboard->rva00232643(77))m_155=false;
 if(m_156 && !TheKeyboard->rva00232643(72))m_156=false;
 if(m_157 && !TheKeyboard->rva00232643(80))m_157=false;
}
