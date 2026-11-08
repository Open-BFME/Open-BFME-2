// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /arch:SSE /DNDEBUG /MD /EHsc
// WB116CFB0 names GettingBuiltBehavior::resumeBuildingConstruction.
// Native45499B..454B5C uses the +20 interface receiver (object at -18,
// module data at -1C). Target fields and calls follow the existing ctor,
// primary/interface units; this secondary ABI view does not claim a primary ABI.
#include "ascii_string.h"
#include <string.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
#include "../../../../Include/GameClient/Drawable.h"
#include "../../../Common/Thing/thing.h"
// WBCA4BE0 is an empty instance method invoked on the builder drawable;
// retail uses the complete shared RET at B3FD0. Original spelling unknown.
enum ObjectStatusTypes { STATUS_NONE = 0 };
enum CommandSourceType { SOURCE_NONE = 0 };
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
struct PlayerPart { unsigned char pad[0x1bc]; bool alternate; };
class Team;
class Player {
public:
 bool rva002AA245() const; // 0x002AA245
 unsigned char pad[0x34]; PlayerPart *part;
 unsigned char pad38[0x2ec-0x38]; Team *team;
};
struct GettingBuiltConditions { unsigned int words[19]; __forceinline unsigned test(int i) const {return words[i>>5] & (1u<<(i&31));} __forceinline void set(int i) {words[i>>5]|=1u<<(i&31);} __forceinline void clear(int i) {words[i>>5]&=~(1u<<(i&31));} };
class Object : public Thing {
public:
 Player *getControllingPlayer() const;
 void setProducer(Object *);
 void setBuilder(const Object *);
 void setEffectivelyDead(bool);
 void setStatus(ObjectStatusTypes, bool);
 bool testStatus(ObjectStatusTypes) const;
 void rva0028AE6D();
 unsigned char pad44[0x10C - 0x60]; GettingBuiltConditions conditions;
 unsigned char pad158[0x258-0x158]; AIUpdateInterface *ai;
 unsigned char pad25c[0x280-0x25c]; float construction;
 unsigned char pad284[0x438-0x284]; unsigned char privateStatus;
};
class ThingTemplate;
struct CreateMask { unsigned int bits[4]; };
enum ObjectID; class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); Object *newObject(const ThingTemplate *,Team *,const CreateMask *,ObjectID); };
extern ThingFactory *TheThingFactory;
#include "../../../../Include/GameLogic/Module/GettingBuiltBehaviorModuleData.h"
class GettingBuiltBehaviorSecondary {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void rva00453652(bool);
 void resumeBuildingConstruction(bool);
};
void GettingBuiltBehaviorSecondary::resumeBuildingConstruction(bool instant)
{
 const GettingBuiltBehaviorModuleData *data = *(const GettingBuiltBehaviorModuleData **)((char *)this-0x1c);
 Object *object = *(Object **)((char *)this-0x18);
 if (data->m_workerName.isEmpty()) { rva00453652(instant); return; }
 Player *player = object->getControllingPlayer();
 if (!player) return;
 if (!object->getControllingPlayer()->rva002AA245()) return;
 const ThingTemplate *thingTemplate;
 if (data->m_testFaction && object->getControllingPlayer()->part->alternate)
   thingTemplate = TheThingFactory->findTemplate(data->m_evilWorkerName);
 else thingTemplate = TheThingFactory->findTemplate(data->m_workerName);
 if (!thingTemplate) return;
 CreateMask mask;
 memset(&mask,0,sizeof(mask));
 Team *team = player->team;
 Object *builder = TheThingFactory->newObject(thingTemplate,team,&mask,(ObjectID)0);
 if (!builder) return;
 builder->setPosition(&object->m_cachedPos);
 builder->setProducer(object);
 object->setBuilder(builder);
 *((bool *)this+0x1c) = true;
 if (object->privateStatus & 1) {
   object->setEffectivelyDead(false);
   object->construction = 0.0f;
   object->setStatus((ObjectStatusTypes)0x57,false);
   object->setStatus((ObjectStatusTypes)2,true);
   if (object->conditions.test(5)) { object->conditions.clear(5); object->rva0028AE6D(); }
   if (object->conditions.test(62)) { object->conditions.clear(62); object->rva0028AE6D(); }
   if (object->conditions.test(60)) { object->conditions.clear(60); object->rva0028AE6D(); }
   if (!object->conditions.test(69)) { object->conditions.set(69); object->rva0028AE6D(); }
 }
 AIUpdateInterface *ai = builder->ai;
 if (ai) {
   if (object->testStatus((ObjectStatusTypes)2)) ai->aiResumeConstruction(object,(CommandSourceType)2);
   else ai->rva0036F19B(object,(CommandSourceType)2);
 }
 Drawable *drawable = builder->getDrawable();
 if (drawable) drawable->rva000B3FD0();
 *((bool *)this+0x1d) = true;
}

