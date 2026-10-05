// cl: /O1 /DNDEBUG /MD /GX-
//
// ?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z, retail
// 0x0055B29C (97B). Zero Hour's ParticleSystemTemplate::parseRandomKeyframe
// (ParticleSys.cpp): low/high reals and the frame (+0x0C) of the keyframe at
// the store, the range set through the rowed
// GameClientRandomVariable::setRange (0x002341E7) with the default UNIFORM
// distribution. Target evidence: the particle-system FieldParse rows Alpha1..
// (0x00C6B988 +0x10 stride, stores +0x0C/+0x1C/..) point here.

typedef float Real;
typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	Real scanReal(const char *token);
	UnsignedInt scanUnsignedInt(const char *token);
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
	void setRange(Real low, Real high, DistributionType type = UNIFORM);
private:
	DistributionType m_type;
	Real m_low;
	Real m_high;
};

struct RandomKeyframe
{
	GameClientRandomVariable var;	// +0x00
	UnsignedInt frame;		// +0x0C
};

class ParticleSystemTemplate
{
public:
	static void parseRandomKeyframe(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z
void ParticleSystemTemplate::parseRandomKeyframe(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	RandomKeyframe *key = static_cast<RandomKeyframe *>(store);

	Real low = ini->scanReal(ini->getNextToken());
	Real high = ini->scanReal(ini->getNextToken());
	key->frame = ini->scanUnsignedInt(ini->getNextToken());

	// set the range of the random variable
	key->var.setRange(low, high);
}
