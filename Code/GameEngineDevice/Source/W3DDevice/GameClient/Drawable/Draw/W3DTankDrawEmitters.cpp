// ?createEmitters@W3DTankDraw@@IAEXXZ
// Retail CE837..CE960 is the 297-byte createEmitters body called by the
// independently rowed W3DTankDraw constructor CEA6C and tail wrapper CEA4B.
// Reference: BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d,
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDrawCreateEmitters.cpp;
// Zero Hour W3DTankDraw.cpp provides the same two-emitter sequence. Target
// fields: handles2E8/2F4, moduleData4 names188/18C, drawable8. Each is
// observed in this body and independently corroborated by constructor/dtor.
// The native handle temporary conditionally calls the existing 4CBC0 unlink
// helper via RvaSmartPtr12::rva0004CBC0, as in ParticleSystemManagerFindByID.
// Callees use existing neutral providers for drawable-ID attachment and the
// stop byte setter; their original method names remain donor facts. No new pins.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

typedef bool Bool;
enum { FALSE = 0, TRUE = 1 };

class ParticleSystemTemplate;
class Rva0055A88BDwordField;

class Rva001F3C20Slot { public: void set(const Rva0055A88BDwordField *) throw(); };
class Rva001F3852ByteOneSetter { public: void enable() throw(); };
class ParticleSystem : public Rva001F3C20Slot
{
public:
	void rva001F45F4(Bool enabled) throw();
};

ParticleSystem *Make001FCBD7(void);

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that) throw();
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	__forceinline ~BfmeParticleSystemHandle() throw() { if(m_system) rva0004CBC0(); }
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
			((Rva001F3852ByteOneSetter *)m_treadDebrisLeft.operator->())->enable();
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
			((Rva001F3852ByteOneSetter *)m_treadDebrisRight.operator->())->enable();
		}
	}
}
