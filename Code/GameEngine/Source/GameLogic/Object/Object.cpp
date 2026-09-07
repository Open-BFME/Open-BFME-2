// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 Object module accessors, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameLogic/Object/Object.cpp).
// Retail BFME2 keeps this run of module-cache fields at the same offsets:
// behaviors at +0x18C, body at +0x194, stealth at +0x198, ai at +0x19C,
// radar data at +0x1A8.

class BehaviorModule;
class BodyModuleInterface;
class StealthUpdate;
class AIUpdateInterface;
class RadarObject;

class Object
{
public:
	BehaviorModule **getBehaviorModules() const;
	BodyModuleInterface *getBodyModule() const;
	StealthUpdate *getStealth() const;
	AIUpdateInterface *getAI();
	RadarObject *friend_getRadarData();

private:
	unsigned char m_pre[0x18C];
	BehaviorModule **m_behaviors;	// +0x18C
	void *m_contain;			// +0x190
	BodyModuleInterface *m_body;	// +0x194
	StealthUpdate *m_stealth;	// +0x198
	AIUpdateInterface *m_ai;	// +0x19C
	void *m_1A0;			// +0x1A0
	void *m_1A4;			// +0x1A4
	RadarObject *m_radarData;	// +0x1A8
};

// ?getBehaviorModules@Object@@QBEPAPAVBehaviorModule@@XZ
BehaviorModule **Object::getBehaviorModules() const
{
	return m_behaviors;
}

// ?getBodyModule@Object@@QBEPAVBodyModuleInterface@@XZ
BodyModuleInterface *Object::getBodyModule() const
{
	return m_body;
}

// ?getStealth@Object@@QBEPAVStealthUpdate@@XZ
StealthUpdate *Object::getStealth() const
{
	return m_stealth;
}

// ?getAI@Object@@QAEPAVAIUpdateInterface@@XZ
AIUpdateInterface *Object::getAI()
{
	return m_ai;
}

// ?friend_getRadarData@Object@@QAEPAVRadarObject@@XZ
RadarObject *Object::friend_getRadarData()
{
	return m_radarData;
}
