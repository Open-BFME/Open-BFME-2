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

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual SpawnBehaviorInterface *getSpawnBehaviorInterface() = 0;
};

class BfmeObjectModule
{
public:
	virtual void slot0() = 0;

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

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
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		SpawnBehaviorInterface *sbi = (*m)->getSpawnBehaviorInterface();
		if (sbi)
		{
			return sbi;
		}
	}
	return 0;
}
