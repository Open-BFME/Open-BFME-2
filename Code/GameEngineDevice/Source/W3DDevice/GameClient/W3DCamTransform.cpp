// cl: /I. /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// W3DCamTransform::transitionLiveMode
// ?transitionLiveMode@W3DCamTransform@@QAEXPAVVector3@@0PAVView@@@Z
// retail 0x00102B83..0x00102F83 (1024B), thiscall ret 0xC; sole caller is the
// W3DView camera update near 0x00103A6F, which passes the view as the third
// argument.
//
// Live-camera transition state machine (state at +0x28, target at +0x2C and
// position at +0x38). The current live mode name (global AsciiString
// 0x00DEC290) selects "Target" (2) or "Zoom" (3). Losing the controlled object
// (view +0xA4) resets the timers and the state. State 2 eases the target
// towards the object with an accelerating zoom timer, state 3 eases both target
// and position (after a screen-centre terrain query on TheTacticalView) and
// states 0, 1 and 4 hand over between them; reaching state 3 in the requested
// mode sets the view's +0xB4 / +0xB8 pair to 16 / 2.
//
// Evidence (target): WorldBuilder twin 0x7E73D0 is
// W3DCamTransform::transitionLiveMode in W3DCamTransform.cpp (asserts
// "W3DView-TransitionLiveCamera - no controlled object" at lines 529 and 569)
// and inlines Vector3::Lerp; two guarded static Vector3s (the second unused in
// retail), four zero-initialised static timers and four tuning statics
// (0.5 / 0.05 and 0.4 / 0.03). Callees StringBase::compare(text) 0x000069B1 and
// GameLogic::findObjectByID 0x00049DC5 (rowed).
//
// Shape note: the reset's self-select store of targetT (this ? 0 : 0) is what
// gives cl retail's register colouring of the cached zoom/target speeds
// (xmm1/xmm2) and its store order; every plainer spelling swaps the two.

#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

#include "Code/Libraries/Include/Lib/ICoord2D.h"

