// cl: /O1 /EHsc

// The template's string accessors. Each returns an AsciiString by value, so the
// copy constructor runs into the caller's slot inside an unwind region - the
// `and dword ptr [ebp-4], 0` ahead of it is the EH state store - which is why
// these cannot sit in FXParticleSystem.cpp with its /GX-.

class AsciiString;

template <typename T>
class StringBase
{
private:
    friend class AsciiString;

    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString
{
public:
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }

    // Declared, never defined: the return object needs cleanup for MSVC to open
    // an unwind region at all, and that state store is the first thing retail
    // does after the frame.
    ~AsciiString();

private:
    char *m_text;
};

struct Region2D
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

namespace FXParticleSystem
{

// Offsets recovered from the accessors themselves: the texture filename is the
// second word of the object and the name sits past the UV rectangle.
class ParticleSystemTemplate
{
public:
    AsciiString getName() const;
    AsciiString getTextureFilename() const;

private:
    char m_unknown00[0x10];
    AsciiString m_textureFilename;
    char m_unknown14[0x74];
    Region2D m_uv;
    char m_unknown98[4];
    AsciiString m_name;
};

AsciiString ParticleSystemTemplate::getName() const
{
    return m_name;
}

AsciiString ParticleSystemTemplate::getTextureFilename() const
{
    return m_textureFilename;
}

}
