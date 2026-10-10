// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
#include "../../GameLogicObjectLookupView.h"
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
class GameState {
public:
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
