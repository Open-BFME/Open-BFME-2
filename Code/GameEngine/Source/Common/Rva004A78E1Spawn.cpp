// cl: /O1 /DNDEBUG /MD
//
// ?rva004A78E1@MissileUpdate@@QAEXXZ @0x004A78E1 137B.
// Play the module data's ignition FX on the object, and when its exhaust
// name at +0x11C is set, spawn that particle system onto +0xC8. Then store
// the fuel-lifetime frame at +0x98 and set state 3.

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Object;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class ParticleSystemTemplate;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	int rva001F5AA4(const ParticleSystemTemplate *tmpl, const Object *obj, bool flag);
};

#include "GameLogicObjectLookupView.h"

extern ParticleSystemManager *TheParticleSystemManager;
extern GameLogic *TheGameLogic;

class MissileUpdateModuleData
{
public:
	char m_pad[0xc4];
	int m_fuelLifetime; // +0xC4
	char m_gap[0xd4 - 0xc8];
	const FXList *m_ignitionFX; // +0xD4
	char m_gap2[0x11c - 0xd8];
	AsciiString m_exhaust; // +0x11C
};

class MissileUpdate
{
public:
	void rva004A78E1();
	void Rva004A7530Set(int val);

private:
	const MissileUpdateModuleData *getMissileUpdateModuleData() const
	{
		return m_moduleData;
	}

	char m_pad[4];
	const MissileUpdateModuleData *m_moduleData; // +4
	Object *m_object; // +8
	char m_gap[0x98 - 0xc];
	int m_98;
	char m_gap2[0xc8 - 0x9c];
	int m_C8;
	char m_gap3[1];
	unsigned char m_CD;
};

void MissileUpdate::rva004A78E1()
{
	const MissileUpdateModuleData *data = getMissileUpdateModuleData();
	FXList::doFXObj(data->m_ignitionFX, m_object, 0);
	const AsciiString &exhaust = data->m_exhaust;
	if (exhaust.isEmpty() == 0) {
		ParticleSystemTemplate *particleSystemTemplate = TheParticleSystemManager->findTemplate(exhaust);
		if (particleSystemTemplate != 0) {
			const Object *obj = m_object;
			m_C8 = TheParticleSystemManager->rva001F5AA4(particleSystemTemplate, obj, 1);
		}
	}
	m_CD = 1;
	int t = data->m_fuelLifetime;
	int frame;
	if (t != 0)
		frame = TheGameLogic->getFrame() + t;
	else
		frame = 0x7fffffff;
	m_98 = frame;
	Rva004A7530Set(3);
}
