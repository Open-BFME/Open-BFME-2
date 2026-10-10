// ?renderOneObject@RTS3DScene@@IAEXAAVRenderInfoClass@@PAVRenderObjClass@@HH@Z
// partial score=0.85864696 date=2026-10-10
// ?renderOneObject@RTS3DScene@@IAEXAAVRenderInfoClass@@PAVRenderObjClass@@HH@Z
// partial score=0.91 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
//
// ?renderOneObject@RTS3DScene@@IAEXAAVRenderInfoClass@@PAVRenderObjClass@@HH@Z
// retail 0x0006FB59..0x0007054F (2550 bytes) thiscall RET 0x10 with EH.
//
// BFME 2's RTS3DScene::renderOneObject. The donor is Zero Hour's
// RTS3DScene::renderOneObject (GeneralsMD W3DScene.cpp; the BFME 1 copy is
// unmatched there); the WorldBuilder twin 0x0072F1E0 shows the same flow.
// BFME 2 differences from Zero Hour, all read from retail:
// - a fourth stack argument that every caller passes as 0 and the body never
//   reads;
// - the scene fog colour (+0x20) is copied into the RenderInfoClass when
//   DX8Wrapper::FogEnable is set (scaled by GlobalData +0xBE9 / +0xBE8 for
//   fogged ghost objects);
// - the TerrainLogic ambient lightmap sample (rowed 0x0027DA6A) at the render
//   object position adds to the ambient;
// - the infantry lighting choice is a RenderObjClass virtual (+0x1C0), not
//   Drawable::isKindOf, and picks the infantry ambient (+0x144);
// - drawable tinting sums three colours (rowed 0x00272C74 / 0x00272C89 and
//   the +0x9C colour) and scales by one minus a fourth (rowed 0x0027070C)
//   and by the GlobalData +0x944 colour when g_Va00DB5FA0 is below 2;
// - lights are added to a private environment only when needed: otherwise
//   one of the scene's precomputed environments (+0x164 / +0x5B4) is used;
// - dynamic lights are always considered; the alpha reference override is
//   taken from the drawable (+0xE4 / +0xF0); partially-cleared objects render
//   under the shroud rendering method (pinned W3DShroud 0x0006F1FE).
// Callers: 0x0007076A 0x000707D7 0x00070B96 0x00070BBE 0x00070C8F and others.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
#define TRUE true
#define FALSE false
#define NULL 0

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	void Scale(const Vector3 &s) { X *= s.X; Y *= s.Y; Z *= s.Z; }
	static void Add(const Vector3 &a, const Vector3 &b, Vector3 *c) { c->X = a.X + b.X; c->Y = a.Y + b.Y; c->Z = a.Z + b.Z; }
	Real X, Y, Z;
};

struct FogColorVector
{
	Real X, Y, Z;
};

class SphereClass
{
public:
	Vector3 Center;
	Real Radius;
};

bool Spheres_Intersect(const SphereClass &s0, const SphereClass &s1);

class Matrix3D
{
public:
	Real Row[3][4];
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }
protected:
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void) { if (Referent) Referent->Release_Ref(); }
private:
	T *Referent;
};

namespace FXShader { class RenderingMethod : public RefCountClass {}; }

struct MultiListNodeClass;

class MultiListObjectClass
{
public:
	MultiListNodeClass *ListNode;
};

struct MultiListNodeClass
{
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
};

class RenderInfoClass;
class SceneClass;

