// cl: /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// AnimationSoundClientBehaviorModuleData constructor.
// Retail 0x4CA70D (63B) builds the 0x18-byte ModuleData: vtable C5EED0,
// a 12-byte tree at +0x08 (ctor rowed at 0x4CA6DA), and a float at +0x14
// loaded from FLT_MAX (0xBBB8E0) via SSE. The factory at 0x252BC2 (rowed)
// news 0x18 and calls this ctor as its sole caller (pin note). The tree's
// key/value identities are unknown; its header, count and comparator storage
// follow the owning TU's existing tree view. The narrow allocator
// shim is unused here but kept for the forthcoming tree-helper bodies.

struct AnimationSoundTreeNode;

class AnimationSoundTree {
public:
	AnimationSoundTree();
	~AnimationSoundTree();
	AnimationSoundTree *rva004CA13D(const void*,const void*);
	AnimationSoundTreeNode *rva004C9FE0(const void*);
public:
	AnimationSoundTreeNode*header;
public:
	unsigned int count;
public:
	char comparator;
public:
	AnimationSoundTreeNode**rva004CA68B(AnimationSoundTreeNode**,const void*);
};

class AnimationSoundClientBehaviorModuleDataBase
{
public:
    virtual ~AnimationSoundClientBehaviorModuleDataBase();

private:
    unsigned int m_unmodelled04;
};

class MultiIniFieldParse;

class AnimationSoundClientBehaviorModuleData
    : public AnimationSoundClientBehaviorModuleDataBase
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    AnimationSoundClientBehaviorModuleData();
    virtual ~AnimationSoundClientBehaviorModuleData();

private:
    AnimationSoundTree m_tree08;
    float m_value14;
};

AnimationSoundClientBehaviorModuleData::AnimationSoundClientBehaviorModuleData()
    : m_value14(3.402823466e+38F)
{
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1AnimationSoundClientBehaviorModuleDataBase@@UAE@XZ=??3@YAXPAX@Z")
