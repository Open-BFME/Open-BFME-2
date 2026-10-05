// cl: /O1 /EHsc /arch:SSE2
// ??0ParticleModule005F2CA0@@QAE@PAX0@Z @0x0055C86D 67B: ParticleModule ctor via Rva003AA228 base plus Init.
// Evidence: BFME1 donor ParticleModuleCtor005F2CA0 T1A1+Interface then s4Second; retail base row 0x3AA228 same PAX0 vptr stores +0/+0x14 Init row 0x5C7889; pin names class; 5 matched callers show PAX0.

class RvaSmartPtr12;

class DefaultModuleHeadBase
{
public:
	virtual ~DefaultModuleHeadBase();
private:
	unsigned int m_storage[4];
};

namespace FXParticleSystem
{
class Rva003AA228Slice
{
public:
	virtual void unusedVirtual();
};

class Rva003AA228 : public DefaultModuleHeadBase, public Rva003AA228Slice
{
public:
	Rva003AA228(void *first, void *second);
};
}

class ParticleModule005F2CA0 : public FXParticleSystem::Rva003AA228
{
public:
	ParticleModule005F2CA0(void *first, void *second);
	virtual void moduleSlot();
};

void __cdecl Rva005C7889Init(void);

ParticleModule005F2CA0::ParticleModule005F2CA0(void *first, void *second)
	: Rva003AA228(first, second)
{
	Rva005C7889Init();
}
