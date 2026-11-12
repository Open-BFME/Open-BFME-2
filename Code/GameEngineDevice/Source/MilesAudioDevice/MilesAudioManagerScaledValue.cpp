// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /EHsc /MD
// Native 0x00059AD0..0x00059CE4 (534B), RET8, receiver and arguments
// independently proven by callers 0x0005A9F8 and the WorldBuilder twin.
// Reference guide: BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d Rva006AE150ScaledValue::compute supplies
// the underlying base/scale/positional-limit/per-view composition. Its offsets
// and early return differ; BFME2 retail supplies every offset and added branch.
// Retail: event view +30; manager filter +678; 3 per-view records at +12C,
// stride1C4; occlusion scale +8C; microphone records settings+12C stride48.
// Info factors +9C/+A0 and event +52 remain address-derived field names.
// Canonical event prefix supplies the measured +88 extent and position ABI.
// 0x53A1F RET4 and 0x5910F RET4 are independently disassembled helper calls;
// their original names remain unknown. Their near-miss banks are not progress.
// Virtual slot107 is the independently rowed manager predicate 0x516EF,
// as in the owner TU and vftable 0x7C55B0. Other slots are declaration-only.
// Codegen: case1 before case0 shares the comparison flags at +21; the base
// float gets the dead input argument home before limit/valid reuse that space.
#include "Common/BfmeAudioEventPrefix136.h"
#include "Coord3D.h"
#include <math.h>
#include "../../../GameEngine/Include/Common/AudioEventRTSClass.h"
class Rva002DA0CF {public:double rva002DA0CF();};
class Rva002D94E4 {public:float rva002D94E4() const;};
class Rva002DA153 {public:float rva002DA153();};
class Rva001D990C {public:bool rva001D990C(int);};
struct ScaledEventInfo {char at00[0x9C];float m_at9C;float m_atA0;};
struct ScaledMic {char at00[0x30];float m_at30;float m_at34;char at38[0x10];};
struct ScaledSettings {char at00[0x12C];ScaledMic m_microphones[3];};
#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

class MilesAudioManager::GlobalVolumeData
{
public:
 float rva0005910F(AudioEventRTS *);
};
float MilesAudioManager::rva00059AD0(void *input,int apply)
{
 BfmeAudioEventPrefix136 *event=static_cast<BfmeAudioEventPrefix136 *>(input);
 float result;
 switch(event->m_int30) {
 case 1:if(m_678!=1) {result=0.0f;goto finish;}break;
 case 0:if(m_678!=0) {result=0.0f;goto finish;}break;
 }
 {
 float base=(float)reinterpret_cast<Rva002DA0CF *>(event)->rva002DA0CF();
 result=base*reinterpret_cast<Rva002D94E4 *>(event)->rva002D94E4();
 if(reinterpret_cast<AudioEventRTS *>(event)->isPositionalAudio()) {
  if(result>0.0f)result*=rva00053A1F(event);
  float limit=reinterpret_cast<Rva002DA153 *>(event)->rva002DA153();
  if(m_8C>0.0f && ((result>0.0f&&(*reinterpret_cast<ScaledEventInfo **>(&event->m_pool08))->m_at9C!=1.0f) || (limit>0.0f&&(*reinterpret_cast<ScaledEventInfo **>(&event->m_pool08))->m_atA0!=1.0f))) {
   bool valid;
   BfmeEventPositionView position=event->rva002DA1CC(valid);
   if(valid&&!rva000516EF(reinterpret_cast<Coord3D *>(&position))) {
    float distanceSquared=rva00053854(reinterpret_cast<Coord3D *>(&position));
    float scale;
    if(distanceSquared>=reinterpret_cast<ScaledSettings *>(m_audioSettings)->m_microphones[m_678].m_at34)scale=1.0f;
    else scale=sqrt(distanceSquared)/reinterpret_cast<ScaledSettings *>(m_audioSettings)->m_microphones[m_678].m_at30;
    ScaledEventInfo *info=*reinterpret_cast<ScaledEventInfo **>(&event->m_pool08);
    result*=1.0-scale*m_8C*(1.0-info->m_at9C);
    limit*=1.0-scale*m_8C*(1.0-info->m_atA0);
   }
  }
  if(limit>result)result=limit;
 }
 }
 if(apply)result*=reinterpret_cast<GlobalVolumeData *>(m_12C + event->m_int30 * 0x1C4)->rva0005910F(reinterpret_cast<AudioEventRTS *>(event));
 finish:
 if(event->m_b52&&result<0.01f) {
  Rva001D990C *info=*reinterpret_cast<Rva001D990C **>(&event->m_pool08);
  if(info&&!info->rva001D990C(2))result=0.01f;
 }
 return result;
}
