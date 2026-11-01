// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?rva003FBFF3@LivingWorldVisual@@QAEXABVMatrix3D@@@Z retail
// 0x003FBFF3..0x003FC149 (342 bytes RET 4). It sits among the LivingWorldVisual
// bodies (setHouseColor 0x003FB602 / createPickboxObject 0x003FC74A) and works
// on the same +0x08 primary render object. The WB twin 0x010702E0 (unnamed)
// has the same inline shape. No direct caller or table reference was found,
// so the name stays address-qualified.
// Body: when the primary render object exists, take the rotation of the
// given transform (rowed Matrix3 ctor 0x00716890). Copy the object's
// transform (Get_Transform: Validate_Transform slot 20 then the +0x18 matrix)
// and put the rotation in it (rowed Matrix3D::Set_Rotation 0x00711EF0).
// Re-apply the object's +0x48 scale to the 3x3 columns. Then Set_Transform
// (slot 21) on the primary and, when present, the +0x14 render object.
// The transform uses the shared WWMath matrix and RenderObjClass interface.
#include "matrix3.h"
typedef float Real;

class Matrix3D;

#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"





class LivingWorldVisual
{
public:
	virtual void setHouseColor(const int &color);
	void rva003FBFF3(const Matrix3D &transform);
	void rva003FC291(float scale);
private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;										// +0x08
	unsigned char m_pad0C[0x14 - 0x0C];
	RenderObjClass *m_secondaryRObj;
	unsigned char unknown18[0x7C-0x18]; Real m_requestedScale;									// +0x14
};

void LivingWorldVisual::rva003FBFF3(const Matrix3D &transform)
{
	if (m_primaryRObj)
	{
		Matrix3 rotation(transform);
		Matrix3D tm = m_primaryRObj->Get_Transform();
		tm.Set_Rotation(rotation);
		tm.Scale(m_primaryRObj->Get_ObjectScale());
		m_primaryRObj->Set_Transform(tm);
		if (m_secondaryRObj)
			m_secondaryRObj->Set_Transform(tm);
	}
}

// Native3FC291..3FC3E4 RET4,339B and WB10715C0 copy primary transform,
// scale its3x3 by requested/object scale and set both render-object scales.
// Named createRenderObject and this helper receive the SAME unchanged this
// in native5C4DE0 and WB LivingWorldIconSubObject ctor1566710. This proves
// LivingWorldVisual ownership; the original method name remains unknown.
// The const reference materializes the genuine computed float temporary:
// native stores it at frame-4 and reloads it after the first multiply.
// The shared matrix supplies the transform copy and column scaling.
void LivingWorldVisual::rva003FC291(float scale) {
 RenderObjClass *renderObj=m_primaryRObj;
 if(!renderObj)return;
 m_requestedScale=scale;
 Matrix3D tm=renderObj->Get_Transform();
 const Real &extra=scale / m_primaryRObj->Get_ObjectScale();
 tm.Scale(extra);
 m_primaryRObj->Set_ObjectScale(scale);
 m_primaryRObj->Set_Transform(tm);
 if(m_secondaryRObj){m_secondaryRObj->Set_ObjectScale(scale);m_secondaryRObj->Set_Transform(tm);}
}
