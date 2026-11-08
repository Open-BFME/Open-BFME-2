// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/GameEngine/Source/Common
// stlport
// platformsdk
//
// W3DDisplay::draw (retail 0x0004BEF2..0x0004C3D8, W3DDisplay vftable 0x007C3C80
// slot 12). Zero Hour's W3DDisplay::draw is the semantic guide and source of the
// carried comments; WorldBuilder 0x96E810 supplies the statement order of the
// panorama capture and the keepDrawing loop. BFME 2 moves the full render into
// 0x0004A462 and adds panorama captures; retail repeats while paused, and array
// new/delete follow native evidence.
// capturePending and captureIndex are file-static: with an external
// capturePending retail's takeScreenShot vptr load would follow dec
// [capturePending]. Its other writer, the 0x0004538C callback, therefore lives
// here too. Evidence: reverse/attempt_support/w1-4bef2-20261020.md,
// w6-4bef2-20261020.md, w8-4bef2-20261019.md.
#include <new>
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include <windows.h>
#include <mmsystem.h>
#define TWO_PI 6.28318530718f
struct POINT2 { int x,y; }; struct RECT2 { int left,top,right,bottom; };
class W3DView {public:bool updateCameraMovements();};
class FrameClient {public:
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
virtual unsigned getFrame();
char pad[0xC8-4];bool active;};
class TimeView {public:
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
virtual bool isCameraMovementFinished();
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
virtual int getTimeMultiplier();
};
#include "../../../../GameEngine/Include/Common/GlobalData.h"
class Rva00084C05System {public:void update();};
class Rva00203B47Host {public:bool rva00203B47();};
class GameClient;class View;extern GameLogic*TheGameLogic;extern GameClient*TheGameClient;extern View*TheTacticalView;extern GlobalData*TheWritableGlobalData;
#define TheGlobalData ((const GlobalData*)TheWritableGlobalData)
class TerrainTracksRenderObjClassSystem;extern TerrainTracksRenderObjClassSystem*TheTerrainTracksRenderObjClassSystem;class ScriptEngine;extern ScriptEngine*TheScriptEngine;
// WinMain owns the non-STRICT handle global; convert only at Win32 calls.
extern void *ApplicationHWnd;
extern int g_bfmeDisplayAnimationSyncClock,g_Va00DB3BDC;
static int capturePending,captureIndex;extern int TheW3DFrameLengthInMsec;

