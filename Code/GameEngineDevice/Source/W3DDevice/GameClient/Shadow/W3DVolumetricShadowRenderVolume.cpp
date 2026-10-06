// cl: /O1 /DNDEBUG /MD
// ?RenderVolume@W3DVolumetricShadow@@IAEXHH@Z @0x000F49D0 231B.
// W3DVolumetricShadow::RenderVolume(int meshIndex, int lightIndex): refresh
// the robj transform from its drawable when present (Get_User_Data /
// drawable +0x441 flag / getTransformMatrix / Set_Transform), else the
// no-drawable vcall pair; resolve the lod subobject via the mesh record's
// m_meshRobjIndex (Peek_Lod_Model slot 138) with Validate_Transform plus the
// plain +0x18 transform (no Validate call in retail); flag30 meshes with a
// MESH Class_ID render from the global identity matrix; dispatch static vs
// dynamic through RenderMeshVolume / RenderDynamicMeshVolume on the
// SHADOW_DYNAMIC bit. Donor shape: Open-BFME-1
// W3DVolumetricShadowRenderVolume.cpp RenderVolume (same name/signature/
// mesh record/flag30/identity-matrix/DYNAMIC-branch); target prologue and
// slot numbers differ (Get_User_Data 87, Set_Transform 21, Peek 139,
// Class_ID 3, Validate 20).

class Matrix3D;
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

#define ROPAD(n) virtual void roPad##n(void)
class RenderObjClass
{
public:
	enum { CLASSID_MESH = 0 };
	ROPAD(00); ROPAD(01); ROPAD(02);
	virtual int Class_ID(void);
	ROPAD(04); ROPAD(05); ROPAD(06); ROPAD(07); ROPAD(08);
	ROPAD(09); ROPAD(10); ROPAD(11); ROPAD(12); ROPAD(13);
	ROPAD(14); ROPAD(15); ROPAD(16); ROPAD(17); ROPAD(18); ROPAD(19);
	virtual void Validate_Transform(void);
	virtual void Set_Transform(const Matrix3D &m);
	ROPAD(22); ROPAD(23); ROPAD(24); ROPAD(25); ROPAD(26);
	ROPAD(27); ROPAD(28); ROPAD(29); ROPAD(30); ROPAD(31);
	ROPAD(32); ROPAD(33); ROPAD(34); ROPAD(35); ROPAD(36);
	ROPAD(37); ROPAD(38); ROPAD(39); ROPAD(40); ROPAD(41);
	virtual void roSlot42(void);
	ROPAD(43); ROPAD(44); ROPAD(45); ROPAD(46);
	virtual int roSlot47(void);
	ROPAD(48); ROPAD(49); ROPAD(50); ROPAD(51); ROPAD(52);
	ROPAD(53); ROPAD(54); ROPAD(55); ROPAD(56); ROPAD(57);
	ROPAD(58); ROPAD(59); ROPAD(60); ROPAD(61); ROPAD(62);
	ROPAD(63); ROPAD(64); ROPAD(65); ROPAD(66); ROPAD(67);
	ROPAD(68); ROPAD(69); ROPAD(70); ROPAD(71); ROPAD(72);
	ROPAD(73); ROPAD(74); ROPAD(75); ROPAD(76); ROPAD(77);
	ROPAD(78); ROPAD(79); ROPAD(80); ROPAD(81); ROPAD(82);
	ROPAD(83); ROPAD(84); ROPAD(85); ROPAD(86);
	virtual void *Get_User_Data(void);
	ROPAD(88); ROPAD(89); ROPAD(90); ROPAD(91); ROPAD(92);
	ROPAD(93); ROPAD(94); ROPAD(95); ROPAD(96); ROPAD(97);
	ROPAD(98); ROPAD(99); ROPAD(100); ROPAD(101); ROPAD(102);
	ROPAD(103); ROPAD(104); ROPAD(105); ROPAD(106); ROPAD(107);
	ROPAD(108); ROPAD(109); ROPAD(110); ROPAD(111); ROPAD(112);
	ROPAD(113); ROPAD(114); ROPAD(115); ROPAD(116); ROPAD(117);
	ROPAD(118); ROPAD(119); ROPAD(120); ROPAD(121); ROPAD(122);
	ROPAD(123); ROPAD(124); ROPAD(125); ROPAD(126); ROPAD(127);
	ROPAD(128); ROPAD(129); ROPAD(130); ROPAD(131); ROPAD(132);
	ROPAD(133); ROPAD(134); ROPAD(135); ROPAD(136); ROPAD(137);
	// Peek_Lod_Model is really HLod's (slot 138); called here on the robj
	// pointer itself since the hlod and robj are the same object.
	virtual RenderObjClass *Peek_Lod_Model(int lod, int model);
	// Retail reads the transform at +0x18 with no Validate call (unlike the
	// ZH Get_Transform); the explicit Validate_Transform above covers it.
	const Matrix3D *Get_Transform(void) const { return (const Matrix3D *)((const char *)this + 0x18); }
};
#undef ROPAD

