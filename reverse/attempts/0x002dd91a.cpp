// ?rva002DD91A@GameState@@QAEHUTreeHintOpaque0043671B@@@Z
// partial score=0.7632370244750121 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7   /arch:SSE /DNDEBUG /MD /EHsc
// Native 2DE3C1..2DE4E6 is the load-game scope wrapper. WorldBuilder's
// corresponding unnamed E6C210 body calls GameState::doLoadGame and carries
// the same GUI labels; ZH loadGame supplies the purpose only. The existing
// address-derived wrapper name and DF4-byte record owner are retained.
// Native by-value copy22D106 and cleanup229840 prove record ABI and ownership.
// FP scope construction calls verified22B provider4224C. Its native exit
// decrements TheGameLogic+1B4; the local access view states only that word.
// s_inLoadGame spelling comes from WB's doLoadGame assertion and the ZH
// static flag. Target DIR32 sites establish DFF090; image startup byte is 0.
// Dispatcher2DD91A is unrowed: first Ghidra block466B has catch continuations.
// Its actual body reaches RET DF4 at2DDC73 (860B total). This declaration
// asserts the call ABI; it does not claim a recovered implementation.
#include "unicode_string.h"
#include "../../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct BfmeSubobject0022CE19 {
 virtual ~BfmeSubobject0022CE19();
 unsigned char opaque04[0xDE4];
 BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
 UnicodeString filename;
 BfmeSubobject0022CE19 saveGameInfo;
 unsigned int next,prev;
 TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
 ~TreeHintOpaque0043671B();
};
typedef char RecordExtent[(sizeof(TreeHintOpaque0043671B)==0xDF4)?1:-1];
class Rva0004224C {
public:
 Rva0004224C *rva0004224C();
 Rva0004224C() { rva0004224C(); }
 ~Rva0004224C() {
  if(TheGameLogic) --((LogicFPScopeView*)TheGameLogic)->nesting;
 }
private: struct LogicFPScopeView { char opaque[0x1B4]; int nesting; };
};
class GameTextInterface {
public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
 virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(); virtual void v14();
 virtual UnicodeString fetch(const char*,bool* =0);
 virtual void v16();
 virtual const UnicodeString* fetchPointer(const char*,bool* =0);
};
extern GameTextInterface *TheGameText;
class GameEngine;
extern GameEngine *TheGameEngine;
class LoadGameEngineResetView {
public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
 virtual void v8(); virtual void reset();
};
void HideControlBar(bool);
class GameWindow;
GameWindow *MessageBoxOk(UnicodeString title,UnicodeString text,void (*callback)());
class BfmeDfe6e4 { public: void _M_rva00625699(); };
extern BfmeDfe6e4 *theBfmeDfe6e4;
class Rva0023D46F {
 BfmeDfe6e4 *counter;
public:
 Rva0023D46F(BfmeDfe6e4*);
 ~Rva0023D46F() { if(counter) counter->_M_rva00625699(); }
};
class Rva00248558Scope { public: Rva00248558Scope(); ~Rva00248558Scope(); };
class Rva002DCCFB { public: bool rva002DCCFB(UnicodeString); };
class Rva002DC74A { public: UnicodeString rva002DC74A(const UnicodeString&)const; };
class Rva0041B790 { public: void rva0041B603(); };
extern void *g_Va00E030D8;
class Xfer { public: virtual ~Xfer(); };
class Rva0060C5FA:public Xfer {
 char opaque04[0x1C];
public: Rva0060C5FA(void*,void*,void*);
};
struct Rva0060C3C3Stream;
class XferLoad { public: bool Open(Rva0060C3C3Stream*,int*); };
class Rva0060C45E { public: void clear(); };
class LoadFileView {
public:
 virtual void v0(); virtual void v1(); virtual void close(); virtual void v3();
 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
 virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(); virtual Rva0060C3C3Stream *getStream();
};
class File;
class FileSystem { public: File *rva00600676(const unsigned short*,int,int); };
extern FileSystem *TheFileSystem;
class AudioManager; extern AudioManager *TheAudio;
class GameLoadAudioView {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void slot14(int);
 virtual void v15();virtual void v16();virtual void slot17(int,int,int);
};
class GhostObjectManager; extern GhostObjectManager *TheGhostObjectManager;
struct GameLoadGhostView { char opaque[9]; bool saved; };
class PartitionManager; extern PartitionManager *TheShroudManager;
class GameLoadShroudView {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void slot10();
};
class AI; extern AI *TheAI;
class Rva002E713FOwner { public: void rva002E713F(); };
struct GameLoadAIView { char opaque[0x10]; Rva002E713FOwner *owner; };
class Display;extern Display *TheDisplay;
struct GameLoadDisplayView { char opaque[0x114]; bool flag; };
class VideoPlayerInterface;extern VideoPlayerInterface *TheVideoPlayer;
class GameLoadVideoView {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();
 virtual void v16();virtual void v17();virtual void v18();virtual void v19();
 virtual void v20();virtual void v21();virtual void v22();virtual void v23();
 virtual void v24();virtual void v25();virtual void v26();virtual void v27();
 virtual void slot28();
};
class LinearCampaignManager;extern LinearCampaignManager *TheLinearCampaignManager;
class Rva001EB75C { public:void rva001EB75C(); };
struct GameLoadLogicFlags { char opaque[0x6F]; bool inLoad; char opaque70[0x125-0x70]; bool suspended; };
class GameStateLoadLatch {bool previous;bool &dest;public:GameStateLoadLatch(bool &flag):dest(flag){previous=flag;dest=true;} virtual ~GameStateLoadLatch(){dest=previous;}};
enum SnapshotType {SNAPSHOT_SAVELOAD=0,SNAPSHOT_NATIVE3=3,SNAPSHOT_NATIVE4=4};
struct StreamCloseView { virtual void v0();virtual void v1();virtual void close(); };
__forceinline void streamClose(Rva0060C3C3Stream*s) {((StreamCloseView*)s)->close();}
void InitRandom(unsigned);
void Rva002DD908(void*,void*,void*);
void Rva002DC66F(void*,void*,void*);
class GameState {
 char m_opaque[0x48];
 int m_saveType;
 char m_toE18[0xE18-0x4C];
 bool m_isInLoadGame;
public:
 void xferSaveData(Xfer*,SnapshotType);
 void rva002DC52B();
 int rva002DE3C1(TreeHintOpaque0043671B);
 int rva002DD91A(TreeHintOpaque0043671B);
 static bool s_inLoadGame;
};
bool GameState::s_inLoadGame=false;
int GameState::rva002DE3C1(TreeHintOpaque0043671B info)
{
 Rva0004224C guard;
 s_inLoadGame=true;
 int result=rva002DD91A(info);
 s_inLoadGame=false;
 if(result>0 && result<=4) {
  HideControlBar(true);
  TheGameLogic->rva00376E92(false,false);
  ((LoadGameEngineResetView*)TheGameEngine)->reset();
  UnicodeString msg;
  msg.format(TheGameText->fetchPointer("GUI:ErrorLoadingGame"),info.filename.str());
  MessageBoxOk(TheGameText->fetch("GUI:Error"),msg,0);
 }
 return result;
}
int GameState::rva002DD91A(TreeHintOpaque0043671B info)
{
 if(!s_inLoadGame)return 3;
 if(!((Rva002DCCFB*)this)->rva002DCCFB(info.filename))return 2;
 int result;
 ((GameLoadLogicFlags*)TheGameLogic)->inLoad=true;
 {
 Rva0023D46F countRef(theBfmeDfe6e4);
 Rva00248558Scope scope;

 bool campaignSave=((*(int*)((char*)&info+0x28))==1 || (*(int*)((char*)&info+0x28))==0);
 if((*(int*)((char*)&info+0x28))==1 || (*(int*)((char*)&info+0x28))==4 || (*(int*)((char*)&info+0x28))==6)TheGameLogic->rva00376E92(false,false);
 ((Rva0041B790*)g_Va00E030D8)->rva0041B603();
 UnicodeString path=((const Rva002DC74A*)this)->rva002DC74A(info.filename);
 LoadFileView *file=(LoadFileView*)TheFileSystem->rva00600676(path.str(),0x41,0);
 if(file) {
  unsigned char error=0;
  Rva0060C3C3Stream *stream=file->getStream();
  { Rva0060C5FA load((void*)Rva002DD908,this,(void*)Rva002DC66F);
  unsigned version;
  if(!((XferLoad*)&load)->Open(stream,(int*)&version) || version>1) {
   streamClose(stream);
   result=4;goto done;
  }
  ((LoadGameEngineResetView*)TheGameEngine)->reset();
  ((GameLoadAudioView*)TheAudio)->slot14(2);
  ((GameLoadGhostView*)TheGhostObjectManager)->saved=true;
  { GameStateLoadLatch latch(m_isInLoadGame);
  try {
   switch((*(int*)((char*)&info+0x28))) {case 1:xferSaveData(&load,SNAPSHOT_NATIVE4);break;
   case 6:xferSaveData(&load,SNAPSHOT_NATIVE3);break;
   default:xferSaveData(&load,SNAPSHOT_SAVELOAD);}
  }catch(...) {error=1;}
  ((Rva0060C45E*)&load)->clear();
  streamClose(stream);
  ((GameLoadGhostView*)TheGhostObjectManager)->saved=false;
  try {rva002DC52B();}catch(...) {error=1;}
  ((GameLoadShroudView*)TheShroudManager)->slot10();
  ((GameLoadAIView*)TheAI)->owner->rva002E713F();
  }
  }
  if(error==1) {
   ((GameLoadDisplayView*)TheDisplay)->flag=true;
   ((GameLoadVideoView*)TheVideoPlayer)->slot28();
   TheGameLogic->rva00376E92(false,true);
   ((GameLoadDisplayView*)TheDisplay)->flag=true;
   ((GameLoadVideoView*)TheVideoPlayer)->slot28();
   result=3;goto done;
  }
  if(m_saveType==4 || m_saveType==6) {
   InitRandom(0);m_saveType=0;
   ((GameLoadLogicFlags*)TheGameLogic)->suspended=true;
  }
  ((GameLoadAudioView*)TheAudio)->slot17(0x3F,7,0);
  if(TheLinearCampaignManager && campaignSave)((Rva001EB75C*)TheLinearCampaignManager)->rva001EB75C();
  result=0;goto done;
 }
 ((GameLoadDisplayView*)TheDisplay)->flag=true;
 ((GameLoadVideoView*)TheVideoPlayer)->slot28();
 TheGameLogic->rva00376E92(false,true);
 ((GameLoadDisplayView*)TheDisplay)->flag=true;
 ((GameLoadVideoView*)TheVideoPlayer)->slot28();
 result=3;
 }
done:
 ((GameLoadLogicFlags*)TheGameLogic)->inLoad=false;
 return result;
}
