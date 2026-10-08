// ?init@WaterTracksObj@@QAEXMMAAVVector2@@0PADHPAX@Z
// partial score=0.985 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Clean BFME1 9cbfb551fe20 W3DWaterTracks.cpp initializer, guided by ZH.
// Native FE379..FE8FC RET28 and editor calls establish seven arguments.
// Bounds8..2C, type30, start40, init58/60, offset68 and timing6C..AC
// are target access facts. Map settings identity is unknown; its optional
// values are read through existing address-derived getter providers.
#include "vector2.h"
#include "vector3.h"
#include <math.h>
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr { public: T *m_ptr; const RefCountPtr &operator=(const RefCountPtr &); };
class BFME2ParticleTextureHandle { public: TextureBaseClass *Ptr; ~BFME2ParticleTextureHandle() { if(Ptr)Ptr->Release_Ref(); } };
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
float GetGameClientRandomValueReal(float,float,char *,int);
class Rva0030C934IntGetter { public: int get()const; };
class Rva0030C8CCIntGetter { public: int get()const; };
class Rva0030C8E6IntGetter { public: int get()const; };
class Rva0030C900IntGetter { public: int get()const; };
class RenderObjClass { public: virtual void *Get_User_Data(); };
class Drawable; class Thing { public: Drawable *getDrawable()const; };
struct waveInfo { float finalWidth,finalHeight,distance,velocity; int fadeMs; float widthFraction,heightFraction; int compressMs,secondOffset; char *textureName,*typeName; };
extern waveInfo waveTypeInfo[7];
struct InitSphere { Vector3 Center; float Radius; void Init(const Vector3 &v,float r) {Center=v;Radius=r;} };
struct InitBox { Vector3 Center,Extent; };
class WaterTracksObj {
public:
 void *vtable; RefCountPtr<TextureClass> texture;
 InitSphere sphere; InitBox box;
 int type,x,y; bool bound; Vector2 startPos,waveDir,perpDir,initStart,initEnd;
 int initOffset,fadeMs,totalMs,elapsedMs;
 float initialWidth,initialHeight,finalWidth,peakFraction,finalHeight;
 float velocity,distance,timeToBeach,frontAcc,timeToStop,timeToRetreat,backAcc,timeToCompress,flipU;
 WaterTracksObj *next,*previous;
 void init(float,float,Vector2&,Vector2&,char*,int,void*);
};
// Target FE440..FE488 evaluates cos before sin, then Y*cos + X*sin.
// Keep that arithmetic visible locally without changing the shared donor header.
static __forceinline void rotateInit(Vector2 &v,float angle)
{
 float c=WWMath::Cos(angle);float s=WWMath::Sin(angle);
 float x=v.X*c-v.Y*s;float y=v.Y*c+v.X*s;
 v.X=x;v.Y=y;
}
void WaterTracksObj::init(float width,float length,Vector2 &start,Vector2 &end,char *textureName,int timeOffset,void *settings)
{
 initStart=start;initEnd=end;initOffset=timeOffset;
 sphere.Init(Vector3(0,0,0),400);
 box.Center.Set(0,0,0);box.Extent.Set(400,400,1);
 x=2;y=2;elapsedMs=-initOffset;
 startPos=start;perpDir=waveDir=end-start;
 rotateInit(perpDir,-1.57079632679f);perpDir.Normalize();
 waveDir=perpDir;waveDir.Rotate(1.57079632679f);
 char *randomFile="C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Water\\W3DWaterTracks.cpp";
 distance=settings?reinterpret_cast<Rva0030C934IntGetter*>(settings)->get():waveTypeInfo[type].distance;
 distance*=GetGameClientRandomValueReal(0.9f,1.1f,randomFile,219);
 waveDir*=distance;startPos-=waveDir;
 velocity=settings?reinterpret_cast<Rva0030C8CCIntGetter*>(settings)->get()*0.001f:waveTypeInfo[type].velocity;
 totalMs=distance/velocity;
 fadeMs=settings?reinterpret_cast<Rva0030C8E6IntGetter*>(settings)->get():waveTypeInfo[type].fadeMs;
 fadeMs*=GetGameClientRandomValueReal(0.5f,1.1f,randomFile,228);
 initialWidth=settings?reinterpret_cast<int>(reinterpret_cast<RenderObjClass*>(settings)->RenderObjClass::Get_User_Data())*0.01f:waveTypeInfo[type].widthFraction;
 initialWidth*=GetGameClientRandomValueReal(0.5f,1.0f,randomFile,231)*length;
 initialHeight=settings?reinterpret_cast<int>(reinterpret_cast<Thing*>(settings)->getDrawable())*0.01f:waveTypeInfo[type].heightFraction;
 initialHeight*=GetGameClientRandomValueReal(0.5f,1.0f,randomFile,233)*width;
 finalWidth=length*GetGameClientRandomValueReal(0.5f,1.1f,randomFile,234);
 finalHeight=width*GetGameClientRandomValueReal(0.5f,1.1f,randomFile,235);
 timeToBeach=(distance-finalHeight)/velocity;
 frontAcc=-(velocity*velocity)/(2*finalHeight);
 timeToStop=-velocity/frontAcc;
 timeToRetreat=sqrt(fabs(2.0f*finalHeight/frontAcc));
 totalMs=timeToBeach+(timeToStop+timeToRetreat);
 backAcc=2.0f*initialHeight/(timeToStop*timeToStop);
 timeToCompress=settings?reinterpret_cast<Rva0030C900IntGetter*>(settings)->get():waveTypeInfo[type].compressMs;
 timeToCompress*=GetGameClientRandomValueReal(0.5f,1.1f,randomFile,245);
 if(type==5) {timeToRetreat=1000;totalMs=((float(fadeMs)+timeToStop)+timeToBeach)+timeToRetreat;startPos=start;fadeMs=1000;}
 texture=*reinterpret_cast<const RefCountPtr<TextureClass>*>(&BFME2LoadParticleTexture(textureName,0,0));
}
