// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /Ireference/shims/bfmeterraintracks /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// Size-optimised (/O1) emission of the TerrainTracksRenderObjClass::edgeInfo constructor.
//
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/heightmap.h"
#include "Common/PerfTimer.h"
#include "common/GlobalData.h"
#include "common/Debug.h"
#include "texture.h"
#include "colmath.h"
#include "coltest.h"
#include "rinfo.h"
#include "camera.h"
#include "assetmgr.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/Scene.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#ifdef _INTERNAL
#endif
#define BRIDGE_OFFSET_FACTOR	0.25f	//amount to raise tracks above bridges.

// edgeInfo is a protected nested type, so the anchor is a static member of a
// derived helper that is never instantiated.
struct BfmeTrackEdgeInfoAnchor : public TerrainTracksRenderObjClass
{
	static void anchor(edgeInfo *e);
};
#pragma inline_depth(0)
// ?anchor@BfmeTrackEdgeInfoAnchor@@ absent-from-retail
void BfmeTrackEdgeInfoAnchor::anchor(edgeInfo *e)
{
	e->edgeInfo::edgeInfo();
}
#pragma inline_depth()
#include "../../../Include/W3DDevice/GameClient/Rva00083CB2.h"
// Reset provider (00083CB2) lives in W3DTerrainTracksBind.cpp.
struct Rva00083CE9Node : public Rva00083CB2
{
public:
	Rva00083CE9Node *m_1320;
	Rva00083CE9Node *m_1324;
};
class Rva00083E87Ref
{
public:
	virtual void rva00083E87Free();
	int m_refs;
	char _pad08[0x1320 - 8];
	Rva00083E87Ref *m_1320;
};

#include "../../../Include/W3DDevice/GameClient/Rva00083CE9Host.h"
// Release provider (00083CE9) lives in W3DTerrainTracksBind.cpp.
// ?Reset@Rva00083CE9Host@@QAEXXZ retail 0x00084002 34B drain m_10 list
// via releaseTrack. Evidence: chain calls 0x00083CE9; caller at 0x00091CE6.
// ?rva00083E87@Rva00083CE9Host@@QAEXXZ @0x00083E87 136B: unlink-walk m_10 calling
// releaseTrack on flag-zero nodes, drain m_14 releasing each ref, then release
// the three ref slots at +0, +4 and +8.
void Rva00083CE9Host::rva00083E87()
{
	Rva00083CE9Node *node = m_10;
	while (node != 0)
	{
		Rva00083CE9Node *next = node->m_1320;
		if (node->m_1311 == 0)
		{
			releaseTrack(node);
		}
		node = next;
	}
	while (m_14 != 0)
	{
		Rva00083E87Ref *cur = reinterpret_cast<Rva00083E87Ref *>(m_14);
		Rva00083E87Ref *next = cur->m_1320;
		if (m_14 != 0)
		{
			if (--cur->m_refs == 0)
			{
				cur->rva00083E87Free();
			}
			m_14 = 0;
		}
		m_14 = reinterpret_cast<Rva00083CE9Node *>(next);
	}
	Rva00083E87Ref *m_04Ref = m_04;
	if (m_04Ref != 0)
	{
		if (--m_04Ref->m_refs == 0)
		{
			m_04Ref->rva00083E87Free();
		}
		m_04 = 0;
	}
	Rva00083E87Ref *m_08Ref = m_08;
	if (m_08Ref != 0)
	{
		if (--m_08Ref->m_refs == 0)
		{
			m_08Ref->rva00083E87Free();
		}
		m_08 = 0;
	}
	Rva00083E87Ref *m_00Ref = m_00;
	if (m_00Ref != 0)
	{
		if (--m_00Ref->m_refs == 0)
		{
			m_00Ref->rva00083E87Free();
		}
		m_00 = 0;
	}
}

void Rva00083CE9Host::Reset()
{
	Rva00083CE9Node *cur = m_10;
	while (cur != 0)
	{
		Rva00083CE9Node *next = cur->m_1320;
		releaseTrack(cur);
		cur = next;
	}
}
// ?Rva00083CD7Clear@@YGXPAVRva00083CB2@@@Z retail 0x00083CD7 18B clear
// m_38 and m_1311 of the edge info. Evidence: gap between 0x00083CB2 and
// 0x00083CE9; caller at 0x000C7A2C.
class Rva00083CD7Owner
{
public:
	void rva00083CD7(Rva00083CB2 *p);
};

void Rva00083CD7Owner::rva00083CD7(Rva00083CB2 *p)
{
	p->m_38 = 0;
	p->m_1311 = 0;
}
class Rva00083E5CRef
{
public:
	virtual void ReleaseRef();
	int m_ref;
};
class Rva00083E5C
{
public:
	void rva00083E5C();
private:
	Rva00083E5CRef *m_0;
	Rva00083E5CRef *m_4;
};
// ?rva00083E5C@Rva00083E5C@@QAEXXZ retail 0x00083E5C 43B release two
// refcounted slots at +0 and +4 via virtual slot0 then null them.
// Evidence: unlock lane; callers at 0x0006688B 0x0007E161 0x0008405F.
void Rva00083E5C::rva00083E5C()
{
	Rva00083E5CRef *a = m_4;
	if (a != 0)
	{
		if (--a->m_ref == 0)
			a->ReleaseRef();
		m_4 = 0;
	}
	Rva00083E5CRef *b = m_0;
	if (b != 0)
	{
		if (--b->m_ref == 0)
			b->ReleaseRef();
		m_0 = 0;
	}
}

// ??1Rva00084CEF@@QAE@XZ @0x00084CEF 18B, the pinned destructor of the same
// track-system object (callers 0x00091AB2 and 0x0009203A, in the terrain
// visual's init and destructor): Zero Hour's ~TerrainTracksRenderObjClassSystem
// shape, the full release above (0x00083E87) followed by clearing the +0x08
// and +0x18 pointers. The pin keeps the address-derived class name.
class Rva00084CEF
{
public:
	~Rva00084CEF();
private:
	char _pad00[8];
	void *m_08;
	char _pad0C[0x18 - 0x0C];
	void *m_18;
};

Rva00084CEF::~Rva00084CEF()
{
	reinterpret_cast<Rva00083CE9Host *>(this)->rva00083E87();
	m_08 = 0;
	m_18 = 0;
}
