// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour W3DSnow.cpp donor with target holder, device guard and COM ABI.
#include "ascii_string.h"
// Only observed virtual slots and fields are represented in these views.
// ReAcquireResources 0x0009390F..0x00093ACB: Zero Hour resource-setup
// algorithm adapted to retail D3D9 COM arguments, weather flags +44/+45,
// 24-byte index buffers and owning texture handles. The verified sibling
// updateIniSettings establishes the derived handle assignment shape; this
// keeps the same +78 holder layout and matches all 444 bytes and bindings.
// Reference reviewed: open-bfme-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
class TextureClass { public: void Release_Ref(); };
class BfmeResetTextureRef {public: TextureClass *Ptr; BfmeResetTextureRef():Ptr(0) {} void clear();};
template<class T> class RefCountPtr:public BfmeResetTextureRef {
public:
 const RefCountPtr &operator=(const RefCountPtr &other);
 ~RefCountPtr() {if(Ptr) Ptr->Release_Ref();}
};
class BFME2ParticleTextureHandle:public RefCountPtr<TextureClass> {};

extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock {
public:
    BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
    ~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};
class DX8IndexBufferClass;
class IndexBufferClass {
public:
class WriteLockClass { IndexBufferClass *m_indexBuffer; unsigned short *m_indices; BFMEDX8DeviceLock m_deviceLock; public: WriteLockClass(IndexBufferClass *, int); ~WriteLockClass(); unsigned short *Get_Index_Array() { return m_indices; } };
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



class SnowManager {
public:
    SnowManager();
    virtual ~SnowManager();
    virtual void init();
protected:
    unsigned char m_targetBase04[0x3D]; bool m_targetFlag41; unsigned char m_target42[0x32];
};

class DX8IndexBufferClass : public IndexBufferClass { unsigned char m_targetTail[16]; public: enum UsageType { USAGE_DEFAULT = 0 }; DX8IndexBufferClass(unsigned int, UsageType); };

class W3DSnowManager : public SnowManager {
public:
    W3DSnowManager();
    virtual ~W3DSnowManager();
    virtual void init();
    void ReleaseResources();
    bool ReAcquireResources();
private:
    DX8IndexBufferClass *m_indexBuffer;
    BFME2ParticleTextureHandle m_snowTexture;
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

// ?init@W3DSnowManager@@UAEXXZ @0x00094642 16B, vftable slot 1 (ZH donor):
// base init, then (re)build the device resources, result ignored.
void W3DSnowManager::init()
{
    SnowManager::init();
    ReAcquireResources();
}


class Overridable { public: virtual ~Overridable(); Overridable *m_nextOverride; bool m_isOverride; const Overridable *getFinalOverride() const { return m_nextOverride ? m_nextOverride->getFinalOverride() : this; } };
class WeatherSetting : public Overridable { public: unsigned char m_pad0C[0x0C]; AsciiString m_snowTexture; unsigned char m_target1C[0x28]; bool m_usePointSprites; bool m_snowEnabled; };
template<class T> class OVERRIDE { public: const T *m_object; operator const T *() const { if (!m_object) return 0; return static_cast<const T *>(m_object->getFinalOverride()); } const T *operator->() const { if (!m_object) return 0; return static_cast<const T *>(m_object->getFinalOverride()); } };
extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class DX8Caps { public: unsigned char m_pad[0x2A9]; bool m_supportPointSprites; bool Support_PointSprites() const { return m_supportPointSprites; } };

struct IDirect3DDevice8 { virtual void Slot00()=0; virtual void Slot04()=0; virtual void Slot08()=0; virtual void Slot0c()=0; virtual void Slot10()=0; virtual void Slot14()=0; virtual void Slot18()=0; virtual void Slot1c()=0; virtual void Slot20()=0; virtual void Slot24()=0; virtual void Slot28()=0; virtual void Slot2c()=0; virtual void Slot30()=0; virtual void Slot34()=0; virtual void Slot38()=0; virtual void Slot3c()=0; virtual void Slot40()=0; virtual void Slot44()=0; virtual void Slot48()=0; virtual void Slot4c()=0; virtual void Slot50()=0; virtual void Slot54()=0; virtual void Slot58()=0; virtual void Slot5c()=0; virtual void Slot60()=0; virtual void Slot64()=0; virtual long __stdcall CreateVertexBuffer(unsigned int, unsigned int, unsigned long, unsigned long, IDirect3DVertexBuffer8 **, void **)=0; };

class DX8Wrapper { protected: static DX8Caps *CurrentCaps; static IDirect3DDevice8 *D3DDevice; public: static DX8Caps *Get_Current_Caps() { return CurrentCaps; } static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; } };

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
bool W3DSnowManager::ReAcquireResources() {
    BFMEDX8DeviceLock lock;
    ReleaseResources();
    if (!TheWeatherSetting->m_snowEnabled || !m_targetFlag41) return true;
    if (TheWeatherSetting->m_usePointSprites && DX8Wrapper::Get_Current_Caps()->Support_PointSprites()) {
        IDirect3DDevice8 *device=DX8Wrapper::_Get_D3D_Device8();
        if (m_vertexBuffer == 0 && device->CreateVertexBuffer(4096 * 16, 0x248, 0x42, 0, &m_vertexBuffer, 0) < 0) return false;
    } else {
        m_indexBuffer = new DX8IndexBufferClass(2048 * 6, DX8IndexBufferClass::USAGE_DEFAULT);
        IndexBufferClass::WriteLockClass lockIdxBuffer(static_cast<IndexBufferClass *>(m_indexBuffer), 0);
        unsigned short *ib=lockIdxBuffer.Get_Index_Array();
        int vbCount=0;
        for (int i=0;i<2048;i++) {
            ib[0]=vbCount+3; ib[1]=vbCount; ib[2]=vbCount+2;
            ib[3]=vbCount+2; ib[4]=vbCount; ib[5]=vbCount+1;
            vbCount+=4; ib+=6;
        }
    }
    m_snowTexture = BFME2LoadParticleTexture(TheWeatherSetting->m_snowTexture.str(), 0, 0);
    m_80=4096; m_88=4096; m_84=2048;
    return true;
}







