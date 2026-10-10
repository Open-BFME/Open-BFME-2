// ?rva0022D290@GameEngine@@QAEXXZ
// partial score=0.985 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BFME1 GameEngine_execute.cpp and ZH GameEngine::execute are primary guides.
// Native22D290..22D7FC includes startup load, embedded catch handlers and pacing.
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/INIException.h"
extern "C" __declspec(dllimport) unsigned __stdcall timeGetTime();
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned);
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
class Profile { public: static void StartRange(const char*); static void StopRange(const char*); };
void _bfme_debugRecordCallsite(int);
struct BfmeSubobject0022CE19 { virtual ~BfmeSubobject0022CE19(); char opaque[0xDE4]; };
struct TreeHintOpaque0043671B {
 UnicodeString m_text;
 BfmeSubobject0022CE19 m_subobject;
 unsigned m_wordDEC,m_wordDF0;
 TreeHintOpaque0043671B();
 TreeHintOpaque0043671B(const TreeHintOpaque0043671B&);
 ~TreeHintOpaque0043671B();
};
class GameState {
public: bool getSaveGameInfoFromFile(UnicodeString,BfmeSubobject0022CE19*);
 int rva002DE3C1(TreeHintOpaque0043671B);
};
extern GameState *TheGameState;
class Shell { public: void rva0035BF4C(bool); };
extern Shell *TheShell;
class Mouse { public: void _bfme_setEngineVisibility(bool); };
extern Mouse *TheMouse;
class GlobalLanguage { public: void onGameEngineExit(); };
extern GlobalLanguage *TheGlobalLanguageData;
class GlobalData; extern GlobalData *TheWritableGlobalData;
struct EngineGlobalDataView {
 char gap00[0x26]; bool useFpsLimit;
 char gap27[0xABC-0x27]; AsciiString initialFile;
 char gapAC0[0xBBD-0xAC0]; bool fastMode;
 char gapBBE[0x1111-0xBBE]; bool autoExit;
};
class GameLogic; extern GameLogic *TheGameLogic;
struct EngineLogicFrameView { char pad[0x40]; unsigned frame; };
class ScriptEngine; extern ScriptEngine *TheScriptEngine;
class Rva00203B47Host { public: bool rva00203B47(); };
class View; extern View *TheTacticalView;
class EngineTacticalSlots { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
 virtual int getTimeMultiplier();
};
class NetworkInterface; extern NetworkInterface *TheNetwork;
class EngineNetworkSlots { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
 virtual int PeekFrameReady();
 virtual int getFrameHeadroom();
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
 virtual bool isPacketRouter();
 virtual void slot44();
 virtual int getNumPlayers();
};
class GameClient; extern GameClient *TheGameClient;
class EngineClientSlots { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
};
class CrashMessage { public:
 virtual void v00();virtual void v01();virtual void v02();virtual void v03();
 virtual void v04();virtual void v05();virtual void v06();virtual void v07();
 virtual void v08();virtual void v09();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual CrashMessage *setText(const char*);
 virtual void v15();virtual void v16();virtual void v17();virtual void v18();
 virtual void show(bool);
};
class Debug; extern Debug *theDebug;
class EngineDebugSlots { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
 virtual void beginReport();
 virtual void slot25();
 virtual void slot26();
 virtual CrashMessage *getCrashMessage(void*,void*,void*);
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void command(const char*);
};
struct Bfme939Helper { int get() const; };
extern Bfme939Helper *g_bfme939Helper;
class RecorderClass { public: bool isMultiplayer(); void cleanUpReplayFile(); };
class BfmeDfe6e4 { public: void rva00225492(); };
extern BfmeDfe6e4 *theBfmeDfe6e4;
class Watchdog { public: void stop(); };
extern float g_Va00DBA2F8;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
extern int SavedClientFrame;
unsigned EngineInitialFrameTime,EnginePreviousFrameTime,EngineFrameElapsedTime;
unsigned EngineSleepTimeRemaining,EngineSleepTimeTotal;
bool EngineLimitFrameRate;
extern bool TheDeepCRC,TheLiteCRC;
class GameEngine { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void update();
 void rva0022D290();
 private:
 char prefix04[8]; int m_maxFPS; bool m_quitting;
 char pad11[0x34-0x11]; int m_clientFramePeriod;
};
#define GLOBAL_DATA ((EngineGlobalDataView*)TheWritableGlobalData)
#define DEBUG_MANAGER ((EngineDebugSlots*)theDebug)
#define LOGIC_SCALE g_Va00DBA2F8
#define REPORT_CRASH(reason) do { \
 _bfme_debugRecordCallsite(1); EngineDebugSlots *manager=DEBUG_MANAGER; \
 manager->beginReport();manager=DEBUG_MANAGER; \
 CrashMessage *message=manager->getCrashMessage(0,0,0); \
 message->setText(reason)->show(true); } while(0)
