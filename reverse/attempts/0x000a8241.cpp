// ?requestFile@AudioFileCache@@QAE?AVRva00690FF0Handle@@ABVBfmePoolRef10@@H@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class Rva00691110Handle {
public: Rva00691110Handle(const Rva00691110Handle&);
private: void *target;
};
class Rva00690FF0Handle {
public:
 Rva00690FF0Handle(const Rva00690FF0Handle& other) {
  ((Rva00691110Handle*)this)->Rva00691110Handle::Rva00691110Handle(*(const Rva00691110Handle*)&other);
 }
 ~Rva00690FF0Handle();
private: void *target;
};
struct AudioInfoView { char unknown[0xB0]; int type; };
struct AudioInfoReference {
 AudioInfoView *value;
 bool isNull() const { return value==0; }
 AudioInfoView *operator->() const { return value; }
};
class AudioEventRTS {
public:
 AsciiString rva002DA867();
 char prefix[8];
 AudioInfoReference info;
};
class BfmePoolRef10 { public: AudioEventRTS *event; };
class AudioFileCache {
public:
 Rva00690FF0Handle requestFile(const BfmePoolRef10&,int);
 Rva00690FF0Handle requestFile(const AsciiString&,int);
private: char unknown[0x44]; Rva00690FF0Handle emptyFile;
};
Rva00690FF0Handle AudioFileCache::requestFile(const BfmePoolRef10 &event,int priority) {
 if (!event.event) return emptyFile;
 if (event.event->info.isNull()) return emptyFile;
 if (event.event->info->type!=2) return emptyFile;
 return requestFile(event.event->rva002DA867(),priority);
}

