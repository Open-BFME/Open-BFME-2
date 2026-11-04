// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Retail 0x00093B5B, 360 bytes: W3DSnowManager weather blend update (WB debug body gives the
// override walk). Codegen: the from-chain temp is assigned after the barrier inside the f arm and
// the to-chain is the !f ? 0 : (next ? FO : f) ternary, which places the f==0 block between the arms.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../GameEngine/Include/Common/Overridable.h"
#include "W3DSnowResourceView.h"
class GlobalWeatherSystem { public: char pad00[0x10]; int state; };
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
static __forceinline const WeatherSetting *walk(const WeatherSetting *weatherSetting) {
 if(weatherSetting && weatherSetting->getNextOverride()) return (const WeatherSetting *)const_cast<Overridable *>(weatherSetting->getNextOverride())->friend_getFinalOverride();
 return weatherSetting;
}
void W3DSnowManager::rva00093B5B() {
 const WeatherSetting *weatherSetting=TheWeatherSetting.m_object;
 const WeatherSetting *d= !weatherSetting ? 0 : (weatherSetting->getNextOverride() ? (const WeatherSetting *)const_cast<Overridable *>(weatherSetting->getNextOverride())->friend_getFinalOverride() : weatherSetting);
 const WeatherSetting *from=0, *to;
 if (!d->m_6c || !m_AC) return;
 const Overridable *next=0;
 if (weatherSetting) { next=weatherSetting->getNextOverride(); const WeatherSetting *ft=next ? (const WeatherSetting *)const_cast<Overridable *>(next)->friend_getFinalOverride() : weatherSetting; _ReadWriteBarrier(); from=ft; }
 to = !weatherSetting ? 0 : (next ? (const WeatherSetting *)const_cast<Overridable *>(next)->friend_getFinalOverride() : weatherSetting);
 float fraction=(float)(from->m_70-m_58)/(float)to->m_70;
 if(fraction>1.0f) { rva00093457(); }
 else if(fraction>(*reinterpret_cast<float *>(&m_60))) {
  float blend=(fraction-(*reinterpret_cast<float *>(&m_60)))/(1.0f-(*reinterpret_cast<float *>(&m_60)));
  m_AC=3;
  (*reinterpret_cast<float *>(&m_3c))=(*reinterpret_cast<float *>(&m_68))-((*reinterpret_cast<float *>(&m_68))-(*reinterpret_cast<float *>(&m_64)))*blend;
  (*reinterpret_cast<float *>(&m_14))=m_70-(m_70-m_6C)*blend;
 } else if(fraction>(*reinterpret_cast<float *>(&m_5c))) { (*reinterpret_cast<float *>(&m_3c))=(*reinterpret_cast<float *>(&m_68)); m_AC=2; (*reinterpret_cast<float *>(&m_14))=m_70; }
 else if(fraction>0.0f) {
  m_AC=1;
  float blend=(*reinterpret_cast<float *>(&m_5c))>1e-5f ? fraction/(*reinterpret_cast<float *>(&m_5c)) : 1.0f;
  (*reinterpret_cast<float *>(&m_3c))=(*reinterpret_cast<float *>(&m_64))+((*reinterpret_cast<float *>(&m_68))-(*reinterpret_cast<float *>(&m_64)))*blend;
  (*reinterpret_cast<float *>(&m_14))=m_6C+(m_70-m_6C)*blend;
 } else { rva00093457(); }
}

