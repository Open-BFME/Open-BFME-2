// ??0Rva00126350@@QAE@ABV0@@Z
// cl: /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// EH copy ctor: default-init the members (m_tex 0, m_4 global 0x009B624C, m_8 0.0f,
// five floats 1.0f from 0x007BB8D8, byte 0) then call the rowed assign 0x00126350.
// Evidence: callee 0x00126350 row assign; caller 0x00168587 copy ctor at +0xE4;
// globals 0x009B624C preset 0x007BB8D8 1.0f; sibling Rva00126350Assign uses these flags.
//
// The 1.0f constant is loaded ONCE (movss xmm0,[0x007BB8D8]) and all five float
// stores reuse it, so the five must be written against one named local rather
// than re-reading the global.
//
// Retail splits those five stores around the operator= call setup: it stores
// m_c/m_10/m_14 (+0xc/+0x10/+0x14) first, THEN emits the two-instruction SEH
// frame save (mov ecx,esi / mov [ebp-0x4],eax), THEN stores m_18/m_1c
// (+0x18/+0x1c), with m_20 last. Writing all five as plain consecutive member
// stores gets the same three-above split but then also sinks m_20 above the EH
// save. Routing the first THREE through a float* alias (f[0..2] from &m_c) and
// writing m_18/m_1c/m_20 directly is what reproduces retail: the aliased run and
// the direct stores are scheduled as separate groups around the EH pair. The
// alias is a codegen device, not the original source's spelling.
class TextureClass;
template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	~RefCountPtr();
	const RefCountPtr<T> &operator=(const RefCountPtr<T> &other);
private:
	T *m_ptr;
};
class ShaderClass
{
public:
	static ShaderClass _PresetAdditiveSpriteShader;	// shader.cpp; its first word
};
extern float g_007BB8D8;
class Rva00126350
{
public:
	Rva00126350(const Rva00126350 &other);
	Rva00126350 &operator=(const Rva00126350 &other);
private:
	RefCountPtr<TextureClass> m_tex;
	int m_4;
	float m_8;
	float m_c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	unsigned char m_20;
};
Rva00126350::Rva00126350(const Rva00126350 &other)
	: m_tex()
	, m_4(*(int *)&ShaderClass::_PresetAdditiveSpriteShader)
	, m_8(0.0f)
{
	float *f = &m_c;
	const float one = g_007BB8D8;
	f[0] = one;
	f[1] = one;
	f[2] = one;
	m_18 = one;
	m_1c = one;
	m_20 = 0;
	*this = other;
}

// Retail global spelled differently by the unit that defines it (same
// address in reverse/data_ledger.csv); bind this unit's name to it.
#pragma comment(linker, "/alternatename:?g_007BB8D8@@3MA=?g_Va00BBB8D8@@3MA")
