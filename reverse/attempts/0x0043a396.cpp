// ??1AptLoadScreen@@UAE@XZ
// partial score=1.0 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Private whole466B trial only. Target native83A396..83A568 and WB129F700
// independently establish AptLoadScreen destruction and its exact strings.
// BF1 verified575 AptLoadScreen.cpp supplies the related constructor purpose;
// its constructor-only TU produced no placements under BF2 settings.
// Final admission would require reconciling the existing screen/preview views.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva00355D66 {
public:
 virtual ~Rva00355D66();
protected:
 void *next; void *window; bool flag;
};
class Rva0057E3DB {
public:
 virtual ~Rva0057E3DB();
private:
 unsigned char unknown04[0x6c];
};
class AptMapPreview { public: void rva0057D5E5(); };
class Rva0043A396Layout {
public:
 virtual void slot00();
 virtual ~Rva0043A396Layout();
 virtual void slot08();
 virtual void shutdown(bool);
};
class Rva002244CA { public: int rva002244CA(const AsciiString *); };
class Rva00223A94 { public: int rva00223A94(const AsciiString *); };
class Rva00222A8BTarget { public: void rva00222F55(bool); };
template<int N> struct LoadSlotTag;
template<int N> class LoadSlots : public LoadSlots<N-1> {
public: virtual void gap(LoadSlotTag<N> *);
};
template<> class LoadSlots<0> {};
class LoadPlayerView : public LoadSlots<19> {
public: virtual void show(int);
};
class LoadAudioView : public LoadSlots<35> {
public: virtual void restore(int,bool,bool);
};
class LoadTextView : public LoadSlots<15> {
public: virtual UnicodeString fetch(const char *,bool *);
};
class BfmeAptWindowManager {
public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class AudioManager;
extern AudioManager *TheAudio;
class GameTextInterface;
extern GameTextInterface *TheGameText;
class GameWindowTransitionsHandler {
public: void reverse(AsciiString);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern int g_Va00E0330C;
class GameInfo;
class AptLoadScreen : public Rva00355D66 {
public:
 virtual ~AptLoadScreen();
 virtual void update(int);
 virtual void init(GameInfo *);
 virtual void reset();
 virtual void processProgress(int,int);
private:
 Rva0043A396Layout *layout;
 void *owner;
 Rva0057E3DB preview;
 int game,level,rows[8],slots[8];
 bool unknownD0;
};
AptLoadScreen::~AptLoadScreen()
{
 layout->shutdown(false);
 ::delete layout;
 layout=0;
 reinterpret_cast<AptMapPreview *>(&preview)->rva0057D5E5();
 AsciiString colorName;
 AsciiString clipName;
 for(int i=0;i<8;++i) {
  colorName.format("GameLoading:PlayerColor:%d",i);
  reinterpret_cast<Rva002244CA *>(g_bfmeAptWindowManager)->rva002244CA(&colorName);
  clipName.format("UIClip/Level/%d",i);
  reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&clipName);
  clipName.format("UIClip/Fellowship/%d",i);
  reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&clipName);
 }
 {
  AsciiString typeName("GameLoadingType");
  reinterpret_cast<Rva002244CA *>(g_bfmeAptWindowManager)->rva002244CA(&typeName);
 }
 reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva00222F55(false);
 reinterpret_cast<LoadPlayerView *>(g_bfmeAptWindowManager)->show(1);
 reinterpret_cast<LoadAudioView *>(TheAudio)->restore(2,true,false);
 {
  AsciiString levelName("GUI:Level");
  g_bfmeAptWindowManager->bfmeSetText(levelName,
   reinterpret_cast<LoadTextView *>(TheGameText)->fetch("GUI:Level",0),false);
 }
 TheTransitionHandler->reverse(AsciiString("MainMenuToSubMenu"));
 g_Va00E0330C=0;
}
