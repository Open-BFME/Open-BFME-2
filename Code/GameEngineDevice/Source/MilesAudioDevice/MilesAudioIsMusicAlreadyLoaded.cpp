// MilesAudioManager::isMusicAlreadyLoaded, 288B. Visible noinline copies of
// AudioEventInfoRef's ctor (0x00051914) and OpaqueRefElement4::operator=
// (0x00239099), both byte-exact, make cl keep the counted info in ESI and
// release it from there, as retail. Retail jumps into a top test
// (mov eax,[ebp-0x28]; cmp eax,ebx; je exit) and re-tests music after the
// loop; cl otherwise rotates the loop to a bottom test and threads the break
// past the post-loop test. Two redundant self-compares of the iterator's
// current node in the loop condition fold away (no bytes) and give retail's
// layout.
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "Common/BfmeAudioEventPrefix136.h"
// Rowed at 0x00239099 (OpaqueRefOwnership.cpp); visible here so the unit
// knows the copy keeps no pointer to its source.
inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
    if (this != &other) {
        if (other.referent)
            InterlockedIncrement(reinterpret_cast<Long volatile *>(reinterpret_cast<char *>(other.referent) + 4));
        if (referent)
            referent->Release_Ref();
        referent = other.referent;
    }
    return *this;
}
class AudioEventInfo { public: char before49[0x49]; unsigned char flags49; char after4A[0x66]; int kindB0; };
class AudioEventInfoRef
{
public:
 // Rowed at 0x00051914 (AudioEventInfoRefConstructor.cpp); visible so the
 // unit knows the reference keeps no pointer to itself.
 __declspec(noinline) AudioEventInfoRef(const AudioEventInfo *p) : info(p)
 {
  if (info)
   InterlockedIncrement(reinterpret_cast<Long volatile *>(reinterpret_cast<char *>(const_cast<AudioEventInfo *>(info)) + 4));
 }
 const AudioEventInfo *info;
};
struct NonNullAudioRef {
 AudioEventInfoRef value;
 __forceinline NonNullAudioRef(const AudioEventInfo*audioEventInfo):value(audioEventInfo){}
 __forceinline ~NonNullAudioRef(){ ((OpaqueRefCounted*)value.info)->Release_Ref(); }
};
struct ScopedMusicRef {
 OpaqueRefElement4 value;
};
#include "../../../GameEngine/Include/GameClient/Rva000411084.h"
#include "../../../GameEngine/Include/GameLogic/Rva000427195.h"
struct AudioEventNode { void *next; AsciiString key; const AudioEventInfo* info; };
class AudioEventRTS { public: void rva002D9ADC(); AsciiString getFilename(); };
#include "../../../GameEngine/Include/Common/FileSystem.h"
extern FileSystem*TheFileSystem;
class MilesAudioManager { public: virtual bool isMusicAlreadyLoaded()const; private: char prefix[0xb8]; mutable Rva000427195 table; };
bool MilesAudioManager::isMusicAlreadyLoaded()const {
 ScopedMusicRef music;
 Rva000411084 it;
 { Rva000411084 first; table.first(&first); it=first; }
 while ((true) && it.m_current==it.m_current && it.m_current==it.m_current) {
  if(!it.m_current)break;
  const AudioEventInfo *audioEventInfo=((AudioEventNode*)it.m_current)->info;
  if(audioEventInfo) {
   NonNullAudioRef ref(audioEventInfo);
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
