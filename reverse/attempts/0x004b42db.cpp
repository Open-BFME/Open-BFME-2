// ?update@UpdateModuleInterface@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.46 date=2026-10-05
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?update@UpdateModuleInterface@@UAE?AW4UpdateSleepTime@@XZ, target 0x004B42DB (753 bytes).
// Target identity: ObjectCreationUpgrade ctor 0x004B40A6 stores vptr 0x00C57560
// at object+0x18; its slot 0 is this body. The matched ObjectCreationUpgrade
// module-data ctor at 0x004B425B establishes the data pointer at owner+0x0C.
// Donor semantics and interface spelling: reference/open-bfme-1/game/.../
// ObjectCreationUpgradeUpdate.cpp (pointer 6583b3c1ff21db4a561285717028fdafc780b7db).
// Target-only offsets and call paths are from BFME2 retail bytes; field labels
// remain donor-derived where the retail table establishes only an offset.

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void set(const Coord3D *src)
	{
		*this = *src;
	}
};

class AsciiString
{
	void *m_buffer;
public:
	bool isEmpty() const;
};

class Team;
class Player;
class Module;
class ThingTemplate;
class UpgradeTemplate;
class Object;
class Drawable;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class Drawable
{
public:
	void fadeIn(unsigned int frames);
};

class Thing
{
public:
	Drawable *getDrawable() const;
	void setPosition(const Coord3D *position);
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void *rva0028BC58(int query);
	Module *findModule(NameKeyType key) const;
	void rva00293077(const void *upgrade);
	void rva00290D42(const UpgradeTemplate *upgrade);
	Team *getTeam() const
	{
		return *(Team *const *)((const char *)this + 0x304);
	}
	int getID() const
	{
		return *(const int *)((const char *)this + 0x74);
	}
};

class Rva00484869
{
public:
	void rva00484869(int objectID);
};

class RvaObjectCreationAuxView
{
public:
	virtual void *slot00();
	virtual void *slot01();
	virtual void *slot02();
	virtual void *slot03();
	virtual void *slot04();
	virtual void *slot05();
	virtual void *slot06();
	virtual void *slot07();
	virtual void *slot08();
	virtual void *slot09();
	virtual void *slot10();
	virtual void *slot11();
	virtual void *slot12();
	virtual void *slot13();
	virtual void *slot14();
	virtual void *slot15();
	virtual void *slot16();
	virtual void *slot17();
	virtual void *slot18();
	virtual void *slot19();
	virtual void *slot20();
	virtual void *slot21();
	virtual void *slot22();
	virtual void *slot23();
	virtual void *slot24();
	virtual void *slot25();
	virtual void *slot26();
};

class RvaObjectCreationAuxAction
{
public:
	virtual void slot0();
	virtual void setOwner(Object *owner);
};

class RvaObjectCreationSpecialContext
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual int prepare(int objectID, int zero, const void *kind, int enabled);
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual bool accept(const ThingTemplate *thing, int objectID, int token);
};

class Rva00E027B8Factory
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual Object *createObject(Object *owner, const ThingTemplate *thing,
		const Coord3D *position, float angle, Team *team, Player *controller);
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

struct ObjectCreationUpgradeModuleDataView
{
	unsigned char pad000[0x120];
	AsciiString m_upgradeToRemove;		// +0x120
	AsciiString m_upgradeToGrant;		// +0x124
	AsciiString m_thingToSpawn;		// +0x128
	float m_offsetX;			// +0x12C
	float m_offsetY;			// +0x130
	float m_offsetZ;			// +0x134
	float m_angleOffset;			// +0x138
	unsigned char m_flag13C;
	unsigned char pad13D[3];
	int m_140;
	int m_144;
	int m_148;
	int m_fadeInMilliseconds;		// +0x14C
	unsigned char m_specialPath;		// +0x150
};

struct ObjectCreationUpgradeView
{
	unsigned char pad000[0x0C];
	ObjectCreationUpgradeModuleDataView *m_moduleData;	// +0x0C
	Object *m_object;			// +0x10
	unsigned char pad014[0x14];
	unsigned int m_nextFrame;		// +0x28
	bool m_updatePending;			// +0x2C
};

