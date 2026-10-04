// ?update@WanderAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.85 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?update@WanderAIUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004A9424:
// slot 0 of WanderAIUpdate's UpdateModuleInterface vftable 0x00C53D24
// (primary vftable 0x00C53D30; ctor 0x004A931F in WanderAIUpdate.cpp; the
// random calls name WanderAIUpdate.cpp). BFME2 rewrites Zero Hour's
// wander: run AIUpdateInterface::update (0x0026E267) first; nothing unless
// the object is of the data's KindOf (+0x68, -1 for any) and the AI's slot
// 110 (0x002645FF) agrees; give the object status 3 unless the data's +0x6C
// flag; with the data's +0x64 flag attack the closest object in vision
// range that the 0x002611F2/0x00261C72/alive/0x00261058/not-self chain
// (BFME2's partition filter chain, the view AIStructureCreepTactic.cpp
// documents) accepts, else move to the object's position jittered by up to
// the data's +0x70 in x and y. Never sleeps.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BF8FF0; the out-of-line ctor 0x002611F2.
class Rva002611F2 : public Rva000421C8
{
public:
	Rva002611F2(Object *obj);	// 0x002611F2
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C53D18, allow 0x00261C72: no members of its own.
class Rva00261C72Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

#define WANDER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\WanderAIUpdate.cpp"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);	// 0x00233FF4

enum KindOfType
{
	KINDOF_INVALID = -1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA004A9424_3 = 3
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;	// 0x0006F039
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	void setStatus(ObjectStatusTypes bit, bool flag);	// 0x0023DB0E
	float getVisionRange() const;	// 0x0028DDE0
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

struct WanderAIUpdateModuleData
{
	char m_pad00[0x64];
	bool m_64;		// +0x64 attack instead of wandering
	char m_pad65[0x68 - 0x65];
	KindOfType m_68;	// +0x68 the KindOf it needs (-1 for any)
	bool m_6C;		// +0x6C
	char m_pad6D[0x70 - 0x6D];
	int m_70;		// +0x70 the wander distance
};

class ModuleData;

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
	void rva0026C26D(const Coord3D *pos, int cmdSource);	// 0x0026C26D
	void rva0026C2D9(Object *target, int maxShots, CommandSourceType cmdSource);	// 0x0026C2D9
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual bool rva002645FF();	// slot 110 (0x002645FF)
	virtual UpdateSleepTime update();	// 0x0026E267
};

class WanderAIUpdate : public AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
private:
	const WanderAIUpdateModuleData *getWanderAIUpdateModuleData() const
	{
		return (const WanderAIUpdateModuleData *)m_moduleData;
	}
};

UpdateSleepTime WanderAIUpdate::update()
{
	const WanderAIUpdateModuleData *data = getWanderAIUpdateModuleData();
	Object *obj = m_object;
	AIUpdateInterface::update();
	if (data->m_68 != KINDOF_INVALID && !obj->isKindOf(data->m_68))
		return UPDATE_SLEEP_NONE;
	if (!rva002645FF())
		return UPDATE_SLEEP_NONE;
	if (!data->m_6C && !obj->testStatus(OBJECT_STATUS_RVA004A9424_3))
		obj->setStatus(OBJECT_STATUS_RVA004A9424_3, true);
	Coord3D dest;
	int range;
	if (data->m_64) {
		const Coord3D *pos = obj->getPosition();
		Coord3D center = *pos;
		Rva002614DFFilter notSelf(obj);
		Rva0026119DFilter alive;
		Rva00261058 stealth(obj, false);
		Rva00261C72Filter fourth;
		Rva002611F2 first(obj);
		first.link(fourth.link(alive.link(stealth.link(&notSelf))));
		Object *target = ThePartitionManager->getClosestObject(&center, m_object->getVisionRange(), 0, &first);
		if (target) {
			rva0026C2D9(target, 0x7FFFFFFF, CMD_FROM_AI);
			return UPDATE_SLEEP_NONE;
		}
		dest.x = pos->x;
		dest.y = pos->y;
		dest.z = pos->z;
		range = data->m_70;
		dest.x += GetGameLogicRandomValue(-range, range, WANDER_FILE, 0x6D);
		dest.y += GetGameLogicRandomValue(-range, range, WANDER_FILE, 0x6E);
		rva0026C26D(&dest, CMD_FROM_AI);
		return UPDATE_SLEEP_NONE;
	}
	dest.x = obj->getPosition()->x;
	dest.y = obj->getPosition()->y;
	dest.z = obj->getPosition()->z;
	range = data->m_70;
	dest.x += GetGameLogicRandomValue(-range, range, WANDER_FILE, 0x79);
	dest.y += GetGameLogicRandomValue(-range, range, WANDER_FILE, 0x7A);
	rva0026C26D(&dest, CMD_FROM_AI);
	return UPDATE_SLEEP_NONE;
}
