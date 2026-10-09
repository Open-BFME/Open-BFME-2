// ?bfmeDoBLD@BfmeSinkBLD@@QAEXPAXH@Z
// partial score=1.0 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "ascii_string.h"
class Rva005C96A9 {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();
 virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void stop();
 void rva00524D01(const AsciiString &,int);
};
struct AlertInner {
 char unknown00[0x60]; unsigned char flags;
 char unknown61[0x17]; Rva005C96A9 *playback;
 char unknown7C[0xD0]; int value14C;bool hidden150;
};
class RadarWindowOverrideSource {
public:
 __declspec(noinline) bool hasOverrideWindow() const;
 void rva002D4240(bool);
private:
 char unknown00[0x10]; AlertInner *inner;
};
bool RadarWindowOverrideSource::hasOverrideWindow() const {
 return (inner->flags&7)==0;
}
class BfmeSinkBLD {
public:
 void bfmeDoBLD(void *,int);
private:
 char unknown00[0x10]; AlertInner *inner;
};
void BfmeSinkBLD::bfmeDoBLD(void *name,int value) {
 RadarWindowOverrideSource *owner=reinterpret_cast<RadarWindowOverrideSource *>(this);
 if(!owner->hasOverrideWindow())return;
 inner->hidden150=!owner->hasOverrideWindow();
 inner->value14C=value;
 if(!owner->hasOverrideWindow())owner->rva002D4240(false);
 inner->playback->stop();
 inner->playback->rva00524D01(*reinterpret_cast<const AsciiString *>(name),64);
}
