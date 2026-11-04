// Shared partial BFME 2 Snow resource/weather view.
// Storage offsets come from the existing byte-verified bodies; omitted slots
// and members remain unrecovered. This is not a complete class contract.
#pragma once

#include "ascii_string.h"

// Retail W3DSnowManager's table at VA 0x00BC8144 has the fourteen
// SubsystemInterface slots followed by updateIniSettings at +0x38.
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#undef BFME_SUBSYSTEM_SLOTS

// Only observed virtual slots and fields are represented in these views.
// ReAcquireResources 0x0009390F..0x00093ACB: Zero Hour resource-setup
// algorithm adapted to retail D3D9 COM arguments, weather flags +44/+45,
// 24-byte index buffers and owning texture handles. The verified sibling
// updateIniSettings establishes the derived handle assignment shape; this
// keeps the same +78 holder layout and matches all 444 bytes and bindings.
// Reference reviewed: open-bfme-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
class TextureClass { public: void Release_Ref(); };

class BfmeResetTextureRef {
public:
 TextureClass *Ptr;
 // A local null-init overload keeps the shared default ctor's /G7 copy out
 // of this object, while leaving member initialization visible to callers.
 struct SnowInit {};
 BfmeResetTextureRef(SnowInit):Ptr(0) {}
 void clear();
};

template<class T> class RefCountPtr:public BfmeResetTextureRef {
public:
 RefCountPtr():BfmeResetTextureRef(SnowInit()) {}
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

class SnowManager : public SubsystemInterface {
public:
    SnowManager();
    virtual ~SnowManager();
    virtual void init();
    virtual void reset();
    virtual void updateIniSettings();
protected:
    unsigned char m_targetBase0C[0x14 - 0x0C];
    // Resource-sync methods copy these values as raw bits. Blend/state methods
    // retain their existing float accesses through this same storage.
    int m_14;
    unsigned char m_target18[0x3C - 0x18];
    int m_3c;
    unsigned char m_target40;
    bool m_targetFlag41;
    unsigned char m_target42[0x48 - 0x42];
    int m_48;
    int m_4c;
    bool m_50;
    unsigned char m_target51[0x54 - 0x51];
    int m_54;
    int m_58;
    int m_5c;
    int m_60;
    int m_64;
    int m_68;
    float m_6C;
    float m_70;
};

class DX8IndexBufferClass : public IndexBufferClass { unsigned char m_targetTail[16]; public: enum UsageType { USAGE_DEFAULT = 0 }; DX8IndexBufferClass(unsigned int, UsageType); };

class W3DSnowManager : public SnowManager {
public:
    W3DSnowManager();
    virtual ~W3DSnowManager();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void updateIniSettings();
    void ReleaseResources();
    bool ReAcquireResources();
    float rva000932E1();
    void rva00093349();
    void rva00093457();
    void rva00093B5B();
private:
    void target_0009322D();
    void target_00094652();
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

#include "../../../../GameEngine/Include/Common/Overridable.h"

// Only the getValue receiver address is established for this embedded view.
class GameClientRandomVariable { public: float getValue() const; };

class WeatherSetting : public Overridable {
public:
    unsigned char m_pad10[0x08];
    AsciiString m_snowTexture;
    unsigned char m_target1C[0x3C - 0x1C];
    int m_3c;
    int m_40;
    bool m_usePointSprites;
    bool m_snowEnabled;
    bool m_46;
    unsigned char m_target47[0x4C - 0x47];
    int m_4c;
    int m_50;
    bool m_54;
    unsigned char m_target55[0x58 - 0x55];
    GameClientRandomVariable m_58;
    unsigned char m_target59[0x64 - 0x59];
    int m_64;
    float m_68;
    bool m_6c;
    unsigned char m_target6D[0x70 - 0x6D];
    int m_70, m_74, m_78;
};

template<class T> class OVERRIDE { public: const T *m_object; operator const T *() const { if (!m_object) return 0; return static_cast<const T *>(m_object->getFinalOverride()); } const T *operator->() const { if (!m_object) return 0; return static_cast<const T *>(m_object->getFinalOverride()); } };

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class DX8Caps { public: unsigned char m_pad[0x2A9]; bool m_supportPointSprites; bool Support_PointSprites() const { return m_supportPointSprites; } };

struct IDirect3DDevice8 { virtual void Slot00()=0; virtual void Slot04()=0; virtual void Slot08()=0; virtual void Slot0c()=0; virtual void Slot10()=0; virtual void Slot14()=0; virtual void Slot18()=0; virtual void Slot1c()=0; virtual void Slot20()=0; virtual void Slot24()=0; virtual void Slot28()=0; virtual void Slot2c()=0; virtual void Slot30()=0; virtual void Slot34()=0; virtual void Slot38()=0; virtual void Slot3c()=0; virtual void Slot40()=0; virtual void Slot44()=0; virtual void Slot48()=0; virtual void Slot4c()=0; virtual void Slot50()=0; virtual void Slot54()=0; virtual void Slot58()=0; virtual void Slot5c()=0; virtual void Slot60()=0; virtual void Slot64()=0; virtual long __stdcall CreateVertexBuffer(unsigned int, unsigned int, unsigned long, unsigned long, IDirect3DVertexBuffer8 **, void **)=0; };

class DX8Wrapper { protected: static DX8Caps *CurrentCaps; static IDirect3DDevice8 *D3DDevice; public: static DX8Caps *Get_Current_Caps() { return CurrentCaps; } static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; } };

#include "../../../Include/W3DDevice/GameClient/TextureAsset.h"

class Rva00938C4TextureRef
{
public:
	~Rva00938C4TextureRef()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

