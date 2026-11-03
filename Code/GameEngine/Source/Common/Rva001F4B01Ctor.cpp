// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ??0Rva001F4B01@@QAE@XZ, retail 0x001F4A40, 80 bytes.
//
// Evidence: the ctor stores the "Particle" binder's vtable 0x00BE171C at +0 and
// the Draw 0x00BE16E8, Physics 0x00BE16F0 and Update 0x00BE16F8 sub-binder
// vtables at +4/+8/+0xC, then registers the object under the "Particle" literal
// (at VA 0xBE1710) through the rowed Rva00153565Register 0x00153565. Retail's
// tables have two slots each, the layout of the FX parameter binder base
// 0x00BC6F24 = { deleting dtor 0x0047DFF2, __purecall }:
//   0x00BE171C = { ??_GRva001F4B01 0x001F4B47, 0x001F4A90 }
//   0x00BE16E8/F0/F8 = { 0x001F45C3, 0x001F69B1 / 0x001F73D5 / 0x001F7740 }
// 0x001F45C3 is the shared sub-binder deleting dtor (it calls the base dtor
// 0x000E14BD), and the three slot-1 bodies are rowed as
// ParticleFXShaderParameterSourceNamespace::SourceNamespace_{Draw,Physics,
// Update}::ResolveBindings (WorldBuilder string leads). The declarations below
// are the ones the rowed dtor 0x001F4B01
// (Rva001F73D5ParticlePhysicsUpdateBinder_~Rva001F4B01.cpp) compiles, so both
// installing units emit one vtable for each class.
//
// Slot 1 of 0x00BE171C is 0x001F4A90, rowed as the nonvirtual
// ParticleFXShaderParameterSourceNamespace::ResolveBindings(const char *, int,
// int); this class (Rva001F4B01) and that one are not yet reconciled, so, like
// the dtor's unit, this view keeps the slot pure.
class FXShaderParameterBinder;
void Rva00153565Register(const char *name, void *object);

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
class FXShaderParameterSourceNamespace
{
public:
	virtual ~FXShaderParameterSourceNamespace() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

// Default binder (0x00153664) every sub-binder dispatcher calls first.
class FXShaderParameterSourceNamespace_Struct : public FXShaderParameterSourceNamespace
{
public:
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// WorldBuilder names the sub-binders ParticleFXShaderParameterSourceNamespace::SourceNamespace_*.
class ParticleFXShaderParameterSourceNamespace
{
public:
	struct SourceNamespace_Physics;
	struct SourceNamespace_Update;
	struct SourceNamespace_Draw;
};

// "Physics" sub-binder, vtable 0x00BE16F0 (dispatcher 0x001F73D5).
struct ParticleFXShaderParameterSourceNamespace::SourceNamespace_Physics : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "Update" sub-binder, vtable 0x00BE16F8 (dispatcher 0x001F7740).
struct ParticleFXShaderParameterSourceNamespace::SourceNamespace_Update : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "Draw" sub-binder, vtable 0x00BE16E8 (dispatcher 0x001F69B1).
struct ParticleFXShaderParameterSourceNamespace::SourceNamespace_Draw : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// The "Particle" binder, vtable 0x00BE171C, holding the three sub-binders at
// +4/+8/+0xC.
class Rva001F4B01 : public FXShaderParameterSourceNamespace
{
public:
	Rva001F4B01();
	virtual ~Rva001F4B01();
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;

private:
	ParticleFXShaderParameterSourceNamespace::SourceNamespace_Draw m_04;
	ParticleFXShaderParameterSourceNamespace::SourceNamespace_Physics m_08;
	ParticleFXShaderParameterSourceNamespace::SourceNamespace_Update m_0C;
};

Rva001F4B01::Rva001F4B01()
{
	Rva00153565Register("Particle", this);
}
