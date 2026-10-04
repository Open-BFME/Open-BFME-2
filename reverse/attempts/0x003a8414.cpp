// ?Rva003A8414Init@@YAXXZ
// partial score=0.9375 date=2026-10-04
// BANK: header-split proposal could not pass the full gate because the
// unchanged51d47d324a baseline has4 byte failures plus DIR32/module/source debt.
// A shared Code header is required to avoid private resource copies while
// retaining the native owner ctor EH. No header/full-gate bypass is permitted.
// Native names for the two publisher/resource receiver classes remain unknown.
// cl: /O1 /EHsc /arch:SSE2
// Native opaque resource2C: ctor177825/59 and dtor177860/195.
// The original owner/type names remain unknown. Allocation2C independently
// occurs in target FX publishers560A58 and5613B2. Fields+18..+28 follow the
// complete native ctor; owned pointer prefix/texture14 follows native dtor.
#ifndef BFME_RVA00177860_RESOURCE_H
#define BFME_RVA00177860_RESOURCE_H
class Rva00177860Ref;
class TextureClass
{
public:
	void Release_Ref();
};

class Rva00177860TextureRef
{
public:
	// ?Rva00177860TextureRef::Rva00177860TextureRef present-unmatched
	Rva00177860TextureRef() : m_ptr(0) {}
	// ?Rva00177860TextureRef::~Rva00177860TextureRef present-unmatched
	~Rva00177860TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	TextureClass *m_ptr;
};

class Rva00177860
{
public:
	Rva00177860();
	~Rva00177860();
	Rva00177860Ref *m_00;
	Rva00177860Ref *m_04;
	Rva00177860Ref *m_08;
	Rva00177860Ref *m_0c;
	int m_10;
	Rva00177860TextureRef m_14;
	unsigned int m_18;
	float m_1c, m_20, m_24, m_28;
};

typedef char Rva00177860SizeCheck[sizeof(Rva00177860)==0x2C?1:-1];
#endif

// Whole BFME1 S4StreakLinePublisher pattern, adapted from independently
// decoded target two new2C opaque resources and the rowed named module calls.
namespace FXParticleSystem {
template<int CATEGORY> class DefaultParticleModule;
template<int CATEGORY, const char *const &KEY, const char *const &NAME,
 class MODULE, class TEMPLATE, class DEFAULT> class ModuleTag {};
template<class TAG> class ConcreteModuleClass {
 public: static const ConcreteModuleClass<TAG> &getInstance();
};
extern const char *const QUAD_DRAW_MODULE_KEY;
extern const char *const QUAD_DRAW_MODULE_NAME;
extern const char *const BUTTERFLY_DRAW_MODULE_KEY;
extern const char *const BUTTERFLY_DRAW_MODULE_NAME;
class QuadDrawModule; class QuadDrawModuleTemplate;
class ButterflyDrawModule; class ButterflyDrawModuleTemplate;
typedef ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME,
 QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6> > QuadTag;
typedef ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME,
 ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6> > ButterflyTag;
}
void __cdecl Rva005C7889Init();
struct Rva00560A58 { Rva00560A58(); ~Rva00560A58(); };
struct Rva005613B2 { Rva005613B2(); ~Rva005613B2(); };
Rva00177860 *g_00E0623C;
Rva00177860 *g_00E06254;
// ?Rva00560A58::Rva00560A58 present-unmatched
Rva00560A58::Rva00560A58() {
 FXParticleSystem::ConcreteModuleClass<FXParticleSystem::QuadTag>::getInstance();
 Rva005C7889Init();
 g_00E0623C = new Rva00177860;
}
// ?Rva005613B2::Rva005613B2 present-unmatched
Rva005613B2::Rva005613B2() {
 FXParticleSystem::ConcreteModuleClass<FXParticleSystem::ButterflyTag>::getInstance();
 Rva005C7889Init();
 g_00E06254 = new Rva00177860;
}
// ?Rva00560A58::~Rva00560A58 present-unmatched
Rva00560A58::~Rva00560A58() { delete g_00E0623C; }
// ?Rva005613B2::~Rva005613B2 present-unmatched
Rva005613B2::~Rva005613B2() { delete g_00E06254; }
// ?Rva003A83D4Init present-unmatched
void Rva003A83D4Init() { static Rva00560A58 publisher; }
// ?Rva003A8414Init present-unmatched
void Rva003A8414Init() { static Rva005613B2 publisher; }
