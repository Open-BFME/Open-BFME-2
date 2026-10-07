// ?createParticleSystems@ActiveBody@@MAEXABVAsciiString@@PBVParticleSystemTemplate@@H@Z
// partial score=0.91 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?validateArmorAndDamageFX@ActiveBody@@QBEXXZ, retail 0x004BE1AE (156B).
// Zero Hour ActiveBody::validateArmorAndDamageFX: look up the template's armor
// set for the current armor-set flags and, when it differs from the cached
// one, refresh the cached armor and damage FX.
// BFME 2 differences (target evidence): an ArmorTemplateSet names its armor
// (AsciiString at set +0x04) instead of pointing at an ArmorTemplate, so the
// "has an armor" test is that name's out-of-line StringBase<char>::isEmpty
// (0x00001E2F), TheArmorStore's makeArmor (0x001D9001) builds the Armor from
// the name, and Armor is the one-string object whose assignment is the
// AsciiString set (0x000366F0) and whose clear assigns
// AsciiString::TheEmptyString. The lookup is the ThingTemplate armor-set
// finder 0x0033DCB8 (its own callers include this body; rowed under an
// address name). Members: armor-set flags +0xF0, armor set +0xF4, armor
// +0xF8, damage FX +0xFC (mutable: the method is const). The template is
// Thing +0x04 of the module's Object (+0x08).

#include "ascii_string.h"

typedef unsigned int size_t;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x, y, z;
	Coord3D();
	~Coord3D();
};

class Matrix3D;
class ParticleSystemTemplate;
class Object;
class BodyParticleSystem;
class ParticleSystem;
ParticleSystem *Make001FCBD7();

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};


template <int NUMBITS> class BitFlags
{
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<17> ArmorSetFlags;

class DamageFX;

class ArmorTemplateSet
{
public:
	const AsciiString &getArmorTemplateName() const { return m_armorName; }
	const DamageFX *getDamageFX() const { return m_fx; }

private:
	ArmorSetFlags m_types;		// +0x00
	AsciiString m_armorName;	// +0x04
	const DamageFX *m_fx;		// +0x08
};

class Armor
{
public:
	void clear() { m_templateName = AsciiString::TheEmptyString; }

private:
	AsciiString m_templateName;
};

class ArmorStore
{
public:
	Armor makeArmor(const AsciiString &name) const;	// 0x001D9001
};
extern ArmorStore *TheArmorStore;

class ThingTemplate
{
};

class WeaponTemplateSet;
struct Rva0033DCB8
{
	const WeaponTemplateSet *rva0033DCB8(const ArmorSetFlags &t) const;	// row at 0x0033DCB8, real findArmorTemplateSet is pinned there
};

class BodyParticleSystem
{
protected:
	virtual ~BodyParticleSystem();

public:
	enum BodyParticleSystemMagicEnum
	{
		BodyParticleSystem_GLUE_NOT_IMPLEMENTED = 0
	};
	static void *operator new(size_t s, BodyParticleSystemMagicEnum, const char *)
	{
		void *operator new(size_t);
		return ::operator new(s);
	}
	ParticleSystemID m_particleSystemID;
	BodyParticleSystem *m_next;
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos);
	void attachToObject(const Object *obj);
	ParticleSystemID getSystemID() const { return m_systemID; }

private:
	char m_pad[0xA8];
	ParticleSystemID m_systemID;
};

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();
	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make001FCBD7();
		return m_system;
	}

private:
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *systemTemplate, Bool createSlaves = true) throw();
};
extern ParticleSystemManager *TheParticleSystemManager;

extern Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);
#define GameClientRandomValue(lo, hi) \
	GetGameClientRandomValue((lo), (hi), __FILE__, __LINE__)
#define newInstance(ARGCLASS) \
	new(ARGCLASS::ARGCLASS##_GLUE_NOT_IMPLEMENTED, __FILE__) ARGCLASS

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones,
		Coord3D *positions, Matrix3D *transforms, Bool convertToWorld,
		Int extra = 0) const;

private:
	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
};

class ActiveBody
{
public:
	void validateArmorAndDamageFX() const;

protected:
	Object *getObject() const { return m_object; }
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

	private:
	void *m_moduleData;				// +0x04
	Object *m_object;				// +0x08
	char m_pad0C[0xC8 - 0x0C];
	BodyParticleSystem *m_particleSystems;
	char m_padCC[0xF0 - 0xCC];
	ArmorSetFlags m_curArmorSetFlags;		// +0xF0
	mutable const ArmorTemplateSet *m_curArmorSet;	// +0xF4
	mutable Armor m_curArmor;			// +0xF8
	mutable const DamageFX *m_curDamageFX;		// +0xFC
};

void ActiveBody::validateArmorAndDamageFX() const
{
	const ArmorTemplateSet *set = (const ArmorTemplateSet *)((const Rva0033DCB8 *)getObject()->getTemplate())->rva0033DCB8(m_curArmorSetFlags);
	if (set && set != m_curArmorSet)
	{
		const AsciiString &armorName = set->getArmorTemplateName();
		if (!((const StringBase<char> &)armorName).isEmpty())
		{
			m_curArmor = TheArmorStore->makeArmor(armorName);
		}
		else
		{
			m_curArmor.clear();
		}
		m_curDamageFX = set->getDamageFX();
		m_curArmorSet = set;
	}
}

// Identity evidence: the target's slot 19 is shared by ActiveBody and its
// body subclasses, and its body performs the particle/bone sequence found in
// the BFME1 ActiveBody::createParticleSystems donor. Target evidence places
// this object's pointer at +0x08 and its particle list at +0xC8; the donor's
// particle-list offset differs, so the target offset comes from retail.
void ActiveBody::createParticleSystems(const AsciiString &boneBaseName,
	const ParticleSystemTemplate *systemTemplate, Int maxSystems)
{
	Object *us = getObject();
	if (systemTemplate == 0)
		return;

	enum { MAX_BONES = 16 };
	Coord3D bonePositions[MAX_BONES];
	Int numBones = us->getMultiLogicalBonePosition(boneBaseName.str(),
		MAX_BONES, bonePositions, 0, false);
	if (numBones == 0)
		return;
	if (numBones < maxSystems)
		maxSystems = numBones;

	Bool usedBoneIndices[MAX_BONES] = { false };
	for (Int i = 0; i < maxSystems; ++i)
	{
#line 1514 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		Int boneIndex = GameClientRandomValue(0, numBones - 1);
		for (Int j = 0; j < numBones; ++j)
		{
			if (usedBoneIndices[boneIndex] != true)
			{
				const Coord3D *pos = &bonePositions[boneIndex];
				usedBoneIndices[boneIndex] = true;
				if (pos)
				{
					BfmeParticleSystemHandle particleSystem =
						TheParticleSystemManager->createParticleSystem(systemTemplate, true);
					if (particleSystem)
					{
						particleSystem->setPosition(pos);
						particleSystem->attachToObject(us);

						BodyParticleSystem *newEntry =
							newInstance(BodyParticleSystem);
						newEntry->m_particleSystemID = particleSystem->getSystemID();
						newEntry->m_next = m_particleSystems;
						m_particleSystems = newEntry;
					}
				}
				break;
			}
			boneIndex = (boneIndex + 1) % numBones;
		}
	}
}
