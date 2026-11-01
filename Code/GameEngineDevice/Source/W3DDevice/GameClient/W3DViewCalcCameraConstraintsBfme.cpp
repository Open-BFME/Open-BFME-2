// cl: /ICode/Libraries/Include/Lib /O1 /G5 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /EHsc /Oy-
// Native89A21..89C2D 524B, WB987BA0 confirms pick rays and quarter-width
// clamp; clean BFME1 donor W3DViewCalcCameraConstraintsBfme.cpp reviewed at
// 2f243e26d provides the constraint purpose and reference algorithm.
// Native proves unchanged terrain20 and width3C/height44 virtual slots,
// ground2408/bounds240C..2418/valid241C and GlobalData debugAI9B8.
// Center/bottom Z are dead until center is zeroed before length; omit those
// dead stores. Visible length body gives compiler readonly knowledge and
// restores target register scheduling. Its emitted69B copy independently
// reproduces the existing Coord3D::length provider at3571 exactly.

#include "Coord2D.h"
#include "Coord3D.h"
typedef float Real;typedef int Int;typedef bool Bool;
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
#include "../../../../Libraries/Include/Lib/Region3D.h"
#include "vector3.h"

#include <float.h>
#include <math.h>
inline float Coord3D::length()const{float squares=x*x+y*y+z*z;return(float)sqrt((double)squares); }
class GlobalData
{
public:
	unsigned char m_padding[0x9B8];
	Int m_debugAI;
};

#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

class W3DView
{
public:
	virtual void viewSlot00() = 0;
	virtual void viewSlot04() = 0;
	virtual void viewSlot08() = 0;
	virtual void viewSlot0C() = 0;
	virtual void viewSlot10() = 0;
	virtual void viewSlot14() = 0;
	virtual void viewSlot18() = 0;
	virtual void viewSlot1C() = 0;
	virtual void viewSlot20() = 0;
	virtual void viewSlot24() = 0;
	virtual void viewSlot28() = 0;
	virtual void viewSlot2C() = 0;
	virtual void viewSlot30() = 0;
	virtual void viewSlot34() = 0;
	virtual void viewSlot38() = 0;
	virtual Int getWidth() = 0;
	virtual void viewSlot40() = 0;
	virtual Int getHeight() = 0;

private:
	void calcCameraConstraints();
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);

	unsigned char m_padding0004[0x1C];
	Int m_originX;
	Int m_originY;
	unsigned char m_padding0028[0x2408 - 0x28];
	Real m_groundLevel;
	Region2D m_cameraConstraint;
	Bool m_cameraConstraintValid;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData
extern TerrainLogic *TheTerrainLogic;

void W3DView::calcCameraConstraints()
{
	if (TheTerrainLogic)
	{
		Region3D mapRegion;
		TheTerrainLogic->getExtent(&mapRegion);

		Real maxEdgeZ = m_groundLevel;
		Coord3D center, bottom;
		Vector3 rayStart, rayEnd;
		{
			ICoord2D screen;

			//Pick at the center
			screen.x = 0.5f * getWidth() + m_originX;
			screen.y = 0.5f * getHeight() + m_originY;
			getPickRay(&screen, &rayStart, &rayEnd);

			// LINK: file-static manual inlines of Vector3::Find_X/Y_At_Z
			// (header-verbatim bodies). This TU's copies are not retail's;
			// the calls inline but still emit loser COMDATs. Rebinding here
			// emits nothing (internal linkage, fully inlined). No flags
			// touched.
			center.x = (rayStart.X + ((maxEdgeZ - rayStart.Z) * ((rayEnd.X - rayStart.X) / (rayEnd.Z - rayStart.Z))));
			center.y = (rayStart.Y + ((maxEdgeZ - rayStart.Z) * ((rayEnd.Y - rayStart.Y) / (rayEnd.Z - rayStart.Z))));
			
			screen.y = m_originY + 0.95f * getHeight();
			getPickRay(&screen, &rayStart, &rayEnd);
		}
		bottom.x = (rayStart.X + ((maxEdgeZ - rayStart.Z) * ((rayEnd.X - rayStart.X) / (rayEnd.Z - rayStart.Z))));
		bottom.y = (rayStart.Y + ((maxEdgeZ - rayStart.Z) * ((rayEnd.Y - rayStart.Y) / (rayEnd.Z - rayStart.Z))));
		
		center.x -= bottom.x;
		center.y -= bottom.y;
		center.z = 0.0f;

		Real offset = center.length();
		if (_isnan(offset))
			offset = 0.0f;
		if (offset > mapRegion.hi.x * 0.25f)
			offset = 0.0f;

		if (TheGlobalData->m_debugAI)
			offset = -1000; // push out the constraints so we can look at staging areas.

		m_cameraConstraint.lo.x = mapRegion.lo.x + offset;
		m_cameraConstraint.hi.x = mapRegion.hi.x - offset;
		// this looks inverted, but is correct
		m_cameraConstraint.lo.y = mapRegion.lo.y + offset;
		m_cameraConstraint.hi.y = mapRegion.hi.y - offset;
		m_cameraConstraintValid = true;
	}
}
