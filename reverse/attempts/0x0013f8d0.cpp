// ?rva0013F8D0@Rva0013F8D0@@QBE_NABV1@@Z
// partial score=0.94 date=2026-10-06
// cl: /Ob2 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva0013F8D0@Rva0013F8D0@@QBE_NABV1@@Z, 0x0013F8D0 626B: LightEnvironmentClass equality over OutputAmbient plus point/directional InputLights partitions; callers 0x00149A90, callees countPoint/findPoint rows at 0x0013F750/0x0013F780, neighbours lightenvironment.cpp/Rva0013F6F0Cluster.cpp.

struct EnvVector3
{
	float x;
	float y;
	float z;
};

struct EnvInputLight
{
	EnvVector3 Direction;
	EnvVector3 Ambient;
	EnvVector3 Diffuse;
	bool DiffuseRejected;
	bool Point;
	EnvVector3 Center;
	float InnerRadius;
	float OuterRadius;
	EnvVector3 PointAmbient;
	EnvVector3 PointDiffuse;
};

class Rva0013F6F0LightEnv
{
public:
	int countPoint() const;
	int findPoint(int index) const;
};

class Rva0013F8D0
{
public:
	bool rva0013F8D0(const Rva0013F8D0 &that) const;

private:
	unsigned char m_leading;
	int m_count;
	EnvVector3 m_center;
	EnvInputLight m_lights[4];
	EnvVector3 m_outputAmbient;
};

bool Rva0013F8D0::rva0013F8D0(const Rva0013F8D0 &that) const
{
	if (this == &that)
		return true;
	if (!(m_outputAmbient.x == that.m_outputAmbient.x)
		|| !(m_outputAmbient.y == that.m_outputAmbient.y)
		|| !(m_outputAmbient.z == that.m_outputAmbient.z))
		return false;
	int lightCount = m_count;
	int nonThis = 0;
	if (lightCount > 0) {
		const EnvInputLight *light = m_lights;
		int remain = lightCount;
		do {
			if (light->Point == false)
				++nonThis;
			++light;
			--remain;
		} while (remain != 0);
	}
	int thatCount = that.m_count;
	int nonThat = 0;
	if (thatCount > 0) {
		const EnvInputLight *light = that.m_lights;
		do {
			if (light->Point == false)
				++nonThat;
			++light;
			--thatCount;
		} while (thatCount != 0);
	}
	if (nonThis != nonThat)
		return false;
	const Rva0013F6F0LightEnv *pThis = (const Rva0013F6F0LightEnv *)this;
	const Rva0013F6F0LightEnv *pThat = (const Rva0013F6F0LightEnv *)&that;
	if (pThis->countPoint() != pThat->countPoint())
		return false;
	int nPoint = pThis->countPoint();
	for (int n = nPoint - 1; n >= 0; --n) {
		int idx = pThis->findPoint(n);
		if (!(m_lights[idx].PointDiffuse.x == that.m_lights[idx].PointDiffuse.x)
			|| !(m_lights[idx].PointDiffuse.y == that.m_lights[idx].PointDiffuse.y)
			|| !(m_lights[idx].PointDiffuse.z == that.m_lights[idx].PointDiffuse.z)
			|| !(m_lights[idx].Center.x == that.m_lights[idx].Center.x)
			|| !(m_lights[idx].Center.y == that.m_lights[idx].Center.y)
			|| !(m_lights[idx].Center.z == that.m_lights[idx].Center.z)
			|| !(m_lights[idx].OuterRadius == that.m_lights[idx].OuterRadius))
			return false;
	}
	int nNon = 0;
	if (lightCount > 0) {
		const EnvInputLight *light = m_lights;
		int remain = lightCount;
		do {
			if (light->Point == false)
				++nNon;
			++light;
			--remain;
		} while (remain != 0);
	}
	for (int n = nNon - 1; n >= 0; --n) {
		int remain = n;
		int idx = -1;
		int result = 0;
		if (lightCount > 0) {
			const EnvInputLight *light = m_lights;
			do {
				if (light->Point == false) {
					if (remain == 0) {
						idx = result;
						break;
					}
					--remain;
				}
				++result;
				++light;
			} while (result < lightCount);
		}
		if (!(m_lights[idx].Diffuse.x == that.m_lights[idx].Diffuse.x)
			|| !(m_lights[idx].Diffuse.y == that.m_lights[idx].Diffuse.y)
			|| !(m_lights[idx].Diffuse.z == that.m_lights[idx].Diffuse.z)
			|| !(m_lights[idx].Direction.x == that.m_lights[idx].Direction.x)
			|| !(m_lights[idx].Direction.y == that.m_lights[idx].Direction.y)
			|| !(m_lights[idx].Direction.z == that.m_lights[idx].Direction.z))
			return false;
	}
	return true;
}
