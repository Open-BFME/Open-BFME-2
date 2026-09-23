// ?ReAcquireResources@W3DSnowManager@@QAE_NXZ
// partial score=0.9887640449438202 date=2026-09-23
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour W3DSnow.cpp resource setup adapted to target D3D9 and owning handles.
// Weather string18 and flags44/45 are target-backed; intervening fields are unknown.
class TextureBaseClass { public: void Release_Ref(); };
class BFME2ParticleTextureHandle { public: TextureBaseClass *Ptr; ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); } };
class BfmeResetTextureRef { public: TextureBaseClass *pointer; void clear(); };
class CursorTextureSlot : public BfmeResetTextureRef { public: void operator=(const BFME2ParticleTextureHandle &); };
class IndexBuffer { public: virtual void DeleteThis(); int m_referenceCount; void Release_Ref() { if (--m_referenceCount == 0) DeleteThis(); } };
class IDirect3DVertexBuffer9 { public: virtual void Slot0() = 0; virtual void Slot1() = 0; virtual unsigned long __stdcall Release() = 0; };
extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock { public: BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); } ~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); } };
class SubsystemInterface { public: virtual ~SubsystemInterface(); private: unsigned int m_targetBase[2]; };
class SnowManager : public SubsystemInterface { public: SnowManager(); virtual ~SnowManager(); virtual void init(); virtual void targetSlot2(); virtual void targetSlot3(); virtual void targetSlot4(); virtual void targetSlot5(); virtual void targetSlot6(); virtual void targetSlot7(); virtual void targetSlot8(); virtual void reset(); virtual void update(); virtual void targetSlot11(); virtual void targetSlot12(); virtual void targetSlot13(); virtual void updateIniSettings(); protected: float *m_startingHeights; float m_time, m_velocity, m_fullTimePeriod; float m_frequencyScaleX, m_frequencyScaleY, m_amplitude, m_pointSize; float m_maxPointSize, m_minPointSize, m_quadSize, m_boxDimensions, m_emitterSpacing; bool m_isVisible; unsigned char m_targetFlag41; unsigned char m_targetPad42[2]; unsigned int m_targetDword44; float m_targetFloat48, m_targetFloat4C; unsigned char m_targetFlag50; unsigned int m_targetDword54, m_targetDword58; float m_targetFloat5C, m_targetFloat60, m_targetFloat64, m_targetFloat68, m_targetFloat6C, m_targetFloat70; };
class AsciiString { public: const char *m_data; const char *str() const { return m_data ? m_data + 8 : ""; } };
class Overridable { public: virtual ~Overridable(); Overridable *m_nextOverride; bool m_isOverride; const Overridable *getFinalOverride() const { return m_nextOverride ? m_nextOverride->getFinalOverride() : this; } };
class WeatherSetting : public Overridable { public: unsigned char m_pad0C[0x0C]; AsciiString m_snowTexture; unsigned char m_target1C[0x28]; bool m_usePointSprites; bool m_snowEnabled; };
template<class T> class OVERRIDE { public: const T *m_object; operator const T *() const { if (!m_object) return 0; return static_cast<const T *>(m_object->getFinalOverride()); } const T *operator->() const { if (!m_object) return 0; return static_cast<const T *>(m_object->getFinalOverride()); } };
extern OVERRIDE<WeatherSetting> TheWeatherSetting;
struct BfmePointSpriteCapsView { unsigned char m_pad[0x2A9]; bool m_supportPointSprites; bool Support_PointSprites() const { return m_supportPointSprites; } };
extern BfmePointSpriteCapsView *g_currentCaps;
struct IDirect3DDevice9 { virtual void Slot00()=0; virtual void Slot04()=0; virtual void Slot08()=0; virtual void Slot0c()=0; virtual void Slot10()=0; virtual void Slot14()=0; virtual void Slot18()=0; virtual void Slot1c()=0; virtual void Slot20()=0; virtual void Slot24()=0; virtual void Slot28()=0; virtual void Slot2c()=0; virtual void Slot30()=0; virtual void Slot34()=0; virtual void Slot38()=0; virtual void Slot3c()=0; virtual void Slot40()=0; virtual void Slot44()=0; virtual void Slot48()=0; virtual void Slot4c()=0; virtual void Slot50()=0; virtual void Slot54()=0; virtual void Slot58()=0; virtual void Slot5c()=0; virtual void Slot60()=0; virtual void Slot64()=0; virtual long __stdcall CreateVertexBuffer(unsigned int, unsigned int, unsigned long, unsigned long, IDirect3DVertexBuffer9 **, void **)=0; };
extern IDirect3DDevice9 *g_d3dDevice;
class DX8Wrapper { public: static BfmePointSpriteCapsView *Get_Current_Caps() { return g_currentCaps; } static IDirect3DDevice9 *_Get_D3D_Device8() { return g_d3dDevice; } };
class IndexBufferClass : public IndexBuffer { public: class WriteLockClass { IndexBufferClass *m_indexBuffer; unsigned short *m_indices; BFMEDX8DeviceLock m_deviceLock; public: WriteLockClass(IndexBufferClass *, int); ~WriteLockClass(); unsigned short *Get_Index_Array() { return m_indices; } }; };
class DX8IndexBufferClass : public IndexBufferClass { unsigned char m_targetTail[16]; public: enum UsageType { USAGE_DEFAULT = 0 }; DX8IndexBufferClass(unsigned int, UsageType); };
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, int, int);
class W3DSnowManager : public SnowManager { public: virtual ~W3DSnowManager(); virtual void init(); virtual void reset(); virtual void updateIniSettings(); virtual void update(); bool ReAcquireResources(); void ReleaseResources(); private: DX8IndexBufferClass *m_indexBuffer; CursorTextureSlot m_snowTexture; IDirect3DVertexBuffer9 *m_vertexBuffer; unsigned int m_dwBase, m_dwFlush, m_dwDiscard; unsigned int m_leafDim; float m_snowCeiling, m_heightTraveled, m_targetFloat98, m_targetFloat9C; unsigned int m_totalRendered; float m_cullOverscan; unsigned int m_targetDwordA8, m_targetDwordAC; };
typedef char SnowBaseSizeCheck[sizeof(SnowManager)==0x74?1:-1]; typedef char SnowDerivedSizeCheck[sizeof(W3DSnowManager)==0xB0?1:-1];

void W3DSnowManager::ReleaseResources() { BFMEDX8DeviceLock lock; m_snowTexture.clear(); if (m_vertexBuffer) m_vertexBuffer->Release(); m_vertexBuffer = 0; if (m_indexBuffer) { m_indexBuffer->Release_Ref(); m_indexBuffer = 0; } }
bool W3DSnowManager::ReAcquireResources() {
    BFMEDX8DeviceLock lock;
    ReleaseResources();
    if (!TheWeatherSetting->m_snowEnabled || !m_targetFlag41) return true;
    if (TheWeatherSetting->m_usePointSprites && DX8Wrapper::Get_Current_Caps()->Support_PointSprites()) {
        IDirect3DDevice9 *device=DX8Wrapper::_Get_D3D_Device8();
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
    m_dwBase=4096; m_dwDiscard=4096; m_dwFlush=2048;
    return true;
}
