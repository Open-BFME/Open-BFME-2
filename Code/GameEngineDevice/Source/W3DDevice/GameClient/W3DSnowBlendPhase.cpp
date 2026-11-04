// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Retail 0x00093B5B, 360 bytes: W3DSnowManager weather blend update (WB debug body gives the
// override walk). Codegen: the from-chain temp is assigned after the barrier inside the f arm and
// the to-chain is the !f ? 0 : (next ? FO : f) ternary, which places the f==0 block between the arms.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
void W3DSnowManager::rva00093B5B() {
 const WeatherSetting *weatherSetting=TheWeatherSetting.ptr;
 const WeatherSetting *d= !weatherSetting ? 0 : (weatherSetting->getNextOverride() ? (const WeatherSetting *)const_cast<Overridable *>(weatherSetting->getNextOverride())->friend_getFinalOverride() : weatherSetting);
 const WeatherSetting *from=0, *to;
 if (!d->enabled || !phase) return;
 const Overridable *next=0;
 if (weatherSetting) { next=weatherSetting->getNextOverride(); const WeatherSetting *ft=next ? (const WeatherSetting *)const_cast<Overridable *>(next)->friend_getFinalOverride() : weatherSetting; _ReadWriteBarrier(); from=ft; }
 to = !weatherSetting ? 0 : (next ? (const WeatherSetting *)const_cast<Overridable *>(next)->friend_getFinalOverride() : weatherSetting);
 float fraction=(float)(from->duration-frames)/(float)to->duration;
 if(fraction>1.0f) { rva00093457(); }
 else if(fraction>endFraction) {
  float blend=(fraction-endFraction)/(1.0f-endFraction);
  phase=3;
  intensity=peakIntensity-(peakIntensity-initialIntensity)*blend;
  velocity=peakVelocity-(peakVelocity-initialVelocity)*blend;
 } else if(fraction>startFraction) { intensity=peakIntensity; phase=2; velocity=peakVelocity; }
 else if(fraction>0.0f) {
  phase=1;
  float blend=startFraction>1e-5f ? fraction/startFraction : 1.0f;
  intensity=initialIntensity+(peakIntensity-initialIntensity)*blend;
  velocity=initialVelocity+(peakVelocity-initialVelocity)*blend;
 } else { rva00093457(); }
}

