// cl: /DNDEBUG /MD /EHsc
// BFME1 clean donor6583b3c1ff21db4a561285717028fdafc780b7db:
// game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp hideShell(void)
// supplies top-layout shutdown, IME detach and shell-active reset semantics.
// Native35BF4C..35BFBC/112B adds a bool argument gating the shutdown, no
// clear-background write, GlobalData+AF0/display69B25D2F6 cleanup and audio.
// Rowed13B Shell::top35BD7E plus receiver+5C establish the Shell prefix;
// all named global DIR32s verify. WindowLayout slot3 gets an actual true
// local bool; cl reuses the dead argument's high byte at EBP+B naturally.
// The target's original method name is unknown: the existing hide(bool) pin
// is a caller ABI spelling, not proof of Zero Hour's hide-all-layouts method.
// GlobalData+AF0 meaning and AudioManager slot35 method name remain unknown.
// The native audio arguments are three words2/1/0. The full30B audio-handle
// release35BD3F independently verifies and is reached with the same receiver.
class WindowLayout {
public:virtual void s0()=0;virtual void s1()=0;virtual void s2()=0;virtual void runShutdown(bool*)=0;
};
class IMEManager {public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void detatch()=0;};extern IMEManager*TheIMEManager;
class GlobalData {public:unsigned char unknown[0xAF0];bool unknownAF0;};extern GlobalData*TheWritableGlobalData;
class Display;extern Display*TheDisplay;
class W3DDisplay {public:void rva0025D2F6();};
class AudioManager {public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void slot21()=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual void slot26()=0;
virtual void slot27()=0;
virtual void slot28()=0;
virtual void slot29()=0;
virtual void slot30()=0;
virtual void slot31()=0;
virtual void slot32()=0;
virtual void slot33()=0;
virtual void slot34()=0;
virtual void slot35(int,int,int)=0;};extern AudioManager*TheAudio;
class Rva0035BD3F {public:void rva0035BD3F();};
class Shell {public:WindowLayout*top();void rva0035BF4C(bool shutdownImmediate);private:char unknown[0x5C];bool active5C;};
void Shell::rva0035BF4C(bool shutdownImmediate) {
 WindowLayout*layout=top();
 if(layout && shutdownImmediate) {bool immediate=true;layout->runShutdown(&immediate);}
 if(TheIMEManager)TheIMEManager->detatch();
 active5C=false;
 if(!TheWritableGlobalData->unknownAF0)reinterpret_cast<W3DDisplay*>(TheDisplay)->rva0025D2F6();
 reinterpret_cast<Rva0035BD3F*>(this)->rva0035BD3F();
 TheAudio->slot35(2,1,0);
}

#pragma comment(linker,"/alternatename:?hide@Shell@@QAEX_N@Z=?rva0035BF4C@Shell@@QAEX_N@Z")