#define RENDEROBJ_SLOT(n) virtual void slot##n();

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RENDEROBJ_SLOT(01) RENDEROBJ_SLOT(02) RENDEROBJ_SLOT(03) RENDEROBJ_SLOT(04)
	RENDEROBJ_SLOT(05) RENDEROBJ_SLOT(06) RENDEROBJ_SLOT(07) RENDEROBJ_SLOT(08)
	RENDEROBJ_SLOT(09) RENDEROBJ_SLOT(10) RENDEROBJ_SLOT(11)
	virtual void Render(RenderInfoClass &rinfo);						// +0x30
	RENDEROBJ_SLOT(13) RENDEROBJ_SLOT(14) RENDEROBJ_SLOT(15) RENDEROBJ_SLOT(16)
	RENDEROBJ_SLOT(17)
	virtual SceneClass *Peek_Scene(void);								// +0x48
	RENDEROBJ_SLOT(19)
	virtual void Validate_Transform(void) const;						// +0x50
	RENDEROBJ_SLOT(21) RENDEROBJ_SLOT(22) RENDEROBJ_SLOT(23) RENDEROBJ_SLOT(24)
	RENDEROBJ_SLOT(25) RENDEROBJ_SLOT(26) RENDEROBJ_SLOT(27) RENDEROBJ_SLOT(28)
	RENDEROBJ_SLOT(29) RENDEROBJ_SLOT(30) RENDEROBJ_SLOT(31) RENDEROBJ_SLOT(32)
	RENDEROBJ_SLOT(33) RENDEROBJ_SLOT(34) RENDEROBJ_SLOT(35) RENDEROBJ_SLOT(36)
	RENDEROBJ_SLOT(37) RENDEROBJ_SLOT(38) RENDEROBJ_SLOT(39) RENDEROBJ_SLOT(40)
	RENDEROBJ_SLOT(41) RENDEROBJ_SLOT(42) RENDEROBJ_SLOT(43) RENDEROBJ_SLOT(44)
	RENDEROBJ_SLOT(45) RENDEROBJ_SLOT(46) RENDEROBJ_SLOT(47) RENDEROBJ_SLOT(48)
	RENDEROBJ_SLOT(49) RENDEROBJ_SLOT(50) RENDEROBJ_SLOT(51) RENDEROBJ_SLOT(52)
	RENDEROBJ_SLOT(53) RENDEROBJ_SLOT(54) RENDEROBJ_SLOT(55) RENDEROBJ_SLOT(56)
	RENDEROBJ_SLOT(57) RENDEROBJ_SLOT(58) RENDEROBJ_SLOT(59) RENDEROBJ_SLOT(60)
	RENDEROBJ_SLOT(61) RENDEROBJ_SLOT(62) RENDEROBJ_SLOT(63) RENDEROBJ_SLOT(64)
	virtual const SphereClass &Get_Bounding_Sphere(void) const;			// +0x104
	RENDEROBJ_SLOT(66) RENDEROBJ_SLOT(67) RENDEROBJ_SLOT(68)
	RENDEROBJ_SLOT(69) RENDEROBJ_SLOT(70) RENDEROBJ_SLOT(71) RENDEROBJ_SLOT(72)
	RENDEROBJ_SLOT(73) RENDEROBJ_SLOT(74) RENDEROBJ_SLOT(75) RENDEROBJ_SLOT(76)
	RENDEROBJ_SLOT(77) RENDEROBJ_SLOT(78) RENDEROBJ_SLOT(79) RENDEROBJ_SLOT(80)
	RENDEROBJ_SLOT(81) RENDEROBJ_SLOT(82) RENDEROBJ_SLOT(83) RENDEROBJ_SLOT(84)
	RENDEROBJ_SLOT(85) RENDEROBJ_SLOT(86)
	virtual void *Get_User_Data(void);									// +0x15C
	RENDEROBJ_SLOT(88)
	RENDEROBJ_SLOT(89) RENDEROBJ_SLOT(90) RENDEROBJ_SLOT(91) RENDEROBJ_SLOT(92)
	RENDEROBJ_SLOT(93) RENDEROBJ_SLOT(94) RENDEROBJ_SLOT(95) RENDEROBJ_SLOT(96)
	RENDEROBJ_SLOT(97) RENDEROBJ_SLOT(98) RENDEROBJ_SLOT(99) RENDEROBJ_SLOT(100)
	RENDEROBJ_SLOT(101) RENDEROBJ_SLOT(102) RENDEROBJ_SLOT(103) RENDEROBJ_SLOT(104)
	RENDEROBJ_SLOT(105) RENDEROBJ_SLOT(106) RENDEROBJ_SLOT(107) RENDEROBJ_SLOT(108)
	RENDEROBJ_SLOT(109) RENDEROBJ_SLOT(110) RENDEROBJ_SLOT(111)
	virtual Int Uses_Infantry_Lighting(void);							// +0x1C0

	Vector3 Get_Position(void) const;
	const Matrix3D &Get_Transform(void) const { Validate_Transform(); return Transform; }

	char m_pad0C[0x18 - 0x0C];
	Matrix3D Transform;													// +0x18
};

