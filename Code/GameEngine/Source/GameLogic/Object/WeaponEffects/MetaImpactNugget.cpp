// cl: /O1 /MD /EHsc /DNDEBUG /arch:SSE /I.
//
// ?rva0050A1E9@Made002CC8A4@@QAEXPAXPAVObject@@@Z @ 0x0050A1E9 (434B), slot 15 of
// Made002CC8A4 (MetaImpactNugget) vtable 0x008649A0; WB 0x10A71E0 MetaImpactNugget.cpp.
// Object::testStatus is visible inline (header inline in ZH Object.h; /O1 still calls
// 0x0004E536): it lets the target->+0x274 load before the call be reused, and the body
// rereads the rider chain from the target as WB does (+0x27C -> +0x27C -> contain).
// Slot 15 (0x3C) of Made002CC8A4 vtable 0x008649A0 (MetaImpactNugget).
// Evidence: vtable slot 15; callers none; callees rowed findObjectByID,
// isValid, getControllingPlayer, kill, rva0028C149, GetGameLogicRandomValueReal,
// testStatus and Rva2225E0Filter::accepts; report and attemptDamage; TheGameLogic,
// BfmeZeroRange, MetaImpactRandomUpperBound, string literal.

#include "Code/Libraries/Include/Lib/Coord3DInline.h"
#include <math.h>
// Retail Coord3D::length (0x00003571) is an inline body that /O1 leaves out of line.
inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "../../../Common/GameLogicObjectLookupView.h"

class Object;
class Player;
enum DamageType
{
	DT_8 = 8
};
enum DeathType
{
	DT_0 = 0
};
enum ObjectStatusTypes
{
	ST_26 = 0x26
};

extern GameLogic *TheGameLogic;

class ObjectFilter
{
public:
	bool isValid() const;
};
struct Rva2225E0Filter
{
	bool accepts(Object *obj, Player *context);
};
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex; // +0x54
};
class DamageInfo
{
public:
	unsigned char m_pad00[8];
	unsigned int m_sourceID; // +0x08
	unsigned int m_sourcePlayerMask; // +0x0C
	unsigned char m_pad10[0x18];
	float m_amount; // +0x28
	unsigned int m_pad2C;
	unsigned int m_sourceObjectID; // +0x30
	Coord3D m_direction; // +0x34
	float m_40, m_44, m_48, m_4C;
	bool m_50;
	unsigned char m_pad51[3];
	float m_54, m_58;
	Coord3D m_center; // +0x5C
	float m_68;
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Player *getControllingPlayer() const;
	void kill(DamageType a, DeathType b);
	bool rva0028C149(int attr, float *value, int arg);
	bool testStatus(ObjectStatusTypes s) const;
	void attemptDamage(DamageInfo *info);
public:
	char m_pad00[4];
	void *m_04;
	float m_transform[3][4]; // +8; native fallback reads first column
	Coord3D m_pos; // +0x38
	char m_pad44[0x74 - 0x44];
	unsigned int m_id; // +0x74
	char m_pad78[0x94 - 0x78];
	unsigned int m_statusBits[4];
};
inline bool Object::testStatus(ObjectStatusTypes bit) const
{
	return (m_statusBits[(unsigned int)bit >> 5] & (1 << (bit & 31))) != 0;
}
extern const float MetaImpactRandomUpperBound;
float __cdecl GetGameLogicRandomValueReal(float a, float b, char *name, int line);

class Rva00263653
{
public:
	Rva00263653() throw();
	char m_data[0x68];
};
class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();
private:
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};
class Rva00294D61
{
public:
	void report(Object *o, int v);
};
class DamageInfoish
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void *v14();
	virtual void v15(void *a);
};
class TargetIface
{
public:
	virtual void v00();
	virtual void *v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void *v31(Object *o);
};
class SelfIface
{
public:
	virtual void v00();
	virtual bool v01(int source, Object *obj);
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual unsigned char v14(const void *a, Object *b, const void *c);
	virtual void v15(void *source, Object *obj);
};

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};
class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};
class Rva00507823
{
public:
	virtual ~Rva00507823();
	virtual bool slot01(int source, Object *obj);
	virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	Rva00507823();
private:
	char m_pad[0x128 - 4];
};
class Made002CC8A4 : public Rva00507823
{
public:
	Made002CC8A4();
	void rva0050A1E9(void *source, Object *b);
	virtual void rva0050A4A2(void *source, const Coord3D *pos);
	unsigned char rva00509F3A(void *weapon, Object *victim, DamageInfo *info);
private:
	float m_128;
	float m_12C;
	float m_130;
	bool m_134;
	char m_pad135[3];
	float m_138;
	float m_13C;
	float m_140;
	float m_144;
	int m_148;
	bool m_14C;
	bool m_14D;
	char m_pad14E[2];
	float m_150;
	bool m_154;
	bool m_155;
	char m_pad156[2];
	float m_158;
	float m_15C;
	Rva003623E5Member m_160;
};

