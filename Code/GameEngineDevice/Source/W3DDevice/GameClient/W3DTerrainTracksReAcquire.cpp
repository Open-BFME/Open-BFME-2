// cl: /O1 /G7 /arch:SSE /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmeterraintracks /Ireference/shims/indexbuffercount /Ireference/shims/vertexbufferlock /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// TerrainTracksRenderObjClassSystem::ReAcquireResources (retail 0x00083D54,
// 264 bytes), split from W3DTerrainTracks.cpp like W3DRoadBufferLoadLit4Pt.cpp:
// it needs BFME's 12-byte DX8 buffer write locks (reference/shims/
// indexbuffercount, vertexbufferlock), and those headers change how the main
// unit's bounding-volume copies compile.  Zero Hour body; BFME deltas are the
// GlobalData offset of the track count, the system layout (shim) and the
// release idiom that clears each pointer inside its test.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it

#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "common/GlobalData.h"
#include "WW3D2/DX8Wrapper.h"

// BFME 2's GlobalData keeps the terrain track count at +0x10C
// (ReAcquireResources 0x00083D54).
struct TerrainTracksGlobalDataView
{
	char m_pad[0x10C];
	Int m_maxTerrainTracks;
};

void TerrainTracksRenderObjClassSystem::ReAcquireResources(void)
{
	Int i;
	const Int numModules=((const TerrainTracksGlobalDataView *)TheGlobalData)->m_maxTerrainTracks;

	// just for paranoia's sake.  BFME 2 clears each pointer inside the test.
	if (m_indexBuffer) {
		m_indexBuffer->Release_Ref();
		m_indexBuffer = NULL;
	}
	if (m_vertexBuffer) {
		m_vertexBuffer->Release_Ref();
		m_vertexBuffer = NULL;
	}

	//Create static index buffers.  These will index the vertex buffers holding the track segments
	m_indexBuffer=NEW_REF(DX8IndexBufferClass,((m_maxTankTrackEdges-1)*6));

	// Fill up the IB
	{
		DX8IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexBuffer);
		UnsignedShort *ib=lockIdxBuffer.Get_Index_Array();

		for (i=0; i<(m_maxTankTrackEdges-1); i++)
		{
			ib[3]=ib[0]=i*2;
			ib[1]=i*2+1;
			ib[4]=ib[2]=(i+1)*2+1;
			ib[5]=(i+1)*2;
			ib+=6;	//skip the 6 indices we just filled
		}
	}

	m_vertexBuffer=NEW_REF(DX8VertexBufferClass,(DX8_FVF_XYZDUV1,numModules*m_maxTankTrackEdges*2,DX8VertexBufferClass::USAGE_DYNAMIC));
}
