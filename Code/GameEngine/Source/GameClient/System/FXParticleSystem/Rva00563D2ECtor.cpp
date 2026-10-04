// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /arch:SSE2
// ??0Rva00563D2E@@QAE@XZ @0x00563D2E 17B: empty publisher default ctor calling GPU_DRAW getInstance 0x003AA652 then Rva005C7889Init 0x005C7889 returning this with esi save.
// Evidence: chain lane (calls 0x005C7889 just landed); push esi mov esi ecx call call mov eax esi pop esi ret; static-init caller 0x003A8494 constructs g_00E0293C via this ctor with guard+atexit; getInstance row 0x003AA652.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class GpuDrawModule;
class GpuDrawModuleTemplate;
extern const char *const GPU_DRAW_MODULE_KEY;
extern const char *const GPU_DRAW_MODULE_NAME;
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
typedef ModuleTag<6, GPU_DRAW_MODULE_KEY, GPU_DRAW_MODULE_NAME, GpuDrawModule, GpuDrawModuleTemplate, DefaultParticleModule<6> > GpuDrawTag6;
}

void __cdecl Rva005C7889Init(void);

class Rva00563D2E
{
public:
	Rva00563D2E();
	~Rva00563D2E();
};

Rva00563D2E::Rva00563D2E()
{
	FXParticleSystem::ConcreteModuleClass<FXParticleSystem::GpuDrawTag6>::getInstance();
	Rva005C7889Init();
}

void __cdecl Rva003A8494Init()
{
    static Rva00563D2E publisher;
}

// BFME1 donor1281192 S5StaticLatches.cpp establishes the local-static pattern.
// Target Ghidra3A8494/64 calls the rowed ctor563D2E for E0293C under
// guardE02940, registers callback7B7E8F and has handler781CF9. Callback
//7B7E8F loads that receiver then tail-jumps to shared RET B3FD0. Its empty
// nonvirtual destructor ABI matches the existing rowed Coord3D destructor;
// the publisher original name and receiver extent remain unknown.
#pragma comment(linker, "/alternatename:??1Rva00563D2E@@QAE@XZ=??1Coord3D@@QAE@XZ")
