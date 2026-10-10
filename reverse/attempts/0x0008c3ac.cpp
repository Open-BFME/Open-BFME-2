// ?update@W3DView@@UAEXXZ
// partial score=0.9784136707374416 date=2026-10-10
// ?update@W3DView@@UAEXXZ
// partial score=0.8900301634 date=2026-10-09
// ?update@W3DView@@UAE_NXZ
// partial score=0.8854845531 date=2026-10-09
// ?update@W3DView@@UAEXXZ
// partial score=0.8209180045876036 date=2026-10-09
// cl: /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// BFME W3DView::update, retail 0x007446A0.
// Constructor 0x00745B10 installs SubsystemInterface table 0x01121764 at +0xFC. Slot 5 reaches this body through ILT 0x00007F31.
#include <math.h>
#include <vector>
// stlport
#include "Coord3D.h"
#include "Coord2D.h"
#include "GameLogicObjectLookupView.h"
struct CameraCoordinates:Coord3D{CameraCoordinates(){}CameraCoordinates(const Coord3D&p){x=p.x;y=p.y;z=p.z;}};
class RenderObjClass;
template<class T> class RefMultiListIterator;
class RTS3DScene { public: RefMultiListIterator<RenderObjClass>* createLightsIterator(); void destroyLightsIterator(RefMultiListIterator<RenderObjClass>*); };
class W3DDisplay { public: static RTS3DScene *m_3DScene; };
class CameraClass { public: virtual void Delete_This(); int refs; void Add_Ref(){++refs;} void Release_Ref(){if(--refs==0)Delete_This();} protected: void Update_Frustum() const; public: void *Get_Frustum() const { Update_Frustum(); return (char*)this+0x100; } };
struct Rva0008B689Element{CameraClass*pointer;Rva0008B689Element():pointer(0){}Rva0008B689Element(const Rva0008B689Element&p):pointer(p.pointer){if(pointer)pointer->Add_Ref();}~Rva0008B689Element(){if(pointer)pointer->Release_Ref();}bool isNull()const{return !pointer;}};
namespace _STL{template<>void vector<Rva0008B689Element>::push_back(const Rva0008B689Element&);}
class Rva0008B470:private _STL::_Vector_base<int,_STL::allocator<int> > {typedef _STL::_Vector_base<int,_STL::allocator<int> > Base;public:__forceinline Rva0008B470(const _STL::allocator<int>&a=_STL::allocator<int>()):Base(a){}~Rva0008B470();void push_back(const Rva0008B689Element&p){reinterpret_cast<std::vector<Rva0008B689Element>*>(this)->push_back(p);}};
Rva0008B689Element Rva000897C8(CameraClass*);
class Rva0007BB79Owner{public:Rva0008B689Element rva0007BB79();};
class Rva0007D9B5Host{public:void rva0007D9B5(int);};
class Rva0006ED29{public:void rva0006ED29(void*);};
extern Rva0007BB79Owner *TheWaterRenderObj;
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
class Object { char gap[0x38]; public: Coord3D m_position; };
class ScriptEngine;
class Rva00203B08 {public:bool rva0020424FF();};
class Rva00203ACEByteField {public:unsigned char get()const;};
extern ScriptEngine *TheScriptEngine;
class Rva0030E7D0 {public:float rva0030E67C(float,float);float*data,*finish,*end;int width,height;float scale;int state;bool ready;};
class PolygonTrigger { public: bool rva002E3A39(const Coord3D&); };
class CameraShakeSystemClass;class Rva00065E21{public:bool rva00065E21();};
extern CameraShakeSystemClass CameraShakerSystem;
extern float FollowFactor007446A0;
extern "C" float __identifier("?FollowFactor007446A0@@3MA") = -1.0f;
class WW3D { public: static unsigned int Get_Frame_Time() { return SyncTime - PreviousSyncTime; } private: static unsigned int SyncTime, PreviousSyncTime; };
// retail singleton: TerrainLogic *TheTerrainLogic (mangled ?TheTerrainLogic@@3PAVTerrainLogic@@A),
// defined in GameLogic/Map/TerrainLogic.cpp. This TU only null-tests it.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class GlobalData;extern GlobalData*TheWritableGlobalData;
class HeightTerrainView{public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual float getGroundHeight(float,float,Coord3D*normal=0);};
struct HeightGlobalView{char gap[0xdd8];float sampleSize;};
static float getHeightAroundPos(float x, float y)
{
    float center = reinterpret_cast<HeightTerrainView*>(TheTerrainLogic)->getGroundHeight(x, y);
    float lowPlus = reinterpret_cast<HeightTerrainView*>(TheTerrainLogic)->getGroundHeight(
        x - reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize, y + reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize);
    float highPlus = reinterpret_cast<HeightTerrainView*>(TheTerrainLogic)->getGroundHeight(
        x + reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize, y + reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize);
    float plus = highPlus > lowPlus ? highPlus : lowPlus;
    float lowMinus = reinterpret_cast<HeightTerrainView*>(TheTerrainLogic)->getGroundHeight(
        x - reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize, y - reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize);
    float highMinus = reinterpret_cast<HeightTerrainView*>(TheTerrainLogic)->getGroundHeight(
        x + reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize, y - reinterpret_cast<HeightGlobalView*>(TheWritableGlobalData)->sampleSize);
    float minus = highMinus > lowMinus ? highMinus : lowMinus;
    float corners = minus > plus ? minus : plus;
    return center > corners ? center : corners;
}

