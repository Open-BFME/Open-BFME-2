// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ?rva000869CF@Rva000869CF@@QAEXXZ @0x000869CF 79B zero-init method, callers 0x00088D0A 0x00086F56 0x0008D477 0x0008D925, no vtable, no donor
struct Rva000869CFVec3
{
	float x;
	float y;
	float z;
};

#include "Rva000869CF.h"

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


// ?rva00086A94@Rva000869CF@@QAEXHHM@Z @0x00086A94 152B; target call at 0x00089C2D reads the 768-float history and index at +0x2070.
void Rva000869CF::rva00086A94(int a, int b, float c)
{
	int index = m_2070;
	_ReadWriteBarrier();
	float *p = &m_1470[index];
	m_146c = c;
	switch (b) {
	case 2:
		p[-2] = c;
		p[-1] = m_1470[0];
		break;
	case 1:
		p[-1] = p[-2] - p[-3] + p[-2];
		break;
	case 0:
		p[-1] = p[-2];
		break;
	default:
		p[-1] = p[-2];
		break;
	}
	switch (a) {
	case 2:
		m_1468 = p[-3];
		break;
	case 1:
		m_1468 = m_146c - m_1470[0] + m_146c;
		break;
	case 0:
		m_1468 = m_146c;
		break;
	default:
		m_1468 = m_146c;
		break;
	}
}
