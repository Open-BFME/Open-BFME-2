// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
class WeatherSetting : public Overridable { public: char pad10[0x6c-0x10]; bool enabled; char pad6d[3]; int duration; };
template<class T> class OVERRIDE { public: const T *ptr; };
extern OVERRIDE<WeatherSetting> TheWeatherSetting;
class GlobalWeatherSystem { public: char pad00[0x10]; int state; };
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class W3DSnowManager { public:
 void rva00093457(); void rva00093349();
 char pad00[0x14]; float velocity; char pad18[0x3c-0x18]; float intensity; char pad40[0x58-0x40]; int frames;
 float startFraction,endFraction,initialIntensity,peakIntensity,initialVelocity,peakVelocity; char pad74[0xa8-0x74]; int weatherState,phase;
 void rva00093B5B();
 private: void target_00094652();
};
static __forceinline const WeatherSetting *walk(const WeatherSetting *weatherSetting) {
 if(weatherSetting && weatherSetting->getNextOverride()) return (const WeatherSetting *)const_cast<Overridable *>(weatherSetting->getNextOverride())->friend_getFinalOverride();
 return weatherSetting;
}
void W3DSnowManager::target_00094652() {
 const WeatherSetting *ov=walk(TheWeatherSetting.ptr);
 if(!ov->enabled) return;
 if(phase) {
  int s=phase;
  if(s==1 || s==3) --frames;
  rva00093B5B();
  int state2=2;
  if(weatherState==state2) {
   int s=TheGlobalWeatherSystem->state;
   if(s!=state2) {
    phase=3; ov=walk(TheWeatherSetting.ptr);
    frames=(int)((1.0f-endFraction)*ov->duration); weatherState=s;
   }
  }
 } else {
  int s=TheGlobalWeatherSystem->state;
  if(s==2 && weatherState!=2) { weatherState=s; rva00093349(); }
 }
}
