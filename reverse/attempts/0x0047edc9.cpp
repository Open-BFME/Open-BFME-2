// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.1025 date=2026-10-09
// BFME2 target identity: native47EDC9..47F92D (2916B), update secondary receiver +0x10,
// ctor47ECA8 and WB011B2240 AnimalAIUpdate.cpp assertions154..245.
// Target-reconciled fields: scaring3D8/original3DC/processed3E8/returning3E9,
// frame40/current state4, template name64, Object flee distance1AC.
// Target behavior: 224-bit masks; Alive filter; emitter kind146; radius against
// Object::distSq(emitter position); returning delta includes Z; same-enemy
// logging reaches the common blah-1 exit; first wander linesBC/BF, secondF2/F5.
// Donor semantic guide: BFME1 revision9cbfb551fe20dae985f91f2319d8997287b6a705,
// targets/game/reverse/attempts/0x002b32a0.cpp and its audited identity receipt.
// Bank only. Native frame8C versus emittedA0, register/slot lifetimes and
// typed callee ownership remain unresolved. No symbols pins were added.
// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.3344272076372315 date=2026-09-26
// cl: /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "coord3d.h"
#include "string_base.h"
template<>inline const char*StringBase<char>::str()const{static const char TheNullChr=0;return m_data?m_data->data:&TheNullChr;}
#include "ascii_string.h"
#include <math.h>
inline Coord3D::Coord3D(){}
inline Coord3D::Coord3D(const Coord3D&t){x=t.x;y=t.y;z=t.z;}
inline Coord3D::~Coord3D(){}
inline Coord3DBase&Coord3DBase::operator=(const Coord3DBase&t){struct Raw{unsigned x,y,z;};*(Raw*)this=*(const Raw*)&t;return *this;}
inline Coord3D&Coord3D::operator=(const Coord3D&t){Coord3DBase*b=this;*b=t;return *this;}
__forceinline Coord3D&Coord3D::Scale(float n){x*=n;y*=n;z*=n;return *this;}


// BFME-only AnimalAIUpdate::update.  There is no Zero Hour twin; the owning
// secondary update-interface slot is installed by the independently named
// constructor: primary object +0x10, vtable VA 0x010C5590, slot 0.
// Bank only: unresolved frame/register scheduling remains. See the adjacent
// identity_evidence/002B32A0-animal-update.md receipt before resuming.

typedef unsigned int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Overridable{public:virtual ~Overridable();const Overridable*getFinalOverride()const;Overridable*m_nextOverride;};
class ThingTemplate:public Overridable{public:char m_08[0x5c];AsciiString m_name;const AsciiString&getName()const{return m_name;}};
class Thing{public:virtual ~Thing();const ThingTemplate*m_template;const ThingTemplate*getTemplate()const{return m_template;}const Coord3D*getUnitDirectionVector2D()const;};
class Object:public Thing{public:float rva002615E3(const Coord3D*)const;};
class BfmeSpotCN;class Gen_0016E370{public:float bfmeDistanceSquared(const BfmeSpotCN*)const;};
class AICommandInterface{public:void aiIdle(CommandSourceType);void aiMoveToPosition(const Coord3D*,CommandSourceType);void aiBfmeCommand2E(Object*,CommandSourceType);};
template<int N>class RvaAnimalSlots:public RvaAnimalSlots<N-1>{public:virtual void slot(char(*)[N]);};template<>class RvaAnimalSlots<0>{};
class RvaAnimalPrimary:public RvaAnimalSlots<142>{public:virtual void rva1fc(int);};
class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
	unsigned getCurrentStateID()const;
	void aiIdle(CommandSourceType source);
	void aiMoveToPosition(const Coord3D *position, CommandSourceType source);
};

class AnimalAIUpdateDestinationLayer
{
public:
	bool isReachableLayer(const Coord3D *position) const;
	char m_00[8];Object*m_object;
};

class AnimalAIUpdate
{
public:
	virtual UpdateSleepTime update();
};

struct AnimalAIUpdateModuleDataView
{
	unsigned char m_beforeFleeRange[0x64];
	int m_fleeRange;
	int m_fleeDistance;
	int m_wanderPercentage;
	int m_maxWanderDistance;
	int m_maxWanderRadius;
	unsigned int m_updateTimer;
};

