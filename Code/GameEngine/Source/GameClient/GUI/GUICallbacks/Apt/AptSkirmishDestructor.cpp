// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 donor 34f59164f6d1efd413c5fd37f4894ec834c3c0fe:
// game/GameEngine/Source/GameClient/GUI/SkirmishScreenDestructor.cpp.
// WB AptSkirmish.cpp's complete destructor and retail 0x00521977/315B
// independently establish the teardown. Preserve the existing opaque ABI
// name used by the rowed deleting destructor at 0x00521CE3.
// Storage below is a consumed-prefix view: the primary +0..+0x217,
// secondary +0x218..+0x27B and callback +0x27C..+0x287 are separate
// vptr regions. The base destructor still receives the complete object's
// +0 receiver and consumes its own independently verified base layout.
// Member storage includes opaque gaps up to the next witnessed destructor
// receiver; it does not assert the complete member types' sizeof values.
#include "ascii_string.h"
#include "unicode_string.h"
class _bfme_AptGameWindow { public: virtual ~_bfme_AptGameWindow(); private: char storage[0x218-4]; };
class AptSkirmishSecondaryView { public: virtual void marker()=0; private: char storage[0x64-4]; };
class Rva004444D2 { public: virtual ~Rva004444D2(); private: char storage[8]; };
class Rva004421E1 { public: virtual ~Rva004421E1(); private: char storage[0x3E0-4]; };
class Rva005C1A36 { public: virtual ~Rva005C1A36(); private: char storage[0x30-4]; };
class SkirmishPreferences { public: virtual ~SkirmishPreferences(); private: char storage[0x20-4]; };
class Rva0031455E { public: virtual ~Rva0031455E(); private: char storage[0x10-4]; };
class GameInfo { public: virtual void* deleteObject(int); };
extern GameInfo *TheSkirmishGameInfo;
extern GameInfo *TheGameInfo;
extern int g_00E04930;
class AptPlayer { public: void RemoveOverButtonHandler(const AsciiString&); };
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
void _bfme_closeAptScreen(const AsciiString&);
void __cdecl operator delete(void*);
class Rva00521977 : public _bfme_AptGameWindow, public AptSkirmishSecondaryView, public Rva004444D2 {
public: virtual ~Rva00521977();
private:
 Rva004421E1 panel;
 Rva005C1A36 honors;
 SkirmishPreferences preferences;
 char gap[0x10];
 Rva0031455E profile;
 UnicodeString unusedName;
};
Rva00521977::~Rva00521977() {
 if ((void*)g_00E04930 == this) {
  GameInfo *info=TheSkirmishGameInfo;
  void *dead=info ? info->deleteObject(0) : 0;
  ::operator delete(dead);
  TheSkirmishGameInfo=0;
  TheGameInfo=0;
  if (g_bfmeAptWindowManager) {
   AsciiString name("Skirmish/tooltipPlayerLevelIcon");
   ((AptPlayer*)g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);
  }
  {
   AsciiString name("AptSkirmish::InitGadgets");
   _bfme_closeAptScreen(name);
  }
  g_00E04930=0;
 }
}
