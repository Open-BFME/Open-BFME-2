// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// ?updateFixedLightEnvironments@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z,
// retail 0x0006E716..0x0006EB3B (1061 bytes, RET 4). Zero Hour's
// RTS3DScene::updateFixedLightEnvironments as Open-BFME-1 reconstructed it
// for BFME (game/.../W3DScene.cpp: three light environments, the infantry
// lights feeding the third, the scratch light carrying fogged copies), with
// BFME 2's additions read from retail: below static LOD 2 (the owned
// LODTextureReduction) every light's diffuse is scaled by the global data's
// low-LOD light scale (+0x944) while it is added and then restored, the
// fogged copies take the scaled diffuse, and each environment's ambient
// (+0x164) is scaled afterwards. BFME 2's scene keeps the lights at
// +0x130 (globals), +0x140 (scratch), +0x144 (infantry ambient), +0x150
// (infantry), +0x160 (count) and the environments at +0x164/+0x38C/+0x5B4;
// the fog fraction is the global data's byte +0xBE9 over +0xBE8. Retail
// builds this body at /O1 (EBP frame), unlike the /O2 rows of W3DScene.cpp.

typedef int Int;
typedef float Real;

#include "vector3.h"

class Matrix3D;

#define PAD_VIRTUAL10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

// The RenderObjClass transform protocol: slot 20 validates the transform at
// +0x18, slot 21 sets it.
class RenderObjClass
{
public:
	PAD_VIRTUAL10(a) PAD_VIRTUAL10(b)
	virtual void Validate_Transform(void) const;		// slot 20
	virtual void Set_Transform(const Matrix3D &m);		// slot 21
	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *reinterpret_cast<const Matrix3D *>(Transform);
	}
protected:
	char m_pad04[0x18 - 0x04];
	char Transform[0x30];					// +0x18
};

class LightClass : public RenderObjClass
{
public:
	// The rowed out-of-line accessors (0x0006920D/0x0006922E), visible as in
	// the WW3D header: cl then knows they keep no pointer to the colour
	// local and schedules the scratch light's load ahead of it as retail.
	__declspec(noinline) void Get_Ambient(Vector3 *color) const { if (color != 0) *color = Ambient; }
	__declspec(noinline) void Get_Diffuse(Vector3 *color) const { if (color != 0) *color = Diffuse; }
	void Set_Ambient(const Vector3 &color) { Ambient = color; }
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
private:
	char m_pad48[0xD4 - 0x48];
	Vector3 Ambient;					// +0xD4
	Vector3 Diffuse;					// +0xE0
};

class CameraClass : public RenderObjClass
{
};

#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"

// LightEnvironmentClass::Reset is rowed under its placeholder spelling. It is
// called directly (an inline Reset wrapper over it loses retail's early
// LEA of the first environment).
class BfmeVecHF;
#include "../../../Include/W3DDevice/GameClient/Gen_0094AC70.h"

class LightEnvironmentClass : public Gen_0094AC70
{
public:
	void Add_Light(const LightClass &light);
	void Pre_Render_Update(const Matrix3D &camera);

	unsigned char m_flag;					// +0x00
	char m_pad01[0x164 - 0x01];
	// WorldBuilder copies the ambient out, scales it and stores it back.
	const Vector3 &Get_Output_Ambient(void) const { return m_outputAmbient; }
	void Set_Output_Ambient(const Vector3 &ambient) { m_outputAmbient = ambient; }
	Vector3 m_outputAmbient;				// +0x164
	char m_pad170[0x228 - 0x170];
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct SceneLightGlobalView
{
	char m_pad000[0x68];
	bool m_enableBehindBuildingMarkers;			// +0x68
	char m_pad069[0x944 - 0x69];
	Real m_lowLODLightScaleRed;				// +0x944
	Real m_lowLODLightScaleGreen;
	Real m_lowLODLightScaleBlue;
	char m_pad950[0xBE8 - 0x950];
	unsigned char m_fogAlpha;				// +0xBE8
	unsigned char m_clearAlpha;				// +0xBE9
};
extern int LODTextureReduction;

// Zero Hour Override.h: OVERRIDE<T>::operator-> null-checks the base entry and
// inlines one level of Overridable::getFinalOverride, whose recursion stays the
// out-of-line COMDAT (retail 0x001E35DF, pinned). Spelling Render through these
// two inline levels gives retail its two temporaries per weather read (the inner
// result spilled, the outer one a register phi with the null arm's zero).
#include "../../../../GameEngine/Include/Common/Overridable.h"
class WeatherSetting : public Overridable
{
public:
	char m_pad10[0x8C - 0x10];
	Real m_fogColorR, m_fogColorG, m_fogColorB;		// +0x8C
	bool m_fogEnabled;					// +0x98
	Real m_fogStart;					// +0x9C
	Real m_fogEnd;						// +0xA0
};
template <class T> class OVERRIDE
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	const T *operator*(void) const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
private:
	const T *m_overridable;
	int m_pad04;
	int m_pad08;
};
extern OVERRIDE<WeatherSetting> TheWeatherSetting;
extern bool bfmeCameraProjectionOverride;

