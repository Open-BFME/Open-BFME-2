// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /Ireference/shims/bfme2_ascii
// BF1 f989 MovieOpen0040E3B0.cpp play0040F780 guides movie loop; target25D6F5..25D904 RET12.
// Native removes thread priority and per-frame keyboard scan, retains helper25CEEF and rva25C3AA.
// Target facts: flag10C, stream38, clear64 and virtual slots66/68/99; owned update25CC7A and clear25D2F6 provide ABI context.
// Play-loop identity/semantics carried from clean BF1 donor; the original method spelling remains unresolved.
// The watchdog global uses the data ledger owner theBfmeDfe6e4; WB identifies the called role as WatchdogThread::Ping.
// Timing and window globals reuse established BfmeConv1435/ApplicationHWnd providers. No global is defined here.
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern "C" __declspec(dllimport) long __stdcall SendMessageA(void*,unsigned,unsigned,long);
extern void*ApplicationHWnd;extern __int64 g_bfmeVM0Total;extern double g_bfmeVM0Scale;
extern GameLogic*TheGameLogic;
bool bfmeGoEMEa(void*);void bfmeSetReceiverFlag(int);void setFPMode();bool Rva0025CEEFCheck(bool);
template<int N>class MovieSlots:public MovieSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class MovieSlots<0>{};
class AudioManager:public MovieSlots<69>{public:virtual void suspend()=0;virtual void resume()=0;virtual void pump()=0;};extern AudioManager*TheAudio;
class GlobalData;extern GlobalData*TheWritableGlobalData;struct MovieSettings{char pad0[0x11c8];bool enabled;};
class GameWindowManager:public MovieSlots<10>{public:virtual void pump()=0;};extern GameWindowManager*TheWindowManager;
class Mouse{public:void _bfme_setEngineVisibility(bool);};extern Mouse*TheMouse;
class GameWindowTransitionsHandler:public MovieSlots<9>{public:virtual void reset()=0;virtual void pump()=0;};extern GameWindowTransitionsHandler*TheTransitionHandler;
class Keyboard:public MovieSlots<10>{public:virtual void pump()=0;};extern Keyboard*TheKeyboard;
class GameEngine:public MovieSlots<23>{public:virtual void pump()=0;};extern GameEngine*TheGameEngine;
class BfmeDfe6e4{public:void rva00225492();};extern BfmeDfe6e4*theBfmeDfe6e4;
class VideoStreamInterface:public MovieSlots<6>{public:virtual unsigned advance(int)=0;};
class Display{public:bool rva0025CC7A(bool);};
class W3DDisplay:public MovieSlots<66>{public:virtual bool startMovie(AsciiString,int,int,int)=0;virtual void gap67()=0;virtual void close()=0;virtual void gap69()=0;virtual void gap70()=0;virtual void gap71()=0;virtual void gap72()=0;virtual void gap73()=0;virtual void gap74()=0;virtual void gap75()=0;virtual void gap76()=0;virtual void gap77()=0;virtual void gap78()=0;virtual void gap79()=0;virtual void gap80()=0;virtual void gap81()=0;virtual void gap82()=0;virtual void gap83()=0;virtual void gap84()=0;virtual void gap85()=0;virtual void gap86()=0;virtual void gap87()=0;virtual void gap88()=0;virtual void gap89()=0;virtual void gap90()=0;virtual void gap91()=0;virtual void gap92()=0;virtual void gap93()=0;virtual void gap94()=0;virtual void gap95()=0;virtual void gap96()=0;virtual void gap97()=0;virtual void gap98()=0;virtual void render(bool)=0;
 bool rva0025D6F5(AsciiString,bool,int);void rva0025D2F6();void rva0025C3AA();char pad4[0x38-4];VideoStreamInterface*stream;char pad3c[0x64-0x3c];bool flag64;char pad65[0x10c-0x65];bool flag10c;
};
bool W3DDisplay::rva0025D6F5(AsciiString name,bool allowSkip,int flags){
 SendMessageA(ApplicationHWnd,15,0,0);g_bfmeVM0Scale=(1.0/30.0)/(double)g_bfmeVM0Total*1000.0;
 TheGameLogic->rva0023CD9E(true,0,false);bool active=bfmeGoEMEa(0);if(TheAudio)TheAudio->suspend();
 if(startMovie(name,flags|8,-1,-1)){
  flag10c=true;unsigned pending=0;bool skipRequested=false;bool drawFrame=false;TheWindowManager->pump();TheMouse->_bfme_setEngineVisibility(false);bool alternateAudio=false;bool done;
  do{if(Rva0025CEEFCheck(allowSkip))skipRequested=true;done=((Display*)this)->rva0025CC7A(skipRequested);
   if(stream&&!(pending&2)){pending|=stream->advance(0);drawFrame=(pending&1)!=0;}else done=true;
   if(drawFrame){drawFrame=false;pending&=~1U;rva0025C3AA();render(true);TheTransitionHandler->pump();TheGameEngine->pump();if(alternateAudio){TheAudio->pump();alternateAudio=false;}else alternateAudio=true;setFPMode();}
   if(theBfmeDfe6e4)theBfmeDfe6e4->rva00225492();
  }while(!done);
  close();flag64=false;rva0025D2F6();TheKeyboard->pump();
 }
 if(TheAudio)TheAudio->resume();if(!((MovieSettings*)TheWritableGlobalData)->enabled&&active)bfmeSetReceiverFlag(0);TheGameLogic->rva0023CD9E(false,0,false);
 if(flags&0x100000){TheTransitionHandler->reset();TheMouse->_bfme_setEngineVisibility(true);}TheWindowManager->pump();return true;
}
