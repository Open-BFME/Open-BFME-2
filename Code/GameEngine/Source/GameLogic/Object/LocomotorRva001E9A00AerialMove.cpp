// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva001E9A00@Locomotor@@QAE_NPAVObject@@MPAMPAVRva00375A73Context@@@Z,
// retail 0x001E9A00..0x001EA05B (1627 bytes, __EH_prolog frame, ret 0x10).
// One aerial (spline-path) movement step: copies the object's transform into
// the locomotor's matrix at +0x68, advances the path distance by the flying
// AI's speed, samples TheAerialPathfinder ahead and behind for pitch and
// heading, blends the turn rate, re-yaws through 0x001E41FA, adjusts speed by
// accel/brake/pitch with max/min clamps, keeps the matrix above terrain plus a
// quarter of the geometry's +0x14 extent, drives model condition bits 61, 72
// and 103 and sets the next position. Returns true only when the path query
// fails (after clearing the three bits).
// Evidence: WorldBuilder twin 0xAE19A0 (debug, 9032 bytes) has the same call
// sequence, constants (70*70, PI, 3, 0.8/0.2, 4, -1, 1.5, 0.4, 0.25, 0.3,
// -0.6) and model-condition helpers; the receiver is the Locomotor (its this
// is passed to the rowed Locomotor::getMaxTurnRate). The object/flying-AI
// field names are descriptive; the method name is a placeholder.
// Codegen notes: the toGoal block and the block around the GeometryInfo copy
// reproduce retail's shared stack slot; the inline speed getter keeps retail's
// SSE compare and operand order.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Retail copy-constructs these points member-wise (movss per field); only a
// user-written copy constructor reproduces that, assignment stays implicit.
struct MemberwiseCoord3D : public Coord3D
{
	MemberwiseCoord3D() {}
	MemberwiseCoord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }
};
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

Real normalizeAngle(Real angle);
float Rva001E3FADGet(const Coord3D *a, const Coord3D *b);

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z;
};

class Vector4
{
public:
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; return *this; }
	Vector3 Get_Translation() const { return Vector3(Row[0][3], Row[1][3], Row[2][3]); }
	void Set_Translation(const Vector3 &t) { Row[0][3] = t[0]; Row[1][3] = t[1]; Row[2][3] = t[2]; }
	Vector4 Row[3];
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva00375A73Coord { float x, y, z; };
class Rva00375A73Context
{
public:
	unsigned char prefix00[0x54];
	Coord3D goal54;					// +0x54
};
class AerialPathfinder
{
public:
	bool rva00375A73(Rva00375A73Context *context, float value, Rva00375A73Coord *output);
};
// ?TheAerialPathfinder@@3PAVAerialPathfinder@@A at 0x00A01F10 (zero-filled
// .data) is defined with its class in AerialPathfinder.cpp.
extern AerialPathfinder *TheAerialPathfinder;

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);
	virtual ~GeometryInfo();
	char m_pad04[0x14 - 0x04];
	Real m_14;							// +0x14
	Real get14() const { return m_14; }
	char m_pad18[0x5C - 0x18];
};

