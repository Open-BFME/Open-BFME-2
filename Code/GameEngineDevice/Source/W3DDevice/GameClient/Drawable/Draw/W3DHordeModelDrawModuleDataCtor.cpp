// cl: /DNDEBUG /MD
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

// Vtable 0x00BC6870: the table whose slot 0 is ??_GRva000D089D (vftable_map); bound to the ??_7 the ledger's deleting-dtor unit emits.
extern "C" const void *__identifier("??_7Rva000D089D@@6B@")[];

struct HordeLodEntry
{
	bool m_allow;
	char m_pad189[3];
	int m_maxTex;
	int m_maxAnim;
	float m_delta;
	int m_start;
};
class MultiIniFieldParse;
class __declspec(novtable) W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();
private:
	unsigned char m_opaque[0x184]; // +0x04
};
class W3DHordeModelDrawModuleData;
class __declspec(novtable) W3DHordeModelDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DHordeModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	__declspec(noinline) bool rva00079147();
	__declspec(noinline) int rva00079157();
	__declspec(noinline) int rva00079167();
	__declspec(noinline) float rva00079176();
	int rva00079186(int count);
	HordeLodEntry m_lods[3];
};

W3DHordeModelDrawModuleData::W3DHordeModelDrawModuleData()
	: W3DModelDrawModuleData()
{
	float f15 = 15.0f;
	float f8 = 8.0f;
	float f05 = 0.5f;
	*(unsigned int *)this = (unsigned int)__identifier("??_7Rva000D089D@@6B@");
	m_lods[0].m_allow = false;
	m_lods[0].m_maxTex = 1;
	m_lods[0].m_maxAnim = 1;
	m_lods[0].m_delta = f15;
	m_lods[0].m_start = 0;
	m_lods[1].m_allow = true;
	m_lods[1].m_maxTex = 2;
	m_lods[1].m_maxAnim = 2;
	m_lods[1].m_delta = f8;
	m_lods[1].m_start = 50;
	m_lods[2].m_allow = true;
	m_lods[2].m_maxTex = 999;
	m_lods[2].m_maxAnim = 999;
	m_lods[2].m_delta = f05;
	m_lods[2].m_start = 100;
}
