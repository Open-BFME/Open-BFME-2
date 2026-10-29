// cl: /DNDEBUG /MD /EHsc

// ?ReAcquireResources@W3DBufferManager@@QAE_NXZ, retail 0x0011604D, 198 bytes.
// Evidence: __thiscall bool with no args (ret, al 1/0); loops 0x12 VB heads at
// this+0x9000 via +0x10 chain allocating BfmeDynamicNativeVB with table at
// 0x00DB5F30 indexed by m_format plus (ushort)m_size then IB list at
// this+0x263D0 allocating DX8IndexBufferClass; callers 0x000F0A50; neighbours
// 0x00115FF1/0x00116113 prove W3DBufferManager class and /O1 /DNDEBUG /MD /EHsc /G7 flags.

#define MAX_VB_SIZES 512	// BFME, not ZH's 128: releaseSlot shifts the format left by 9
#define MIN_SLOT_SIZE 32
#define MIN_SLOT_SIZE_SHIFT 5
#define MAX_VERTEX_BUFFERS_CREATED 32
#define MAX_NUMBER_SLOTS 4096
#define MAX_IB_SIZES 1024	// BFME, not ZH's 128: m_W3DIndexBuffers sits at this+0x263D0
#define MAX_INDEX_BUFFERS_CREATED 32

typedef int Int;

// BFME's vertex buffer, defined in
// Code/Libraries/Source/WWVegas/WW3D2/bfmedynamicvertexbuffer.cpp. Spelled
// here are only the constructor the manager calls and the reference count it
// drops: the count at +4, its deleter in the first virtual slot.
class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned fvf, unsigned short count, unsigned usage, unsigned fvfSize);
	virtual void DeleteThis();
	void Release_Ref() { m_references--; if (m_references == 0) DeleteThis(); }
private:
	int m_references;
	char m_storage[24];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DX8IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass( unsigned indexCount, UsageType usage = USAGE_DEFAULT );
	virtual void Delete_This();
	void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