class Drawable;
void drawDrawable(Drawable *,void*);
class GlobalData {public:
 char prefix[0xd4];float m_partitionCellSize;
 char gapd8[0xab0-0xd8];float m_cameraAdjustSpeed;bool m_enforceMaxCameraHeight;
 char gapab5[0xb71-0xab5];bool field0c0d;
 char gapb72[0xdd4-0xb72];float field0e58;
 char gapdd8[8];float field0e64;
 char gapde4[0xea6-0xde4];bool field0ed0,field0ed1;
};
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
class BaseHeightMapRenderObjClass { public:
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual void slot0a4();
 virtual void slot0a8();
 virtual void slot0ac();
 virtual void slot0b0();
 virtual void slot0b4();
 virtual void slot0b8();
 virtual void slot0bc();
 virtual void slot0c0();
 virtual void slot0c4();
 virtual void slot0c8();
 virtual void slot0cc();
 virtual void slot0d0();
 virtual void slot0d4();
 virtual void slot0d8();
 virtual void slot0dc();
 virtual void slot0e0();
 virtual void slot0e4();
 virtual void slot0e8();
 virtual void slot0ec();
 virtual void slot0f0();
 virtual void slot0f4();
 virtual void slot0f8();
 virtual void slot0fc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11c();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12c();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13c();
 virtual void slot140();
 virtual void slot144();
 virtual void slot148();
 virtual void slot14c();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15c();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16c();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17c();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18c();
 virtual void slot190();
 virtual void slot194();
 virtual void slot198();
 virtual void slot19c();
 virtual void slot1a0();
 virtual void slot1a4();
 virtual void slot1a8();
 virtual void slot1ac();
 virtual void slot1b0();
 virtual void slot1b4();
 virtual void slot1b8();
 virtual void slot1bc();
 virtual void slot1c0();
 virtual void slot1c4();
 virtual void slot1c8();
 virtual void slot1cc();
 virtual void slot1d0();
 virtual void slot1d4();
 virtual void slot1d8();
 virtual void slot1dc();
 virtual void slot1e0();
 virtual void slot1e4();
 virtual void slot1e8();
 virtual void slot1ec();
 virtual void slot1f0();
 virtual void slot1f4();
 virtual void slot1f8();
 virtual void slot1fc();
 virtual void slot200();
 virtual void slot204();
 virtual void slot208();
 virtual void slot20c();
 virtual void slot210();
 virtual void slot214();
 virtual void updateCenter(std::vector<Rva0008B689Element >&,RefMultiListIterator<RenderObjClass>*);
 virtual void target220();
 virtual void slot220();
 virtual void slot224();
 virtual void slot228();
 virtual void slot22c(int);
 virtual void slot230();
 virtual void slot234(int);

