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
class AudioEventRTS {public:bool isPositionalAudio() const;};
class Rva002DA0CF {public:double rva002DA0CF();};
class Rva002D94E4 {public:float rva002D94E4() const;};
class Rva002DA153 {public:float rva002DA153();};
class Rva001D990C {public:bool rva001D990C(int);};
struct ScaledEventInfo {char at00[0x9C];float m_at9C;float m_atA0;};
struct ScaledMic {char at00[0x30];float m_at30;float m_at34;char at38[0x10];};
struct ScaledSettings {char at00[0x12C];ScaledMic m_microphones[3];};
class MilesAudioManager {
public:
 virtual ~MilesAudioManager();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual bool rva000516EF(const Coord3D *);
 float rva00059AD0(void *input,int apply);
 float rva00053A1F(void *input);
 float rva00053854(const Coord3D *);
 class GlobalVolumeData {public:float rva0005910F(AudioEventRTS *);};
 char at04[0x10-4];ScaledSettings *m_settings;
 char at14[0x8C-0x14];float m_at8C;
 char at90[0x12C-0x90];char m_volumes[3][0x1C4];int m_at678;
};
float MilesAudioManager::rva00059AD0(void *input,int apply)
{
 BfmeAudioEventPrefix136 *event=static_cast<BfmeAudioEventPrefix136 *>(input);
 float result;
 switch(event->m_int30) {
 case 1:if(m_at678!=1) {result=0.0f;goto finish;}break;
 case 0:if(m_at678!=0) {result=0.0f;goto finish;}break;
 }
 {
 float base=(float)reinterpret_cast<Rva002DA0CF *>(event)->rva002DA0CF();
 result=base*reinterpret_cast<Rva002D94E4 *>(event)->rva002D94E4();
 if(reinterpret_cast<AudioEventRTS *>(event)->isPositionalAudio()) {
  if(result>0.0f)result*=rva00053A1F(event);
  float limit=reinterpret_cast<Rva002DA153 *>(event)->rva002DA153();
  if(m_at8C>0.0f && ((result>0.0f&&(*reinterpret_cast<ScaledEventInfo **>(&event->m_pool08))->m_at9C!=1.0f) || (limit>0.0f&&(*reinterpret_cast<ScaledEventInfo **>(&event->m_pool08))->m_atA0!=1.0f))) {
   bool valid;
   BfmeEventPositionView position=event->rva002DA1CC(valid);
   if(valid&&!rva000516EF(reinterpret_cast<Coord3D *>(&position))) {
    float distanceSquared=rva00053854(reinterpret_cast<Coord3D *>(&position));
    float scale;
    if(distanceSquared>=m_settings->m_microphones[m_at678].m_at34)scale=1.0f;
    else scale=sqrt(distanceSquared)/m_settings->m_microphones[m_at678].m_at30;
    ScaledEventInfo *info=*reinterpret_cast<ScaledEventInfo **>(&event->m_pool08);
    result*=1.0-scale*m_at8C*(1.0-info->m_at9C);
    limit*=1.0-scale*m_at8C*(1.0-info->m_atA0);
   }
  }
  if(limit>result)result=limit;
 }
 }
 if(apply)result*=reinterpret_cast<GlobalVolumeData *>(m_volumes[event->m_int30])->rva0005910F(reinterpret_cast<AudioEventRTS *>(event));
 finish:
 if(event->m_b52&&result<0.01f) {
  Rva001D990C *info=*reinterpret_cast<Rva001D990C **>(&event->m_pool08);
  if(info&&!info->rva001D990C(2))result=0.01f;
 }
 return result;
}
