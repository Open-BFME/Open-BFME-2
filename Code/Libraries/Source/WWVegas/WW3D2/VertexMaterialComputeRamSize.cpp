// cl: /Ireference/shims/bfmemapper /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?rva0013D250@VertexMaterialClass@@QBEHXZ @ 0x0013D250 (89B).
// Gap between Get_Preset and GridClassic ctor in vertmaterial.cpp: const size
// calc returning 0x6C or 0xB0 from +0x08 then +0x20 per present Mapper[8] at
// +0x20...+0x3C. Called by MeshMatDesc::Compute_Ram_Size at 0x0015CB9A and
// 0x0015CBEC plus 0x0016EF0A; layout is the 8-mapper array per the ctor which
// nulls Mapper[i]. Honest address name on the real VertexMaterialClass;
// method computes RAM size like sibling Compute_Ram_Size bodies.

class TextureMapperClass;

class VertexMaterialClass
{
public:
	int rva0013D250() const;

private:
	char m_pad00[8];
	int m_08;
	char m_pad0C[0x20 - 0x0C];
	TextureMapperClass *m_mapper[8];
};

int VertexMaterialClass::rva0013D250() const
{
	int size = 0x6C;
	if (m_08 != 0)
		size = 0xB0;
	if (m_mapper[0])
		size += 0x20;
	if (m_mapper[1])
		size += 0x20;
	if (m_mapper[2])
		size += 0x20;
	if (m_mapper[3])
		size += 0x20;
	if (m_mapper[4])
		size += 0x20;
	if (m_mapper[5])
		size += 0x20;
	if (m_mapper[6])
		size += 0x20;
	if (m_mapper[7])
		size += 0x20;
	return size;
}