 char gap0004[0x37d4-4];
 bool field3009; // +0x3009
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class GameClient { public: virtual void target00();virtual void target04();virtual void target08();virtual void target0c();virtual void target10();
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual BFMERopeDrawable *slot02c(int);
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054(void*,float,void (*)(Drawable*,void*),void*);

};
extern GameClient *TheGameClient;
class InGameUI { public:
 virtual void targetExtraSlot0();
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual bool isScrolling();

};
extern InGameUI *TheInGameUI;
class CameraSettings007446A0 { public:
 virtual float slot000();
 virtual float slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048(Coord3D*,int);

};
class AIData007446A0 { public:

 char gap0000[192];
 float field00bc; // +0xbc
 float field00c0; // +0xc0
};
class AI { public:

 char gap0000[24];
 AIData007446A0 * field0014; // +0x14
};
extern AI *TheAI;
class View { public: virtual void targetPrimaryExtra();
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c(int);
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual void slot0a4();
 virtual void slot0a8();
 virtual void slot0ac();
 virtual void slot0b0();
 virtual void slot0b4();
 virtual void slot0b8();
 virtual void slot0bc();
 virtual void slot0c0();
 virtual void slot0c4();
 virtual void slot0c8();
 virtual void slot0cc();
 virtual void slot0d0();
 virtual void slot0d4();
 virtual void slot0d8();
 virtual void slot0dc();
 virtual void slot0e0();
 virtual void slot0e4();
 virtual void slot0e8();
 virtual void slot0ec();
 virtual void slot0f0();
 virtual void slot0f4();
 virtual void slot0f8();
 virtual void slot0fc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11c();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12c();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13c();
 virtual void slot140();
 virtual void slot144();
 virtual void slot148();
 virtual void slot14c();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15c();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16c();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual int getCameraLock();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18c();
 virtual void slot190();
 virtual int getCameraLockDrawable();
 virtual void slot198();
 virtual void slot19c();
 virtual void slot1a0();
 virtual void slot1a4();
 virtual void slot1a8();
 virtual void slot1ac();
 virtual void slot1b0();
 virtual void slot1b4();
 virtual void slot1b8();
 virtual void slot1bc();
 virtual void slot1c0();
 virtual void slot1c4();
 virtual void slot1c8();
 virtual void slot1cc();
 virtual void slot1d0();
 virtual void slot1d4();
 virtual void slot1d8();
 virtual void slot1dc();
 virtual void slot1e0();
 virtual void slot1e4();
 virtual void slot1e8();
 virtual void slot1ec();
 virtual void slot1f0();
 virtual void slot1f4();
 virtual void slot1f8();
 virtual void slot1fc();
 virtual void slot200();
 virtual void slot204();
 virtual void slot208();
 virtual void slot20c();
 virtual void slot210();
 virtual void slot214();
 virtual void slot218();
 virtual void slot21c();
 virtual void slot220();
 virtual void slot224();
 virtual void slot228();
 virtual void slot22c(int);
 virtual void slot230();
 virtual void slot234();
 virtual void slot238();
 virtual void slot23c();
 virtual void slot240();
 virtual void slot244();
 virtual void slot248();
 virtual void zoomExtra0();virtual void zoomExtra1();virtual void zoomExtra2();virtual void zoomExtra3();virtual void zoomExtra4();virtual void zoomExtra5();virtual void zoomExtra6();virtual void zoomExtra7();
 virtual float slot24c(float);

