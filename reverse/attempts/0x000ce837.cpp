// ?createEmitters@W3DTankDraw@@IAEXXZ
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

typedef bool Bool;
enum { FALSE = 0, TRUE = 1 };

class ParticleSystemTemplate;
class Rva0055A88BDwordField;

class ParticleSystem
{
public:
	void set(const Rva0055A88BDwordField *field) throw();
	void rva001F45F4(Bool enabled) throw();
	void enable() throw();
};

ParticleSystem *Make001FCBD7(void);

class RvaSmartPtr12
{
public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that) throw();
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	~BfmeParticleSystemHandle() throw();
	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make001FCBD7();
		return m_system;
	}
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const throw();
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class Thing;
class ModuleData;
class RenderObjClass;

class W3DTankDrawModuleData
{
public:
	char m_pad00[0x188];
	AsciiString m_treadDebrisNameLeft;
	AsciiString m_treadDebrisNameRight;
};

struct W3DTankDrawDebrisHandle
{
	void *m_ptr0;
	void *m_ptr1;
	void *m_ptr2;
};

class DrawModuleBase
{
public:
	virtual ~DrawModuleBase();
private:
	char m_pad04[8];
};

class DrawInterfaceA { public: virtual void a(); };
class DrawInterfaceB { public: virtual void b(); };

class W3DScriptedModelDrawPrimaryBase
{
public:
	virtual void slot();
	W3DTankDrawModuleData *m_moduleData;
	Rva0055A88BDwordField *m_drawable;
};

class W3DScriptedModelDraw : public W3DScriptedModelDrawPrimaryBase,
	public DrawInterfaceA, public DrawInterfaceB
{
private:
	char m_pad14[0x2E8 - 0x14];
};

class W3DTankDraw : public W3DScriptedModelDraw
{
protected:
	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
	void createEmitters();
};

void W3DTankDraw::createEmitters()
{
	Bool disabled = FALSE;
	ParticleSystem *nullSystem = 0;
	if (m_treadDebrisLeft.m_system == nullSystem)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(
			m_moduleData->m_treadDebrisNameLeft);
		if (sysTemplate)
		{
			m_treadDebrisLeft = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			Rva0055A88BDwordField *drawable = m_drawable;
			m_treadDebrisLeft->set(drawable);
			m_treadDebrisLeft->rva001F45F4(disabled);
			m_treadDebrisLeft->enable();
		}
	}
	if (!m_treadDebrisRight)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(
			m_moduleData->m_treadDebrisNameRight);
		if (sysTemplate)
		{
			m_treadDebrisRight = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			Rva0055A88BDwordField *drawable = m_drawable;
			m_treadDebrisRight->set(drawable);
			m_treadDebrisRight->rva001F45F4(disabled);
			m_treadDebrisRight->enable();
		}
	}
}
