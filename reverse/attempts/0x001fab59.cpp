// ?update@Rva001FAB59@@QAE_NH@Z
// partial score=0.9229118389841187 date=2026-10-10
// ?update@Rva001FAB59@@QAE_NH@Z
// partial score=0.8664 date=2026-10-08
// cl: /O1 /Ob2 /Oy- /MD /I. /ICode/Libraries/Include /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /arch:SSE /G7 /DNDEBUG /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct Coord3D {float x,y,z; __forceinline void set(float a,float b,float c) {x=a;y=b;z=c;} };
struct Vector3 {float X,Y,Z; __forceinline Vector3(float a,float b,float c):X(a),Y(b),Z(c){} };
struct Vector4 { float X,Y,Z,W; __forceinline Vector4 &operator=(const Vector4 &v) {X=v.X;Y=v.Y;Z=v.Z;W=v.W;return *this;} };
class Matrix3D {public: __forceinline Vector3 getTranslation() const {return Vector3(Row[0].W,Row[1].W,Row[2].W);}  Vector4 Row[3]; __forceinline void mul(const Matrix3D&,const Matrix3D&); __forceinline Matrix3D &operator=(const Matrix3D &v) {Row[0]=v.Row[0];Row[1]=v.Row[1];Row[2]=v.Row[2];return *this;} };
__forceinline float submul(const Vector4 &v,float a,float b,float c) { return v.Z*c+v.Y*b+(&v.X)[0]*a; }
__forceinline void Matrix3D::mul(const Matrix3D& A, const Matrix3D& B)
{

	//assert(this != &B);
	// nope, this is actually ok. (srj)
	//assert(this != &B);

	float tmp1,tmp2,tmp3;

	tmp1 = B.Row[0].X;
	tmp2 = B.Row[1].X;
	tmp3 = B.Row[2].X;

	this->Row[0].X = submul(A.Row[0], tmp1, tmp2, tmp3);
	this->Row[1].X = submul(A.Row[1], tmp1, tmp2, tmp3);
	this->Row[2].X = submul(A.Row[2], tmp1, tmp2, tmp3);

	tmp1 = B.Row[0].Y;
	tmp2 = B.Row[1].Y;
	tmp3 = B.Row[2].Y;

	this->Row[0].Y = submul(A.Row[0], tmp1, tmp2, tmp3);
	this->Row[1].Y = submul(A.Row[1], tmp1, tmp2, tmp3);
	this->Row[2].Y = submul(A.Row[2], tmp1, tmp2, tmp3);

	tmp1 = B.Row[0].Z;
	tmp2 = B.Row[1].Z;
	tmp3 = B.Row[2].Z;

	this->Row[0].Z = submul(A.Row[0], tmp1, tmp2, tmp3);
	this->Row[1].Z = submul(A.Row[1], tmp1, tmp2, tmp3);
	this->Row[2].Z = submul(A.Row[2], tmp1, tmp2, tmp3);

	tmp1 = B.Row[0].W;
	tmp2 = B.Row[1].W;
	tmp3 = B.Row[2].W;

	this->Row[0].W = submul(A.Row[0], tmp1, tmp2, tmp3) + A.Row[0].W;
	this->Row[1].W = submul(A.Row[1], tmp1, tmp2, tmp3) + A.Row[1].W;
	this->Row[2].W = submul(A.Row[2], tmp1, tmp2, tmp3) + A.Row[2].W;
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64*);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);
class GlobalData {public: char pad[0x9af]; bool useFX; char gap[0x12]; bool profileFX;};
extern GlobalData *TheGlobalData;
class Drawable {public: const Matrix3D *getTransformMatrix() const; int getCurrentClientBonePositions(const char*,int,Coord3D*,Matrix3D*,int) const;
 char gap[0x440]; bool shrouded,hidden;
};
class Thing {public: Drawable *getDrawable() const;};
enum CellShroudStatus {clear,fogged,shrouded,count};
enum ObjectID { INVALID_ID=0 };
class Object:public Thing {public: CellShroudStatus getShroudStatusForPlayer(int) const; char pad[8]; Matrix3D transform;};
class GameLogic {public:Object *findObjectByID(ObjectID);};
extern GameLogic *TheGameLogic;
class GameClient {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual Drawable *findDrawableByID(int);
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual unsigned getFrame();
};
extern GameClient *TheGameClient;
struct Rva001F38C1Arg { int v[12]; };
class Rva001F38C1Slot {public:void set(const Rva001F38C1Arg&);};
class Rva001F3C9A {public:bool rva001F3C9A();};
class Rva001FA7F8 {public:void rva001FA7F8();};
class ParticleSystem {public:void destroy(); void rva001F4696(void*,void*,bool,void*);};
struct ControlParticle {char pad[0x1c];Coord3D pos;};
class Rva001FAB59 {public:bool update(int);
private:
 char head[0x7c]; int priority; char gap80[0x2c]; float profileTime;
 int drawableID; ObjectID objectID; AsciiString boneName;
 Matrix3D localTransform,transform;
 unsigned burstDelayLeft,delayLeft,startTimestamp,lifetimeLeft,personality;
 char gap130[0x14]; Coord3D pos,lastPos;
 char gap15C[0x10]; void *masterSystem;
 char gap170[0x2c]; ControlParticle *control;
 bool isLocalIdentity,isIdentity,isForever,isStopped,isDestroyed,isFirstPos,flag1A6,flag1A7,skipParent;
 char gap1A9[3]; Rva001FA7F8 modules;
};
bool Rva001FAB59::update(int localPlayerIndex) {if(0){throw 0;throw 0;}

 profileTime=0.0f;
 __int64 start,frequency,end;
 if(TheGlobalData->profileFX) {QueryPerformanceFrequency(&frequency);QueryPerformanceCounter(&start);}
 if(!TheGlobalData->useFX) return false;
 if(delayLeft) { if(--delayLeft==0) startTimestamp=TheGameClient->getFrame();return true;}
 bool hidden=false,shrouded=false;
 if(!masterSystem) {
  const Matrix3D *parent=0;
  if(drawableID) {
   Drawable *attached=TheGameClient->findDrawableByID(drawableID);
   if(attached) {
    if(!attached->hidden) hidden=true;
    if(attached->shrouded) shrouded=true;
    parent=attached->getTransformMatrix();
    lastPos=pos;pos.set(parent->Row[0].W,parent->Row[1].W,parent->Row[2].W);
    if(!boneName.isEmpty()) { Matrix3D bone; if(attached->getCurrentClientBonePositions(boneName.str(),0,0,&bone,1)) ((Rva001F38C1Slot*)this)->set((const Rva001F38C1Arg&)bone); }
   } else {drawableID=0;((ParticleSystem*)this)->destroy();}
  } else if(objectID) {
   Object *attached=TheGameLogic->findObjectByID(objectID);
   if(attached) {
    shrouded=attached->getShroudStatusForPlayer(localPlayerIndex)>=3;
    Drawable *draw=attached->getDrawable();
    if(draw) {
     if(!draw->hidden) hidden=true;
     parent=draw->getTransformMatrix();
     if(!boneName.isEmpty()) { Matrix3D bone; if(draw->getCurrentClientBonePositions(boneName.str(),0,0,&bone,1)) ((Rva001F38C1Slot*)this)->set((const Rva001F38C1Arg&)bone); }
    } else parent=&attached->transform;
    lastPos=pos;pos.set(parent->Row[0].W,parent->Row[1].W,parent->Row[2].W);
   } else {objectID=INVALID_ID;((ParticleSystem*)this)->destroy();}
  }
  if(parent) {
   if(skipParent) transform=localTransform;
   else if(!isLocalIdentity) transform.mul(*parent,localTransform);
   else transform=*parent;
   isIdentity=false;
  } else if(!isLocalIdentity) {transform=localTransform;isIdentity=false;} else isIdentity=true;
  if(control) {
   const Coord3D *p=&control->pos;
   transform.Row[0].W=p->x;transform.Row[1].W=p->y;transform.Row[2].W=p->z;
   lastPos=pos;isIdentity=false;pos=*p;
  }
  if(!isDestroyed && (isForever || (!isForever && lifetimeLeft>0)) && !shrouded && !isStopped && !hidden)
   ((ParticleSystem*)this)->rva001F4696(&pos,(void*)priority,isIdentity,&transform);
 }
 modules.rva001FA7F8();
 bool result=((Rva001F3C9A*)this)->rva001F3C9A();
 if(TheGlobalData->profileFX) {QueryPerformanceCounter(&end);profileTime=(float)((end-start)*1000.0f/frequency);}
 return result;
}
