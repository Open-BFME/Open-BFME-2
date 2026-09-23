// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour W3DSnow.cpp donor with target holder, device guard and COM ABI.
// Only observed virtual slots and fields are represented in these views.
class BfmeResetTextureRef {
    void *m_texture;
public:
    void clear();
    ~BfmeResetTextureRef();
};

class IndexBufferClass {
public:
    virtual void Delete_This();
    int m_referenceCount;
    void Release_Ref()
    {
        if (--m_referenceCount == 0) Delete_This();
    }
};

class IDirect3DVertexBuffer8 {
public:
    virtual void QueryInterfaceSlot() = 0;
    virtual void AddRefSlot() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock {
public:
    BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
    ~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class SnowManager {
public:
    virtual ~SnowManager();
    virtual void init();
private:
    unsigned char m_targetBase[0x70];
};

class W3DSnowManager : public SnowManager {
public:
    virtual ~W3DSnowManager();
    virtual void init();
    void ReleaseResources();
    bool ReAcquireResources();
private:
    IndexBufferClass *m_indexBuffer;
    BfmeResetTextureRef m_snowTexture;
    IDirect3DVertexBuffer8 *m_vertexBuffer;
    unsigned int m_targetCounters[3];
    unsigned char m_targetTail[0x24];
};

typedef char SnowBaseExtent[sizeof(SnowManager) == 0x74 ? 1 : -1];
typedef char W3DSnowExtent[sizeof(W3DSnowManager) == 0xB0 ? 1 : -1];

void W3DSnowManager::ReleaseResources()
{
    BFMEDX8DeviceLock lock;
    m_snowTexture.clear();
    if (m_vertexBuffer) m_vertexBuffer->Release();
    m_vertexBuffer = 0;
    if (m_indexBuffer) {
        m_indexBuffer->Release_Ref();
        m_indexBuffer = 0;
    }
}
