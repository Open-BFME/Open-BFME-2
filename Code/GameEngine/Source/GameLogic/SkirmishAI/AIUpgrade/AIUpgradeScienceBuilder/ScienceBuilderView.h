#pragma once

#include "ScienceBuilderVectorView.h"

class Object;
class Player;
class ModuleData;
class Rva00597E30Entry;
struct Rva002A8AB1Record;

// Manager calls used by registration and shutdown.
#include "../../../../../Include/GameLogic/Rva002A8F24.h"

// The seed's existing four-byte vector provider identity. This vector holds
// object identifiers; the spelling does not establish ScienceType semantics.
enum ScienceType
{
	SCIENCE_DUMMY = 0
};

class BaseA
{
public:
	virtual void Register(Object *, void *) = 0;
	virtual void UnRegister(Object *) = 0;
	virtual ~BaseA();
	int m_04;
	int m_08;
};

class Rva00506B1B
{
public:
	virtual ~Rva00506B1B();
	virtual void rva00597fc5() = 0;
	virtual void shutdown() = 0;
	bool m_04;
};

// Shared native receiver prefix: the secondary callback starts at +0x0C,
// owner at +0x14, object IDs at +0x18, and record ranges at +0x24/+0x30.
// Preserve the seed's existing template providers; consumers of the generic
// pointer-vector erase use an explicit view rather than rebinding providers.
class AIUpgradeScienceBuilder : public BaseA, public Rva00506B1B
{
public:
	virtual void Register(Object *, void *);
	virtual void UnRegister(Object *);
	virtual ~AIUpgradeScienceBuilder();
	virtual void rva00597fc5();
	virtual void shutdown();
	bool rva0059764A(Object *object);
	void buildExpansionUpgrades();
private:
	Player *m_14;
	_STL::vector<ScienceType> m_objects;
	_STL::vector<const ModuleData *> m_upgrades;
	Rva00597E30Entry **m_30;
	Rva00597E30Entry **m_34;
	char m_pad38[0x3C - 0x38];
	unsigned m_3C;
};
