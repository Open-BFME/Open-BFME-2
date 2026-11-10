// cl: /O1 /Oi- /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I.
// stlport
#include <algorithm>
// ?rva0042CB81@Rva0042CBB6@@QAEXH@Z @0x0042CB81 53B via conditional counter decrement plus zero-guard clear
// Evidence: layout matches Rva0042CBB6Ctor (+8 +0x30 +0x34 +0x39); callers 5 incl 0x0042CE09 0x0042D0CD; unblocks 0x0042D068
#include "../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;

class Rva0042CBB6
{
public:
	void rva0042CB81(int x);
	void rva0042CC1B();
	void rva0042CAEB(int y);
	void rva0042CB57(int x);
	void rva002B230F(int impl);
	void rva0042CAFB();
	void rva0042D068();
	int rva0042CC7B(class GameMessage *message);
private:
	const void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	char m_3A[4];
	unsigned char m_3E;
	unsigned char m_3F;
	unsigned char m_40;
	unsigned char m_41;
	unsigned char m_42;
};

// The complete 10-byte body at 002B230F is folded with the rowed listener
// setters. Native 42C693 passes its new impl and the same +20 owner whose
// conditional clear42CAEB tests the +4 slot below; this establishes the
// receiver and storage relationship without claiming an original method name.
void Rva0042CBB6::rva002B230F(int impl)
{
	m_04 = impl;
}

void Rva0042CBB6::rva0042CAEB(int y)
{
	if (m_04 == y)
		m_04 = 0;
}

void Rva0042CBB6::rva0042CB81(int x)
{
	if (x == 0)
		m_08 = 0;
	else {
		int cur = m_08;
		if ((x & cur) != 0)
			m_08 = cur - x;
	}
	if (m_08 < 0)
		m_08 = 0;
	if (m_08 == 0) {
		m_39 = 0;
		m_30 = 0;
		m_34 = 0;
	}
}

// ?rva0042CB57@Rva0042CBB6@@QAEXH@Z @0x0042CB57 42B via TheMouse+0x4FA4 fill plus bit-gated add
// Evidence: same class layout as neighbours (+8 +0x0C +0x39); TheMouse at 0x009FDCA0 field +0x4FA4 per Rva0042C7B1; callers 0x0042CD88 0x0042CEC4
void Rva0042CBB6::rva0042CB57(int x)
{
	int cur = m_08;
	if (cur == 0)
		m_0C = TheMouse->m_currentCursor;
	if ((x & cur) == 0)
		m_08 = cur + x;
	m_39 = 1;
}

// Native Ghidra extent 0x0042CC1B..0x0042CC7B, 96 bytes, thiscall RET0.
// The consumed offsets and reset constants agree with the rowed constructor
// at 0x0042CBB6; original class and field meanings remain unknown.
// STLport 4.5.3's generic fill with a bool value retains the runtime pointer
// span for +0x3A..+0x3D. Its char overload folds that span into a constant
// memset and does not reproduce the retail comparison and REP stores.
void Rva0042CBB6::rva0042CC1B()
{
	m_08 = 0;
	m_0C = 2;
	m_14 = 0;
	m_10 = 0;
	m_1C = 0;
	m_18 = 0;
	m_24 = 0;
	m_20 = 0;
	m_2C = 0;
	m_28 = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 1;
	m_39 = 0;
	m_3E = 0;
	m_3F = 0;
	m_40 = 0;
	m_41 = 0;
	m_42 = 0;
	_STL::fill(m_3A, m_3A + 4, false);
}

// Reuse the data ledger owner at 0x009FEF18; original class identity is unknown.
class Rva002D3627Host; class LivingWorld; extern LivingWorld *TheLivingWorld;
extern int BfmeClientFramesPerSecond;
class Rva002BE8D4 { public: bool rva002BE8D4(); };
struct CameraPoint42 { float x,y,z; };
class CameraOperations42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
 virtual void s24(); virtual float s25(int);
 virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(CameraPoint42 *);
 virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
 virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
 virtual void s38(); virtual void s39(CameraPoint42 *,float,float);
};

