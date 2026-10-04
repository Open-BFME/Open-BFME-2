// cl: /O1 /EHsc /arch:SSE2
// ??0Rva0055C8BC@@QAE@XZ, retail 0x0055C8BC 71B.
// Empty publisher ctor: DefaultModuleTag6 getInstance plus Rva005C7889Init then
// new PointGroupClass (0x5c) into g_00E06098. Evidence: guarded init caller
// 0x003A8314 plus same S4 publisher shape as 0x00560135,
// callee rows 0x003AA350 0x005C7889 0x0002FDA0 0x00178E50.
namespace FXParticleSystem
{
template <int N>
class DefaultModuleTag
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
}
void __cdecl Rva005C7889Init(void);
void *__cdecl operator new(unsigned int);
class PointGroupClass
{
public:
    PointGroupClass();
    virtual ~PointGroupClass();
private:
    char m_pad[0x58];
};
typedef char CheckPointGroupSize[(sizeof(PointGroupClass) == 0x5c) ? 1 : -1];
extern PointGroupClass *g_00E06098;
// g_00E06098: matched references place it at VA 0xe06098 (zero-filled .bss).
PointGroupClass * g_00E06098;
struct Rva0055C8BC
{
    Rva0055C8BC();
    ~Rva0055C8BC();
};
Rva0055C8BC::Rva0055C8BC()
{
    FXParticleSystem::ConcreteModuleClass<FXParticleSystem::DefaultModuleTag<6> >::getInstance();
    Rva005C7889Init();
    PointGroupClass *group = new PointGroupClass;
    g_00E06098 = group;
}

// Reference source: complete clean BFME1 S5StaticLatches.cpp at
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies the local-static pattern.
// Target full Ghidra64B at3A8314 and named FX staticInitModules3AE381 call
// independently establish the guarded initializer; native ctor55C8BC and
// cleanup7B7ECB -> dtor55C45F establish this publisher lifecycle.
// The empty receiver view is retained from the already rowed constructor;
// original publisher identity and complete application layout remain unknown.
void __cdecl Rva003A8314Init()
{
    static Rva0055C8BC publisher;
}

// Target full Ghidra25B at55C45F is called by native cleanup7B7ECB.
// It destroys the object in the same global E06098 populated by the rowed
// publisher constructor: virtual destructor flag0 then global delete2FD60.
// Global-qualified delete is required by that independently observed call shape.
Rva0055C8BC::~Rva0055C8BC()
{
    ::delete g_00E06098;
}
