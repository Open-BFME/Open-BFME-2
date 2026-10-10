// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
// Native27824D..278341 selects a counted4-byte audio reference. The ZH
// Drawable audio getters are a semantic lead; BFME selectors and fallback
// policy are reconstructed from this native body, so its name remains neutral.
// Field10C and record choice+4 are target accesses. The ABI views bind owned
// constructors51914/A8C7C/2390CB and factory274DD4, not invented callee names.
// The owned31B copy is a null-tested InterlockedIncrement and is declared
// nonthrowing by its provider; this suppresses an extra fallback EH state.
#include "Common/BfmeAudioEventPrefix136.h"
class AudioEventInfo;
class AudioEventInfoRef {public:AudioEventInfoRef(const AudioEventInfo *);AudioEventInfoRef():value(0){} OpaqueRefCounted *value;};
class Rva0036CA00Str {
public:
 AudioEventInfoRef handle;
 Rva0036CA00Str() {}
 Rva0036CA00Str(const AudioEventInfo *p):handle(p){}
 Rva0036CA00Str(const Rva0036CA00Str &) throw();
 ~Rva0036CA00Str(){if(handle.value)handle.value->Release_Ref();}
};
class Rva002390CB {
public:
 Rva002390CB(const Rva002390CB &);
 void *unknown;
 Rva0036CA00Str choice;
};
Rva0036CA00Str Rva00274DD4();
class Drawable {
public:
 char pad10c[0x10c];const AudioEventInfo *raw;
 Rva002390CB rva0027756D(int);
 Rva0036CA00Str rva0027824D(int);
};
Rva0036CA00Str Drawable::rva0027824D(int selector)
{
 if(selector!=3 && raw) {
  bool different;
  different=raw!=(const AudioEventInfo *)Rva00274DD4().handle.value;
  if(different)return Rva0036CA00Str(raw);
 } else {
  Rva002390CB first=rva0027756D(selector);
  if(first.choice.handle.value)return first.choice;
  if(selector!=0 && selector!=3){Rva002390CB fallback=rva0027756D(0);if(fallback.choice.handle.value)return fallback.choice;}
 }
 return Rva0036CA00Str();
}