#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static bool Has_Stencil();
	static unsigned Convert_Color(const Vector3 &color, float alpha);
	static void Set_Fog(bool enable, const Vector3 &color, float start, float end);
protected:
	// dx8wrapper.cpp defines these as protected statics (@@1, data ledger 0x009EDA21/24).
	static bool FogEnable;
	static unsigned long FogColor;
};
// The fog range globals keep the ledger's spellings (owners fxshadernamespaceww3d.cpp
// 0x009EDA28 and GlobalFloatGetters.cpp 0x009EDA2C), as in Rva0006F0BBSetFog.cpp.
extern float g_Va00DEDA28;
extern float g_Va00DEDA2C;
// dx8wrapper.h's x87 colour packing, as in RTS3DSceneFlushTranslucent.cpp.
__forceinline unsigned DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;
	__asm
	{
		sub	esp,20
		fwait
		fstcw		[esp+16]
		mov		eax,[esp+16]
		mov		edi,eax
		and		eax,~(1024|2048)
		or			eax,(1024|2048)
		sub		edi,eax
		jz			skip
		mov		[esp],eax
		fldcw		[esp]
skip:
		mov	esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov	ecx,[esp]
		mov	eax,[esp+4]
		mov	edx,[esp+8]
		mov	ebx,[esp+12]
		shl	ecx,24
		shl	ebx,16
		shl	edx,8
		or		eax,ecx
		or		eax,ebx
		or		eax,edx
		fstp	st(0)
		cmp	edi,0
		je		not_changed
		fwait
		fldcw	[esp+16];
not_changed:
		add	esp,20
		mov	col,eax
	}
	return col;
}
// dx8wrapper.h Set_Fog, forced inline as in retail Render (its out-of-line
// copy in retail's W3DScene.obj is the rowed 0x0006F0BB).
// ?DX8Wrapper::Set_Fog present-unmatched
__forceinline void DX8Wrapper::Set_Fog(bool enable, const Vector3 &color, float start, float end)
{
	DX8Wrapper::FogEnable = enable;
	DX8Wrapper::FogColor = DX8Wrapper::Convert_Color(color, 0.0f);
	g_Va00DEDA28 = start;
	g_Va00DEDA2C = end;
	ShaderClass::Invalidate();
	DX8Wrapper::Set_DX8_Render_State(36, *(unsigned *)(&start));
	DX8Wrapper::Set_DX8_Render_State(37, *(unsigned *)(&end));
}


class RTS3DScene
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual const Vector3 &Get_Ambient_Light(void);		// slot 7
	virtual void Set_Fog_Enable(bool set);			// slot 8
	virtual void s9();
	virtual void Set_Fog_Color(const Vector3 &color);		// slot 10
	virtual void s11();
	virtual void Set_Fog_Range(float start, float end);		// slot 12
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
	virtual void s21(); virtual void s22();
	virtual void Customized_Render(RenderInfoClass &rinfo);	// slot 23
	virtual void Render(RenderInfoClass &rinfo);
	void Flush(RenderInfoClass &rinfo);				// 0x00071606
protected:
	void updateFixedLightEnvironments(RenderInfoClass &rinfo);
public:
	void rva0006E605(Vector3 *delta, bool remove);	// 0x0006E605
