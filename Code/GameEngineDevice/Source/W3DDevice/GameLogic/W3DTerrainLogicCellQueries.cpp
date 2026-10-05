// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// W3DTerrainLogic per-cell terrain queries that BFME added after isCliffCell.
//
// Target evidence: W3DTerrainLogic's vftable holds five adjacent (Real x, Real y)
// slots at 0x007C58E0..0x007C58F0, right after isUnderwater. The first is
// isCliffCell (0x00062D94, rowed in W3DTerrainLogic.cpp: ZH puts isCliffCell
// directly after isUnderwater); the other four are these bodies. Each is the
// same 31-byte forwarder, `return TheTerrainRenderObject->query(x, y);` with
// ecx reloaded from TheTerrainRenderObject (0x00DE1EAC, the global newMap and
// isClearLineOfSight read) and ret 8.
//
// Each callee is a 115-byte BaseHeightMapRenderObjClass body that null-checks
// m_map (+0x37C0), converts x/y to a border-adjusted clamped cell and asks the
// WorldHeightMap one per-cell question, exactly like isCliffCell at 0x000671B2.
// The donor names of the four BFME queries are unknown, so they are
// address-derived; return widths follow each callee's own return register use.
class BaseHeightMapRenderObjClass
{
public:
	unsigned char rva0006B187(float x, float y);
	unsigned char rva00067225(float x, float y);
	bool rva00067298(float x, float y);
	unsigned char rva0006730B(float x, float y);
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DTerrainLogic
{
public:
	virtual unsigned char rva00062DB3(float x, float y) const;
	virtual unsigned char rva00062DD2(float x, float y) const;
	virtual bool rva00062DF1(float x, float y) const;
	virtual unsigned char rva00062E10(float x, float y) const;
};

// vftable 0x007C58E4, callee 0x0006B187
unsigned char W3DTerrainLogic::rva00062DB3(float x, float y) const
{
	return TheTerrainRenderObject->rva0006B187(x, y);
}

// vftable 0x007C58E8, callee 0x00067225
unsigned char W3DTerrainLogic::rva00062DD2(float x, float y) const
{
	return TheTerrainRenderObject->rva00067225(x, y);
}

// vftable 0x007C58EC, callee 0x00067298
bool W3DTerrainLogic::rva00062DF1(float x, float y) const
{
	return TheTerrainRenderObject->rva00067298(x, y);
}

// vftable 0x007C58F0, callee 0x0006730B
unsigned char W3DTerrainLogic::rva00062E10(float x, float y) const
{
	return TheTerrainRenderObject->rva0006730B(x, y);
}
