// ?rva0025C3AA@W3DDisplay@@QAEXXZ
// partial score=0.8977104755784062 date=2026-10-10
// cl: /O1 /G7 /arch:IA32 /DNDEBUG /MD /EHsc /I. /Ireference/shims/bfme2_ascii
// BF1 f989 MovieOpen0040E3B0.cpp play0040F780 guides movie loop; target25D6F5..25D904 RET12.
// Native removes thread priority and per-frame keyboard scan, retains helper25CEEF and rva25C3AA.
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern "C" __declspec(dllimport) long __stdcall SendMessageA(void*,unsigned,unsigned,long);
extern void*ApplicationHWnd;extern __int64 g_bfmeVM0Total;extern double g_bfmeVM0Scale;
extern GameLogic*TheGameLogic;
bool bfmeGoEMEa(void*);void bfmeSetReceiverFlag(int);void setFPMode();bool Rva0025CEEFCheck(bool);
template<int N>class MovieSlots:public MovieSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class MovieSlots<0>{};
class AudioManager:public MovieSlots<69>{public:virtual void suspend()=0;virtual void resume()=0;virtual void pump()=0;};extern AudioManager*TheAudio;
class GlobalData;extern GlobalData*TheGlobalData;struct MovieSettings{char pad0[0x11c8];bool enabled;};
class GameWindowManager:public MovieSlots<10>{public:virtual void pump()=0;};extern GameWindowManager*TheWindowManager;
class Mouse{public:void _bfme_setEngineVisibility(bool);};extern Mouse*TheMouse;
class GameWindowTransitionsHandler:public MovieSlots<9>{public:virtual void reset()=0;virtual void pump()=0;};extern GameWindowTransitionsHandler*TheTransitionHandler;
class Keyboard:public MovieSlots<10>{public:virtual void pump()=0;};extern Keyboard*TheKeyboard;
class GameEngine:public MovieSlots<23>{public:virtual void pump()=0;};extern GameEngine*TheGameEngine;
class BfmeDfe6e4{public:void rva00225492();};extern BfmeDfe6e4*TheWatchdogThread;
class VideoStreamInterface:public MovieSlots<6>{public:virtual unsigned advance(int)=0;virtual void gap7()=0;virtual void gap8()=0;virtual void gap9()=0;virtual void gap10()=0;virtual int width()=0;virtual int height()=0;};
class Display{public:bool rva0025CC7A(bool);};
class W3DDisplay:public MovieSlots<16>{public:virtual unsigned width()=0;virtual unsigned height()=0;virtual void gap18()=0;virtual void gap19()=0;virtual void gap20()=0;virtual void gap21()=0;virtual void gap22()=0;virtual void gap23()=0;virtual void gap24()=0;virtual void gap25()=0;virtual void gap26()=0;virtual void gap27()=0;virtual void gap28()=0;virtual void gap29()=0;virtual void gap30()=0;virtual void gap31()=0;virtual void gap32()=0;virtual void gap33()=0;virtual void gap34()=0;virtual void gap35()=0;virtual void gap36()=0;virtual void gap37()=0;virtual void gap38()=0;virtual void gap39()=0;virtual void gap40()=0;virtual void gap41()=0;virtual void gap42()=0;virtual void gap43()=0;virtual void gap44()=0;virtual void gap45()=0;virtual void gap46()=0;virtual void gap47()=0;virtual void gap48()=0;virtual void gap49()=0;virtual void gap50()=0;virtual void gap51()=0;virtual void gap52()=0;virtual void gap53()=0;virtual void gap54()=0;virtual void gap55()=0;virtual void gap56()=0;virtual void gap57()=0;virtual void gap58()=0;virtual void gap59()=0;virtual void gap60()=0;virtual void gap61()=0;virtual void gap62()=0;virtual void gap63()=0;virtual void gap64()=0;virtual void gap65()=0;virtual bool startMovie(AsciiString,int,int,int)=0;virtual void gap67()=0;virtual void close()=0;virtual void gap69()=0;virtual void gap70()=0;virtual void gap71()=0;virtual void gap72()=0;virtual void gap73()=0;virtual void gap74()=0;virtual void gap75()=0;virtual void gap76()=0;virtual void gap77()=0;virtual void gap78()=0;virtual void gap79()=0;virtual void gap80()=0;virtual void gap81()=0;virtual void gap82()=0;virtual void gap83()=0;virtual void gap84()=0;virtual void gap85()=0;virtual void gap86()=0;virtual void gap87()=0;virtual void gap88()=0;virtual void gap89()=0;virtual void gap90()=0;virtual void gap91()=0;virtual void gap92()=0;virtual void gap93()=0;virtual void gap94()=0;virtual void gap95()=0;virtual void gap96()=0;virtual void gap97()=0;virtual void gap98()=0;virtual void render(bool)=0;
 bool rva0025D6F5(AsciiString,bool,int);void rva0025D2F6();void rva0025C3AA();char pad4[0x38-4];VideoStreamInterface*stream;char pad3c[0x64-0x3c];bool flag64;char pad65[0xfc-0x65];float left,top,right,bottom;bool flag10c;
};
// BF1 UnsignedBlendStateUpdate.cpp bfmeGoDC, target viewport16/17 not donor11/12.
void W3DDisplay::rva0025C3AA(){
 if(!flag10c)return;if(!stream)return;
 float ratio=(float)stream->width()/(float)stream->height();float a=(float)width();left=0.0f;a*=ratio;
 float b=(float)height()-a;top=0.5f*b;right=(float)width();bottom=a+top;
}
