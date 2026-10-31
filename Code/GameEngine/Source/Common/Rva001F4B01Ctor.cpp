// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ??0Rva001F4B01@@QAE@XZ, retail 0x001F4A40, 80 bytes.
//
// Evidence: the rowed "Particle" binder dtor (??1Rva001F4B01@@UAE@XZ 0x1F4B01,
// vtable 0x00BE171C, dtor family Rva001F73D5ParticlePhysicsUpdateBinder.cpp)
// and the rowed select 0x1F4A90 leave all four vptrs at the shared base vtable
// 0x00BC6F24, so the object is a four-base hierarchy: the binder primary plus
// the Draw 0x00BE16E8, Physics 0x00BE16F0 and Update 0x00BE16F8 sub-binders
// whose ResolveBindings overrides live in the rowed 0x1F69B1/0x1F73D5/0x1F7740
// bodies. The ctor stores those four vtables and registers the object under
// the "Particle" literal (at VA 0xBE1710) through the rowed
// Rva00153565Register 0x00153565.

class Rva001F4A90HostBase
{
public:
	virtual void slot0();
	virtual void ResolveBindings();
	virtual ~Rva001F4A90HostBase();
};

class ParticleDrawBinder
{
public:
	virtual void slot0();
	virtual void ResolveBindings();
	virtual ~ParticleDrawBinder();
};

class ParticlePhysicsBinder
{
public:
	virtual void slot0();
	virtual void ResolveBindings();
	virtual ~ParticlePhysicsBinder();
};

class ParticleUpdateBinder
{
public:
	virtual void slot0();
	virtual void ResolveBindings();
	virtual ~ParticleUpdateBinder();
};

class Rva001F4B01 : public Rva001F4A90HostBase
{
public:
	Rva001F4B01();
	virtual ~Rva001F4B01();

private:
	ParticleDrawBinder m_draw; // +0x04
	ParticlePhysicsBinder m_physics; // +0x08
	ParticleUpdateBinder m_update; // +0x0C
};

void Rva00153565Register(const char *name, void *object);

Rva001F4B01::Rva001F4B01()
{
	Rva00153565Register("Particle", this);
}
