// cl: /Ireference/shims/bfme2_ascii
// ?rva003E514F@ScriptConditions@@IAE_NPAVParameter@@PAUCondA003E514F@@PAUCondB003E514F@@@Z
// retail 0x003E514F, 138 bytes.
// Evidence: leaf via rowed ScriptEngine::getUnitNamed plus ThePlayerList not needed; g_Va009FE16C ScriptEngine global; Object +0x264 ptr plus +0x24 value; op switch 0..5 to setl/setle/sete/setge/setg/setne.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

#include "ascii_string.h"
class AsciiString;
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

extern class ScriptEngine *TheScriptEngine;

struct CondA003E514F
{
	char m_pad[8];
	int m_op;
};

struct CondB003E514F
{
	char m_pad[8];
	int m_value;
};

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::rva003E514F(Parameter *param, CondA003E514F *a, CondB003E514F *b)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (!obj)
		return false;

	ExperienceTracker *inner = obj->m_experienceTracker;
	if (!inner)
		return false;

	int op = a->m_op;
	int count = inner->getRank();
	bool result;

	switch (op)
	{
	case 0:
		result = count < b->m_value;
		break;
	case 1:
		result = count <= b->m_value;
		break;
	case 2:
		result = count == b->m_value;
		break;
	case 3:
		result = count >= b->m_value;
		break;
	case 4:
		result = count > b->m_value;
		break;
	case 5:
		result = count != b->m_value;
		break;
	default:
		result = false;
		break;
	}

	if (result)
		return true;

	return false;
}
