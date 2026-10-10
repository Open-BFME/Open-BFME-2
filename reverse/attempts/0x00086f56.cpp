// ?rva00086F56@Rva00086761CameraMove@@QAEXH@Z
// partial score=0.9127187610288775 date=2026-10-10
// BANK ONLY: proposed expansion of canonical Rva0008990CArrayOwner.h below.
// Merge these target-proven fields into that header before any Code admission;
// never land this copied canonical class view. Body remains nonmatching.
// BF1 575ba2b04 W3DView::moveAlongWaypointPath is the semantic guide, not
// proof of the target name. Target86F56..87452 RET4 proves offsets/accesses,
// two Ease calls, point IDs via primary slot28, settings slot18 and normAngle.
// Existing matched constructor/slots associate canonical Rva00086761CameraMove.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /ICode/GameEngine/Source /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
struct CameraBounds {struct XY {float x,y;} lo,hi;};
struct CameraSettings {virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();virtual void s0a();virtual void s0b();virtual void s0c();virtual void s0d();virtual void s0e();virtual void s0f();virtual void s10();virtual void s11();virtual void offset(struct Rva00089894Point*,int);};
#pragma once
// Target BC745C/BC74F4 and their RET4/RET24 slots establish this dispatch
// order. Owner8990C/89971 establishes two 20B owning-element arrays (255/4)
// starting at2C/1418. Cleanup4F82B reaches StringBase<char>::releaseBuffer
// at36410 from element+C. The initializer accesses through2070. These are
// observed prefixes; original names and complete sizes remain unknown.
// The destructor TU uses novtable solely to reproduce retail's absent entry
// vptr store. This does not claim a historical source annotation.
typedef float Real;

class ParabolicEase
{
public:
	void rva0030E51F(Real easeInTime, Real easeOutTime, Real duration);
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
	Real operator()(Real param) const;
private:
	Real m_in;
	Real m_out;
};

class Rva000851F3
{
public:
	Rva000851F3();
	// ?Rva000851F3::~Rva000851F3 present-unmatched
	virtual ~Rva000851F3() {}
	virtual void rva00047A69C(int) = 0;
	virtual void rva00086B2C(int, int, Real, Real, int, int) = 0;
protected:
	friend class Rva00086761CameraMove;
	int m_04;
	int m_08;
	int m_0C;
	ParabolicEase m_10;
	float m_18;
	float m_1C;
	int m_20;
	bool m_24;
	int m_28;
};


#include "ascii_string.h"
// The three-float prefix is read/stored by177B86761; original point name
// remains unknown. This trivial value preserves complete12B copies.
struct Rva00089894Point
{
 float x, y, z;
};

class Rva00089894ArrayElement
{
public:
 Rva00089894ArrayElement();
 ~Rva00089894ArrayElement();
private:
 friend class Rva00086761CameraMove;
 Rva00089894Point m_position;
 AsciiString m_0C;
 int m_10;
};

#ifndef BFME_ARRAY_OWNER_ATTRIBUTES
#define BFME_ARRAY_OWNER_ATTRIBUTES
#endif
class BFME_ARRAY_OWNER_ATTRIBUTES Rva0089971 : public Rva000851F3
{
public:
 Rva0089971();
 virtual ~Rva0089971();
 // ?Rva0089971::rva00047A69C present-unmatched
 virtual void rva00047A69C(int) {}
 virtual void rva00086B2C(int, int, Real, Real, int, int);
private:
 friend class Rva00086761CameraMove;
 Rva00089894ArrayElement m_arr255[255];
 Rva00089894ArrayElement m_arr4[4];
 float m_cameraAngles[255];
 int m_values[257];
 float m_totalDistance,m_groundStart,m_groundEnd;
 int m_filled[255];
 int m_numValues;
};

#undef BFME_ARRAY_OWNER_ATTRIBUTES

