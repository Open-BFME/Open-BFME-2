// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
// Native 0x00091763..0x000918BC (345B), stream vslot20 called by open918BC.
// Lead: BFME1 revision575ba2b04743f190f069805fbdc59936123c45da,
// game/GameEngine/Source/Common/Rva007E5420Vp6StreamAudio.cpp. Its purpose
// (movie audio plus _Music companion) is retained; BFME2 retail establishes
// the manager slots25/75/81, info smart-reference return, +52 event flag,
// +5C/+60 handles, and native136-byte event prefix. Labels remain views.
// Initial result and both handles are initialized before the string copy;
// returning info by value with inline Release_Ref gives the five native EH states.
#include "Common/BfmeAudioEventPrefix136.h"
class StreamAudioRef {public:OpaqueRefCounted *ptr;__forceinline ~StreamAudioRef(){if(ptr)ptr->Release_Ref();}};
class Rva00091763AudioManager {public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual int addEvent(const BfmeAudioEventPrefix136*);
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
virtual void s62();
virtual void s63();
virtual void s64();
virtual void s65();
virtual void s66();
virtual void s67();
virtual void s68();
virtual void s69();
virtual void s70();
virtual void s71();
virtual void s72();
virtual void s73();
virtual void s74();
virtual StreamAudioRef getInfo(const AsciiString&);
virtual void s76();
virtual void s77();
virtual void s78();
virtual void s79();
virtual void s80();
virtual int finish();
};
class AudioManager;extern AudioManager *TheAudio;
class Rva007E3C20Vp6Stream {public:virtual int rva00091763(const AsciiString&);private:char pad04[0x58];int audio,music;};
int Rva007E3C20Vp6Stream::rva00091763(const AsciiString &name) {
 int result=0;audio=1;music=1;
 AsciiString musicName(name);musicName.concat("_Music");
 if(TheAudio) {
  StreamAudioRef musicInfo=((Rva00091763AudioManager*)TheAudio)->getInfo(musicName);
  if(musicInfo.ptr) {
   BfmeAudioEventPrefix136 event(*(OpaqueRefElement4*)&musicInfo,2);
   event.m_b52=1;
   music=((Rva00091763AudioManager*)TheAudio)->addEvent(&event);
   result=-((Rva00091763AudioManager*)TheAudio)->finish();
  }
  StreamAudioRef audioInfo=((Rva00091763AudioManager*)TheAudio)->getInfo(name);
  if(audioInfo.ptr) {
   BfmeAudioEventPrefix136 event(*(OpaqueRefElement4*)&audioInfo,2);
   event.m_b52=1;
   audio=((Rva00091763AudioManager*)TheAudio)->addEvent(&event);
   result=-((Rva00091763AudioManager*)TheAudio)->finish();
  }
 }
 return result;
}
