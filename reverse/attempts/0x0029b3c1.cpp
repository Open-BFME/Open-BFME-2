// ?rva0029B3C1@InGameUI@@QBEMPBVObject@@@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include/Lib
// Scratch-only canonical12B layout; header is missing owned Normalize2D declaration.
struct Coord3D {float x,y,z;float Normalize2D();};
class Object { char pad[0x38];public:Coord3D position;char pad44[0x1C0-0x44];float orientation;};
float ACos(float);
class InGameUI {char pad[0x9B4];public:bool overrideHeading;char pad9B5[3];Coord3D target;
float rva0029B3C1(const Object*)const;
};
float InGameUI::rva0029B3C1(const Object *obj)const
{
 if(!overrideHeading)return obj->orientation;
 Coord3D delta;
 delta.x=target.x-obj->position.x;
 delta.y=target.y-obj->position.y;
 delta.z=target.z-obj->position.z;
 if(delta.x*delta.x+delta.y*delta.y<1.0f)return obj->orientation;
 delta.Normalize2D();
 return delta.y<0.0f?-ACos(delta.x):ACos(delta.x);
}
