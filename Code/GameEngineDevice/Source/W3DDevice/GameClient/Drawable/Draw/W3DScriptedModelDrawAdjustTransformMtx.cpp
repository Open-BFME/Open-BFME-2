// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
//
// Three bodies of one retail unit kept together: both callers keep ECX (the
// angle pointer) live across the clamp helper's call and B710D reuses its
// dead Matrix3D& parameter slot for the angle which cl only does when the
// callees are compiled earlier in the same unit.
//   ?Rva000B2BFFClamp@@YAXPAMM@Z                              0x000B2BFF 190B
//   ?rva000B4CE2@W3DScriptedModelDraw@@QAE_NPAM@Z              0x000B4CE2 321B
//   ?rva000B710D@W3DScriptedModelDraw@@QAEXAAVMatrix3D@@@Z     0x000B710D 1068B
// B710D is Zero Hour's W3DModelDraw::adjustTransformMtx extended by BFME
// (BFME1 donor AttachmentTransform007629F0::adjust 0x007629F0): parent
// drawable bone attach with turret-style Z clamp then own-drawable bone
// attach (+0x04 module data +0x40 bone name) then virtual slot 0x104; a 1/30
// per frame Matrix3D::Lerp blend (+0x290/+0x2C0/+0x2C4) and the construction
// height Translate_Z. Its callers 0x000B8440 and 0x000B9EC2 are
// W3DScriptedModelDraw methods in WorldBuilder.
// B4CE2 aims the turret at the AI victim (WorldBuilder twin 0x929CC0):
// victim from AIUpdateInterface::getCurrentVictim; the current weapon must
// be in range; then Obj_Look_At from the object's XY translation toward the
// XY goal at (ai+0x30)+0x24 and the clamp steps m_turnAngle toward the
// look matrix's Z rotation. Retail stores the whole target before loading
// pos (Y then X): cl only keeps that order when target and pos are
// function-scope locals filled with Vector3::Set (canonical WWMath header).
#include <math.h>
#include "ascii_string.h"

#include "matrix3d.h"

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
	Vector3 target;
	Vector3 pos;
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
				target.Set(goal.X, goal.Y, 0.0f);
				pos.Set(obj->m_transform[0][3], obj->m_transform[1][3], 0.0f);
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
