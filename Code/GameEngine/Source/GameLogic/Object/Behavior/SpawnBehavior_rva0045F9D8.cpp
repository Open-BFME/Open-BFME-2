// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?reclaimOrphanSpawn@SpawnBehavior@@QAE_NXZ, retail 0x0045F9D8, 127 bytes.
// Identity: BFME 2 moves Zero Hour's orphan reclaiming out of createSpawn
// (whose rowed BFME 2 body 0x0045FA57 has none) into this helper: with the
// module data's m_canReclaimOrphans (+0x15) set it asks the rowed orphan
// finder 0x0045F4D7 (Zero Hour's reclaimOrphanSpawn) for an orphan, and a
// found one gets createSpawn's adoption statements: setProducer (0x0028AFD2),
// the SlavedUpdate onEnslave walk, and its ID pushed on the spawn list
// (+0x4C, list push_back 0x0005548F). Its caller is the SpawnBehaviorInterface
// slot 12 body 0x004601CC, which consumes a replacement time per reclaim.
// Primary-this layout as in the SpawnBehavior ctor: module data +0x04,
// object +0x08.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const;
	virtual void onEnslave(const Object *slaver);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
#define BMI_SLOT(n) virtual void behaviorModuleInterfaceSlot##n();
	BMI_SLOT(00) BMI_SLOT(01) BMI_SLOT(02) BMI_SLOT(03) BMI_SLOT(04) BMI_SLOT(05)
	BMI_SLOT(06) BMI_SLOT(07) BMI_SLOT(08) BMI_SLOT(09) BMI_SLOT(10) BMI_SLOT(11)
	BMI_SLOT(12) BMI_SLOT(13) BMI_SLOT(14) BMI_SLOT(15) BMI_SLOT(16) BMI_SLOT(17)
	BMI_SLOT(18) BMI_SLOT(19) BMI_SLOT(20) BMI_SLOT(21) BMI_SLOT(22) BMI_SLOT(23)
	BMI_SLOT(24) BMI_SLOT(25)
#undef BMI_SLOT
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

	void setProducer(Object *obj);

private:
	unsigned char m_pad000[0x74];
	ObjectID m_id;
	unsigned char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors;
};

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0x14];
	Bool m_isOneShotData;
	Bool m_canReclaimOrphans;
};

class SpawnBehavior
{
public:
	Bool reclaimOrphanSpawn();
	Object *rva0045F4D7();

private:

	Object *getObject() const { return m_object; }
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return m_moduleData; }

	void *m_vptr;
	const SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x4c - 0x0c];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?reclaimOrphanSpawn@SpawnBehavior@@QAE_NXZ
Bool SpawnBehavior::reclaimOrphanSpawn()
{
	Object *parent = getObject();
	if (parent == NULL)
		return false;
	const SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();
	if (md == NULL)
		return false;

	if (md->m_canReclaimOrphans)
	{
		Object *newSpawn = rva0045F4D7();
		if (newSpawn)
		{
			newSpawn->setProducer(parent);

			// If they have a SlavedUpdate, then I have to tell them who their daddy is from now on.
			for (BehaviorModule **update = newSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onEnslave(parent);
					break;
				}
			}

			m_spawnIDs.push_back(newSpawn->getID());
			return true;
		}
	}
	return false;
}