// Target primary-table slots32/39/59 and unchanged-this call88F2E->86CDA
// associate these methods. Constructor8B7CF embeds the owning prefix at280.
// The target-proven parent prefix ends2358; full size/original names unknown.
class Rva00086761CameraMove
{
public:
 void rva00086761(Rva00089894Point *pLoc);
 void rva00086F56(int milliseconds);
 void rva0008690A(int value);
 // Primary vftable BC7568 slot33, target86812/248/RET4; exact name unknown.
 void rva00086812(int value);
 // Primary vftable BC7568 slot60, target88F38/190/RET16; exact name unknown.
 void rva00088F38(float finalPitch, int milliseconds, float easeIn, float easeOut);
 void rva00088EB4(float finalValue, int milliseconds, float easeIn, float easeOut);
 void rva00086CDA();
private:
 char m_padding0000[0x0C];
 Rva00089894Point m_position;
 char m_padding0018[0x28-0x18];
 float m_angle;
 char m_padding002c[0x3c-0x2c];
 float m_3C;
 char m_padding0040[0xa0-0x40];
 float m_offsetScale;
 char m_padding00a4[0x1dc-0xa4];
 bool m_doingRotateCamera;
 char m_padding1dd[0x208-0x1DD];
 int m_208, m_20C;
 float m_210, m_214;
 char m_padding218[8];
 ParabolicEase m_220;
 unsigned char m_228;
 char m_padding229[0x280-0x229];
 Rva0089971 m_cameraPath;
 char m_padding22f4[0x2354-0x22F4];
 int m_cameraMovementMode;
 char m_padding2358[0x23d0-0x2358];
 bool m_freeze;
 char m_padding23d1[3];
 int m_timeMultiplier;
 char m_padding23d8[0x23e8-0x23d8];
 Rva00089894Point m_cameraOffset;
 char m_padding23f4[0x2408-0x23f4];
 float m_ground;
 CameraBounds m_constraints;
 char m_padding241c[0x24c8-0x241c];
 CameraSettings m_settings;
};

#include "GameClient/Rva000869CF.h"
class GlobalData;extern GlobalData *TheWritableGlobalData;
typedef Rva00089894Point CPoint;

struct CameraDispatch {virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();virtual void s0a();virtual void s0b();virtual void s0c();virtual void s0d();virtual void s0e();virtual void s0f();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s1a();virtual void s1b();virtual void arrived(int);};
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" double __cdecl fabs(double);
static inline __declspec(noinline) void normAngle(float &angle) {
 if(angle < -10*3.14159265359f) angle=0;
 if(angle > 10*3.14159265359f) angle=0;
 while(angle < -3.14159265359f) angle+=2*3.14159265359f;
 while(angle > 3.14159265359f) angle-=2*3.14159265359f;
}
__forceinline long roundFloat(float f) { long i; __asm {
 fld [f]
 fistp [i]
 } return i; }