// Native 0004538C/32 is a complete RET8 body, referenced by retail callback
// table operand 007C3DD0 (whole clean BFME 1 Gen_006eab10_Clamp.cpp donor at
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24). It clears capturePending (VA
// DE1B28) when positive, otherwise stores the first stack word, and returns
// AL=1. The ignored second word's original type and the callback's name remain
// unknown; the donor's clamp name is not promoted to a target identity.
bool __stdcall Rva0004538C(int value, unsigned int)
{
    if (capturePending > 0)
        capturePending = 0;
    else
        capturePending = value;
    return true;
}

class DebugDisplayInterface;
struct _iobuf;
typedef void DebugDisplayCallback(DebugDisplayInterface *, void *, _iobuf *);
void StatDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
void AnimDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
void NetworkDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
void SkirmishAIDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
void Rva00079985Clear();
#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
class W3DDisplay {public:
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
virtual void draw();
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
virtual W3DView*getFirstView();
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
virtual void takeScreenShot(const char*);
void updateAverageFPS();void rva00043FB9();protected:void gatherAnimationDebuggingInfo();public:virtual void gatherDebugStats();virtual void gatherNetworkStats();void gatherSkirmishAIStats();bool rva0004A462(unsigned);
private:
void rva00045213(char*,unsigned);void rva00047BC0(char*,unsigned,unsigned,const char*);
public:
char pad04[0x30-4]; DebugDisplayCallback *debugDisplayCallback;char pad34[0x115-0x34];bool disabled;
};
// The slice index takes the count by const reference: retail's add eax,0xEA0 / mov ecx,[eax] in that arm is the materialized reference.
inline int panoramaSliceIndex(int i,const int&count){return (i+count/2)%count;}
void W3DDisplay::draw(){
 if(ApplicationHWnd && IsIconic((HWND)ApplicationHWnd))return;
 updateAverageFPS();rva00043FB9();
 // compute debug statistics for display later
 if(debugDisplayCallback==StatDebugDisplay)W3DDisplay::gatherDebugStats();
 else if(debugDisplayCallback==AnimDebugDisplay)gatherAnimationDebuggingInfo();
 else if(debugDisplayCallback==NetworkDebugDisplay)W3DDisplay::gatherNetworkStats();
 else if(debugDisplayCallback==SkirmishAIDebugDisplay)gatherSkirmishAIStats();
 bool freezeTime=!((FrameClient*)TheGameClient)->active;
 /// @todo: I'm assuming the first view is our main 3D view.
 W3DView*primaryW3DView=getFirstView();
 // hack to let client spin fast in network games but still do effects at the same pace. -MDC
 if((unsigned)g_Va00DB3BDC>((FrameClient*)TheGameClient)->getFrame())g_Va00DB3BDC=((FrameClient*)TheGameClient)->getFrame();
 unsigned delta=((FrameClient*)TheGameClient)->getFrame()-g_Va00DB3BDC;
 if(freezeTime)delta=0;else g_Va00DB3BDC=((FrameClient*)TheGameClient)->getFrame();
 bool fastMode=false;
 if(!TheGameLogic->isGamePaused() && TheGlobalData->field0BBD)fastMode=true;
 if(((Rva00203B47Host*)TheScriptEngine)->rva00203B47())fastMode=true;
 if(!freezeTime && fastMode && !TheGameLogic->getFlag125() && ((FrameClient*)TheGameClient)->getFrame()%30!=0){
  primaryW3DView->updateCameraMovements();  // Update camera motion effects.
  g_bfmeDisplayAnimationSyncClock+=TheW3DFrameLengthInMsec;WW3D::Sync(g_bfmeDisplayAnimationSyncClock);return;}
 //update state of all the terrain tracks (fade, remove, etc.)
 if(TheGlobalData->field0AF5!=true && TheTerrainTracksRenderObjClassSystem)((Rva00084C05System*)TheTerrainTracksRenderObjClassSystem)->update();
 /// @todo Decouple framerate from timestep
 // for now, use constant time steps to avoid animations running independent of framerate
 g_bfmeDisplayAnimationSyncClock+=TheW3DFrameLengthInMsec*delta;WW3D::Sync(g_bfmeDisplayAnimationSyncClock);
 // Fast & Frozen time limits the time to 33 fps.
 int minTime=30;
 static int prevTime=timeGetTime();
 int now=timeGetTime();
 if(((TimeView*)TheTacticalView)->getTimeMultiplier()>1){
  static int timeMultiplierCounter=1;--timeMultiplierCounter;if(timeMultiplierCounter>1)return;timeMultiplierCounter=((TimeView*)TheTacticalView)->getTimeMultiplier();
  // limit the framerate, because while fast time is on, the game logic is running as fast as it can.
 }
 else prevTime=now-minTime;		 // do the first frame immediately.
 if(disabled)return;
 bool keepDrawing=false;
 do{
  if(TheGlobalData->field0AF5!=true){
   // limit the framerate
   while(TheGlobalData->m_useFpsLimit && now-prevTime<minTime-1)now=timeGetTime();prevTime=now;}
  if(capturePending>0 && TheGlobalData->field0EA0!=0){
   TheWritableGlobalData->field0EA6=true;TheWritableGlobalData->field0EA8=TWO_PI/TheGlobalData->field0EA0;
   RECT2 rect;GetClientRect((HWND)ApplicationHWnd,(RECT*)&rect);POINT2 point;point.x=rect.left;point.y=rect.top;ClientToScreen((HWND)ApplicationHWnd,(POINT*)&point);rect.left=point.x;rect.top=point.y;point.x=rect.right;point.y=rect.bottom;ClientToScreen((HWND)ApplicationHWnd,(POINT*)&point);rect.right=point.x;rect.bottom=point.y;
   int width=rect.right-rect.left;int height=rect.bottom-rect.top;
   char*image=0;
   if(!TheGlobalData->field0EA4)image=new char[width*3*height*TheGlobalData->field0EA0];
   for(int i=0;i<TheGlobalData->field0EA0;++i){
    TheWritableGlobalData->field0EAC=i*-TWO_PI/TheGlobalData->field0EA0;
    TheWritableGlobalData->field0EA7=(i==TheGlobalData->field0EA0-1);
    if(!rva0004A462(now))freezeTime=false;
    if(TheGlobalData->field0EA4){AsciiString name;name.format("sshot_panorama_%.2d_%.4d",i,captureIndex);takeScreenShot(name.str());}
    else rva00045213(image+width*3*panoramaSliceIndex(i,TheGlobalData->field0EA0),width*3*TheGlobalData->field0EA0);
   }
   if(!TheGlobalData->field0EA4){rva00047BC0(image,width*TheGlobalData->field0EA0,height,0);delete[]image;}
   ++captureIndex;--capturePending;TheWritableGlobalData->field0EA6=false;
  }else if(!rva0004A462(now))break;
  keepDrawing=freezeTime&&!((TimeView*)TheTacticalView)->isCameraMovementFinished();
  if(keepDrawing&&!TheGameLogic->isGamePaused())keepDrawing=false;
 }while(keepDrawing);
 if(capturePending>0&&TheGlobalData->field0EA0==0&&TheGlobalData->field0C54.empty()){--capturePending;takeScreenShot(0);}
 Rva00079985Clear();
}
