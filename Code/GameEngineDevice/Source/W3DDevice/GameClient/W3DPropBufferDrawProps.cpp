// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
// ?drawProps@W3DPropBuffer@@QAEXAAVRenderInfoClass@@@Z
// retail 0x000EE452 (976B)
//
// BFME 2's W3DPropBuffer::drawProps. Against Zero Hour: no camera cull here;
// each frame it invalidates the shroud status of the next 30 props (cursor
// +0x2F720), rebuilds the prop draw state when the +0x2EE0A flag is set
// (0x000EE15B), dims the object lighting by the g_00DFE1E4 slot-18 level when
// slot 15 says it applies, sets each prop's 0x0013BEB0 slot to 2 or 0 from
// GlobalData +0xC60, copies the DX8 fog colour into the RenderInfoClass, and
// renders shrouded props under the shroud's material pass and rendering
// method. Lighting is Zero Hour's (time-of-day object lighting, three
// lights through m_light). The Zero Hour-header W3DPropBuffer.cpp cannot see
// these BFME 2 types, so the body is compiled here against views of the
// layouts its matched rows use: props of 0x30 bytes at +0x04 (robj +0x00,
// location +0x08, shroud status +0x18, visible +0x1C), count +0x2EE04, the
// shroud material pass +0x2F71C and m_light +0x2F724.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Vector3 &operator*=(Real k) { X *= k; Y *= k; Z *= k; return *this; }
	Real X, Y, Z;
};

class Matrix3D
{
public:
	Matrix3D(void) {}
	__forceinline void Set(const Vector3 &x, const Vector3 &y, const Vector3 &z, const Vector3 &pos)
	{
		Row[0][0] = x.X; Row[0][1] = y.X; Row[0][2] = z.X; Row[0][3] = pos.X;
		Row[1][0] = x.Y; Row[1][1] = y.Y; Row[1][2] = z.Y; Row[1][3] = pos.Y;
		Row[2][0] = x.Z; Row[2][1] = y.Z; Row[2][2] = z.Z; Row[2][3] = pos.Z;
	}
	Real Row[3][4];
};

class LightClass
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20();
	virtual void Set_Transform(const Matrix3D &m);	// slot 21
	void Set_Ambient(const Vector3 &color) { Ambient = color; }
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
	void Set_Specular(const Vector3 &color) { Specular = color; }
private:
	char m_pad04[0xD4 - 0x04];
	Vector3 Ambient;	// +0xD4
	Vector3 Diffuse;	// +0xE0
	Vector3 Specular;	// +0xEC
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
private:
	char m_storage[0x228];
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

class MaterialPassClass;

class RenderInfoClass
{
public:
	void Push_Material_Pass(MaterialPassClass *matpass);
	void Pop_Material_Pass(void);
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);

	void *Camera;	// +0x00
	char m_pad04[0x08 - 0x04];
	Vector3 FogColor;	// +0x08
	char m_pad14[0x28 - 0x14];
	class LightEnvironmentClass *light_environment;	// +0x28
};

class RenderObjClass
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
	virtual void s10(); virtual void s11();
	virtual void Render(RenderInfoClass &rinfo);	// slot 12
};

// Rowed setter at 0x0013BEB0 on the render object.
class Rva0013BEB0DwordSlot { public: void set(Int value); };

class DX8Wrapper
{
public:
	static bool FogEnable;
	static unsigned long FogColor;
	static __forceinline Vector3 Convert_Color(unsigned color)
	{
		Vector3 col;
		col.X = ((color & 0xff0000) >> 16) / 255.0f;
		col.Y = ((color & 0xff00) >> 8) / 255.0f;
		col.Z = ((color & 0xff) >> 0) / 255.0f;
		return col;
	}
};

// Time-of-day object lighting: three 0x24-byte lights (ambient, diffuse,
// position) per time of day, 0x6C apart from GlobalData +0x3C8.
struct BfmeTerrainLighting { Vector3 ambient; Vector3 diffuse; Vector3 lightPos; };
class GlobalData
{
public:
	char m_pad000[0x1C];
	Bool m_drawProps;	// +0x1C
	char m_pad01D[0x134 - 0x1D];
	Int m_timeOfDay;	// +0x134
	char m_pad138[0x3C8 - 0x138];
	BfmeTerrainLighting m_terrainObjectsLighting[1][3];	// +0x3C8 (indexed by time of day)
	char m_pad434[0xC60 - 0x434];
	Int m_atC60;	// +0xC60, -1 when unset
};
extern GlobalData *TheWritableGlobalData;

struct Rva000E2D26Vector3 { float x, y, z; };
class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual bool slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(Rva000E2D26Vector3 *out);
};
extern Rva0027070CGlobal *g_00DFE1E4;

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

class Player { public: Int getPlayerIndex(void) const { return m_playerIndex; } private: char m_pad[0x54]; Int m_playerIndex; };
class PlayerList { public: Player *getLocalPlayer(void) { return m_local; } private: char m_pad[0x10]; Player *m_local; };
extern PlayerList *ThePlayerList;

class PartitionManager;
extern PartitionManager *TheShroudManager;
class Rva00739800 { public: ObjectShroudStatus rva00739800(Int playerIndex, const Coord3D *loc) const; };

