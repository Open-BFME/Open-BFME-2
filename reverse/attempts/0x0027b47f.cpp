// ?calcPhysicsXformHugeFourLegs@Drawable@@QAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// partial score=0.99557 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// stlport
//
// ?calcPhysicsXformHugeFourLegs@Drawable@@QAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// retail 0x0027B47F..0x0027BA95 (1558 bytes) thiscall RET 8.
//
// HugeFourLegs appearance case of Drawable::calcPhysicsXform (caller
// 0x0027BB52): spring/damper pitch/roll/overlap update over four foot points
// (module feet via collectFeet, else geometry corners), terrain heights via
// TheTerrainLogic slot 7. Identity: WB 0x00CA8750; ZH/BFME1 wheel/tread
// donors guide the shared equations.
#include <math.h>
#include <stl/_alloc.h>
// TU-local Coord3D (name and trivial-ABI shape shared with the rowed
// vector<Coord3D> resize body at 0x000CA2F3; user-declared ctor/copy/dtor so
// a value temporary stays uninitialized, as retail passes it).
struct Coord3D { Coord3D() {} Coord3D(const Coord3D &) {} ~Coord3D() {} float x; float y; float z; };
typedef float Real; typedef int Int;typedef bool Bool;
struct Region2D{struct Point{float x,y;}lo,hi;};
class Rva0087E370{public:void method(const Coord3D&,float,Region2D&)const;};
void Rva00030830FreeAllocation(void*);
namespace _STL {

template<class T,class A>class _Vector_base{public:T*_M_start;T*_M_finish;_STLP_alloc_proxy<T*,T,A>_M_end;__declspec(noinline) _Vector_base(const A&a):_M_start(0),_M_finish(0),_M_end(a,0){}~_Vector_base(){if(_M_start)Rva00030830FreeAllocation(_M_start);}};
template<class T,class A=allocator<T> >class vector:public _Vector_base<T,A>{public:
vector(const A&a=A()):_Vector_base<T,A>(a){}~vector(){}
unsigned int size()const{return _M_finish-_M_start;}T&operator[](unsigned int n){return _M_start[n];}
// Out-of-line definition: the rowed vector<Coord3D> resize at 0x000CA2F3.
void resize(unsigned int n,T value);
};
}
class DrawableLocoInfo{public:virtual ~DrawableLocoInfo(){}DrawableLocoInfo();float m_pitch,m_pitchRate,m_roll,m_rollRate,m_yaw,m_accelerationPitch,m_accelerationPitchRate,m_accelerationRoll,m_accelerationRollRate,m_overlapZVel,m_overlapZ,m_wobble,m_yawModulator,m_pitchModulator;float wheels[7];};
struct LocomotorTemplate{char pad[0x88];float accelLimit,decelLimit,pitchStiff,rollStiff,pitchDamp,rollDamp;char padA0[0x18];float axial;};
class Locomotor{public:void*vp;const LocomotorTemplate*data;float getAccelPitchLimit()const{return data->accelLimit;}float getPitchStiffness()const{return data->pitchStiff;}float getRollStiffness()const{return data->rollStiff;}float getPitchDamping()const{return data->pitchDamp;}float getRollDamping()const{return data->rollDamp;}float getUniformAxialDamping()const{return data->axial;}};
class Object{public:char pad[0x25C];void*physics;Int rva0028B511()const;};
class TerrainLogic{public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual float getLayerHeight(float,float,int,Coord3D*,bool);};extern TerrainLogic*TheTerrainLogic;
class BfmeFootDraw{public:
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
virtual void slot16();
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
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual bool collectFeet(_STL::vector<Coord3D>*,int);
};
class DrawModule{public:
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
virtual void slot16();
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
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual BfmeFootDraw* getDraw();
};
float Sin(float);float Cos(float);
class Drawable{public:struct PhysicsXformInfo{float m_totalPitch,m_totalRoll,m_totalYaw,m_totalZ;};
void calcPhysicsXformHugeFourLegs(const Locomotor*,PhysicsXformInfo&);
const Coord3D*getPosition()const;
char pad00[0x44];float angle;char pad48[0xFC-0x48];Object*m_object;char pad100[0x13C-0x100];DrawableLocoInfo*m_locoInfo;char pad140[0x14C-0x140];DrawModule**modules;
};
void Drawable::calcPhysicsXformHugeFourLegs(const Locomotor*locomotor,PhysicsXformInfo&info){
if(!m_locoInfo)m_locoInfo=new DrawableLocoInfo;
const Real ACCEL_PITCH_LIMIT=locomotor->getAccelPitchLimit();
const Real PITCH_STIFFNESS=locomotor->getPitchStiffness();
const Real ROLL_STIFFNESS=locomotor->getRollStiffness();
const Real PITCH_DAMPING=locomotor->getPitchDamping();
const Real ROLL_DAMPING=locomotor->getRollDamping();
const Real UNIFORM_AXIAL_DAMPING=locomotor->getUniformAxialDamping();
const Object*obj=m_object;if(!obj||!obj->physics)return;
const Coord3D*pos=getPosition();
Real direction=angle;
_STL::vector<Coord3D> points;
union{Region2D bounds;float heights[4];}scratch;
bool found=false;
for(DrawModule**mod=modules;!found&&*mod;++mod){BfmeFootDraw*draw=(*mod)->getDraw();if(draw&&draw->collectFeet(&points,0)&&points.size()>=4)found=true;}
if(!found){const Rva0087E370*geom=(const Rva0087E370*)((const char*)obj+0xA8);Region2D&bounds=scratch.bounds;Coord3D zero;zero.x=0;zero.y=0;zero.z=0;
geom->method(zero,0.0f,bounds);
points.resize(4,Coord3D());
Real s=Sin(direction),c=Cos(direction);
points[1].x=bounds.hi.x*c-bounds.hi.y*s;points[1].y=bounds.hi.y*c+bounds.hi.x*s;points[1].z=pos->z;
points[0].x=bounds.lo.x*c-bounds.hi.y*s;points[0].y=bounds.hi.y*c+bounds.lo.x*s;points[0].z=pos->z;
points[3].x=bounds.hi.x*c-bounds.lo.y*s;points[3].y=bounds.lo.y*c+bounds.hi.x*s;points[3].z=pos->z;
points[2].x=bounds.lo.x*c-bounds.lo.y*s;points[2].y=bounds.lo.y*c+bounds.lo.x*s;points[2].z=pos->z;
}
Real*heights=scratch.heights;
for(Int i=0;i<4;++i){if(i==0||points[i].x!=points[i-1].x||points[i].y!=points[i-1].y)heights[i]=TheTerrainLogic->getLayerHeight(points[i].x,points[i].y,obj->rva0028B511(),0,true);else heights[i]=heights[i-1];}
Real front=(heights[0]+heights[1])/2,back=(heights[2]+heights[3])/2;
Real frontX=(points[0].x+points[1].x)/2,frontY=(points[0].y+points[1].y)/2;
Real backX=(points[2].x+points[3].x)/2,backY=(points[2].y+points[3].y)/2;
Real dx=frontX-backX,dy=frontY-backY;
Real dist=(Real)sqrt(dx*dx+dy*dy);
Real pitch=atan2f(back-front,dist);
m_locoInfo->m_pitchRate+=(-PITCH_STIFFNESS*(m_locoInfo->m_pitch-pitch))+(-PITCH_DAMPING*m_locoInfo->m_pitchRate);
if(m_locoInfo->m_pitchRate>0)m_locoInfo->m_pitchRate*=0.5f;
m_locoInfo->m_pitch+=UNIFORM_AXIAL_DAMPING*m_locoInfo->m_pitchRate;
m_locoInfo->m_roll+=UNIFORM_AXIAL_DAMPING*m_locoInfo->m_rollRate;
m_locoInfo->m_accelerationPitchRate+=(-PITCH_STIFFNESS*m_locoInfo->m_accelerationPitch)+(-PITCH_DAMPING*m_locoInfo->m_accelerationPitchRate);
m_locoInfo->m_accelerationPitch+=m_locoInfo->m_accelerationPitchRate;
m_locoInfo->m_accelerationRollRate+=(-ROLL_STIFFNESS*m_locoInfo->m_accelerationRoll)+(-ROLL_DAMPING*m_locoInfo->m_accelerationRollRate);
m_locoInfo->m_accelerationRoll+=m_locoInfo->m_accelerationRollRate;
info.m_totalPitch=m_locoInfo->m_accelerationPitch+m_locoInfo->m_pitch;
info.m_totalRoll=m_locoInfo->m_accelerationRoll+m_locoInfo->m_roll;
if(m_locoInfo->m_accelerationPitch>ACCEL_PITCH_LIMIT)m_locoInfo->m_accelerationPitch=ACCEL_PITCH_LIMIT;
else if(m_locoInfo->m_accelerationPitch<-ACCEL_PITCH_LIMIT)m_locoInfo->m_accelerationPitch=-ACCEL_PITCH_LIMIT;
if(m_locoInfo->m_accelerationRoll>ACCEL_PITCH_LIMIT)m_locoInfo->m_accelerationRoll=ACCEL_PITCH_LIMIT;
else if(m_locoInfo->m_accelerationRoll<-ACCEL_PITCH_LIMIT)m_locoInfo->m_accelerationRoll=-ACCEL_PITCH_LIMIT;
Real old=m_locoInfo->m_overlapZ;
Real wanted=(front+back)/2-pos->z;
m_locoInfo->m_overlapZ+=m_locoInfo->m_overlapZVel;
if(wanted>=old&&wanted<=m_locoInfo->m_overlapZ||wanted<=old&&wanted>=m_locoInfo->m_overlapZ){m_locoInfo->m_overlapZ=wanted;m_locoInfo->m_overlapZVel=0.0f;}
else if(wanted>m_locoInfo->m_overlapZ&&m_locoInfo->m_overlapZVel<0||wanted<m_locoInfo->m_overlapZ&&m_locoInfo->m_overlapZVel>0){m_locoInfo->m_overlapZ-=m_locoInfo->m_overlapZVel;m_locoInfo->m_overlapZVel=0.0f;}
else if(wanted>m_locoInfo->m_overlapZ)m_locoInfo->m_overlapZVel+=1.5f;
else m_locoInfo->m_overlapZVel-=0.5f;
info.m_totalZ=m_locoInfo->m_overlapZ;
}
