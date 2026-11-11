// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
//
// ?updateBounds@W3DShadowTexture@@QAEXAAVVector3@@PAVRenderObjClass@@@Z
// retail 0x00109648..0x00109BEB (1443 bytes) thiscall RET 8.
// BFME 1 W3DProjectedShadow.cpp W3DShadowTexture::updateBounds (Zero Hour
// lineage): the render object's bounding box is projected from the light
// onto the ground below the object, rebounded and recentred in object
// space. The WWMath Vector3/AABoxClass/SphereClass inlines and WWMath::Sqrt
// are the real Zero Hour headers. Target facts: box +0x64, sphere +0x7C,
// RenderObjClass::Get_Position 0x0013B8A0 and Get_Bounding_Box vtable slot
// +0x108. The box assignment reaches the 24-byte copy body 0x0009AC04 (ICF
// group of the rowed Region3D copy constructor); the ledger's AABoxClass
// operator= name is already the unfolded library copy 0x001492E0, so this
// unit spells that copy through the Region3D owner.
#include "always.h"
#include "vector3.h"
#include "aabox.h"
#include "sphere.h"
#include <math.h>

typedef float Real;

#include "../../../../../Libraries/Include/Lib/Region3D.h"

#include "../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class W3DShadowTexture
{
public:
	void updateBounds(Vector3 &lightPos, RenderObjClass *robj);

private:
	char m_pad00[0x64];
	AABoxClass m_areaEffectBox;			// +0x64
	SphereClass m_areaEffectSphere;		// +0x7C
};

void W3DShadowTexture::updateBounds(Vector3 &lightPos, RenderObjClass *robj)
{
		AABoxClass	&box=m_areaEffectBox;	///@todo: fix for multiple lights
		Vector3			objPos;
		Vector3 Corners[8];
		Vector3 lightRay;
		Real floorZ;
		Real vectorScale,vectorScaleTemp, vectorScaleMax,length;

		//calculate local bounding box of shadow projection
		objPos=robj->Get_Position();
		((Region3D *)&box)->Region3D::Region3D(*(const Region3D *)&robj->Get_Bounding_Box());
		floorZ = objPos.Z - 2.0f;	//lower slightly so shadows go under ground.

		//project each box corner to base of object to determine rough extent of shadow
		//Get vertices of top of bounding box
		Corners[0]=box.Center+box.Extent;	//top right corner
		Corners[1]=Corners[0];
		Corners[1].X -= 2.0f*box.Extent.X;		//top left corner
		Corners[2]=Corners[1];
		Corners[2].Y -= 2.0f*box.Extent.Y;		//bottom left corner
		Corners[3]=Corners[2];
		Corners[3].X += 2.0f*box.Extent.X;		//bottom right corner

		//Project top volume corners onto ground plane
		lightRay = Corners[0] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleMax=vectorScale=(Real)fabs((Corners[0].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[4]=Corners[0]+lightRay*vectorScale;
		vectorScaleMax *= length;

		lightRay = Corners[1] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleTemp=(Real)fabs((Corners[1].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[5]=Corners[1]+lightRay*vectorScaleTemp;
		vectorScaleTemp *= length;

		if (vectorScaleTemp > vectorScaleMax)
			vectorScaleMax=vectorScaleTemp;	//keep track of maximum required extrusion length.

		lightRay = Corners[2] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScale=(Real)fabs((Corners[2].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[6]=Corners[2]+lightRay*vectorScale;
		vectorScale *= length;

		if (vectorScale > vectorScaleMax)
			vectorScaleMax=vectorScale;	//keep track of maximum required extrusion length.

		lightRay = Corners[3] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleTemp=(Real)fabs((Corners[3].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[7]=Corners[3]+lightRay*vectorScaleTemp;
		vectorScaleTemp *= length;

		if (vectorScaleTemp > vectorScaleMax)
			vectorScaleMax=vectorScaleTemp;	//keep track of maximum required extrusion length.

		box.Init(Corners, 8);	//generate a new bounding box to fit the shadow projection
		m_areaEffectSphere.Init(box.Center,box.Extent.Length());

		m_areaEffectSphere.Center -= objPos;	//translate sphere to object space.
		box.Translate(-objPos);	//translate box to object space.
}
