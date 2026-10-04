// cl: /O1 /EHsc /arch:SSE2
// ??0Rva00560135@@QAE@XZ, retail 0x00560135 74B.
// Empty publisher ctor: STREAK_DRAW getInstance plus Rva005C7889Init then
// new StreakLineClass (0x19c) into g_00E06224. Evidence: guarded init caller
// 0x003A8354 (object VA 0x00E02914 guard VA 0x00E02918 atexit VA 0x007B7EC1),
// callee rows 0x003AA37B 0x005C7889 0x0002FDA0 0x00742470, S4StreakLinePublisher pattern.
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
    static const ConcreteModuleClass<TAG> &getInstance();
private:
    void *m_words[4];
};
extern const char *const STREAK_DRAW_MODULE_KEY;
extern const char *const STREAK_DRAW_MODULE_NAME;
class StreakDrawModule;
class StreakDrawModuleTemplate;
}
void __cdecl Rva005C7889Init(void);
void *__cdecl operator new(unsigned int);
class RefCountClass
{
public:
    virtual void Delete_This();
    virtual ~RefCountClass();
    int NumRefs;
    // Same donor inline operation; emitted10B also matches native5D1A7D.
    void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
};
class MultiListObjectClass
{
public:
    virtual ~MultiListObjectClass();
    void *ListNode;
};
class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
private:
    char m_tail[0xB8];
};
class StreakLineClass : public RenderObjClass
{
public:
    StreakLineClass();
private:
    char m_tail[0xD4];
};
typedef char CheckStreakSize[(sizeof(StreakLineClass) == 0x19c) ? 1 : -1];
extern StreakLineClass *g_00E06224;
// g_00E06224: matched references place it at VA 0xe06224 (zero-filled .bss).
StreakLineClass * g_00E06224;
struct Rva00560135
{
    Rva00560135();
    ~Rva00560135();
};
Rva00560135::Rva00560135()
{
    FXParticleSystem::ConcreteModuleClass<FXParticleSystem::ModuleTag<6, FXParticleSystem::STREAK_DRAW_MODULE_KEY, FXParticleSystem::STREAK_DRAW_MODULE_NAME, FXParticleSystem::StreakDrawModule, FXParticleSystem::StreakDrawModuleTemplate, FXParticleSystem::DefaultParticleModule<6> > >::getInstance();
    Rva005C7889Init();
    StreakLineClass *line = new StreakLineClass;
    g_00E06224 = line;
}

// Reference sources: whole clean BFME1 S5StaticLatches.cpp and refcount.h
// at1281192f682ce6f29b8f06b7daea4b5e8fdfbb24. Target initializer full64B
// and native FX staticInitModules3AE381 call prove local-static entry.
// Native atexit callback independently names the publisher destructor;
// release/null behavior and counter+4 disposal-slot0 are target facts.
// Original publisher identity and complete receiver layout remain unknown.
void __cdecl Rva003A8354Init()
{
    static Rva00560135 publisher;
}

// Native 0055FD4A release/null destructor via observed cleanup callback.
Rva00560135::~Rva00560135()
{
    if (g_00E06224) {
        g_00E06224->Release_Ref();
        g_00E06224 = 0;
    }
}
