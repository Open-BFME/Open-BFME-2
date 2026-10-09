// Target light environment comparison13F8D0..13FB45 (629B, final RET4 included).
// Neutral owner retained: neighbour lightenvironment.cpp and caller149A90 support
// LightEnvironment semantics; WB/ZH alone do not supply a target method spelling.
// OutputAmbient equality followed by point/non-point partitions. Target InputLights
// begins14, stride54, point flag25; scans/providers below prove each offset.
// Unified failure edge retains retail's early EBX/EBP saves. Walk the non-point
// flags as bytes so LEA of this+39 precedes the count-register copy in both scans.
// Inlining the established non-point index loop preserves native -1/not-found flow.
// Scalar float equality deliberately retains unordered/NaN comparison behavior.
// cl: /Ob2 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Comparison 0x0013F8D0 629B: LightEnvironmentClass equality over OutputAmbient plus point/directional InputLights partitions; callers 0x00149A90, callees countPoint/findPoint rows at 0x0013F750/0x0013F780, neighbours lightenvironment.cpp/Rva0013F6F0Cluster.cpp.

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

__forceinline int Rva0013F6F0LightEnv::findNonPoint(int index) const
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

bool Rva0013F8D0::rva0013F8D0(const Rva0013F8D0 &that) const
{
	if (this == &that)
		return true;
	if (!(m_outputAmbient.x == that.m_outputAmbient.x)
		|| !(m_outputAmbient.y == that.m_outputAmbient.y)
		|| !(m_outputAmbient.z == that.m_outputAmbient.z))
		goto fail;
	int lightCount = m_count;
	int nonThis = 0;
	if (lightCount > 0) {
		const char* light=(const char*)m_lights+0x25;
		int remain = lightCount;
		do {
			if (*light == 0)
				++nonThis;
			light=(const char*)((const char*)light+sizeof(EnvInputLight));
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
		goto fail;
	const Rva0013F6F0LightEnv *pThis = (const Rva0013F6F0LightEnv *)this;
	const Rva0013F6F0LightEnv *pThat = (const Rva0013F6F0LightEnv *)&that;
	if (pThis->countPoint() != pThat->countPoint())
		goto fail;
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
			goto fail;
	}
	int nNon = 0;
	if (lightCount > 0) {
		const char* light=(const char*)m_lights+0x25;
		int remain = lightCount;
		do {
			if (*light == 0)
				++nNon;
			light=(const char*)((const char*)light+sizeof(EnvInputLight));
			--remain;
		} while (remain != 0);
	}
	for (int n = nNon - 1; n >= 0; --n) {
		int idx=pThis->findNonPoint(n);
		if (!(m_lights[idx].Diffuse.x == that.m_lights[idx].Diffuse.x)
			|| !(m_lights[idx].Diffuse.y == that.m_lights[idx].Diffuse.y)
			|| !(m_lights[idx].Diffuse.z == that.m_lights[idx].Diffuse.z)
			|| !(m_lights[idx].Direction.x == that.m_lights[idx].Direction.x)
			|| !(m_lights[idx].Direction.y == that.m_lights[idx].Direction.y)
			|| !(m_lights[idx].Direction.z == that.m_lights[idx].Direction.z))
			goto fail;
	}
	return true;
fail:
 return false;
}
