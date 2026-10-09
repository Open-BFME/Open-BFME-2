// ?GetAssetList@GenericObjectCreationNugget@@QBEXAAVAssetList@@PAX@Z
// partial score=0.82 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 game/GameEngine/Source/GameLogic/Object/GenericObjectCreationNuggetGetAssetList.cpp
// (BFME 1 retail 0x001D7F90 is the same body: member layout +0x04 names, +0x10 container,
// +0x14 anim sets, +0x20 FX, +0x24 particle system is identical in BFME 2).
// Open-BFME: GenericObjectCreationNugget asset collection, retail 0x001D7F90.
// The adjacent constructor fixes the vector, string, FX, and particle fields.

#include "ascii_string.h"

// BFME 2's concatenation is lazy: a two-reference proxy that converts to
// AsciiString out of line (0x000BC495).
struct AsciiStringPlusString
{
	operator AsciiString();
	const AsciiString *m_left;
	const AsciiString *m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_left = &left;
	result.m_right = &right;
	return result;
}

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int first, int second);	// 0x001E11F8, null-checked forwarder
};

class Rva0020AA00Target
{
public:
	void notify(int first, int second);
};

class ThingTemplate;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// TU-local view of the 0x012EF1D8 template singleton; the global takes the
// canonical spelling, defined once in Common/Thing/ThingFactory.cpp.
class ThingFactory;
extern ThingFactory *TheThingFactory;

class Rva003392B0TemplateStore
{
public:
	void *findTemplate(const AsciiString &name);
};

class ParticleSystemManager
{
};

extern ParticleSystemManager *TheParticleSystemManager;

struct GenericObjectCreationNuggetAnimSet
{
	AsciiString m_initial;
	AsciiString m_flying;
	AsciiString m_final;
};

struct GenericObjectCreationNuggetStringVector
{
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct GenericObjectCreationNuggetAnimSetVector
{
	GenericObjectCreationNuggetAnimSet *m_begin;
	GenericObjectCreationNuggetAnimSet *m_end;
	GenericObjectCreationNuggetAnimSet *m_capacity;
};

class GenericObjectCreationNugget
{
public:
	void GetAssetList(AssetList &assets, void *context) const;

private:
	char m_vftable[4];
	GenericObjectCreationNuggetStringVector m_names;
	AsciiString m_putInContainer;
	GenericObjectCreationNuggetAnimSetVector m_animSets;
	Rva001E11F8 *m_fxFinal;
	AsciiString m_particleSysName;
};

void GenericObjectCreationNugget::GetAssetList(AssetList &assets, void *context) const
{
	if (m_fxFinal)
		m_fxFinal->rva001E11F8((int)&assets, (int)context);

	if (!m_putInContainer.isEmpty())
	{
		Rva0020AA00Target *container = (Rva0020AA00Target *)((BfmeThingFactory *)TheThingFactory)->findTemplate(m_putInContainer);
		if (container)
			container->notify((int)&assets, (int)context);
	}

	for (AsciiString *name = m_names.m_begin; name != m_names.m_end; ++name)
	{
		Rva0020AA00Target *prototype = (Rva0020AA00Target *)((BfmeThingFactory *)TheThingFactory)->findTemplate(*name);
		if (prototype)
			prototype->notify((int)&assets, (int)context);
	}

	if (!m_particleSysName.isEmpty())
	{
		((Rva003392B0TemplateStore *)TheParticleSystemManager)->findTemplate(m_particleSysName);
	}

	for (GenericObjectCreationNuggetAnimSet *animSet = m_animSets.m_begin;
		animSet != m_animSets.m_end; ++animSet)
	{
		AsciiString prefix("a*");
		if (!animSet->m_initial.isEmpty())
			assets << prefix + animSet->m_initial;
		if (!animSet->m_flying.isEmpty())
			assets << prefix + animSet->m_flying;
		if (!animSet->m_final.isEmpty())
			assets << prefix + animSet->m_final;
	}
}
