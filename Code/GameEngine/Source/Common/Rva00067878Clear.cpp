// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00067878@BaseHeightMapRenderObjClass@@QAEXXZ, retail 0x00067878, 67 bytes.
// Unlock lane: releases ref-counted holders at +0xCC/+0xD0 (dec ref at +4,
// virtual slot0 if zero, then and-zero) then tail-jumps to rowed
// ?clear@BfmeResetTextureRef@@QAEXXZ at 0x0004D75B for +0xD4.
// Evidence: callers at 0x00069340/0x0006B416 (both unclaimed), rowed callee,
// and-zero plus tail-jmp shape.

struct BfmeResetResource;

struct RefObj00067878
{
	virtual void v0();
	int m_ref;
};

#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h"

// The header types the +0xCC/+0xD0 scorch buffers by class only; this body
// releases them through their reference count at +4 and slot 0.
static __forceinline RefObj00067878 *&scorchHolder(VertexBufferClass *&field)
{
	return reinterpret_cast<RefObj00067878 *&>(field);
}

static __forceinline RefObj00067878 *&scorchHolder(IndexBufferClass *&field)
{
	return reinterpret_cast<RefObj00067878 *&>(field);
}

static __forceinline BfmeResetTextureRef &scorchTexture(RefCountPtr<TextureClass> &field)
{
	return reinterpret_cast<BfmeResetTextureRef &>(field);
}

void BaseHeightMapRenderObjClass::rva00067878()
{
	RefObj00067878 *a = scorchHolder(m_vertexScorch);
	if (a)
	{
		if (--a->m_ref == 0)
			a->v0();
		scorchHolder(m_vertexScorch) = 0;
	}
	RefObj00067878 *b = scorchHolder(m_indexScorch);
	if (b)
	{
		if (--b->m_ref == 0)
			b->v0();
		scorchHolder(m_indexScorch) = 0;
	}
	return scorchTexture(field00D4).clear();
}