// Slot 14 of Made002CC8A4 vtable 0x008649A0; WB 0x10A6DC0 twin (set/sub per arm, rotation tail).
static inline const float &bfmeMin(const float &a, const float &b) { return b < a ? b : a; }
unsigned char Made002CC8A4::rva00509F3A(void *weapon, Object *victim, DamageInfo *info)
{
 if (!weapon || !victim) return 0;
 Object *source = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)weapon + 8));
 if (!source) return 0;
 info->m_40 = m_128;
 Coord3D dir;
 if (m_155 || !m_14C) {
  dir.set(victim->getPosition());
  dir.sub(source->getPosition());
 } else {
  dir.set(source->getPosition());
  dir.sub(victim->getPosition());
 }
 if (m_144 != 0.0f) {
  float side = bfmeMin(m_144, 1.0f);
  float normal = 1.0f - side;
  float a = dir.y * side;
  float b = -dir.x * side;
  dir.x = dir.x * normal + a * side;
  dir.y = dir.y * normal + b * side;
 }
 if (fabs(dir.x) < 0.0001f && fabs(dir.y) < 0.0001f && fabs(dir.z) < 0.0001f) {
  if (m_155) {
   float angle = GetGameLogicRandomValueReal(0.0f, 6.2831855f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\WeaponEffects\\MetaImpactNugget.cpp", 0x15B);
   // Keep the native float CRT calls without emitting the C++ overload copies.
   dir.x = cosf(angle); dir.y = sinf(angle);
  } else dir.z = 1.0f;
 }
 info->m_direction = dir;
 info->m_44 = m_12C; info->m_48 = m_138; info->m_4C = m_140;
 info->m_50 = m_155; info->m_54 = m_158; info->m_58 = m_15C;
 if (m_155) info->m_center = *source->getPosition();
 info->m_amount = (float)(unsigned int)m_148;
 info->m_68 = m_144;
 if (m_13C > 0.0f) info->m_amount += dir.length() / m_13C;
 info->m_sourceObjectID = source->m_id;
 if (source->getControllingPlayer()) info->m_sourcePlayerMask = 1u << source->getControllingPlayer()->m_playerIndex;
 info->m_sourceID = *(unsigned int *)((char *)weapon + 8);
 info->m_sourcePlayerMask = source ? (1u << source->getControllingPlayer()->m_playerIndex) : 0;
 return 1;
}

void Made002CC8A4::rva0050A1E9(void *source, Object *shooter)
{
	if (!source)
		return;
	if (!shooter)
		return;
	Object *found = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)source + 8));
	if (found)
	{
		char *base = (char *)this + 0x160;
		if (!((ObjectFilter *)base)->isValid())
			goto doAttr;
		if (!((Rva2225E0Filter *)base)->accepts(shooter, found->getControllingPlayer()))
			goto doAttr;
		shooter->kill(DT_8, DT_0);
		return;
	}
doAttr:
	{
		float chance;
		shooter->rva0028C149(0xA, &chance, 0);
		if (!(chance > 0.0f))
			goto checkBit;
		float roll = GetGameLogicRandomValueReal(0.0f, MetaImpactRandomUpperBound, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\WeaponEffects\\MetaImpactNugget.cpp", 0x19B);
		if (!(roll > chance))
			return;
	}
checkBit:
	{
		void *vp = (void *)*(int *)((char *)shooter + 4);
		if (*(unsigned char *)((char *)vp + 0x113) & 4)
		{
			float secondRoll = GetGameLogicRandomValueReal(0.0f, MetaImpactRandomUpperBound, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\WeaponEffects\\MetaImpactNugget.cpp", 0x1A4);
			if (secondRoll < m_150)
				return;
		}
	}
	{
		Object *object = shooter;
		void *tail = (void *)*(int *)((char *)object + 0x274);
		if (object->testStatus(ST_26) && tail && *(int *)((char *)tail + 0x274) &&
            (*(unsigned char *)((char *)*(void **)((char *)tail + 4) + 0x115) & 0x20))
        {
		void *t274 = (void *)*(int *)(*(char **)((char *)object + 0x274) + 0x274);
		void *t250 = (void *)*(int *)((char *)t274 + 0x250);
		if (!t250)
			return;
		Object *found2 = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)source + 8));
		if (found2)
			((Rva00294D61 *)found2)->report(object, 1);
		((DamageInfoish *)((TargetIface *)t250)->v01())->v15(((TargetIface *)t250)->v31(object));
		return;
        }
	}
