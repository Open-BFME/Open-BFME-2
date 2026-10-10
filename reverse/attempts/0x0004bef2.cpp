// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.9213 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/GameEngine/Source/Common
// stlport
// ZH W3DDisplay::draw semantic guide; native 4BEF2..4C3D8.
// BFME2 separates the full render into 4A462 and adds panorama captures.
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include <windows.h>
#include <mmsystem.h>
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
class GlobalData {public:
char pad0[0x26];bool useFpsLimit; char pad27[0xAF5-0x27];bool loadScreenRender;
char padAF6[0xBBD-0xAF6];bool fastMode;char padBBE[0xC54-0xBBE];void*begin,*end;
char padC5C[0xEA0-0xC5C];int panoramaCount; bool panoramaIndividual; char reservedEA5;bool panoramaMode;bool panoramaLast;float panoramaScale;float panoramaAngle;
};
class Tracks {public:void update();};
class Rva00203B47Host {public:bool rva00203B47();};
extern GameLogic*TheGameLogic;extern FrameClient*TheGameClient;extern TimeView*TheTacticalView;extern GlobalData*TheGlobalData;
extern Tracks*TheTerrainTracksRenderObjClassSystem;extern Rva00203B47Host*g_pRva003BBEDE;
extern HWND ApplicationHWnd;
extern unsigned syncTime,displayLastFrame;extern int timeMultiplierCounter,prevTime,prevTimeFlag;
extern int capturePending,captureIndex;extern int g_Va00DE204C;
void StatDebugDisplay();void Rva00043D69Callback();void Rva00043D96Callback();void Rva00043D3CCallback();
void Rva00079985();
class WW3D {public:static void Sync(unsigned);};
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
void draw();void updateAverageFPS();void rva00043FB9();void rva0004826C();void rva0004B31C();void rva00049271();void rva0004AA4A();bool rva0004A462(unsigned);
private:
void rva00045213(char*,unsigned);void rva00047BC0(char*,unsigned,unsigned,const char*);
public:
char pad04[0x30-4]; void(*debugDisplayCallback)();char pad34[0x115-0x34];bool disabled;
};
void W3DDisplay::draw(){
 if(ApplicationHWnd && IsIconic(ApplicationHWnd))return;
 updateAverageFPS();rva00043FB9();
 if(debugDisplayCallback==StatDebugDisplay)rva0004826C();
 else if(debugDisplayCallback==Rva00043D69Callback)rva0004B31C();
 else if(debugDisplayCallback==Rva00043D96Callback)rva00049271();
 else if(debugDisplayCallback==Rva00043D3CCallback)rva0004AA4A();
 bool freezeTime=!TheGameClient->active;
 W3DView*primaryW3DView=getFirstView();
 if(displayLastFrame>TheGameClient->getFrame())displayLastFrame=TheGameClient->getFrame();
 unsigned delta=TheGameClient->getFrame()-displayLastFrame;
 if(freezeTime)delta=0;else displayLastFrame=TheGameClient->getFrame();
 bool fastMode=false;
 if(!TheGameLogic->isGamePaused() && TheGlobalData->fastMode)fastMode=true;
 if(g_pRva003BBEDE->rva00203B47())fastMode=true;
 if(!freezeTime && fastMode && !TheGameLogic->getFlag125() && TheGameClient->getFrame()%30!=0){primaryW3DView->updateCameraMovements();syncTime+=g_Va00DE204C;WW3D::Sync(syncTime);return;}
 if(TheGlobalData->loadScreenRender!=true && TheTerrainTracksRenderObjClassSystem)TheTerrainTracksRenderObjClassSystem->update();
 syncTime+=g_Va00DE204C*delta;WW3D::Sync(syncTime);
 if(!(prevTimeFlag&1)){prevTimeFlag|=1;prevTime=timeGetTime();}
 int now=timeGetTime();
 if(TheTacticalView->getTimeMultiplier()>1){--timeMultiplierCounter;if(timeMultiplierCounter>1)return;timeMultiplierCounter=TheTacticalView->getTimeMultiplier();}
 else prevTime=now-30;
 if(disabled)return;
 do{
  if(TheGlobalData->loadScreenRender!=true){while(TheGlobalData->useFpsLimit && now-prevTime<29)now=timeGetTime();prevTime=now;}
  if(capturePending>0 && TheGlobalData->panoramaCount!=0){
   TheGlobalData->panoramaMode=true;TheGlobalData->panoramaScale=1.0f/TheGlobalData->panoramaCount;
   RECT2 rect;GetClientRect(ApplicationHWnd,(RECT*)&rect);POINT2 point;point.x=rect.left;point.y=rect.top;ClientToScreen(ApplicationHWnd,(POINT*)&point);rect.left=point.x;rect.top=point.y;point.x=rect.right;point.y=rect.bottom;ClientToScreen(ApplicationHWnd,(POINT*)&point);rect.right=point.x;rect.bottom=point.y;
   int width=rect.right-rect.left,height=rect.bottom-rect.top;int i=0;char*image=0;
   if(!TheGlobalData->panoramaIndividual)image=new char[TheGlobalData->panoramaCount*height*width*3];
   for(;i<TheGlobalData->panoramaCount;++i){
    TheGlobalData->panoramaAngle=i*-6.28318530717958647692f/TheGlobalData->panoramaCount;
    TheGlobalData->panoramaLast=(i==TheGlobalData->panoramaCount-1);
    if(!rva0004A462(now))freezeTime=false;
    if(TheGlobalData->panoramaIndividual){AsciiString name;name.format("sshot_panorama_%.2d_%.4d",i,captureIndex);takeScreenShot(name.str());}
    else{int&count=TheGlobalData->panoramaCount;rva00045213(image+((i+count/2)%count)*width*3,count*width*3);}
   }
   if(!TheGlobalData->panoramaIndividual){rva00047BC0(image,TheGlobalData->panoramaCount*width,height,0);delete[]image;}
   ++captureIndex;--capturePending;TheGlobalData->panoramaMode=false;
  }else if(!rva0004A462(now))break;
 }while(freezeTime&&!TheTacticalView->isCameraMovementFinished()&&!TheGameLogic->isGamePaused());
 if(capturePending>0&&TheGlobalData->panoramaCount==0&&TheGlobalData->begin==TheGlobalData->end){--capturePending;takeScreenShot(0);}
 Rva00079985();
}
