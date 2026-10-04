// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE
// ??0Rva00561D3D@@QAE@XZ @ 0x00561D3D 87B unlock via rowed getInstance Init new StreakLine.
// Honest-address default ctor for static at 0x00E0291C (caller 0x003A8394 guards at 0x00E02920).
// Evidence: EH prologue, rowed getInstance LIGHTNING_DRAW 0x003AA5A7, rowed Init 0x005C7889,
// rowed new 0x0002FDA0 with 0x19c, rowed StreakLine ctor 0x00742470,
// rowed Set_Texture_Mapping_Mode 0x007419A0 with 2, global g_00E0626C, returns this.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE,
    class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
template <class TAG>
class ConcreteModuleClass
{
public:
    __declspec(noinline) static const ConcreteModuleClass<TAG> &getInstance();
};
extern const char *const LIGHTNING_DRAW_MODULE_KEY;
extern const char *const LIGHTNING_DRAW_MODULE_NAME;
class LightningDrawModule;
class LightningDrawModuleTemplate;
typedef ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule,
    LightningDrawModuleTemplate, DefaultParticleModule<6> > LightningDrawTag5;
}
void __cdecl Rva005C7889Init();
class SegLineRendererClass
{
public:
    enum TextureMapMode
    {
        MODE0 = 0,
        MODE1 = 1,
        MODE2 = 2
    };
};
// Primary counter+4 / virtual disposal-slot0 proven by native561543.
// Total native new extent19C is preserved; the remaining fields stay opaque.
class RefCountClass
{
public:
    virtual void Delete_This();
    virtual ~RefCountClass();
    int NumRefs;
    // Same donor inline operation; emitted10B also matches native5D1A7D.
    void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
};
class StreakLineClass : public RefCountClass
{
public:
    StreakLineClass();
    void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode);
private:
    char m_pad[0x194];
};
class Rva00561D3D
{
public:
    Rva00561D3D();
    ~Rva00561D3D();
};
// Native ctor and dtor share this zero-filled pointer at E0626C.
StreakLineClass *g_00E0626C;
Rva00561D3D::Rva00561D3D()
{
    FXParticleSystem::ConcreteModuleClass<FXParticleSystem::LightningDrawTag5>::getInstance();
    Rva005C7889Init();
    StreakLineClass *p = new StreakLineClass;
    g_00E0626C = p;
    p->Set_Texture_Mapping_Mode((SegLineRendererClass::TextureMapMode)2);
}

// Reference sources: whole clean BFME1 S5StaticLatches.cpp and refcount.h
// at1281192f682ce6f29b8f06b7daea4b5e8fdfbb24. Target initializer full64B
// and native FX staticInitModules3AE381 call prove local-static entry.
// Native atexit callback independently names the publisher destructor;
// release/null behavior and counter+4 disposal-slot0 are target facts.
// Original publisher identity and complete receiver layout remain unknown.
void __cdecl Rva003A8394Init()
{
    static Rva00561D3D publisher;
}
// Native 00561543 release/null destructor via observed cleanup callback.
Rva00561D3D::~Rva00561D3D()
{
    if (g_00E0626C) {
        g_00E0626C->Release_Ref();
        g_00E0626C = 0;
    }
}
