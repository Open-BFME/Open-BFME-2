// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
#include "Common/BfmeAudioEventPrefix136.h"
class AudioEventInfo;
class AudioEventInfoRef {public:AudioEventInfoRef(const AudioEventInfo *);AudioEventInfoRef():value(0){} OpaqueRefCounted *value;};
// The owner released by the selector's caller. The local volatile reference in the destructor retains the
// two native reads around the EH-state reset at 0x00278440; it is a scheduling choice, not a claim that the
// historical member was volatile (the sibling rows keep the plain destructor in their own unit).
class Rva0036CA00Str {
public:
 AudioEventInfoRef handle;
 Rva0036CA00Str() {}
 Rva0036CA00Str(const AudioEventInfo *audioEventInfo):handle(audioEventInfo){}
 Rva0036CA00Str(const Rva0036CA00Str &) throw();
 ~Rva0036CA00Str(){OpaqueRefCounted *const volatile &value=handle.value;if(value)value->Release_Ref();}
};
#include "../../Include/GameClient/Drawable.h"
class Rva00278341Host
{
public:
 char pad100[0x100];
 DrawableID identifier;
 char pad104[0xc];
 OpaqueRefElement4 playing;
 char pad114[0x30];
 int playingHandle;
 char pad148[0x2ff];
 unsigned char flag447;
 unsigned char flag448;
 unsigned char flag449;
 unsigned char flag44A;
 unsigned char flag44B;
 void rva00278341(int selector, int permanent);
};
// Native278440..2784AF complete 111B RET4. The matched 2784AF wrapper and WB CB11D0 establish the
// receiver, selector and three flag-byte guard. Compare the selected counted owner with field 0x110 and
// restart only on change. The saved current owner preserves the native field load and memory-left comparison.
class Rva00278440Host : public Rva00278341Host
{ public: void rva00278440(int selector); };
void Rva00278440Host::rva00278440(int selector)
{
 if(flag447 && flag448 && flag44A)
 {
  Rva0036CA00Str info=reinterpret_cast<Drawable *>(this)->rva0027824D(selector);
  OpaqueRefCounted *current=playing.referent;
  if(info.handle.value!=current)rva00278341(selector,0);
 }
}
