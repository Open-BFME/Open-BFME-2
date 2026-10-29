// cl: /DNDEBUG /MD /EHsc
// readable body of ?allocateSlotStorage@W3DBufferManager@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp
// readable body of ?freeAllSlots@W3DBufferManager@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp
// readable body of ?getSlot@W3DBufferManager@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp
// readable body of ?releaseSlot@W3DBufferManager@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// W3DBufferManager's four slot pool accessors -- Zero Hour bodies, unchanged,
// compiled against the BFME member block.
//
// Two constants drifted. releaseSlot(W3DVertexBufferSlot*) at 0x00116113
// indexes m_W3DVertexBufferSlots with `shl edi,9` on the vertex format before
// adding the size index, so a row of that array is 512 pointers wide, not ZH's
// MAX_VB_SIZES of 128.
//
// releaseSlot(W3DIndexBufferSlot*) at 0x0011629A reaches m_W3DIndexBufferSlots
// at this+0x253D0, and
//
//     18*512*4  m_W3DVertexBufferSlots[MAX_FVF][512]
//   +   18*4    m_W3DVertexBuffers[MAX_FVF]
//   + 4096*28   m_W3DVertexBufferEmptySlots[MAX_NUMBER_SLOTS]
//   +      4    m_numEmptySlotsAllocated
//   +   32*28   m_W3DEmptyVertexBuffers[MAX_VERTEX_BUFFERS_CREATED]
//   +      4    m_numEmptyVertexBuffersAllocated
//   = 0x253D0
//
// so MAX_FVF, MAX_NUMBER_SLOTS and MAX_VERTEX_BUFFERS_CREATED are all still ZH's.
// ReAcquireResources (0x0011604D) reads m_W3DIndexBuffers at this+0x263D0,
// 0x1000 bytes further on: MAX_IB_SIZES is 1024, not ZH's 128.
//
// The class is spelled here rather than in a corrected copy of
// W3DDevice/GameClient/W3DBufferManager.h on purpose: a header or shim change
// makes every later commit in the tree run the full gate, which is the same
// reason FrameDataManager.cpp declares its class inline. Every file of the
// W3DBufferManager.cpp unit spells the same block.

#include <stddef.h>

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

// ?freeAllSlots@W3DBufferManager@@QAEXXZ
void W3DBufferManager::freeAllSlots(void)
{
	Int i,j;

	for (i=0; i<MAX_FVF; i++)
	{
		for (j=0; j<MAX_VB_SIZES; j++)
		{
			W3DVertexBufferSlot *vbSlot = m_W3DVertexBufferSlots[i][j];
			while (vbSlot)
			{
				if (vbSlot->m_prevSameVB)
					vbSlot->m_prevSameVB->m_nextSameVB=vbSlot->m_nextSameVB;
				else
					vbSlot->m_VB->m_usedSlots=NULL;

				if (vbSlot->m_nextSameVB)
					vbSlot->m_nextSameVB->m_prevSameVB=vbSlot->m_prevSameVB;
				vbSlot=vbSlot->m_nextSameSize;
				m_numEmptySlotsAllocated--;
			}
			m_W3DVertexBufferSlots[i][j]=NULL;
		}
	}

	for (j=0; j<MAX_IB_SIZES; j++)
	{
		W3DIndexBufferSlot *ibSlot = m_W3DIndexBufferSlots[j];
		while (ibSlot)
		{
			if (ibSlot->m_prevSameIB)
				ibSlot->m_prevSameIB->m_nextSameIB=ibSlot->m_nextSameIB;
			else
				ibSlot->m_IB->m_usedSlots=NULL;

			if (ibSlot->m_nextSameIB)
				ibSlot->m_nextSameIB->m_prevSameIB=ibSlot->m_prevSameIB;
			ibSlot=ibSlot->m_nextSameSize;
			m_numEmptyIndexSlotsAllocated--;
		}
		m_W3DIndexBufferSlots[j]=NULL;
	}
}

W3DBufferManager::~W3DBufferManager(void)
{
	freeAllSlots();
	freeAllBuffers();
}

