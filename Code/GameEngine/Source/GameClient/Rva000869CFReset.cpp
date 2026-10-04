// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// ?rva000869CF@Rva000869CF@@QAEXXZ @0x000869CF 79B zero-init method, callers 0x00088D0A 0x00086F56 0x0008D477 0x0008D925, no vtable, no donor
struct Rva000869CFVec3
{
	float x;
	float y;
	float z;
};

class Rva00088D0AMember
{
public:
	virtual float v0();
	virtual float v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7(float value);
};

class Rva000869CF
{
public:
	float *rva000869CF();
	void rva00088D0A(float value, int unused, float scale);

	char m_pad0[0x4c];
	float m_4c;
	char m_pad50[0x58 - 0x50];
	int m_58;
	int m_5c;
	char m_pad60[0x8];
	float m_68;
	char m_pad6c[0x170];
	unsigned char m_1dc;
	char m_pad1dd[0x27];
	unsigned char m_204;
	char m_pad205[0x23];
	unsigned char m_228;
	char m_pad229[0x53];
	unsigned char m_27c;
	unsigned char m_27d;
	char m_pad27e[0x20d6];
	int m_2354;
	char m_pad2358[0x70];
	unsigned char m_23c8;
	char m_pad23c9[0x83];
	float m_244cArr[3];
	char m_pad2458[0x24c8 - 0x2458];
	Rva00088D0AMember m_24c8;
};

float *Rva000869CF::rva000869CF()
{
	float *vec = m_244cArr;
	m_2354 = 0;
	m_1dc = 0;
	m_204 = 0;
	m_228 = 0;
	m_27d = 0;
	m_27c = 0;
	m_23c8 = 0;
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
	m_58 = 0;
	m_5c = 0;
	m_68 = 0.0f;
	return vec;
}

// ?rva00088D0A@Rva000869CF@@QAEXMHM@Z @0x00088D0A 91B, slot 0 of the table
// at VA 0x00BC764C: reset through 0x000869CF (same unit, so retail keeps
// ECX across the call), store the first argument at +0x4C, rescale the
// +0x24C8 member's slot-7 value from its slot 1 by the third argument, and
// pull slot 7 down to slot 0 when slot 0 exceeds slot 1. The second
// argument is unused. Retail compares with fcompi under /arch:SSE.
void Rva000869CF::rva00088D0A(float value, int unused, float scale)
{
	rva000869CF();
	m_4c = value;
	m_24c8.v7(m_24c8.v1() * scale);
	if (m_24c8.v0() > m_24c8.v1())
		m_24c8.v7(m_24c8.v0());
}
