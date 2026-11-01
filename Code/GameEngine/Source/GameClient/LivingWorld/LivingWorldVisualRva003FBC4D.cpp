// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?rva003FBC4D@LivingWorldVisual@@QAEXM@Z retail
// 0x003FBC4D..0x003FBD9F (338 bytes RET 4). It sits among the LivingWorldVisual
// bodies just before rva003FBFF3 (LivingWorldVisualRva003FBFF3.cpp) and works
// on the same +0x08 primary and +0x14 secondary render objects. The WB twin
// 0x01071340 (unnamed) has the same statements. No direct caller or table
// reference was found so the name stays address-qualified.
// Body: when the primary render object exists, copy its transform
// (Get_Transform: Validate_Transform slot 20 then the +0x18 matrix), take its
// +0x48 object scale times the given factor into +0x7C, scale the 3x3 columns
// of the copy by the factor, and give the new object scale (slot 93) and the
// scaled transform (Set_Transform slot 21) to the primary and, when present,
// the secondary render object.
// The transform uses the shared WWMath matrix and RenderObjClass interface.
typedef float Real;



#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class LivingWorldVisual
{
public:
	virtual void setHouseColor(const int &color);
	void rva003FBC4D(Real scale);
private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;										// +0x08
	unsigned char m_pad0C[0x14 - 0x0C];
	RenderObjClass *m_secondaryRObj;									// +0x14
	unsigned char m_pad18[0x7C - 0x18];
	Real m_scale;														// +0x7C
};

void LivingWorldVisual::rva003FBC4D(Real scale)
{
	if (m_primaryRObj)
	{
		Matrix3D tm = m_primaryRObj->Get_Transform();
		Real objectScale = m_primaryRObj->Get_ObjectScale() * scale;
		m_scale = objectScale;
		tm.Scale(scale);
		m_primaryRObj->Set_ObjectScale(objectScale);
		m_primaryRObj->Set_Transform(tm);
		if (m_secondaryRObj)
		{
			m_secondaryRObj->Set_ObjectScale(objectScale);
			m_secondaryRObj->Set_Transform(tm);
		}
	}
}
