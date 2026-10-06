// cl: /DNDEBUG /MD /EHsc /Ob2
//
// ?Rva00072480@W3DVideoBuffer@@UAEXXZ @0x00072480 32B
// Virtual slot 12 (offset 0x30) of vtable 0x007C64D8 (class of ??0W3DVideoBuffer@@QAE@H@Z).
// Calls slot 2 (offset 0x8, retail 0x00072760) with (m_width at +0xC, m_height at +0x10,
// m_flag_49 at +0x49) when m_flag_4A is set, then clears m_flag_4A.
// Layout matches W3DVideoBufferCtorBfme.cpp: VideoBuffer prefix through +0x28,
// one 0x14-byte state at +0x2C, pointers at +0x40/+0x44, flags at +0x48..+0x4A.
// Retail 0x72760 takes 3 args (ret 0xC) and returns bool; it is declared here as
// Rva00072760 to reproduce the offset-8 virtual call. No donor covers slot 12.

class TextureClass;

class W3DVideoSurfaceHandle
{
public:
    ~W3DVideoSurfaceHandle();

private:
    void *m_surface;
};

class Rva00739C70State
{
public:
    Rva00739C70State();
    ~Rva00739C70State();

private:
    int m_value_00;
    int m_value_04;
    TextureClass *m_texture;
    W3DVideoSurfaceHandle m_surface;
    unsigned int m_flags;
};

class VideoBuffer
{
public:
    VideoBuffer(int format);
    virtual ~VideoBuffer();
    virtual bool allocate(unsigned int width, unsigned int height);
    virtual bool Rva00072760(unsigned int a, unsigned int b, bool c);
    virtual void *lock();
    virtual void unlock();
    virtual bool valid();

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

class W3DVideoBuffer : public VideoBuffer
{
public:
    W3DVideoBuffer(int format);
    virtual ~W3DVideoBuffer();
    virtual void Rva00072480();

private:
    Rva00739C70State m_states[1];
    Rva00739C70State *m_state_40;
    Rva00739C70State *m_state_44;
    bool m_flag_48;
    bool m_flag_49;
    bool m_flag_4a;
};

void W3DVideoBuffer::Rva00072480()
{
    if (m_flag_4a) {
        Rva00072760(m_width, m_height, m_flag_49);
        m_flag_4a = false;
    }
}
