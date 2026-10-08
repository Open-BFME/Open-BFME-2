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
#pragma optimize("s", on)

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
class Rva00083CB2
{
public:
	void rva00083CB2();
	friend void __stdcall Rva00083CD7Clear(Rva00083CB2 *p);
	friend class Rva00083CE9Host;
private:
	char _pad00[0x30];
	int m_30;
	int m_34;
	int m_38;
	char _pad3C[0x1308 - 0x3C];
	int m_1308;
	int m_130C;
	unsigned char m_1310;
	unsigned char m_1311;
	char _pad1312[0x131D - 0x1312];
	unsigned char m_131D;
};
// ?rva00083CB2@Rva00083CB2@@QAEXXZ retail 0x00083CB2 37B reset of scattered
// fields to 0 with +0x131D set to 1. Evidence: unlock lane; callers at
// 0x00083D4C 0x000840B1 0x00084213 unblock 0x00083CE9 0x00084206.
void Rva00083CB2::rva00083CB2()
{
	m_1310 = 0;
	m_131D = 1;
	m_130C = 0;
	m_1308 = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
}
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

class Rva00083CE9Host
{
public:
	void rva00083CE9(Rva00083CE9Node *p);
	void rva00084002();
	void rva00083E87();
private:
	Rva00083E87Ref *m_00;
	Rva00083E87Ref *m_04;
	Rva00083E87Ref *m_08;
	char _pad0C[4];
	Rva00083CE9Node *m_10;
	Rva00083CE9Node *m_14;
};
// ?rva00083CE9@Rva00083CE9Host@@QAEXPAURva00083CE9Node@@@Z retail 0x00083CE9
// 107B unlink node from old list then push at head of this list and reset it.
// Evidence: chain calls 0x00083CB2; callers at 0x00083EA6 0x00083FDD 0x00084016.
void Rva00083CE9Host::rva00083CE9(Rva00083CE9Node *p)
{
	if (p == 0)
		return;
	if (p->m_1320 != 0)
		p->m_1320->m_1324 = p->m_1324;
	Rva00083CE9Node *next = p->m_1324;
	if (next != 0)
		next->m_1320 = p->m_1320;
	else
		m_10 = p->m_1320;
	p->m_1324 = 0;
	p->m_1320 = m_14;
	if (m_14 != 0)
		m_14->m_1324 = p;
	m_14 = p;
	p->rva00083CB2();
}
// ?rva00084002@Rva00083CE9Host@@QAEXXZ retail 0x00084002 34B drain m_10 list
// via rva00083CE9. Evidence: chain calls 0x00083CE9; caller at 0x00091CE6.
// ?rva00083E87@Rva00083CE9Host@@QAEXXZ @0x00083E87 136B: unlink-walk m_10 calling
// rva00083CE9 on flag-zero nodes, drain m_14 releasing each ref, then release
// the three ref slots at +0, +4 and +8.
void Rva00083CE9Host::rva00083E87()
{
	Rva00083CE9Node *node = m_10;
	while (node != 0)
	{
		Rva00083CE9Node *next = node->m_1320;
		if (node->m_1311 == 0)
		{
			rva00083CE9(node);
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

void Rva00083CE9Host::rva00084002()
{
	Rva00083CE9Node *cur = m_10;
	while (cur != 0)
	{
		Rva00083CE9Node *next = cur->m_1320;
		rva00083CE9(cur);
		cur = next;
	}
}
// ?Rva00083CD7Clear@@YGXPAVRva00083CB2@@@Z retail 0x00083CD7 18B clear
// m_38 and m_1311 of the edge info. Evidence: gap between 0x00083CB2 and
// 0x00083CE9; caller at 0x000C7A2C.
void __stdcall Rva00083CD7Clear(Rva00083CB2 *p)
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
