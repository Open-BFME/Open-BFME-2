// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ??0Rva002D6C02@@QAE@XZ @0x002D6C02 26B via baseConstruct pattern from Rva0026201C; callees rowed 0x001B4E63; caller 0x0023A30B; neighbours Anim2D cluster.

extern "C" const void *const vtbl_00C0331C[];  // ??_7Rva002D6C02@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C0331C=??_7Rva002D6C02@@6B@")

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class Rva002D6C02
{
	int m_pad00[3];
	int m_0C;
	int m_10;
public:
	Rva002D6C02();
};

Rva002D6C02::Rva002D6C02()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_0C = 0;
	m_10 = 0;
	*(void **)this = (void *)((unsigned int)vtbl_00C0331C);
}