void GameEngine::rva0022D290()
{
 float oldScale;
 if (!EngineInitialFrameTime) EngineInitialFrameTime=timeGetTime();
 const AsciiString &initialFile=GLOBAL_DATA->initialFile;
 if (!reinterpret_cast<const StringBase<char>*>(&initialFile)->isEmpty()) {
  AsciiString file(initialFile); file.toLower();
  if (file.endsWithNoCase(".BfME2Campaign") || file.endsWithNoCase(".BfME2Skirmish") || file.endsWithNoCase(".BfME2WotR") || file.endsWithNoCase(".BfME2WotRMP")) {
   TreeHintOpaque0043671B saved;
   saved.m_text=UnicodeString(file);
   saved.m_wordDEC=0;saved.m_wordDF0=0; bool loaded=false;
   if (TheGameState->getSaveGameInfoFromFile(saved.m_text,&saved.m_subobject)) {
    if (TheGameState->rva002DE3C1(saved)==0) {
     loaded=true;
     if(TheShell)TheShell->rva0035BF4C(true);
     if(TheMouse)TheMouse->_bfme_setEngineVisibility(true);
    }
   }
   if(GLOBAL_DATA->autoExit) {
    if(!loaded)Sleep(666);
    char text[100];
    sprintf(text,"%i0:debug.exit",((EngineLogicFrameView*)TheGameLogic)->frame+30);
    DEBUG_MANAGER->command(text);
   }
  }
 }
 while(!m_quitting) {
  try {
   Profile::StartRange(0);update();Profile::StopRange(0);
  } catch(INIException *e) {
   char *failure=e->mFailureMessage;
   if(failure) {
    _bfme_debugRecordCallsite(1);EngineDebugSlots *manager=DEBUG_MANAGER;
    manager->beginReport();manager=DEBUG_MANAGER;
    CrashMessage *message=manager->getCrashMessage(0,0,0);
    message=message->setText("\n\n");
    char *text=e->mFailureMessage;
    message->setText(text)->show(true);
   } else REPORT_CRASH("\n\nUncaught INI exception in GameEngine::update");
  } catch(...) {
   try {
    if(g_bfme939Helper && g_bfme939Helper->get()==0 && ((RecorderClass*)g_bfme939Helper)->isMultiplayer())
     ((RecorderClass*)g_bfme939Helper)->cleanUpReplayFile();
   } catch(...) {}
   REPORT_CRASH("Uncaught Exception in GameEngine::update");
  }
  EngineTacticalSlots *view=(EngineTacticalSlots*)TheTacticalView;
  EngineLimitFrameRate=false;
  if(view->getTimeMultiplier()<=1 && !((Rva00203B47Host*)TheScriptEngine)->rva00203B47())
   EngineLimitFrameRate=GLOBAL_DATA->useFpsLimit;
  if(GLOBAL_DATA->fastMode)EngineLimitFrameRate=false;
  oldScale=LOGIC_SCALE;
  EngineNetworkSlots *network=(EngineNetworkSlots*)TheNetwork;
  if(!network || TheDeepCRC || TheLiteCRC) LOGIC_SCALE=1.0f;
  else if(m_clientFramePeriod==1) {
   LOGIC_SCALE=1.0f;
   if(network->getNumPlayers()==1)LOGIC_SCALE=1.0f;
   else {
    if(((EngineNetworkSlots*)TheNetwork)->isPacketRouter()) {
     EngineLimitFrameRate=true;
     int headroom=((EngineNetworkSlots*)TheNetwork)->getFrameHeadroom();
     if(headroom>10)headroom=10;
     if(headroom<=5)goto pacing_done;
     float desired=(10.0f-(float)headroom)*0.1f+0.5f;
     _ReadWriteBarrier();
     LOGIC_SCALE=(desired+oldScale)*0.5f;
    } else {
     float desired=(float)((EngineNetworkSlots*)TheNetwork)->PeekFrameReady()*0.1f+0.7f;
     if(!(desired<1.0f))desired=1.0f;
     LOGIC_SCALE=(desired+oldScale)*0.5f;
    }
   }
  }
 pacing_done:
  if(LOGIC_SCALE!=1.0f)EngineLimitFrameRate=true;
  if((unsigned)SavedClientFrame+6>((EngineClientSlots*)TheGameClient)->getFrame())EngineLimitFrameRate=false;
  if(EngineLimitFrameRate) {
   unsigned now=timeGetTime();
   int limit=(int)(1000.0f/((double)m_maxFPS*LOGIC_SCALE));
   unsigned elapsed=now-EnginePreviousFrameTime;
   unsigned remaining=((unsigned)limit-elapsed) & ((unsigned)(elapsed>=(unsigned)limit)-1);
   EngineFrameElapsedTime=elapsed;EngineSleepTimeTotal+=remaining;EngineSleepTimeRemaining=remaining;
   if(elapsed<(unsigned)limit) {
    do {Sleep(0);now=timeGetTime();} while(now-EnginePreviousFrameTime<(unsigned)limit);
   }
   EnginePreviousFrameTime=now;
  } else {
   unsigned now=timeGetTime();EngineFrameElapsedTime=now-EnginePreviousFrameTime;
   EngineSleepTimeRemaining=0;EnginePreviousFrameTime=now;
  }
  if(theBfmeDfe6e4)theBfmeDfe6e4->rva00225492();
 }
 if(theBfmeDfe6e4)((Watchdog*)theBfmeDfe6e4)->stop();
 if(TheGlobalLanguageData)TheGlobalLanguageData->onGameEngineExit();
}
