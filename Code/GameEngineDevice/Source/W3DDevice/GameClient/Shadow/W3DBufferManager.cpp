// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#include "Common/Debug.h"
#include "W3DDevice/GameClient/W3DBufferManager.h"

W3DBufferManager *TheW3DBufferManager=NULL;	//singleton

static int FVFTypeIndexList[W3DBufferManager::MAX_FVF]=
{
	D3DFVF_XYZ,
	D3DFVF_XYZ|D3DFVF_DIFFUSE,
	D3DFVF_XYZ|D3DFVF_TEX1,
	D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
	D3DFVF_XYZ|D3DFVF_TEX2,
	D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX2,
	D3DFVF_XYZ|D3DFVF_NORMAL,
	D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE,
	D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1,
	D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1,
	D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2,
	D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2,
	D3DFVF_XYZRHW,
	D3DFVF_XYZRHW|D3DFVF_DIFFUSE,
	D3DFVF_XYZRHW|D3DFVF_TEX1,
	D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1,
	D3DFVF_XYZRHW|D3DFVF_TEX2,
	D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX2
};

// ?getDX8Format@W3DBufferManager@@SAHW4VBM_FVF_TYPES@1@@Z present-unmatched
Int W3DBufferManager::getDX8Format(VBM_FVF_TYPES format)
{
	return FVFTypeIndexList[format];
}

// header's declarations.  Keep that drift local to this body so the matched
// ZH-era methods below continue to compile against their vendored header.
W3DBufferManager::W3DBufferManager(void)
{
	struct BFMEBufferSlotStorage
	{
		unsigned int value0;
		unsigned int value1;
		unsigned int value2;
		unsigned int value3;
		unsigned int value4;
		unsigned int value5;
		unsigned int value6;
	};
	struct BFMEIndexBufferStorage
	{
		unsigned int value0;
		unsigned int value1;
		unsigned int value2;
		unsigned int value3;
		unsigned int value4;
	};
	struct BFMEBufferManagerView
	{
		unsigned int vertexSlotLists[18][512];
		unsigned int vertexBuffers[18];
		BFMEBufferSlotStorage emptyVertexSlots[4096];
		unsigned int numEmptySlots;
		BFMEBufferSlotStorage emptyVertexBuffers[32];
		unsigned int numEmptyVertexBuffers;
		unsigned int indexSlotLists[1024];
		unsigned int indexBuffers;
		BFMEBufferSlotStorage emptyIndexSlots[4096];
		unsigned int numEmptyIndexSlots;
		BFMEIndexBufferStorage emptyIndexBuffers[32];
		unsigned int numEmptyIndexBuffers;
	};
	BFMEBufferManagerView *bfme = reinterpret_cast<BFMEBufferManagerView *>(this);

	bfme->numEmptySlots=0;
	bfme->numEmptyVertexBuffers=0;
	bfme->indexBuffers=0;
	bfme->numEmptyIndexSlots=0;
	bfme->numEmptyIndexBuffers=0;

	for (Int i=0; i<18; i++)
		bfme->vertexBuffers[i]=0;
	for (Int i=0; i<18*512; i++)
		reinterpret_cast<unsigned int *>(bfme->vertexSlotLists)[i]=0;
	for (Int i=0; i<4096; i++)
	{
		bfme->emptyVertexSlots[i].value0=0;
		bfme->emptyVertexSlots[i].value1=0;
		bfme->emptyVertexSlots[i].value2=0;
		bfme->emptyVertexSlots[i].value3=0;
		bfme->emptyVertexSlots[i].value4=0;
		bfme->emptyVertexSlots[i].value5=0;
		bfme->emptyVertexSlots[i].value6=0;
	}
	for (Int i=0; i<32; i++)
	{
		bfme->emptyVertexBuffers[i].value0=0;
		bfme->emptyVertexBuffers[i].value1=0;
		bfme->emptyVertexBuffers[i].value2=0;
		bfme->emptyVertexBuffers[i].value3=0;
		bfme->emptyVertexBuffers[i].value4=0;
		bfme->emptyVertexBuffers[i].value5=0;
		bfme->emptyVertexBuffers[i].value6=0;
	}
	for (Int i=0; i<1024; i++)
		bfme->indexSlotLists[i]=0;
	for (Int i=0; i<4096; i++)
	{
		bfme->emptyIndexSlots[i].value0=0;
		bfme->emptyIndexSlots[i].value1=0;
		bfme->emptyIndexSlots[i].value2=0;
		bfme->emptyIndexSlots[i].value3=0;
		bfme->emptyIndexSlots[i].value4=0;
		bfme->emptyIndexSlots[i].value5=0;
		bfme->emptyIndexSlots[i].value6=0;
	}
	for (Int i=0; i<32; i++)
	{
		bfme->emptyIndexBuffers[i].value0=0;
		bfme->emptyIndexBuffers[i].value1=0;
		bfme->emptyIndexBuffers[i].value2=0;
		bfme->emptyIndexBuffers[i].value3=0;
		bfme->emptyIndexBuffers[i].value4=0;
	}
}