class CameraClass : public RenderObjClass
{
};

class LightClass : public RenderObjClass
{
public:
	enum LightType { POINT = 0, DIRECTIONAL, SPOT };
	LightType Get_Type(void) { return Type; }
	void Get_Diffuse(Vector3 *set_c) const;
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
private:
	char m_pad48[0xC4 - 0x48];
	LightType Type;														// +0xC4
	char m_padC8[0xE0 - 0xC8];
	Vector3 Diffuse;													// +0xE0
};

class W3DDynamicLight : public LightClass
{
public:
	Bool isEnabled(void) { return m_enabled; }
private:
	char m_padEC[0x144 - 0xEC];
	Bool m_enabled;														// +0x144
};

class RefRenderObjListIterator
{
public:
	RefRenderObjListIterator(GenericMultiListClass *list) : List(list), CurNode(0) {}
	void First(void) { CurNode = List->Head.Next; }
	bool Is_Done(void) const { return CurNode == &List->Head; }
	void Next(void) { CurNode = CurNode->Next; }
	RenderObjClass *Peek_Obj(void) const { return (RenderObjClass *)Current_Object(); }
	MultiListObjectClass *Current_Object(void) const { return CurNode->Object; }
private:
	GenericMultiListClass *List;
	MultiListNodeClass *CurNode;
};

// LightEnvironmentClass::Reset is rowed as Gen_0094AC70::bfmeSetPair.
class BfmeVecHF;
class Gen_0094AC70 { public: void bfmeSetPair(const BfmeVecHF *center, const BfmeVecHF *ambient); };

class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);
	void Reset(const Vector3 &center, const Vector3 &ambient)
	{
		reinterpret_cast<Gen_0094AC70 *>(this)->bfmeSetPair(
			reinterpret_cast<const BfmeVecHF *>(&center), reinterpret_cast<const BfmeVecHF *>(&ambient));
	}
	void Add_Light(const LightClass &light);
	void Pre_Render_Update(const Matrix3D &camera_tm);
	const Vector3 &Get_Equivalent_Ambient(void) const { return OutputAmbient; }
	void Set_Output_Ambient(Vector3 &oa) { OutputAmbient = oa; }
private:
	char m_pad000[0x164];
	Vector3 OutputAmbient;												// +0x164
	char m_pad170[0x228 - 0x170];
};

class MaterialPassClass;
class W3DShroudMaterialPassClass;

class RenderInfoClass
{
public:
	enum RINFO_OVERRIDE_FLAGS
	{
		RINFO_OVERRIDE_DEFAULT = 0x0000,
		RINFO_OVERRIDE_FORCE_TWO_SIDED = 0x0001,
		RINFO_OVERRIDE_FORCE_SORTING = 0x0002,
		RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY = 0x0004
	};
	void Push_Material_Pass(MaterialPassClass *matpass);
	void Pop_Material_Pass(void);
	void Push_Override_Flags(RINFO_OVERRIDE_FLAGS flg);
	void Pop_Override_Flags(void);
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);

	CameraClass &Camera;												// +0x00
	char m_pad04[0x08 - 0x04];
	Vector3 fogColor;											// +0x08
	char m_pad14[0x24 - 0x14];
	Real materialPassEmissiveOverride;									// +0x24
	LightEnvironmentClass *light_environment;							// +0x28
};

class DX8Wrapper
{
public:
	static bool FogEnable;
};

