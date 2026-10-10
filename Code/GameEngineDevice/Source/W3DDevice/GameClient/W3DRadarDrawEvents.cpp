// ?rva0004E5A2@W3DRadar@@QAEXHHHHH@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "Common/BfmeAudioEventPrefix136.h"
struct ICoord2D {int x,y;};
class RadarEventRef {public:void release();};
class RadarEventRefSlot {public:RadarEventRefSlot():ptr(0){}RadarEventRefSlot(const RadarEventRefSlot&s):ptr(s.ptr){}~RadarEventRefSlot(){if(ptr)ptr->release();}RadarEventRefSlot&operator=(const RadarEventRefSlot&);RadarEventRef*ptr;};
class RadarWindowOverrideSource {public:RadarEventRefSlot rva002D508B(const char*);};
extern RadarWindowOverrideSource*theRadarWindowOverrideSource;
class Rva002D3366 {public:void rva002D3366(float,float);};
class Rva002D5333 {public:virtual~Rva002D5333();virtual void rva002D3D2A();virtual void rva002D4AEF(float,float);virtual void rva002D4BA5();__declspec(noinline) void rva005CB265();};
struct RadarEventView {int type;unsigned char active;char pad05[0x10-5];unsigned expiry;char pad14[0x40-0x14];ICoord2D radarLoc;bool soundPlayed;char pad49[3];RadarEventRefSlot ping;};
struct RadarAudioMiscView {char pad[0x14];OpaqueRefElement4 radarEvent;};
class RadarAudioView {public:
#define V(n) virtual void pad##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24)
virtual void addAudioEvent(const BfmeAudioEventPrefix136*);
V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
#undef V
virtual RadarAudioMiscView*getMiscAudio();
};
class AudioManager;extern AudioManager*TheAudio;
class GameClient;extern GameClient*TheGameClient;
class RadarClientView{public:
#define V(n) virtual void pad##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
#undef V
virtual unsigned getFrame();};
struct RadarPingName {int type;const char*name;};
static const RadarPingName pingNames[]={{6,"PingBeacon"},{3,"PingAttack"},{1,"PingGeneric"},{0,"PingInformation"},{2,"PingUpgrade"}};
static __forceinline const char*Rva0004D835PingName(int type){for(unsigned n=0;n<5;++n)if(pingNames[n].type==type)return pingNames[n].name;return 0;}
class W3DRadar {public:void rva0004E5A2(int,int,int,int,int);protected:void radarToPixel(const ICoord2D*,ICoord2D*,int,int,int,int);public:char pad[0x2C];RadarEventView events[64];};
void W3DRadar::rva0004E5A2(int pixelX,int pixelY,int width,int height,int unused){for(int i=0;i<64;++i){RadarEventView&e=events[i];if(e.active==true&&e.type!=10){if(!e.soundPlayed&&e.type!=6){static BfmeAudioEventPrefix136 eventSound(((RadarAudioView*)TheAudio)->getMiscAudio()->radarEvent,0);((RadarAudioView*)TheAudio)->addAudioEvent(&eventSound);}int type=e.type;e.soundPlayed=true;
_ReadWriteBarrier();
if(!e.ping.ptr){const char*name=Rva0004D835PingName(type);if(name)e.ping=theRadarWindowOverrideSource->rva002D508B(name);}RadarEventRef*ping=e.ping.ptr;if(ping){ICoord2D pixel;radarToPixel(&e.radarLoc,&pixel,pixelX,pixelY,width,height);((Rva002D3366*)ping)->rva002D3366((float)pixel.x,(float)pixel.y);if(((RadarClientView*)TheGameClient)->getFrame()>e.expiry)((Rva002D5333*)e.ping.ptr)->rva005CB265();}}}}
