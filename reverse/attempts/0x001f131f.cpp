// ?GetAssetList@GenericObjectCreationNugget@@UBEXAAVAssetList@@PAX@Z
// partial score=0.9885244652686512 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Native1F131F..1F14B6; GenericObjectCreationNugget table7E1160 slot4
// points here. The const asset-list purpose/name comes from BFME1 donor
// GenericObjectCreationNuggetGetAssetList.cpp, reviewed575ba2b04743f190f069805fbdc59936123c45da.
// Target field offsets are the constructor and destructor's proven layout;
// callers/owned lookup APIs establish ThingFactory and ParticleSystemManager.
// The unknown slots1..3 below preserve slot4 only; their ABI is unproven and
// they are never called or emitted in this bank. No vtable is claimed.
// Remaining four instructions: flying proxy address should live in ECX and
// be calculated before the first pointer store. Current form uses EAX.
#include "ascii_string.h"
// ?rva001F131F@Rva001F131F@@QAEXHH@Z @0x001F131F 407B: vslot 4 of GenericObjectCreationNugget.
// Evidence: forwards HH to 0x001E11F8 when +0x20 set; StringBase isEmpty at +0x10/+0x24; rva002D06CAGet + notify pin; loops over AsciiString array +0x04..+0x08 and 12B records +0x14..+0x18 with a*/PlusString/AssetList; findTemplate via TheParticleSystemManager.

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

class ThingTemplate;
class ThingFactory
{
public:
 const ThingTemplate *findTemplate(const AsciiString &s);
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

class GenericObjectCreationNugget
{
public:
	virtual ~GenericObjectCreationNugget();
 virtual void slot1() = 0;
 virtual void slot2() = 0;
 virtual void slot3() = 0;
 virtual void GetAssetList(AssetList &assets, void *context) const;
private:
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

class ThingFactory;
extern ThingFactory *TheThingFactory;

void GenericObjectCreationNugget::GetAssetList(AssetList &assets, void *context) const
{
 const int a=(int)&assets, b=(int)context;
	if (m_fxFinal)
		m_fxFinal->rva001E11F8(a, b);
	if (!((const StringBase<char> &)m_putInContainer).isEmpty()) {
		const ThingTemplate *p = TheThingFactory->findTemplate(m_putInContainer);
		if (p)
			((Rva0020AA00Target *)p)->notify(a, b);
	}
	for (AsciiString *name = m_namesBegin; name != m_namesEnd; ++name) {
		const ThingTemplate *p = TheThingFactory->findTemplate(*name);
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
