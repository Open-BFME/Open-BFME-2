// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /EHc-
// ZH W3DDisplay.cpp destructor is the semantic guide. Native493B DT
// 49FCB..4A1B8 changes scenes to static globals and adds camera-shake,
// asset-registry and three display-string groups. The owned base111B
// destructor and target unwind prove base and allocation-member lifetimes.
// Views claim only the fields accessed here; original allocation type unknown.
extern "C" void __cdecl free(void*);
void __cdecl Rva0012641FClear();void __cdecl Rva001296F0Destroy();
bool __cdecl shutdownRenderDevice();void __cdecl DX8_Assert();
class W3DShaderManager {public:static void shutdown();};
class CameraShakeSystemClass {public:~CameraShakeSystemClass();};
extern CameraShakeSystemClass CameraShakerSystem;
class Rva009EB960 {public:virtual ~Rva009EB960();};extern Rva009EB960 *Rva0134FAA0;
class W3DFileSystem {public:virtual ~W3DFileSystem();};extern W3DFileSystem *TheW3DFileSystem;
class DebugDisplayInterface {public:virtual ~DebugDisplayInterface();};
class Render2DClass {public:~Render2DClass();};
class DisplayString;
class DisplayStringManager {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();
 virtual void s12();virtual void s13();virtual void s14();
 virtual void freeDisplayString(DisplayString*);
};extern DisplayStringManager *TheDisplayStringManager;
class SceneClass {public:virtual void destroy();int refs;void Release_Ref(){if(--refs==0)destroy();}};
class RTS3DScene:public SceneClass{};class RTS2DScene:public SceneClass{};class RTS3DInterfaceScene:public SceneClass{};
class LightClass {public:virtual void destroy();int refs;void Release_Ref(){if(--refs==0)destroy();}};
class Rva0025C0FF {public:void rva0025C0FF();};
class BfmeStrVM0 {public:virtual ~BfmeStrVM0();char unknown04[0x28];DebugDisplayInterface *debugDisplay;char unknown30[0x114];};
struct DisplayAllocation {void *data;~DisplayAllocation(){if(data)free(data);}};
class W3DDisplay:public BfmeStrVM0 {public:virtual ~W3DDisplay();
 static RTS3DScene *m_3DScene;static RTS2DScene *m_2DScene;static RTS3DInterfaceScene *m_3DInterfaceScene;
 char unknown144[4];LightClass *lights[4];LightClass *lights2[4];Render2DClass *renderer;
 char unknown16C[0x20];DisplayString *strings16[16];char unknown1CC[4];DisplayString *strings25[25];DisplayString *strings17[17];char unknown278[0x2c];DisplayAllocation allocation;
};
W3DDisplay::~W3DDisplay(){
 delete *(CameraShakeSystemClass**)&CameraShakerSystem;*(CameraShakeSystemClass**)&CameraShakerSystem=0;
 Rva0012641FClear();
 ::delete Rva0134FAA0;Rva0134FAA0=0;
 ::delete debugDisplay;
 for(int i=0;i<16;++i)TheDisplayStringManager->freeDisplayString(strings16[i]);
 for(int j=0;j<25;++j)TheDisplayStringManager->freeDisplayString(strings25[j]);
 for(int k=0;k<17;++k)TheDisplayStringManager->freeDisplayString(strings17[k]);
 delete renderer;renderer=0;
 ((Rva0025C0FF*)this)->rva0025C0FF();
 if(m_3DScene){m_3DScene->Release_Ref();m_3DScene=0;}
 if(m_2DScene){m_2DScene->Release_Ref();m_2DScene=0;}
 if(m_3DInterfaceScene){m_3DInterfaceScene->Release_Ref();m_3DInterfaceScene=0;}
 for(int n=0;n<4;++n){if(lights[n]){lights[n]->Release_Ref();lights[n]=0;}if(lights2[n]){lights2[n]->Release_Ref();lights2[n]=0;}}
 Rva001296F0Destroy();W3DShaderManager::shutdown();shutdownRenderDevice();DX8_Assert();
 ::delete TheW3DFileSystem;TheW3DFileSystem=0;
}
