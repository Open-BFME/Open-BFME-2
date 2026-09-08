// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmelight /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// BFME2 direct reconstruction of DX8Wrapper::Set_Light_Environment.
#include "dx8wrapper.h"
#include "lightenvironment.h"
#include <math.h>

struct Bfme2LightEnvironmentInputView
{
	Vector3 Direction;
	Vector3 Ambient;
	Vector3 Diffuse;
	bool DiffuseRejected;
	bool Point;
	Vector3 Center;
	float InnerRadius;
	float OuterRadius;
	Vector3 PointAmbient;
	Vector3 PointDiffuse;
};

struct Bfme2LightEnvironmentView
{
	// The BFME2 environment carries a one-byte state before the donor fields.
	// The shifted view is kept local so the legacy reference header stays intact.
	unsigned char State;
	unsigned char StatePadding[3];
	int LightCount;
	Vector3 ObjectCenter;
	Bfme2LightEnvironmentInputView InputLights[4];
	Vector3 OutputAmbient;
	const Vector3 &Get_Equivalent_Ambient() const { return OutputAmbient; }
	int Get_Light_Count() const { return LightCount; }
};

// The identical D3DLIGHT8 overload is already claimed in dx8wrapper.cpp at
// RVA 0x0011DD20.  Keep this TU-local definition so MSVC inlines its body into
// the recovered environment loop; folding the method into that TU removes the
// duplicate definition without changing either body.
void DX8Wrapper::Set_Light(unsigned index, const D3DLIGHT8* light)
{
	if (light) {
		render_state.Lights[index] = *light;
		render_state.LightEnable[index] = true;
	} else {
		render_state.LightEnable[index] = false;
	}
	render_state_changed |= (LIGHT0_CHANGED << index);
}

void DX8Wrapper::Set_Light_Environment(LightEnvironmentClass* light_env)
{
	Bfme2LightEnvironmentView *environment =
		reinterpret_cast<Bfme2LightEnvironmentView *>(light_env);
	if (Light_Environment == light_env && light_env && environment->State) {
		return;
	}

	Light_Environment = light_env;

	extern bool bfmeSkipFixedFunctionState;
	if (!light_env || bfmeSkipFixedFunctionState) {
		return;
	}

	int light_count = environment->Get_Light_Count();
	unsigned int color = Convert_Color(environment->Get_Equivalent_Ambient(), 0.0f);
	if (RenderStates[D3DRS_AMBIENT] != color) {
		Set_DX8_Render_State(D3DRS_AMBIENT, color);
	}

	D3DLIGHT8 light;
	int l = 0;
	for (; l < light_count; ++l) {
		::ZeroMemory(&light, sizeof(D3DLIGHT8));

		light.Type = D3DLIGHT_DIRECTIONAL;
		(Vector3&)light.Diffuse = environment->InputLights[l].Diffuse;
		Vector3 dir = -environment->InputLights[l].Direction;
		light.Direction = (const D3DVECTOR&)dir;

		if (l == 0) {
			light.Specular.r = light.Specular.g = light.Specular.b = 1.0f;
		}

		if (environment->InputLights[l].Point) {
			light.Type = D3DLIGHT_POINT;
			(Vector3&)light.Diffuse = environment->InputLights[l].PointDiffuse;
			(Vector3&)light.Ambient = environment->InputLights[l].PointAmbient;
			light.Position = (const D3DVECTOR&)environment->InputLights[l].Center;
			light.Range = environment->InputLights[l].OuterRadius;

			double a, b;
			b = environment->InputLights[l].OuterRadius;
			a = environment->InputLights[l].InnerRadius;
			light.Attenuation0 = 1.0f;
			if (fabs(a - b) < 1e-5) {
				light.Attenuation1 = 0.0f;
			} else {
				light.Attenuation1 = (float)0.1 / a;
			}
			light.Attenuation2 = 8.0f / (b * b);
		}

		Set_Light(l, &light);
	}

	for (; l < 4; ++l) {
		Set_Light(l, NULL);
	}
}
