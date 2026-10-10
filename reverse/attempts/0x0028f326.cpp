// ?rva0028F326@Rva0028F326Owner@@QAEEIM@Z
// partial score=0.673469387755102 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 28F326..28F44C 294B RET8; complete WB CE75F0 twin.
#include "Coord3D.h"
struct Vec2 {float x,y;};
extern bool Rva004DF8D8Test(const Vec2*,const Vec2*,const Vec2*,float,float,float,float);
extern float Cos(float),Sin(float);
class Thing {public:const Coord3D*getUnitDirectionVector2D()const;};
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
 const Coord3D*targetPos=&target->position;
 const Coord3D*sourcePos=&position;
 if(!Rva004DF8D8Test((const Vec2*)targetPos,(const Vec2*)sourcePos,
    (const Vec2*)((const Thing*)this)->getUnitDirectionVector2D(),range,1.0f,1.0f,radius+target->radius))return 0;
 if(type->visionAngle>=360.0f)return 1;
 Coord3D delta={targetPos->x-sourcePos->x,targetPos->y-sourcePos->y,0.0f};
 delta.Normalize();
 FacingVector facing;
 facing.x=Cos(angle);
 facing.y=Sin(angle);
 facing.z=0.0f;
 range=facing.dot(delta);
 return range>=Cos(type->visionAngle*0.008725001f);
}
