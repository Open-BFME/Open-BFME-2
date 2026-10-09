// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// Native [000CE3E3,000CE6E6),771B, RET4. W3DTankDraw::doDrawModule, the Zero
// Hour W3DTankDraw.cpp body adapted to BFME 2: the speed comes from the
// object's 0x0028AC7D accessor, the tread turning state and drive speed from
// the AI update (+0x258) and its +0x1F0 companion, and the treads scroll
// without the ZH isMotive test. Debris emitters are the +0x2E8/+0x2F4
// particle-system handles (null handle -> Make001FCBD7). Early outs skip
// the W3DModelDraw::doDrawModule (0x000C7BC4) tail call exactly as retail.

#include <math.h>

#include "Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

class Matrix3D;
class ParticleSystem;
ParticleSystem *Make001FCBD7();

struct ParticleSystemView
{
	unsigned char m_pad000[0x130];
	Coord3D m_velocityMultiplier;
	Real m_burstCountMultiplier;
};

struct BfmeParticleSystemHandle
{
	ParticleSystem *volatile m_system;
	void *m_prev;
	void *m_next;
	ParticleSystemView *operator->()
	{
		ParticleSystem *p = m_system;
		if (!p)
			p = Make001FCBD7();
		return (ParticleSystemView *)p;
	}
};

class View
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27();
	virtual void vf28(); virtual void vf29();
	virtual Bool isCameraMovementFinished(void);	// slot 30 (+0x78)
	virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34();
	virtual void vf35(); virtual void vf36(); virtual void vf37(); virtual void vf38();
	virtual void vf39(); virtual void vf40(); virtual void vf41(); virtual void vf42();
	virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46();
	virtual void vf47(); virtual void vf48(); virtual void vf49(); virtual void vf50();
	virtual void vf51(); virtual void vf52(); virtual void vf53();
	virtual Bool isTimeFrozen(void);	// slot 54 (+0xD8)
};
extern View *TheTacticalView;

class Rva00203B08
{
public:
	bool rva0020424FF();
};

class Rva00203ACEByteField
{
public:
	unsigned char get() const;
};

extern Rva00203B08 *TheScriptEngine;

class Rva00270260
{
public:
	bool rva00270260();
};

class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &dir) const;
};

class Rva002627E8
{
public:
	Real rva002627E8() const;
};

struct TurnStateView
{
	unsigned char m_pad000[0xA8];
	Int m_turning;
};

struct AIUpdateView
{
	unsigned char m_pad000[0x1F0];
	TurnStateView *m_turnState;
};

class Object : public Thing
{
public:
	Real rva0028AC7D() const;

	unsigned char m_pad000[0x258];
	AIUpdateView *m_ai;
	void *m_physics;
};

struct DrawableView
{
	unsigned char m_pad000[0xFC];
	Object *m_object;
};

struct W3DTankDrawModuleData
{
	unsigned char m_pad000[0x190];
	Real m_treadAnimationRate;
	Real m_treadPivotSpeedFraction;
	Real m_treadDriveSpeedFraction;
};

struct Vector2
{
	Real X;
	Real Y;
	void Set(Real x, Real y) { X = x; Y = y; }
};

struct TreadObjectInfo
{
	void *m_robj;
	Int m_type;
	Int m_structID;
	Vector2 m_customUVOffset;
};

class W3DTankTruckDraw
{
	friend class W3DTankDraw;
protected:
	void updateTreadPositions(Real uvDelta);
};

class W3DModelDraw
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27();
	virtual void vf28(); virtual void vf29(); virtual void vf30(); virtual void vf31();
	virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
	virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39();
	virtual void vf40(); virtual void vf41(); virtual void vf42(); virtual void vf43();
	virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
	virtual void vf48();
	virtual void *getRenderObject(void);	// slot 49 (+0xC4)
	virtual void doDrawModule(const Matrix3D *transformMtx);
	const W3DTankDrawModuleData *getW3DTankDrawModuleData() const { return m_moduleData; }

