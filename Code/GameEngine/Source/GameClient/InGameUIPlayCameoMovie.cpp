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
class Display { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40)
#undef V
 virtual VideoBuffer *createVideoBuffer(bool);
};
extern Display *TheDisplay;
class WinInstanceData { public: void setVideoBuffer(VideoBuffer*); };
class GameWindow { public: WinInstanceData *winGetInstanceData(); };
class GameWindowManager { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
#undef V
 virtual GameWindow *winGetWindowFromId(GameWindow*,int);
};
extern GameWindowManager *TheWindowManager;
enum NameKeyType { INVALID_KEY=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString&); };
extern NameKeyGenerator *TheNameKeyGenerator;
class InGameUI { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79) V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
#undef V
 virtual void playCameoMovie(const AsciiString&); // slot 90 (+0x168)
 virtual void stopCameoMovie(); // slot 91 (+0x16C)
 char pad004[0x5c8-4]; VideoBuffer *m_cameoVideoBuffer; VideoStreamInterface *m_cameoVideoStream;
};
void InGameUI::playCameoMovie(const AsciiString& movieName) {
 stopCameoMovie();
 m_cameoVideoStream=TheVideoPlayer->open(movieName,0);
 if(m_cameoVideoStream) {
  if(!m_cameoVideoStream->start(TheDisplay->createVideoBuffer(false)))stopCameoMovie();
  else {
   GameWindow *window=TheWindowManager->winGetWindowFromId(0,TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:RightHUD")));
   WinInstanceData *winData=window->winGetInstanceData();
   winData->setVideoBuffer(m_cameoVideoBuffer);
  }
 }
}
