// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// MeshClass::Set_Lighting_Environment, retail 0x0014BB20 (66 bytes): the
// REL32 callee of MeshClass::Render 0x0014BB90 (pinned). BFME 2's
// LightEnvironmentClass starts with a flag byte: an environment that has it set
// is referenced as is; otherwise it is copied into the mesh's own environment
// (LightEnvironmentClass::operator= 0x0014A230) and that copy is used.
// Layout: LightEnvironment at +0xC8 and the local copy at +0xCC, as
// MeshClass::Render reads them.

#include "../../../Libraries/Source/WWVegas/WW3D2/LightEnvironmentClass.h"

class MeshClass
{
public:
	void Set_Lighting_Environment(LightEnvironmentClass *light_env);

private:
	char m_head[0xC8];					// +0x00
	LightEnvironmentClass *LightEnvironment;		// +0xC8
	LightEnvironmentClass m_localLightEnv;			// +0xCC
};

// ?Set_Lighting_Environment@MeshClass@@QAEXPAVLightEnvironmentClass@@@Z
void MeshClass::Set_Lighting_Environment(LightEnvironmentClass *light_env)
{
	if (light_env)
	{
		if (light_env->field00)
		{
			LightEnvironment = light_env;
			return;
		}

		m_localLightEnv = *light_env;
		LightEnvironment = &m_localLightEnv;
		return;
	}

	LightEnvironment = 0;
}