class TerrainLogic
{
public:
	int getLayerForDestination(Object *object, const Coord3D *position);
};

class GameLogic
{
public:
	unsigned char m_beforeFrame[0x40];
	unsigned int m_frame;
	Object *findObjectByID(int id);
};

class PartitionFilter;
class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float range,
		int measureFrom, PartitionFilter *filters);
};

extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
extern "C" unsigned char bfmeRetailCritterDesyncFlag;extern bool g_012F0239;
class CRCParameterCheck; extern "C" int __cdecl fprintf(CRCParameterCheck*,const char*,...);
extern CRCParameterCheck *bfmeRetailCritterDesyncSink;
extern int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);
extern float __cdecl Sin(float radians);
extern float __cdecl Cos(float radians);

template<int N>class BitFlags{public:enum BogusInitType{kInit=0};BitFlags(BogusInitType,int);BitFlags(BogusInitType,int,int,int,int);unsigned m_bits[(N+31)/32];};

extern "C" void*__cdecl memset(void*,int,unsigned);
template<int N> __declspec(noinline) BitFlags<N>::BitFlags(BogusInitType,int a){memset(m_bits,0,sizeof(m_bits));m_bits[(unsigned)a>>5]|=1u<<((unsigned)a&31);}
template<int N> __declspec(noinline) BitFlags<N>::BitFlags(BogusInitType,int a,int b,int c,int d){memset(m_bits,0,sizeof(m_bits));m_bits[(unsigned)a>>5]|=1u<<((unsigned)a&31);m_bits[(unsigned)b>>5]|=1u<<((unsigned)b&31);m_bits[(unsigned)c>>5]|=1u<<((unsigned)c&31);m_bits[(unsigned)d>>5]|=1u<<((unsigned)d&31);}
typedef BitFlags<224> KindOfMaskType;extern const KindOfMaskType KINDOFMASK_NONE;
class PartitionFilter{public:PartitionFilter():m_next(0){}virtual ~PartitionFilter(){}virtual bool allow(Object*)=0;virtual int getPlayerMask();PartitionFilter*link(PartitionFilter*);PartitionFilter*m_next;};
class Rva0025F2D0KindOfAnyFilter:public PartitionFilter{public:__forceinline Rva0025F2D0KindOfAnyFilter(const KindOfMaskType&m);virtual ~Rva0025F2D0KindOfAnyFilter(){}virtual bool allow(Object*);KindOfMaskType m_mask;};
class PartitionFilterRelationship:public PartitionFilter{public:PartitionFilterRelationship(Object*o,int f,bool b):m_object(o),m_flags(f),m_match(b){}virtual ~PartitionFilterRelationship(){}virtual bool allow(Object*);virtual int getPlayerMask();Object*m_object;int m_flags;bool m_match;};
class PartitionFilterAlive:public PartitionFilter {public:virtual bool allow(Object*);};
class PartitionFilterAcceptByKindOf:public PartitionFilter{public:PartitionFilterAcceptByKindOf(const KindOfMaskType&,const KindOfMaskType&);virtual ~PartitionFilterAcceptByKindOf(){}virtual bool allow(Object*);KindOfMaskType m_mustBeSet,m_mustBeClear;};


static const char *const kAnimalSource =
	"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\AnimalAIUpdate.cpp";

static __forceinline const AnimalAIUpdateModuleDataView *animalData(AnimalAIUpdate *self)
{
	return *(AnimalAIUpdateModuleDataView **)((char *)self - 0x0c);
}

static __forceinline Object *animalObject(AnimalAIUpdate *self)
{
	return *(Object **)((char *)self - 8);
}

static __forceinline Coord3D *animalPosition(Object *object)
{
	return (Coord3D *)((char *)object + 0x38);
}

static __forceinline ObjectID animalID(Object *object)
{
	return *(ObjectID *)((char *)object + 0x74);
}

static __forceinline const char *animalDebugName(Object*object){return ((const StringBase<char> *)&object->getTemplate()->getName())->str();}
static __forceinline AICommandInterface*animalCommands(AnimalAIUpdate*self){return (AICommandInterface*)((char*)self+0x10);}
static __forceinline RvaAnimalPrimary*animalPrimary(AnimalAIUpdate*self){return (RvaAnimalPrimary*)((char*)self-0x10);}
static __forceinline Coord3D *originalPosition(AnimalAIUpdate *self)
{
	return (Coord3D *)((char *)self + 0x3dc);
}

