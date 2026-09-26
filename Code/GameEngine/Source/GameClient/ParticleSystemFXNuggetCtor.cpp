// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0ParticleSystemFXNugget@@QAE@XZ 392B @0x001E0AEF: no-arg ctor called by
// ParticleSystemFXNugget::parse (0x001E2679) for the ParticleSystem FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD428 (Name@0x148 Count@0x14C Offset@0x150 Radius@0x15C
// Height@0x168 InitialDelay@0x174 RotateX@0x180 RotateY@0x184 RotateZ@0x188
// OrientToObject@0x18C AttachToObject@0x18D AttachToBone@0x190
// CreateAtGroundHeight@0x194 Ricochet@0x195 CreateBoneOverride@0x198
// TargetBoneOverride@0x19C CreateBoneAtTarget@0x1A0 TargetCoeff@0x1A4
// SystemLife@0x1A8 UseTargetOffset@0x1AC SetTargetMatrix@0x1AD
// OnlyIfOnLand@0x1AE OnlyIfOnWater@0x1AF TargetOffset@0x1B0) and the BFME1
// donor (m_name clear plus m_count 1 plus radius and height 0-0 plus delay
// -1--1 plus zero offsets and rotates plus nugget type 8; BFME2 adds tail
// strings floats and bools). Base 0x001DFEAA is a shared FXNugget-family base
// ctor; pinned opaquely. Vtable 0x00BDD908. News 0x1BC builder 0x001DFD15.

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

struct Coord3D
{
	float x;
	float y;
	float z;
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

class ParticleSystemFXNugget : public Rva001DFEAABase
{
public:
	ParticleSystemFXNugget();
	virtual ~ParticleSystemFXNugget();
private:
	AsciiString m_name; // +0x148
	int m_count; // +0x14C
	Coord3D m_offset; // +0x150
	GameClientRandomVariable m_radius; // +0x15C
	GameClientRandomVariable m_height; // +0x168
	GameClientRandomVariable m_delay; // +0x174
	float m_rotateX; // +0x180
	float m_rotateY; // +0x184
	float m_rotateZ; // +0x188
	bool m_orientToObject; // +0x18C
	bool m_attachToObject; // +0x18D
	unsigned char m_pad18E[2]; // +0x18E
	AsciiString m_attachToBone; // +0x190
	bool m_createAtGroundHeight; // +0x194
	bool m_ricochet; // +0x195
	unsigned char m_pad196[2]; // +0x196
	AsciiString m_createBoneOverride; // +0x198
	AsciiString m_targetBoneOverride; // +0x19C
	bool m_createBoneAtTarget; // +0x1A0
	unsigned char m_pad1A1[3]; // +0x1A1
	float m_targetCoeff; // +0x1A4
	int m_systemLife; // +0x1A8
	bool m_useTargetOffset; // +0x1AC
	bool m_setTargetMatrix; // +0x1AD
	bool m_onlyIfOnLand; // +0x1AE
	bool m_onlyIfOnWater; // +0x1AF
	Coord3D m_targetOffset; // +0x1B0
};

ParticleSystemFXNugget::ParticleSystemFXNugget()
{
	m_name.clear();
	m_count = 1;
	m_radius.setRange(0.0f, 0.0f, GameClientRandomVariable::CONSTANT);
	m_height.setRange(0.0f, 0.0f, GameClientRandomVariable::CONSTANT);
	m_delay.setRange(-1.0f, -1.0f, GameClientRandomVariable::CONSTANT);
	m_systemLife = -1;
	m_offset.x = m_offset.y = m_offset.z = 0.0f;
	m_orientToObject = false;
	m_attachToObject = false;
	m_createAtGroundHeight = false;
	m_rotateX = m_rotateY = m_rotateZ = 0.0f;
	m_nuggetType = 8;
	m_targetCoeff = 1.0f;
	m_createBoneAtTarget = false;
	m_useTargetOffset = false;
	m_targetOffset.x = m_targetOffset.y = m_targetOffset.z = 0.0f;
	m_setTargetMatrix = false;
	m_onlyIfOnLand = false;
	m_onlyIfOnWater = false;
	m_ricochet = false;
}
