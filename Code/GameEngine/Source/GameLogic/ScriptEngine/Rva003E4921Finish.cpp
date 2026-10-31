// ?rva003E4921@ScriptConditions@@QAE_NPAVParameter@@@Z
// cl: /EHsc /Ireference/shims/bfme2_ascii
// ?rva003E4921@ScriptConditions@@QAE_NPAVParameter@@@Z
// @0x003E4921 151B gate condition via rowed getUnitNamed 0x003588E7 plus
// rowed nameToKey 0x00148E1A plus rowed findModule 0x0028B6D6.
// Evidence: vslot slot 17 of 0x00835B38; caller none; static
// GateOpenAndCloseBehavior key; donor BFME1 ScriptActionsGates.
// Each failing condition returns immediately so the false arm owns the
// fallthrough and the true arm becomes the forward jmp target, which is the
// polarity retail emits (jne over xor al,al to mov al,1).
class AsciiString;
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Parameter;
class Object;
class Module;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/Common/Module.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
struct Coord3D;
class Rva00261C89;
class Player;
class ContainModuleInterface;
class PolygonTrigger;
class BodyModuleInterface;
class ThingTemplate;
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

class GateOpenAndCloseBehaviorView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual bool stateIsOne() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual bool isReady() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	int m_pad40[15];
	int m_state40;
};

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::rva003E4921(Parameter *param)
{
	Object *object = TheScriptEngine->getUnitNamed(param);
	if (!object)
		return false;
	static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Module *module = object->findModule(gateKey);
	GateOpenAndCloseBehaviorView *gate = module ? (GateOpenAndCloseBehaviorView *)((char *)module - 4) : 0;
	if (gate == 0)
		return false;
	if (!gate->isReady())
		return false;
	bool result = gate->m_state40 <= 0 || gate->stateIsOne();
	return result;
}