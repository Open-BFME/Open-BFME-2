// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /arch:SSE2
// ??0Rva005635CD@@QAE@XZ @0x005635CD 17B: empty publisher default ctor calling RENDEROBJECT_DRAW getInstance 0x003AA57C then Rva005C7889Init 0x005C7889 returning this with esi save.
// Evidence: chain lane (calls 0x005C7889 just landed); push esi mov esi ecx call call mov eax esi pop esi ret; static-init caller 0x003A8454 constructs g_00E02934 via this ctor with guard+atexit; getInstance row 0x003AA57C.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class RenderObjectDrawModule;
class RenderObjectDrawModuleTemplate;
extern const char *const RENDEROBJECT_DRAW_MODULE_KEY;
extern const char *const RENDEROBJECT_DRAW_MODULE_NAME;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
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
typedef ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6> > RenderObjectDrawTag6;
}

void __cdecl Rva005C7889Init(void);

class Rva005635CD
{
public:
	Rva005635CD();
	~Rva005635CD();
};

Rva005635CD::Rva005635CD()
{
	FXParticleSystem::ConcreteModuleClass<FXParticleSystem::RenderObjectDrawTag6>::getInstance();
	Rva005C7889Init();
}

void __cdecl Rva003A8454Init()
{
    static Rva005635CD publisher;
}

// BFME1 donor1281192 S5StaticLatches.cpp establishes the local-static pattern.
// Target Ghidra3A8454/64 calls the rowed ctor5635CD for E02934 under
// guardE02938, registers callback7B7E99 and has handler781CE2. Callback
//7B7E99 loads that receiver then tail-jumps to shared RET B3FD0. Its empty
// nonvirtual destructor ABI matches the existing rowed Coord3D destructor;
// the publisher original name and receiver extent remain unknown.
#pragma comment(linker, "/alternatename:??1Rva005635CD@@QAE@XZ=??1Coord3D@@QAE@XZ")

// Compiler-emitted atexit callback _$E2 at0x007B7E99/10 loads receiverE02934
// and tail-jumps to the independently verified empty destructor B3FD0.
