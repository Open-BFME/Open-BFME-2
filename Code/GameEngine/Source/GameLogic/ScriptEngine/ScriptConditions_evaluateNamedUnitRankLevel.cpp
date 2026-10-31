// ?evaluateNamedUnitRankLevel@ScriptConditions@@IAE_NPAVParameter@@0@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateNamedUnitRankLevel@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E92DF 148B
// Target evidence: retail pushes Parameter* to rowed getUnitNamed 0x003588E7,
// warn-once byte at 0x00E02E34, string at 0x00835B8C, rowed concat 0x00006987,
// rowed AppendDebugMessage 0x00205263, Object+0x264 null-checked then +0x24
// compared >= with second Parameter+0x08, ret 8. Donor: BFME1
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsNamedUnit.cpp
// evaluateNamedUnitRankLevel (same name/mangled/shape, Body+0x28 rank there).
// Target layout from Rva003E514F/Rva003BC96F siblings: Object+0x264 inner
// with rank at +0x24, not donor +0x210/+0x28.
// TheScriptEngine is 0x00DFE16C (reverse/symbols.csv).
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
extern ScriptEngine *TheScriptEngine;
bool g_00E02E34;	// retail RVA 0x00A02E34 (.data, 4 bytes), defined here: nothing else owns it

#include "../../../Include/GameLogic/ScriptConditions.h"

// The warn block is textual A and the rank load is textual B, because retail's
// +0x1c is a jne OUT of the warn block into the out-of-line rank load; both
// falses reach the single trailing return false, which is the xor al,al / ret 8
// sink at +0x67.
bool ScriptConditions::evaluateNamedUnitRankLevel(Parameter *pUnitParm, Parameter *pRankParm)
{
	Object *pUnit = TheScriptEngine->getUnitNamed(pUnitParm);
	if (pUnit == 0) {
	if (!g_00E02E34) {
		g_00E02E34 = true;
		AsciiString message("ScriptConditions::evaluateNamedUnitRankLevel: Unit not found: ");
		message += pUnitParm->getString();
		TheScriptEngine->AppendDebugMessage(message, false);
	}
	} else {
		ExperienceTracker *body = pUnit->m_experienceTracker;
		if (body != 0)
			return body->getRank() >= pRankParm->getInt();
	}
	return false;
}