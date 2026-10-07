// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?Update@W3DVolumetricShadow@@QAEX_N@Z @0x000F4017 736B.
//
// W3DVolumetricShadow::Update: rebuilds this caster's shadow volumes when it
// can be visible. Target evidence: retail 0x000F4017..0x000F42F7 (plain
// frame, ret 4), called from renderShadows (0x000F4AB7) and through the
// Update(true) forwarder 0x000F42F7. Callees: RenderObjClass::Get_Position
// (0x0013B8A0), TheTerrainLogic slot 6 getGroundHeight or
// TheTerrainRenderObject slot 145 getHeightMapHeight, CRT fabs, the minimum
// terrain height at TheTerrainRenderObject+0x37D8,
// updateOptimalExtrusionPadding (0x000F1212, reads m_robj and
// m_shadowLengthScale, writes the padding) and updateVolumes (0x000F3D23,
// the per-light mesh loop over m_geometry). Constants 2.0f, 1.5f and 0.1f
// are the ZH AIRBORNE_UNIT_GROUND_DELTA,
// MAX_SHADOW_LENGTH_EXTRA_AIRBORNE_SCALE_FACTOR and SHADOW_EXTRUSION_BUFFER.
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp Update (0x007BF7D0), itself
// the ZH body. BFME 2 deltas read from retail: a forceUpdate argument that
// is parked in the byte at +0x4900 while the shadow vertex/index buffers
// (0x00DEBCDC/0x00DEBCE0, created by ReAcquireResources) are missing, the
// X bound test only for casters with more than one mesh (+0x2094), and,
// when an update was forced, every XYZ vertex buffer's render-task list is
// cleared. Field names past the ZH members are descriptive.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define NULL 0

#define AIRBORNE_UNIT_GROUND_DELTA	2.0f
#define MAX_SHADOW_LENGTH_EXTRA_AIRBORNE_SCALE_FACTOR	1.5f
#define SHADOW_EXTRUSION_BUFFER	0.1f

#include <math.h>

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real X, Y, Z;
};

__forceinline bool operator==(const Vector3 &a, const Vector3 &b)
{
	return ((a.X == b.X) && (a.Y == b.Y) && (a.Z == b.Z));
}

class WWMath
{
public:
	static float Fabs(float val)
	{
		int value = *(int *)&val;
		value &= 0x7fffffff;
		return *(float *)&value;
	}
};

struct Coord3D;

class RenderObjClass
{
public:
	Vector3 Get_Position(void) const;
};

class TerrainLogic
{
public:
	virtual void vslot000(void);
	virtual void vslot001(void);
	virtual void vslot002(void);
	virtual void vslot003(void);
	virtual void vslot004(void);
	virtual void vslot005(void);
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const;
};
extern TerrainLogic *TheTerrainLogic;

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
	Real getMinHeight(void) const { return m_minHeight; }
private:
	char m_pad[0x37d4];
	Real m_minHeight;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DBufferManager
{
public:
	enum VBM_FVF_TYPES { VBM_FVF_XYZ, MAX_FVF = 9 };
	struct W3DRenderTask
	{
		W3DRenderTask *m_nextTask;
	};
	struct W3DVertexBuffer
	{
		char m_pad[0x10];
		W3DVertexBuffer *m_NextVB;
		char m_pad14[4];
		W3DRenderTask *m_renderTaskList;
	};
	W3DVertexBuffer *getNextVertexBuffer(W3DVertexBuffer *pVb, VBM_FVF_TYPES type)
	{
		if (pVb == 0) return m_W3DVertexBuffers[type];
		return pVb->m_NextVB;
	}
private:
	char m_pad[0x9000];
	W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF];
};
extern W3DBufferManager *TheW3DBufferManager;

class W3DShadowGeometry
{
public:
	Int getMeshCount(void) { return m_meshCount; }
private:
	char m_pad[0x2094];
	Int m_meshCount;
};

class W3DVolumetricShadow
{
public:
	void Update(Bool forceUpdate);
protected:
	void updateVolumes(Real zoffset);
	void updateOptimalExtrusionPadding(void);
	void *m_vtable;
	char m_pad4[0x64];
	W3DVolumetricShadow *m_next;
	W3DShadowGeometry *m_geometry;
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
	char m_pad80[0x4880];
	Bool m_pendingUpdate;
};

struct IDirect3DVertexBuffer8;
struct IDirect3DIndexBuffer8;
extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;

extern Real bcX, bcY, bcZ, beX, beY, beZ;

void W3DVolumetricShadow::Update(Bool forceUpdate)
{
	static Int currentTime, lastTime;
	static Vector3 originCompareVector(0,0,0);
	Vector3 pos;

	// sanity
	if( m_geometry == NULL)
		return;

	if (shadowVertexBufferD3D == NULL || shadowIndexBufferD3D == NULL)
	{
		m_pendingUpdate |= forceUpdate;
		return;
	}

	forceUpdate = forceUpdate | m_pendingUpdate;
	m_pendingUpdate = false;

	{
		pos=m_robj->Get_Position();
		if (pos == originCompareVector)
		{	//the transform on this object was never set so we can't make any determination
			//if it's visible or what the shadow looks like.
			return;
		}
		Real groundHeight;
		if (TheTerrainLogic)
			groundHeight=TheTerrainLogic->getGroundHeight(pos.X,pos.Y);	//logic knows about bridges so use if available.
		else
			groundHeight=TheTerrainRenderObject->getHeightMapHeight(pos.X,pos.Y, NULL);
		if (fabs(pos.Z - groundHeight) >= AIRBORNE_UNIT_GROUND_DELTA)
		{
			Real extent = MAX_SHADOW_LENGTH_EXTRA_AIRBORNE_SCALE_FACTOR * m_robjExtent;
			if (WWMath::Fabs(pos.X - bcX) > (beX + extent) ||
				WWMath::Fabs(pos.Y - bcY) > (beY + extent) ||
				WWMath::Fabs(pos.Z - bcZ) > (beZ + extent))
				return;	//shadow can't be visible so no point in updating.

			//this unit is above ground, extend shadow volume to reach lowest point on the terrain plus extra bit to make
			//sure shadow goes under ground.
			updateVolumes(fabs(pos.Z - TheTerrainRenderObject->getMinHeight()) + SHADOW_EXTRUSION_BUFFER);
		}
		else
		{
			if ((m_geometry->getMeshCount() > 1 && WWMath::Fabs(pos.X - bcX) > (beX + m_robjExtent)) ||
				WWMath::Fabs(pos.Y - bcY) > (beY + m_robjExtent) ||
				WWMath::Fabs(pos.Z - bcZ) > (beZ + m_robjExtent))
				return;	//shadow can't be visible so no point in updating.

			//check if this object has never had it's extrusion length updated.  Will only be true for
			//immobile objects because finding an optimal extrusion length is expensive.
			if (!m_extraExtrusionPadding)
				updateOptimalExtrusionPadding();

			updateVolumes(m_extraExtrusionPadding);
		}

		if (forceUpdate)
		{
			for (W3DBufferManager::W3DVertexBuffer *vb = TheW3DBufferManager->getNextVertexBuffer(NULL, W3DBufferManager::VBM_FVF_XYZ);
				vb; vb = TheW3DBufferManager->getNextVertexBuffer(vb, W3DBufferManager::VBM_FVF_XYZ))
				vb->m_renderTaskList = NULL;
		}

		// update delay time
		lastTime = currentTime;
	}

}  // end Update