tryDamage:
	{
		Rva00263895Member info;
		if (((SelfIface *)this)->v14(source, shooter, &info) != 1)
			return;
		shooter->attemptDamage((DamageInfo *)&info);
	}
}

// Native751B virtual slot6 at50A4A2; range/cone operation on the same
// independently owned nugget layout as slot15 above. Position38 and
// fallback matrix-column offsets8/18/28 are target facts. Snapshot all
// position components before source reads; retain native X/Y/Z subtraction.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern PartitionManager *ThePartitionManager;
float Cos(float value);
class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

struct Vector3
{
	float X, Y, Z;
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	static float Dot_Product(const Vector3 &a, const Vector3 &b) { return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
};

// This unit needs the header-inline SSE operation; retain the canonical
// out-of-line Vector3::Normalize provider instead of emitting a second copy.
static __forceinline void normalizeDirection(Vector3 &direction)
{
 float len2 = direction.Length2();
 if (len2 != 0.0f) {
  float oolen = WWMath::Inv_Sqrt(len2);
  direction.X *= oolen; direction.Y *= oolen; direction.Z *= oolen;
 }
}

// The weapon source record handed to the nugget: its source ObjectID at +0x08.
struct Rva0050A4A2Source
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};

// BFME 2's partition filter base (ctor 0x000421C8): a vptr and the +0x04 link.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask(); // native filter base has three slots
	Rva000421C8 *m_next;
};
// The 224-bit KindOf mask and the one-bit mask builder 0x00045411.
struct Rva00045411BitSet : public BfmeFixedStorage0004543D
{
	Rva00045411BitSet(int unused, int bit) throw();
};
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
// The out-of-line constructor 0x00395A35.
class PartitionFilterRejectByKindOf : public Rva000421C8
{
public:
	PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &require, const BfmeFixedStorage0004543D &reject);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_require;
	BfmeFixedStorage0004543D m_reject;
};


void Made002CC8A4::rva0050A4A2(void *source, const Coord3D *pos)
{
	if (!source || !pos)
		return;
	float radius = m_12C;
	if (radius < 1.0f)
		radius = 1.0f;
	PartitionFilterRejectByKindOf filter(Rva00045411BitSet(0, 0x59), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE);
	bool centerDistance = m_144 != 0.0f;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(pos, radius, centerDistance ? 1 : 3, &filter, 0);
	Object *obj;
	while ((obj = iter.next()) != 0)
	{
		if (!((SelfIface *)this)->v01((int)source, obj))
			continue;
		if (m_130 < 3.14159265359f)
		{
			Coord3D toObj;
			toObj.set(obj->getPosition());
			toObj.sub(pos);
			Object *src = TheGameLogic->findObjectByID(((const Rva0050A4A2Source *)source)->m_sourceID);
			if (!src)
				continue;
			float px = pos->x, py = pos->y, pz = pos->z;
			_ReadWriteBarrier();
			Coord3D diff;
			diff.x = px - src->getPosition()->x;
			diff.y = py - src->getPosition()->y;
			diff.z = pz - src->getPosition()->z;
			Coord3D diffCopy;
			diffCopy.set(&diff);
			Vector3 dir(diff.x, diff.y, diff.z);
			if (diffCopy.length() == 0.0f)
				dir.Set(src->m_transform[0][0], src->m_transform[1][0], src->m_transform[2][0]);
			Vector3 toV(toObj.x, toObj.y, toObj.z);
			normalizeDirection(dir);
			normalizeDirection(toV);
			float dot = Vector3::Dot_Product(toV, dir);
			if (!(dot >= Cos(m_130)))
			{
				if (!m_134)
					continue;
			}
			else if (m_134)
				continue;
		}
		((SelfIface *)this)->v15(source, obj);
	}
}

// Retail VA00C6499C owns exact float bits3F7FBE77. Both native slot15
// random calls use this read-only upper bound; original identifier unknown.
extern const float MetaImpactRandomUpperBound = 0.999f;