protected:
	const W3DTankDrawModuleData *m_moduleData;
	DrawableView *m_drawable;
	unsigned char m_pad00C[0x49 - 0x0C];
	Bool m_fullyObscuredByShroud;
	unsigned char m_pad04A[0x2E8 - 0x4A];
};

class W3DTankDraw : public W3DModelDraw
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);
	void rva000CE09E();
	void rva000CE0EA();

protected:
	void updateTreadObjects(void);

	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
	void *m_prevRenderObj;
	TreadObjectInfo m_treads[4];
	Int m_treadCount;
	Coord3D m_lastDirection;
};

// ?doDrawModule@W3DTankDraw@@UAEXPBVMatrix3D@@@Z
void W3DTankDraw::doDrawModule(const Matrix3D *transformMtx)
{
	const Real DEBRIS_THRESHOLD = 0.00001f;

	if (TheTacticalView->isTimeFrozen() && !TheTacticalView->isCameraMovementFinished())
		return;
	if (TheScriptEngine->rva0020424FF())
		return;
	if (((Rva00203ACEByteField *)TheScriptEngine)->get())
		return;
	if (getRenderObject() == 0)
		return;
	if (getRenderObject() != m_prevRenderObj)
		updateTreadObjects();

	Object *obj = m_drawable->m_object;
	if (obj == 0)
		return;
	if (obj->m_physics == 0)
		return;

	Real velMag = obj->rva0028AC7D();
	if (velMag > DEBRIS_THRESHOLD && !((Rva00270260 *)m_drawable)->rva00270260() && !m_fullyObscuredByShroud)
		rva000CE09E();
	else
		rva000CE0EA();

	Coord3D velMult;
	velMag = (Real)sqrt(velMag);
	velMult.x = 0.5f * velMag + 0.1f;
	if (velMult.x > 1.0f)
		velMult.x = 1.0f;
	velMult.y = velMult.x;
	velMult.z = velMag + 0.1f;
	if (velMult.z > 1.0f)
		velMult.z = 1.0f;

	if (m_treadDebrisLeft.m_system) {
		m_treadDebrisLeft->m_velocityMultiplier = velMult;
		m_treadDebrisLeft->m_burstCountMultiplier = velMult.z;
	}
	if (m_treadDebrisRight.m_system) {
		m_treadDebrisRight->m_velocityMultiplier = velMult;
		m_treadDebrisRight->m_burstCountMultiplier = velMult.z;
	}

	if (m_treadCount) {
		AIUpdateView *ai = obj->m_ai;
		TurnStateView *turnState = ai ? ai->m_turnState : 0;
		if (turnState == 0)
			return;
		Int turn = turnState->m_turning;
		Real treadScrollSpeed = getW3DTankDrawModuleData()->m_treadAnimationRate;
		Real maxSpeed = ((Rva002627E8 *)ai)->rva002627E8();
		if (turn != 0 && obj->rva0028AC7D() / maxSpeed < getW3DTankDrawModuleData()->m_treadPivotSpeedFraction) {
			Coord3D dir;
			obj->getUnitDirectionVector2D(dir);
			Real angleToGoal = dir.x * m_lastDirection.x + dir.y * m_lastDirection.y;
			if (fabs(1.0f - angleToGoal) > 0.00001f) {
				if (turn == -1)
					((W3DTankTruckDraw *)this)->updateTreadPositions(-treadScrollSpeed);
				else
					((W3DTankTruckDraw *)this)->updateTreadPositions(treadScrollSpeed);
			}
			m_lastDirection = dir;
		} else if (obj->rva0028AC7D() / maxSpeed >= getW3DTankDrawModuleData()->m_treadDriveSpeedFraction) {
			TreadObjectInfo *pTread = m_treads;
			for (Int i = 0; i < m_treadCount; i++) {
				Real offset_u = pTread->m_customUVOffset.X - treadScrollSpeed;
				offset_u = offset_u - (Real)floor(offset_u);
				pTread->m_customUVOffset.Set(offset_u, 0);
				pTread++;
			}
		}
	}
	W3DModelDraw::doDrawModule(transformMtx);
}
