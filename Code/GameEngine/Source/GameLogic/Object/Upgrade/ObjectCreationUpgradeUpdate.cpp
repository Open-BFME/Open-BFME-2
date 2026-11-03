// cl: /Ireference/shims/bfme2_ascii /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// ObjectCreationUpgrade::update, retail 0x004B42DB (753 B): slot 0 of the
// UpdateModuleInterface vftable at +0x18 (0x10 vftable of the module). Once
// the upgrade is armed (+0x2C) and the frame passes +0x28 it spawns the
// data's thing (+0x128) at the owner's transform applied to the offset
// (+0x12C), rotated by +0x138, either through the owner's special context
// (byte +0x150) or BuildAssistant slot 14, fades it in (+0x14C frames scaled
// by the frame/millisecond global), hands it to the owner's SlaveWatcher,
// sets the spawn's owner actions, then grants (+0x124) and removes (+0x120)
// upgrades. Target facts: boundary 0x4B42DB..0x4B45CC, callees by their
// rows, the "SlaveWatcherBehavior" key string; field names follow Zero
// Hour's ObjectCreationUpgrade/OCL semantics (donor inference). /G6 rather
// than the /G7 of ReplaceSelfUpgrade: only /G6 schedules the angle spill.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
#include "ascii_string.h"

typedef float Real;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Team;
class Player;
class Module;
class ThingTemplate;
class UpgradeTemplate;
class Object;
class ModuleData;

#include "../../../../Include/Common/NameKeyGenerator.h"

#include "../../../../Include/Common/ThingFactory.h"

#include "../../../../Include/Common/Upgrade.h"

class Drawable
{
public:
	void fadeIn(UnsignedInt frames);
};

template<int N> class OCUSlots : public OCUSlots<N - 1> { public: virtual void slot(char (*)[N]); };
template<> class OCUSlots<0> {};

#include "../../../../Include/Common/BuildAssistantClass.h"

// Retail calls slot 2 to open a request and slot 8 to test the template.
class OCUSpecialContext
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual int prepare(int objectID, int zero, const AsciiString *name, int enabled);
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual bool accept(const ThingTemplate *thing, int objectID, int token);
};

class OCUOwnerAction
{
public:
	virtual void slot0();
	virtual void setOwner(Object *owner);
};

class OCUModuleView : public OCUSlots<26>
{
public:
	virtual OCUOwnerAction *getOwnerAction();
};

struct OCUModuleEntry
{
	char m_pad00[0x0C];
	OCUModuleView m_view;
};

struct OCUVector3
{
	float X, Y, Z;
	OCUVector3() {}
	OCUVector3(float x, float y, float z) { X = x; Y = y; Z = z; }
};

struct OCUMatrix3D
{
	float Row[3][4];
};

inline OCUVector3 operator*(const OCUMatrix3D &A, const OCUVector3 &a)
{
	float x = A.Row[0][0] * a.X + A.Row[0][1] * a.Y + A.Row[0][2] * a.Z + A.Row[0][3];
	float y = A.Row[1][0] * a.X + A.Row[1][1] * a.Y + A.Row[1][2] * a.Z + A.Row[1][3];
	float z = A.Row[2][0] * a.X + A.Row[2][1] * a.Y + A.Row[2][2] * a.Z + A.Row[2][3];
	return OCUVector3(x, y, z);
}

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void *rva0028BC58(int query);
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
	void rva00293077(const void *upgrade);
	void removeUpgrade(const UpgradeTemplate *upgrade);
	int getID() const { return m_id; }
protected:
	Module *findModule(NameKeyType key) const;
public:
	char m_pad48[0x74 - sizeof(Thing)]; // Retain the legacy label; the canonical base is0x60.
	int m_id;
	char m_pad78[0x1C0 - 0x78];
	Real m_1C0;
	char m_pad1C4[0x244 - 0x1C4];
	OCUModuleEntry **m_244;
};

class SlaveWatcherBehavior
{
public:
	void rva00484869(int objectID);
};

