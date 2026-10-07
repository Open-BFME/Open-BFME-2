// cl: /O1 /DNDEBUG /MD /GX
//
// ??1LaserUpdate@@UAE@XZ, retail 0x00362F64, 95 bytes. Dtor of the LaserUpdate
// class whose ctor is rowed at 0x00362EEE (vtable 0x00C170E0, slot 0 deleting
// dtor at 0x00363177 calls here).
//
// Donor: BFME1 LaserUpdateDestructorAndRadius.cpp and ZH LaserUpdate.cpp
// LaserUpdate::~LaserUpdate destroys the two ParticleSystemIDs at +0x28 and
// +0x2C through TheParticleSystemManager->destroyParticleSystemByID (pinned
// 0x001F5B79); retail then restores the intermediate vtable 0x00C170A4 and
// tail-calls the opaque fold-point base at 0x0049B47C via the Rva0049B47C pin
// (rowed as ??1WindModuleInfo@FXParticleSystem@@UAE@XZ). Layout follows the
// rowed ctor TU (opaque 0x0C base plus derived IDs at +0x28/+0x2C); the
// C170A4 restore is hand-placed so the 95B shape matches with EH states.

extern "C" const void *const vtbl_00C170A4[];  // folded, 2 classes; via ??_7Rva00362EC7@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C170A4=??_7Rva00362EC7@@6B@")

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Drawable;
class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	protected:
	char m_pad04[4];
	Drawable *m_drawable;
};

class LaserUpdate : public Rva0049B47C
{
public:
	virtual ~LaserUpdate();
	float getCurrentLaserRadius() const;

private:
	char m_pad0C[0x28 - 0x0C];
	ParticleSystemID m_particleSystemID;
	ParticleSystemID m_targetParticleSystemID;
	char m_pad30[0x3C - 0x30];
	float m_currentWidthScalar;
	char m_pad40[0x54 - 0x40];
};

LaserUpdate::~LaserUpdate()
{
	if (m_particleSystemID != INVALID_PARTICLE_SYSTEM_ID)
		TheParticleSystemManager->destroyParticleSystemByID(m_particleSystemID);
	if (m_targetParticleSystemID != INVALID_PARTICLE_SYSTEM_ID)
		TheParticleSystemManager->destroyParticleSystemByID(m_targetParticleSystemID);
	*(void **)this = (void *)((unsigned int)vtbl_00C170A4);
}

// BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/Update/LaserUpdateDestructorAndRadius.cpp.
// Target ctor and named pool key independently identify LaserUpdate; native
// draw module query is slot +0xBC (BFME1 +0xB0), drawable at +8 and scale +3C.
// Reuse the existing owner of the folded drawable+14C pointer getter.
class Rva002B224BDwordField { public: int get() const; };
class LaserDrawInterface { public: virtual float getLaserTemplateWidth() const; };
class LaserRadiusDrawModule {
public:
 virtual void unused00();
 virtual void unused01();
 virtual void unused02();
 virtual void unused03();
 virtual void unused04();
 virtual void unused05();
 virtual void unused06();
 virtual void unused07();
 virtual void unused08();
 virtual void unused09();
 virtual void unused0A();
 virtual void unused0B();
 virtual void unused0C();
 virtual void unused0D();
 virtual void unused0E();
 virtual void unused0F();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual void unused16();
 virtual void unused17();
 virtual void unused18();
 virtual void unused19();
 virtual void unused1A();
 virtual void unused1B();
 virtual void unused1C();
 virtual void unused1D();
 virtual void unused1E();
 virtual void unused1F();
 virtual void unused20();
 virtual void unused21();
 virtual void unused22();
 virtual void unused23();
 virtual void unused24();
 virtual void unused25();
 virtual void unused26();
 virtual void unused27();
 virtual void unused28();
 virtual void unused29();
 virtual void unused2A();
 virtual void unused2B();
 virtual void unused2C();
 virtual void unused2D();
 virtual void unused2E();
 virtual LaserDrawInterface *getLaserDrawInterface() const;
};
float LaserUpdate::getCurrentLaserRadius() const
{
    const Drawable *draw = m_drawable;
    for (LaserRadiusDrawModule **d = (LaserRadiusDrawModule **)((const Rva002B224BDwordField *)draw)->get(); *d; ++d)
    {
        LaserDrawInterface *ldi = (*d)->getLaserDrawInterface();
        if (ldi)
            return ldi->getLaserTemplateWidth() * m_currentWidthScalar;
    }
    return 0.0f;
}
