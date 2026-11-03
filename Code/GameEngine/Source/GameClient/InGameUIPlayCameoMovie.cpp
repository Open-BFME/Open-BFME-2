// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
// ZH InGameUI.cpp playCameoMovie is the semantic guide. Retail vftables
// 0x007C7A88 and 0x007FD410 slots 90/91 identify play/stopCameoMovie
// (0x0029F3D7 / 0x0029F4AB). BFME2 opens with flags 0 and starts the
// stream with Display slot 41's buffer; this differs from ZH allocation.
// Target fields: buffer +0x5C8 and stream +0x5CC. Existing globals use
// their data-ledger owner types. Retain the guarded success branch: it
// gives the native __EH_prolog frame and lifetime of the RightHUD string.
// No new pins or aliases; the 212-byte body matches in full.
#include "ascii_string.h"
class VideoBuffer;
class VideoStreamInterface { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
 virtual bool start(VideoBuffer*);
};
class VideoPlayerInterface { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
 virtual VideoStreamInterface *open(AsciiString,int);
};
extern VideoPlayerInterface *TheVideoPlayer;
#include "../../Include/GameClient/Display.h"
extern Display *TheDisplay;
class WinInstanceData { public: void setVideoBuffer(VideoBuffer*); };
class GameWindow { public: WinInstanceData *winGetInstanceData(); };
#include "../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
enum NameKeyType { INVALID_KEY=0 };
#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../Include/GameClient/InGameUI.h"
void InGameUI::playCameoMovie(const AsciiString& movieName) {
 stopCameoMovie();
 m_5CC=TheVideoPlayer->open(movieName,0);
 if(m_5CC) {
  if(!m_5CC->start(TheDisplay->createVideoBuffer(false)))stopCameoMovie();
  else {
   GameWindow *window=TheWindowManager->winGetWindowFromId(0,TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:RightHUD")));
   WinInstanceData *winData=window->winGetInstanceData();
   winData->setVideoBuffer(m_cameoVideoBuffer);
  }
 }
}