// BFME 2's shroud hands out the rendering method props draw with when
// shrouded (0x0006F1FE).
class W3DShroud { public: RefCountPtr<FXShader::RenderingMethod> rva0006F1FE(void); };
class BaseHeightMapRenderObjClass
{
public:
	W3DShroud *getShroud(void) { return m_shroud; }
private:
	char m_pad[0x3878];
	W3DShroud *m_shroud;	// +0x3878
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

struct TProp
{
	RenderObjClass *m_robj;	// +0x00
	Int id;
	Coord3D location;	// +0x08
	Int propType;
	ObjectShroudStatus ss;	// +0x18
	Bool visible;	// +0x1C
	char m_pad1D[0x30 - 0x1D];
};

#define MAX_PROPS 4000
#define MAX_GLOBAL_LIGHTS 3

class W3DPropBuffer
{
public:
	void drawProps(RenderInfoClass &rinfo);
	void rva000EE15B(void);
protected:

	char m_pad00[0x04];
	TProp m_props[MAX_PROPS];	// +0x04
	Int m_numProps;	// +0x2EE04
	char m_pad2EE08[0x2EE0A - 0x2EE08];
	Bool m_rebuild;	// +0x2EE0A
	char m_pad2EE0B[0x2F71C - 0x2EE0B];
	MaterialPassClass *m_propShroudMaterialPass;	// +0x2F71C
	Int m_shroudResetIndex;	// +0x2F720
	LightClass *m_light;	// +0x2F724
};

void W3DPropBuffer::drawProps(RenderInfoClass &rinfo)
{
	if (!TheWritableGlobalData->m_drawProps)
		return;

	Int i;
	for (i = 0; i < 30; i++) {
		if (m_shroudResetIndex >= m_numProps)
			m_shroudResetIndex = 0;
		m_props[m_shroudResetIndex].ss = OBJECTSHROUD_INVALID;
		m_shroudResetIndex++;
	}

	if (m_rebuild) {
		rva000EE15B();
		m_rebuild = false;
	}

	const BfmeTerrainLighting *objectLighting =
		TheWritableGlobalData->m_terrainObjectsLighting[TheWritableGlobalData->m_timeOfDay];
	Real scale = 1.0f;
	if (g_00DFE1E4 && g_00DFE1E4->slot3C()) {
		Rva000E2D26Vector3 level;
		g_00DFE1E4->slot48(&level);
		scale = 1.0f - level.x;
	}

	LightEnvironmentClass lightEnv;
	Vector3 center(0, 0, 0);
	Vector3 ambient(objectLighting[0].ambient.X, objectLighting[0].ambient.Y, objectLighting[0].ambient.Z);
	ambient *= scale;
	lightEnv.Reset(center, ambient);
	Matrix3D mtx;
	for (i = 0; i < MAX_GLOBAL_LIGHTS; ++i)
	{
		m_light->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
		Vector3 diffuse(objectLighting[i].diffuse.X, objectLighting[i].diffuse.Y, objectLighting[i].diffuse.Z);
		diffuse *= scale;
		m_light->Set_Diffuse(diffuse);
		m_light->Set_Specular(Vector3(0.0f, 0.0f, 0.0f));
		mtx.Set(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(objectLighting[i].lightPos.X, objectLighting[i].lightPos.Y, objectLighting[i].lightPos.Z), Vector3(0.0f, 0.0f, 0.0f));
		m_light->Set_Transform(mtx);
		lightEnv.Add_Light(*m_light);
	}

	rinfo.light_environment = &lightEnv;

	for (i = 0; i < m_numProps; i++) {
		if (!m_props[i].visible) {
			continue;
		}
		if (m_props[i].m_robj == 0) {
			continue;
		}
		if (TheWritableGlobalData->m_atC60 != -1)
			reinterpret_cast<Rva0013BEB0DwordSlot *>(m_props[i].m_robj)->set(2);
		else
			reinterpret_cast<Rva0013BEB0DwordSlot *>(m_props[i].m_robj)->set(0);
		if (!ThePlayerList || !TheShroudManager) {
			m_props[i].ss = OBJECTSHROUD_CLEAR;
		}
		if (m_props[i].ss == OBJECTSHROUD_INVALID) {
			Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
			m_props[i].ss = reinterpret_cast<Rva00739800 *>(TheShroudManager)->rva00739800(localPlayerIndex, &m_props[i].location);
		}
		if (m_props[i].ss >= OBJECTSHROUD_SHROUDED) {
			continue;
		}
		if (m_props[i].ss <= OBJECTSHROUD_INVALID) {
			continue;
		}
		if (DX8Wrapper::FogEnable) {
			rinfo.FogColor = DX8Wrapper::Convert_Color(DX8Wrapper::FogColor);
		}
		if (TheTerrainRenderObject->getShroud() && m_props[i].ss != OBJECTSHROUD_CLEAR) {
			rinfo.Push_Material_Pass(m_propShroudMaterialPass);
			if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud())
				rinfo.Push_Rendering_Method(TheTerrainRenderObject->getShroud()->rva0006F1FE());
			m_props[i].m_robj->Render(rinfo);
			if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud())
				rinfo.Pop_Rendering_Method();
			rinfo.Pop_Material_Pass();
		} else {
			m_props[i].m_robj->Render(rinfo);
		}
	}
	rinfo.light_environment = 0;
}
