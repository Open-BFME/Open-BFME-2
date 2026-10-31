// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateBuildingEntered@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E3FFE (123B): unit-player ownership check via +0x250 slot 0x144 mask
// Evidence: neighbours ScriptConditions_evaluateNamedUnit and evaluateIsBuildingEmpty same flags
// rowed getUnitNamed 0x003588E7 pin rva00357B82 rowed getPlayerFromMask getEachPlayerFromMask
// globals TheScriptEngine ThePlayerList caller 0x003EAE3B.
class Parameter;
class Player;
class ContainModuleInterface;
class Rva003E3FFEFace
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual int getMask();
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
class Module;
class ScriptConditions;
class AsciiString;
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
class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
	Player *getEachPlayerFromMask(int &mask);
	int rva002A7C0B(bool flag);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
	char m_pad00[0x18];
private:
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateBuildingEntered(Parameter *pPlayerParm, Parameter *pUnitParm)
{
	Object *obj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!obj) {
		return false;
	}
	Rva003E3FFEFace *face = (Rva003E3FFEFace *)obj->m_contain;
	if (!face) {
		return false;
	}
	int ownerMask = face->getMask();
	if (!ownerMask) {
		return false;
	}
	Player *owner = ThePlayerList->getPlayerFromMask(ownerMask);
	if (!owner) {
		return false;
	}
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (owner == player) {
			return true;
		}
	}
	return false;
}