struct ObjectCreationUpgradeModuleData
{
	unsigned char m_pad000[0x120];
	AsciiString m_removeUpgrade;		// +0x120
	AsciiString m_grantUpgrade;		// +0x124
	AsciiString m_thingToSpawn;		// +0x128
	Coord3D m_offset;			// +0x12C
	Real m_angleOffset;			// +0x138
	unsigned char m_pad13C[0x14C - 0x13C];
	UnsignedInt m_fadeInTime;		// +0x14C
	bool m_useSpecialContext;		// +0x150
};

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
protected:
	virtual UpdateSleepTime update();
	const ObjectCreationUpgradeModuleData *getObjectCreationUpgradeModuleData() const { return (const ObjectCreationUpgradeModuleData *)getModuleData(); }
	Object *getObject() const { return m_object; }
private:
	UnsignedInt m_28;
	bool m_2C;
};

extern GameLogic *TheGameLogic;
extern ThingFactory *TheThingFactory;
extern UpgradeCenter *TheUpgradeCenter;
extern NameKeyGenerator *TheNameKeyGenerator;
extern BuildAssistant *TheBuildAssistant;

UpdateSleepTime ObjectCreationUpgrade::update()
{
	if (m_2C && TheGameLogic->getFrame() > m_28)
	{
	const ObjectCreationUpgradeModuleData *data = getObjectCreationUpgradeModuleData();
	if (data && !((const StringBase<char> &)data->m_thingToSpawn).isEmpty())
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(data->m_thingToSpawn);
		if (data->m_useSpecialContext)
		{
			OCUSpecialContext *context = (OCUSpecialContext *)getObject()->rva0028BC58(0);
			if (context)
			{
				if (!context->accept(thingTemplate, -1, context->prepare(-1, 0, &AsciiString::TheEmptyString, 1)))
					return UPDATE_SLEEP_NONE;
			}
		}
		else
		{
			OCUVector3 pos;
			OCUVector3 offset(data->m_offset.x, data->m_offset.y, data->m_offset.z);
			pos.X = getObject()->getPosition()->x;
			pos.Y = getObject()->getPosition()->y;
			pos.Z = getObject()->getPosition()->z;
			pos = *reinterpret_cast<const OCUMatrix3D *>(getObject()->getTransformMatrix()) * offset;

			Object *owner = getObject();
			Real angle = owner->getOrientation();
			Object *obj = TheBuildAssistant->buildObjectNow(owner, thingTemplate, (const Coord3D *)&pos,
				angle + data->m_angleOffset, owner->getControllingPlayer());
			if (obj == 0)
				return UPDATE_SLEEP_FOREVER;

			if (obj->getDrawable())
				obj->getDrawable()->fadeIn((UnsignedInt)(data->m_fadeInTime * 0.03f));

			Real spawnAngle = data->m_angleOffset + getObject()->getOrientation();
			obj->m_1C0 = spawnAngle;
			obj->setPosition((const Coord3D *)&pos);

			static NameKeyType slaveWatcherKey = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
			SlaveWatcherBehavior *slaveWatcher = (SlaveWatcherBehavior *)getObject()->findUpdateModule(slaveWatcherKey);
			if (slaveWatcher)
				slaveWatcher->rva00484869(obj->getID());

			for (OCUModuleEntry **entry = obj->m_244; *entry; ++entry)
			{
				OCUOwnerAction *action = (*entry)->m_view.getOwnerAction();
				if (action)
				{
					Object *current = getObject();
					if (current)
						action->setOwner(current);
				}
			}
		}
	}

	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_grantUpgrade);
	if (upgrade)
		getObject()->rva00293077(upgrade);

	upgrade = TheUpgradeCenter->findUpgrade(data->m_removeUpgrade);
	if (upgrade)
		getObject()->removeUpgrade(upgrade);

	return UPDATE_SLEEP_FOREVER;
	}
	return UPDATE_SLEEP_NONE;
}
