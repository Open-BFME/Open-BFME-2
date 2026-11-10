// cl: /DNDEBUG /MD /EHsc /Ob2
//
// BFME's W3DVideoBuffer grew beyond the Zero Hour layout.  The matched
// W3DDisplay::createVideoBuffer(bool) caller allocates 0x4c bytes and calls
// this constructor through ILT 0x0002b733.  Retail's VideoBuffer initializer
// writes the prefix through +0x28; the derived constructor then builds one
// nontrivial 0x14-byte state at +0x2c, points +0x40/+0x44 at it, and clears
// the three flags at +0x48..+0x4a.
//
// The state layout is independently exercised by the matched cleanup family
// at 0x00739c70..0x00739f00: +8 owns a texture reference, +0xc owns a surface
// handle, and +0x10 is its flags word.  Public names for this BFME-only state
// and the Display registration method were not recovered, so their names stay
// address-derived while retaining their proven data and calling ABIs.

class TextureClass;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

#include "../../../../GameEngine/Include/Common/Rva000724AE.h"

class W3DVideoSurfaceHandle
{
public:
	W3DVideoSurfaceHandle() : m_surface(0) {}
	~W3DVideoSurfaceHandle() {}
private:
	void *m_surface; // +0x00
};

class Rva00739C70State
{
public:
	// Retail's element ctor 0x000724A0 zeroes +8, +0xC and +0x10; +0 and +4 are left.
	Rva00739C70State() : m_texture(0), m_surface(), m_flags(0) {}
	~Rva00739C70State() {}
private:
	int m_value_00; // +0x00
	int m_value_04; // +0x04
	TextureClass *m_texture; // +0x08
	W3DVideoSurfaceHandle m_surface; // +0x0C
	unsigned int m_flags; // +0x10
};

class Rva00739C70
{
public:
    void cleanup();
};

class VideoBuffer
{
public:
    VideoBuffer(int format);
    virtual void slot0() = 0;
    // Nothing to tear down in this view: retail's constructor has no unwind state for this base.
    virtual ~VideoBuffer() {}

protected:
    unsigned int m_x_pos;
    unsigned int m_y_pos;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_texture_width;
    unsigned int m_texture_height;
    unsigned int m_pitch;
    float m_value_20;
    int m_format;
    bool m_flag_28;
};

#include "../../../../GameEngine/Include/GameClient/Display.h"

extern Display *TheDisplay;

// The rows in retail's table 0x007C64D8. None has stack arguments, and each takes this object in ecx.
extern "C" {
void __identifier("?bfmeSwapBits@Gen_0073A2E0@@QAEXXZ")();
void __identifier("?rva00072559@Rva00072559@@QAEXXZ")();
bool __identifier("?rva00072566@Rva00072566@@UAE_NXZ")();
int __identifier("?get@Rva00072756MaskedChaseField@@QBEHXZ")();
int *__identifier("?rva00072740@Rva00072740@@QAEPAHXZ")();
int *__identifier("?rva0007274B@Rva00072740@@QAEPAHXZ")();
}
class BfmeOwnerCC { public: virtual ~BfmeOwnerCC(); };

// The slots in retail's order, since the constructor installs the table built from them.
class W3DVideoBuffer : public VideoBuffer
{
public:
    W3DVideoBuffer(int format);
    __declspec(noinline) virtual void slot0() { __identifier("?bfmeSwapBits@Gen_0073A2E0@@QAEXXZ")(); }
    __declspec(noinline) virtual ~W3DVideoBuffer() { ((BfmeOwnerCC *)this)->BfmeOwnerCC::~BfmeOwnerCC(); }
    virtual bool allocate(unsigned int width, unsigned int height, bool flag);
    __declspec(noinline) virtual void slot3() { rva00072583(); }
    __declspec(noinline) virtual void slot4() { __identifier("?rva00072559@Rva00072559@@QAEXXZ")(); }
    virtual void Rva000723FB();
    __declspec(noinline) virtual bool slot6() { return __identifier("?rva00072566@Rva00072566@@UAE_NXZ")(); }
    __declspec(noinline) virtual int slot7() { return __identifier("?get@Rva00072756MaskedChaseField@@QBEHXZ")(); }
    virtual bool slot8() { return false; }
    __declspec(noinline) virtual int *slot9() { return __identifier("?rva00072740@Rva00072740@@QAEPAHXZ")(); }
    __declspec(noinline) virtual int *slot10() { return __identifier("?rva0007274B@Rva00072740@@QAEPAHXZ")(); }
    virtual void Rva00072472();
    virtual void Rva00072480();
    void rva00072583();

private:
    Rva00739C70State m_states[1];
    Rva00739C70State *m_state_40;
    Rva00739C70State *m_state_44;
    bool m_flag_48;
    bool m_flag_49;
    bool m_flag_4a;
};

W3DVideoBuffer::W3DVideoBuffer(int format)
    : VideoBuffer(format),
      m_state_40(m_states),
      m_state_44(m_states),
      m_flag_48(false),
      m_flag_49(false),
      m_flag_4a(false)
{
    if (TheDisplay != 0) {
        TheDisplay->Rva006F2890RegisterVideoBuffer(this);
    }
}

// ?Rva000723FB@W3DVideoBuffer@@UAEXXZ @0x000723FB 17B
// Virtual slot 5 (offset 0x14) of vtable 0x007C64D8 (class of ??0W3DVideoBuffer).
// Calls rowed ?cleanup@Rva00739C70@@QAEXXZ on +0x44 then sets +0x28 to 1.
// Same shape as Owner00739C90::cleanup; offsets match W3DVideoBuffer layout
// (m_state_44 at +0x44 via vptr; m_flag_28 at +0x28).
void W3DVideoBuffer::Rva000723FB()
{
    ((Rva00739C70 *)m_state_44)->cleanup();
    m_flag_28 = true;
}

// ?Rva00072472@W3DVideoBuffer@@UAEXXZ @0x00072472 14B
// Virtual slot 11 (offset 0x2C) of vtable 0x007C64D8 (class of ??0W3DVideoBuffer).
// Calls slot 3 (offset 0xC, retail 0x00072583) then sets +0x4A to 1.
void W3DVideoBuffer::Rva00072472()
{
    slot3();
    m_flag_4a = true;
}

// ?rva00072583@W3DVideoBuffer@@QAEXXZ, RVA 0x00072583, 57B. Virtual slot 3
// (offset 0xC) of vtable 0x007C64D8. Guarded reset: device lock guard then
// triple-clear of the 0x10-byte state at +0x2c via rowed 0x724AE and clear
// of flag +0x4a. Evidence: chain from 0x724AE; caller at 0x72828; same
// lock/clear shape as sibling video-buffer methods.
void W3DVideoBuffer::rva00072583()
{
    BFMEDX8DeviceLock guard;
    reinterpret_cast<Rva000724AE*>(m_states)->rva000724AE();
    m_flag_4a = false;
}
