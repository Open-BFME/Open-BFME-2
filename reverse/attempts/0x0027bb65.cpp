// ?applyPhysicsXform@Drawable@@QAEXPAVMatrix3D@@@Z
// partial score=0.9977 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// retail 0x0027BB65..0x0027BED0 (875 bytes) thiscall RET 4; ZH Drawable::applyPhysicsXform order and guards.
// Translation via WWMath Matrix3D::Translate(const Vector3&) with (float) casts on a Vector3(0,0,m_totalZ)
// temporary: with all three rows 3-term it reproduces retail's zero-term factoring (Y+X, X+Y, Y+X) and every
// rotation byte, but leaves row 1's z load after the row-0 W store. Writing row 1 as BFME1's translatePhysicsZ
// explicit sum (X+Y)*t0 + Z*t2 hoists that z load like retail but flips row 1's sum to [esi+0x14] then
// [esi+0x10] (retail 0x10 then 0x14): 873/875 bytes, sole residue those two displacement bytes.
// calcPhysicsXform 0x0027BA95 has no row: landing needs a pin or its row.
// Reference WWMath Matrix3D postMul and assignment; native BED0 proves flag43F and order.
#include <math.h>
class Vector3{public:float X,Y,Z;__forceinline Vector3(float x,float y,float z){X=x;Y=y;Z=z;}__forceinline float&operator[](int i){return (&X)[i];}__forceinline const float&operator[](int i)const{return (&X)[i];}};
class Vector4{public:float X,Y,Z,W;__forceinline Vector4&operator=(const Vector4&v){X=v.X;Y=v.Y;Z=v.Z;W=v.W;return *this;}
__forceinline float&operator[](int i){return (&X)[i];}__forceinline const float&operator[](int i)const{return (&X)[i];}};
class Matrix3D{Vector4 Row[3];public:
__forceinline void Translate(const Vector3 &t)
{
	Row[0][3] += (float)(Row[0][0]*t[0] + Row[0][1]*t[1] + Row[0][2]*t[2]);
	Row[1][3] += (Row[1][0] + Row[1][1])*t[0] + Row[1][2]*t[2];
	Row[2][3] += (float)(Row[2][0]*t[0] + Row[2][1]*t[1] + Row[2][2]*t[2]);
}
__forceinline void Rotate_X(const float&theta)
{
	float tmp1,tmp2;
	float s,c;

	s = sinf(theta);
	c = cosf(theta);

	tmp1 = Row[0][1]; tmp2 = Row[0][2];
	Row[0][1] = (float)( c*tmp1 + s*tmp2);
	Row[0][2] = (float)(-s*tmp1 + c*tmp2);

	tmp1 = Row[1][1]; tmp2 = Row[1][2];
	Row[1][1] = (float)( c*tmp1 + s*tmp2);
	Row[1][2] = (float)(-s*tmp1 + c*tmp2);

	tmp1 = Row[2][1]; tmp2 = Row[2][2];
	Row[2][1] = (float)( c*tmp1 + s*tmp2);
	Row[2][2] = (float)(-s*tmp1 + c*tmp2);

}
__forceinline void Rotate_Y(const float&theta)
{
	float tmp1,tmp2;
	float s,c;

	s = sinf(theta);
	c = cosf(theta);

	tmp1 = Row[0][0]; tmp2 = Row[0][2];
	Row[0][0] = (float)(c*tmp1 - s*tmp2);
	Row[0][2] = (float)(s*tmp1 + c*tmp2);

	tmp1 = Row[1][0]; tmp2 = Row[1][2];
	Row[1][0] = (float)(c*tmp1 - s*tmp2);
	Row[1][2] = (float)(s*tmp1 + c*tmp2);

	tmp1 = Row[2][0]; tmp2 = Row[2][2];
	Row[2][0] = (float)(c*tmp1 - s*tmp2);
	Row[2][2] = (float)(s*tmp1 + c*tmp2);
}
__forceinline void Rotate_Z(const float&theta)
{
	float tmp1,tmp2;
	float c,s;

	c = cosf(theta);
	s = sinf(theta);

	tmp1 = Row[0][0]; tmp2 = Row[0][1];
	Row[0][0] = (float)( c*tmp1 + s*tmp2);
	Row[0][1] = (float)(-s*tmp1 + c*tmp2);

	tmp1 = Row[1][0]; tmp2 = Row[1][1];
	Row[1][0] = (float)( c*tmp1 + s*tmp2);
	Row[1][1] = (float)(-s*tmp1 + c*tmp2);

	tmp1 = Row[2][0]; tmp2 = Row[2][1];
	Row[2][0] = (float)( c*tmp1 + s*tmp2);
	Row[2][1] = (float)(-s*tmp1 + c*tmp2);
}
};
enum KindOfType{NATIVE_KIND_51=0x51};
class Object{public:bool isKindOf(KindOfType)const;char pad[0x1c8];unsigned char disabled;};
class GlobalData{public:char pad[0x9b0];bool showPhysics;};
extern GlobalData*TheGlobalData;
class View{public:
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
virtual bool isCameraMovementFinished();
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
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual bool isTimeFrozen();
};extern View*TheTacticalView;
class ScriptEngine;extern ScriptEngine*TheScriptEngine;
class Rva00203B08{public:bool rva0020424FF();};
class Rva00203ACEByteField{public:unsigned char get()const;};
class Drawable{public:
struct PhysicsXformInfo{float m_totalPitch,m_totalRoll,m_totalYaw,m_totalZ;PhysicsXformInfo():m_totalPitch(0),m_totalRoll(0),m_totalYaw(0),m_totalZ(0){}};
bool calcPhysicsXform(PhysicsXformInfo&);
void applyPhysicsXform(Matrix3D*matrix);
char pad[0xfc];Object*object;
};
void Drawable::applyPhysicsXform(Matrix3D*mtx){
const Object*obj=object;
if(!obj||(obj->disabled&8)&&!obj->isKindOf(NATIVE_KIND_51)||!TheGlobalData->showPhysics)return;
bool frozen=TheTacticalView->isTimeFrozen()&&!TheTacticalView->isCameraMovementFinished();
frozen=frozen||((Rva00203B08*)TheScriptEngine)->rva0020424FF()||((Rva00203ACEByteField*)TheScriptEngine)->get();
if(frozen)return;
PhysicsXformInfo info;
if(calcPhysicsXform(info)){
 mtx->Translate(Vector3(0.0f,0.0f,info.m_totalZ));
 mtx->Rotate_Y(info.m_totalPitch);
 mtx->Rotate_X(-info.m_totalRoll);
 mtx->Rotate_Z(info.m_totalYaw);
}
}
