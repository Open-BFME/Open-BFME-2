// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// dxsdk
// platformsdk
//
// ?Flush@RTS3DScene@@QAEXAAVRenderInfoClass@@@Z, retail 0x00071606..0x00071E40
// (2106 bytes, RET 4, EH). Zero Hour's RTS3DScene::Flush with BFME 2's render
// events, inline stencil states and the trees light environment. Two levers
// from retail's same-TU codegen: the stencil states go through an inline
// Set_DX8_Render_State-shaped function (its early return gives retail's frame
// weights), and the global lights are walked through a local LightClass **
// (as Zero Hour's renderOneObject does with sceneLights), which keeps cl from
// strength-reducing the index.
typedef float Real;
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
class Matrix3D;
class RenderObjClass { public: virtual ~RenderObjClass(); };
class LightClass : public RenderObjClass
{
public:
	__declspec(noinline) void Get_Diffuse(Vector3 *color) const { if (color != 0) color->Set(Diffuse); }
	void Set_Diffuse(const Vector3 &color) { Diffuse.Set(color); }
private:
	char m_pad04[0xE0 - 0x04];
	Vector3 Diffuse; // +0xE0
};
class BfmeVecHF;
#include "../../../Include/W3DDevice/GameClient/Gen_0094AC70.h"
class LightEnvironmentClass : public Gen_0094AC70
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);
	void Add_Light(const LightClass &light);
	const Vector3 &Get_Output_Ambient(void) const { return m_outputAmbient; }
	void Set_Output_Ambient(const Vector3 &ambient) { m_outputAmbient.Set(ambient); }
private:
	char m_pad000[0x164];
	Vector3 m_outputAmbient; // +0x164
	char m_pad170[0x228 - 0x170];
};
#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"
class StringClass
{
	char *m_Buffer; static char *m_EmptyString; static char m_NullChar;
	void Free_String();
public:
	StringClass(int n = 0, bool temporary = false);
	__forceinline ~StringClass() { Free_String(); }
};
class BFME2ScopedRenderEvent
{
	char Label[256];
	char Group[64];
public:
	BFME2ScopedRenderEvent(const char *label, const char *group, unsigned color);
	~BFME2ScopedRenderEvent();
};
#include <d3d9.h>

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (SetRenderState slot 57, SetVertexShader slot 92).
struct IDirect3DDevice8;
extern unsigned number_of_DX8_calls;
#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
class DX8Wrapper
{
	friend class RTS3DScene;
	friend void bfmeSetRS(unsigned long, unsigned);
protected:
	static unsigned render_state_changes, RenderStates[256];
	static IDirect3DDevice8 *D3DDevice;
public:
	static bool Has_Stencil();
	static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned int);
};
#include "../../../../Libraries/Source/WWVegas/WW3D2/SortingRendererClass.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8MeshRendererClass.h"
extern DX8MeshRendererClass *TheDX8MeshRenderer;
__forceinline void bfmeSetRS(unsigned long state, unsigned value)
{
	if (DX8Wrapper::RenderStates[state] == value) return;
	if (WW3D::SnapshotActivated) {
		StringClass valueName(0, true);
		DX8Wrapper::Get_DX8_Render_State_Value_Name(valueName, state, value);
	}
	DX8Wrapper::RenderStates[state] = value;
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state, value);
	++number_of_DX8_calls;
	++DX8Wrapper::render_state_changes;
}
#define BFME_SET_RS(s_, v_) bfmeSetRS((s_), (v_))
void rva001173f0(unsigned renderArgument);
void Rva0004CB1E(int arg);
void bfmeGo991B(int arg);
#include "../../../Include/W3DDevice/GameClient/W3DShadowManager.h"
class Rva0009A361 { public: void rva0009A361(int arg); };
extern W3DShadowManager *TheW3DShadowManager;
class BaseHeightMapRenderObjClass
{
public:
	void rva0006B895(RenderInfoClass &rinfo);
	void rva0006BBD9(int rinfo, int flag);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
struct Rva0027070CData { float a, b, c; };
class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual bool slot3C();
	virtual void slot40(); virtual void slot44();
	virtual Rva0027070CData *slot48(Rva0027070CData *out);
};
extern Rva0027070CGlobal *TheCloudEffectManager;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct SceneLightGlobalView
{
	char m_pad000[0x944];
	Real m_lowLODLightScaleRed, m_lowLODLightScaleGreen, m_lowLODLightScaleBlue; // +0x944
};
extern int LODTextureReduction;
extern void *W3DGCData00DE2000;
extern class GameClient *TheGameClient;
struct WaterView { char pad[0x25c]; bool flag25c; };
class WaterVirtual { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void render(RenderInfoClass &rinfo); };
class RTS3DScene
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual const Vector3 &Get_Ambient_Light(void);
	void rva00070F80(RenderInfoClass &rinfo);
	void rva000710D6(RenderInfoClass &rinfo);
	void Flush(RenderInfoClass &rinfo);
protected:
	void flushOccludedObjectsIntoStencil(RenderInfoClass &rinfo);
