// ?createFromView@TabWindowManagerView@@UAEPAVGameWindow@@PAVGadgetCreateView@@@Z
// partial score=0.94 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/GameClient/GUI
#include "ascii_string.h"
class GameFont;
class WinInstanceData;
class GameWindow {
public:
 int winSetInstanceData(WinInstanceData *);
 virtual void winSetFont(GameFont *);
};
#include "GameWindowManagerRecordView.h"
class Rva00477DF0 { public: void orderPairs(); };
class GameWindowManager {
public:
 void linkWindow(GameWindow *);
protected:
 void dumpWindow(GameWindow *);
 friend class TabWindowManagerView;
};
class CreatedWindowRecordView {
public:
#define V(n) virtual void unused##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
#undef V
 virtual bool needsManagerData();
 void *managerData;
 char pad8[0x1F8-8];
 GameWindow *next;
 char pad1FC[8];
 GameWindow *child;
};
class WindowCreationManagerView {
public:
#define V(n) virtual void unused##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
 virtual void *newManagerData();
 virtual GameWindow *allocateFromRecord(GadgetCreateView *);
 V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43)
 V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
 virtual void addToParent(GameWindow *, GameWindow *);
 V(57)
 virtual void sendSystemMsg(GameWindow *, unsigned, unsigned, unsigned);
 V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75)
 virtual GameFont *findFont(AsciiString, int, bool);
#undef V
 char pad4[8];
 GameWindow *windowList;
};
class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;
struct WindowCreationLanguageView {
 char pad[0xA4];
 AsciiString name;
 int size;
 bool bold;
};
typedef GameWindow *(__stdcall *RecordWindowFactory)(GadgetCreateView *);
void GameWindowManager::dumpWindow(GameWindow *window) {
 if (!window) return;
 for (GameWindow *child = ((CreatedWindowRecordView *)window)->child; child;
      child = ((CreatedWindowRecordView *)child)->next)
  dumpWindow(child);
}
GameWindow *TabWindowManagerView::createFromView(GadgetCreateView *view) {
 WindowCreationManagerView *manager = (WindowCreationManagerView *)this;
 GameWindow *window;
 RecordWindowFactory factory = (RecordWindowFactory)view->unknown24;
 if (factory) {
  window = factory(view);
  CreatedWindowRecordView *fields = (CreatedWindowRecordView *)window;
  if (!fields->managerData && fields->needsManagerData())
   fields->managerData = manager->newManagerData();
 } else {
  window = manager->allocateFromRecord(view);
  if (!window) {
   for (GameWindow *item = manager->windowList; item; item = ((CreatedWindowRecordView *)item)->next)
    ((GameWindowManager *)this)->dumpWindow(item);
   return 0;
  }
 }
 if (view->parent) manager->addToParent(window, view->parent);
 else ((GameWindowManager *)this)->linkWindow(window);
 if (view->instance) window->winSetInstanceData(view->instance);
 ((Rva00477DF0 *)window)->orderPairs();
 manager->sendSystemMsg(window, 1, 0, 0);
 WindowCreationLanguageView *language = (WindowCreationLanguageView *)TheGlobalLanguageData;
 if (language && !((StringBase<char> *)&language->name)->isEmpty())
  window->GameWindow::winSetFont(manager->findFont(language->name, language->size, language->bold));
 else
  window->GameWindow::winSetFont(manager->findFont(AsciiString("Times New Roman"), 14, false));
 return window;
}
