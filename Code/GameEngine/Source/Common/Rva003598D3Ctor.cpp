// cl: /O1
// ??0Rva003598D3@@QAE@HHH_N@Z, retail 0x003598D3, 47 bytes.
// Ctor storing vtable 0x008153DC (TerrainResource string after) at [this]:
// mov eax,ecx; mov ecx,[esp+4]; and [eax+0x10],0; and [eax+0x14],0;
// mov [eax+4],ecx; mov ecx,[esp+8]; mov [eax+8],ecx; mov ecx,[esp+0xC];
// mov [eax+0xC],ecx; mov cl,[esp+0x10]; mov [eax],vtable; mov [eax+0x18],cl;
// ret 0x10 (thiscall, 4 args). Caller at 0x00359F94 pushes [ebp+0x14]/[edi+0x74]/
// (0 or 0x7FFFF43)/esi with this lea [ebp-0x38]. Identity stays honest Rva
// ctor (class unproven, vtable string TerrainResou... only).
class Rva003598D3
{
public:
	virtual ~Rva003598D3();
	Rva003598D3(int a1, int a2, int a3, bool a4);
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	bool m_18;
};
Rva003598D3::Rva003598D3(int a1, int a2, int a3, bool a4)
{
	m_10 = 0;
	m_14 = 0;
	m_04 = a1;
	m_08 = a2;
	m_0C = a3;
	m_18 = a4;
}
// ??1Rva003598D3@@UAE@XZ present-unmatched
Rva003598D3::~Rva003598D3() {}
