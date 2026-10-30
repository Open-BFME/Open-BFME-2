// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include
//
// ?rva0047A895@HordeContain@@QAEXPAVObject@@PBUCoord3D@@M_N@Z, retail 0x0047A895 (1018 B, RET 0x10):
// moves one horde member towards pos. Kind 0xDA members defer to HordeContain::updatePosition
// (0x00474842); a member whose AI slot 0x1BC holds only clears its model condition 61; with a
// +0x2A0 owner the full HordeContain::_updatePosition (0x00471464) runs. Otherwise the member's
// formation slot key picks the rank angle, its locomotor caps the step (max speed x1.25) and the
// turn (max turn rate, when the module data's +0x124 bit 23 asks to face pos), the data's two
// flags toggle model conditions 61 and 215, and the member gets the rotated transform, the
// position and its next position.
//
// Target facts: native 0x0047A895..0x0047AC8F; WB 0x0115F9B0 (debug build: Object.h
// clear/setModelConditionState at lines 862/873 over BitFlags test/set/clear, the callees named
// above plus Locomotor::getMaxSpeed/getMaxTurnRate, Object::GetRelativeAngle, Coord3D
// GetLength/normalize/Scale/Add, cos/sin, Thing::setTransformMatrix/setPosition and an inlined
// Object::setNextPosition at +0x198/+0x1A6). Carried from donors: the WWMath Matrix3D inlines
// (identity, Set_Translation, Rotate_Z) as the matched W3DPropBufferUpdatePropPosition.cpp
// spells them, Zero Hour's Coord3D sub/scale/add, and the model-condition BitFlags spelling of
// the matched RousingSpeechUpdateRva004ACF1D.cpp (test returns the masked word; words from
// Object +0x10C). Class, field and method names not listed are address-derived.
#include <math.h>
#define COORD3D_VIEW_INLINE
#include "Lib/Coord3DCtorView.h"
#include "Lib/Coord2D.h"

class Vector3
{
public:
	__forceinline Vector3() {}
	__forceinline Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float &operator[](int i) { return (&X)[i]; }
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	// Inlined at every use; retail's out-of-line copy (0x0004C91A) builds Row[] through
	// a Vector4 ctor iterator this view lacks, so emit none here.
	__declspec(dllimport) __forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	__forceinline void Set_Translation(const Vector3 &t) { Row[0][3] = t[0]; Row[1][3] = t[1]; Row[2][3] = t[2]; }
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float cosTheta, s;

		cosTheta = cosf(theta);
		s = sinf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( cosTheta*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + cosTheta*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( cosTheta*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + cosTheta*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( cosTheta*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + cosTheta*tmp2);
	}
private:
	Vector4 Row[3];
};

enum KindOfType { KINDOF_RVA0047A895_DA = 0xDA };

class Object;
class Locomotor
{
public:
	float getMaxSpeed(Object *obj) const;		// 0x001E46E1
	float getMaxTurnRate(Object *obj) const;	// 0x001E3E9F
};
struct Rva0028AC4EEntry;

class PhysicsBehavior
{
public:
	void rva00390629(bool flag);			// 0x00390629
};

class Rva0047A895AI
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual bool rva0047A895Slot111();	// +0x1BC
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mtx);	// 0x0030A2B7
	void setPosition(const Coord3D *pos);		// 0x0030AA80
};

class Rva0047A895ConditionBits
{
public:
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
	void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }
private:
	unsigned int m_words[7];
};

class Object : public Thing
{
public:
	bool isKindOf(KindOfType t) const;		// 0x0006F039
	const Rva0028AC4EEntry *rva0028AC4E() const;	// 0x0028AC4E
	void rva0028AE6D();				// 0x0028AE6D
	float GetRelativeAngle(const Coord3D *pos) const;	// 0x000B4542
	char m_pad000[0x38];
	Coord3D m_pos;				// +0x38
	float m_orientation;			// +0x44
	char m_pad048[0x74 - 0x48];
	int m_id;				// +0x74
	char m_pad078[0x10C - 0x78];
	Rva0047A895ConditionBits m_conditionBits;	// +0x10C
	char m_pad128[0x198 - 0x128];
	Coord3D m_198;				// +0x198
	char m_pad1A4[0x1A6 - 0x1A4];
	bool m_1A6;				// +0x1A6
	char m_pad1A7[0x258 - 0x1A7];
	Rva0047A895AI *m_258;			// +0x258
	PhysicsBehavior *m_physics;		// +0x25C
};

