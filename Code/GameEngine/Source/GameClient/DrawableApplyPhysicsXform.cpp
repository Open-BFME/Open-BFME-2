// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?applyPhysicsXform@Drawable@@QAEXPAVMatrix3D@@@Z
// retail 0x0027BB65..0x0027BED0 (875 bytes) thiscall RET 4.
//
// Guards: object +0xFC, disabled bit 8 unless kind-of 0x51, TheWritableGlobalData
// +0x9B0 showPhysics (converged global 0x009FE758, one name), then TheTacticalView slots 0xD8 (isTimeFrozen) / 0x78
// (isCameraMovementFinished), ScriptEngine 0x00424FF and 0x0203ACE byte
// field. Then calcPhysicsXform(info) (rowed 0x0027BA95) and the four
// Matrix3D post-multiplies Translate/Rotate_Y/Rotate_X(-roll)/Rotate_Z.
// The offsets, the guard order and the four calls are ZH
// Drawable::applyPhysicsXform as carried by the BFME1 donor.
//
// Codegen fact for the WWMath row math: the translation is
// Translate(Vector3(0,0,info.m_totalZ)) inlined, so the t[0]/t[1] terms are
// the constants 0 and survive as multiplies (MSVC folds X*0+Y*0 to (X+Y)*0,
// no /fp:fast). Retail's schedule loads the row-1 z operand into xmm2 before
// the row-0 W store and computes row 1's sum X-first while rows 0/2 are
// Y-first; a named z local shared by rows 0/1 reproduces exactly that, row 2
// keeps the t[2] memory operand. Every other row spelling measured 2-42
// residual instructions (see reverse/re_attempts.log 0x0027BB65).
//
// The view-class helpers are __declspec(dllimport) __forceinline so the TU
// emits only the row itself (no divergent Vector3/Matrix3D COMDATs).
#include <math.h>
class Vector3{public:float X,Y,Z;__declspec(dllimport) __forceinline Vector3(float x,float y,float z){X=x;Y=y;Z=z;}__forceinline float&operator[](int i){return (&X)[i];}__declspec(dllimport) __forceinline const float&operator[](int i)const{return (&X)[i];}};
#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
// Preserve the pointer-based component access used by the native row math.
static __forceinline float &vector4Component(Vector4 &row, int index)
{
	return (&row.X)[index];
}
class Matrix3D{Vector4 Row[3];public:
__declspec(dllimport) __forceinline void Translate(const Vector3 &t)
{
	// Named z local used by rows 0/1 only: retail's row-1 z load
	// (movss xmm2,[ebp-8]) is hoisted above the row-0 W store and its X+Y
	// sum is X-first; row 2 keeps the direct t[2] memory operand. All other
	// orientations were measured non-exact (2-42 residual instructions).
	const float z=t[2];
	vector4Component(Row[0],3) += (float)(vector4Component(Row[0],0)*t[0] + vector4Component(Row[0],1)*t[1] + vector4Component(Row[0],2)*z);
	vector4Component(Row[1],3) += (float)(vector4Component(Row[1],0)*t[0] + vector4Component(Row[1],1)*t[1] + vector4Component(Row[1],2)*z);
	vector4Component(Row[2],3) += (float)(vector4Component(Row[2],0)*t[0] + vector4Component(Row[2],1)*t[1] + vector4Component(Row[2],2)*t[2]);
}
__declspec(dllimport) __forceinline void Rotate_X(const float&theta)
{
	float tmp1,tmp2;
	float s,c;

	s = sinf(theta);
	c = cosf(theta);

	tmp1 = vector4Component(Row[0],1); tmp2 = vector4Component(Row[0],2);
	vector4Component(Row[0],1) = (float)( c*tmp1 + s*tmp2);
	vector4Component(Row[0],2) = (float)(-s*tmp1 + c*tmp2);

	tmp1 = vector4Component(Row[1],1); tmp2 = vector4Component(Row[1],2);
	vector4Component(Row[1],1) = (float)( c*tmp1 + s*tmp2);
	vector4Component(Row[1],2) = (float)(-s*tmp1 + c*tmp2);

	tmp1 = vector4Component(Row[2],1); tmp2 = vector4Component(Row[2],2);
	vector4Component(Row[2],1) = (float)( c*tmp1 + s*tmp2);
	vector4Component(Row[2],2) = (float)(-s*tmp1 + c*tmp2);

}
__declspec(dllimport) __forceinline void Rotate_Y(const float&theta)
{
	float tmp1,tmp2;
	float s,c;

	s = sinf(theta);
	c = cosf(theta);

	tmp1 = vector4Component(Row[0],0); tmp2 = vector4Component(Row[0],2);
	vector4Component(Row[0],0) = (float)(c*tmp1 - s*tmp2);
	vector4Component(Row[0],2) = (float)(s*tmp1 + c*tmp2);

	tmp1 = vector4Component(Row[1],0); tmp2 = vector4Component(Row[1],2);
	vector4Component(Row[1],0) = (float)(c*tmp1 - s*tmp2);
	vector4Component(Row[1],2) = (float)(s*tmp1 + c*tmp2);

	tmp1 = vector4Component(Row[2],0); tmp2 = vector4Component(Row[2],2);
	vector4Component(Row[2],0) = (float)(c*tmp1 - s*tmp2);
	vector4Component(Row[2],2) = (float)(s*tmp1 + c*tmp2);
}
__declspec(dllimport) __forceinline void Rotate_Z(const float&theta)
{
	float tmp1,tmp2;
	float c,s;

	c = cosf(theta);
	s = sinf(theta);

	tmp1 = vector4Component(Row[0],0); tmp2 = vector4Component(Row[0],1);
	vector4Component(Row[0],0) = (float)( c*tmp1 + s*tmp2);
	vector4Component(Row[0],1) = (float)(-s*tmp1 + c*tmp2);

	tmp1 = vector4Component(Row[1],0); tmp2 = vector4Component(Row[1],1);
	vector4Component(Row[1],0) = (float)( c*tmp1 + s*tmp2);
	vector4Component(Row[1],1) = (float)(-s*tmp1 + c*tmp2);

	tmp1 = vector4Component(Row[2],0); tmp2 = vector4Component(Row[2],1);
	vector4Component(Row[2],0) = (float)( c*tmp1 + s*tmp2);
	vector4Component(Row[2],1) = (float)(-s*tmp1 + c*tmp2);
}
};
enum KindOfType{NATIVE_KIND_51=0x51};
class Object{public:bool isKindOf(KindOfType)const;char pad[0x1c8];unsigned char disabled;};
class GlobalData;
extern class GlobalData *TheWritableGlobalData;
class GlobalDataView{public:char pad[0x9b0];bool showPhysics;};
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
struct PhysicsXformInfo{float m_totalPitch,m_totalRoll,m_totalYaw,m_totalZ;__declspec(dllimport) PhysicsXformInfo():m_totalPitch(0),m_totalRoll(0),m_totalYaw(0),m_totalZ(0){}};
bool calcPhysicsXform(PhysicsXformInfo&);
void applyPhysicsXform(Matrix3D*matrix);
char pad[0xfc];Object*object;
};
void Drawable::applyPhysicsXform(Matrix3D*mtx){
const Object*obj=object;
if(!obj||(obj->disabled&8)&&!obj->isKindOf(NATIVE_KIND_51)||!((GlobalDataView*)TheWritableGlobalData)->showPhysics)return;
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
