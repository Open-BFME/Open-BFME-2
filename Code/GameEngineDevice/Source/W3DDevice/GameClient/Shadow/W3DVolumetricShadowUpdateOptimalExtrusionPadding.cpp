// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?updateOptimalExtrusionPadding@W3DVolumetricShadow@@IAEXXZ @0x000F1212 790B.
//
// W3DVolumetricShadow::updateOptimalExtrusionPadding: finds how far below
// the caster the shadow volume must reach. Target evidence: retail
// 0x000F1212..0x000F1528 (ebp-0x78 frame, plain ret), called from Update
// (0x000F4017) when the padding at +0x7C is still zero. Callees:
// W3DShadowManager::getLightPosWorld (0x0009A497), CRT sqrt,
// RenderObjClass::Get_Position (0x0013B8A0), RenderObjClass slot 66
// Get_Bounding_Box, WWMath::Inv_Sqrt (0x0004233A) and
// TheTerrainRenderObject slot 145 getHeightMapHeight.
// Donor: the ZH W3DVolumetricShadow::updateOptimalExtrusionPadding (light
// clamp by m_shadowLengthScale, top bounding-box corners, the final
// objPos.Z - baseGroundHeight + SHADOW_EXTRUSION_BUFFER). BFME 2 replaces
// the ZH Cast_Ray and dip search with a march read from retail: from each
// corner, step 20 units along the normalized light ray up to 5120, keep
// the lowest sampled terrain height, and stop the corner once a sample is
// above the ray and the point 200 units further on is above the terrain
// again. The constant names are descriptive. operator+ adds b to a, which
// is the operand order retail loads for the corner sum.

typedef float Real;
typedef int Int;

#define NULL 0

#include <math.h>

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	__forceinline void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline float Length2(void) const { return X*X + Y*Y + Z*Z; }
	__forceinline void Normalize(void);
	Real X, Y, Z;
};

__forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(b.X+a.X, b.Y+a.Y, b.Z+a.Z); }
__forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b) { return Vector3(a.X-b.X, a.Y-b.Y, a.Z-b.Z); }
__forceinline Vector3 operator*(const Vector3 &a, float k) { return Vector3(a.X*k, a.Y*k, a.Z*k); }

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

__forceinline void Vector3::Normalize(void)
{
	float len2 = Length2();
	if (len2 != 0.0f)
	{
		float oolen = WWMath::Inv_Sqrt(len2);
		X *= oolen;
		Y *= oolen;
		Z *= oolen;
	}
}

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

class RenderObjClass
{
public:
	virtual void vslot000(void);
	virtual void vslot001(void);
	virtual void vslot002(void);
	virtual void vslot003(void);
	virtual void vslot004(void);
	virtual void vslot005(void);
	virtual void vslot006(void);
	virtual void vslot007(void);
	virtual void vslot008(void);
	virtual void vslot009(void);
	virtual void vslot010(void);
	virtual void vslot011(void);
	virtual void vslot012(void);
	virtual void vslot013(void);
	virtual void vslot014(void);
	virtual void vslot015(void);
	virtual void vslot016(void);
	virtual void vslot017(void);
	virtual void vslot018(void);
	virtual void vslot019(void);
	virtual void vslot020(void);
	virtual void vslot021(void);
	virtual void vslot022(void);
	virtual void vslot023(void);
	virtual void vslot024(void);
	virtual void vslot025(void);
	virtual void vslot026(void);
	virtual void vslot027(void);
	virtual void vslot028(void);
	virtual void vslot029(void);
	virtual void vslot030(void);
	virtual void vslot031(void);
	virtual void vslot032(void);
	virtual void vslot033(void);
	virtual void vslot034(void);
	virtual void vslot035(void);
	virtual void vslot036(void);
	virtual void vslot037(void);
	virtual void vslot038(void);
	virtual void vslot039(void);
	virtual void vslot040(void);
	virtual void vslot041(void);
	virtual void vslot042(void);
	virtual void vslot043(void);
	virtual void vslot044(void);
	virtual void vslot045(void);
	virtual void vslot046(void);
	virtual void vslot047(void);
	virtual void vslot048(void);
	virtual void vslot049(void);
	virtual void vslot050(void);
	virtual void vslot051(void);
	virtual void vslot052(void);
	virtual void vslot053(void);
	virtual void vslot054(void);
	virtual void vslot055(void);
	virtual void vslot056(void);
	virtual void vslot057(void);
	virtual void vslot058(void);
	virtual void vslot059(void);
	virtual void vslot060(void);
	virtual void vslot061(void);
	virtual void vslot062(void);
	virtual void vslot063(void);
	virtual void vslot064(void);
	virtual void vslot065(void);
	virtual const AABoxClass &Get_Bounding_Box(void) const;
	Vector3 Get_Position(void) const;
};

