// cl: /Ireference/shims/bfmeterraintracks /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?freeTerrainTracksResources@TerrainTracksRenderObjClass@@QAEHXZ 0x0008E187 107B
// BFME2 byte-exact reconstruction. Donor Zero Hour W3DTerrainTracks.cpp freeTerrainTracksResources
// (single REF_PTR_RELEASE of m_stageZeroTexture plus scalar resets) and BFME1 same; retail BFME2
// holds four DX8 resources instead (creator 0x0008E1F2 builds index buffer at +0xD4 via
// DX8IndexBuffer ctor, material at +0xDC via VertexMaterial Get_Preset, two vertex buffers at
// +0xE0/+0xE4 via BfmeDynamicNativeVB, shader dword 0x1198B7 at +0xD8, count 0x14 at +0xC4) and
// Render 0x0008E7A4 (vtable slot 12 of 0x007C7850, the dtor's vtable) consumes them via
// Set_Index_Buffer/Set_Vertex_Buffer with the same displacements. Callers: 0x0008E20B in the
// creator and 0x0008E50E in ??1TerrainTracksRenderObjClass 0x0008E4EC. Returns 0, no scalar resets.
class Rva0008E187RefCount
{
public:
	virtual void Delete_This() = 0;
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
	int m_refs;
};
#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); x = 0; } }
class TerrainTracksRenderObjClass
{
public:
	int freeTerrainTracksResources();
private:
	char _pad[0xD4];
	Rva0008E187RefCount *m_indexBuffer;
	char _padD8[4];
	Rva0008E187RefCount *m_vertexMaterial;
	Rva0008E187RefCount *m_vertexBuffer;
	Rva0008E187RefCount *m_vertexBuffer2;
};
int TerrainTracksRenderObjClass::freeTerrainTracksResources()
{
	REF_PTR_RELEASE(m_indexBuffer);
	REF_PTR_RELEASE(m_vertexBuffer2);
	REF_PTR_RELEASE(m_vertexBuffer);
	REF_PTR_RELEASE(m_vertexMaterial);
	return 0;
}