struct Rva0047A895Slot				// 0x1C bytes at +0x188
{
	int m_00;
	float m_04;
	char m_pad08[0x1C - 0x08];
};

struct Rva0047A895Rank				// 0x18 bytes at +0x6FC
{
	float m_threshold;
	float m_angle;
	Coord3D m_pos;				// +0x08
	float m_pad14;
};

struct Rva0047A413Point				// 0x10 bytes at +0x338
{
	Coord3D m_pos;
	float m_angle;				// +0x0C
};

float normalizeAngle(float angle);		// 0x00238954

struct Rva0047A895Data
{
	char m_pad000[0x110];
	unsigned int m_110;			// +0x110 flags (bit 29)
	char m_pad114[0x124 - 0x114];
	unsigned int m_124;			// +0x124 flags (bit 23)
};


class Rva0046ACF6
{
public:
	int rva0046ACF6(int id);			// 0x0046ACF6
};

class HordeContain
{
public:
	void rva0047A413();
	void rva0047A895(Object *obj, const Coord3D *pos, float angle, bool flag);
	void rva00474842(Object *obj, const Coord3D *pos, float angle, bool flag);	// 0x00474842
	void _updatePosition(Object *obj, const Coord3D *pos, float angle);	// 0x00471464
	Coord2D *rva0046A5B1(Coord2D *out, int slot);	// 0x0046A5B1
private:
	char m_pad000[0x08];
	const Rva0047A895Data *m_data;		// +0x08
	char m_pad00C[0x188 - 0x0C];
	Rva0047A895Slot *m_slots;		// +0x188
	char m_pad18C[0x2A0 - 0x18C];
	int m_2A0;				// +0x2A0
	char m_pad2A4[0x338 - 0x2A4];
	Rva0047A413Point m_points[(0x6F8 - 0x338) / 0x10];	// +0x338
	int m_pointCount;			// +0x6F8
	Rva0047A895Rank m_ranks[(0x8DC - 0x6FC) / 0x18];	// +0x6FC
	int m_rankCount;			// +0x8DC
};

// The module data's flags read through a plain bit test (retail shifts and tests AL).
static inline bool flagTest(unsigned int flags, int bit) { return (flags & (1u << (bit & 31))) != 0; }

static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

