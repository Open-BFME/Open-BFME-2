// cl: /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Four LightEnvironmentClass scans over the InputLights array, 0x0013F6F0..0x0013F780.
//
// Retail's object carries a vptr (the near lightenvironment.cpp indexes every
// member through `(char*)this + 4`), so LightCount sits at this+4, InputLights
// at this+0x14 and the per-light stride is 0x54. Within InputLightStruct,
// m_point is the bool at +0x25, i.e. this+0x39 for element zero -- exactly the
// byte these loops test. Two bodies count the directional (m_point==0) and
// point (m_point!=0) lights; the other two return the index of the n-th light
// of each kind, or -1. Identity beyond LightEnvironmentClass is unproven, so
// the names are address-derived.

struct Rva0013F6F0Light
{
	char m_pad00[0x25];
	bool m_point;			// this+0x39 for element zero
	char m_pad26[0x54 - 0x26];
};

class Rva0013F6F0LightEnv
{
public:
	int countNonPoint() const;
	int countPoint() const;
	int findNonPoint(int index) const;
	int findPoint(int index) const;

private:
	int m_vptr;
	int m_count;
	char m_objectCenter[0x0C];
	Rva0013F6F0Light m_lights[4];
};

int Rva0013F6F0LightEnv::countNonPoint() const
{
	int result = 0;
	int count = m_count;
	if (count > 0) {
		const Rva0013F6F0Light *light = m_lights;
		do {
			if (light->m_point == false)
				++result;
			++light;
			--count;
		} while (count != 0);
	}
	return result;
}

int Rva0013F6F0LightEnv::countPoint() const
{
	int result = 0;
	int count = m_count;
	if (count > 0) {
		const Rva0013F6F0Light *light = m_lights;
		do {
			if (light->m_point != false)
				++result;
			++light;
			--count;
		} while (count != 0);
	}
	return result;
}

int Rva0013F6F0LightEnv::findNonPoint(int index) const
{
	int result = 0;
	int count = m_count;
	if (count > 0) {
		const Rva0013F6F0Light *light = m_lights;
		do {
			if (light->m_point == false) {
				if (index == 0)
					return result;
				--index;
			}
			++result;
			++light;
		} while (result < count);
	}
	return -1;
}

int Rva0013F6F0LightEnv::findPoint(int index) const
{
	int result = 0;
	int count = m_count;
	if (count > 0) {
		const Rva0013F6F0Light *light = m_lights;
		do {
			if (light->m_point != false) {
				if (index == 0)
					return result;
				--index;
			}
			++result;
			++light;
		} while (result < count);
	}
	return -1;
}
