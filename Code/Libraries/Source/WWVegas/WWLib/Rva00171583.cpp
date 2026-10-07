// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00171583@Rva00171583@@QAE_NABIPAUVec2@@1@Z retail 0x00171583 162B unlock lane map-lookup rect scaler
// Evidence: calls rowed _M_find 0x00357180 at +8; flag at +0x1c calls pin 0x001711A6; scales at +0x20/+0x24; floats at node+0x14-0x20; callers 0x000EB40F 0x000E7B3F.
#include <map>

struct Vec2
{
    float x;
    float y;
};

struct GlyphRect
{
    int left;
    int top;
    int right;
    int bottom;
};

class TextureClass;
template <class T> class RefCountPtr;
template <> class RefCountPtr<TextureClass>
{
public:
    RefCountPtr const &operator=(RefCountPtr const &other);
};

class Rva00171024
{
public:
    void rva001711a6();
};

class Rva00171583
{
public:
    bool rva00171583(const unsigned int &key, Vec2 *outSize, Vec2 *outPos);
    bool rva00171540(RefCountPtr<TextureClass> &reference, GlyphRect *out);
private:
    int m_00;
    int m_04;
    _STL::map<unsigned int, GlyphRect> m_map;
    void *m_14;
    int m_18;
    bool m_1c;
    bool m_1d;
    float m_20;
    float m_24;
};

bool Rva00171583::rva00171583(const unsigned int &key, Vec2 *outSize, Vec2 *outPos)
{
    _STL::map<unsigned int, GlyphRect>::iterator it = m_map.find(key);
    if (it == m_map.end())
    {
        outSize->x = 1.0f;
        outSize->y = 1.0f;
        outPos->x = 0.0f;
        outPos->y = 0.0f;
        return false;
    }
    if (m_1c)
        ((Rva00171024 *)this)->rva001711a6();
    outPos->x = (float)(*it).second.left * m_20;
    outPos->y = (float)(*it).second.top * m_24;
    outSize->x = (float)((*it).second.right - (*it).second.left) * m_20;
    outSize->y = (float)((*it).second.bottom - (*it).second.top) * m_24;
    return true;
}

// ?rva00171540@Rva00171583@@QAE_NAAV?$RefCountPtr@VTextureClass@@@@PAUGlyphRect@@@Z
// 0x00171540: target checks the iterator at +0x14 against the map root at
// +0x08 and the validity word at +0x18, after the shared +0x1C refresh call.
// On success it assigns the node's first 4-byte field through rowed 0x000424D0
// and copies the following 16 bytes to the caller. Class and owner identity
// remain unresolved; the output record type follows the adjacent 0x00171583
// layout view.
bool Rva00171583::rva00171540(RefCountPtr<TextureClass> &reference, GlyphRect *out)
{
    if (m_1c)
        ((Rva00171024 *)this)->rva001711a6();
    if (m_14 == *(void **)&m_map)
        return false;
    if (m_18 == 0)
        return false;
    reference = *reinterpret_cast<RefCountPtr<TextureClass> *>((char *)m_14 + 0x10);
    *out = *reinterpret_cast<GlyphRect *>((char *)m_14 + 0x14);
    return true;
}