void HordeContain::rva0047A895(Object *obj, const Coord3D *pos, float angle, bool flag)
{
	if (obj->isKindOf(KINDOF_RVA0047A895_DA)) {
		rva00474842(obj, pos, angle, flag);
		clearModelConditionBit(obj, 6 * 32 + 26);
		return;
	}
	Rva0047A895AI *ai = obj->m_258;
	if (ai && ai->rva0047A895Slot111()) {
		clearModelConditionBit(obj, 1 * 32 + 29);
		return;
	}
	if (m_2A0 != 0) {
		_updatePosition(obj, pos, angle);
		return;
	}
	float maxMove;
	{
		int slot = ((Rva0046ACF6 *)this)->rva0046ACF6(obj->m_id);
		float key = m_slots[slot].m_04;
		int i;
		for (i = m_rankCount - 1; i > 0; --i) {
			if (m_ranks[i].m_threshold == key)
				break;
		}
		if (i < 0)
			i = 0;
		angle = m_ranks[i].m_angle;
		maxMove = 9999.0f;
		float maxTurn = 3.1415927f;
		Locomotor *loco = (Locomotor *)obj->rva0028AC4E();
		if (loco) {
			maxMove = loco->getMaxSpeed(obj) * 1.25f;
			maxTurn = loco->getMaxTurnRate(obj);
		}
		if (flagTest(m_data->m_110, 29))
			setModelConditionBit(obj, 1 * 32 + 29);
		else
			clearModelConditionBit(obj, 1 * 32 + 29);
		if (flagTest(m_data->m_124, 23)) {
			setModelConditionBit(obj, 6 * 32 + 23);
			{
				// The slot's formation offset; only the debug build uses it.
				Coord2D offset;
				rva0046A5B1(&offset, slot);
			}
			float rel = obj->GetRelativeAngle(pos);
			if (rel > maxTurn)
				rel = maxTurn;
			else if (-maxTurn > rel)
				rel = -maxTurn;
			angle = obj->m_orientation + rel;
		} else {
			clearModelConditionBit(obj, 6 * 32 + 23);
		}
	}
	Coord3D newPos(obj->m_pos);
	{
		Coord3D delta(*pos);
		delta.sub(&newPos);
		if (delta.GetLength() > maxMove) {
			delta.normalize();
			delta.scaleInlined(maxMove);
			newPos.add(&delta);
		} else {
			newPos = *pos;
		}
	}
	Matrix3D mtx(true);
	mtx.Set_Translation(Vector3(newPos.x, newPos.y, newPos.z));
	mtx.Rotate_Z(angle);
	obj->setTransformMatrix(&mtx);
	obj->setPosition(&newPos);
	obj->m_1A6 = true;		// setNextPosition
	obj->m_198 = newPos;
	if (obj->m_physics)
		obj->m_physics->rva00390629(false);
}

// ?rva0047A413@HordeContain@@QAEXXZ, retail 0x0047A413 (608 B, RET 0; caller 0x0047A841, WB 0x0115F550):
// lays the ranks along the path points (+0x338, 0x10 each: position and angle). Each rank sits at its
// distance behind the first rank's, measured along the path; its position is the point reached there
// and its angle turns towards the path's interpolated heading by at most 10 degrees a call. The WB body
// gives the shape (while (true) with the placement and break inside, Coord3D sub/scale/add, the turn
// limit as a local constant, the reused delta).
//
// The rowed Coord3D::length (0x00003571), visible and out of line: cl then knows the call does not write
// dir, keeps dir.z's zero in XMM0 across it and drops the initial z store, as retail does. Its copy here
// is retail's body.
__declspec(noinline) inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

void HordeContain::rva0047A413()
{
	const float maxTurn = 0.17453294f;
	float first = m_ranks[0].m_threshold;
	float traveled = 0.0f;
	int seg = 0;
	Coord3D dir;
	dir.x = -1.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;
	float cur = 0.0f;
	for (int i = 0; i < m_rankCount; ++i) {
		float remaining = first - m_ranks[i].m_threshold - traveled;
		while (true) {
			float segLen = 0.0f;
			if (seg < m_pointCount - 1) {
				dir = m_points[seg + 1].m_pos;
				dir.sub(&m_points[seg].m_pos);
				dir.z = 0.0f;
				segLen = dir.length();
			} else {
				segLen = 99999.9f;
			}
			if (segLen > remaining) {
				Coord3D d(dir);
				d.normalize();
				d.scaleInlined(remaining);
				d.add(&m_points[seg].m_pos);
				m_ranks[i].m_pos = d;
				float startAngle = m_points[seg].m_angle;
				float endAngle = startAngle;
				if (seg < m_pointCount - 1)
					endAngle = m_points[seg + 1].m_angle;
				float ratio = remaining / segLen;
				float delta = normalizeAngle(endAngle - startAngle) * ratio;
				float target = normalizeAngle(startAngle + delta);
				cur = m_ranks[i].m_angle;
				delta = normalizeAngle(target - cur);
				if (delta > maxTurn)
					m_ranks[i].m_angle = cur + maxTurn;
				else if (-maxTurn > delta)
					m_ranks[i].m_angle = cur - maxTurn;
				else
					m_ranks[i].m_angle = target;
				m_ranks[i].m_angle = normalizeAngle(m_ranks[i].m_angle);
				break;
			}
			remaining -= segLen;
			traveled += segLen;
			++seg;
		}
	}
}
