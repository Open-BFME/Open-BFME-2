// ?rva00093B5B@W3DSnowManager@@QAEXXZ
// partial score=0.972 date=2026-10-09
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
class Overridable { public: void *vtable; const Overridable *m_nextOverride; const Overridable *getFinalOverride() const; };
class WeatherSetting : public Overridable { public: char pad08[0x6c-8]; bool enabled; char pad6d[3]; int duration; };
template<class T> struct OVERRIDE { const T *ptr; };
extern OVERRIDE<WeatherSetting> TheWeatherSetting;
class GlobalWeatherSystem { public: char pad00[0x10]; int state; };
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class Rva00093457 { public: void rva00093457(); };
class Rva00093349 { public: void rva00093349(); };
class W3DSnowManager { public:
 char pad00[0x14]; float velocity; char pad18[0x3c-0x18]; float intensity; char pad40[0x58-0x40]; int frames;
 float startFraction,endFraction,initialIntensity,peakIntensity,initialVelocity,peakVelocity; char pad74[0xa8-0x74]; int weatherState,phase;
 void rva00093B5B();
 private: void target_00094652();
};
static __forceinline const WeatherSetting *walk(const WeatherSetting *p) {
 if(p && p->m_nextOverride) return (const WeatherSetting *)p->m_nextOverride->getFinalOverride();
 return p;
}
void W3DSnowManager::rva00093B5B() {
 const WeatherSetting *f=TheWeatherSetting.ptr;
 const WeatherSetting *d= !f ? 0 : (f->m_nextOverride ? (const WeatherSetting *)f->m_nextOverride->getFinalOverride() : f);
 const WeatherSetting *from=0, *to;
 if (!d->enabled || !phase) return;
 if(f) {
  const Overridable *next=f->m_nextOverride;
  const WeatherSetting *first;
  if(next) first=(const WeatherSetting *)next->getFinalOverride(); else first=f;
  from=first;
  if(next) to=(const WeatherSetting *)next->getFinalOverride(); else to=f;
  _ReadWriteBarrier();
  goto blend_phase;
 }
 to=0;
blend_phase:
 float fraction=(float)(from->duration-frames)/(float)to->duration;
 if(fraction>1.0f) { ((Rva00093457 *)this)->rva00093457(); }
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
 } else { ((Rva00093457 *)this)->rva00093457(); }
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
  if(s==2 && weatherState!=2) { weatherState=s; ((Rva00093349 *)this)->rva00093349(); }
 }
}