// Complete native 82CAFB..82CB57, 92B; WB12C1010 saves ECX as this.
// Two calls from the receiver's 1005B handler at 42CC7B and its layout
// siblings establish the owner. Original method and virtual slot names
// remain unknown. Native slots 0x74, 0x64, 0x9C respectively fill a
// three-float point, return a float for FPS/4 and accept that point plus
// zero and the returned float. Camera roles are structural inferences.
// Keep the height query nested: its vtable stays in ESI across both calls.
void Rva0042CBB6::rva0042CAFB()
{
 if(!reinterpret_cast<Rva002BE8D4 *>(((Rva002D3627Host *)TheLivingWorld))->rva002BE8D4()) {
  CameraPoint42 point;
  reinterpret_cast<CameraOperations42 *>(((Rva002D3627Host *)TheLivingWorld))->s29(&point);
  reinterpret_cast<CameraOperations42 *>(((Rva002D3627Host *)TheLivingWorld))->s39(
   &point,0.0f,reinterpret_cast<CameraOperations42 *>(((Rva002D3627Host *)TheLivingWorld))->s25(BfmeClientFramesPerSecond / 4));
 }
}

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord2D.h"
#include <math.h>
extern GameLogic *TheGameLogic;
class GlobalData; extern GlobalData *TheWritableGlobalData;
class Display; extern Display *TheDisplay;
class InGameUI; extern InGameUI *TheInGameUI;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/Common/BfmeSelectionState.h"
struct CameraData42 {
 char gap[0xA9C]; float horizontal,vertical,edge;
 char gapAA8[0xAF8-0xAA8]; float keyboard;
 char gapAFC[0xC2C-0xAFC]; float rotate;
};
#define CAMERA_DATA42 (reinterpret_cast<CameraData42 *>(TheWritableGlobalData))
class CameraDisplay42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual unsigned width(); virtual unsigned height();
};
class CameraMotion42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10();
 virtual void s11(Coord2D *,float);
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual void s21(int);
};
// Complete native 82D068..82D468, 1024B, ending in RET at 82D467.
// The receiver agrees with the rowed 42CBB6 constructor and the same home's
// input flags, anchors and counter helpers. Original method name is unknown.
// Target establishes every access and virtual slot. Camera meanings and
// GlobalData field roles are inferences supported by the independently
// matched BfmeOwnVVDScrollUpdate.cpp sibling; see identity evidence.
void Rva0042CBB6::rva0042D068()
{
 unsigned char moved=m_42;
 m_42=0;
 if(!TheLivingWorldLogic || !reinterpret_cast<BfmeSelectionState *>(TheLivingWorldLogic)->isSelectionLocked() || TheGameLogic->isGamePaused()) return;
 Coord2D offset;
 offset.x=0.0f; offset.y=0.0f;
 float extra=0.0f;
 if(m_39) {
  if(!moved) rva0042CB81(8);
  if(reinterpret_cast<Rva002BE8D4 *>(((Rva002D3627Host *)TheLivingWorld))->rva002BE8D4()) rva0042CB81(1);
 }
 if(m_39) {
  if(m_08 & 1) {
   if(*(reinterpret_cast<unsigned char *>(TheInGameUI)+0x8C4)) {
    int maxX=reinterpret_cast<CameraDisplay42 *>(TheDisplay)->width()/2;
    int maxY=reinterpret_cast<CameraDisplay42 *>(TheDisplay)->height()/2;
    if(m_18+maxX < m_10) m_10=m_18+maxX;
    else if(m_18-maxX > m_10) m_10=m_18-maxX;
    if(m_1C+maxY < m_14) m_14=m_1C+maxY;
    else if(m_1C-maxY > m_14) m_14=m_1C-maxY;
   }
   offset.x=(m_18-m_10)*CAMERA_DATA42->horizontal;
   offset.y=(m_1C-m_14)*CAMERA_DATA42->vertical;
   Coord2D direction;
   direction.x=offset.x; direction.y=offset.y;
   direction.normalize();
   offset.x+=CAMERA_DATA42->horizontal*CAMERA_DATA42->keyboard*CAMERA_DATA42->keyboard*direction.x;
   offset.y+=CAMERA_DATA42->vertical*CAMERA_DATA42->keyboard*CAMERA_DATA42->keyboard*direction.y;
  }
  if(m_08 & 2) extra=(m_28-m_20)*0.005f;
  if(m_08 & 4) {
   if(m_3A[0]) offset.y-=CAMERA_DATA42->keyboard*CAMERA_DATA42->vertical*350.0f;
   if(m_3A[1]) offset.y+=CAMERA_DATA42->keyboard*CAMERA_DATA42->vertical*350.0f;
   if(m_3A[2]) offset.x-=CAMERA_DATA42->keyboard*CAMERA_DATA42->horizontal*350.0f;
   if(m_3A[3]) offset.x+=CAMERA_DATA42->keyboard*CAMERA_DATA42->horizontal*350.0f;
  }
  if(m_08 & 8) {
   unsigned height=reinterpret_cast<CameraDisplay42 *>(TheDisplay)->height();
   unsigned width=reinterpret_cast<CameraDisplay42 *>(TheDisplay)->width();
   if(m_1C<3) offset.y-=CAMERA_DATA42->keyboard*CAMERA_DATA42->edge*CAMERA_DATA42->vertical*350.0f;
   if((unsigned)m_1C>=height-3) offset.y+=CAMERA_DATA42->keyboard*CAMERA_DATA42->edge*CAMERA_DATA42->vertical*350.0f;
   if(m_18<3) offset.x-=CAMERA_DATA42->keyboard*CAMERA_DATA42->edge*CAMERA_DATA42->horizontal*350.0f;
   if((unsigned)m_18>=width-3) offset.x+=CAMERA_DATA42->keyboard*CAMERA_DATA42->edge*CAMERA_DATA42->horizontal*350.0f;
  }
  reinterpret_cast<CameraMotion42 *>(((Rva002D3627Host *)TheLivingWorld))->s11(&offset,extra);
  m_30+=fabs(offset.x);
  m_34+=fabs(offset.y);
 } else {
  if(m_3E) reinterpret_cast<CameraMotion42 *>(((Rva002D3627Host *)TheLivingWorld))->s11(&offset,CAMERA_DATA42->rotate*-15.0f);
  else if(m_3F) reinterpret_cast<CameraMotion42 *>(((Rva002D3627Host *)TheLivingWorld))->s11(&offset,CAMERA_DATA42->rotate*15.0f);
  else if(m_40) reinterpret_cast<CameraMotion42 *>(((Rva002D3627Host *)TheLivingWorld))->s21(1);
  else if(m_41) reinterpret_cast<CameraMotion42 *>(((Rva002D3627Host *)TheLivingWorld))->s21(-1);
 }
}