// A used scalar aggregate keeps each arithmetic result in its native memory
// home and preserves the compiler's scheduling regions. This is a codegen
// adaptation, not a claim that this helper type occurred in the original.
struct CameraScalar
{
    float value;
    CameraScalar(float scalarValue) : value(scalarValue) {}
};
static __forceinline CameraScalar addCameraScalar(float a, float b)
{
    return CameraScalar(a + b);
}
class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	Vector3() {}
    Vector3(float x,float y,float z):X(x),Y(y),Z(z) {}
	Vector3(const Vector3 &sourceVector)
	{
		X = sourceVector.X;
		Y = sourceVector.Y;
		Z = sourceVector.Z;
	}

	Vector3 &operator=(const Coord3D &that)
	{
		X = that.x;
		Y = that.y;
		Z = that.z;
		return *this;
	}

	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}

	void Set(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	__forceinline Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	__forceinline Vector3 &operator-=(const Vector3 &v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
	__forceinline Vector3 &operator*=(float k) { X = X*k; Y=Y*k; Z=Z*k; return *this; }
	__forceinline friend Vector3 operator-(const Vector3 &a,const Vector3 &b) { return Vector3(a.X-b.X,a.Y-b.Y,a.Z-b.Z); }
	__forceinline float Length2() const { return X*X + Y*Y + Z*Z; }
	__forceinline float Length() const;
	static __forceinline float Distance(const Vector3 &p1, const Vector3 &p2);
	static __forceinline void Lerp(const Vector3 &startVector, const Vector3 &endVector, Real alpha, Vector3 *set_result)
	{
		set_result->X = (startVector.X + (endVector.X - startVector.X) * alpha);
		set_result->Y = (startVector.Y + (endVector.Y - startVector.Y) * alpha);
		set_result->Z = (startVector.Z + (endVector.Z - startVector.Z) * alpha);
	}
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
    unsigned char cameraKindFlags() const {return *((const unsigned char*)m_template+0x109);}
private:
	unsigned char m_pad00[4];
    const void *m_template; // native +4
    unsigned char m_pad08[0x38-8];
	Coord3D m_pos;					// +0x38
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class View
{
public:
	PAD_VIRTUALS10(v0) PAD_VIRTUALS10(v1) PAD_VIRTUALS10(v2) PAD_VIRTUALS10(v3) PAD_VIRTUALS10(v4)
	PAD_VIRTUALS10(v5) PAD_VIRTUALS10(v6) PAD_VIRTUALS10(v7) PAD_VIRTUALS10(v8)
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);	// slot 90

	unsigned char m_pad004[0x9C - 0x04];
	Bool m_9c;					// +0x9C
	unsigned char m_pad09d[0xA4 - 0x9D];
	ObjectID m_cameraLock;				// +0xA4
	unsigned char m_pad0a8[0xB4 - 0xA8];
	Int m_b4;					// +0xB4
	Int m_b8;					// +0xB8
	Int m_width;					// +0xBC
	Int m_height;					// +0xC0
};

extern View *TheTacticalView;
extern GameLogic *TheGameLogic;
// Retail's run opens with this unit's Drawable.h copy 0x007ACA9A, its static 0x00DEC28C just
// before the camera mode name (LINK-236). The unit's private Matrix3D and Thing views keep the
// canonical Drawable.h out, so it takes Drawable.h's one dynamic constant on its own.
#include "Code/GameEngine/Include/GameClient/DrawableFramesPerFlash.h"

// The live camera mode name; "Zoom" until a script sets another. Retail builds it in this
// unit's .text$yc run (0x007ACAAA, after the unit's Drawable.h copy 0x007ACA9A and before its
// pool-init marker 0x007ACAC5) through the out-of-line AsciiString(const char *) 0x0000654A.
// Descriptive name; the original is unknown.
#pragma inline_depth( 0 )
AsciiString BfmeLiveCameraModeNameStorage("Zoom");
#pragma inline_depth()

#include <math.h>
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/wwmath.h"
__forceinline float Vector3::Length() const { return WWMath::Sqrt(Length2()); }
__forceinline float Vector3::Distance(const Vector3 &p1, const Vector3 &p2) { Vector3 displacement; displacement = p1 - p2; return (displacement.Length()); }
// Reduced donor math view: formulas from GeneralsMD WWMath/matrix3d.h.
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
class Matrix3D {
public:
    Vector4 Row[3];
    Matrix3D() {}
    explicit Matrix3D(bool init) {if(init)Make_Identity();}
    __forceinline Matrix3D(const Vector3 &rotationAxis, float angle) {
        float cosine = cosf(angle);
        float s = sinf(angle);
        Row[0].Set(
            (float)(rotationAxis.X*rotationAxis.X + cosine*(1.0f - rotationAxis.X*rotationAxis.X)),
            (float)(rotationAxis.X*rotationAxis.Y*(1.0f - cosine) - rotationAxis.Z*s),
            (float)(rotationAxis.Z*rotationAxis.X*(1.0f - cosine) + rotationAxis.Y*s),
            0.0f);
        Row[1].Set(
            (float)(rotationAxis.X*rotationAxis.Y*(1.0f - cosine) + rotationAxis.Z*s),
            (float)(rotationAxis.Y*rotationAxis.Y + cosine*(1.0f - rotationAxis.Y*rotationAxis.Y)),
            (float)(rotationAxis.Y*rotationAxis.Z*(1.0f - cosine) - rotationAxis.X*s),
            0.0f);
        Row[2].Set(
            (float)(rotationAxis.Z*rotationAxis.X*(1.0f - cosine) - rotationAxis.Y*s),
            (float)(rotationAxis.Y*rotationAxis.Z*(1.0f - cosine) + rotationAxis.X*s),
            (float)(rotationAxis.Z*rotationAxis.Z + cosine*(1 - rotationAxis.Z*rotationAxis.Z)),
            0.0f);
    }
    __forceinline Matrix3D &operator=(const Matrix3D &m) {
        Row[0]=m.Row[0];Row[1]=m.Row[1];Row[2]=m.Row[2];return *this;
    }
    __forceinline void Make_Identity() {
        Row[0][0]=1; Row[0][1]=0; Row[0][2]=0; Row[0][3]=0;
        Row[1][0]=0; Row[1][1]=1; Row[1][2]=0; Row[1][3]=0;
        Row[2][0]=0; Row[2][1]=0; Row[2][2]=1; Row[2][3]=0;
    }
    void Look_At(const Vector3 &,const Vector3 &,float);
    __forceinline void mulVector3(Vector3 &inputVector) const {
        float x=Row[0][0]*inputVector.X+Row[0][1]*inputVector.Y+Row[0][2]*inputVector.Z+Row[0][3];
        float y=Row[1][0]*inputVector.X+Row[1][1]*inputVector.Y+Row[1][2]*inputVector.Z+Row[1][3];
        float z=Row[2][0]*inputVector.X+Row[2][1]*inputVector.Y+Row[2][2]*inputVector.Z+Row[2][3];
        inputVector.Set(x,y,z);
    }
    __forceinline void mulCameraAngleVector(Vector3 &inputVector) const {
        float x=Row[0][0]*inputVector.X+Row[0][1]*inputVector.Y+Row[0][2]*inputVector.Z+Row[0][3];
        float y=(Row[1][0]*inputVector.X+Row[1][1]*inputVector.Y)+Row[1][2]*inputVector.Z+Row[1][3];
        float z=(Row[2][0]*inputVector.X+Row[2][1]*inputVector.Y)+Row[2][2]*inputVector.Z+Row[2][3];
        inputVector.Set(x,y,z);
    }
    __forceinline void Rotate_X(float theta) {
	float originalY,tmp2;
	float s,cosine;
	s = sinf(theta);
	cosine = cosf(theta);
	originalY = Row[0][1]; tmp2 = Row[0][2];
	Row[0][1] = (float)( cosine*originalY + (s*tmp2));
	Row[0][2] = (float)(-s*originalY + cosine*tmp2);
	originalY = Row[1][1]; tmp2 = Row[1][2];
	Row[1][1] = (float)( cosine*originalY + (s*tmp2));
	Row[1][2] = (float)(-s*originalY + cosine*tmp2);
	originalY = Row[2][1]; tmp2 = Row[2][2];
	Row[2][1] = (float)( cosine*originalY + (s*tmp2));
	Row[2][2] = (float)(-s*originalY + cosine*tmp2);
    }
    __forceinline void Rotate_Y(float theta) {
	float originalX,originalZ;
	float s,cosine;
	s = sinf(theta);
	cosine = cosf(theta);
	originalX = Row[0][0]; originalZ = Row[0][2];
	Row[0][0] = (float)(cosine*originalX - s*originalZ);
	Row[0][2] = (float)(s*originalX + cosine*originalZ);
	originalX = Row[1][0]; originalZ = Row[1][2];
	Row[1][0] = (float)(cosine*originalX - s*originalZ);
	Row[1][2] = (float)(s*originalX + cosine*originalZ);
	originalX = Row[2][0]; originalZ = Row[2][2];
	Row[2][0] = (float)(cosine*originalX - s*originalZ);
	Row[2][2] = (float)(s*originalX + cosine*originalZ);
    }
    __forceinline void Rotate_Y(float s,float cosine)
{
	float originalX,originalZ;

	originalX = Row[0][0]; originalZ = Row[0][2];
	Row[0][0] = (float)(cosine*originalX - s*originalZ);
	Row[0][2] = (float)(s*originalX + cosine*originalZ);

	originalX = Row[1][0]; originalZ = Row[1][2];
	Row[1][0] = (float)(cosine*originalX - s*originalZ);
	Row[1][2] = (float)(s*originalX + cosine*originalZ);

	originalX = Row[2][0]; originalZ = Row[2][2];
	Row[2][0] = (float)(cosine*originalX - s*originalZ);
	Row[2][2] = (float)(s*originalX + cosine*originalZ);
}
    __forceinline void Rotate_Z(float theta) {
	float originalX,originalY;
	float cosine,s;
	cosine = cosf(theta);
	s = sinf(theta);
	originalX = Row[0][0]; originalY = Row[0][1];
	Row[0][0] = (float)( cosine*originalX + s*originalY);
	Row[0][1] = (float)(-s*originalX + cosine*originalY);
	originalX = Row[1][0]; originalY = Row[1][1];
	Row[1][0] = (float)( cosine*originalX + s*originalY);
	Row[1][1] = (float)(-s*originalX + cosine*originalY);
	originalX = Row[2][0]; originalY = Row[2][1];
	Row[2][0] = (float)( cosine*originalX + s*originalY);
	Row[2][1] = (float)(-s*originalX + cosine*originalY);
    }
};
class CameraAnimation {public:virtual void slot0();virtual void slot1();virtual void getTransform(Matrix3D *);};
class Rva0010274F {
public:
    Matrix3D *transform; float distance;
    Vector3 source,target,shakerAngles;
    float groundLevel,zoom,angle,pitch,roll,fov,finalRotation,targetZAdjustment;
    Coord3D pos,previousPos,explicitTarget;
    float shakeX,shakeY;
    bool constraintValid; char pad79[3];
    float minX,minY,maxX,maxY;
    bool realZoom; char pad8d[3]; Vector3 offset;
    bool liveCamera; char pad9d[3]; float fxPitch; ObjectID lock;
    bool positionHold,retainHold,slaved;char padab;
    AsciiString slaveName,boneName;
    char padb4[0xd0-0xb4]; bool special,padd1,nearAdjust,padd3;
    int mode; CameraAnimation *animation; float animationValue;
};
class CameraShakeSystemClass {public:void Update_Camera_Shaker(Vector3,Vector3 *);};
class Rva0065CA4 {public:void rva00065E3C(float);};
extern CameraShakeSystemClass CameraShakerSystem;
#include "Code/GameEngine/Include/GameClient/Display.h"
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class Rva00358752Opaque {public:Object *lookupUnitByValue(AsciiString);};
#include "../../../../GameEngine/Include/Common/Rva002B224BDwordField.h"
class Drawable;
class Thing {public:Drawable *getDrawable() const;};
class ObjectDrawInterface {public:virtual void slot0();virtual void slot1();virtual bool boneTransform(const AsciiString &,Matrix3D *)const;};
#include "../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

class Rva00102F83Owner { public: void rva00102F83(Rva0010274F *); };

class W3DCamTransform
{
public:
	void transitionLiveMode(Vector3 *pos, Vector3 *target, View *view);
    friend class Rva00102F83Owner;
private:
	unsigned char m_pad00[0x0c];
    Vector3 m_cameraSource; // +0x0c
    char m_pad18[2]; bool m_cameraFlag; // +0x1a
    char m_pad1b[0x28-0x1b];
	Int m_liveState;				// +0x28
	Vector3 m_liveTarget;				// +0x2C
	Vector3 m_livePos;				// +0x38
};

static __forceinline const AsciiString &liveModeName()
{
	return BfmeLiveCameraModeNameStorage;
}

void W3DCamTransform::transitionLiveMode(Vector3 *pos, Vector3 *target, View *view)
{
	static Vector3 startPos;
	static Vector3 unusedPos;
	static Real zoomProgress = 0.0f;
	static Real zoomSpeed = 0.0f;
	static Real targetProgress = 0.0f;
	static Real targetSpeed = 0.0f;
	static Real targetMaxSpeed = 0.5f;
	static Real targetAccel = 0.05f;
	static Real zoomMaxSpeed = 0.4f;
	static Real zoomAccel = 0.03f;

	Int liveMode = -1;
	if (liveModeName().compare("Target") == 0)
		liveMode = 2;
	else if (liveModeName().compare("Zoom") == 0)
		liveMode = 3;

	Object *controlledObject = TheGameLogic->findObjectByID(view->m_cameraLock);
	if (!controlledObject)
	{
		zoomProgress = 0.0f;
		zoomSpeed = 0.0f;
		targetProgress = this ? 0.0f : 0.0f;
		targetSpeed = 0.0f;
		m_liveState = 0;
	}

	if (!view->m_9c)
	{
		m_liveTarget = *target;
		m_livePos = *pos;
	}

	switch (m_liveState)
	{
		case 0:
			if (view->m_9c)
			{
				m_liveState = 3;
				if (liveMode == m_liveState)
				{
					startPos = m_livePos;
					view->m_b4 = 16;
					view->m_b8 = 2;
				}
			}
			break;

		case 1:
			if (!view->m_9c)
				m_liveState = 4;
			break;

		case 2:
		{
			zoomProgress += zoomSpeed;
			if (zoomSpeed < zoomMaxSpeed)
				zoomSpeed += zoomAccel;

			Object *lockObj = TheGameLogic->findObjectByID(view->m_cameraLock);
			Vector3 objPos;
			objPos.Set(lockObj->getPosition()->x, lockObj->getPosition()->y, lockObj->getPosition()->z);
			Vector3::Lerp(m_liveTarget, objPos, zoomProgress, target);
			*pos = m_livePos;
			if (zoomProgress >= 1.0f)
			{
				m_liveState = 3;
				zoomProgress = 0.0f;
				zoomSpeed = 0.0f;
				startPos = m_livePos;
				if (liveMode == m_liveState)
				{
					view->m_b4 = 16;
					view->m_b8 = 2;
				}
			}
			break;
		}

		case 3:
		{
			Real maxSpeed = targetMaxSpeed;
			Real accel = targetAccel;
			targetProgress += targetSpeed;
			if (targetSpeed < maxSpeed)
				targetSpeed += accel;

			if (targetProgress < 0.9f)
			{
				Object *lockObj = TheGameLogic->findObjectByID(view->m_cameraLock);
				Vector3 objPos;
				objPos.Set(lockObj->getPosition()->x, lockObj->getPosition()->y, lockObj->getPosition()->z);
				Coord3D terrainPosition;
				ICoord2D screenCenter;
				screenCenter.x = view->m_width / 2;
				screenCenter.y = view->m_height / 2;
				TheTacticalView->screenToTerrain(&screenCenter, &terrainPosition, false);
				Vector3::Lerp(m_liveTarget, objPos, targetProgress, target);
				Vector3::Lerp(startPos, m_liveTarget, targetProgress, pos);
			}
			else
			{
				m_liveState = 1;
				targetProgress = 0.0f;
				targetSpeed = 0.0f;
				view->m_b4 = 0;
				view->m_b8 = 0;
			}
			break;
		}

		case 4:
			m_liveState = 0;
			break;
	}
}

// Whole native 0x00102F83..0x0010404E, 4299 bytes, RET4.
// ?rva00102F83@Rva00102F83Owner@@QAEXPAVRva0010274F@@@Z
// Target evidence: W3DView caller passes its camera state at +0xC0 and a
// 0xE0 descriptor. WorldBuilder supplies the camera flow and local lifetimes;
// GeneralsMD supplies the vector/matrix formulas. The established neutral
// entry and descriptor symbols are retained. Identity: enclosing camera state;
// original entry-point/descriptor names are not independently established.
// The scalar-value helper preserves separate pitch arms and native stores.
static __forceinline void pitchCamera(Vector3 &s,const Vector3 &targetPosition,float p) {s.X=CameraScalar((s.X-targetPosition.X)/p).value+targetPosition.X;s.Y=CameraScalar((s.Y-targetPosition.Y)/p).value+targetPosition.Y;}
class Rva0010274F;static __forceinline Vector3 translated(Vector3 p,const Rva0010274F *v);
static __forceinline Vector3 translated(Vector3 p,const Rva0010274F *cameraState) {p.X+=cameraState->pos.x;p.Y+=cameraState->pos.y;return p;}
__forceinline float cameraMin(float a,float b) {return a<b?a:b;}
__forceinline float cameraMax(float a,float b) {return a>b?a:b;}
/** @todo This is inefficient. We should construct the matrix directly using vectors. */
void Rva00102F83Owner::rva00102F83(Rva0010274F *cameraState)
{
    Vector3 sourcePos,targetPos;
    if(cameraState->mode==4) {
        if(cameraState->animation) {
            struct AnimatedTransform {Matrix3D tm;float value;} result;
            cameraState->animation->getTransform(&result.tm);
            *cameraState->transform=result.tm; cameraState->animationValue=result.value; return;
        }
        cameraState->mode=0;
    }
    // add in the camera shake, if any
    cameraState->pos.x+=cameraState->shakeX;cameraState->pos.y+=cameraState->shakeY;
    if(cameraState->mode==2) {
        sourcePos=cameraState->pos;
        if(cameraState->explicitTarget.lengthSqr()==0.0f) {targetPos=sourcePos;targetPos.Z=0;}
        else targetPos.Set(cameraState->explicitTarget.x,cameraState->explicitTarget.y,cameraState->explicitTarget.z);
        cameraState->transform->Make_Identity();cameraState->transform->Look_At(sourcePos,targetPos,cameraState->roll); return;
    }
    if(cameraState->constraintValid) {
        {float x=cameraMax(cameraState->minX,cameraState->pos.x); cameraState->pos.x=x;
        cameraState->pos.x=cameraMin(cameraState->maxX,x);}
        cameraState->pos.y=cameraMax(cameraState->minY,cameraState->pos.y);
        cameraState->pos.y=cameraMin(cameraState->maxY,cameraState->pos.y);
    }
    // set position of camera itself
    if(cameraState->realZoom) {
        sourcePos=cameraState->offset;
        float capped=cameraState->zoom;
        if(capped>1.0f)capped=1.0f;
        if(capped<0.5f)capped=0.5f;
        cameraState->fov=0.87266463f*capped;
    } else {
        sourcePos.X=cameraState->offset.X*cameraState->zoom;sourcePos.Y=cameraState->offset.Y*cameraState->zoom;sourcePos.Z=cameraState->offset.Z*cameraState->zoom;
        if(cameraState->liveCamera) {
            Object *object=TheGameLogic->findObjectByID(cameraState->lock);
            if(object) sourcePos.Z=(cameraState->offset.Z+object->getPosition()->z)*cameraState->zoom;
        }
    }
    // camera looking at origin
    targetPos.Set(0,0,0);
    float groundFraction=cameraState->groundLevel/sourcePos.Z;
    float aboveGroundFraction=CameraScalar((float)(1.0-groundFraction)).value;
    // construct a matrix to rotate around the up vector by the given angle
    Matrix3D angleTransform(Vector3(0,0,1),cameraState->angle);
    // construct a matrix to rotate around the horizontal vector by the given angle
    Matrix3D pitchTransform(Vector3(1,0,0),cameraState->pitch);
    // rotate camera position (pitch, then angle)
    pitchTransform.mulVector3(sourcePos); angleTransform.mulCameraAngleVector(sourcePos);
    sourcePos *= aboveGroundFraction;
    // translate to current XY position
    sourcePos.X=addCameraScalar(sourcePos.X,cameraState->pos.x).value;
    sourcePos.Y=addCameraScalar(sourcePos.Y,cameraState->pos.y).value;
    targetPos.X=addCameraScalar(targetPos.X,cameraState->pos.x).value;
    targetPos.Y=addCameraScalar(targetPos.Y,cameraState->pos.y).value;
    Object *object=cameraState->liveCamera?TheGameLogic->findObjectByID(cameraState->lock):0;
    if(cameraState->liveCamera && (!object || (object->cameraKindFlags()&0x10))) {
        Matrix3D angleTransform2(Vector3(0,0,1),cameraState->angle);
        Matrix3D pitchTransform2(Vector3(1,0,0),cameraState->pitch);
        pitchTransform2.mulVector3(sourcePos);angleTransform2.mulCameraAngleVector(sourcePos);
        sourcePos=translated(sourcePos,cameraState);
        sourcePos.Z=addCameraScalar(sourcePos.Z,cameraState->pos.z).value;
        targetPos.X=addCameraScalar(targetPos.X,cameraState->pos.x).value;
        targetPos.Y=addCameraScalar(targetPos.Y,cameraState->pos.y).value;
        targetPos.Z+=cameraState->pos.z+cameraState->targetZAdjustment;
    } else {
        sourcePos.Z+=cameraState->groundLevel;
        targetPos.Z+=cameraState->groundLevel+cameraState->targetZAdjustment;
    }
    // The following code moves camera down and pitch up when player zooms in.
    // Use scripts to switch to useRealZoomCam
    if(cameraState->realZoom) {
        float pitchAdjust=1.0f;
        if(!TheDisplay->slot88()) {
            float capped=cameraState->zoom;
            if(capped>1.0f)capped=1.0f;
            if(capped<0.5f)capped=0.5f;
            sourcePos.Z*=capped*0.75f+0.25f; // move camera down physically
            pitchAdjust=capped; // adjust camera to pitch up
        }
        cameraState->fxPitch=1.0f*(0.25f+pitchAdjust*0.75f);
        pitchCamera(sourcePos,targetPos,cameraState->fxPitch);
    } else if(cameraState->fxPitch <= 1.0f || cameraState->liveCamera) {
        if(cameraState->liveCamera) {
        if(reinterpret_cast<W3DCamTransform *>(this)->m_cameraFlag)reinterpret_cast<W3DCamTransform *>(this)->m_cameraFlag=false;
        reinterpret_cast<W3DCamTransform *>(this)->m_cameraSource=sourcePos;
        Vector3 targetGroundProjection=targetPos; targetGroundProjection.Z=0;
        Vector3 sourceGroundProjection=sourcePos; sourceGroundProjection.Z=0;
        float distance=Vector3::Distance(targetGroundProjection,sourceGroundProjection);
        float height=tan(cameraState->fxPitch)*distance;
        targetPos.Z=sourcePos.Z-height;
        } else {
            float height=sourcePos.Z-targetPos.Z; height*=cameraState->fxPitch;targetPos.Z=sourcePos.Z-height;
        }
    } else {
        sourcePos.X=(sourcePos.X-targetPos.X)/cameraState->fxPitch+targetPos.X;
        sourcePos.Y=(sourcePos.Y-targetPos.Y)/cameraState->fxPitch+targetPos.Y;
    }
    if(cameraState->positionHold) {
        Vector3 delta=cameraState->source-sourcePos;
        sourcePos=cameraState->source;
        targetPos.X+=delta.X;targetPos.Y+=delta.Y;targetPos.Z+=delta.Z;
        cameraState->pos=cameraState->previousPos;cameraState->pos.x+=delta.X;cameraState->pos.y+=delta.Y;cameraState->previousPos=cameraState->pos;
        if(!cameraState->retainHold)cameraState->positionHold=false;
    }
    cameraState->source=sourcePos;cameraState->target=targetPos;
    Vector3 delta=cameraState->source;
    delta-=cameraState->target;
    cameraState->distance=WWMath::Sqrt(((delta.X*delta.X) + delta.Z*delta.Z) + delta.Y*delta.Y);
    if(!cameraState->special) reinterpret_cast<W3DCamTransform *>(this)->transitionLiveMode(&sourcePos,&targetPos,(View*)cameraState);
    if(cameraState->explicitTarget.lengthSqr()>0)targetPos.Set(cameraState->explicitTarget.x,cameraState->explicitTarget.y,cameraState->explicitTarget.z);
    // build new camera transform
    cameraState->transform->Make_Identity();cameraState->transform->Look_At(sourcePos,targetPos,cameraState->roll);
    if(!cameraState->special) {
        //WST 11/12/2002 New camera shaker system
        ((Rva0065CA4 *)*(CameraShakeSystemClass**)&CameraShakerSystem)->rva00065E3C(1.0f/30.0f);
        (*(CameraShakeSystemClass**)&CameraShakerSystem)->Update_Camera_Shaker(sourcePos,&cameraState->shakerAngles);
        cameraState->transform->Rotate_X(cameraState->shakerAngles.X);
        cameraState->transform->Rotate_Y(cameraState->shakerAngles.Y);
        cameraState->transform->Rotate_Z(cameraState->shakerAngles.Z);
    }
    // (gth) check if the camera is being controlled by an animation
    if(cameraState->slaved) {
        // find object named m_cameraSlaveObjectName
        Object *slave=((Rva00358752Opaque*)TheScriptEngine)->lookupUnitByValue(cameraState->slaveName);
        if(slave) {
            // dig out the drawable
            Drawable *drawable=((Thing*)slave)->getDrawable();
            if(drawable) {
                // dig out the first drawable module with an ObjectDrawInterface
                DrawModule **modules=(DrawModule**)((Rva002B224BDwordField*)drawable)->get();
                for(;*modules;++modules) {
                    const ObjectDrawInterface *drawInterface=(*modules)->getObjectDrawInterface();
                    if(drawInterface) {
                        // Ok, slam it into the camera!
                        Matrix3D tm(false);drawInterface->boneTransform(cameraState->boneName,&tm);*cameraState->transform=tm;
                        // WST 10.22.2002. Update the Listener positions used by audio system
                        Matrix3D *transform=cameraState->transform; Coord3D origin; origin.x=transform->Row[0][3]; origin.y=transform->Row[1][3]; origin.z=transform->Row[2][3]; cameraState->previousPos=origin; break;
                    }
                }
            } else cameraState->slaved=false;
        } else cameraState->slaved=false;
    }
    float finalAngle=cameraState->finalRotation;
    Matrix3D *finalTransform=cameraState->transform;
    float finalSin=sinf(finalAngle);
    float finalCos=cosf(finalAngle);
    finalTransform->Rotate_Y(finalSin,finalCos);
    if(cameraState->special&&cameraState->nearAdjust) {
        sourcePos.X=targetPos.X+(sourcePos.X-targetPos.X)/(90.0f+cameraState->fxPitch);
        sourcePos.Y=targetPos.Y+(sourcePos.Y-targetPos.Y)/(90.0f+cameraState->fxPitch);
        cameraState->transform->Look_At(sourcePos,targetPos,0);
        cameraState->source=sourcePos;cameraState->target=targetPos;
    }
}

// Target Z updates are kept inside their WB-proven live/non-live arms.
// Full native extent and every relocation verified; see the landing evidence.
