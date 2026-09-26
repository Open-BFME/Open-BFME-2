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
    BfmeResetTextureRef() : m_texture(0) {}
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
    SnowManager();
    virtual ~SnowManager();
    virtual void init();
private:
    unsigned char m_targetBase[0x70];
};

class W3DSnowManager : public SnowManager {
public:
    W3DSnowManager();
    virtual ~W3DSnowManager();
    virtual void init();
    void ReleaseResources();
    bool ReAcquireResources();
private:
    IndexBufferClass *m_indexBuffer;
    BfmeResetTextureRef m_snowTexture;
    IDirect3DVertexBuffer8 *m_vertexBuffer;
    unsigned int m_80;
    unsigned int m_84;
    unsigned int m_88;
    unsigned int m_8C;
    float m_90;
    float m_94;
    float m_98;
    float m_9C;
    unsigned int m_A0;
    float m_A4;
    unsigned int m_A8;
    unsigned int m_AC;
};

typedef char SnowBaseExtent[sizeof(SnowManager) == 0x74 ? 1 : -1];
typedef char W3DSnowExtent[sizeof(W3DSnowManager) == 0xB0 ? 1 : -1];

W3DSnowManager::W3DSnowManager()
    : m_indexBuffer(0)
    , m_vertexBuffer(0)
    , m_80(0)
    , m_84(0)
    , m_88(0)
    , m_8C(0)
    , m_90(0.0f)
    , m_94(0.0f)
    , m_A0(0)
    , m_A4(0.0f)
    , m_A8(0)
    , m_AC(0)
{
    float *pair98 = &m_98;
    pair98[0] = 0.0f;
    pair98[1] = 0.0f;
}

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
