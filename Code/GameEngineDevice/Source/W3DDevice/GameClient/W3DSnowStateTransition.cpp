// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native94652..9470F189B, reached by rowed W3DSnowManager update949D9.
// BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d semantic guide:
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnowManagerExtraAfterFmod.cpp.
// Original target method name remains unknown. The target observes weather
// enabled6C/duration70 and receiver frames58/endFraction60/stateA8/phaseAC.
// Neutral rva00093B5B is the complete360B RET0/tail93457 body, with this
// in ECX at both calls and receiver accesses. BFME1 transitionTBA supports
// its purpose; the10B CFG near miss is banked separately and not counted.
// Existing reset93349, override1E35DF and named weather globals bind the rest.
#include "../../../../GameEngine/Include/Common/Overridable.h"
#include "W3DSnowResourceView.h"
class GlobalWeatherSystem { public: char pad00[0x10]; int state; };
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
static __forceinline const WeatherSetting *walk(const WeatherSetting *weatherSetting) {
 if(weatherSetting && weatherSetting->getNextOverride()) return (const WeatherSetting *)const_cast<Overridable *>(weatherSetting->getNextOverride())->friend_getFinalOverride();
 return weatherSetting;
}
void W3DSnowManager::target_00094652() {
 const WeatherSetting *ov=walk(TheWeatherSetting.m_object);
 if(!ov->m_6c) return;
 if(m_AC) {
  int s=m_AC;
  if(s==1 || s==3) --m_58;
  rva00093B5B();
  int state2=2;
  if(m_A8==state2) {
   int s=TheGlobalWeatherSystem->state;
   if(s!=state2) {
    m_AC=3; ov=walk(TheWeatherSetting.m_object);
    m_58=(int)((1.0f-(*reinterpret_cast<float *>(&m_60)))*ov->m_70); m_A8=s;
   }
  }
 } else {
  int s=TheGlobalWeatherSystem->state;
  if(s==2 && m_A8!=2) { m_A8=s; rva00093349(); }
 }
}
