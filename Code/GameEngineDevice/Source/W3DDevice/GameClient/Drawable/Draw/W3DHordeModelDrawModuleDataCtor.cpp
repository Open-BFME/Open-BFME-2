// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0W3DHordeModelDrawModuleData@@QAE@XZ, retail 0x000789E3, 159 bytes.
// ModuleData ctor over the pinned W3DModelDrawModuleData base (0xC8EEF):
// three 0x14 LOD settings at +0x188/+0x19C/+0x1B0 (AllowMultipleModels bool
// at +0, MaxRandomTextures/Animations ints at +4/+8, MaxAnimFrameDelta float
// at +0xC via literal pool 15.0f/8.0f/0.5f, RandomStartFramePercent int at
// +0x10), vtable 0x00BC6870 explicitly (novtable, shared-fold with Sail).
// Layout from retail FieldParse tables (own LodOptions table 0xBC6B80 via
// parse 0x79305 selecting +0x188 stride 0x14 from table 0xBC6B00, base table
// 0xBCB3C8); values match BFME1 donor W3DHordeModelDrawModuleDataConstructor
// shifted +0x2C for the 0x188 base. Factory at 0x64EBB news 0x1C4 sole caller.
// Row supersedes the ctor pin.

class __declspec(novtable) W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();

private:
	unsigned char m_opaque[0x184];
};

class __declspec(novtable) W3DHordeModelDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DHordeModelDrawModuleData();

private:
	bool m_allow0; // +0x188
	char m_pad189[3];
	int m_maxTex0; // +0x18C
	int m_maxAnim0; // +0x190
	float m_delta0; // +0x194
	int m_start0; // +0x198
	bool m_allow1; // +0x19C
	char m_pad19D[3];
	int m_maxTex1; // +0x1A0
	int m_maxAnim1; // +0x1A4
	float m_delta1; // +0x1A8
	int m_start1; // +0x1AC
	bool m_allow2; // +0x1B0
	char m_pad1B1[3];
	int m_maxTex2; // +0x1B4
	int m_maxAnim2; // +0x1B8
	float m_delta2; // +0x1BC
	int m_start2; // +0x1C0
};

W3DHordeModelDrawModuleData::W3DHordeModelDrawModuleData()
	: W3DModelDrawModuleData()
{
	float f15 = 15.0f;
	float f8 = 8.0f;
	float f05 = 0.5f;
	*(unsigned int *)this = 0x00BC6870;
	m_allow0 = false;
	m_maxTex0 = 1;
	m_maxAnim0 = 1;
	m_delta0 = f15;
	m_start0 = 0;
	m_allow1 = true;
	m_maxTex1 = 2;
	m_maxAnim1 = 2;
	m_delta1 = f8;
	m_start1 = 50;
	m_allow2 = true;
	m_maxTex2 = 999;
	m_maxAnim2 = 999;
	m_delta2 = f05;
	m_start2 = 100;
}
