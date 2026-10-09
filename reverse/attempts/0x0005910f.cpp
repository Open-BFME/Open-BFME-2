// ?rva0005910F@GlobalVolumeData@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z
// partial score=0.8389113412 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native5910F..591A3 RET4. Volume receiver type established by owned
// per-view callers/1C4 stride; table indexing and set offsets from retail.
#include <set>
#include <vector>
#include "ascii_string.h"
struct AudioEventChannelVolume {int m_channel;float m_volume;};
struct AudioEventInfo {
 char at00[0xB0];
 int m_atB0;
 char atB4[4];
 _STL::vector<AudioEventChannelVolume> m_channelVolumes;
 int getVolumeSlider();
};
class AudioEventRTS {
public:
 bool isPositionalAudio() const;
 char at00[8];
 AudioEventInfo *m_info;
};
class Rva001F8437 {public:void *rva001F8437(const AsciiString &);};
class MilesAudioManager {public:class GlobalVolumeData {public:
 float rva0005910F(AudioEventRTS *event);
 char at00[0xA0];
 _STL::set<AsciiString> m_names;
 char atAC[0xC8-0xAC];
 float m_volumeTable[48];
};};
struct AmbientInfoNameView {virtual void slot0();virtual const AsciiString &slot1();};
// Native5910F..591A3 RET4. GlobalVolumeData is established by the owned
// per-view callers and the native 1C4 stride. Its +A0 name set and +C8 table
// are independently accessed here; the table bit meanings follow this body.
float MilesAudioManager::GlobalVolumeData::rva0005910F(AudioEventRTS *event)
{
 int positional=0;
 if(event->isPositionalAudio() || event->m_info->m_atB0==3)positional=1;
 int flags=0;

 if(!m_names.empty()) {
  void *end=*reinterpret_cast<void**>(&m_names);
  const AsciiString &name=reinterpret_cast<AmbientInfoNameView*>(event->m_info)->slot1();
  if(reinterpret_cast<Rva001F8437*>(&m_names)->rva001F8437(name)==end)flags=1;
 }else flags=1;
 AudioEventInfo *info=event->m_info;
 if(info->m_channelVolumes.empty())flags|=2;
 int slider=info->getVolumeSlider();
 return m_volumeTable[(slider*2+positional)*4+flags];
}
