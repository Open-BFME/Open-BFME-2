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

class Rva00171024
{
public:
    void rva001711a6();
};

class Rva00171583
{
public:
    bool rva00171583(const unsigned int &key, Vec2 *outSize, Vec2 *outPos);
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
