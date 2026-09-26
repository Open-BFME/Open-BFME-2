// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0CursorParticleSystemFXNugget@@QAE@XZ 157B @0x001E0C90: no-arg ctor called
// by CursorParticleSystemFXNugget::parse (0x001E26F5) for the
// CursorParticleSystem FXList keyword; class name from BFME1. Member names
// and offsets from the retail FieldParse table 0x00BDD600
// (Anim2DTemplateName@0x148 BurstCount@0x14C ParticleLife@0x150 SystemLife@0x15C
// DriftVelX@0x168 DriftVelY@0x174) and the BFME1 donor
// (CursorParticleSystemFXNuggetConstructor: type 12 burst 10 name clear plus
// four GameClientRandomVariables). Base 0x001DFEAA is a shared
// FXNugget-family base ctor; pinned opaquely. Vtable 0x00BDD91C. News 0x180
// builder 0x001DFD36.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
protected:
	int m_nuggetType; // +4, nugget type id (BFME1 FXNugget::m_nuggetType)
	unsigned char m_pad[0x148 - 8];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();
private:
	void *m_data;
};

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM,
		GAUSSIAN,
		TRIANGULAR,
		LOW_BIAS,
		HIGH_BIAS
	};

	GameClientRandomVariable()
	{
		m_type = CONSTANT;
		m_low = 0.0f;
		m_high = 0.0f;
	}
	void setRange(float low, float high, DistributionType type);
private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

class CursorParticleSystemFXNugget : public Rva001DFEAABase
{
public:
	CursorParticleSystemFXNugget();
	virtual ~CursorParticleSystemFXNugget();
private:
	AsciiString m_name; // +0x148
	int m_burstCount; // +0x14C
	GameClientRandomVariable m_particleLife; // +0x150
	GameClientRandomVariable m_systemLife; // +0x15C
	GameClientRandomVariable m_driftVelX; // +0x168
	GameClientRandomVariable m_driftVelY; // +0x174
};

CursorParticleSystemFXNugget::CursorParticleSystemFXNugget()
{
	m_nuggetType = 12;
	m_burstCount = 10;
	m_name.clear();
}
