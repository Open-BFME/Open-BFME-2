// cl: /O1 /arch:SSE /G7 /MD /EHs
// Native 00375ED7..0037609C/453B RET12. WB F2BE60 corroborates five
// height probes: center, then four corners, and final separation push.
// The original method name is unknown. Target proves AI+258, motion+1F0,
// clearance+48 and Object bounding radius+BC. Probe vector reuse and the
// initial comparison against zero follow the debug body and native SSE.
// Keep the separation provider external: visible body knowledge changes
// MSVC's receiver allocation. The final object read preserves its native
// parameter home; local volatile qualification asserts no original type.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct AerialMotionInfo { char prefix[0x48]; float height; };
struct AerialAI { char prefix[0x1F0]; AerialMotionInfo *motion; };
class GeometryInfo {public: char prefix[0x14];float radius;};
class Object {public:
 char prefix[0xA8];GeometryInfo geometry;
 char padC0[0x258-0xC0];AerialAI* ai;
};
class Rva00375AF7HeightQuery {public:float rva00375B7A(float,float);};
class AerialPathfinder {public:
 int rva00375ED7(Object*,const Coord3D*,Coord3D*);
 bool rva00375C28(Object*,const Coord3D*,float*,Coord3D*);
};
int AerialPathfinder::rva00375ED7(Object*obj,const Coord3D*pos,Coord3D*push)
{
 AerialAI*ai=obj->ai;
 if(!ai)return 2;
 push->x=0;push->y=0;push->z=0;
 float height=ai->motion->height;
 float radius=obj->geometry.radius;
 Coord3D sample={0,0,0};
 float worst=0;
 sample.z=pos->z-height*0.5f;
 sample.x=pos->x;sample.y=pos->y;
 float ground=((Rva00375AF7HeightQuery*)this)->rva00375B7A(sample.x,sample.y);
 if(ground-sample.z>0.0f)worst=ground-sample.z;
 sample.z=pos->z-height*0.5f*0.777f;
 sample.x=pos->x-radius;sample.y=pos->y-radius;
 ground=((Rva00375AF7HeightQuery*)this)->rva00375B7A(sample.x,sample.y);
 if(ground-sample.z>worst)worst=ground-sample.z;
 sample.y=pos->y+radius;
 ground=((Rva00375AF7HeightQuery*)this)->rva00375B7A(sample.x,sample.y);
 if(ground-sample.z>worst)worst=ground-sample.z;
 sample.x=pos->x+radius;
 ground=((Rva00375AF7HeightQuery*)this)->rva00375B7A(sample.x,sample.y);
 if(ground-sample.z>worst)worst=ground-sample.z;
 sample.y=pos->y-radius;
 ground=((Rva00375AF7HeightQuery*)this)->rva00375B7A(sample.x,sample.y);
 if(ground-sample.z>worst)worst=ground-sample.z;
 push->z+=worst;
 rva00375C28(*(Object*volatile*)&obj,pos,&worst,push);
 return worst>0.0f ? 1:0;
}