protected:
private:
	char m_pad004[0x18 - 0x04];
	Int m_extraPassPolygonMode;				// +0x18
	bool m_fogEnabled;					// +0x1C
	Vector3 m_fogColor;					// +0x20
	Real m_fogStart;					// +0x2C
	Real m_fogEnd;						// +0x30
	char m_pad034[0x130 - 0x34];
	LightClass *m_globalLight[4];				// +0x130
	LightClass *m_scratchLight;				// +0x140
	Vector3 m_infantryAmbient;				// +0x144
	LightClass *m_infantryLight[4];				// +0x150
	Int m_numGlobalLights;					// +0x160
	LightEnvironmentClass m_defaultLightEnv;		// +0x164
	LightEnvironmentClass m_foggedLightEnv;			// +0x38C
	LightEnvironmentClass m_ambientLightEnv;		// +0x5B4
	unsigned char m_lightEnvironmentFlag;			// +0x7DC
	char m_pad7DD[0x7EC - 0x7DD];
	Int m_customPassMode;					// +0x7EC
};

void RTS3DScene::updateFixedLightEnvironments(RenderInfoClass &rinfo)
{
	const SceneLightGlobalView *global = reinterpret_cast<const SceneLightGlobalView *>(TheWritableGlobalData);
	Real foggedLightFrac = (Real)global->m_clearAlpha / (Real)global->m_fogAlpha;
	Vector3 lodScale(1.0f, 1.0f, 1.0f);
	if (LODTextureReduction < 2)
	{
		lodScale.X = global->m_lowLODLightScaleRed;
		lodScale.Y = global->m_lowLODLightScaleGreen;
		lodScale.Z = global->m_lowLODLightScaleBlue;
	}

	m_defaultLightEnv.bfmeSetPair(reinterpret_cast<const BfmeVecHF *>(&Vector3(0, 0, 0)), reinterpret_cast<const BfmeVecHF *>(&Get_Ambient_Light()));
	m_foggedLightEnv.bfmeSetPair(reinterpret_cast<const BfmeVecHF *>(&Vector3(0, 0, 0)), reinterpret_cast<const BfmeVecHF *>(&(Get_Ambient_Light() * foggedLightFrac)));
	m_ambientLightEnv.bfmeSetPair(reinterpret_cast<const BfmeVecHF *>(&Vector3(0, 0, 0)), reinterpret_cast<const BfmeVecHF *>(&m_infantryAmbient));

	for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
	{
		Vector3 diffuse;
		m_globalLight[globalLightIndex]->Get_Diffuse(&diffuse);
		m_globalLight[globalLightIndex]->Set_Diffuse(Vector3(diffuse.X * lodScale.X, diffuse.Y * lodScale.Y, diffuse.Z * lodScale.Z));
		m_defaultLightEnv.Add_Light(*m_globalLight[globalLightIndex]);
		m_globalLight[globalLightIndex]->Set_Diffuse(diffuse);
		if (m_infantryLight[globalLightIndex])
		{
			Vector3 infantryDiffuse;
			m_infantryLight[globalLightIndex]->Get_Diffuse(&infantryDiffuse);
			m_infantryLight[globalLightIndex]->Set_Diffuse(Vector3(infantryDiffuse.X * lodScale.X, infantryDiffuse.Y * lodScale.Y, infantryDiffuse.Z * lodScale.Z));
			m_ambientLightEnv.Add_Light(*m_infantryLight[globalLightIndex]);
			m_infantryLight[globalLightIndex]->Set_Diffuse(infantryDiffuse);
		}

		m_scratchLight->Set_Transform(m_globalLight[globalLightIndex]->Get_Transform());
		Vector3 oldLightColor;
		m_globalLight[globalLightIndex]->Get_Diffuse(&oldLightColor);
		oldLightColor.Scale(lodScale);
		m_scratchLight->Set_Diffuse(oldLightColor * foggedLightFrac);
		m_globalLight[globalLightIndex]->Get_Ambient(&oldLightColor);
		m_scratchLight->Set_Ambient(oldLightColor * foggedLightFrac);
		m_foggedLightEnv.Add_Light(*m_scratchLight);
	}

	Vector3 ambient;
	ambient = m_defaultLightEnv.Get_Output_Ambient();
	ambient.Scale(lodScale);
	m_defaultLightEnv.Set_Output_Ambient(ambient);
	ambient = m_foggedLightEnv.Get_Output_Ambient();
	ambient.Scale(lodScale);
	m_foggedLightEnv.Set_Output_Ambient(ambient);
	ambient = m_ambientLightEnv.Get_Output_Ambient();
	ambient.Scale(lodScale);
	m_ambientLightEnv.Set_Output_Ambient(ambient);

	m_defaultLightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
	m_defaultLightEnv.m_flag = m_lightEnvironmentFlag;
	m_foggedLightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
	m_foggedLightEnv.m_flag = m_lightEnvironmentFlag;
	m_ambientLightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
	m_ambientLightEnv.m_flag = m_lightEnvironmentFlag;
}