class GlobalData
{
public:
	char m_pad000[0x944];
	Real m_lightScale[3];												// +0x944
	char m_pad950[0xBE8 - 0x950];
	unsigned char m_fogAlpha;											// +0xBE8
	unsigned char m_clearAlpha;											// +0xBE9
};
extern GlobalData *TheWritableGlobalData;

enum CellShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

enum ObjectID { INVALID_ID = 0 };

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	Bool isEffectivelyDead(void) const { return (m_privateStatus & 1) != 0; }
private:
	char m_pad000[0x438];
	unsigned char m_privateStatus;										// +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame(void) { return m_frame; }
private:
	char m_pad000[0x40];
	UnsignedInt m_frame;												// +0x40
};
extern GameLogic *TheGameLogic;

extern Int g_Va00DBA4E4;	// logic frames per second
extern Int g_Va00DB5FA0;

// Rowed Drawable helpers under placeholder names.
class Rva00270260 { public: bool rva00270260(void); };
struct Rva0027070CData;
class Rva0027070C { public: Rva0027070CData *rva0027070C(void); };
class BfmeThingDDA { public: Int bfmeGoDDA(void); };
class BfmeThingDDB { public: Int bfmeGoDDB(void); };

class Drawable
{
public:
	Bool isDrawableEffectivelyHidden(void) { return reinterpret_cast<Rva00270260 *>(this)->rva00270260(); }
	const Vector3 *getTintColor(void) { return (const Vector3 *)reinterpret_cast<BfmeThingDDA *>(this)->bfmeGoDDA(); }
	const Vector3 *getSelectionColor(void) { return (const Vector3 *)reinterpret_cast<BfmeThingDDB *>(this)->bfmeGoDDB(); }
	const Vector3 *getLightColor(void) { return (const Vector3 *)reinterpret_cast<Rva0027070C *>(this)->rva0027070C(); }
	const Vector3 *getBaseColor(void) { return &m_baseColor; }
	Object *getObject(void) { return m_object; }
	UnsignedInt getShroudClearFrame(void) { return m_shroudClearFrame; }
	void setShroudClearFrame(UnsignedInt frame) { m_shroudClearFrame = frame; }
	Int getStealthLook(void) { return m_stealthLook; }
	Real getSecondMaterialPassOpacity(void) { return m_secondMaterialPassOpacity; }
	Bool hasAlphaReferenceOverride(void) { return m_alphaOverride; }
	Int getAlphaReference(void) { return m_alphaReference; }
private:
	char m_pad000[0x9C];
	Vector3 m_baseColor;												// +0x9C
	char m_padA8[0xE4 - 0xA8];
	Bool m_alphaOverride;												// +0xE4
	char m_padE5[0xF0 - 0xE5];
	Int m_alphaReference;												// +0xF0
	char m_padF4[0xFC - 0xF4];
	Object *m_object;													// +0xFC
	char m_pad100[0x138 - 0x100];
	UnsignedInt m_shroudClearFrame;										// +0x138
	char m_pad13C[0x164 - 0x13C];
	Int m_stealthLook;													// +0x164
	char m_pad168[0x358 - 0x168];
	Real m_secondMaterialPassOpacity;									// +0x358
};

struct DrawableInfo
{
	ObjectID m_shroudStatusObjectID;									// +0x00
	Drawable *m_drawable;												// +0x04
};

class Rva0062AF7 { public: bool rva0027DA6A(const float *pos, float *color); };
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class W3DShroud { public: RefCountPtr<FXShader::RenderingMethod> rva0006F1FE(void); };
class BaseHeightMapRenderObjClass
{
public:
	W3DShroud *getShroud(void) { return m_shroud; }
private:
	char m_pad[0x3878];
	W3DShroud *m_shroud;												// +0x3878
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

extern bool ShaderAlphaReferenceOverride;
extern unsigned char ShaderAlphaReference;

enum CustomScenePassModes { SCENE_PASS_DEFAULT = 0 };

class RTS3DScene
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual const Vector3 &Get_Ambient_Light(void);					// +0x1C
protected:
	void renderOneObject(RenderInfoClass &rinfo, RenderObjClass *robj, Int localPlayerIndex, Int unused);