private:
	int NumRefs;
	char m_storage[ 16 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBufferManager.h,
// with BFME's MAX_VB_SIZES and MAX_IB_SIZES and its own vertex buffer class.
class W3DBufferManager
{
public:
	//List of all possible vertex formats available to the game.
	enum VBM_FVF_TYPES
	{
		VBM_FVF_XYZ,		//position
		VBM_FVF_XYZD,		//position, diffuse
		VBM_FVF_XYZUV,		//position, uv
		VBM_FVF_XYZDUV,		//position, diffuse, uv
		VBM_FVF_XYZUV2,		//position, uv1, uv2
		VBM_FVF_XYZDUV2,	//position, diffuse, uv1, uv2
		VBM_FVF_XYZN,		//position, normal
		VBM_FVF_XYZND,		//position, normal, diffuse
		VBM_FVF_XYZNUV,		//position, normal, uv
		VBM_FVF_XYZNDUV,	//position, normal, diffuse, uv
		VBM_FVF_XYZNUV2,	//position, normal, uv1, uv2
		VBM_FVF_XYZNDUV2,	//position, normal, diffuse, uv1, uv2
		VBM_FVF_XYZRHW,		//transformed position
		VBM_FVF_XYZRHWD,	//transformed position, diffuse
		VBM_FVF_XYZRHWUV,	//transformed position, uv
		VBM_FVF_XYZRHWDUV,	//transformed position, diffuse, uv
		VBM_FVF_XYZRHWUV2,	//transformed position, uv1, uv2
		VBM_FVF_XYZRHWDUV2,	//transformed position, diffuse, uv1, uv2
		MAX_FVF
	};

	struct W3DRenderTask
	{
		W3DRenderTask	*m_nextTask;	///<next rendering task
	};

	struct W3DVertexBuffer;	//forward reference
	struct W3DIndexBuffer; //forward reference

	struct W3DVertexBufferSlot
	{
		Int m_size;								///<number of vertices in slot
		Int m_start;							///<index of first vertex within VB
		W3DVertexBuffer *m_VB;		///<vertex buffer holding this slot.
		W3DVertexBufferSlot *m_prevSameSize;		//previous slot of equal size.
		W3DVertexBufferSlot *m_nextSameSize;		//next slot of equal size.
		W3DVertexBufferSlot *m_prevSameVB;			//previous slot in same VB.
		W3DVertexBufferSlot *m_nextSameVB;			//next slot in same VB.
	};

	struct W3DVertexBuffer
	{
		VBM_FVF_TYPES	m_format;			///<format of vertices in this VB.
		W3DVertexBufferSlot *m_usedSlots;	///<slots inside this vertex buffer being used.
		Int	m_startFreeIndex;				///<index of vertex at start of unallocated memory.
		Int m_size;							///<number of vertices allowed in VB.
		W3DVertexBuffer *m_nextVB;			///<next vertex buffer of same type.
		BfmeDynamicNativeVB *m_DX8VertexBuffer;	///<actual DX8 vertex buffer interface
		W3DRenderTask	*m_renderTaskList;	///<used to help app sort its D3D access by VB.
	};

	struct W3DIndexBufferSlot
	{
		Int m_size;								///<number of vertices in slot
		Int m_start;							///<index of first index within VB
		W3DIndexBuffer *m_IB;		///<index buffer holding this slot.
		W3DIndexBufferSlot *m_prevSameSize;		//previous slot of equal size.
		W3DIndexBufferSlot *m_nextSameSize;		//next slot of equal size.
		W3DIndexBufferSlot *m_prevSameIB;			//previous slot in same VB.
		W3DIndexBufferSlot *m_nextSameIB;			//next slot in same VB.
	};

	struct W3DIndexBuffer
	{
		W3DIndexBufferSlot *m_usedSlots;	///<slots inside this index buffer being used.
		Int	m_startFreeIndex;				///<index of index at start of unallocated memory.
		Int m_size;							///<number of vertices allowed in VB.
		W3DIndexBuffer *m_nextIB;			///<next index buffer of same type.
		DX8IndexBufferClass *m_DX8IndexBuffer;	///<actual DX8 index buffer interface
	};

	W3DBufferManager(void);
	~W3DBufferManager(void);

	///return free vertex buffer memory slot.
	W3DVertexBufferSlot *getSlot(VBM_FVF_TYPES fvfType, Int size);
	///return free index buffer memory slot.
	W3DIndexBufferSlot *getSlot(Int size);
	void releaseSlot(W3DVertexBufferSlot *vbSlot);	///<return slot to pool
	void releaseSlot(W3DIndexBufferSlot *vbSlot);	///<return slot to pool
	void freeAllSlots(void);	///<release all slots to pool.
	void freeAllBuffers(void);	///<release all vertex buffers to pool.
	void ReleaseResources(void);	///<release D3D/W3D resources.
	bool ReAcquireResources(void);	///<reaquire D3D/W3D resources.

	static Int getDX8Format(VBM_FVF_TYPES format);	///<translates our vertex format into D3D equivalent

protected:

	///holds previously allocated slots that are free to fill again.
	W3DVertexBufferSlot *m_W3DVertexBufferSlots[MAX_FVF][MAX_VB_SIZES];	///< this+0x00000
	///holds allocated vertex buffers of each type.
	W3DVertexBuffer		*m_W3DVertexBuffers[MAX_FVF];				///< this+0x09000
	///holds unallocated slot wrappers which were never initialized
	W3DVertexBufferSlot	m_W3DVertexBufferEmptySlots[MAX_NUMBER_SLOTS];
	Int m_numEmptySlotsAllocated;
	///holds unallocated vertex buffer wrappers which were never initialized
	W3DVertexBuffer		m_W3DEmptyVertexBuffers[MAX_VERTEX_BUFFERS_CREATED];
	Int m_numEmptyVertexBuffersAllocated;

	///holds previously allocated slots that are free to fill again.
	W3DIndexBufferSlot *m_W3DIndexBufferSlots[MAX_IB_SIZES];			///< this+0x253D0
	///holds allocated index buffers of each type.
	W3DIndexBuffer		*m_W3DIndexBuffers;								///< this+0x263D0
	///holds unallocated slot wrappers which were never initialized
	W3DIndexBufferSlot	m_W3DIndexBufferEmptySlots[MAX_NUMBER_SLOTS];
	Int m_numEmptyIndexSlotsAllocated;
	///holds unallocated index buffer wrappers which were never initialized
	W3DIndexBuffer		m_W3DEmptyIndexBuffers[MAX_INDEX_BUFFERS_CREATED];
	Int m_numEmptyIndexBuffersAllocated;

	///allocate new memory inside a vertex buffer.
	W3DVertexBufferSlot *allocateSlotStorage(VBM_FVF_TYPES fvfType, Int size);
	W3DIndexBufferSlot *allocateSlotStorage(Int size);
};

// Retail's own per-format FVF table at RVA 0x009B5F30 (.data, file offset
// 0x00975FB0): eighteen unsigned entries in the order of W3DBufferManager's
// VBM_FVF_TYPES, so the D3D flexible vertex format the rowed body below hands to
// the dynamic vertex buffer. XYZ is D3DFVF_XYZ (0x002); the D suffix adds
// D3DFVF_DIFFUSE (0x040); UV is D3DFVF_TEX1 (0x100) and UV2 D3DFVF_TEX2 (0x200);
// the N prefix adds D3DFVF_NORMAL (0x010); and XYZRHW is D3DFVF_XYZRHW (0x004).
// Eighteen entries is MAX_FVF, and 72 bytes is all but eight of the ledger's
// bound - the words that follow belong to retail's next object. The words are
// transcribed verbatim from retail's own .data.
// Symbol ?g_00DB5F30@@3PAIA, transcribed below.
extern unsigned g_00DB5F30[] =
{
	0x002, 0x042, 0x102, 0x142, 0x202, 0x242,
	0x012, 0x052, 0x112, 0x152, 0x212, 0x252,
	0x004, 0x044, 0x104, 0x144, 0x204, 0x244
};

bool W3DBufferManager::ReAcquireResources()
{
	for (int i = 0; i < MAX_FVF; ++i)
	{
		W3DVertexBuffer *vb = m_W3DVertexBuffers[i];
		while (vb)
		{
			vb->m_DX8VertexBuffer = new BfmeDynamicNativeVB(g_00DB5F30[vb->m_format], (unsigned short)vb->m_size, 0, 0);
			if (!vb->m_DX8VertexBuffer)
				return false;
			vb = vb->m_nextVB;
		}
	}
	W3DIndexBuffer *ib = m_W3DIndexBuffers;
	while (ib)
	{
		ib->m_DX8IndexBuffer = new DX8IndexBufferClass(ib->m_size, DX8IndexBufferClass::USAGE_DEFAULT);
		if (!ib->m_DX8IndexBuffer)
			return false;
		ib = ib->m_nextIB;
	}
	return true;
}
