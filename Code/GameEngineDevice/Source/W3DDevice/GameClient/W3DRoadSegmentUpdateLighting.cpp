// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc /O1 /arch:SSE /Ireference/shims/bfme2renderobj /Ireference/shims/w3droadbuffer /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// RoadSegment::updateSegLighting (retail 0x000D4613, 187 B) in its own TU, like the
// sibling W3DRoadBufferLoadRoadSegment.cpp. RoadSegment is declared locally with the
// layout that sibling uses (count +0x58, vb +0x5c), so this TU does not include the
// shared road header.
//
// Basis. The loop shape and the 0x24-byte lit vertex (x, y at +0/+4, diffuse at +0x18)
// come from the sibling layout and the retail-measured loadLit4PtSection notes. Target
// facts: the diffuse query is the three-argument call at 0x0006B4CC with constant 1 as
// third argument (one of the opaque callees named in W3DRoadBufferLoadLit4Pt.cpp), and
// the border offset is read through the terrain object's +0x37C0 map pointer at +0x10.
// Inference, not target-proven: the class name of the callee and the identity of the
// terrain object's map member are neutral RVA names only, pending a real header.
#define Matrix4x4 Matrix4  // BFME renamed it

#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"

// Opaque one-method class for the unclaimed callee at 0x0006B4CC (see symbols.csv).
class Rva0006B4CC { public: Int call(Int x, Int y, Int z); };

class RoadSegment
{
public:
	char m_pad[0x50];
	Int m_uniqueID;
	unsigned char m_visible;
	char m_pad55[3];
	Int m_numVertex;
	void *m_vb;
	Int m_numIndex;

	void updateSegLighting(void);
};

void RoadSegment::updateSegLighting(void)
{
	if (TheTerrainRenderObject == NULL) return;
	if (*(void **)((char *)TheTerrainRenderObject + 0x37C0) == NULL) return;
	for (Int i = 0; i < m_numVertex; i++) {
		Real vx = *(Real *)((char *)m_vb + i * 0x24);
		Real vy = *(Real *)((char *)m_vb + i * 0x24 + 4);
		Int x = (Int)(vx / MAP_XY_FACTOR + 0.5) + *(Int *)(*(char **)((char *)TheTerrainRenderObject + 0x37C0) + 0x10);
		Int y = (Int)(vy / MAP_XY_FACTOR + 0.5) + *(Int *)(*(char **)((char *)TheTerrainRenderObject + 0x37C0) + 0x10);
		Int diffuse = (255<<24)|((Rva0006B4CC *)TheTerrainRenderObject)->call(x, y, 1);
		*(Int *)(((char *)m_vb) + i * 0x24 + 0x18) = diffuse;
	}
}
