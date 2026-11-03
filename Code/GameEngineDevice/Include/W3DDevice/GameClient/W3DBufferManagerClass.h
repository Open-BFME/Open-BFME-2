/* Target facts (all addresses are BFME2 retail RVAs):
   Constructor 0x00115DF4 (215 bytes) has no base call or vtable store; destructor
   0x001163E7 calls freeAllSlots (0x00115ECB), then jumps to freeAllBuffers
   (0x00115F73), without a vtable store. Deleting destructor 0x000F0956 calls it
   directly. This is a plain class with no virtual functions and no base.
   Allocation 0x000F1A6A pushes 0x4265C for new at 0x000F1A72, then calls the
   constructor at 0x000F1A88. Constructor stores +0x42658, the final int.
   Constructor clears 18 VB heads at +0x9000 and 0x2400 slot pointers at +0;
   releaseSlot 0x00116113 shifts the format by 9, proving 512 slots per format.
   Constructor clears 4096 0x1C-byte vertex slots at +0x9048, their count at
   +0x25048, 32 0x1C-byte VBs at +0x2504C, and their count at +0x253CC.
   It clears 1024 IB slot pointers at +0x253D0, the IB head at +0x263D0,
   4096 0x1C-byte index slots at +0x263D4, their count at +0x423D4,
   and 32 0x14-byte IBs at +0x423D8, with their count at +0x42658.
   allocateSlotStorage 0x0011615B/0x001162BE proves slot fields at +0,+4,+8,
   +0xC,+0x10,+0x14,+0x18; VB fields at +0,+4,+8,+0xC,+0x10,+0x14,+0x18;
   and IB fields at +0,+4,+8,+0xC,+0x10. The VB constructor called at
   0x001161F3 is BfmeDynamicNativeVB (0x0013AC00); IB ctor is 0x00138980.
   getSlot 0x001163F1/0x00116434 and releaseSlot 0x00116113/0x0011629A,
   ReleaseResources 0x00115FF1 and ReAcquireResources 0x0011604D are out of line.
   getNextVertexBuffer 0x000EFB14 reads the VB head at +0x9000 or next at +0x10;
   it is inline: renderShadows 0x000F4AB7 inlines each walk's first call and
   calls the out-of-line copy 0x000EFB14 for the rest.
   getDX8Format 0x00115DE8 reads the 18-entry FVF table at 0x009B5F30.
   renderShadows reads the task's next pointer at +0 (0x000F5897) and clears
   the VB's task head at +0x18 (0x000F58AB).
   Donor facts: Zero Hour W3DBufferManager.h supplies the member, nested-type,
   method and FVF enumerator names, including the DX8VertexBufferClass pointer
   type. Its slot-array limits are not BFME2's.
*/
#pragma once

#ifndef BFME2_W3D_BUFFER_MANAGER_CLASS_H
#define BFME2_W3D_BUFFER_MANAGER_CLASS_H

class DX8VertexBufferClass;
class DX8IndexBufferClass;

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
        int m_size;
        int m_start;
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
        int m_startFreeIndex;
        int m_size;
        W3DVertexBuffer *m_nextVB;
        DX8VertexBufferClass *m_DX8VertexBuffer;
        W3DRenderTask *m_renderTaskList;
    };

    struct W3DIndexBufferSlot
    {
        int m_size;
        int m_start;
        W3DIndexBuffer *m_IB;
        W3DIndexBufferSlot *m_prevSameSize;
        W3DIndexBufferSlot *m_nextSameSize;
        W3DIndexBufferSlot *m_prevSameIB;
        W3DIndexBufferSlot *m_nextSameIB;
    };

    struct W3DIndexBuffer
    {
        W3DIndexBufferSlot *m_usedSlots;
        int m_startFreeIndex;
        int m_size;
        W3DIndexBuffer *m_nextIB;
        DX8IndexBufferClass *m_DX8IndexBuffer;
    };

    W3DBufferManager();
    ~W3DBufferManager();
    W3DVertexBufferSlot *getSlot(VBM_FVF_TYPES format, int size);
    W3DIndexBufferSlot *getSlot(int size);
    void releaseSlot(W3DVertexBufferSlot *slot);
    void releaseSlot(W3DIndexBufferSlot *slot);
    void freeAllSlots();
    void freeAllBuffers();
    void ReleaseResources();
    bool ReAcquireResources();
    W3DVertexBuffer *getNextVertexBuffer(W3DVertexBuffer *pVb, VBM_FVF_TYPES type)
    {
        if (pVb == 0)
            return m_W3DVertexBuffers[type];
        return pVb->m_nextVB;
    }
    static int getDX8Format(VBM_FVF_TYPES format);

protected:
    W3DVertexBufferSlot *m_W3DVertexBufferSlots[MAX_FVF][512]; // +0x00000
    W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF]; // +0x09000
    W3DVertexBufferSlot m_W3DVertexBufferEmptySlots[4096]; // +0x09048
    int m_numEmptySlotsAllocated; // +0x25048
    W3DVertexBuffer m_W3DEmptyVertexBuffers[32]; // +0x2504C
    int m_numEmptyVertexBuffersAllocated; // +0x253CC
    W3DIndexBufferSlot *m_W3DIndexBufferSlots[1024]; // +0x253D0
    W3DIndexBuffer *m_W3DIndexBuffers; // +0x263D0
    W3DIndexBufferSlot m_W3DIndexBufferEmptySlots[4096]; // +0x263D4
    int m_numEmptyIndexSlotsAllocated; // +0x423D4
    W3DIndexBuffer m_W3DEmptyIndexBuffers[32]; // +0x423D8
    int m_numEmptyIndexBuffersAllocated; // +0x42658

    W3DVertexBufferSlot *allocateSlotStorage(VBM_FVF_TYPES format, int size);
    W3DIndexBufferSlot *allocateSlotStorage(int size);
};

extern W3DBufferManager *TheW3DBufferManager;

#endif
