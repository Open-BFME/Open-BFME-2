// cl: /DNDEBUG /MD /GX /O1 /arch:SSE /G7
//
// ?construct@DozerAIUpdate@@UAEPAVObject@@PBVThingTemplate@@PBVCoord3D@@MPAVPlayer@@_N@Z, retail 0x00488F52, 231 bytes. VTABLE slot 126 of 0x0084B848 class DozerAIUpdate via ctor 0x004894F5; stores isRebuild at +0x40C then createMachines rowed 0x00488EFC; early NULL and playerType checks match ZH DozerAIUpdate::construct; BuildAssistant globals g_00A027B8 g_00DFEEF8 and task tail via dozer vslots 6 13 12 25 29.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define FALSE false
#define TRUE true
#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};

class Thing;
class ModuleData;
class ThingTemplate;
class Object;
class Player;

enum DozerTask
{
	DOZER_TASK_INVALID = -1,
	DOZER_TASK_FIRST = 0,
	DOZER_TASK_BUILD = DOZER_TASK_FIRST,
	DOZER_TASK_REPAIR,
	DOZER_TASK_FORTIFY
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

class DozerAIInterface
{
public:
	virtual void onDelete() = 0; // 0
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual DozerTask getMostRecentCommand() = 0; // 5
	virtual Bool isTaskPending(DozerTask task) = 0; // 6
	virtual void slot7() = 0; virtual void slot8() = 0; virtual void slot9() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void newTask(DozerTask task, Object *target) = 0; // 12
	virtual void cancelTask(DozerTask task) = 0; // 13
	virtual void slot14() = 0; virtual void slot15() = 0; virtual void slot16() = 0;
	virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void finishBuildingSound() = 0; // 24
	virtual void slot25(const ThingTemplate *what, Player *owningPlayer, const Coord3D *pos, Real angle) = 0; // 25
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual Object *slot29() = 0; // 29
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void onDelete(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
	virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
	virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
	virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69(); virtual void v70();
	virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79(); virtual void v80();
	virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89(); virtual void v90();
	virtual void v91(); virtual void v92();
	virtual DozerAIInterface *getDozerAIInterface();
	virtual void v94(); virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99(); virtual void v100();
	virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107(); virtual void v108(); virtual void v109();
	virtual Bool isIdle() const;
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	Int getPlayerType() const { return m_playerType; }
private:
	unsigned char m_pad[0x5C];
	Int m_playerType; // +0x5C
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva00A027B8
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15();
	virtual Int isLocationLegalToBuild(const Coord3D *pos, const ThingTemplate *what, Real angle, Int flags, Object *obj, void *unk) = 0; // 16
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23();
	virtual Int canMakeUnit(Object *obj, const ThingTemplate *what, Int unk) = 0; // 24
};

extern Rva00A027B8 *g_00A027B8;

class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int unused);
private:
	void createMachines();
	unsigned char m_pad3E4[0x40C - 0x3E8];
	Bool m_isRebuild; // +0x40C
};

Object *DozerAIUpdate::construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int unused)
{
	m_isRebuild = isRebuild;
	createMachines();
	if (what == NULL || pos == NULL || owningPlayer == NULL)
		return NULL;
	if (isRebuild == FALSE)
	{
		if (owningPlayer->getPlayerType() != 1)
			goto checks;
		{
			Player *controlling = getObject()->getControllingPlayer();
			Rva002A8AB1Record *res = g_00DFEEF8->rva002A8AB1(controlling);
			if (res == NULL)
				goto create;
		}
	checks:
		if (g_00A027B8->canMakeUnit(getObject(), what, -1) != 0)
			return NULL;
		if (g_00A027B8->isLocationLegalToBuild(pos, what, angle, 0x49F, getObject(), NULL) != 0)
			return NULL;
	}
create:
	{
		DozerAIInterface *d = this;
		if (d->isTaskPending(DOZER_TASK_BUILD) == TRUE)
			d->cancelTask(DOZER_TASK_BUILD);
		d->slot25(what, owningPlayer, pos, angle);
		d->newTask(DOZER_TASK_BUILD, d->slot29());
		return d->slot29();
	}
}
