// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ScriptActions::doBuildBaseBuilding, retail 0x003BE38B (207B; ret 0xC)
// ScriptActions::doBuildBaseBuildingInSlot, retail 0x003BE45A (216B; ret 0x10)
// ScriptActions::rva003C66F1, retail 0x003C66F1 (384B; ret 0x14)
// Target identity: executeAction case 383 (BUILD_BASE_BUILDING) calls
// 0x003BE38B with parameter 0's string, parameter 1 and parameter 2's string;
// case 384 (BUILD_BASE_BUILDING_IN_SLOT) calls 0x003BE45A with parameter 0's
// string, parameters 1 and 2 and parameter 3's string. The names and flow are
// carried from the BFME 1 donor ScriptActionsBuildBase.cpp (same action
// numbers). Target body: the base unit by parameter (rowed getUnitNamed
// 0x003588E7), its controlling player (0x0028AFA9), which must have the
// +0x339 flag set and be the script engine's current player (0x00205C93),
// the template by name (pinned findTemplate 0x002D06CA), the base's
// CastleBehavior module (rowed key 0x003955DA, findModule 0x0028B6D6), the
// rowed module check 0x003971BF and the rowed player check 0x002AA00C
// (template, 0), then the pinned module build 0x003980BF with slot -2 (first
// free) or the slot parameter's int; a non-empty reference name is given to
// the new object through 0x00208968 and addObjectToCache 0x0020A5FF.
// Target differences from the donor: the base is a Parameter, the ownership
// flag is at +0x339 and the two pre-build checks are the BFME 2 callees above.
// Case 385 (BUILD_BASE_BUILDING_PER_TACTICAL_MARKER) calls 0x003C66F1 with
// parameter 0's string, parameter 1, parameter 2's string, parameter 3 and
// parameter 4's string. It has no donor body, so the method keeps an address
// name. Target body: the same prefix, then, unless TheWritableGlobalData's
// +0x1110 flag is set, the template is announced to a fresh asset list
// (notify 0x0033CF34, merge 0x0061F010) as GameLogic::init does; the castle's
// pinned 0x00397429 finds the object of the marker type, and the pinned
// 0x0039815B builds at a copy of its position (+0x38) with parameter 1's int
// (a 0/1 mode), else 0x003980BF builds in slot -2. The new object is named as
// above.
// Shape: the module key is a named local; passing the call result straight
// to findModule swaps retail's ESI/EDI choice for the base and template. The
// marker position is copied member by member (retail movss); a struct copy
// becomes movsd and spills the template.
#include <set>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module;
class ThingTemplate;
class Object;

class Parameter
{
public:
	Int getInt() const { return m_int; }
private:
	unsigned char m_pad[8];
	Int m_int;	// +0x08
};

class Player
{
public:
	unsigned char rva002AA00C(ThingTemplate *tmpl, Int unknown);
	bool getCanBuildBase() const { return m_canBuildBase != 0; }
private:
	unsigned char m_pad[0x339];
	unsigned char m_canBuildBase;	// +0x339
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad[0x38];
	Coord3D m_pos;	// +0x38
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
	Object *rva00397429(const AsciiString &templateName);
	Object *rva0039815B(ThingTemplate *tmpl, const Coord3D *pos, Int mode);
};

// The rowed and pinned address-named views of the same CastleBehavior module.
struct Arg3971BF;
class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *arg);
};

class Rva003980BF
{
public:
	void *rva003980BF(void *tmpl, Int slot, Int unknown);
};

class GlobalData
{
public:
	char m_pad0000[0x1110];
	bool m_1110;
};
extern GlobalData *TheWritableGlobalData;

// The asset announcement GameLogic::init makes for a looked-up template
// (GameLogicInit.cpp): notify 0x0033CF34 with a fresh asset list and load
// mode, then merge 0x0061F010.
class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
	_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;

class AssetList
{
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

struct AssetLoadMode
{
	bool m_alternate;
	AssetLoadMode() : m_alternate(false) {}
};

void bfmeMergeReceiverKeys(int value);

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *pUnitParm);
	Player *getCurrentPlayer();
	void rva00208968(const AsciiString &name, Object *obj);
	void addObjectToCache(Object *obj, const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doBuildBaseBuilding(const AsciiString &buildingType, Parameter *baseParm, const AsciiString &referenceName);
	void doBuildBaseBuildingInSlot(const AsciiString &buildingType, Parameter *slotParm, Parameter *baseParm, const AsciiString &referenceName);
	void rva003C66F1(const AsciiString &buildingType, Parameter *modeParm, const AsciiString &markerType, Parameter *baseParm, const AsciiString &referenceName);
};