// ?rva0006E605@RTS3DScene@@QAEXPAVVector3@@_N@Z, retail 0x0006E605..0x0006E716
// (273 bytes, RET 8; the spelling is pinned through its caller 0x000982F9,
// which loads the receiver from W3DDisplay::m_3DScene). It adds a colour
// delta to the first global light (+0x130), or removes it: the full delta
// on the diffuse and half of it on the ambient, read through the rowed
// Get_Diffuse/Get_Ambient and stored back by one shared tail. Retail's
// compound per-component update (diffuse -= delta / += delta) is what keeps
// the six results in xmm0-5 ahead of that tail.
void RTS3DScene::rva0006E605(Vector3 *delta, bool remove)
{
	Vector3 diffuse;
	m_globalLight[0]->Get_Diffuse(&diffuse);
	Vector3 ambient;
	m_globalLight[0]->Get_Ambient(&ambient);
	if (remove)
	{
		diffuse -= *delta;
		ambient -= *delta * 0.5f;
	}
	else
	{
		diffuse += *delta;
		ambient += *delta * 0.5f;
	}
	m_globalLight[0]->Set_Diffuse(diffuse);
	m_globalLight[0]->Set_Ambient(ambient);
}

// ?Render@RTS3DScene@@UAEXAAVRenderInfoClass@@@Z, retail 0x00071E40..0x00072109
// (713 bytes, RET 4). Zero Hour's RTS3DScene::Render default pass with BFME 2's
// weather fog in front: the final WeatherSetting override switches the scene
// fog on (only when not under the camera projection override and at static
// LOD 1 or better) and copies its colour (+0x8C) and range (+0x9C/+0xA0)
// through the scene's fog virtuals (slots 8/10/12), then DX8Wrapper::Set_Fog,
// the stencil gate on the behind-building markers, and for the pass modes
// 0/3/4 the fixed light environments (same unit, as in retail's W3DScene.obj)
// before Customized_Render (slot 23) and Flush (0x00071606); modes 5/6/7 skip
// only the light update (one shared tail after cross-jumping).
void RTS3DScene::Render(RenderInfoClass &rinfo)
{
	if (*TheWeatherSetting)
	{
		Set_Fog_Enable(TheWeatherSetting->m_fogEnabled && !bfmeCameraProjectionOverride && LODTextureReduction >= 1);
		if (TheWeatherSetting->m_fogEnabled)
		{
			Set_Fog_Color(Vector3(TheWeatherSetting->m_fogColorR, TheWeatherSetting->m_fogColorG, TheWeatherSetting->m_fogColorB));
			Set_Fog_Range(TheWeatherSetting->m_fogStart, TheWeatherSetting->m_fogEnd);
		}
	}
	DX8Wrapper::Set_Fog(m_fogEnabled, m_fogColor, m_fogStart, m_fogEnd);

	SceneLightGlobalView *const &global = reinterpret_cast<SceneLightGlobalView *const &>(TheWritableGlobalData);
	global->m_enableBehindBuildingMarkers = global->m_enableBehindBuildingMarkers && DX8Wrapper::Has_Stencil();

	if (m_extraPassPolygonMode == 0)
	{
		if (m_customPassMode == 0 || m_customPassMode == 3 || m_customPassMode == 4)
		{
			updateFixedLightEnvironments(rinfo);
			Customized_Render(rinfo);
			Flush(rinfo);
		}
		else if (m_customPassMode == 5 || m_customPassMode == 6 || m_customPassMode == 7)
		{
			Customized_Render(rinfo);
			Flush(rinfo);
		}
	}
}
