// cl: /DNDEBUG /MD
//
// ?getSpawnBehaviorInterface@Object@@QBEPAVSpawnBehaviorInterface@@XZ,
// retail 0x0028BCD4, 32 bytes. Dedicated TU.
// BFME2 scans the BehaviorModule array at +0x244 (not the +0x18C behaviors
// array getBehaviorModules returns) and returns the first non-null spawn
// interface, reached through the +0x0C sub-object exactly like BFME1's
// BehaviorModule layout (vptr + two words, then the interface). The getter
// sits at slot 30 (+0x78) of that sub-object.

class SpawnBehaviorInterface;

#include "../../../Include/GameLogic/Module/BehaviorModule.h"



class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
};

// ?getSpawnBehaviorInterface@Object@@QBEPAVSpawnBehaviorInterface@@XZ
SpawnBehaviorInterface *Object::getSpawnBehaviorInterface() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		SpawnBehaviorInterface *sbi = static_cast<SpawnBehaviorInterface *>((*behaviorModule)->slot30());
		if (sbi)
		{
			return sbi;
		}
	}
	return 0;
}