// Complete native 82CC7B..82D068, 1005B, RET4: the receiver's message
// handler. Slot 0 of the +4 listener may consume the message first. A
// GameLogic counter guard (pinned ctor 0x0004224C, inline decrement) spans
// the dispatch; the sparse message and key cases drive the same home's
// scroll flags and anchors. Message and key meanings are inferences.
// The guard's ctor body is visible (as in LivingWorldLogic.cpp): cl then
// keeps the empty object in the dead message home. Case order decides
// which identical disposition tails cl keeps; separate checks keep the
// early-exit unwind beside them, as in retail.
class Rva0023C748 { public: char rva0023C748(); };
class Rva002B34E5 { public: void rva002B34E5(bool); };
class Rva000421FD { public: void rva000421FD(); };
class Rva0004224C {
public:
 Rva0004224C() { if(TheGameLogic) reinterpret_cast<Rva000421FD *>(TheGameLogic)->rva000421FD(); }
 ~Rva0004224C() { if(TheGameLogic) --*reinterpret_cast<int *>(reinterpret_cast<char *>(TheGameLogic)+0x1B4); }
};
union GameMessageArgumentType {
 int integer; float real; unsigned char boolean;
 struct Pix { int x,y; } pixel;
};
class GameMessage {
public:
 const GameMessageArgumentType *getArgument(int) const;
 char pad[0x10]; int type;
};
class MessageForward42 { public: virtual int translate(GameMessage *); };
class MessageUI42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual void s21(); virtual void s22();
 virtual void s23(int,GameMessageArgumentType::Pix *);
};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Shell; extern Shell *TheShell;
#define BYTE_AT42(p,o) (*(reinterpret_cast<unsigned char *>(p)+(o)))
int Rva0042CBB6::rva0042CC7B(GameMessage *message)
{
 if(m_04) {
  int forwarded=reinterpret_cast<MessageForward42 *>(m_04)->translate(message);
  if(forwarded==1) return forwarded;
 }
 int disposition=0;
 if(reinterpret_cast<Rva0023C748 *>(TheGameLogic)->rva0023C748()) return 0;
 Rva0004224C guard;
 if(!TheLivingWorld) return 0;
 int type=message->type;
 if(!BYTE_AT42(TheLivingWorld,0x18)) return 0;
 if(TheGameLogic->isGamePaused()) return 0;
 switch(type) {
 case 14:
  if(TheLivingWorld && !BYTE_AT42(TheLivingWorldManager,0x2C0)) {
   const GameMessageArgumentType *gameMessageArgumentType=message->getArgument(0);
   m_10=gameMessageArgumentType->pixel.x; m_14=gameMessageArgumentType->pixel.y;
   gameMessageArgumentType=message->getArgument(0);
   m_18=gameMessageArgumentType->pixel.x; m_1C=gameMessageArgumentType->pixel.y;
   if(TheMouse->m_currentCursor) { rva0042CB57(1); m_30=0; m_34=0; }
  }
  disposition=1;
  break;
 case 11:
  rva0042CAFB();
  break;
 case 16:
  {
   int limit=*reinterpret_cast<int *>(reinterpret_cast<char *>(TheLivingWorldManager)+0x1E0);
   int within=0;
   if(m_30<limit && m_34<limit) within=1;
   m_38=within;
   rva0042CB81(1);
   disposition=1;
  }
  break;
 case 19:
  if(!reinterpret_cast<Rva002BE8D4 *>(((Rva002D3627Host *)TheLivingWorld))->rva002BE8D4()) {
   GameMessageArgumentType::Pix point=message->getArgument(0)->pixel;
   int value=message->getArgument(1)->integer;
   reinterpret_cast<MessageUI42 *>(((Rva002D3627Host *)TheLivingWorld))->s23(value,&point);
   disposition=1;
  }
  break;
 case 153:
  reinterpret_cast<Rva002B34E5 *>(TheLivingWorldLogic)->rva002B34E5(!BYTE_AT42(TheLivingWorldLogic,0x10B));
  break;
 case 23:
  disposition=1;
  break;
 case 1104:
  disposition=1;
  break;
 case 10:
  if(!BYTE_AT42(TheLivingWorldManager,0x2C0)) {
   const GameMessageArgumentType *gameMessageArgumentType=message->getArgument(0);
   m_20=gameMessageArgumentType->pixel.x; m_24=gameMessageArgumentType->pixel.y;
   gameMessageArgumentType=message->getArgument(0);
   m_28=gameMessageArgumentType->pixel.x; m_2C=gameMessageArgumentType->pixel.y;
   if(TheMouse->m_currentCursor) rva0042CB57(2);
  }
  disposition=1;
  break;
 case 21:
 case 22:
  {
   unsigned char key=message->getArgument(0)->boolean;
   unsigned char down=~message->getArgument(1)->boolean&1;
   if(TheShell && BYTE_AT42(TheShell,0x5C))
    break;
   switch(key) {
   case 72: m_40=down; break;
   case 75: m_3E=down; break;
   case 76: rva0042CAFB(); break;
   case 77: m_3F=down; break;
   case 80: m_41=down; break;
   case 200: m_3A[0]=down; break;
   case 203: m_3A[2]=down; break;
   case 205: m_3A[3]=down; break;
   case 208: m_3A[1]=down; break;
   }
   int pressed=0;
   for(int i=0;i<4;++i)
    if(m_3A[i]) ++pressed;
   if(pressed) rva0042CB57(4);
   else rva0042CB81(4);
   disposition=1;
  }
  break;
 case 12:
  rva0042CB81(2);
  disposition=1;
  break;
 case 3:
  if(!BYTE_AT42(TheLivingWorld,0x18)) {
   rva0042CB81(0);
   break;
  }
  m_42=1;
  {
   const GameMessageArgumentType *gameMessageArgumentType=message->getArgument(0);
   m_18=gameMessageArgumentType->pixel.x; m_1C=gameMessageArgumentType->pixel.y;
   gameMessageArgumentType=message->getArgument(0);
   m_28=gameMessageArgumentType->pixel.x; m_2C=gameMessageArgumentType->pixel.y;
   unsigned height=reinterpret_cast<CameraDisplay42 *>(TheDisplay)->height();
   unsigned width=reinterpret_cast<CameraDisplay42 *>(TheDisplay)->width();
   if(!BYTE_AT42(TheWritableGlobalData,0x2C)) {
    if(m_08 & 8) {
     if(m_08==8 && m_18>=3 && m_1C>=3 && (unsigned)m_1C<height-3 && (unsigned)m_18<width-3)
      rva0042CB81(8);
    } else if(!BYTE_AT42(TheLivingWorldManager,0x2C0)) {
     if(m_18<3 || m_1C<3 || (unsigned)m_1C>=height-3 || (unsigned)m_18>=width-3)
      rva0042CB57(8);
    }
   }
  }
  disposition=1;
  break;
 }
 return disposition;
}
