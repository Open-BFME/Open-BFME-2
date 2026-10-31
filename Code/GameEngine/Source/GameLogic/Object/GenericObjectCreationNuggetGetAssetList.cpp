// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?GetAssetList@GenericObjectCreationNugget@@UBEXAAVAssetList@@PAX@Z, retail 0x001F131F (407 B).
// The concat follows WB 0xB044D0: both operands become AsciiStringRef temporaries (right to left),
// then the AsciiStringPlusString node (RegistryAsciiPath.cpp layout) is built from them and copied out.
// Scratch result 2026-10-20 (claude-opus-5-5), build/nbr/r35/1f131f/best.cpp.
#include "ascii_string.h"

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &s);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int assets, int context);
};

class ThingTemplate
{
public:
	void GetAssetList(int assets, int context);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &s);
};
extern ThingFactory *TheThingFactory;

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &s) const;
};
extern ParticleSystemManager *TheParticleSystemManager;

struct AsciiStringRef
{
	AsciiStringRef() {}
	AsciiStringRef(const AsciiString &asciiString) : m_string(&asciiString) {}
	const AsciiString *m_string;
};
struct AsciiStringPlusString : AsciiStringRef
{
	operator AsciiString();
	AsciiStringRef m_second;
};
// The house expression-template node (RegistryAsciiPath.cpp layout: AsciiStringRef base,
// AsciiStringRef m_second). WB 0xB044D0 (unoptimised) shows each `prefix + set.m_x`
// building both operand refs right to left into temps, assembling the node from them
// and copying it out: an operator+ over two AsciiStringRef operands, like the
// AsciiStringRefWithChar operator+ in Rva0037BA97Finish.cpp.
inline AsciiStringPlusString operator+(const AsciiStringRef &a, const AsciiStringRef &b)
{
	AsciiStringPlusString r;
	r.m_string = a.m_string;
	r.m_second = b;
	return r;
}


class GenericObjectCreationNugget
{
public:
	virtual ~GenericObjectCreationNugget();
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void GetAssetList(AssetList &assets, void *context) const;
private:
	struct NameList
	{
		const AsciiString *begin() const { return m_begin; }
		const AsciiString *end() const { return m_end; }
		AsciiString *m_begin;
		AsciiString *m_end;
		AsciiString *m_capacity;
	};
	struct AnimSet
	{
		AsciiString m_animInitial;
		AsciiString m_animFlying;
		AsciiString m_animFinal;
	};
	struct AnimSetList
	{
		const AnimSet *begin() const { return m_begin; }
		const AnimSet *end() const { return m_end; }
		AnimSet *m_begin;
		AnimSet *m_end;
		AnimSet *m_capacity;
	};
	NameList m_names;
	AsciiString m_putInContainer;
	AnimSetList m_animSets;
	Rva001E11F8 *m_fxFinal;
	AsciiString m_particleSysName;
};

void GenericObjectCreationNugget::GetAssetList(AssetList &assets, void *context) const
{
	if (m_fxFinal)
		((Rva001E11F8 *)m_fxFinal)->rva001E11F8((int)&assets, (int)context);
	if (!((const StringBase<char> &)m_putInContainer).isEmpty()) {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(m_putInContainer);
		if (thingTemplate)
			const_cast<ThingTemplate *>(thingTemplate)->GetAssetList((int)&assets, (int)context);
	}
	for (const AsciiString *name = m_names.begin(); name != m_names.end(); ++name) {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(*name);
		if (thingTemplate)
			const_cast<ThingTemplate *>(thingTemplate)->GetAssetList((int)&assets, (int)context);
	}
	if (!((const StringBase<char> &)m_particleSysName).isEmpty())
		TheParticleSystemManager->findTemplate(m_particleSysName);
	for (const AnimSet *it = m_animSets.begin(); it != m_animSets.end(); ++it) {
		AsciiString prefix("a*");
		if (!((const StringBase<char> &)it->m_animInitial).isEmpty())
			assets << (prefix + it->m_animInitial);
		if (!((const StringBase<char> &)it->m_animFlying).isEmpty())
			assets << (prefix + it->m_animFlying);
		if (!((const StringBase<char> &)it->m_animFinal).isEmpty())
			assets << (prefix + it->m_animFinal);
	}
}