class Drawable
{
public:
	const Matrix3D *getTransformMatrix(void) const;
	char m_pad00[0x441];
	// Clear means refresh the robj transform (donor tests +0x3b1 instead).
	unsigned char m_flag441; // +0x441
};

struct DrawableInfo
{
	void *m_pad00;
	Drawable *m_drawable; // +0x04
};

// Identity 3x4 at VA 0x00DDD9D0 (value-verified 1,0,0,0,...); role and value
// match Matrix3D::Identity, pinned here under an address-derived name.
extern const Matrix3D Rva00DDD9D0Identity;

struct W3DShadowGeometryMesh
{
	char m_unmodelled00[0xc];
	int m_meshRobjIndex;
	char m_unmodelled10[0x20];
	unsigned char m_unmodelled30;
	char m_unmodelled31[3];
};

class W3DShadowGeometry
{
public:
	W3DShadowGeometryMesh *getMesh(int index) { return &m_meshList[index]; }

private:
	char m_unmodelled00[0x14];
	W3DShadowGeometryMesh m_meshList[160];
};

class W3DVolumetricShadow
{
protected:
	enum { SHADOW_DYNAMIC = 0x1 };

	void RenderVolume(int meshIndex, int lightIndex);
	void RenderMeshVolume(int meshIndex, int lightIndex, const Matrix3D *meshXform);
	void RenderDynamicMeshVolume(int meshIndex, int lightIndex, const Matrix3D *meshXform);

	static inline unsigned char shadowVolumeFlags(const void *geometry)
	{
		return *((const unsigned char *)geometry + 0x18);
	}

	char m_unmodelled00[0x6c];
	W3DShadowGeometry *m_geometry;
	RenderObjClass *m_robj;
	char m_unmodelled74[0xc];
	void *m_shadowVolume[160];
};

#ifndef NULL
#define NULL 0
#endif

void W3DVolumetricShadow::RenderVolume(int meshIndex, int lightIndex)
{
	RenderObjClass *robj = m_robj;
	if (robj && m_robj->Get_User_Data()) {
		Drawable *draw = ((DrawableInfo *)m_robj->Get_User_Data())->m_drawable;
		if (draw && !draw->m_flag441)
			m_robj->Set_Transform(*draw->getTransformMatrix());
	} else if (m_robj && m_robj->roSlot47()) {
		m_robj->roSlot42();
	}

	W3DShadowGeometryMesh *meshInfo = m_geometry->getMesh(meshIndex);
	int meshRobjIndex = meshInfo->m_meshRobjIndex;
	RenderObjClass *mesh;
	if (meshRobjIndex >= 0)
		mesh = robj->Peek_Lod_Model(0, meshRobjIndex);
	else
		mesh = m_robj;

	mesh->Validate_Transform();
	const Matrix3D *meshXform = mesh->Get_Transform();
	if (meshInfo->m_unmodelled30 && mesh->Class_ID() == RenderObjClass::CLASSID_MESH)
		meshXform = &Rva00DDD9D0Identity;

	void *shadowVolume = m_shadowVolume[meshIndex];
	if (shadowVolumeFlags(shadowVolume) & SHADOW_DYNAMIC)
		RenderDynamicMeshVolume(meshIndex, lightIndex, meshXform);
	else
		RenderMeshVolume(meshIndex, lightIndex, meshXform);
}
