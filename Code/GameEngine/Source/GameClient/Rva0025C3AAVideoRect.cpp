// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0025C3AA@Rva0025C3AA@@QAEXXZ retail 0x0025C3AA (196 bytes, RET).
// A Display-family object (the vtable also carries getWidth/getHeight at
// slots 0x40/0x44 next to Display::setHeight/setWidth, 0x0025C378/0x0025C391)
// letterboxes its video: when the ready byte at +0x10C and the video buffer
// at +0x38 are set, the buffer's aspect ratio (slots 0x2C/0x30) scales the
// display width, the vertical remainder is halved into +0x100, +0xFC is
// cleared, +0x104 takes the display width and +0x108 the scaled extent plus
// the margin. The unsigned display sizes convert with the usual 2^32 fixup.
// Class names are placeholders for the address.
typedef unsigned int UnsignedInt;

class Rva0025C3AAVideo
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual int width();
    virtual int height();
};

class Rva0025C3AA
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual UnsignedInt getWidth();
    virtual UnsignedInt getHeight();
    void rva0025C3AA();

private:
    unsigned char m_pad04[0x38 - 0x04];
    Rva0025C3AAVideo *m_video;          // +0x38
    unsigned char m_pad3c[0xFC - 0x3C];
    float m_fc;                         // +0xFC
    float m_margin;                     // +0x100
    float m_displayWidth;               // +0x104
    float m_extent;                     // +0x108
    bool m_ready;                       // +0x10C
};

void Rva0025C3AA::rva0025C3AA()
{
    if (m_ready && m_video)
    {
        float ratio = (float)m_video->width() / (float)m_video->height();
        float scaled = (float)getWidth() * ratio;
        m_fc = 0.0f;
        m_margin = ((float)getHeight() - scaled) * 0.5f;
        m_displayWidth = (float)getWidth();
        m_extent = scaled + m_margin;
    }
}
