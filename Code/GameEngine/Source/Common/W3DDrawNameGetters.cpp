// W3D draw/buffer literal name getters: six-byte const members with one shape
// (mov eax,<offset string literal> / ret). Same shape and verbatim
// BFME_LITERAL_NAME_GETTER macro as
// Code/GameEngine/Source/Common/SubsystemNameGetters.cpp (BFME1
// LiteralNameGetters_01 port); kept as its own unit to keep concurrent
// contributors conflict-free. Each body returns a pointer to a
// NUL-terminated class-name string in .rdata with exactly one vtable (body-VA)
// reference behind a C3 predecessor; verify_string_refs re-reads the string.
// No // cl: line (defaults match the frameless 6-byte shape).

#define BFME_LITERAL_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	public: \
		const char *name() const; \
	}; \
	const char *NAME::name() const \
	{ \
		return TEXT; \
	}

BFME_LITERAL_NAME_GETTER(W3DDefaultDraw, "W3DDefaultDraw")
BFME_LITERAL_NAME_GETTER(Rva000C1246Named, "W3DScriptedModelDraw")
BFME_LITERAL_NAME_GETTER(Rva000C9C11Named, "W3DLaserDraw")
BFME_LITERAL_NAME_GETTER(Rva000CA113Named, "W3DQuadrupedDraw")
class W3DRopeDraw
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *W3DRopeDraw::GetSnapshotName() const
{
	return "W3DRopeDraw";
}
BFME_LITERAL_NAME_GETTER(Rva000CAEC0Named, "W3DSupplyDraw")
BFME_LITERAL_NAME_GETTER(W3DTruckDraw, "W3DTruckDraw")
BFME_LITERAL_NAME_GETTER(Rva000CEA33Named, "W3DTankDraw")
BFME_LITERAL_NAME_GETTER(W3DStreakDraw, "W3DStreakDraw")
BFME_LITERAL_NAME_GETTER(W3DSailModelDraw, "W3DSailModelDraw")
BFME_LITERAL_NAME_GETTER(Rva000E6B93Named, "W3DVegetationBufferBase")
BFME_LITERAL_NAME_GETTER(Rva000EDB39Named, "W3DTreeBuffer")
// Native W3DPropBuffer ctor EF008 and dtor EEEF4 install 7CEECC, whose slot 2
// is EEFE6: the canonical Snapshot GetSnapshotName slot.
class W3DPropBuffer
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *W3DPropBuffer::GetSnapshotName() const
{
	return "W3DPropBuffer";
}
BFME_LITERAL_NAME_GETTER(Rva000CEB69Named, "W3DTreeDraw")
BFME_LITERAL_NAME_GETTER(W3DBuffDraw, "W3DBuffDraw")
class W3DPropDraw
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *W3DPropDraw::GetSnapshotName() const
{
	return "W3DPropDraw";
}
BFME_LITERAL_NAME_GETTER(W3DFloorDraw, "W3DFloorDraw")
BFME_LITERAL_NAME_GETTER(W3DLightDraw, "W3DLightDraw")
BFME_LITERAL_NAME_GETTER(Rva000D0B63Named, "W3DBoatWakeModelDraw")
BFME_LITERAL_NAME_GETTER(W3DProjectileStreamDraw, "W3DProjectileStreamDraw")
BFME_LITERAL_NAME_GETTER(W3DTornadoDraw, "W3DTornadoDraw")
BFME_LITERAL_NAME_GETTER(Rva000D1BA0Named, "TBuff")
class W3DTerrainLogic
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *W3DTerrainLogic::GetSnapshotName() const
{
	return "W3DTerrainLogic";
}
