// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateNamedInsideArea, target 0x003E5EFF (116 bytes).
// Identity: target retrieves the named unit and trigger, converts the unit's
// three position coordinates to ints, then calls the trigger point test.

typedef bool Bool;

#include "ascii_string.h"


class ScriptConditions;
class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class ThingTemplate;
class Rva00261C89
{
public:
	Bool rva00261C89(); // 0x00261C89
};

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
class Player;
class Module;
class ContainModuleInterface;
class PolygonTrigger;
class BodyModuleInterface;
class AIUpdateInterface;
class ExperienceTracker;
class Object
{
private:
	friend bool __stdcall Rva003E4B83Get(Parameter *);
public:
	friend class ScriptConditions;
	const Coord3D *getPosition() const { return &m_pos; }
	Rva00261C89 *getField04() const { return (Rva00261C89 *)m_template; }
	bool testStatus(ObjectStatusTypes status) const;
	float getVisionRange() const;
	bool hasSpecialPower(SpecialPowerType type) const;
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned int getID() const { return m_id; }
	const AsciiString *rva00290E67() const;
	bool didEnter(PolygonTrigger *trigger); // 0x0028D718
	bool didExit(PolygonTrigger *trigger); // 0x0028D757
	BodyModuleInterface *getBodyModule() const { return m_body; }
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	void *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38
	char m_pad44[0x30];
	unsigned int m_id; // +0x74
	char m_pad78[0x150];
	unsigned char m_disabledMask[4]; // +0x1C8
	char m_pad1CC[0x84];
	ContainModuleInterface *m_contain; // +0x250
private:
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258 (retail-proven by the kept ScriptActions_doTeamFaceWaypoint row)
	char m_pad25C[0x8];
public:
	ExperienceTracker *m_experienceTracker; // +0x264
	char m_pad268[0xC];
private:
	void *m_containedBy; // +0x274
	char m_pad278[0x1D4];
public:
	int m_44c; // +0x44C
};

#include "../../../../Libraries/Include/Lib/ICoord3D.h"

class Rva0030B719Shape
{
public:
	float getRadius() const;	// 0x0030B719
};

class PolygonTrigger
{
public:
	bool pointInTrigger(const ICoord3D &position);
	void getCenterPoint(Coord3D *pOutCoord) const; // 0x002E38F3
	char m_pad00[0x8];
	Rva0030B719Shape m_shape; // +0x08
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptConditions.h"


Bool ScriptConditions::evaluateNamedInsideArea(
    Parameter *unitParm, Parameter *triggerParm)
{
    Object *object = TheScriptEngine->getUnitNamed(unitParm);
    if (!object)
        return false;

    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(
        triggerParm->getString());
    if (!trigger)
        return false;

    const float *sourcePosition = (const float *)object->getPosition();
    float pCoord[3] = { sourcePosition[0], sourcePosition[1], sourcePosition[2] };
    ICoord3D position;
    position.x = (int)pCoord[0];
    position.y = (int)pCoord[1];
    position.z = (int)pCoord[2];
    return trigger->pointInTrigger(position);
}

// Native 0x003E6032..0x003E609F is a cdecl callback returning full EAX.
// Object positions agree with the named-area sibling at +0x38/+0x3C/+0x40.
// The context contains a point, squared-distance limit, counter and maximum.
// Its original callback and context names remain unknown.
struct Rva003E6032Context
{
    float point[3];
    float limit0C;
    int count10;
    int maximum14;
};

int Rva003E6032(Object *object, Rva003E6032Context *context)
{
    Rva00261C89 *value = object->getField04();
    if (value && value->rva00261C89())
    {
        const float *position = (const float *)object->getPosition();
        float dx = position[0] - context->point[0];
        float dy = position[1] - context->point[1];
        float dz = position[2] - context->point[2];
        float distanceSquared = dz*dz + dy*dy + dx*dx;
        if (distanceSquared > context->limit0C)
        {
            ++context->count10;
            if (context->count10 > context->maximum14)
                return 0;
        }
    }
    return 1;
}
