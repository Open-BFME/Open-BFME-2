// ?rva000B710D@W3DModelDraw@@QAEXAAVMatrix3D@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
//
// NEAR draft (not landable yet). Three bodies of one retail unit (the
// W3DModelDraw-area TU), kept together because both callers keep ECX (the
// angle pointer) live across the clamp helper's call and B710D reuses its
// dead Matrix3D& parameter slot for the angle, which cl only does when the
// callees are compiled earlier in the same unit:
//   ?Rva000B2BFFClamp@@YAXPAMM@Z                              0x000B2BFF 190B  EXACT here (row now in Common/Rva000B2BFFClamp.cpp; must move)
//   ?rva000B4CE2@W3DScriptedModelDraw@@QAE_NPAM@Z              0x000B4CE2 321B  10 diffs (scheduling/xmm choice of the target/pos Vector3 stores)
//   ?rva000B710D@W3DScriptedModelDraw@@QAEXAAVMatrix3D@@@Z     0x000B710D 1068B exact except the REL32 to the unrowed B4CE2
// B710D is Zero Hour's W3DModelDraw::adjustTransformMtx extended by BFME
// (BFME1 donor AttachmentTransform007629F0::adjust 0x007629F0): parent
// drawable bone attach with turret-style Z clamp, own-drawable bone attach
// (+0x04 module data +0x40 bone name) then virtual slot 0x104, 1/30 per
// frame Matrix3D::Lerp blend (+0x290/+0x2C0/+0x2C4) and the construction
// height Translate_Z. B4CE2 aims at the AI victim (WorldBuilder 0x929CC0).
#include <math.h>
#include "ascii_string.h"

class Vector4
{
public:
	__forceinline float &operator[](int i) { return (&X)[i]; }
	__forceinline const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z, W;
};

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	float X, Y, Z;
};

class Matrix3D
{
public:
	Matrix3D() {}
	__forceinline explicit Matrix3D(bool init)
	{
		if (init)
		{
			Row[0].X = 1.0f; Row[0].Y = 0.0f; Row[0].Z = 0.0f; Row[0].W = 0.0f;
			Row[1].X = 0.0f; Row[1].Y = 1.0f; Row[1].Z = 0.0f; Row[1].W = 0.0f;
			Row[2].X = 0.0f; Row[2].Y = 0.0f; Row[2].Z = 1.0f; Row[2].W = 0.0f;
		}
	}
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0].X = m.Row[0].X; Row[0].Y = m.Row[0].Y; Row[0].Z = m.Row[0].Z; Row[0].W = m.Row[0].W;
		Row[1].X = m.Row[1].X; Row[1].Y = m.Row[1].Y; Row[1].Z = m.Row[1].Z; Row[1].W = m.Row[1].W;
		Row[2].X = m.Row[2].X; Row[2].Y = m.Row[2].Y; Row[2].Z = m.Row[2].Z; Row[2].W = m.Row[2].W;
		return *this;
	}
	float Get_Z_Rotation() const;
	void Obj_Look_At(const Vector3 &p, const Vector3 &t, float roll);
	static void Lerp(const Matrix3D &A, const Matrix3D &B, float factor, Matrix3D &result);
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;
		c = (float)cos(theta);
		s = (float)sin(theta);
		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)(c * tmp1 + s * tmp2);
		Row[0][1] = (float)(-s * tmp1 + c * tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)(c * tmp1 + s * tmp2);
		Row[1][1] = (float)(-s * tmp1 + c * tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)(c * tmp1 + s * tmp2);
		Row[2][1] = (float)(-s * tmp1 + c * tmp2);
	}
	__forceinline void Translate_Z(float z)
	{
		Row[0][3] += (float)(Row[0][2] * z);
		Row[1][3] += (float)(Row[1][2] * z);
		Row[2][3] += (float)(Row[2][2] * z);
	}
	Vector4 Row[3];
};

#define SLOT(n) virtual void slot##n();

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Rva0028B6A2Host
{
public:
	float rva0028B6A2();
};

class Coord3D;
class Object;

class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *victim, float extra, int flag) const;
};

enum WeaponSlotType {};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
	char m_pad00[0x30];
	char *m_field30;
};

class ContainView
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44)
	virtual bool slot45();
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	ContainView *getContain() const { return m_contain; }
	char m_pad00[0x08];
	Matrix3D m_transform;
	char m_pad38[0xA8 - 0x38];
	GeometryInfo m_geometry;
	char m_padA9[0x250 - 0xA9];
	ContainView *m_contain;
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x280 - 0x25C];
	float m_constructionPercent;
};

class Drawable
{
public:
	bool rva00272835(int boneName, int boneMtx);
	char m_pad00[0xFC];
	Object *m_object;
};

class GameClient
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	virtual Drawable *findDrawableByID(unsigned int id);
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
	virtual unsigned int getFrame();
};

class W3DScriptedModelDraw;

class GameEngine
{
	friend class W3DScriptedModelDraw;
private:
	bool rva00225D38();
	char m_pad00[0x3C];
	float m_logicTimeScale;
};

extern GameClient *TheGameClient;
extern GameEngine *TheGameEngine;
extern int g_Va00DEAF14;

struct W3DScriptedModelDrawData
{
	char m_pad00[0x40];
	AsciiString m_attachToBone;
};

struct W3DScriptedModelDrawState
{
	char m_pad00[0x5C];
	unsigned int m_flags;
};

