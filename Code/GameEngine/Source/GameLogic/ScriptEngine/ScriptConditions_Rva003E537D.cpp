// cl: /Ireference/shims/bfme2_ascii
// ?Rva003E537DCheck@@YG_NPAVParameter@@@Z
// retail 0x003E537D, 52 bytes.
// Evidence: leaf free __stdcall bool with 1 Parameter arg frameless; rowed ScriptEngine::getUnitNamed; Object +0x250 Mid with vslot 69 (0x114) taking int returning unsigned; unsigned <=0 gives jbe.
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

class Object;

class ContainModuleInterface;
class Mid003E537D
{
public:
	virtual unsigned int v00(int);
	virtual unsigned int v01(int);
	virtual unsigned int v02(int);
	virtual unsigned int v03(int);
	virtual unsigned int v04(int);
	virtual unsigned int v05(int);
	virtual unsigned int v06(int);
	virtual unsigned int v07(int);
	virtual unsigned int v08(int);
	virtual unsigned int v09(int);
	virtual unsigned int v10(int);
	virtual unsigned int v11(int);
	virtual unsigned int v12(int);
	virtual unsigned int v13(int);
	virtual unsigned int v14(int);
	virtual unsigned int v15(int);
	virtual unsigned int v16(int);
	virtual unsigned int v17(int);
	virtual unsigned int v18(int);
	virtual unsigned int v19(int);
	virtual unsigned int v20(int);
	virtual unsigned int v21(int);
	virtual unsigned int v22(int);
	virtual unsigned int v23(int);
	virtual unsigned int v24(int);
	virtual unsigned int v25(int);
	virtual unsigned int v26(int);
	virtual unsigned int v27(int);
	virtual unsigned int v28(int);
	virtual unsigned int v29(int);
	virtual unsigned int v30(int);
	virtual unsigned int v31(int);
	virtual unsigned int v32(int);
	virtual unsigned int v33(int);
	virtual unsigned int v34(int);
	virtual unsigned int v35(int);
	virtual unsigned int v36(int);
	virtual unsigned int v37(int);
	virtual unsigned int v38(int);
	virtual unsigned int v39(int);
	virtual unsigned int v40(int);
	virtual unsigned int v41(int);
	virtual unsigned int v42(int);
	virtual unsigned int v43(int);
	virtual unsigned int v44(int);
	virtual unsigned int v45(int);
	virtual unsigned int v46(int);
	virtual unsigned int v47(int);
	virtual unsigned int v48(int);
	virtual unsigned int v49(int);
	virtual unsigned int v50(int);
	virtual unsigned int v51(int);
	virtual unsigned int v52(int);
	virtual unsigned int v53(int);
	virtual unsigned int v54(int);
	virtual unsigned int v55(int);
	virtual unsigned int v56(int);
	virtual unsigned int v57(int);
	virtual unsigned int v58(int);
	virtual unsigned int v59(int);
	virtual unsigned int v60(int);
	virtual unsigned int v61(int);
	virtual unsigned int v62(int);
	virtual unsigned int v63(int);
	virtual unsigned int v64(int);
	virtual unsigned int v65(int);
	virtual unsigned int v66(int);
	virtual unsigned int v67(int);
	virtual unsigned int v68(int);
	virtual unsigned int v69(int);
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

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

bool __stdcall Rva003E537DCheck(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj)
	{
		Mid003E537D *mid = (Mid003E537D *)obj->m_contain;
		if (mid)
		{
			if (mid->v69(0) > 0)
				return true;
		}
	}
	return false;
}
