// cl: /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003E4E6AGet@@YG_NPAVParameter@@@Z @0x003E4E6A 59B leaf single-param unit-mesh check via rowed ScriptEngine::getUnitNamed and rowed MeshGeometryClass::get_polys. Evidence: caller 0x003EBEA1; prev 0x003E4C77 next 0x003E4EA5 same // cl: /O1.
class Parameter;
class Vector3i16;
// ledger 0x000B49A1 (named MeshGeometryClass::get_polys): [[this+0x2C]+0xC].
class MeshGeometryClass
{
protected:
	Vector3i16 *get_polys();
};

class ExperienceTracker : public MeshGeometryClass
{
public:
	int getRank() const { return m_rank; }
	int getLevelCap() { return (int)get_polys(); }
private:
	unsigned char m_pad[0x24];
	int m_rank; // +0x24
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
struct Coord3D;
class Rva00261C89;
class Player;
class Module;
class ContainModuleInterface;
class ScriptConditions;
class AsciiString;
class PolygonTrigger;
class BodyModuleInterface;
class ThingTemplate;
class AIUpdateInterface;
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
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
bool __stdcall Rva003E4E6AGet(Parameter *parameter)
{
    if (parameter) {
        Object *obj = TheScriptEngine->getUnitNamed(parameter);
        if (obj) {
            ExperienceTracker *tracker = obj->m_experienceTracker;
            if (tracker) {
                int rank = tracker->getRank();
                if (rank > tracker->getLevelCap())
                    return true;
            }
        }
    }
    return false;
}
