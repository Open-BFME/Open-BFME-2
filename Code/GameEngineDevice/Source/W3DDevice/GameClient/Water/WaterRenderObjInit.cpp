// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// BF1 2f243e26d WaterRenderObjInit.cpp supplies setup order and purpose.
// BFME2 removes the old light/material/caustic/sky mesh branches; native
// 7FC38..7FD57 still initializes four settings and the track system.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct WaterDeviceScope {
 WaterDeviceScope() { BFME_DX8_Thread_Lock(); }
 ~WaterDeviceScope() { BFME_DX8_Thread_Assert(); }
};
class ShaderClass {
public:
 static ShaderClass _PresetAlphaShader;
 unsigned int bits;
 void disableCull() { bits &= 0xffefffff; }
};
enum TimeOfDay { TOD_0, TOD_1, TOD_2, TOD_3, TOD_4 };
enum WaterType { WATER_TYPE_0, WATER_TYPE_1, WATER_TYPE_2 };
class WaterRenderObjClass {
public:
 struct Setting;
protected:
 void loadSetting(Setting *, TimeOfDay);
};
template<class Base,int N> class WaterInitSlots : public WaterInitSlots<Base,N-1> {
public: virtual void gap(Base *,char (*)[N]);
};
template<class Base> class WaterInitSlots<Base,0> : public Base {};
class WaterInitHead {};
class WaterInitSort : public WaterInitSlots<WaterInitHead,95> {
public: virtual void Set_Sort_Level(int);
};
class WaterInitRenderView : public WaterInitSlots<WaterInitSort,9> {
public: virtual void Set_Force_Visible(int);
};
class Rva00066A9ASub { public: void headB(); };
class WaterTracksRenderSystem {
public:
 WaterTracksRenderSystem();
 void init();
 char bytes[0x2c];
};
class SceneClass;
class Rva0007FC38 {
public:
 int rva0007FC38(float waterLevel,float dx,float dy,SceneClass *parentScene,WaterType type);
 char unknown00[0xd4];
 SceneClass *parentScene;
 ShaderClass shader;
 float scrollU,scrollV,incrementU,incrementV;
 unsigned long lastTime;
 char unknownF0[4];
 WaterType type;
 char unknownF8[8];
 WaterTracksRenderSystem *tracks;
 char unknown104[0x168-0x104];
 char settings[4][0x30];
};
int Rva0007FC38::rva0007FC38(float,float,float,SceneClass *scene,WaterType waterType) {
 WaterDeviceScope lock;
 lastTime=timeGetTime();
 parentScene=scene;
 type=waterType;
 incrementU=0.001f;
 incrementV=0.001f;
 scrollU=0;
 scrollV=0;
 // loadSetting is an established native WaterRenderObjClass member.
 struct SettingsDispatch : public WaterRenderObjClass { using WaterRenderObjClass::loadSetting; };
 SettingsDispatch *water=reinterpret_cast<SettingsDispatch *>(this);
 water->loadSetting(reinterpret_cast<WaterRenderObjClass::Setting *>(settings[0]),TOD_1);
 water->loadSetting(reinterpret_cast<WaterRenderObjClass::Setting *>(settings[1]),TOD_2);
 water->loadSetting(reinterpret_cast<WaterRenderObjClass::Setting *>(settings[2]),TOD_3);
 water->loadSetting(reinterpret_cast<WaterRenderObjClass::Setting *>(settings[3]),TOD_4);
 WaterInitRenderView *render=reinterpret_cast<WaterInitRenderView *>((char *)this+4);
 render->Set_Sort_Level(2);
 render->Set_Force_Visible(1);
 reinterpret_cast<Rva00066A9ASub *>(this)->headB();
 shader=ShaderClass::_PresetAlphaShader;
 shader.disableCull();
 tracks=new WaterTracksRenderSystem;
 tracks->init();
 return 0;
}