void ScriptActions::doBuildBaseBuilding(const AsciiString &buildingType, Parameter *baseParm, const AsciiString &referenceName)
{
	Object *base = TheScriptEngine->getUnitNamed(baseParm);
	if (!base)
		return;

	Player *player = base->getControllingPlayer();
	if (!player)
		return;
	if (!player->getCanBuildBase())
		return;
	if (player != TheScriptEngine->getCurrentPlayer())
		return;

	ThingTemplate *tmpl = (ThingTemplate *)TheThingFactory->findTemplate(buildingType);
	if (!tmpl)
		return;

	NameKeyType castleKey = CastleBehavior::rva0003955DA();
	Module *castle = base->findModule(castleKey);
	if (!castle)
		return;
	if (!((Rva003971BF *)castle)->rva003971BF((Arg3971BF *)tmpl))
		return;
	if (!player->rva002AA00C(tmpl, 0))
		return;

	Object *obj = (Object *)((Rva003980BF *)castle)->rva003980BF(tmpl, -2, 0);
	if (!obj)
		return;
	if (referenceName.isEmpty())
		return;

	TheScriptEngine->rva00208968(referenceName, obj);
	TheScriptEngine->addObjectToCache(obj, referenceName);
}

void ScriptActions::doBuildBaseBuildingInSlot(const AsciiString &buildingType, Parameter *slotParm, Parameter *baseParm, const AsciiString &referenceName)
{
	Object *base = TheScriptEngine->getUnitNamed(baseParm);
	if (!base)
		return;

	Player *player = base->getControllingPlayer();
	if (!player)
		return;
	if (!player->getCanBuildBase())
		return;
	if (player != TheScriptEngine->getCurrentPlayer())
		return;

	ThingTemplate *tmpl = (ThingTemplate *)TheThingFactory->findTemplate(buildingType);
	if (!tmpl)
		return;

	NameKeyType castleKey = CastleBehavior::rva0003955DA();
	Module *castle = base->findModule(castleKey);
	if (!castle)
		return;
	if (!((Rva003971BF *)castle)->rva003971BF((Arg3971BF *)tmpl))
		return;
	if (!player->rva002AA00C(tmpl, 0))
		return;

	Object *obj = (Object *)((Rva003980BF *)castle)->rva003980BF(tmpl, slotParm->getInt(), 0);
	if (!obj)
		return;
	if (referenceName.isEmpty())
		return;

	TheScriptEngine->rva00208968(referenceName, obj);
	TheScriptEngine->addObjectToCache(obj, referenceName);
}

void ScriptActions::rva003C66F1(const AsciiString &buildingType, Parameter *modeParm, const AsciiString &markerType, Parameter *baseParm, const AsciiString &referenceName)
{
	Object *base = TheScriptEngine->getUnitNamed(baseParm);
	if (!base)
		return;

	Player *player = base->getControllingPlayer();
	if (!player)
		return;
	if (!player->getCanBuildBase())
		return;
	if (player != TheScriptEngine->getCurrentPlayer())
		return;

	ThingTemplate *tmpl = (ThingTemplate *)TheThingFactory->findTemplate(buildingType);
	if (!tmpl)
		return;

	NameKeyType castleKey = CastleBehavior::rva0003955DA();
	Module *castle = base->findModule(castleKey);
	if (!castle)
		return;
	if (!((Rva003971BF *)castle)->rva003971BF((Arg3971BF *)tmpl))
		return;
	if (!player->rva002AA00C(tmpl, 0))
		return;

	if (!TheWritableGlobalData->m_1110) {
		AssetLoadMode mode;
		AssetList assets;
		((Rva0020AA00Target *)tmpl)->notify((int)&assets, (int)&mode);
		bfmeMergeReceiverKeys((int)&assets);
	}

	Object *obj;
	Object *marker = ((CastleBehavior *)castle)->rva00397429(markerType);
	if (marker) {
		Coord3D pos;
		pos.x = marker->getPosition()->x;
		pos.y = marker->getPosition()->y;
		pos.z = marker->getPosition()->z;
		obj = ((CastleBehavior *)castle)->rva0039815B(tmpl, &pos, modeParm->getInt());
	} else {
		obj = (Object *)((Rva003980BF *)castle)->rva003980BF(tmpl, -2, 0);
	}
	if (!obj)
		return;
	if (referenceName.isEmpty())
		return;

	TheScriptEngine->rva00208968(referenceName, obj);
	TheScriptEngine->addObjectToCache(obj, referenceName);
}
