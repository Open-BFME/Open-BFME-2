// ?createCrate@CreateCrateDie@@AAEPAVObject@@PBVCrateTemplate@@@Z
// partial score=0.96 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ?createCrate@CreateCrateDie@@AAEPAVObject@@PBVCrateTemplate@@@Z, retail 0x00485565 590B: CreateCrateDie::createCrate picks a crate name by chance roll then creates it via ThingFactory.
// Evidence: donor CreateCrateDie.cpp createCrate shape with GetGameLogicRandomValueReal lines 167/226 plus caller 0x00485882 in onDie 0x004857B3 passing CrateTemplate 0x002C7501 path; rowed callees 0x0028B511 0x00234092 0x002D06CA 0x0030AA80 0x0030AB9D 0x0028B4CE 0x005508E2 0x00272870 0x002728C5 0x00270644 plus pins 0x00285202 0x002D0A23.
#include "ascii_string.h"

float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

extern const char g_Rva0107301CEmptyString[];
extern float g_00BCFB10;

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct FindPositionOptions
{
	unsigned int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	const void *ignoreObject;
	const void *sourceToPathToDest;
	const void *relationshipObject;
};

enum
{
	FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS = 8
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class ThingTemplate;
class Team;
class Drawable;
class Object;

struct CreateMask
{
	unsigned int words[4];
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(float angle);
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	int rva0028B511() const;
	void rva0028B4CE(PathfindLayerEnum layer);
	float getMajorRadius() const { return *(const float *)((const char *)this + 0xB8); }
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
};

class Drawable
{
public:
	void rva00272870(int x);
	void rva002728C5(float a, float b);
};

class Rva00270644
{
public:
	void rva00270644(float a, float b);
};

class PartitionManager
{
public:
	static bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern Rva002D06CA *g_009FF000;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};

struct CrateCreationNode
{
	CrateCreationNode *m_next;
	CrateCreationNode *m_prev;
	AsciiString m_crateName;
	float m_crateChance;
};

struct CrateNameList
{
	CrateCreationNode *m_node;
};

class CrateTemplate
{
public:
	char m_pad[0x3C];
	CrateNameList m_possibleCrates;
};

class CreateCrateDie
{
private:
	char m_pad[8];
	Object *m_object;
	Object *createCrate(const CrateTemplate *currentCrateData);
};

// ?createCrate@CreateCrateDie@@AAEPAVObject@@PBVCrateTemplate@@@Z present-unmatched
Object *CreateCrateDie::createCrate(const CrateTemplate *currentCrateData)
{
	Object *obj = m_object;
	int layer = obj->rva0028B511();
	float pick = GetGameLogicRandomValueReal(0.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp", 167);
	float runningTotal = 0.0f;
	AsciiString crateName(g_Rva0107301CEmptyString);

	CrateCreationNode *sentinel = currentCrateData->m_possibleCrates.m_node;
	for (CrateCreationNode *iter = sentinel->m_next; iter != sentinel; iter = iter->m_next) {
		runningTotal += iter->m_crateChance;
		if (runningTotal > pick) {
			crateName = iter->m_crateName;
			break;
		}
	}

	const ThingTemplate *crateType = (const ThingTemplate *)g_009FF000->rva002D06CA(&crateName);
	if (!crateType)
		return 0;

	Object *object = m_object;
	Coord3D centerPoint;
	centerPoint.x = object->getPosition()->x;
	centerPoint.y = object->getPosition()->y;
	centerPoint.z = object->getPosition()->z;

	Coord3D creationPoint;
	FindPositionOptions fpOptions;
	fpOptions.startAngle = -99999.9f;
	fpOptions.maxZDelta = 1e10f;
	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 5.0f;
	fpOptions.ignoreObject = 0;
	fpOptions.sourceToPathToDest = 0;
	fpOptions.relationshipObject = object;
	fpOptions.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS;

	if (layer != LAYER_GROUND) {
		creationPoint = centerPoint;
	} else if (PartitionManager::findPositionAround(&centerPoint, &fpOptions, &creationPoint)) {
	} else {
		fpOptions.minRadius = 0.0f;
		fpOptions.maxRadius = 125.0f;
		fpOptions.relationshipObject = 0;
		fpOptions.flags = 0;
		if (!PartitionManager::findPositionAround(&centerPoint, &fpOptions, &creationPoint))
			return 0;
	}

	CreateMask mask;
	ji_006291ae(&mask, 0, 16);

	Object *newCrate = ((ThingFactory *)g_009FF000)->newObject(crateType, 0, &mask, false);
	newCrate->setPosition(&creationPoint);
	newCrate->setOrientation(GetGameLogicRandomValueReal(0.0f, 2.0f * 3.14159265359f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp", 226));
	newCrate->rva0028B4CE((PathfindLayerEnum)layer);

	Drawable *d = newCrate->getDrawable();
	if (d) {
		d->rva00272870(5);
		d->rva002728C5(newCrate->getMajorRadius() * g_00BCFB10, newCrate->getMajorRadius() * g_00BCFB10);
		((Rva00270644 *)d)->rva00270644(1.0f, 0.03f);
	}

	return newCrate;
}
