// cl: /DNDEBUG /MD /GX
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
// ?rva004AEF46@RespawnUpdate@@QAEXXZ @0x004AEF46 103B
// Chain from Money 0x003B0D7C: RespawnUpdate state gate plus wake plus Money cond-add; layout from RespawnUpdateCtor and Rva004AEFAD.
// Evidence: callees getControllingPlayer 0x0028AFA9 setWakeFrame 0x0044DF71 Money 0x003B0D7C rowed; touches +0x2C +0x30 +0x34 +0x3C +0x40.
class Player;
enum DisabledType;
enum ObjectStatusTypes;
enum ObjectID;
class Player;
class ExitInterface;
class BodyModuleInterface;
class AIUpdateInterface;
class ThingTemplate;
class ExperienceTracker;
class Object
{
public:
    ExitInterface *getObjectExitInterface() const;
    void restoreObjectToWorld(const Coord3D *);
    void rva001E42F2(const int *);
    void rva001E431E(const int *);
    void setStatus(ObjectStatusTypes, bool);
    bool clearDisabled(DisabledType);
    void setDisabledUntil(DisabledType, unsigned);
    void setDisabled(DisabledType);
    void setEffectivelyDead(bool);
    Player *getControllingPlayer() const;
    __forceinline const Coord3D *getPosition() const { return &position; }
    __forceinline ThingTemplate *getTemplate() const { return m_template; }

    char pad00[4];
    ThingTemplate *m_template;
    char pad08[0x38 - 0x08];
    Coord3D position;
    char pad44[0x74 - 0x44];
    int m_heroKey;
    ObjectID producer;
    char pad7C[0x254 - 0x7C];
    BodyModuleInterface *body;
    AIUpdateInterface *ai;
    char pad25C[0x264 - 0x25C];
    ExperienceTracker *m_experienceTracker;
    char pad268[0x45C - 0x268];
    int handle;
};

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1,
    UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class Rva0039B7AD;
class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

#include "../../../../Include/Common/Player.h"

class RespawnUpdate : public UpdateModule
{
public:
	void rva004AEF46();

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};

void RespawnUpdate::rva004AEF46()
{
	Object *obj = m_object;
	Player *player = obj->getControllingPlayer();
	Rva003B0D7C *money;
	if (player != 0)
		money = (Rva003B0D7C *)((char *)player + 0x90);
	else
		money = 0;
	if (m_2C == 0)
		return;
	m_2C = 1;
	setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
	m_34 = (unsigned int)-1;
	m_30 = 0;
	m_40 = 1;
	money->rva003B0D7C(m_3C, (Rva0039B7AD *)((char *)player + 0x3BC), true);
}
