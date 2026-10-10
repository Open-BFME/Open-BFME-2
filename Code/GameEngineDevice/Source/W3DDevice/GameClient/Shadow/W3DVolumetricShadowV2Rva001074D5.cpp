// cl: /O1 /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /GR-
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

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

struct Open2Triple
{
public:
	Real m_x;
	Real m_y;
	Real m_z;
};

class W3DShadowManager
{
public:
	Vector3 &getLightPosWorld(int which);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, void *normal) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
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
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
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
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void v142();
	virtual void v143();
	virtual void v144();
	virtual Real getHeightMapHeight(Real x, Real y, void *normal) const;
};

#include "wwmath.h"

extern TerrainLogic *TheTerrainLogic;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;




// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadowV2.h
inline void ScaleShadowOffset(Vector3 &v,float k){v.X=v.X*k;v.Y=v.Y*k;v.Z=v.Z*k;}
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