class ModelConditionFlags
{
public:
	UnsignedInt test(Int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(Int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(Int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[19];
};

class AerialAIUpdateView
{
public:
	char m_pad000[0x4B8];
	UnsignedInt m_flags4B8;				// +0x4B8 (bit 7)
	char m_pad4BC[0x538 - 0x4BC];
	Real m_speed;						// +0x538
	Real m_turnRate;					// +0x53C
	Real getSpeed() const { return m_speed; }
	char m_pad540[0x544 - 0x540];
	Coord3D m_anchor;					// +0x544
};

class AIUpdateInterface
{
public:
#define X1_V(n) virtual void slot##n();
#define X1_V10(n) X1_V(n##0) X1_V(n##1) X1_V(n##2) X1_V(n##3) X1_V(n##4) X1_V(n##5) X1_V(n##6) X1_V(n##7) X1_V(n##8) X1_V(n##9)
	X1_V10(0) X1_V10(1) X1_V10(2) X1_V10(3) X1_V10(4) X1_V10(5) X1_V10(6)
	X1_V10(7) X1_V10(8)
	X1_V(90) X1_V(91) X1_V(92) X1_V(93) X1_V(94) X1_V(95) X1_V(96) X1_V(97)
#undef X1_V10
#undef X1_V
	virtual AerialAIUpdateView *getAerialAIUpdate();	// slot 98 (+0x188)
};

class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};
class Rva001E438B
{
public:
	void rva001E438B(float *dst, const float *src);
};
class Rva0030A3E4
{
public:
	void rva0030A3E4(const Matrix3D *mtx);
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mtx);
};

class Object : public Thing
{
public:
	Real GetRelativeAngle(const Coord3D *pos) const;
	void rva0028AE6D();
	__forceinline void setModelConditionState(Int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(Int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearAndSetModelConditionState(Int clearBit, Int setBit)
	{
		if (m_conditionBits.test(clearBit) != 0 || m_conditionBits.test(setBit) == 0)
		{
			m_conditionBits.clear(clearBit);
			m_conditionBits.set(setBit);
			rva0028AE6D();
		}
	}
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void setNextPosition(const Coord3D &pos) { m_hasNextPosition = true; m_nextPosition = pos; }
private:
	char m_pad000[0x08];
	Matrix3D m_transform;				// +0x08
	Coord3D m_position;					// +0x38
	Real m_orientation;					// +0x44
	char m_pad048[0xA8 - 0x48];
	GeometryInfo m_geometryInfo;		// +0xA8
	char m_pad104[0x10C - 0x104];
	ModelConditionFlags m_conditionBits;	// +0x10C
	char m_pad158[0x198 - 0x158];
	Coord3D m_nextPosition;				// +0x198
	char m_pad1A4[0x1A6 - 0x1A4];
	Bool m_hasNextPosition;				// +0x1A6
	char m_pad1A7[0x258 - 0x1A7];
	AIUpdateInterface *m_ai;			// +0x258
};

struct LocomotorTemplate
{
	char m_pad00[0x18];
	Real m_18;							// +0x18
	Bool m_1C;							// +0x1C
};

class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
	float rva001E4845(Object *obj);
	float rva001E488A(Object *obj);
};
struct Rva001E3F08Arg;
class Rva001E3F08
{
public:
	float rva001E3F08(Rva001E3F08Arg *p);
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
template <class T> inline const T &maxOf(const T &a, const T &b) { return a > b ? a : b; }

class Locomotor
{
public:
	virtual void locoAnchor();
	Real getMaxTurnRate(Object *object) const;
	void rva001E41FA(float angle);
	Bool rva001E9A00(Object *obj, Real goalSpeed, Real *pathDistance, Rva00375A73Context *path);
	Real getMaxSpeed(Object *obj) { return ((Rva001E46E1 *)this)->rva001E46E1(obj); }
	Real getAcceleration(Object *obj) { return ((Rva001E46E1 *)this)->rva001E4845(obj); }
	Real getBraking(Object *obj) { return ((Rva001E46E1 *)this)->rva001E488A(obj); }
	Real getMinSpeed(Object *obj) { return ((Rva001E3F08 *)this)->rva001E3F08((Rva001E3F08Arg *)obj); }
private:
	const LocomotorTemplate *m_template;	// +0x04
	char m_pad08[0x68 - 0x08];
	Matrix3D m_transform;				// +0x68
};

enum
{
	MODELCONDITION_61 = 61,
	MODELCONDITION_72 = 72,
	MODELCONDITION_103 = 103
};

Bool Locomotor::rva001E9A00(Object *obj, Real goalSpeed, Real *pathDistance, Rva00375A73Context *path)
{
	if (!obj)
		return false;
	Real lookAhead = obj->getGeometryInfo().get14() * 0.5f;
	if (m_template->m_18 > 1.0f)
		lookAhead *= m_template->m_18;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;
	AerialAIUpdateView *aerial = ai->getAerialAIUpdate();
	if (!aerial)
		return false;
	m_transform = *obj->getTransformMatrix();
	Real speed = aerial->getSpeed();
	*pathDistance += speed;
	Coord3D pos;
	if (TheAerialPathfinder->rva00375A73(path, *pathDistance, (Rva00375A73Coord *)&pos))
	{
		m_transform.Set_Translation(Vector3(pos.x, pos.y, pos.z));
		Bool isFar = (aerial->m_flags4B8 >> 7) & 1;
		if (!isFar)
		{
			MemberwiseCoord3D anchor = aerial->m_anchor;
			isFar = ((Gen_000E5A50 *)obj)->bfmeDistanceSquared((const BfmeVec3EJ *)&anchor) > 70.0f * 70.0f;
		}
		if (isFar)
			obj->setModelConditionState(MODELCONDITION_61);
		else
			obj->clearModelConditionState(MODELCONDITION_61);

		Real angle = 0.0f;
		Real count = 0.0f;
		Real pitch = 0.0f;
		if (m_template->m_1C)
			((Rva0030A3E4 *)obj)->rva0030A3E4(&m_transform);
		Coord3D behind;
		if (TheAerialPathfinder->rva00375A73(path, *pathDistance - lookAhead, (Rva00375A73Coord *)&behind))
		{
			pitch += Rva001E3FADGet(&behind, &pos);
			angle += normalizeAngle(obj->GetRelativeAngle(&behind) + 3.1415927f);
			count += 1.0f;
		}
		Coord3D ahead;
		if (TheAerialPathfinder->rva00375A73(path, *pathDistance + lookAhead, (Rva00375A73Coord *)&ahead))
		{
			pitch += Rva001E3FADGet(&pos, &ahead);
			angle += obj->GetRelativeAngle(&ahead);
			count += 1.0f;
		}
		if (count > 0.0f)
		{
			angle /= count;
			pitch /= count;
		}
		Real turnRate = aerial->m_turnRate;
		Real maxTurn = getMaxTurnRate(obj);
		Bool bigTurn = fabs(angle) > maxTurn * 3.0f;
		Real turn = MIN(MAX(angle, -maxTurn), maxTurn);
		turnRate = turnRate * 0.8f + turn * 0.2f;
		aerial->m_turnRate = turnRate;
		rva001E41FA(normalizeAngle(obj->getOrientation() + turn));
		Real dist;
		{
			Coord3D toGoal;
			((Rva001E438B *)obj)->rva001E438B(&toGoal.x, &path->goal54.x);
			dist = toGoal.length();
		}
		Bool close = aerial->getSpeed() * 4.0f > dist;
		if (close && pitch < 0.0f)
			pitch *= -1.0f;
		else if (bigTurn)
			pitch += 1.5f;
		if (speed < goalSpeed)
			speed += getAcceleration(obj);
		else if (speed > goalSpeed)
			speed -= getBraking(obj);
		speed *= 1.0f - pitch * 0.4f;
		if (getMaxSpeed(obj) < speed)
			speed = getMaxSpeed(obj);
		else if (getMinSpeed(obj) > speed)
			speed = getMinSpeed(obj);
		aerial->m_speed = speed;

		Vector3 position = m_transform.Get_Translation();
		Real height = TheTerrainLogic->getGroundHeight(position[0], position[1], 0);
		{
			GeometryInfo geom(obj->getGeometryInfo());
			Real minZ = geom.m_14 * 0.25f + height;
			position[2] = maxOf(position[2], minZ);
			m_transform.Set_Translation(position);
			if (pitch > 0.3f)
				obj->clearAndSetModelConditionState(MODELCONDITION_72, MODELCONDITION_103);
			else if (pitch < -0.6f)
				obj->clearAndSetModelConditionState(MODELCONDITION_103, MODELCONDITION_72);
			else
			{
				obj->clearModelConditionState(MODELCONDITION_72);
				obj->clearModelConditionState(MODELCONDITION_103);
			}
			obj->setTransformMatrix(&m_transform);
			MemberwiseCoord3D next = *obj->getPosition();
			if (TheAerialPathfinder->rva00375A73(path, *pathDistance + aerial->getSpeed(), (Rva00375A73Coord *)&next))
				obj->setNextPosition(next);
		}
		return false;
	}
	obj->clearModelConditionState(MODELCONDITION_61);
	obj->clearModelConditionState(MODELCONDITION_103);
	obj->clearModelConditionState(MODELCONDITION_72);
	return true;
}
