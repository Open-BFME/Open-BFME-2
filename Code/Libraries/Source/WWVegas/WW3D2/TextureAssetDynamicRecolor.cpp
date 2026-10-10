// cl: /Ob1 /DNDEBUG /MD
// Retail 0x001326EA..0x0013270C: complete 34-byte bool-returning wrapper.
// WB 0x009D3C60..0x009D3C9A tests its packed setting at this+0x40,
// checks the retained source at +0x50 and calls the independently named
// TextureAsset::RecolorFactoryDecal::RecolorTexture at WB 0x009D2F80.
// Retail's existing 0x001321A7 pin identifies that same 1347-byte callee.
// The unsigned one-bit field reproduces the DWORD load, SHR 30 and TEST AL,1;
// a bool or signed field instead emits a different memory-test instruction.
// TextureRecolorView and tryDynamicRecolor are descriptive ABI-view names.
// The unobserved 30-bit prefix and final flag are not assigned semantics.

class BfmeThing937B
{
public:
    void rva001321A7(void *options);
};

class TextureRecolorView
{
    unsigned char m_unobserved00[0x40];
    struct
    {
        unsigned m_unobserved : 30;
        unsigned m_dynamic : 1;
        unsigned m_unobservedLast : 1;
    } m_flags;
    unsigned char m_unobserved44[0x0C];
    void *m_dynamicRecoloringSource;

public:
    bool tryDynamicRecolor(void *options);
};

// ?tryDynamicRecolor@TextureRecolorView@@QAE_NPAX@Z
bool TextureRecolorView::tryDynamicRecolor(void *options)
{
    bool dynamic = m_flags.m_dynamic;
    if (dynamic && m_dynamicRecoloringSource)
    {
        reinterpret_cast<BfmeThing937B *>(this)->rva001321A7(options);
        return true;
    }
    return false;
}
