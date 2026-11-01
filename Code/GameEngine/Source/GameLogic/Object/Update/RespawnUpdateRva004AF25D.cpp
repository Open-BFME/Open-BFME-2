// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva004AF25D@RespawnUpdate@@QAEPAXXZ, retail 0x004AF25D, 50 bytes.
// Lazy RespawnUpdate getter: cached void at +0x28 (init -1 per ctor
// 0x004AF096) else lookup ModuleData string at +0x11C through global
// 0x00DFF000 via rowed 0x002D06CA else Object+4 fallback. Caller at
// 0x0029111F finds RespawnUpdate module then adds 0x64 for AsciiString.
#include "ascii_string.h"

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};

extern class ThingFactory *TheThingFactory;

struct RespawnUpdateModuleDataRef
{
	char m_pad[0x118];
	AsciiString m_deadImageName;
	AsciiString m_respawnAsTemplate;
};

class Image;
class ThingTemplate
{
public:
	unsigned char m_unknown[0x11F];
	unsigned char m_kindOfByte;
};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
enum DisabledType;
enum ObjectStatusTypes;
class Player;
class ExitInterface;
class BodyModuleInterface;
class FXList;
class ThingTemplate;
class Image;
class AIUpdateInterface;
class INI;
class Object {public:
 ExitInterface *getObjectExitInterface() const;
 void restoreObjectToWorld(const Coord3D *);
 void rva001E42F2(const int *);
 void rva001E431E(const int *);
 void setStatus(ObjectStatusTypes,bool);
 bool clearDisabled(DisabledType);
 void setDisabledUntil(DisabledType,unsigned);
 Player *getControllingPlayer() const;
 __forceinline const Coord3D *getPosition() const {return &position;}
 __forceinline ThingTemplate *getTemplate() const {return m_template;}
 char pad00[4];ThingTemplate *m_template;char pad08[0x38-0x08];Coord3D position;char pad44[0x74-0x44];int m_heroKey;ObjectID producer;
 char pad7C[0x254-0x7C];BodyModuleInterface *body;AIUpdateInterface *ai;
 char pad25C[0x45C-0x25C];int handle;
};

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface {public:virtual void slot0()=0;};

class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {public:virtual ~BehaviorModule();};

class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};

class UpdateModule:public BehaviorModule,public UpdateModuleInterface {public:virtual ~UpdateModule();protected:void setWakeFrame(Object *,UpdateSleepTime);private:unsigned nextWake;int index,reserved;};


class RespawnUpdate:public UpdateModule {
public:
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;
	virtual float getPercentReady(int *out);
	virtual const Image *getDeadImage();
	void rva004AF182();
	void *rva004AF25D();
	Object *searchForSuitableSpawnAtObject();
	static void iniParseNewRuleForLevel(INI *, void *, void *, const void *);
	static void iniParseDefaultRule(INI *, void *, void *, const void *);
public:
	float health;
	const Image *deadImage;
	void *respawnTemplate;
	unsigned state;
	ObjectID spawnAt;
	int at34,at38,at3C;
	bool at40,at41;
};

class CreateAHeroHero;
// The rowed lookup ?rva002197A6@CreateAHeroManager@@QAEPAVCreateAHeroData@@H@Z.
class CreateAHeroData;
class CreateAHeroManager
{
public:
	CreateAHeroData *rva002197A6(int);
	const AsciiString &GetButtonImageName(const CreateAHeroHero *);
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &);
};
extern CreateAHeroManager *TheCreateAHeroManager;
extern ImageCollection *TheMappedImageCollection;
const Image *getButtonImage(ThingTemplate *, Object *);

// WorldBuilder RespawnUpdate::getDeadImage, source lines 851/868. Retail
// 4AF2DE..4AF3BD tests cached image +24, module-data string +118,
// template KindOf byte +11F bit40 and the object's hero key +74.
// Callees and both singleton globals retain their existing verified names.
const Image *RespawnUpdate::getDeadImage()
{
	if (deadImage)
		return deadImage;
	const RespawnUpdateModuleDataRef *data = reinterpret_cast<const RespawnUpdateModuleDataRef *>(getModuleData());
	Object *object = m_object;
	const AsciiString &name = data->m_deadImageName;
	if (!name.isEmpty()) {
		if (object->getTemplate()->m_kindOfByte & 0x40) {
			CreateAHeroHero *hero = (CreateAHeroHero *)(
				TheCreateAHeroManager->rva002197A6(object->m_heroKey));
			if (hero) {
				deadImage = TheMappedImageCollection->findImageByName(
					TheCreateAHeroManager->GetButtonImageName(hero));
				if (!deadImage)
					deadImage = TheMappedImageCollection->findImageByName(
						AsciiString("BuildingNoArt"));
			}
		} else {
			deadImage = TheMappedImageCollection->findImageByName(name);
		}
		if (deadImage)
			return deadImage;
		Object *current = m_object;
		ThingTemplate *currentTemplate = current->getTemplate();
		deadImage = getButtonImage(currentTemplate, current);
	} else {
		deadImage = getButtonImage(object->getTemplate(), object);
	}
	return deadImage;
}

void *RespawnUpdate::rva004AF25D()
{
	if (respawnTemplate == (void *)-1) {
		void *found = (void *)TheThingFactory->findTemplate(reinterpret_cast<const RespawnUpdateModuleDataRef *>(getModuleData())->m_respawnAsTemplate);
		respawnTemplate = found;
		if (found == 0)
			respawnTemplate = m_object->m_template;
	}
	return respawnTemplate;
}
