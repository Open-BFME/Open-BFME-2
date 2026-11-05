// cl: /DNDEBUG /MD /GX-
//
// ?parseRandomKeyframe@?$DefaultModuleTemplate@$00@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z,
// retail 0x0055B29C (97B), retail export 1837: BFME 2 moved Zero Hour's
// ParticleSystemTemplate::parseRandomKeyframe (ParticleSys.cpp) into
// FXParticleSystem's DefaultModuleTemplate<1>: low/high reals and the
// frame (+0x0C) of the keyframe at
// the store, the range set through the rowed
// GameClientRandomVariable::setRange (0x002341E7) with the default UNIFORM
// distribution. Target evidence: the particle-system FieldParse rows Alpha1..
// (0x00C6B988 +0x10 stride, stores +0x0C/+0x1C/..) point here.

typedef float Real;
typedef unsigned int UnsignedInt;

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/GameClient/GameClientRandomVariable.h"

struct RandomKeyframe
{
	GameClientRandomVariable var;	// +0x00
	UnsignedInt frame;		// +0x0C
};

namespace FXParticleSystem
{

template <int CATEGORY>
class DefaultModuleTemplate
{
public:
	static void parseRandomKeyframe(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseRandomKeyframe@?$DefaultModuleTemplate@$00@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
template <int CATEGORY>
void DefaultModuleTemplate<CATEGORY>::parseRandomKeyframe(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	RandomKeyframe *key = static_cast<RandomKeyframe *>(store);

	Real low = ini->scanReal(ini->getNextToken());
	Real high = ini->scanReal(ini->getNextToken());
	key->frame = ini->scanUnsignedInt(ini->getNextToken());

	// set the range of the random variable
	key->var.setRange(low, high);
}

// Category 1's table (Alpha1..) names it; retail exports this instance.
template void DefaultModuleTemplate<1>::parseRandomKeyframe(INI *, void *, void *, const void *);

} // namespace FXParticleSystem
