// Object motion history: native 0x0028E8FD..0x0028EA91, RET4, 404 bytes.
// The crushing notifier at 0x004CE700 proves the three-float output. Native
// accesses prove position+38, frame+188, previous+18C, planned+198 and the
// three flags at +1A4..1A6; WB CE1A50 supplies the separate branch order.
// MotionCoord is a local inline-copy adapter over canonical Coord3D, not an
// original class-name claim. The 41-byte translation provider stays here;
// its visible body prevents the temporary coordinate from escaping. Reading
// its three components as one Coord3D preserves its SSE body under /O1.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include 
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct MotionCoord:Coord3D{
 __forceinline MotionCoord(){}
 __forceinline MotionCoord(const Coord3D&coord){x=coord.x;y=coord.y;z=coord.z;}
 __forceinline MotionCoord(const MotionCoord&motionCoord){x=motionCoord.x;y=motionCoord.y;z=motionCoord.z;}
 __forceinline void add(const Coord3D&other){x+=other.x;y+=other.y;z+=other.z;}
 __forceinline void sub(const Coord3D&other){x-=other.x;y-=other.y;z-=other.z;}
 __forceinline void scale(float f){x*=f;y*=f;z*=f;}
 __forceinline MotionCoord& operator=(const MotionCoord&r){x=r.x;y=r.y;z=r.z;return *this;}
 __forceinline void divide(float divisor){float i=1.0f/divisor;x*=i;y*=i;z*=i;}
};
class Object{public:
 char pad00[0x38];MotionCoord position;char pad44[0x188-0x44];unsigned frame;
 MotionCoord previous,planned;bool flag1A4,flag1A5,flag1A6;
 __forceinline unsigned lastFrame() const {return frame;}void rva0028E8FD(Coord3D*);
};
#include "../../Include/GameClient/Rva002722AA.h"

struct Rva0028E8D4Matrix
{
	float m[12];
};

#include "../../Include/GameLogic/Module/Rva0028E8D4.h"

void Rva0028E8D4::rva0028E8D4(float *out) const
{
 const Rva0028E8D4Matrix *m =
  (const Rva0028E8D4Matrix *)((const Rva002722AA *)this)->get();
 Coord3D translation = {m->m[3],m->m[7],m->m[11]};
 out[0]=translation.x;
 out[1]=translation.y;
 out[2]=translation.z;
}

void Object::rva0028E8FD(Coord3D*out){
    if(flag1A6){
        MotionCoord delta(planned);
        delta.sub(position);
        out->y=delta.y;
        out->z=delta.z;
        out->x=delta.x;
    }
    else if(flag1A4 && lastFrame()<TheGameLogic->getFrame()){
        MotionCoord translation;
        ((const Rva0028E8D4*)this)->rva0028E8D4(&translation.x);
        _ReadWriteBarrier();
        // WB CE1B4E scales the translation before reading the elapsed frame.
        translation.scale(-1.0f);
        unsigned elapsed=TheGameLogic->getFrame()-lastFrame();
        MotionCoord delta((out ? translation : translation));
        delta.add(position);
        *((MotionCoord*)out)=delta;
        ((MotionCoord*)out)->divide((float)elapsed);
    }
    else if(flag1A5 && lastFrame()<=TheGameLogic->getFrame()){
        unsigned elapsed=TheGameLogic->getFrame()-lastFrame()+1;
        MotionCoord delta(position);
        delta.sub(previous);
        *((MotionCoord*)out)=delta;
        ((MotionCoord*)out)->divide((float)elapsed);
    }
    else{
        out->y=0.0f;
        out->z=0.0f;
        out->x=0.0f;
    }
}
