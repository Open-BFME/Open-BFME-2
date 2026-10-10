// cl: /DNDEBUG /MD /EHsc
//
// ?releaseTrack@WaterTracksRenderSystem (retail 0x000FE001, 100 bytes): intrusive list move
// that unlinks other (FeNode via +0xb0 next and +0xb4 prev) from its old list
// and prepends it to this container's head at +0x14 (tail at +0x10 when other
// was head). No calls; pure moves. Evidence: 4 callers pass node as stack arg
// with ecx=this (e.g. 0x000FE19B pushes eax after clearing [eax+0x3c]); callee
//-free body unblocks 0x000FE188/0x000FE1AC/0x000FE8FC/0x000FF448.
//
// ?rva000FE188@WaterTracksRenderSystem (retail 0x000FE188, 36 bytes): drains the list
// from +0x10, clearing each node's +0x3C flag and moving it with
// releaseTrack, then clears +0x10. Callers 0x000FF606, 0x000FFEF7 and a tail
// jump at 0x00082B81. Retail keeps this in ecx across the releaseTrack call,
// which cl only does when that callee was compiled earlier in the same TU.

// Resource recovery follows BFME 1 575ba2b04 WaterTracksRenderSystemReAcquireResources.cpp
// and ZH W3DWaterTracks.cpp. Target 0x000FE065 independently proves the
// resource offsets, 24/32-byte allocations, 12-byte lock and constructor calls.
// Resource declarations below are borrowed ABI prefixes, not full class contracts.
#define WATER_VB_PAGES 1000

typedef unsigned short UnsignedShort;

// BFME's resource classes have the same witnessed refcount/vtable prefix as
// the neighboring TerrainTracks converter, but their full headers introduce
// constructor overloads that are not part of this retail call shape.
class RefCountedResource
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	int m_refCount;
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *m_indexBuffer;
		UnsignedShort *m_indices;
        unsigned char m_deviceGuardStorage[4];

	public:
		WriteLockClass(IndexBufferClass *indexBuffer, int flags = 0);
		~WriteLockClass(void);

		UnsignedShort *Get_Index_Array(void)
		{
			return m_indices;
		}
	};
};

class DX8IndexBufferClass : public RefCountedResource
{
public:
	typedef IndexBufferClass::WriteLockClass WriteLockClass;

	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8IndexBufferClass(unsigned indexCount, UsageType usage = USAGE_DEFAULT);

private:
	unsigned char m_bfmeTail[0x10];
};

class BfmeDynamicNativeVB : public RefCountedResource
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	BfmeDynamicNativeVB(unsigned fvf, UnsignedShort vertexCount,
        unsigned usage, unsigned vertexSize);

private:
	unsigned char m_bfmeTail[0x18];
};

enum
{
	DX8_FVF_XYZDUV1 = 0x142
};

struct FeNode
{
	unsigned char m_pad0[0x3c];
	unsigned char m_flag3c;
	unsigned char m_pad1[0xb0 - 0x3d];
	FeNode *m_next;
	FeNode *m_prev;
};

class WaterTracksRenderSystem
{
public:
	void releaseTrack(FeNode *other);
	void rva000FE8FC(FeNode *other);
	void rva000FE188();
	void ReAcquireResources();

private:
	BfmeDynamicNativeVB *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	unsigned char m_pad08[8];
	FeNode *m_tail10;
	FeNode *m_head14;
	int m_stripSizeX;
	int m_stripSizeY;
	int m_batchStart;
};

void WaterTracksRenderSystem::releaseTrack(FeNode *other)
{
	if (other == 0)
		return;
	FeNode *next = other->m_next;
	if (next != 0)
		next->m_prev = other->m_prev;
	FeNode **prevLink = &other->m_prev;
	FeNode *prev = *prevLink;
	if (prev != 0)
		prev->m_next = other->m_next;
	else
		m_tail10 = other->m_next;
	*prevLink = 0;
	other->m_next = m_head14;
	if (m_head14 != 0)
		m_head14->m_prev = other;
	m_head14 = other;
}

void WaterTracksRenderSystem::rva000FE8FC(FeNode *other)
{
	other->m_flag3c = 0;
	releaseTrack(other);
}

void WaterTracksRenderSystem::rva000FE188()
{
	FeNode *node = m_tail10;
	while (node != 0)
	{
		FeNode *next = node->m_next;
		node->m_flag3c = 0;
		releaseTrack(node);
		node = next;
	}
	m_tail10 = 0;
}

// ?ReAcquireResources@WaterTracksRenderSystem@@QAEXXZ
void WaterTracksRenderSystem::ReAcquireResources(void)
{
	int i, j, k;

	if (m_indexBuffer)
	{
		m_indexBuffer->Release_Ref();
		*(DX8IndexBufferClass * volatile *)&m_indexBuffer = 0;
	}
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release_Ref();
		*(BfmeDynamicNativeVB * volatile *)&m_vertexBuffer = 0;
	}

	int idxCount = (m_stripSizeY - 1) * (m_stripSizeX * 2 + 2) - 2;

	m_indexBuffer = new DX8IndexBufferClass(idxCount);

	{
		DX8IndexBufferClass::WriteLockClass lockIdxBuffer((IndexBufferClass *)m_indexBuffer);
		unsigned short *ib = lockIdxBuffer.Get_Index_Array();

		for (i = 0, j = 0, k = 0; i < idxCount; j++)
		{
			for (; k < (m_stripSizeX * (j + 1)); k++, i += 2)
			{
				ib[i] = (unsigned short)k + m_stripSizeX;
				ib[i + 1] = (unsigned short)k;
			}
			if (i < idxCount)
			{
				ib[i] = k - 1;
				ib[i + 1] = k + m_stripSizeX;
				i += 2;
			}
		}
	}

	m_vertexBuffer = new BfmeDynamicNativeVB(
		DX8_FVF_XYZDUV1,
		(UnsignedShort)(m_stripSizeX * m_stripSizeY * WATER_VB_PAGES),
		BfmeDynamicNativeVB::USAGE_DYNAMIC, 0);
	m_batchStart = 0;
}

typedef char AssertIndexSize[(sizeof(DX8IndexBufferClass)==24)?1:-1];
typedef char AssertVertexSize[(sizeof(BfmeDynamicNativeVB)==32)?1:-1];