class W3DShadowManager
{
public:
	Vector3 &getLightPosWorld(Int lightIndex);
};
extern W3DShadowManager *TheW3DShadowManager;

struct Coord3D;

class BaseHeightMapRenderObjClass
{
public:
	virtual void vslot000(void);
	virtual void vslot001(void);
	virtual void vslot002(void);
	virtual void vslot003(void);
	virtual void vslot004(void);
	virtual void vslot005(void);
	virtual void vslot006(void);
	virtual void vslot007(void);
	virtual void vslot008(void);
	virtual void vslot009(void);
	virtual void vslot010(void);
	virtual void vslot011(void);
	virtual void vslot012(void);
	virtual void vslot013(void);
	virtual void vslot014(void);
	virtual void vslot015(void);
	virtual void vslot016(void);
	virtual void vslot017(void);
	virtual void vslot018(void);
	virtual void vslot019(void);
	virtual void vslot020(void);
	virtual void vslot021(void);
	virtual void vslot022(void);
	virtual void vslot023(void);
	virtual void vslot024(void);
	virtual void vslot025(void);
	virtual void vslot026(void);
	virtual void vslot027(void);
	virtual void vslot028(void);
	virtual void vslot029(void);
	virtual void vslot030(void);
	virtual void vslot031(void);
	virtual void vslot032(void);
	virtual void vslot033(void);
	virtual void vslot034(void);
	virtual void vslot035(void);
	virtual void vslot036(void);
	virtual void vslot037(void);
	virtual void vslot038(void);
	virtual void vslot039(void);
	virtual void vslot040(void);
	virtual void vslot041(void);
	virtual void vslot042(void);
	virtual void vslot043(void);
	virtual void vslot044(void);
	virtual void vslot045(void);
	virtual void vslot046(void);
	virtual void vslot047(void);
	virtual void vslot048(void);
	virtual void vslot049(void);
	virtual void vslot050(void);
	virtual void vslot051(void);
	virtual void vslot052(void);
	virtual void vslot053(void);
	virtual void vslot054(void);
	virtual void vslot055(void);
	virtual void vslot056(void);
	virtual void vslot057(void);
	virtual void vslot058(void);
	virtual void vslot059(void);
	virtual void vslot060(void);
	virtual void vslot061(void);
	virtual void vslot062(void);
	virtual void vslot063(void);
	virtual void vslot064(void);
	virtual void vslot065(void);
	virtual void vslot066(void);
	virtual void vslot067(void);
	virtual void vslot068(void);
	virtual void vslot069(void);
	virtual void vslot070(void);
	virtual void vslot071(void);
	virtual void vslot072(void);
	virtual void vslot073(void);
	virtual void vslot074(void);
	virtual void vslot075(void);
	virtual void vslot076(void);
	virtual void vslot077(void);
	virtual void vslot078(void);
	virtual void vslot079(void);
	virtual void vslot080(void);
	virtual void vslot081(void);
	virtual void vslot082(void);
	virtual void vslot083(void);
	virtual void vslot084(void);
	virtual void vslot085(void);
	virtual void vslot086(void);
	virtual void vslot087(void);
	virtual void vslot088(void);
	virtual void vslot089(void);
	virtual void vslot090(void);
	virtual void vslot091(void);
	virtual void vslot092(void);
	virtual void vslot093(void);
	virtual void vslot094(void);
	virtual void vslot095(void);
	virtual void vslot096(void);
	virtual void vslot097(void);
	virtual void vslot098(void);
	virtual void vslot099(void);
	virtual void vslot100(void);
	virtual void vslot101(void);
	virtual void vslot102(void);
	virtual void vslot103(void);
	virtual void vslot104(void);
	virtual void vslot105(void);
	virtual void vslot106(void);
	virtual void vslot107(void);
	virtual void vslot108(void);
	virtual void vslot109(void);
	virtual void vslot110(void);
	virtual void vslot111(void);
	virtual void vslot112(void);
	virtual void vslot113(void);
	virtual void vslot114(void);
	virtual void vslot115(void);
	virtual void vslot116(void);
	virtual void vslot117(void);
	virtual void vslot118(void);
	virtual void vslot119(void);
	virtual void vslot120(void);
	virtual void vslot121(void);
	virtual void vslot122(void);
	virtual void vslot123(void);
	virtual void vslot124(void);
	virtual void vslot125(void);
	virtual void vslot126(void);
	virtual void vslot127(void);
	virtual void vslot128(void);
	virtual void vslot129(void);
	virtual void vslot130(void);
	virtual void vslot131(void);
	virtual void vslot132(void);
	virtual void vslot133(void);
	virtual void vslot134(void);
	virtual void vslot135(void);
	virtual void vslot136(void);
	virtual void vslot137(void);
	virtual void vslot138(void);
	virtual void vslot139(void);
	virtual void vslot140(void);
	virtual void vslot141(void);
	virtual void vslot142(void);
	virtual void vslot143(void);
	virtual void vslot144(void);
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#define SHADOW_SAMPLING_INTERVAL	20.0f
#define SHADOW_SAMPLING_LOOKAHEAD	200.0f
#define MAX_SHADOW_SAMPLING_LENGTH	5120.0f
#define SHADOW_EXTRUSION_BUFFER	0.1f

class W3DVolumetricShadow
{
protected:
	void updateOptimalExtrusionPadding(void);
	void *m_vtable;
	char m_pad4[0x6c];
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
};

void W3DVolumetricShadow::updateOptimalExtrusionPadding(void)
{
	if (m_robj)
	{
		Vector3 lightPosWorld = TheW3DShadowManager->getLightPosWorld(0);

		if (m_shadowLengthScale)
		{
			Real lightXYDistance = sqrt(lightPosWorld.X*lightPosWorld.X + lightPosWorld.Y*lightPosWorld.Y);
			Real newZ = lightXYDistance*m_shadowLengthScale;
			if (newZ > lightPosWorld.Z)
				lightPosWorld.Z = newZ;
		}

		Vector3 objPos = m_robj->Get_Position();
		Real baseGroundHeight = objPos.Z;
		const AABoxClass &box = m_robj->Get_Bounding_Box();
		Vector3 Corners[4];

		Corners[0] = box.Center + box.Extent;
		Corners[1] = Corners[0];
		Corners[1].X -= 2.0f*box.Extent.X;
		Corners[2] = Corners[1];
		Corners[2].Y -= 2.0f*box.Extent.Y;
		Corners[3] = Corners[2];
		Corners[3].X += 2.0f*box.Extent.X;

		for (Int i=0; i<4; i++)
		{
			Vector3 lightRay = Corners[i] - lightPosWorld;
			lightRay.Normalize();

			Vector3 step = lightRay*SHADOW_SAMPLING_INTERVAL;
			Vector3 lookAhead = lightRay*SHADOW_SAMPLING_LOOKAHEAD;
			Vector3 terrainPoint = Corners[i];

			for (Real len = SHADOW_SAMPLING_INTERVAL; len < MAX_SHADOW_SAMPLING_LENGTH; len += SHADOW_SAMPLING_INTERVAL)
			{
				terrainPoint += step;
				Real terrainHeight = TheTerrainRenderObject->getHeightMapHeight(terrainPoint.X, terrainPoint.Y, NULL);
				if (terrainHeight > terrainPoint.Z)
				{
					Vector3 aheadPoint = terrainPoint + lookAhead;
					if (aheadPoint.Z > TheTerrainRenderObject->getHeightMapHeight(aheadPoint.X, aheadPoint.Y, NULL))
						break;
				}
				if (terrainHeight < baseGroundHeight)
					baseGroundHeight = terrainHeight;
			}
		}

		m_extraExtrusionPadding = objPos.Z - baseGroundHeight + SHADOW_EXTRUSION_BUFFER;
	}
}
