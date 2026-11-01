// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// W3DModelDraw::reactToTransformChange @0x000B7FE8 730B.
// Target facts: slot 38 of W3DModelDraw's vtable 0x00BCBFC0 and of the five
// derived draw vtables (0x00BC68F0 0x00BCBC40 0x00BCC650 0x00BCCBE4 0x00BCDC60);
// thiscall RET 0xC; module data +0x04 flags +0x69/+0x6A; drawable +0x08 whose
// template float +0x4A8 (> 1.0f) drives two TheTerrainRenderObject +0x37C0 mask
// circle updates (old position set then new position cleared); render object
// +0x50 takes Set_Transform (slot 21) after adjustTransformMtx (0x000B710D);
// track +0x60 with shroud flag +0x49 and airborne byte +0x131C.
// Donor facts: Zero Hour W3DModelDraw::reactToTransformChange supplies the
// render-object and track spine; Open-BFME-1 W3DModelDrawTransformChange.cpp
// supplies the BFME shroud-mask prefix and translation-only branch.
// BFME 2 adds +0x6A: translation only, then Matrix3D::Rotate_Z by the
// InGameUI angle (0x0029B3C1) when TheInGameUI exists, else the object's
// heading +0x1C0. Retail stores that angle to memory on both arms, which cl
// does for an if/else assigned local but not for a conditional expression.
#include <math.h>
#include "Coord3D.h"
#include "matrix3d.h"

#define SLOT(n) virtual void slot##n();

typedef float Real;

class ThingTemplate
{
public:
	char m_pad00[0x4A8];
	Real m_float4A8;
};

class Object
{
public:
	bool isSignificantlyAboveTerrain() const;
	char m_pad00[0x1C0];
	Real m_orientation;
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	const Matrix3D *getTransformMatrix() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getObject() const { return m_object; }
	char m_pad00[0x04];
	const ThingTemplate *m_template;
	char m_pad08[0xFC - 0x08];
	Object *m_object;
};

#include "../../../../../../GameEngine/Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

struct MaskCirclePoint;

class Rva000ADA1AMask
{
public:
	void rva000ADF90(const MaskCirclePoint *, float, unsigned char);
};

class BaseHeightMapRenderObjClass
{
public:
	Rva000ADA1AMask *getMask() const { return m_mask; }
	char m_pad00[0x37C0];
	Rva000ADA1AMask *m_mask;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class RenderObjClass
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
	virtual void Set_Transform(const Matrix3D &m);
};

class Rva00084206Track
{
public:
	void addCapEdgeToTrack(float x, float y);
	void addEdgeToTrack(float x, float y);
	void setAirborne() { m_airborne = true; }
	char m_pad00[0x131C];
	bool m_airborne;
};

class W3DScriptedModelDraw
{
public:
	void rva000B710D(Matrix3D &mtx);
};

struct W3DModelDrawModuleData
{
	char m_pad00[0x69];
	bool m_bfmeFlag69;
	bool m_bfmeFlag6A;
};

class W3DModelDraw
{
public:
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle);
protected:
	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }
	void adjustTransformMtx(Matrix3D &mtx) { ((W3DScriptedModelDraw *)this)->rva000B710D(mtx); }
private:
	const W3DModelDrawModuleData *m_moduleData;	// 0x04
	Drawable *m_drawable;				// 0x08
	char m_pad0C[0x49 - 0x0C];
	bool m_fullyObscuredByShroud;			// 0x49
	char m_pad4A[0x50 - 0x4A];
	RenderObjClass *m_renderObject;			// 0x50
	char m_pad54[0x60 - 0x54];
	Rva00084206Track *m_trackRenderObject;		// 0x60
};

void W3DModelDraw::reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle)
{
	const W3DModelDrawModuleData *w3DModelDrawModuleData = getW3DModelDrawModuleData();
	const ThingTemplate *thingTemplate = getDrawable()->getTemplate();
	const Coord3D *pos = getDrawable()->getPosition();

	if (thingTemplate->m_float4A8 > 1.0f)
	{
		TheTerrainRenderObject->getMask()->rva000ADF90((const MaskCirclePoint *)oldPos, thingTemplate->m_float4A8, 1);
		TheTerrainRenderObject->getMask()->rva000ADF90((const MaskCirclePoint *)pos, thingTemplate->m_float4A8, 0);
	}

	if (m_renderObject)
	{
		Matrix3D mtx(true);
		if (!w3DModelDrawModuleData->m_bfmeFlag69 && !w3DModelDrawModuleData->m_bfmeFlag6A)
		{
			mtx = *getDrawable()->getTransformMatrix();
		}
		else
		{
			mtx.Set_Translation(getDrawable()->getTransformMatrix()->Get_Translation());
			if (w3DModelDrawModuleData->m_bfmeFlag6A)
			{
				Object *obj = getDrawable()->getObject();
				Real angle;
				if (TheInGameUI)
					angle = TheInGameUI->rva0029B3C1(obj);
				else
					angle = obj->m_orientation;
				mtx.Rotate_Z(angle);
			}
		}
		adjustTransformMtx(mtx);
		m_renderObject->Set_Transform(mtx);
	}

	if (m_trackRenderObject)
	{
		Object *obj = getDrawable()->getObject();
		if (m_fullyObscuredByShroud)
		{
			m_trackRenderObject->addCapEdgeToTrack(pos->x, pos->y);
		}
		else
		{
			if (obj && obj->isSignificantlyAboveTerrain())
				m_trackRenderObject->setAirborne();
			m_trackRenderObject->addEdgeToTrack(pos->x, pos->y);
		}
	}
}
