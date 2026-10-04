// ?rva001F131F@Rva001F131F@@QAEXHH@Z
// partial score=0.97 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ?rva001F131F@Rva001F131F@@QAEXHH@Z @0x001F131F 407B: vslot 4 of GenericObjectCreationNugget.
// Evidence: forwards HH to 0x001E11F8 when +0x20 set; StringBase isEmpty at +0x10/+0x24; rva002D06CAGet + notify pin; loops over AsciiString array +0x04..+0x08 and 12B records +0x14..+0x18 with a*/PlusString/AssetList; findTemplate via TheParticleSystemManager.

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *s);
};

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &s);
};

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &s) const;
};
extern ParticleSystemManager *TheParticleSystemManager;

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	operator AsciiString();
	AsciiStringRef m_second;
};

class Rva001F131F
{
public:
	void rva001F131F(int a, int b);
private:
	void *m_vptr;
	AsciiString *m_namesBegin;
	AsciiString *m_namesEnd;
	AsciiString *m_namesCap;
	AsciiString m_putInContainer;
	struct AnimSet
	{
		AsciiString m_initial;
		AsciiString m_flying;
		AsciiString m_final;
	};
	AnimSet *m_animBegin;
	AnimSet *m_animEnd;
	AnimSet *m_animCap;
	Rva001E11F8 *m_fxFinal;
	AsciiString m_particleSysName;
};

extern Rva002D06CA *g_009FF000;

// ?rva001F131F@Rva001F131F@@QAEXHH@Z present-unmatched
void Rva001F131F::rva001F131F(int a, int b)
{
	if (m_fxFinal)
		m_fxFinal->rva001E11F8(a, b);
	if (!((const StringBase<char> &)m_putInContainer).isEmpty()) {
		void *p = g_009FF000->rva002D06CA(&m_putInContainer);
		if (p)
			((Rva0020AA00Target *)p)->notify(a, b);
	}
	for (AsciiString *name = m_namesBegin; name != m_namesEnd; ++name) {
		void *p = g_009FF000->rva002D06CA(name);
		if (p)
			((Rva0020AA00Target *)p)->notify(a, b);
	}
	if (!((const StringBase<char> &)m_particleSysName).isEmpty())
		TheParticleSystemManager->findTemplate(m_particleSysName);
	for (AnimSet *animSet = m_animBegin; animSet != m_animEnd; ++animSet) {
		AsciiString prefix("a*");
		if (!((const StringBase<char> &)animSet->m_initial).isEmpty()) {
			AsciiStringPlusString plus;
			plus.m_string = &prefix;
			plus.m_second.m_string = &animSet->m_initial;
			((AssetList *)a)->operator<<(plus);
		}
		if (!((const StringBase<char> &)animSet->m_flying).isEmpty()) {
			AsciiStringPlusString plus;
			plus.m_string = &prefix;
			plus.m_second.m_string = &animSet->m_flying;
			((AssetList *)a)->operator<<(plus);
		}
		if (!((const StringBase<char> &)animSet->m_final).isEmpty()) {
			AsciiStringPlusString plus;
			plus.m_string = &prefix;
			plus.m_second.m_string = &animSet->m_final;
			((AssetList *)a)->operator<<(plus);
		}
	}
}
