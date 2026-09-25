// cl: /O1 /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// AnimationSoundClientBehaviorModuleData constructor.
// Retail 0x4CA70D (63B) builds the 0x18-byte ModuleData: vtable C5EED0, an
// 8-byte tree at +0x08 (ctor pinned at 0x4CA6DA), and a float at +0x14
// loaded from FLT_MAX (0xBBB8E0) via SSE. The factory at 0x252BC2 (rowed)
// news 0x18 and calls this ctor as its sole caller (pin note). The tree's
// key/value identities are unknown; it is modelled as an opaque header
// pointer plus count to preserve the 8-byte layout. The narrow allocator
// shim is unused here but kept for the forthcoming tree-helper bodies.

class AnimationSoundTree
{
public:
    AnimationSoundTree();
    ~AnimationSoundTree();

private:
    void *m_header;
    unsigned int m_count;
};

class AnimationSoundClientBehaviorModuleDataBase
{
public:
    virtual ~AnimationSoundClientBehaviorModuleDataBase();

private:
    unsigned int m_unmodelled04;
};

class AnimationSoundClientBehaviorModuleData
    : public AnimationSoundClientBehaviorModuleDataBase
{
public:
    AnimationSoundClientBehaviorModuleData();

private:
    AnimationSoundTree m_tree08;
    unsigned int m_unmodelled10;
    float m_value14;
};

AnimationSoundClientBehaviorModuleData::AnimationSoundClientBehaviorModuleData()
    : m_value14(3.402823466e+38F)
{
}