	char m_pad004[0x20 - 0x04];
	Vector3 m_fogColor;											// +0x20
	char m_pad02C[0x8C - 0x2C];
	GenericMultiListClass LightList;									// +0x8C
	char m_pad0A4[0x114 - 0xA4];
	GenericMultiListClass m_dynamicLightList;							// +0x114
	char m_pad12C[0x130 - 0x12C];
	LightClass *m_globalLight[4];										// +0x130
	LightClass *m_scratchLight;											// +0x140
	Vector3 m_infantryAmbient;											// +0x144
	LightClass *m_infantryLight[4];										// +0x150
	Int m_numGlobalLights;												// +0x160
	LightEnvironmentClass m_defaultLightEnv;							// +0x164
	LightEnvironmentClass m_foggedLightEnv;								// +0x38C
	LightEnvironmentClass m_infantryLightEnv;							// +0x5B4
	Bool m_7DC;															// +0x7DC
	W3DShroudMaterialPassClass *m_shroudMaterialPass;					// +0x7E0
	MaterialPassClass *m_heatVisionMaterialPass;						// +0x7E4
	MaterialPassClass *m_heatVisionOnlyPass;							// +0x7E8
	CustomScenePassModes m_customPassMode;								// +0x7EC
};

void RTS3DScene::renderOneObject(RenderInfoClass &rinfo, RenderObjClass *robj, Int localPlayerIndex, Int unused)
{
	Drawable *draw = NULL;
	DrawableInfo *drawInfo = NULL;
	Bool drawableHidden = FALSE;
	Object *obj = NULL;
	CellShroudStatus ss = OBJECTSHROUD_INVALID;
	Bool doExtraMaterialPop = FALSE;
	Bool doExtraFlagsPop = FALSE;
	LightClass **sceneLights = m_globalLight;

	LightEnvironmentClass lightEnv;
	Int lightsAdded = FALSE;
	SphereClass sph = robj->Get_Bounding_Sphere();
	drawInfo = (DrawableInfo *)robj->Get_User_Data();
	if (drawInfo)
	{
		draw = drawInfo->m_drawable;
		if (!draw)
			ss = OBJECTSHROUD_FOGGED;
	}

	Real foggedLightFrac = (Real)TheWritableGlobalData->m_clearAlpha / (Real)TheWritableGlobalData->m_fogAlpha;
	if (DX8Wrapper::FogEnable)
		rinfo.fogColor = m_fogColor;

	Vector3 ambient = Get_Ambient_Light();
	Vector3 lightmapColor;
	Bool hasLightmap = FALSE;
	if (TheTerrainLogic)
	{
		Vector3 sample;
		if (reinterpret_cast<Rva0062AF7 *>(TheTerrainLogic)->rva0027DA6A((const float*)&robj->Get_Position(), (float*)&sample))
		{
			hasLightmap = TRUE;
			lightmapColor = sample;
			ambient += lightmapColor;
		}
	}

	if (draw && (drawableHidden = draw->isDrawableEffectivelyHidden()) != TRUE)
	{
		obj = draw->getObject();
		if (obj)
		{
			ss = obj->getShroudStatusForPlayer(localPlayerIndex);
			if (ss == OBJECTSHROUD_CLEAR)
			{
				draw->setShroudClearFrame(TheGameLogic->getFrame());
			}
			else if (ss >= OBJECTSHROUD_FOGGED && draw->getShroudClearFrame() != 0)
			{
				UnsignedInt limit = 2 * g_Va00DBA4E4;
				if (obj->isEffectivelyDead())
					limit += 3 * g_Va00DBA4E4;
				if (TheGameLogic->getFrame() < limit + draw->getShroudClearFrame())
					ss = OBJECTSHROUD_PARTIAL_CLEAR;
			}
			if (!robj->Peek_Scene())
				return;
		}
		else
		{
			ss = OBJECTSHROUD_CLEAR;
			if (drawInfo->m_shroudStatusObjectID != INVALID_ID)
			{
				Object *shroudObject = TheGameLogic->findObjectByID(drawInfo->m_shroudStatusObjectID);
				if (shroudObject && shroudObject->getShroudStatusForPlayer(localPlayerIndex) >= OBJECTSHROUD_FOGGED)
					ss = OBJECTSHROUD_SHROUDED;
			}
		}

		if (robj->Uses_Infantry_Lighting())
		{
			ambient = m_infantryAmbient;
			if (hasLightmap)
				ambient += lightmapColor;
			sceneLights = m_infantryLight;
		}

		lightEnv.Reset(sph.Center, ambient);

		const Vector3 *tintColor = NULL;
		const Vector3 *selectionColor = NULL;
		const Vector3 *baseColor = draw->getBaseColor();
		const Vector3 *lightColor = draw->getLightColor();

		tintColor = draw->getTintColor();
		selectionColor = draw->getSelectionColor();

		if (tintColor || selectionColor || baseColor || lightColor || g_Va00DB5FA0 < 2)
		{
			Vector3 sumTint, temp, restore;

			sumTint.Set(0, 0, 0);

			if (tintColor)
				Vector3::Add(sumTint, *tintColor, &sumTint);
			if (selectionColor)
				Vector3::Add(sumTint, *selectionColor, &sumTint);
			if (baseColor)
				Vector3::Add(sumTint, *baseColor, &sumTint);

			Vector3 scale(1.0f, 1.0f, 1.0f);
			if (lightColor)
			{
				scale.X = 1.0f - lightColor->X;
				scale.Y = 1.0f - lightColor->Y;
				scale.Z = 1.0f - lightColor->Z;
			}
			if (g_Va00DB5FA0 < 2)
			{
				scale.X *= TheWritableGlobalData->m_lightScale[0];
				scale.Y *= TheWritableGlobalData->m_lightScale[1];
				scale.Z *= TheWritableGlobalData->m_lightScale[2];
			}

			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
			{
				sceneLights[globalLightIndex]->Get_Diffuse(&temp);
				restore = temp;

				Vector3::Add(temp, sumTint, &temp);
				temp.X *= scale.X;
				temp.Y *= scale.Y;
				temp.Z *= scale.Z;

				sceneLights[globalLightIndex]->Set_Diffuse(temp);
				lightEnv.Add_Light(*sceneLights[globalLightIndex]);
				sceneLights[globalLightIndex]->Set_Diffuse(restore);
			}

			temp = lightEnv.Get_Equivalent_Ambient();
			Vector3::Add(sumTint, temp, &temp);
			temp.X *= scale.X;
			temp.Y *= scale.Y;
			temp.Z *= scale.Z;
			lightEnv.Set_Output_Ambient(temp);
			lightsAdded = TRUE;
		}
		else
		{
			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
				lightEnv.Add_Light(*sceneLights[globalLightIndex]);
		}

		if (draw->getSecondMaterialPassOpacity() != 0.0f)
		{
			rinfo.materialPassEmissiveOverride = draw->getSecondMaterialPassOpacity();
			if (draw->getStealthLook() == 3)
			{
				rinfo.Push_Override_Flags(RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY);
				rinfo.Push_Material_Pass(m_heatVisionOnlyPass);
				doExtraFlagsPop = TRUE;
			}
			else
			{
				rinfo.Push_Material_Pass(m_heatVisionMaterialPass);
			}
			doExtraMaterialPop = TRUE;
		}
	}
	else
	{
		if (drawableHidden)
			return;

		if (ss == OBJECTSHROUD_FOGGED)
		{
			rinfo.light_environment = &m_foggedLightEnv;
			if (DX8Wrapper::FogEnable)
			{
				Vector3 fogged(m_fogColor.X * foggedLightFrac, m_fogColor.Y * foggedLightFrac, m_fogColor.Z * foggedLightFrac);
				rinfo.fogColor.X = fogged.X;
				rinfo.fogColor.Y = fogged.Y;
				rinfo.fogColor.Z = fogged.Z;
			}
			robj->Render(rinfo);
			rinfo.light_environment = NULL;
			return;
		}
		else
		{
			if (robj->Uses_Infantry_Lighting())
			{
				ambient = m_infantryAmbient;
				if (hasLightmap)
					ambient += lightmapColor;
				sceneLights = m_infantryLight;
			}

			lightEnv.Reset(sph.Center, ambient);
			if (g_Va00DB5FA0 < 2)
			{
				Vector3 lightScale(TheWritableGlobalData->m_lightScale[0], TheWritableGlobalData->m_lightScale[1], TheWritableGlobalData->m_lightScale[2]);
				for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
				{
					Vector3 temp;
					sceneLights[globalLightIndex]->Get_Diffuse(&temp);
					Vector3 scaled = temp;
					scaled.Scale(lightScale);
					sceneLights[globalLightIndex]->Set_Diffuse(scaled);
					lightEnv.Add_Light(*sceneLights[globalLightIndex]);
					sceneLights[globalLightIndex]->Set_Diffuse(temp);
				}
			}
			else
			{
				for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
					lightEnv.Add_Light(*sceneLights[globalLightIndex]);
			}
		}
	}

	if (!drawableHidden)
	{
		RefRenderObjListIterator it2(&LightList);
		for (it2.First(); !it2.Is_Done(); it2.Next())
		{
			LightClass *pLight = (LightClass *)it2.Peek_Obj();
			SphereClass lSph = pLight->Get_Bounding_Sphere();
			Bool cull = (pLight->Get_Type() == LightClass::POINT && !Spheres_Intersect(sph, lSph));
			if (!cull)
			{
				lightEnv.Add_Light(*pLight);
				lightsAdded = TRUE;
			}
		}

		RefRenderObjListIterator dynaLightIt(&m_dynamicLightList);
		for (dynaLightIt.First(); !dynaLightIt.Is_Done(); dynaLightIt.Next())
		{
			W3DDynamicLight *pDyna = (W3DDynamicLight *)dynaLightIt.Peek_Obj();
			if (!pDyna->isEnabled())
				continue;
			SphereClass lSph = pDyna->Get_Bounding_Sphere();
			if (pDyna->Get_Type() == LightClass::POINT && !Spheres_Intersect(sph, lSph))
				continue;
			lightEnv.Add_Light(*(LightClass *)dynaLightIt.Peek_Obj());
			lightsAdded = TRUE;
		}

		if (!lightsAdded && !hasLightmap)
		{
			if (robj->Uses_Infantry_Lighting())
				rinfo.light_environment = &m_infantryLightEnv;
			else
				rinfo.light_environment = &m_defaultLightEnv;
		}
		else
		{
			lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
			rinfo.light_environment = &lightEnv;
		}

		if (draw && draw->hasAlphaReferenceOverride())
		{
			ShaderAlphaReferenceOverride = true;
			ShaderAlphaReference = (unsigned char)draw->getAlphaReference();
		}
		else
		{
			ShaderAlphaReferenceOverride = false;
			ShaderAlphaReference = 0x60;
		}

		if (drawInfo)
		{
			if (m_customPassMode == SCENE_PASS_DEFAULT)
			{
				if (ss <= OBJECTSHROUD_CLEAR)
					robj->Render(rinfo);
				else if (ss == OBJECTSHROUD_PARTIAL_CLEAR)
				{
					rinfo.Push_Material_Pass((MaterialPassClass *)m_shroudMaterialPass);
					if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud())
						rinfo.Push_Rendering_Method(TheTerrainRenderObject->getShroud()->rva0006F1FE());
					robj->Render(rinfo);
					if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud())
						rinfo.Pop_Rendering_Method();
					rinfo.Pop_Material_Pass();
				}
			}
			else
			{
				robj->Render(rinfo);
			}
		}
		else
		{
			robj->Render(rinfo);
		}
	}

	rinfo.light_environment = NULL;
	if (doExtraMaterialPop)
		rinfo.Pop_Material_Pass();
	if (doExtraFlagsPop)
		rinfo.Pop_Override_Flags();
}
