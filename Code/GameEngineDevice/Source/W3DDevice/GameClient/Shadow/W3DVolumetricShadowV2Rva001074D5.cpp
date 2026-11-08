// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /GR- /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva001074D5@W3DVolumetricShadowV2@@QAEXXZ @0x001074D5 532B

class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;

typedef float Real;

#include "vector3.h"

class ShadowOffset
{
public:
	Real X;
	Real Y;
	Real Z;

	__forceinline Real Length2() const
	{
		return X * X + Y * Y + Z * Z;
	}

	__forceinline Real Length2D() const
	{
		return X * X + Y * Y;
	}
};

#include "../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

struct Open2Triple
{
public:
	Real m_x;
	Real m_y;
	Real m_z;
};

#include "../../../../Include/W3DDevice/GameClient/W3DShadowManager.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
#include "../../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
#include "../../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

#include "wwmath.h"

extern TerrainLogic *TheTerrainLogic;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;




// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadowV2.h
inline void ScaleShadowOffset(Vector3 &vec,float k){vec.X=vec.X*k;vec.Y=vec.Y*k;vec.Z=vec.Z*k;}
class W3DVolumetricShadowV2
{
	unsigned char m_unreconstructed_000[0x74];
	RenderObjClass *m_robj;
	unsigned char m_unreconstructed_078[0x0c];
	Real m_extraExtrusionPadding;
	Real m_shadowLengthScale;
	Real m_lightOffsetZAdd;
	Vector3 m_lightOffset;

public:
	void rva001074D5();
};

void W3DVolumetricShadowV2::rva001074D5()
{
	Vector3 pos = m_robj->Get_Position();
	m_lightOffset=pos;

	const Vector3 *light = &((W3DShadowManager *)TheW3DShadowManager)->getLightPosWorld(0);
	m_lightOffset-=*(light?light:light);

	m_lightOffset.Normalize();

	if (m_shadowLengthScale > 0.0f)
	{
		Real horizontalSquared = (m_lightOffset.X*m_lightOffset.X+m_lightOffset.Y*m_lightOffset.Y);
		horizontalSquared *= m_shadowLengthScale;
		horizontalSquared *= m_shadowLengthScale;
		if (horizontalSquared > m_lightOffset.Z)
			m_lightOffset.Z = WWMath::Sqrt(horizontalSquared);
	}

	if (!(m_lightOffset.Z > -0.01f))
	{
		Real groundHeight;
		if (TheTerrainLogic)
			groundHeight = TheTerrainLogic->getGroundHeight(pos.X, pos.Y, 0);
		else
			groundHeight = TheTerrainRenderObject->getHeightMapHeight(pos.X,
				pos.Y, 0);

		Real scale = (pos.Z + m_extraExtrusionPadding - groundHeight +
			m_lightOffsetZAdd) * (-1.0f / m_lightOffset.Z);
		ScaleShadowOffset(m_lightOffset,scale);
	}
}