W3DBufferManager::~W3DBufferManager(void)
{
	freeAllSlots();
	freeAllBuffers();
}

// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp
// ?freeAllSlots@W3DBufferManager@@ present-unmatched
void W3DBufferManager::freeAllSlots(void)
{
	Int i,j;

	for (i=0; i<MAX_FVF; i++)
	{
		for (j=0; j<MAX_VB_SIZES; j++)
		{
			//Release all slots allocated for each size
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
		//Release all slots allocated for each size
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

	DEBUG_ASSERTCRASH(m_numEmptySlotsAllocated==0, ("Failed to free all empty vertex buffer slots"));
	DEBUG_ASSERTCRASH(m_numEmptyIndexSlotsAllocated==0, ("Failed to free all empty index buffer slots"));
}

void W3DBufferManager::freeAllBuffers(void)
{
	struct BFMEBufferManagerView
	{
		unsigned char pad_to_vertex_buffers[0x9000];
		W3DVertexBuffer *vertex_buffers[MAX_FVF];
		unsigned char pad_to_vertex_count[0x1c384];
		Int empty_vertex_count;
		unsigned char pad_to_index_buffers[0x1000];
		W3DIndexBuffer *index_buffers;
		unsigned char pad_to_index_count[0x1c284];
		Int empty_index_count;
	};
	BFMEBufferManagerView *bfme = reinterpret_cast<BFMEBufferManagerView *>(this);
	Int i;

	//Make sure all slots are free
	freeAllSlots();	///<release all slots to pool.

	for (i=0; i<MAX_FVF; i++)
	{
		W3DVertexBuffer *vb = bfme->vertex_buffers[i];
		while (vb)
		{	DEBUG_ASSERTCRASH(vb->m_usedSlots == NULL, ("Freeing Non-Empty Vertex Buffer"));
			if (vb->m_DX8VertexBuffer)
				REF_PTR_RELEASE(vb->m_DX8VertexBuffer);
			bfme->empty_vertex_count--;
			vb=vb->m_nextVB;	//get next vertex buffer of this type
		}
		bfme->vertex_buffers[i]=NULL;
	}

	W3DIndexBuffer *ib = bfme->index_buffers;
	while (ib)
	{	DEBUG_ASSERTCRASH(ib->m_usedSlots == NULL, ("Freeing Non-Empty Index Buffer"));
		if (ib->m_DX8IndexBuffer)
			REF_PTR_RELEASE(ib->m_DX8IndexBuffer);
		bfme->empty_index_count--;
		ib=ib->m_nextIB;	//get next vertex buffer of this type
	}
	bfme->index_buffers=NULL;

	DEBUG_ASSERTCRASH(m_numEmptyVertexBuffersAllocated==0, ("Failed to free all empty vertex buffers"));
	DEBUG_ASSERTCRASH(m_numEmptyIndexBuffersAllocated==0, ("Failed to free all empty index buffers"));
}

// ?ReleaseResources@W3DBufferManager@@ present-unmatched
void W3DBufferManager::ReleaseResources(void)
{
	for (Int i=0; i<MAX_FVF; i++)
	{
		W3DVertexBuffer *vb = m_W3DVertexBuffers[i];
		while (vb)
		{
			REF_PTR_RELEASE(vb->m_DX8VertexBuffer);
			vb=vb->m_nextVB;	//get next vertex buffer of this type
		}
	}

	W3DIndexBuffer *ib = m_W3DIndexBuffers;
	while (ib)
	{
		REF_PTR_RELEASE(ib->m_DX8IndexBuffer);
		ib=ib->m_nextIB;	//get next vertex buffer of this type
	}
}

class BfmeDX8VertexBuffer
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };

	BfmeDX8VertexBuffer(unsigned fvf, unsigned short count,
		UsageType usage, unsigned vertexSize);

private:
	unsigned char m_storage[0x20];
};

class BfmeDX8IndexBuffer
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };

	BfmeDX8IndexBuffer(unsigned count, UsageType usage);

private:
	unsigned char m_storage[0x18];
};

struct BFMEReAcquireBufferManagerView
{
	unsigned char m_beforeVertexBuffers[0x9000];
	W3DBufferManager::W3DVertexBuffer *m_vertexBuffers[W3DBufferManager::MAX_FVF];
	unsigned char m_beforeIndexBuffers[0x1c384];
	Int m_emptyVertexBufferCount;
	unsigned char m_beforeIndexBufferList[0x1000];
	W3DBufferManager::W3DIndexBuffer *m_indexBuffers;
};

// W3DBufferManager::ReAcquireResources is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManagerRva0011604D.cpp (0x0011604D).

// Defined in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp: getSlot(VBM_FVF_TYPES, Int).
// Defined in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp: releaseSlot(W3DVertexBufferSlot *).
// Defined in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp: allocateSlotStorage(VBM_FVF_TYPES, Int).

//******************************** Index Buffer code ******************************************************
// Defined in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp: getSlot(Int).
// Defined in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp: releaseSlot(W3DIndexBufferSlot *).
// Defined in Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager_Slots.cpp: allocateSlotStorage(Int).