UpdateSleepTime UpdateModuleInterface::update()
{
	char *currentView = (char *)this;
	ObjectCreationUpgradeView *upgrade =
		(ObjectCreationUpgradeView *)(currentView - 0x18);
	if (!upgrade->m_updatePending ||
		*(unsigned int *)(*(unsigned int *)0x00DFE78C + 0x40) <= upgrade->m_nextFrame)
	{
		return UPDATE_SLEEP_NONE;
	}

	ObjectCreationUpgradeModuleDataView *data =
		*(ObjectCreationUpgradeModuleDataView **)(currentView - 0x0C);
	if (!data)
		goto apply_upgrades;

	if (data->m_thingToSpawn.isEmpty())
		goto apply_upgrades;

	const ThingTemplate *thingTemplate =
		((ThingFactory *)*(void **)0x00DFF000)->findTemplate(data->m_thingToSpawn);

	if (data->m_specialPath)
	{
		Object *ownerBeforeSpecial = *(Object **)(currentView - 8);
		RvaObjectCreationSpecialContext *context =
			(RvaObjectCreationSpecialContext *)ownerBeforeSpecial->rva0028BC58(0);
		if (!context)
			goto apply_upgrades;

		currentView = (char *)context;
		int token = context->prepare(-1, 0, (const void *)0x00DE0878, 1);
		if (context->accept(thingTemplate, -1, token))
			goto apply_upgrades;
	}

	Object *owner = *(Object **)(currentView - 8);
	Coord3D position;
	position.set((const Coord3D *)((const char *)owner + 0x38));

	const float *matrix = (const float *)((const char *)owner + 0x08);
	Coord3D offset;
	offset.x = data->m_offsetX;
	offset.y = data->m_offsetY;
	offset.z = data->m_offsetZ;
	Coord3D transformed;
	transformed.x = matrix[1] * offset.y + matrix[2] * offset.z;
	transformed.x += matrix[0] * offset.x;
	transformed.x += matrix[3];
	transformed.y = matrix[5] * offset.y + matrix[4] * offset.x;
	transformed.y += matrix[6] * offset.z;
	transformed.y += matrix[7];
	transformed.z = matrix[8] * offset.x + matrix[9] * offset.y;
	transformed.z += matrix[10] * offset.z;
	transformed.z += matrix[11];
	position.set(&transformed);

	Rva00E027B8Factory *factory =
		*(Rva00E027B8Factory **)0x00E027B8;
	float ownerAngle = *(const float *)((const char *)owner + 0x44);
	Player *controller = owner->getControllingPlayer();
	float angle = data->m_angleOffset + ownerAngle;
	Team *team = owner->getTeam();
	Object *spawned = factory->createObject(owner, thingTemplate,
		&position, angle, team, controller);

	if (spawned)
	{
		if (spawned->getDrawable())
		{
			int frames = (int)(data->m_fadeInMilliseconds
				* *(const float *)0x00DBA500);
			spawned->getDrawable()->fadeIn(frames);
		}

		float spawnAngle = *(const float *)((const char *)owner + 0x44);
		spawnAngle += data->m_angleOffset;
		*(float *)((char *)spawned + 0x1C0) = spawnAngle;
		spawned->setPosition(&position);

		static NameKeyType slaveWatcherKey =
			((NameKeyGenerator *)*(void **)0x00DF36A4)
				->nameToKey("SlaveWatcherBehavior");
		Module *slaveWatcher = owner->findModule(slaveWatcherKey);
		if (slaveWatcher)
			((Rva00484869 *)slaveWatcher)->rva00484869(spawned->getID());

		void **entries = *(void ***)((char *)spawned + 0x244);
		while (*entries)
		{
			RvaObjectCreationAuxView *aux =
				(RvaObjectCreationAuxView *)((char *)*entries + 0x0C);
			void *action = aux->slot26();
			if (action)
			{
				Object *currentOwner = *(Object **)(currentView - 8);
				if (currentOwner)
					((RvaObjectCreationAuxAction *)action)->setOwner(currentOwner);
			}
			++entries;
		}
	}

apply_upgrades:
	{
		const UpgradeTemplate *upgradeToGrant =
			((UpgradeCenter *)*(void **)0x00DFEB60)
				->findUpgrade(data->m_upgradeToGrant);
		if (upgradeToGrant)
		{
			Object *currentOwner = *(Object **)(currentView - 8);
			currentOwner->rva00293077(upgradeToGrant);
		}
	}

	{
		const UpgradeTemplate *upgradeToRemove =
			((UpgradeCenter *)*(void **)0x00DFEB60)
				->findUpgrade(data->m_upgradeToRemove);
		if (upgradeToRemove)
		{
			Object *currentOwner = *(Object **)(currentView - 8);
			currentOwner->rva00290D42(upgradeToRemove);
		}
	}

	return UPDATE_SLEEP_FOREVER;
}