/**Reserves space inside a vertex buffer.  If no space is available,
   creates a new slot and adds it to the pool.
*/
// ?getSlot@W3DBufferManager@@QAEPAUW3DVertexBufferSlot@1@W4VBM_FVF_TYPES@1@H@Z
W3DBufferManager::W3DVertexBufferSlot *W3DBufferManager::getSlot(VBM_FVF_TYPES fvfType, Int size)
{
	W3DVertexBufferSlot *vbSlot=NULL;

	//round size to next multiple of minimum slot size.
	//should help avoid fragmentation.
	size = (size + (MIN_SLOT_SIZE-1)) & (~(MIN_SLOT_SIZE-1));
	Int sizeIndex = (size >> MIN_SLOT_SIZE_SHIFT)-1;

	// DEBUG_ASSERTCRASH -- compiled out under NDEBUG

	if ((vbSlot=m_W3DVertexBufferSlots[fvfType][sizeIndex]) != 0)
	{	//found a previously allocated slot matching required size
		m_W3DVertexBufferSlots[fvfType][sizeIndex]=vbSlot->m_nextSameSize;
		if (vbSlot->m_nextSameSize)
			vbSlot->m_nextSameSize->m_prevSameSize=NULL;
		return vbSlot;
	}
	else
	{	//need to allocate a new slot
		return allocateSlotStorage(fvfType, size);
	}

	return NULL;
}

/**Returns vertex buffer space back to pool so it can be reused later*/
// ?releaseSlot@W3DBufferManager@@QAEXPAUW3DVertexBufferSlot@1@@Z
void W3DBufferManager::releaseSlot(W3DVertexBufferSlot *vbSlot)
{
	Int sizeIndex = (vbSlot->m_size >> MIN_SLOT_SIZE_SHIFT)-1;

	vbSlot->m_nextSameSize=m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex];
	if (m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex])
		m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex]->m_prevSameSize=vbSlot;

	m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex]=vbSlot;
}

/**Reserves space inside an index buffer.  If no space is available,
   creates a new slot and adds it to the pool.
*/
// ?getSlot@W3DBufferManager@@QAEPAUW3DIndexBufferSlot@1@H@Z
W3DBufferManager::W3DIndexBufferSlot *W3DBufferManager::getSlot(Int size)
{
	W3DIndexBufferSlot *ibSlot=NULL;

	//round size to next multiple of minimum slot size.
	//should help avoid fragmentation.
	size = (size + (MIN_SLOT_SIZE-1)) & (~(MIN_SLOT_SIZE-1));
	Int sizeIndex = (size >> MIN_SLOT_SIZE_SHIFT)-1;

	// DEBUG_ASSERTCRASH -- compiled out under NDEBUG

	if ((ibSlot=m_W3DIndexBufferSlots[sizeIndex]) != 0)
	{	//found a previously allocated slot matching required size
		m_W3DIndexBufferSlots[sizeIndex]=ibSlot->m_nextSameSize;
		if (ibSlot->m_nextSameSize)
			ibSlot->m_nextSameSize->m_prevSameSize=NULL;
		return ibSlot;
	}
	else
	{	//need to allocate a new slot
		return allocateSlotStorage(size);
	}

	return NULL;
}

/**Returns index buffer space back to pool so it can be reused later*/
// ?releaseSlot@W3DBufferManager@@QAEXPAUW3DIndexBufferSlot@1@@Z
void W3DBufferManager::releaseSlot(W3DIndexBufferSlot *ibSlot)
{
	Int sizeIndex = (ibSlot->m_size >> MIN_SLOT_SIZE_SHIFT)-1;

	ibSlot->m_nextSameSize=m_W3DIndexBufferSlots[sizeIndex];
	if (m_W3DIndexBufferSlots[sizeIndex])
		m_W3DIndexBufferSlots[sizeIndex]->m_prevSameSize=ibSlot;

	m_W3DIndexBufferSlots[sizeIndex]=ibSlot;
}

// The FVF table at RVA 0x009B5F30 is owned by
// W3DBufferManager_ReAcquireResources.cpp.
extern unsigned g_00DB5F30[];

