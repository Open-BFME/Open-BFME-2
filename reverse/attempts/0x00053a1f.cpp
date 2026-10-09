// ?rva00053A1F@MilesAudioManager@@QAEMPAX@Z
// partial score=0.9765818656229615 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /EHsc /MD /Op
// Native53A1F..53AFA/219B RET4; receiver listener position18..20,
// event position provider2DA1CC, global flag8 and distance fields94/98.
// BF1 f989 Rva006AE150ScaledValue establishes the same scaled-volume
// purpose; target spatial branch is an independent BFME2 extension.
#include "Common/BfmeAudioEventPrefix136.h"
#include "Coord3D.h"
struct PositionalAudioInfo {
 char at00[0x48];unsigned int m_type;
 char at4C[0x94-0x4C];float m_maxDistance;float m_minDistance;
};
struct PositionalAudioSettings {
 char at00[0x70];int m_at70;int m_at74;
};
class MilesAudioManager {
public:
 float rva00053A1F(void *event);
 char at00[0x10];
 PositionalAudioSettings *m_audioSettings;
 char at14[4];
 Coord3D m_listener;
};
float MilesAudioManager::rva00053A1F(void *input)
{
 BfmeAudioEventPrefix136 *event=static_cast<BfmeAudioEventPrefix136 *>(input);
 bool valid;
 BfmeEventPositionView pos=event->rva002DA1CC(valid);
 if(valid) {
  PositionalAudioInfo *info=*reinterpret_cast<PositionalAudioInfo **>(&event->m_pool08);
  
  Coord3D delta;
  float maximum,minimum;
  if(info->m_type&8) {
  float y=m_listener.y;float x=m_listener.x;float z=m_listener.z;z-=pos.z;y-=pos.y;x-=pos.x;delta.x=x;delta.y=y;delta.z=z;maximum=m_audioSettings->m_at70;minimum=m_audioSettings->m_at74;}
  else {
  float y=m_listener.y;float x=m_listener.x;float z=m_listener.z;z-=pos.z;y-=pos.y;x-=pos.x;delta.x=x;delta.y=y;delta.z=z;maximum=info->m_maxDistance;minimum=info->m_minDistance;}
  float distance=delta.length();
  if(distance>=minimum)return 0.0f;
  if(distance>maximum&&minimum>maximum)return(minimum-distance)/(minimum-maximum);
  return 1.0f;
 }
 return 0.0f;
}
