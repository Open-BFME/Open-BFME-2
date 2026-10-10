// ?doDrawModule@W3DTruckDraw@@UAEXPBVMatrix3D@@@Z
// partial score=0.9760234996 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Include
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// The W3DTankTruckDraw cast names the legacy typed view of the matched
// createEmitters callee. It does not name this caller's owner.

#include "ascii_string.h"
#include "matrix3d.h"
#include "Lib/Coord3D.h"
class RenderObjClass { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0C();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1C();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2C();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3C();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4C();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5C();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6C();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7C();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8C();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9C();
virtual void sA0();
virtual void sA4();
virtual void sA8();
virtual void sAC();
virtual void sB0();
virtual void sB4();
virtual void sB8();
virtual void sBC();
virtual void sC0();
virtual void sC4();
virtual void sC8();
virtual void sCC();
virtual void sD0();
virtual void sD4();
virtual void Capture_Bone(int); virtual void sDC(); virtual void sE0(); virtual void Control_Bone(int,const Matrix3D&,bool=false); };


class BfmeVec3FC { public: float x,y,z; };
class BfmeHostFC { public: char pad[0x18]; BfmeVec3FC pos; void bfmeGetPosFC(BfmeVec3FC *p) { p->x=pos.x;p->y=pos.y;p->z=pos.z; } };
enum KindOfType { NATIVE_KIND_61=61 };
class Thing {};
class Rva000D3F10 { public: int test(unsigned); };
class BfmeOwnerRW { public: int bfmeCheckRW(); };
class W3DModelDraw { public: virtual void doDrawModule(const Matrix3D*); };
class W3DTankTruckDraw { friend class W3DTruckDraw; protected: void enableEmitters(bool); };
struct Rva00781660Locomotor { char head[0x44]; unsigned field40; bool isMovingBackwards() const { return (field40 >> 7) & 1; } };
struct AIUpdateInterface { char head[0x140]; BfmeHostFC *path; char gap[0x1f0-0x144]; Rva00781660Locomotor *loco; BfmeHostFC *getPath() const { return path; } Rva00781660Locomotor *getCurLocomotor() const { return loco; } };
class Object : public Thing { public: bool isKindOf(KindOfType)const; float rva0028AC7D() const; float GetRelativeAngle(const Coord3D*)const; bool isSignificantlyAboveTerrain()const; char head[0x258]; AIUpdateInterface *ai; AIUpdateInterface *getAI() const { return ai; } };
struct TWheelInfo { float m_frontLeftHeightOffset, m_frontRightHeightOffset, m_rearLeftHeightOffset, m_rearRightHeightOffset, m_wheelAngle; };
class Drawable { public: const TWheelInfo *getWheelInfo() const; char head[0xfc]; Object *object; char before138[0x3c]; void *m_locoInfo; Object *getObject() const { return object; } };
class ParticleSystem { public: void stop(); };
ParticleSystem *Make00001B18();
struct Rva00781660Handle { ParticleSystem *system; void *previous, *next; operator bool() const { return system != 0; } ParticleSystem *operator->() const { if (!system) return Make00001B18(); return system; } };
struct Rva006C9270GlobalData { char head[0x9b0]; bool m_showClientPhysics; };
extern Rva006C9270GlobalData *TheWritableGlobalData;
class GameEngine { public: char head[0x38]; int field34; };
extern GameEngine *TheGameEngine;
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00203ACEByteField { public: unsigned char get()const; };
class ScriptEngine { public: bool isFrozen(); };
extern ScriptEngine *TheScriptEngine;
class BfmeScriptEngineFreezeExtra { public: unsigned char get() const; };
class View { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2c();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3c();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4c();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5c();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6c();
virtual void slot70();
virtual void slot74();
virtual bool isCameraMovementFinished();
virtual void slot7c();
virtual void slot80();
virtual void slot84();
virtual void slot88();
virtual void slot8c();
virtual void slot90();
virtual void slot94();
virtual void slot98();
virtual void slot9c();
virtual void slota0();
virtual void slota4();
virtual void slota8();
virtual void slotac();
virtual void slotb0();
virtual void slotb4();
virtual void slotb8();
virtual void slotbc();
virtual void slotc0();
virtual void slotc4();
virtual void slotc8();
virtual void slotcc();
virtual void slotd0();
virtual void slotd4();
virtual bool isTimeFrozen();
};
extern View *TheTacticalView;
class W3DTruckDrawModuleData {
public:
    char prefix[0x194];
    AsciiString m_frontLeftTireBoneName;
    AsciiString m_frontRightTireBoneName;
    AsciiString m_rearLeftTireBoneName;
    AsciiString m_rearRightTireBoneName;
    AsciiString m_midFrontLeftTireBoneName;
    AsciiString m_midFrontRightTireBoneName;
    AsciiString m_midRearLeftTireBoneName;
    AsciiString m_midRearRightTireBoneName;
    AsciiString m_midMidLeftTireBoneName;
    AsciiString m_midMidRightTireBoneName;
    AsciiString field190;
    AsciiString field194;
    AsciiString field198;
    AsciiString field19c;
    AsciiString field1a0;
    AsciiString field1a4;
    AsciiString m_cabBoneName, m_trailerBoneName;
    float m_cabRotationFactor, m_trailerRotationFactor, m_rotationDampingFactor, m_rotationSpeedMultiplier, m_powerslideRotationAddition;
};
class W3DTruckDraw {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7c();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9c();
    virtual void slota0();
    virtual void slota4();
    virtual void slota8();
    virtual void slotac();
    virtual void slotb0();
    virtual void slotb4();
    virtual void slotb8(); virtual void slotbc(); virtual void slotc0(); virtual RenderObjClass *getRenderObject() const;
    W3DTruckDrawModuleData *data;
    Drawable *drawable;
    char gap00c[0x2e8-0xc];
    bool m_effectsInitialized;
    unsigned char m_wasAirborne;
    bool m_isPowersliding;
    char gap27f;
    Rva00781660Handle m_dustEffect,m_dirtEffect,m_powerslideEffect;
    float m_frontWheelRotation,m_rearWheelRotation,m_midFrontWheelRotation,m_midRearWheelRotation;

