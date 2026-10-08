// ?rva000CF20C@W3DFloorDraw@@QAEXPAVAsciiString@@@Z
// partial score=0.9 date=2026-10-08
// ?rva000CF20C@W3DFloorDraw@@QAEXPAVAsciiString@@@Z
// partial score=0.9 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva000CF2CF@W3DFloorDraw@@QAEXXZ @0x000CF2CF 161B
// Address-derived method on W3DFloorDraw. The target boundary is Ghidra's
// 0x000CF2CF..0x000CF370 interval, checked against the retail prolog and ret.
// Target accesses moduleData at this+4, drawable at this+8 and flags at
// this+0x15..0x17; the rowed constructor, xfer, destructor and flag setters
// corroborate the W3DFloorDraw view. moduleData+8 is the AsciiString passed to
// the matched terrain forwarder. Callee ABI pins are derived from the direct
// calls and their target epilogues, not from the address-based names.
#include "ascii_string.h"

struct FloorDrawTerrainPair
{
	int m_key;
	AsciiString m_value;
};

struct FloorDrawModuleDataView
{
	char m_pad0[8];
	AsciiString m_name;
	char m_pad0C[4];
	FloorDrawTerrainPair *m_begin;
	FloorDrawTerrainPair *m_end;
	char m_pad18[4];
	bool m_flag1C;
	bool m_flag1D;
};

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class BaseHeightMapRenderObjClass
{
private:
	char m_pad0[0x3860];
	void *m_3860;

public:
	void rva0006B76C(const Rva0055A88BDwordField *id, AsciiString name);
	void rva00068395(int id, AsciiString *moduleName, AsciiString *terrainName,
		bool flag1D, bool flag1C);
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DFloorDraw
{
private:
	void *m_vtable;
	FloorDrawModuleDataView *m_moduleData;
	Rva0055A88BDwordField *m_drawable;
	char m_pad0C[8];
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	bool m_flag17;

public:
	void rva000CF20C(AsciiString *out);
	void rva000CF2CF();
};

extern void *g_00DFE758;

// ?rva000CF20C@W3DFloorDraw@@QAEXPAVAsciiString@@@Z @0x000CF20C
void W3DFloorDraw::rva000CF20C(AsciiString *out)
{
	*out = "";
	FloorDrawModuleDataView *moduleData = m_moduleData;
	int count = ((int)moduleData->m_end - (int)moduleData->m_begin) >> 3;
	if (count == 0)
		return;
	FloorDrawTerrainPair *pair = moduleData->m_begin;
	FloorDrawTerrainPair *end = moduleData->m_end;
	int key = *(int *)((char *)g_00DFE758 + 0x138);
	do
	{
		if (pair->m_key == key)
		{
			*out = pair->m_value;
			return;
		}
		++pair;
	} while (pair != end);
}

void W3DFloorDraw::rva000CF2CF()
{
	FloorDrawModuleDataView *moduleData = m_moduleData;
	if (moduleData != 0)
	{
		Rva0055A88BDwordField *drawable = m_drawable;
		if (drawable != 0)
		{
			TheTerrainRenderObject->rva0006B76C(drawable, moduleData->m_name);
			if (m_flag15 == 0 && m_flag16 == 0 && m_flag17 == 0)
			{
				AsciiString terrainName;
				rva000CF20C(&terrainName);
				TheTerrainRenderObject->rva00068395(drawable->get(),
					&moduleData->m_name, &terrainName,
					moduleData->m_flag1D, moduleData->m_flag1C);
			}
		}
	}
}
