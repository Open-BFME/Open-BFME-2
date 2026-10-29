// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva0028F326@Rva0028F326Owner@@QAEEIM@Z, retail 0x0028F326..0x0028F44C,
// 294 bytes, RET8; complete WB 0x00CE75F0 twin (unnamed there). A vision
// test of the receiver (position +0x38, radius +0xB8, facing angle +0x1C0,
// template vision angle +0x53C) against the target word: a negative range
// means the receiver's vision range; the rowed seven-argument ellipse test
// 0x004DF8D8 gates on the combined radii; a vision angle of 360 or more
// passes; otherwise the normalized planar delta (WB MathCoord3D.h:
// copy-constructed delta, operator-= 0x41F630, Normalize 0x5A70) is dotted
// with (Cos(angle), Sin(angle), 0) and compared with Cos(visionAngle/2).
//
// The dot product's terms are parenthesized, (x*r.x)+(y*r.y)+(z*r.z) (WB
// 0x41FB90). Each parenthesized floating-point term is a paren node in c2's
// IL, which lengthens the dot chain, so the scheduler issues the first dot
// fmul ahead of the visionAngle load as retail does (traced in c2 3077 with
// SchSelectInstrs picks, 2026-10-20). The unparenthesized sum schedules the
// load first.
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
#include "Coord3DBase.h"
#include <math.h>
__declspec(noinline) inline float Coord3D::length() const { return (float)sqrt(x * x + y * y + z * z); }
__declspec(noinline) inline float Coord3D::GetLength() const
{
	float x_value = x;
	float y_value = y;
	float z_value = z;
	return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}
__declspec(noinline) inline float Coord3D::Normalize()
{
	float len = GetLength();
	float scale = 1.0f / len;
	x *= scale;
	y *= scale;
	z *= scale;
	return len;
}

inline float Coord3D::operator*(const Coord3DBase &r) const { return (x*r.x)+(y*r.y)+(z*r.z); }
struct Vec2 {float x,y;};
extern bool Rva004DF8D8Test(const Vec2*,const Vec2*,const Vec2*,float,float,float,float);
extern float Cos(float),Sin(float);
#include "../../Common/Thing/thing.h"
class Object {public:float getVisionRange()const;};
struct RangeTemplate {char pad[0x53C];float visionAngle;};
struct FacingVector {float x,y,z;FacingVector():x(0),y(0),z(0){}
 float dot(const Coord3D&a)const{return a.x*x+a.y*y+a.z*z;}};
class Rva0028F326Owner {public:unsigned char rva0028F326(unsigned,float);
 char pad00[4];const RangeTemplate*data;char pad08[0x38-8];Coord3D position;char pad44[0xB8-0x44];float radius;char padBC[0x1C0-0xBC];float angle;};
unsigned char Rva0028F326Owner::rva0028F326(unsigned targetWord,float range)
{
 const RangeTemplate*type=data;
 if(range<0.0f)range=((const Object*)this)->getVisionRange();
 const Rva0028F326Owner*target=(const Rva0028F326Owner*)targetWord;
 float sourceRadius=radius;float targetRadius=target->radius;
 const Coord3D*sourcePos=&position;
 const Coord3D*targetPos=&target->position;
 if(!Rva004DF8D8Test((const Vec2*)targetPos,(const Vec2*)sourcePos,
    (const Vec2*)((const Thing*)this)->getUnitDirectionVector2D(),range,1.0f,1.0f,sourceRadius+targetRadius))return 0;
 if(type->visionAngle>=360.0f)return 1;
 Coord3D delta=*targetPos;
 delta-=*sourcePos;
 delta.z=0.0f;
 delta.Normalize();
 Coord3D facing;
 facing.x=Cos(angle);
 facing.y=Sin(angle);
 facing.z=0.0f;
 range=delta*asBase(facing);
 return range>=Cos(type->visionAngle*0.008725001f);
}