W3DBufferManager::W3DVertexBufferSlot *W3DBufferManager::allocateSlotStorage(
	VBM_FVF_TYPES fvfType, Int size )
{
	W3DVertexBuffer *pVB = m_W3DVertexBuffers[ fvfType ];
	W3DVertexBufferSlot *vbSlot;

	while ( pVB )
	{
		if ( pVB->m_size - pVB->m_startFreeIndex >= size )
		{
			if ( m_numEmptySlotsAllocated < MAX_NUMBER_SLOTS )
			{
				vbSlot = &m_W3DVertexBufferEmptySlots[ m_numEmptySlotsAllocated ];
				vbSlot->m_size = size;
				vbSlot->m_start = pVB->m_startFreeIndex;
				vbSlot->m_VB = pVB;
				vbSlot->m_nextSameVB = pVB->m_usedSlots;
				vbSlot->m_prevSameVB = NULL;
				if ( pVB->m_usedSlots )
					pVB->m_usedSlots->m_prevSameVB = vbSlot;
				vbSlot->m_prevSameSize = vbSlot->m_nextSameSize = NULL;
				pVB->m_usedSlots = vbSlot;
				pVB->m_startFreeIndex += size;
				m_numEmptySlotsAllocated++;
				return vbSlot;
			}
		}
		pVB = pVB->m_nextVB;
	}

	pVB = m_W3DVertexBuffers[ fvfType ];
	if ( m_numEmptyVertexBuffersAllocated < MAX_VERTEX_BUFFERS_CREATED )
	{
		m_W3DVertexBuffers[ fvfType ] =
			&m_W3DEmptyVertexBuffers[ m_numEmptyVertexBuffersAllocated ];
		m_W3DVertexBuffers[ fvfType ]->m_nextVB = pVB;
		m_numEmptyVertexBuffersAllocated++;
		pVB = m_W3DVertexBuffers[ fvfType ];

		Int vbSize = size < 16384 ? 16384 : size;
		pVB->m_DX8VertexBuffer = new BfmeDynamicNativeVB(
			g_00DB5F30[ fvfType ], (unsigned short)vbSize, 0, 0 );
		pVB->m_format = fvfType;
		pVB->m_startFreeIndex = size;
		pVB->m_size = vbSize;
		pVB->m_renderTaskList = NULL;
		vbSlot = &m_W3DVertexBufferEmptySlots[ m_numEmptySlotsAllocated ];
		m_numEmptySlotsAllocated++;
		pVB->m_usedSlots = vbSlot;
		vbSlot->m_size = size;
		vbSlot->m_start = 0;
		vbSlot->m_VB = pVB;
		vbSlot->m_prevSameVB = vbSlot->m_nextSameVB = NULL;
		vbSlot->m_prevSameSize = vbSlot->m_nextSameSize = NULL;
		return vbSlot;
	}

	return NULL;
}

W3DBufferManager::W3DIndexBufferSlot *W3DBufferManager::allocateSlotStorage( Int size )
{
	W3DIndexBuffer *pIB = m_W3DIndexBuffers;
	W3DIndexBufferSlot *ibSlot;

	while ( pIB )
	{
		if ( pIB->m_size - pIB->m_startFreeIndex >= size )
		{
			if ( m_numEmptyIndexSlotsAllocated < MAX_NUMBER_SLOTS )
			{
				ibSlot = &m_W3DIndexBufferEmptySlots[ m_numEmptyIndexSlotsAllocated ];
				ibSlot->m_size = size;
				ibSlot->m_start = pIB->m_startFreeIndex;
				ibSlot->m_IB = pIB;
				ibSlot->m_nextSameIB = pIB->m_usedSlots;
				ibSlot->m_prevSameIB = NULL;
				if ( pIB->m_usedSlots )
					pIB->m_usedSlots->m_prevSameIB = ibSlot;
				ibSlot->m_prevSameSize = ibSlot->m_nextSameSize = NULL;
				pIB->m_usedSlots = ibSlot;
				pIB->m_startFreeIndex += size;
				m_numEmptyIndexSlotsAllocated++;
				return ibSlot;
			}
		}
		pIB = pIB->m_nextIB;
	}

	pIB = m_W3DIndexBuffers;
	if ( m_numEmptyIndexBuffersAllocated < MAX_INDEX_BUFFERS_CREATED )
	{
		m_W3DIndexBuffers = &m_W3DEmptyIndexBuffers[ m_numEmptyIndexBuffersAllocated ];
		m_W3DIndexBuffers->m_nextIB = pIB;
		m_numEmptyIndexBuffersAllocated++;
		pIB = m_W3DIndexBuffers;

		Int ibSize = size < 32768 ? 32768 : size;
		pIB->m_DX8IndexBuffer =
			new DX8IndexBufferClass( ibSize, DX8IndexBufferClass::USAGE_DEFAULT );
		pIB->m_startFreeIndex = size;
		pIB->m_size = ibSize;
		ibSlot = &m_W3DIndexBufferEmptySlots[ m_numEmptyIndexSlotsAllocated ];
		m_numEmptyIndexSlotsAllocated++;
		pIB->m_usedSlots = ibSlot;
		ibSlot->m_size = size;
		ibSlot->m_start = 0;
		ibSlot->m_IB = pIB;
		ibSlot->m_prevSameIB = ibSlot->m_nextSameIB = NULL;
		ibSlot->m_prevSameSize = ibSlot->m_nextSameSize = NULL;
		return ibSlot;
	}

	return NULL;
}