static __forceinline ObjectID &scaringObjectID(AnimalAIUpdate *self)
{
	return *(ObjectID *)((char *)self + 0x3d8);
}

static __forceinline unsigned char &processedOne(AnimalAIUpdate *self)
{
	return *(unsigned char *)((char *)self + 0x3e8);
}

static __forceinline unsigned char &returning(AnimalAIUpdate *self)
{
	return *(unsigned char *)((char *)self + 0x3e9);
}

static __forceinline void animalLog(const char *text)
{
	if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
		fprintf(bfmeRetailCritterDesyncSink, text);
}

UpdateSleepTime AnimalAIUpdate::update()
{
	AnimalAIUpdate *self = this;
	CRCParameterCheck*log;
	const AnimalAIUpdateModuleDataView *data = animalData(self);
	Object *animal = animalObject(self);
	char *machine = *(char **)((char *)self + 0x20);
	char *state = *(char **)(machine + 4);
	int stateID = state ? *(int *)(state + 4) : 999999;

	((AIUpdateInterface *)self)->AIUpdateInterface::update();

	if (!processedOne(self))
	{
		*originalPosition(self) = *animalPosition(animal);
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			fprintf(log,
				"CritterDesync:  m_processedOne false - setting m_originalPos to %g,%g,%g",
				originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		processedOne(self) = 1;
	}

	Coord3D *position = animalPosition(animal);
	if (!((AnimalAIUpdateDestinationLayer*)((char*)self-0x10))->isReachableLayer(position))
	{
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			fprintf(log,
				"CritterDesync:  animal %s is in a bad area, return to origin %g,%g,%g.",
				animalDebugName(animal), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		animalCommands(self)->aiIdle(CMD_FROM_AI);
		animalCommands(self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
		animalPrimary(self)->rva1fc(0);
		returning(self) = 1;
		return UPDATE_SLEEP_NONE;
	}

	if (returning(self))
	{
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			fprintf(log,
				"CritterDesync:  m_returning is true - animal %s is checking if we are near origin %g,%g,%g to stop.",
				animalDebugName(animal), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);

		Coord3D delta=*originalPosition(self);delta.x-=position->x;delta.y-=position->y;delta.z-=position->z;
		if(delta.GetLengthEstimate2D() < 10.0f)
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s is finished returning to origin.",
					animalDebugName(animal));
			returning(self) = 0;
		}
		else
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s is NOT finished returning to origin.",
					animalDebugName(animal));
			return UPDATE_SLEEP_NONE;
		}
	}

	if (TheGameLogic->m_frame % data->m_updateTimer == 0)
	{
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			fprintf(log,
				"CritterDesync:  animal %s is doing periodic search for enemies.",
				animalDebugName(animal));
		Object *enemy;
		{
			Rva0025F2D0KindOfAnyFilter kindFilter(KindOfMaskType(KindOfMaskType::kInit, 8, 9, 10, 11));
			PartitionFilterRelationship enemyFilter(animal,3,false);
			enemy = ThePartitionManager->getClosestObject(animalPosition(animal),
				(float)data->m_fleeRange, 0, enemyFilter.link(PartitionFilterAlive().link(&kindFilter)));
		}
		if (enemy)
		{
			ObjectID enemyID = animalID(enemy);
			bool same = enemyID == scaringObjectID(self) &&
				(((const AIUpdateInterface*)((char*)self-0x10))->getCurrentStateID() == 20 || ((const AIUpdateInterface*)((char*)self-0x10))->getCurrentStateID() == 19);
            if(same)
			{
				if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
					fprintf(log,
						"CritterDesync:  animal %s(%d) sees SAME enemy %s(%d) to be scared of.",
						animalDebugName(animal), animalID(animal), animalDebugName(enemy), enemyID);
				}
            else {
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s(%d) found NEW enemy %s(%d) to be scared of RUNAWAYPANIC.",
					animalDebugName(animal), animalID(animal), animalDebugName(enemy), enemyID);
			*(float *)((char *)animal + 0x1ac) = (float)data->m_fleeDistance;
			animalCommands(self)->aiBfmeCommand2E(TheGameLogic->findObjectByID(animalID(enemy)), (CommandSourceType)1);
			scaringObjectID(self) = animalID(enemy);
            }
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s(%d) blah-1",
					animalDebugName(animal), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}

	}

		if (stateID != 0)
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s(%d) is not idle, sleep.",
					animalDebugName(animal), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}
		scaringObjectID(self) = 0;
		if (GetGameLogicRandomValue(0, 100, (char *)kAnimalSource, 0x9a)
			< data->m_wanderPercentage)
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s(%d) dice roll suceeded for wanderpercentage",
					animalDebugName(animal), animalID(animal));
			Object*emitter;{PartitionFilterAcceptByKindOf emitterFilter(KindOfMaskType(KindOfMaskType::kInit,0x92),KINDOFMASK_NONE);
			emitter = ThePartitionManager->getClosestObject(animalPosition(animal),
				(float)data->m_fleeRange, 1, &emitterFilter);}
			animalPrimary(self)->rva1fc(0);
			if (emitter)
			{
				if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
					fprintf(log,
						"CritterDesync:  animal %s(%d) EMITTER CASE",
						animalDebugName(animal), animalID(animal));
				int radius = data->m_maxWanderRadius;
				if (animal->rva002615E3(animalPosition(emitter)) > (float)(radius * radius))
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						fprintf(log,
							"CritterDesync:  animal %s(%d) moving to emitter at %g,%g,%g",
							animalDebugName(animal), animalID(animal),
							animalPosition(emitter)->x, animalPosition(emitter)->y,
							animalPosition(emitter)->z);
					animalCommands(self)->aiMoveToPosition(animalPosition(emitter), CMD_FROM_AI);
				}
				else
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						fprintf(log,
							"CritterDesync:  animal %s(%d) wander to random location",
							animalDebugName(animal), animalID(animal));
					animal->getUnitDirectionVector2D();
					Coord3D destination = *animal->getUnitDirectionVector2D();
					float angle = (float)GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xbc);
					destination.x += Cos(angle);destination.y += Sin(angle);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xbf);
					destination.Scale(distance);
					destination.x += position->x;destination.y += position->y;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							fprintf(log,
								"CritterDesync:  animal %s(%d) wandering to dest %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
						g_012F0239=true;animalCommands(self)->aiMoveToPosition(&destination, CMD_FROM_AI);g_012F0239=false;
					}
					else
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							fprintf(log,
								"CritterDesync:  animal %s(%d) CANNOT wander to dest %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
			else
			{
				if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
					fprintf(log,
						"CritterDesync:  animal %s(%d) NO EMITTER CASE",
						animalDebugName(animal), animalID(animal));
				Coord3D delta=*originalPosition(self);delta.x-=position->x;delta.y-=position->y;delta.z-=position->z;
				if(delta.GetLengthEstimate() > (float)data->m_maxWanderRadius)
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						fprintf(log,
							"CritterDesync:  animal %s(%d) returning to m_originalPos %g,%g,%g",
							animalDebugName(animal), animalID(animal),
							originalPosition(self)->x, originalPosition(self)->y,
							originalPosition(self)->z);
					animalCommands(self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
				}
				else
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						fprintf(log,
							"CritterDesync:  animal %s(%d) wandering to random spot",
							animalDebugName(animal), animalID(animal));
					animal->getUnitDirectionVector2D();
					Coord3D destination = *animal->getUnitDirectionVector2D();
					float angle = (float)GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xf2);
					destination.x += Cos(angle);destination.y += Sin(angle);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xf5);
					destination.Scale(distance);
					destination.x += position->x;destination.y += position->y;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							fprintf(log,
								"CritterDesync:  animal %s(%d) wandering to %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
						animalCommands(self)->aiMoveToPosition(&destination, CMD_FROM_AI);
					}
					else
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							fprintf(log,
								"CritterDesync:  animal %s(%d) CANNOT wander to %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
		}
		else
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				fprintf(log,
					"CritterDesync:  animal %s(%d) dice roll failed.",
					animalDebugName(animal), animalID(animal));
		}

	if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
		fprintf(log,
			"CritterDesync:  animal %s(%d) finished update.", animalDebugName(animal), animalID(animal));

	return UPDATE_SLEEP_NONE;
}
