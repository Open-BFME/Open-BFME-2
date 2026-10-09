// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
#include "Common/BfmeAudioEventPrefix136.h"
class AudioEventInfo { public: char before49[0x49]; unsigned char flags49; char after4A[0x66]; int kindB0; };
class AudioEventInfoRef { public: AudioEventInfoRef(const AudioEventInfo*); const AudioEventInfo *info; };
struct NonNullAudioRef {
 AudioEventInfoRef value;
 __forceinline NonNullAudioRef(const AudioEventInfo*p):value(p){}
 __forceinline ~NonNullAudioRef(){ ((OpaqueRefCounted*)value.info)->Release_Ref(); }
};
struct ScopedMusicRef {
 OpaqueRefElement4 value;
 __forceinline ScopedMusicRef(){value.referent=0;}
 __forceinline ~ScopedMusicRef(){if(value.referent)value.referent->Release_Ref();}
};
class Rva000411084 { public: void *next(); void *current,*owner; Rva000411084(){}; Rva000411084(const Rva000411084&x):current(x.current),owner(x.owner){} };
class Rva000427195 { public: void *first(Rva000411084*); };
struct AudioEventNode { void *next; AsciiString key; const AudioEventInfo* info; };
class AudioEventRTS { public: void rva002D9ADC(); AsciiString getFilename(); };
class FileSystem { public: bool doesFileExist(const char*)const; };extern FileSystem*TheFileSystem;
class AudioManager { public: virtual bool isMusicAlreadyLoaded()const; private: char prefix[0xb8]; mutable Rva000427195 table; };
bool AudioManager::isMusicAlreadyLoaded()const {
 ScopedMusicRef music;
 Rva000411084 it;
 { Rva000411084 first; table.first(&first); it=first; }
 for(;;) {
  if(!it.current)break;
  const AudioEventInfo *p=((AudioEventNode*)it.current)->info;
  if(p) {
   NonNullAudioRef ref(p);
   const AudioEventInfo *info=ref.value.info;
   if(info->kindB0==0 && !(info->flags49&6))
    music.value=*(const OpaqueRefElement4*)&ref.value;
  }
  it.next();
  if(music.value.referent)break;
 }
 if(!music.value.referent)return true;
 BfmeAudioEventPrefix136 aud(music.value,2);
 ((AudioEventRTS*)&aud)->rva002D9ADC();
 AsciiString name=((AudioEventRTS*)&aud)->getFilename();
 return TheFileSystem->doesFileExist(name.str());
}
