// cl: /MD
// ?Rva0007912DGet@@YAHXZ @ 0x0007912D (26B): clamped LOD index from
// [0xDFE144]+0x1788. Returns ([global]+0x1788)-1 clamped to 0..2 (dec/jns
// zero path plus push-2/pop-2 cap). Callers 0x79147/0x79157/0x79176 index
// the W3DHordeModelDrawModuleData triple at +0x188 stride 0x14 (bool/int/
// float at +0/+4/+0xC per W3DHordeModelDrawModuleDataCtor.cpp); 0x7A5BF
// compares the same slot against 4. Global models the OptionPreferences
// TheRva00DFE144 struct extended to 0x1788.
// ?rva00079147@W3DHordeModelDrawModuleData@@QAE_NXZ @ 0x00079147 (16B),
// ?rva00079157@W3DHordeModelDrawModuleData@@QAEHXZ @ 0x00079157 (16B) and
// ?rva00079176@W3DHordeModelDrawModuleData@@QAEMXZ @ 0x00079176 (16B) are
// the three LOD accessors over that index (call plus imul 0x14 plus
// [eax+ecx+0x188/0x18C/0x194]); same-TU callee keeps ecx live, /G7 keeps
// the imul (lea law per ScriptEngine_indexedTable.cpp).

struct Rva00DFE144Globals
{
	char m_pad[0x1788];
	int m_1788;
};

extern Rva00DFE144Globals *TheRva00DFE144;

int Rva0007912DGet(void)
{
	int v = TheRva00DFE144->m_1788 - 1;
	if (v < 0)
		return 0;
	if (v > 2)
		return 2;
	return v;
}

struct HordeLodEntry
{
	bool m_allow;
	char m_pad189[3];
	int m_maxTex;
	int m_maxAnim;
	float m_delta;
	int m_start;
};

class W3DHordeModelDrawModuleData
{
public:
	bool rva00079147();
	int rva00079157();
	float rva00079176();
	char m_pad[0x188];
	HordeLodEntry m_lods[3];
};

bool W3DHordeModelDrawModuleData::rva00079147()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_allow;
}

int W3DHordeModelDrawModuleData::rva00079157()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_maxTex;
}

float W3DHordeModelDrawModuleData::rva00079176()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_delta;
}
