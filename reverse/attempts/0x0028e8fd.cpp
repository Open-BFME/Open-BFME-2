// ?rva0028E8FD@Object@@QAEXPAUCoord3D@@@Z
// partial score=0.8989050382870799 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include /I.
#include "Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva0028E8D4{public:void rva0028E8D4(float*)const;};
struct MotionCoord:Coord3D{
 __forceinline MotionCoord(){}
 __forceinline MotionCoord(const Coord3D&r){x=r.x;y=r.y;z=r.z;}
 __forceinline MotionCoord(const MotionCoord&r){x=r.x;y=r.y;z=r.z;}
 __forceinline void add(const Coord3D&r){x+=r.x;y+=r.y;z+=r.z;}
 __forceinline void sub(const Coord3D&r){x-=r.x;y-=r.y;z-=r.z;}
 __forceinline void scale(float f){x*=f;y*=f;z*=f;}
 __forceinline MotionCoord& operator=(const MotionCoord&r){x=r.x;y=r.y;z=r.z;return *this;}
 __forceinline void divide(float f){float i=1.0f/f;x*=i;y*=i;z*=i;}
};
class Object{public:
 char pad00[0x38];MotionCoord position;char pad44[0x188-0x44];unsigned frame;
 MotionCoord previous,planned;bool flag1A4,flag1A5,flag1A6;
 __forceinline unsigned lastFrame() const {return frame;}void rva0028E8FD(Coord3D*);
};
void Object::rva0028E8FD(Coord3D*out){
 if(flag1A6){MotionCoord delta(planned);delta.sub(position);out->y=delta.y;out->z=delta.z;out->x=delta.x;}
 else if(flag1A4 && lastFrame()<TheGameLogic->getFrame()){
  MotionCoord translation;((const Rva0028E8D4*)this)->rva0028E8D4(&translation.x);
  unsigned elapsed=TheGameLogic->getFrame()-lastFrame();translation.scale(-1.0f);MotionCoord delta(translation);delta.add(position);
  *((MotionCoord*)out)=delta;((MotionCoord*)out)->divide((float)elapsed);
 }else if(flag1A5 && lastFrame()<=TheGameLogic->getFrame()){
  unsigned elapsed=TheGameLogic->getFrame()-lastFrame()+1;MotionCoord delta(position);delta.sub(previous);*((MotionCoord*)out)=delta;((MotionCoord*)out)->divide((float)elapsed);
 }else{out->y=0.0f;out->z=0.0f;out->x=0.0f;}
}