__declspec(noinline) void __cdecl Rva000B2BFFClamp(float *p, float v)
{
	if (*p > v)
	{
		float diff = *p - v;
		if (diff > 3.1415927410125732f)
		{
			*p += 0.1f;
		}
		else if (diff > 0.1f)
		{
			*p -= 0.1f;
		}
		else
		{
			*p = v;
		}
	}
	else if (v > *p)
	{
		float diff = v - *p;
		if (diff > 3.1415927410125732f)
		{
			*p -= 0.1f;
		}
		else if (diff > 0.1f)
		{
			*p += 0.1f;
		}
		else
		{
			*p = v;
		}
	}
	if (*p > 3.1415927410125732f)
	{
		*p -= 6.2831854820251465f;
	}
	if (-3.1415927410125732f > *p)
	{
		*p += 6.2831854820251465f;
	}
}

class W3DScriptedModelDraw
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64)
	virtual void adjustAttachedTransform(Matrix3D *mtx);

	bool rva000B4CE2(float *angle);
	__forceinline Drawable *getDrawable() const { return m_drawable; }
	void rva000B710D(Matrix3D &mtx);

	const W3DScriptedModelDrawData *m_moduleData;
	Drawable *m_drawable;
	char m_pad0C[0x18 - 0x0C];
	W3DScriptedModelDrawState *m_curState;
	char m_pad1C[0x8C - 0x1C];
	float m_turnAngle;
	char m_pad90[0xA4 - 0x90];
	unsigned int m_parentID;
	char m_padA8[0xB4 - 0xA8];
	AsciiString m_parentBone;
	char m_padB8[0x26C - 0xB8];
	float m_constructionPercent;
	char m_pad270[0x290 - 0x270];
	Matrix3D m_blendMtx;
	float m_blend;
	unsigned int m_blendFrame;
};

__declspec(noinline) bool W3DScriptedModelDraw::rva000B4CE2(float *angle)
{
	Drawable *draw = m_drawable;
	if (!draw)
		return false;
	Object *obj = draw->m_object;
	if (!obj)
		return false;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
	{
		Object *victim = ai->getCurrentVictim();
		if (victim)
		{
			const Weapon *weapon = obj->getCurrentWeapon(0);
			if (weapon && weapon->isWithinAttackRange(obj, victim, 0.0f, 1))
			{
				Vector3 goal(*(const Vector3 *)(ai->m_field30 + 0x24));
				Vector3 target(goal.X, goal.Y, 0.0f);
				Vector3 pos(obj->m_transform.Row[0].W, obj->m_transform.Row[1].W, 0.0f);
				Matrix3D look(true);
				look.Obj_Look_At(pos, target, 0.0f);
				float z = look.Get_Z_Rotation();
				Rva000B2BFFClamp(&m_turnAngle, z);
				*angle = m_turnAngle - *angle;
				return true;
			}
		}
	}
	return false;
}

void W3DScriptedModelDraw::rva000B710D(Matrix3D &mtx)
{
	if (m_parentID)
	{
		Drawable *parent = TheGameClient->findDrawableByID(m_parentID);
		if (parent)
		{
			Object *obj = parent->m_object;
			Matrix3D boneMtx;
			if (parent->rva00272835((int)((const StringBase<char> *)&m_parentBone)->str(), (int)&boneMtx))
			{
				mtx = boneMtx;
				ContainView *contain = obj->getContain();
				if (contain && contain->slot45())
				{
					float angle = mtx.Get_Z_Rotation();
					if (!rva000B4CE2(&angle))
					{
						Rva000B2BFFClamp(&m_turnAngle, angle);
						angle = m_turnAngle - angle;
					}
					mtx.Rotate_Z(angle);
				}
				return;
			}
			if (g_Va00DEAF14 < 100)
				++g_Va00DEAF14;
		}
	}
	const W3DScriptedModelDrawData *d = m_moduleData;
	if (!((const StringBase<char> *)&d->m_attachToBone)->isEmpty())
	{
		Matrix3D boneMtx;
		if (getDrawable()->rva00272835((int)d->m_attachToBone.str(), (int)&boneMtx))
		{
			mtx = boneMtx;
			adjustAttachedTransform(&mtx);
		}
	}
	if (m_blend < 1.0f)
	{
		if (m_blendFrame < TheGameClient->getFrame())
		{
			m_blendFrame = TheGameClient->getFrame();
			m_blend += 1.0f / 30.0f;
			if (m_blend > 1.0f)
				m_blend = 1.0f;
		}
		Matrix3D::Lerp(m_blendMtx, mtx, m_blend, mtx);
	}
	else
	{
		m_blendFrame = ~0u;
		m_blend = 1.0f;
	}
	if (m_curState && (m_curState->m_flags & 8))
	{
		Object *obj = m_drawable->m_object;
		if (obj)
		{
			if (TheGameEngine->rva00225D38())
				m_constructionPercent = obj->m_constructionPercent;
			if (m_constructionPercent >= 0.0f)
			{
				float rate = reinterpret_cast<Rva0028B6A2Host *>(obj)->rva0028B6A2();
				float pct = TheGameEngine->m_logicTimeScale * rate + m_constructionPercent;
				float height = obj->m_geometry.getMaxHeightAbovePosition();
				mtx.Translate_Z(height * pct * 0.01f - height);
			}
		}
	}
}