private:
	char m_pad004[0x18 - 0x04];
	int m_polygonMode; // +0x18
	char m_pad01c[0x130 - 0x1c];
	LightClass *m_globalLight[4]; // +0x130
	char m_pad140[0x160 - 0x140];
	int m_numGlobalLights; // +0x160
	char m_pad164[0x7EC - 0x164];
	int m_customPassMode; // +0x7EC
};
void RTS3DScene::Flush(RenderInfoClass &rinfo)
{
	rva001173f0((unsigned)&rinfo);
	if (m_customPassMode == 0 && DX8Wrapper::Has_Stencil())
		flushOccludedObjectsIntoStencil(rinfo);
	if (W3DGCData00DE2000 && TheGameClient && m_customPassMode != 3)
	{
		BFME2ScopedRenderEvent event("RenderWater", "Frame", 0);
		((WaterView *)W3DGCData00DE2000)->flag25c = true;
		((WaterVirtual *)((char *)W3DGCData00DE2000 + 4))->render(rinfo);
		((WaterView *)W3DGCData00DE2000)->flag25c = false;
	}
	if (m_customPassMode == 0 && m_polygonMode == 0 && TheW3DShadowManager)
	{
		BFME2ScopedRenderEvent event("RenderDecalShadows", "Frame", 0);
		TheW3DShadowManager->rva0009A348(rinfo);
	}
	if (DX8Wrapper::Has_Stencil())
	{
		BFME_SET_RS(D3DRS_STENCILENABLE, TRUE);
		BFME_SET_RS(D3DRS_STENCILREF, 0);
		BFME_SET_RS(D3DRS_STENCILMASK, 0xFFFFFFFF);
		BFME_SET_RS(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);
		BFME_SET_RS(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		BFME_SET_RS(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		BFME_SET_RS(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		BFME_SET_RS(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	}
	if (TheTerrainRenderObject)
	{
		LightEnvironmentClass lightEnv;
		Vector3 ambient = Get_Ambient_Light();
		lightEnv.bfmeSetPair((const BfmeVecHF *)&Vector3(0, 0, 0), (const BfmeVecHF *)&ambient);
		Vector3 lodScale(1.0f, 1.0f, 1.0f);
		if (TheCloudEffectManager && TheCloudEffectManager->slot3C())
		{
			Rva0027070CData tmp;
			const Rva0027070CData *p = TheCloudEffectManager->slot48(&tmp);
			lodScale.Set(1.0f - p->a, 1.0f - p->b, 1.0f - p->c);
		}
		if (LODTextureReduction <= 1)
		{
			const SceneLightGlobalView *global = (const SceneLightGlobalView *)TheWritableGlobalData;
			lodScale.X = global->m_lowLODLightScaleRed * lodScale.X;
			lodScale.Y = global->m_lowLODLightScaleGreen * lodScale.Y;
			lodScale.Z = global->m_lowLODLightScaleBlue * lodScale.Z;
		}
		LightClass **lights = m_globalLight;
		for (int i = 0; i < m_numGlobalLights; i++)
		{
			Vector3 diffuse;
			lights[i]->Get_Diffuse(&diffuse);
			Vector3 saved = diffuse;
			diffuse.X *= lodScale.X;
			diffuse.Y *= lodScale.Y;
			diffuse.Z *= lodScale.Z;
			lights[i]->Set_Diffuse(diffuse);
			lightEnv.Add_Light(*lights[i]);
			lights[i]->Set_Diffuse(saved);
		}
		Vector3 outAmbient = lightEnv.Get_Output_Ambient();
		outAmbient.X *= lodScale.X;
		outAmbient.Y *= lodScale.Y;
		outAmbient.Z *= lodScale.Z;
		lightEnv.Set_Output_Ambient(outAmbient);
		rinfo.light_environment = &lightEnv;
		TheTerrainRenderObject->rva0006B895(rinfo);
		rinfo.light_environment = 0;
	}
	BFME_SET_RS(D3DRS_STENCILENABLE, FALSE);
	if (m_customPassMode == 0 && m_polygonMode == 0 && TheW3DShadowManager)
	{
		BFME2ScopedRenderEvent event("RenderVolumeShadows", "Frame", 0);
		((Rva0009A361 *)TheW3DShadowManager)->rva0009A361((int)&rinfo);
	}
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetVertexShader(0);
	++number_of_DX8_calls;
	{
		BFME2ScopedRenderEvent event("RenderStaticSortLists", "Frame", 0);
		WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);
	}
	if (m_customPassMode == 0 && TheTerrainRenderObject)
	{
		TheTerrainRenderObject->rva0006BBD9((int)&rinfo, true);
		TheTerrainRenderObject->rva0006BBD9((int)&rinfo, false);
	}
	if (m_customPassMode == 0 && m_polygonMode == 0)
		rva00070F80(rinfo);
	{
		BFME2ScopedRenderEvent particles("RenderParticles", "Frame", 0);
		if (m_customPassMode == 0 && m_polygonMode == 0)
			Rva0004CB1E((int)&rinfo);
		SortingRendererClass::Flush();
	}
	if (m_customPassMode == 0 && m_polygonMode == 0)
		rva000710D6(rinfo);
	{
		BFME2ScopedRenderEvent smudges("RenderSmudges", "Frame", 0);
		if (m_customPassMode == 0 && m_polygonMode == 0)
			bfmeGo991B((int)&rinfo);
		SortingRendererClass::Flush();
	}
	TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
}
