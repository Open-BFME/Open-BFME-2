// cl: /DNDEBUG /MD /EHsc
// ??0AnimationSoundClientBehavior@@QAE@ABV0@@Z, retail 0x004CA1C1, 98 bytes.
// Target evidence: the body copy-constructs the 12-byte primary base through
// the rowed Rva00252B68 copy ctor (0x004CA125), stores the folded secondary-
// base vftable C6FFFC at +0x0C, then the class vftables C5EE80 (+0x00) and
// C5EE74 (+0x0C), copies +0x10 from the source, zeros the two list links at
// +0x14/+0x18 and registers itself with the container global at VA 0x00E032D0
// through rowed rva00432F7D (0x00432F7D).
// Identity inference: the vftable xrefs, rowed regular constructor 0x004CA05A
// and destructor 0x004C9DC9 support this as the class copy constructor. The
// secondary base is modelled as a plain interface whose inline ctor stores the
// folded vftable; member names beyond the offsets are not established.

class Rva00252B68
{
public:
	Rva00252B68(const Rva00252B68 &other);
	virtual ~Rva00252B68();

private:
	unsigned int m_field04;
	unsigned int m_field08;
};

// Declared as AnimationSoundClientBehaviorDtor.cpp declares it (both slots
// rowed on AnimationSoundClientBehavior, 0x004C9E33 / 0x004C9E48).
class Rva004C9E33Iface
{
public:
	virtual void rva004C9E33() = 0;
	virtual void rva004C9E48() = 0;
};

#include "../../../../Include/Common/Rva00432F23Node.h"

#include "../../../../Include/Common/AnimationSoundModuleManager.h"

extern AnimationSoundModuleManager *TheAnimationSoundModuleManager;

class AnimationSoundClientBehavior : public Rva00252B68, public Rva004C9E33Iface
{
public:
	AnimationSoundClientBehavior(const AnimationSoundClientBehavior &other);
	virtual ~AnimationSoundClientBehavior();
	virtual void rva004C9E33();
	virtual void rva004C9E48();

private:
	float m_float10;
	Rva00432F23Node *m_next14;
	Rva00432F23Node *m_prev18;
};

AnimationSoundClientBehavior::AnimationSoundClientBehavior(
	const AnimationSoundClientBehavior &other)
	: Rva00252B68(other), m_float10(other.m_float10), m_next14(0), m_prev18(0)
{
	if (TheAnimationSoundModuleManager)
		TheAnimationSoundModuleManager->rva00432F7D((Rva00432F23Node *)this);
}
