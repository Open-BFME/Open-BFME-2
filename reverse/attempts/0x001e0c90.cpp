// ??0CursorParticleSystemFXNugget@@QAE@XZ
// partial score=0.89 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0CursorParticleSystemFXNugget@@QAE@XZ 157B @0x1E0C90: no-arg ctor called
// by CursorParticleSystemFXNugget::parse (0x001E26CB) for the
// CursorParticleSystem FXList keyword; class name from BFME1. Member names
// and offsets from the retail FieldParse table 0x00BDD600
// (Anim2DTemplateName@0x148, BurstCount@0x14C, ParticleLife@0x150,
// SystemLife@0x15C, DriftVelX@0x168, DriftVelY@0x174) and the BFME1 donor
// (CursorParticleSystemFXNuggetConstructor: type 12, burst 10, name clear,
// four GameClientRandomVariables). The four variables are addressed through
// a reused local pointer (retail leas each member fresh into eax); the name
// string is nulled through an early-taken pointer whose ecx survives to the
// trailing clear() call (rowed Image-ctor null-plus-clear precedent resolves
// clear via the existing 0x36410 pin). Base 0x001DFEAA is a shared
// FXNugget-family base ctor; pinned opaquely, do not name.

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	~Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_nuggetType; // +4, nugget type id
	unsigned char m_pad[0x148 - 8];
};

class AsciiString
{
public:
	void clear();
	~AsciiString();
public:
	void *m_data;
};

struct GameClientRandomVariable
{
	int m_type;
	float m_min;
	float m_max;
};

class CursorParticleSystemFXNugget : public Rva001DFEAABase
{
public:
	CursorParticleSystemFXNugget();
private:
	AsciiString m_name; // +0x148
	int m_burstCount; // +0x14C
	GameClientRandomVariable m_particleLife; // +0x150
	GameClientRandomVariable m_systemLife; // +0x15C
	GameClientRandomVariable m_driftVelX; // +0x168
	GameClientRandomVariable m_driftVelY; // +0x174
};

// ??0CursorParticleSystemFXNugget@@QAE@XZ
CursorParticleSystemFXNugget::CursorParticleSystemFXNugget()
{
	GameClientRandomVariable *var = &m_particleLife;
	AsciiString *name = &m_name;
	*(unsigned int *)this = 0x00BDD91C;
	name->m_data = 0;
	var->m_type = 0;
	var->m_min = 0.0f;
	var->m_max = 0.0f;
	var = &m_systemLife;
	var->m_type = 0;
	var->m_min = 0.0f;
	var->m_max = 0.0f;
	var = &m_driftVelX;
	var->m_type = 0;
	var->m_min = 0.0f;
	var->m_max = 0.0f;
	var = &m_driftVelY;
	var->m_type = 0;
	var->m_min = 0.0f;
	var->m_max = 0.0f;
	m_nuggetType = 12;
	m_burstCount = 10;
	name->clear();
}