    int m_frontLeftTireBone, m_frontRightTireBone;
    int m_rearLeftTireBone, m_rearRightTireBone;
    int m_midFrontLeftTireBone, m_midFrontRightTireBone;
    int m_midRearLeftTireBone, m_midRearRightTireBone;
    int m_midMidLeftTireBone, m_midMidRightTireBone;
    int m_secondaryFrontLeftTireBone, m_secondaryFrontRightTireBone;
    int m_secondaryRearLeftTireBone, m_secondaryRearRightTireBone;
    int m_secondaryMidMidLeftTireBone, m_secondaryMidMidRightTireBone;
    int m_cabBone; float m_curCabRotation; int m_trailerBone; float m_curTrailerRotation; int m_prevNumBones;
    char gap374[0x484-0x374];
    RenderObjClass *m_prevRenderObj;
    const W3DTruckDrawModuleData *getW3DTruckDrawModuleData() const { return data; }
protected:
    void updateBones();
public:
    Drawable *getDrawable() const { return drawable; }
    virtual void doDrawModule(const Matrix3D *);
};
static __forceinline void Rva00781660RotateCabZ(Matrix3D &matrix, const float &theta)
{
	float tmp1, tmp2;
	float c, s;
	c = cosf(theta);
	s = sinf(theta);
	tmp1 = matrix[0][0];
	matrix[0][0] = (float)(c * tmp1 + s * (*(volatile float *)&matrix[0][1]));
	matrix[0][1] = (float)(-s * tmp1 + c * (*(volatile float *)&matrix[0][1]));
	tmp1 = matrix[1][0]; tmp2 = matrix[1][1];
	matrix[1][0] = (float)(c * tmp1 + s * tmp2);
	matrix[1][1] = (float)(-s * tmp1 + c * tmp2);
	tmp1 = matrix[2][0]; tmp2 = matrix[2][1];
	matrix[2][0] = (float)(c * tmp1 + s * tmp2);
	matrix[2][1] = (float)(-s * tmp1 + c * tmp2);
}