static __forceinline float interpolate(float a,float b,float factor){return a+(b-a)*factor;}
void Rva00086761CameraMove::rva00086F56(int milliseconds) {
 m_cameraPath.m_08+=milliseconds;
 if(((unsigned char*)TheWritableGlobalData)[0x9a4]) {
  if(m_cameraPath.m_08>m_cameraPath.m_04) {reinterpret_cast<Rva000869CF*>(this)->rva000869CF();m_freeze=false;}
  return;
 }
 if(m_cameraPath.m_08>m_cameraPath.m_04) {
  m_cameraMovementMode=0;reinterpret_cast<CameraDispatch*>(this)->arrived(0);m_freeze=false;
  m_angle=m_cameraPath.m_cameraAngles[m_cameraPath.m_numValues];m_ground=m_cameraPath.m_groundEnd;
  m_settings.offset(&m_cameraOffset,0);
  m_cameraOffset.x*=m_offsetScale;m_cameraOffset.y*=m_offsetScale;
  const CPoint &finalPoint=m_cameraPath.m_arr255[m_cameraPath.m_numValues].m_position;CPoint pos;pos.x=finalPoint.x;pos.y=finalPoint.y;pos.z=0;m_position=pos;
  if(m_constraints.lo.x>pos.x)m_constraints.lo.x=(_ReadWriteBarrier(),pos.x);else if(pos.x>m_constraints.hi.x)m_constraints.hi.x=(pos.x?pos.x:pos.x);
  if(m_constraints.lo.y>pos.y)m_constraints.lo.y=(_ReadWriteBarrier(),pos.y);else if(pos.y>m_constraints.hi.y)m_constraints.hi.y=(pos.y?pos.y:pos.y);
  return;
 }
 const float invTime=1.0f/m_cameraPath.m_04;
 const float currentEase=m_cameraPath.m_10(m_cameraPath.m_08*invTime);
 const float deltaTime=currentEase-m_cameraPath.m_10((m_cameraPath.m_08-milliseconds)*invTime);
 m_cameraPath.m_18+=deltaTime*m_cameraPath.m_totalDistance;
 while(m_cameraPath.m_18-m_cameraPath.m_1C>=m_cameraPath.m_values[m_cameraPath.m_20]) {
  reinterpret_cast<CameraDispatch*>(this)->arrived(m_cameraPath.m_arr255[m_cameraPath.m_20].m_10);
  m_cameraPath.m_1C+=m_cameraPath.m_values[m_cameraPath.m_20];++m_cameraPath.m_20;
  if(m_cameraPath.m_20>=m_cameraPath.m_numValues) {m_cameraPath.m_04=0;return;}
 }
 float avgFactor=1.0f/m_cameraPath.m_28;
 float factor=(m_cameraPath.m_18-m_cameraPath.m_1C)/m_cameraPath.m_values[m_cameraPath.m_20];
 if(m_cameraPath.m_20==m_cameraPath.m_numValues-1)avgFactor=avgFactor+(1.0f-avgFactor)*factor;
 float angle1=m_cameraPath.m_cameraAngles[m_cameraPath.m_20],angle2=m_cameraPath.m_cameraAngles[m_cameraPath.m_20+1];
 if(angle2-angle1>3.14159265359f)angle1+=2*3.14159265359f;
 if(angle2-angle1< -3.14159265359f)angle1-=2*3.14159265359f;
 float angle=angle1+(angle2-angle1)*factor;normAngle(angle);
 float deltaAngle=angle-m_angle;normAngle(deltaAngle);fabs(deltaAngle);
 m_angle+=avgFactor*deltaAngle;normAngle(m_angle);
 float tm=(float)m_cameraPath.m_filled[m_cameraPath.m_20]+((float)m_cameraPath.m_filled[m_cameraPath.m_20+1]-(float)m_cameraPath.m_filled[m_cameraPath.m_20])*factor;
 m_timeMultiplier=roundFloat((float)floor(0.5f+tm));
 m_ground=interpolate(m_cameraPath.m_groundStart,m_cameraPath.m_groundEnd,currentEase);
 m_settings.offset(&m_cameraOffset,0);
 m_cameraOffset.x*=m_offsetScale;m_cameraOffset.y*=m_offsetScale;
 CPoint start,mid,end;
 int seg=(m_cameraPath.m_20?m_cameraPath.m_20:m_cameraPath.m_20);
 if(factor<0.5f) {
  start=m_cameraPath.m_arr255[seg-1].m_position;start.x+=m_cameraPath.m_arr255[seg].m_position.x;start.y+=m_cameraPath.m_arr255[seg].m_position.y;start.x/=2;start.y/=2;
  mid=m_cameraPath.m_arr255[seg].m_position;end=m_cameraPath.m_arr255[seg].m_position;end.x+=m_cameraPath.m_arr255[seg+1].m_position.x;end.y+=m_cameraPath.m_arr255[seg+1].m_position.y;end.x/=2;end.y/=2;factor+=0.5f;
 } else {
  start=m_cameraPath.m_arr255[seg].m_position;start.x+=m_cameraPath.m_arr255[seg+1].m_position.x;start.y+=m_cameraPath.m_arr255[seg+1].m_position.y;start.x/=2;start.y/=2;
  mid=m_cameraPath.m_arr255[seg+1].m_position;end=m_cameraPath.m_arr255[seg+1].m_position;end.x+=m_cameraPath.m_arr255[seg+2].m_position.x;end.y+=m_cameraPath.m_arr255[seg+2].m_position.y;end.x/=2;end.y/=2;factor-=0.5f;
 }
 CPoint result;result.z=0;
 result.x=start.x+factor*(end.x-start.x);result.y=start.y+factor*(end.y-start.y);
 result.x+=(1-factor)*factor*(mid.x-end.x+mid.x-start.x);result.y+=(1-factor)*factor*(mid.y-end.y+mid.y-start.y);
 m_position=result;
 if(m_constraints.lo.x>result.x)m_constraints.lo.x=(_ReadWriteBarrier(),result.x);else if(result.x>m_constraints.hi.x)m_constraints.hi.x=(result.x?result.x:result.x);
 if(m_constraints.lo.y>result.y)m_constraints.lo.y=(_ReadWriteBarrier(),result.y);else if(result.y>m_constraints.hi.y)m_constraints.hi.y=(result.y?result.y:result.y);
}