 char gap0004[8];
 Coord3D m_pos; // +0xc
 char gap0018[36];
 float m_zoom; // +0x3c
 float m_heightAboveGround; // +0x40
 char gap0044[12];
 float m_currentHeightAboveGround; // +0x50
 float m_terrainHeightUnderCamera; // +0x54
 char gap0058[8];
 int m_lockType; // +0x60
 float m_lockDist; // +0x64
 float field0068; // +0x68
 char gap006c[9];
 bool m_okToAdjustHeight; // +0x75
 bool m_snapImmediate; // +0x76
 char gap0077[1];
 Coord2D m_guardBandBias; // +0x78
 char gap0080[28];
 float field009c; // +0x9c
 float field00a0; // +0xa0
 float field00a4; // +0xa4
 float field00a8; // +0xa8
 char gap00ac[8];
};
class SubsystemInterface { public: virtual void update(); };
class W3DView : public View, public SubsystemInterface { public:
virtual void update(); bool updateCameraMovements();
private: void setCameraTransform();
public:
 char gap0100[76];
 CameraClass * m_3DCamera; // +0x104
 char gap0108[16];
 Coord2D m_shakeOffset; // +0x118
 float m_shakeAngleCos; // +0x120
 float m_shakeAngleSin; // +0x124
 float m_shakeIntensity; // +0x128
 char gap012c[176];
 bool m_doingMoveCameraOnWaypointPath; // +0x1dc
 char gap01dd[39];
 bool field0204; // +0x204
 char gap0205[35];
 bool m_doingZoomCamera; // +0x228
 char gap0229[83];
 bool field027c; // +0x27c
 bool m_doingScriptedCameraLock; // +0x27d
 char gap027e[8406];
 int field2354; // +0x2354
 char gap2358[144];
 Coord3D m_cameraOffset; // +0x23d8
 Coord2D m_previousLookAtPosition; // +0x23e4
 Coord2D m_scrollAmount; // +0x23ec
 float m_scrollAmountCutoff; // +0x23f4
 float m_groundLevel; // +0x23f8
 char gap23fc[16];
 bool m_cameraConstraintValid; // +0x240c
 char gap240d[28];
 bool m_isCameraSlaved; // +0x2429
 char gap242a[30];
 Rva0030E7D0 field2448; // +0x2448
 char gap2465[68];
 PolygonTrigger * field24ac; // +0x24ac
 bool field24b0; // +0x24b0
 char gap24b1[7];
 CameraSettings007446A0 field24b8; // +0x24b8
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
static __forceinline void CameraMemoryBarrier(){_ReadWriteBarrier();}
inline float square(float x) { return x*x; }
inline const float &minimum(const float &a,const float &b) { return a<b?a:b; }
void W3DView::update()
{
    bool recalcCamera = TheWritableGlobalData->field0ed0;
    bool didScriptedMovement = false;
    if (TheTerrainRenderObject && TheTerrainRenderObject->field3009) {
        RefMultiListIterator<RenderObjClass>* it=W3DDisplay::m_3DScene->createLightsIterator();
        Rva0008B470 cameras;
        cameras.push_back(Rva000897C8(m_3DCamera));
        if(TheWaterRenderObj){reinterpret_cast<Rva0007D9B5Host*>(TheWaterRenderObj)->rva0007D9B5((int)m_3DCamera);Rva0008B689Element extra=TheWaterRenderObj->rva0007BB79();if(!extra.isNull())cameras.push_back(extra);}
        TheTerrainRenderObject->updateCenter(*reinterpret_cast<std::vector<Rva0008B689Element>*>(&cameras),it);
        if(it) reinterpret_cast<Rva0006ED29*>(W3DDisplay::m_3DScene)->rva0006ED29(it);
    }
    int cameraLock=getCameraLock();
    if(cameraLock==0) FollowFactor007446A0=-1.0f;
    if(cameraLock!=0) {
        field2354=0;
        slot06c(0);
        Object* cameraLockObj=TheGameLogic->findObjectByID((ObjectID)cameraLock);
        bool loseLock=false;
        if(cameraLockObj==0) loseLock=true;
        BFMERopeDrawable *drawable=TheGameClient->slot02c(getCameraLockDrawable());
        if(loseLock) {
            slot19c();
            FollowFactor007446A0=-1.0f;
        } else {
            if(0.0f>FollowFactor007446A0) FollowFactor007446A0=0.05f;
            else {
_ReadWriteBarrier();
                FollowFactor007446A0+=0.05f;
                if(1.0f<FollowFactor007446A0) FollowFactor007446A0=1.0f;
            }
            Coord3D objpos; objpos.x=cameraLockObj->m_position.x; objpos.y=cameraLockObj->m_position.y; objpos.z=cameraLockObj->m_position.z;
            if(drawable) objpos=*drawable->getPosition();
            CameraCoordinates curpos(m_pos);
            float snapThreshSqr=square((cameraLockObj?TheWritableGlobalData:TheWritableGlobalData)->m_partitionCellSize);
            float distx=curpos.x-objpos.x;
            float disty=curpos.y-objpos.y;
            float curDistSqr=disty*disty+distx*distx;
            if(m_snapImmediate) { curpos.x=objpos.x; curpos.y=objpos.y; }
            else {
                float dx=objpos.x-curpos.x;
                float dy=objpos.y-curpos.y;
                if(m_lockType==1) {
                    if(curDistSqr>=snapThreshSqr) {
                        float ratio=(1.0f-snapThreshSqr/curDistSqr)*TheWritableGlobalData->field0e64;
                        curpos.x+=dx*ratio; curpos.y+=dy*ratio;CameraMemoryBarrier();
                    } else {
                        float ratio=0.01f*m_lockDist;
                        curpos.x+=ratio*(objpos.x-curpos.x); curpos.y+=ratio*(objpos.y-curpos.y);
                    }
                } else { curpos.x+=dx*FollowFactor007446A0; curpos.y+=dy*FollowFactor007446A0; }
            }
            if(!(reinterpret_cast<Rva00203B08*>(TheScriptEngine)->rva0020424FF()) &&
                !reinterpret_cast<Rva00203ACEByteField*>(TheScriptEngine)->get() && !TheGameLogic->isGamePaused())
                m_previousLookAtPosition=*reinterpret_cast<Coord2D*>(&m_pos);
            m_pos=curpos;
            if(m_snapImmediate) m_snapImmediate=false;
            m_groundLevel=objpos.z;
            didScriptedMovement=true;
            recalcCamera=true;
        }
    }
    if(!(reinterpret_cast<Rva00203B08*>(TheScriptEngine)->rva0020424FF()) && !TheGameLogic->isGamePaused() && !TheGameLogic->getFlag125()) {
        if(updateCameraMovements()) { recalcCamera=true; didScriptedMovement=true; }
    } else {
        if(field2354 || m_doingMoveCameraOnWaypointPath || field0204 || m_doingZoomCamera || m_doingScriptedCameraLock || field027c)
            didScriptedMovement=true;
    }
    if(m_shakeIntensity>0.01f) {
        m_shakeOffset.x=m_shakeIntensity*m_shakeAngleCos;
        m_shakeOffset.y=m_shakeAngleSin*m_shakeIntensity;
        if(!TheWritableGlobalData->field0ed0 || TheWritableGlobalData->field0ed1) {
            m_shakeIntensity*=0.75f;
            m_shakeAngleCos=-m_shakeAngleCos;
            m_shakeAngleSin=-m_shakeAngleSin;
        }
        if(!getCameraLockDrawable()) recalcCamera=true;
    } else { m_shakeIntensity=0.0f; m_shakeOffset.x=0.0f; m_shakeOffset.y=0.0f; }
    if((*reinterpret_cast<Rva00065E21 **>(&CameraShakerSystem))->rva00065E21()) recalcCamera=true;
    if(field2354!=2 && field2354!=3 && field2354!=4) {
        if(!getCameraLockDrawable() && !getCameraLock()) {
            if(field2448.ready) {
                float height=field2448.rva0030E67C(m_pos.x,m_pos.y);
                if(TheInGameUI->isScrolling() && !didScriptedMovement) {
                    if(height>700.0f) height=700.0f;
                    if(height!=m_groundLevel) { m_groundLevel=height; m_cameraConstraintValid=false; }
                }
                m_terrainHeightUnderCamera=height;
            } else m_terrainHeightUnderCamera=getHeightAroundPos(m_pos.x,m_pos.y);
            m_currentHeightAboveGround=m_zoom*m_cameraOffset.z-m_terrainHeightUnderCamera;
            if(TheTerrainLogic && TheWritableGlobalData && TheInGameUI && m_okToAdjustHeight && !TheGameLogic->isGamePaused()) {
                float desiredZoom=(m_heightAboveGround+m_terrainHeightUnderCamera)/m_cameraOffset.z;
                if(didScriptedMovement || (TheGameLogic->m_110==3 && TheWritableGlobalData->field0c0d)) {
                    m_heightAboveGround=m_currentHeightAboveGround;
                    desiredZoom=m_zoom;
                }
                if(TheInGameUI->isScrolling()) {
                    if(m_scrollAmount.length()<m_scrollAmountCutoff ||
                        field24b8.slot000()>m_currentHeightAboveGround || (TheWritableGlobalData->m_enforceMaxCameraHeight && field24b8.slot004()<m_currentHeightAboveGround)) {
                        float zoomAdj=(desiredZoom-m_zoom)*TheWritableGlobalData->m_cameraAdjustSpeed;
                        if(fabs(zoomAdj)>=0.0001) { m_zoom+=zoomAdj; recalcCamera=true; }
                    }
                } else {
                    float zoomAdj=(m_zoom-desiredZoom)*TheWritableGlobalData->m_cameraAdjustSpeed;
                    float zoomAdjAbs=fabs(zoomAdj);
                    if(zoomAdjAbs>=0.0001) {
                        if(didScriptedMovement) m_zoom=desiredZoom;
                        else { m_zoom-=zoomAdj; if(!getCameraLockDrawable()) recalcCamera=true; }
                    }
                }
            }
        } else {
            BFMERopeDrawable *drawable=TheGameClient->slot02c(getCameraLockDrawable());
            const Coord3D *pos;
            if(drawable) pos=drawable->getPosition();
            else {
                Object *obj=TheGameLogic->findObjectByID((ObjectID)getCameraLock());
                if(obj){pos=&obj->m_position;_ReadWriteBarrier();}else{pos=0;_ReadWriteBarrier();}
            }
            if(pos) {
                float height=field0068>0.0f?field0068:TheWritableGlobalData->field0e58;
                m_zoom=slot24c(pos->z+height);
                recalcCamera=true;
            }
        }
    }
heightDone:
    if(field24ac && field24ac->rva002E3A39(m_pos)) {
        if(!field24b0) { field009c=TheAI->field0014->field00c0; field00a4=TheAI->field0014->field00bc; }
        field24b0=true;
    } else {
        if(field24b0) { field009c=1.0f; field00a4=1.0f; }
        field24b0=false;
    }
    if(field009c<0.0001f) field009c=0.001f;
    {
    float delta1=field009c-field00a0;
    float ratio1;
    if(fabs(delta1)<0.01f) ratio1=1.0f;
    else {
        float step=delta1*0.08f;
        if(fabs(step)<0.01f) step=step>0.0f?0.01f:-0.01f;
        ratio1=step/delta1;
        recalcCamera=true;
    }
    float delta2=field00a4-field00a8;
    float ratio2;
    if(fabs(delta2)<0.01f) ratio2=1.0f;
    else {
        float step=delta2*0.08f;
        if(fabs(step)<0.01f) step=step>0.0f?0.01f:-0.01f;
        ratio2=step/delta2;
        recalcCamera=true;
    }
    float sign2=1.0f;
    if(ratio2<0.0f) { sign2=-1.0f; ratio2=-ratio2; }
    float sign1=1.0f;
    if(ratio1<0.0f) { ratio1=-ratio1; sign1=-1.0f; }
    float ratio=minimum(ratio2,ratio1);
    field00a8+=sign2*ratio*delta2;
    field00a0+=sign1*ratio*delta1;
    }
    field24b8.slot048(&m_cameraOffset,0);
    m_cameraOffset.x=m_cameraOffset.x*field00a0;
    m_cameraOffset.y*=field00a0;
    if(recalcCamera || m_isCameraSlaved) {
        setCameraTransform();
        if(didScriptedMovement && TheTerrainRenderObject) TheTerrainRenderObject->slot22c(0);
    }
    if(WW3D::Get_Frame_Time()) {
float biasY;
float biasX;
float *biasYAddress=&biasY;
biasX=m_guardBandBias.x;
*biasYAddress=m_guardBandBias.y;
TheGameClient->slot054(m_3DCamera->Get_Frustum(),sqrt(biasX*biasX+biasY*biasY)-0.01f,drawDrawable,this);
    }
}