void W3DTruckDraw::doDrawModule(const Matrix3D* transformMtx)
{

	((W3DModelDraw *)this)->W3DModelDraw::doDrawModule(transformMtx);

	if (!TheWritableGlobalData->m_showClientPhysics)
		return;
	const W3DTruckDrawModuleData *moduleData = getW3DTruckDrawModuleData();
	if (moduleData==0) return; // shouldn't ever happen.

    if(TheTacticalView->isTimeFrozen() && !TheTacticalView->isCameraMovementFinished()) return;
    if(((Rva00203B08*)TheScriptEngine)->rva0020424FF()) return;
    if(((Rva00203ACEByteField *)TheScriptEngine)->get()) return;



	// get object from logic
	Object *obj = getDrawable()->getObject();
	if (obj == 0)
		return;

	if (getRenderObject()==0) return;
	if (getRenderObject() != m_prevRenderObj) {
		updateBones();
	}
	
    float speed=obj->rva0028AC7D();
    if(!obj->isKindOf(NATIVE_KIND_61)) speed=0;

	const TWheelInfo *wheelInfo = getDrawable()->getWheelInfo();	// note, can return null!
	AIUpdateInterface *ai = obj->getAI();
	if (m_cabBone && wheelInfo) {
		Matrix3D cabXfrm(1);
		cabXfrm.Make_Identity();		 
		float desiredAngle = wheelInfo->m_wheelAngle*moduleData->m_cabRotationFactor;

		// Check goal angle.
		if (ai && ai->getPath())
		{
			Coord3D pointOnPath;
			ai->getPath()->bfmeGetPosFC((BfmeVec3FC *)&pointOnPath);
			float angleToGoal = obj->GetRelativeAngle(&pointOnPath);
			//DEBUG_LOG(("To goal %f, desired %f ", 180*angleToGoal/PI, 180*desiredAngle/PI));
			if (angleToGoal<0) {
				if (desiredAngle<angleToGoal) desiredAngle=angleToGoal;
				if (desiredAngle>0) desiredAngle = 0;
			} else {
				if (desiredAngle>angleToGoal) desiredAngle = angleToGoal;
				if (desiredAngle<0) desiredAngle = 0;
			}
			//DEBUG_LOG(("final desired %f ", 180*desiredAngle/PI));
		}	

		float deltaAngle = desiredAngle - m_curCabRotation;
		deltaAngle *= moduleData->m_rotationDampingFactor;
		m_curCabRotation += deltaAngle;
		Rva00781660RotateCabZ(cabXfrm,m_curCabRotation);
		getRenderObject()->Capture_Bone( m_cabBone );
		getRenderObject()->Control_Bone( m_cabBone, cabXfrm );
		if (m_trailerBone && wheelInfo) {
			desiredAngle = -wheelInfo->m_wheelAngle*moduleData->m_trailerRotationFactor;
			float deltaAngle = desiredAngle - m_curTrailerRotation;
			deltaAngle *= moduleData->m_rotationDampingFactor;
			m_curTrailerRotation += deltaAngle;
			cabXfrm.Make_Identity();
			cabXfrm.Rotate_Z(m_curTrailerRotation);
			getRenderObject()->Capture_Bone( m_trailerBone );
			getRenderObject()->Control_Bone( m_trailerBone, cabXfrm );
		}
	}

	if (m_frontLeftTireBone || m_rearLeftTireBone) 
	{
		float powerslideRotationAddition = moduleData->m_powerslideRotationAddition;
		if (ai) {
			Rva00781660Locomotor *loco = ai->getCurLocomotor();
			if (loco) {
				if (loco->isMovingBackwards()) {
					speed = -speed; // rotate wheels backwards.  jba.
					powerslideRotationAddition = -powerslideRotationAddition;
				}
			}
		}
		const float rotationFactor = moduleData->m_rotationSpeedMultiplier / TheGameEngine->field34;
		m_frontWheelRotation = *(const volatile float*)&m_frontWheelRotation + rotationFactor*speed;
		if (m_isPowersliding) 
		{
			m_rearWheelRotation += rotationFactor*(speed + powerslideRotationAddition);
		} 
		else 
		{
			m_rearWheelRotation += rotationFactor*speed;
		}

		// For now, just use the same values for mid wheels -- may want to do independent calcs later...
		m_midFrontWheelRotation = m_frontWheelRotation;
		m_midRearWheelRotation = m_rearWheelRotation;

		Matrix3D wheelXfrm(1);



		if (m_frontLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontLeftHeightOffset);		 
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_frontWheelRotation);
			getRenderObject()->Capture_Bone( m_frontLeftTireBone );
			getRenderObject()->Control_Bone( m_frontLeftTireBone, wheelXfrm );
            if(m_secondaryFrontLeftTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryFrontLeftTireBone);
                getRenderObject()->Control_Bone(m_secondaryFrontLeftTireBone,wheelXfrm);
            }


			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontRightHeightOffset);
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_frontWheelRotation);
			getRenderObject()->Capture_Bone( m_frontRightTireBone );
			getRenderObject()->Control_Bone( m_frontRightTireBone, wheelXfrm );
            if(m_secondaryFrontRightTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryFrontRightTireBone);
                getRenderObject()->Control_Bone(m_secondaryFrontRightTireBone,wheelXfrm);
            }	
		}
		if (m_rearLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_rearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearLeftHeightOffset);
			getRenderObject()->Capture_Bone( m_rearLeftTireBone );
			getRenderObject()->Control_Bone( m_rearLeftTireBone, wheelXfrm );
            if(m_secondaryRearLeftTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryRearLeftTireBone);
                getRenderObject()->Control_Bone(m_secondaryRearLeftTireBone,wheelXfrm);
            }	

			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_rearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearRightHeightOffset);

			//@todo TROUBLE HERE, THE BONE INDICES DO NOT MATCH THE RENDEROBJECTS BONES, SOMETIMES

			getRenderObject()->Capture_Bone( m_rearRightTireBone );
			getRenderObject()->Control_Bone( m_rearRightTireBone, wheelXfrm );
            if(m_secondaryRearRightTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryRearRightTireBone);
                getRenderObject()->Control_Bone(m_secondaryRearRightTireBone,wheelXfrm);
            }	
		}
		if (m_midFrontLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontLeftHeightOffset);		 
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_midFrontWheelRotation);
			getRenderObject()->Capture_Bone( m_midFrontLeftTireBone );
			getRenderObject()->Control_Bone( m_midFrontLeftTireBone, wheelXfrm );

			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontRightHeightOffset);
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_midFrontWheelRotation);
			getRenderObject()->Capture_Bone( m_midFrontRightTireBone );
			getRenderObject()->Control_Bone( m_midFrontRightTireBone, wheelXfrm );	
		}
		if (m_midRearLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearLeftHeightOffset);
			getRenderObject()->Capture_Bone( m_midRearLeftTireBone );
			getRenderObject()->Control_Bone( m_midRearLeftTireBone, wheelXfrm );	

			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearRightHeightOffset);
			getRenderObject()->Capture_Bone( m_midRearRightTireBone );
			getRenderObject()->Control_Bone( m_midRearRightTireBone, wheelXfrm );	
		}
		if (m_midMidLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearLeftHeightOffset);
			getRenderObject()->Capture_Bone( m_midMidLeftTireBone );
			getRenderObject()->Control_Bone( m_midMidLeftTireBone, wheelXfrm );
            if(m_secondaryMidMidLeftTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryMidMidLeftTireBone);
                getRenderObject()->Control_Bone(m_secondaryMidMidLeftTireBone,wheelXfrm);
            }	

			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearRightHeightOffset);
			getRenderObject()->Capture_Bone( m_midMidRightTireBone );
			getRenderObject()->Control_Bone( m_midMidRightTireBone, wheelXfrm );
            if(m_secondaryMidMidRightTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryMidMidRightTireBone);
                getRenderObject()->Control_Bone(m_secondaryMidMidRightTireBone,wheelXfrm);
            }	
		}
	}


    ((W3DTankTruckDraw *)this)->enableEmitters(false);
    m_wasAirborne=(unsigned char)obj->isSignificantlyAboveTerrain();
}

inline const TWheelInfo *Drawable::getWheelInfo() const { return m_locoInfo ? reinterpret_cast<const TWheelInfo *>(reinterpret_cast<const unsigned char *>(m_locoInfo)+0x3c) : 0; }
