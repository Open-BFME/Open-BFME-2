// cl: /DNDEBUG /MD /EHsc
// ?rva00115FF1@W3DBufferManager@@QAEXXZ @0x00115FF1 92B. Identity: W3DBufferManager release of DX8 VBs over 18 lists at +0x9000 then IBs at +0x263D0 via Release_Ref dec-call plus null.
// Evidence: callers 0xF09BF; neighbours 0x115F73/0x116113; same +0x9000/+0x263D0 layout as W3DBufferManager_Slots; LINK BONUS via 0xF0972.
#define MAX_VB_SIZES 512
#define MAX_NUMBER_SLOTS 4096
#define MAX_VERTEX_BUFFERS_CREATED 32
#define MAX_IB_SIZES 1024
#define MAX_INDEX_BUFFERS_CREATED 32

#define NULL 0

typedef int Int;

class DX8VertexBufferClass
{
public:
	virtual void Delete_This();
	int m_refs;
	char m_pad[24];
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

class DX8IndexBufferClass
{
public:
	virtual void Delete_This();
	int m_refs;
	char m_pad[16];
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

class W3DBufferManager
{
public:
	enum VBM_FVF_TYPES
	{
		VBM_FVF_XYZ,
		VBM_FVF_XYZD,
		VBM_FVF_XYZUV,
		VBM_FVF_XYZDUV,
		VBM_FVF_XYZUV2,
		VBM_FVF_XYZDUV2,
		VBM_FVF_XYZN,
		VBM_FVF_XYZND,
		VBM_FVF_XYZNUV,
		VBM_FVF_XYZNDUV,
		VBM_FVF_XYZNUV2,
		VBM_FVF_XYZNDUV2,
		VBM_FVF_XYZRHW,
		VBM_FVF_XYZRHWD,
		VBM_FVF_XYZRHWUV,
		VBM_FVF_XYZRHWDUV,
		VBM_FVF_XYZRHWUV2,
		VBM_FVF_XYZRHWDUV2,
		MAX_FVF
	};

	struct W3DRenderTask
	{
		W3DRenderTask *m_nextTask;
	};

	struct W3DVertexBuffer;
	struct W3DIndexBuffer;

	struct W3DVertexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DVertexBuffer *m_VB;
		W3DVertexBufferSlot *m_prevSameSize;
		W3DVertexBufferSlot *m_nextSameSize;
		W3DVertexBufferSlot *m_prevSameVB;
		W3DVertexBufferSlot *m_nextSameVB;
	};

	struct W3DVertexBuffer
	{
		VBM_FVF_TYPES m_format;
		W3DVertexBufferSlot *m_usedSlots;
		Int m_startFreeIndex;
		Int m_size;
		W3DVertexBuffer *m_nextVB;
		DX8VertexBufferClass *m_DX8VertexBuffer;
		W3DRenderTask *m_renderTaskList;
	};

	struct W3DIndexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DIndexBuffer *m_IB;
		W3DIndexBufferSlot *m_prevSameSize;
		W3DIndexBufferSlot *m_nextSameSize;
		W3DIndexBufferSlot *m_prevSameIB;
		W3DIndexBufferSlot *m_nextSameIB;
	};

	struct W3DIndexBuffer
	{
		W3DIndexBufferSlot *m_usedSlots;
		Int m_startFreeIndex;
		Int m_size;
		W3DIndexBuffer *m_nextIB;
		DX8IndexBufferClass *m_DX8IndexBuffer;
	};

	void rva00115FF1();

protected:
	W3DVertexBufferSlot *m_W3DVertexBufferSlots[MAX_FVF][MAX_VB_SIZES];
	W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF];
	W3DVertexBufferSlot m_W3DVertexBufferEmptySlots[MAX_NUMBER_SLOTS];
	Int m_numEmptySlotsAllocated;
	W3DVertexBuffer m_W3DEmptyVertexBuffers[MAX_VERTEX_BUFFERS_CREATED];
	Int m_numEmptyVertexBuffersAllocated;

	W3DIndexBufferSlot *m_W3DIndexBufferSlots[MAX_IB_SIZES];
	W3DIndexBuffer *m_W3DIndexBuffers;
	W3DIndexBufferSlot m_W3DIndexBufferEmptySlots[MAX_NUMBER_SLOTS];
	Int m_numEmptyIndexSlotsAllocated;
	W3DIndexBuffer m_W3DEmptyIndexBuffers[MAX_INDEX_BUFFERS_CREATED];
	Int m_numEmptyIndexBuffersAllocated;
};

void W3DBufferManager::rva00115FF1()
{
	for (Int i = 0; i < MAX_FVF; i++)
	{
		W3DVertexBuffer *vb = m_W3DVertexBuffers[i];
		while (vb)
		{
			if (vb->m_DX8VertexBuffer)
			{
				vb->m_DX8VertexBuffer->Release_Ref();
				vb->m_DX8VertexBuffer = 0;
			}
			vb = vb->m_nextVB;
		}
	}
	W3DIndexBuffer *ib = m_W3DIndexBuffers;
	while (ib)
	{
		if (ib->m_DX8IndexBuffer)
		{
			ib->m_DX8IndexBuffer->Release_Ref();
			ib->m_DX8IndexBuffer = 0;
		}
		ib = ib->m_nextIB;
	}
}
