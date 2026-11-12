// cl: /arch:SSE /ICode/GameEngine/Source/Common /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Split from AIBase.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// The 0x2C-byte elements the skirmish-AI object AIBaseBuilder owns in its +0x0C
// vector (Rva00506B74Tactic.cpp builds them with operator new and this ctor,
// deletes them, and calls their pinned members). Layout from the ctor:
//   +0x00 vector of owned Rva005DCE08 (non-virtual dtor 0x005DCE08)
//   +0x0C the element's index, +0x10 cleared, +0x14 the owner
//   +0x18 Coord3D and +0x24 float, both zeroed
//   +0x28 an owned polymorphic object
//
//   0x005AD9FF  ctor (index, owner)
//   0x005ADA40  dtor: delete every item, ::delete the +0x28 object, free
//               the vector
//   0x005AD9C0  the first item hit (0x005DCC86) by the argument
//   0x005AD964  whether the owner's start position is not yet among
//               TheSkirmishAIManager's +0x864 list
//   0x005ADC63  update: retire the +0x28 object once done (0x004E9378), or
//               start one (0x005ADAB2); then update every item
//   0x005ADCBE  pick a base template for the current map (or the .bss name
//               when the start is still open) that fits the owner's start
//               position, at random when several do
//   0x005ADE1D  lay out: copy each template order (copy ctor 0x00573EB8),
//               grow the items up to its 1-based slot, rotate its offset by
//               the angle about Z, then hand it to that item (0x005DCE62)
//   0x005AE26A  place: pick a template for the owner's side (0x005ADCBE),
//               take the point (and the angle when the template keeps it),
//               then lay the base out (0x005ADE1D)
//   0x005AE0AD  xfer: index, point, angle, the base template by name, the
//               items, then the +0x28 order
//
// The assert path these bodies share with 0x005ADCBE names the retail file
// GameLogic/SkirmishAI/AIBaseBuilder/AIBase.cpp; the templates come from
// TheBaseTemplateLibrary (0x00A03124).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
// STLport already supplies the placement forms always.h would redefine.
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include <algorithm>


struct Rva005AE26AOwner
{
	char m_pad00[0x58];
	AsciiString m_58;	// +0x58
};

// Coord3D: shared derived view (Coord3DBase base); no private copy.
#define COORD3D_DV_ZERO
#include "../../../../../Libraries/Include/Lib/Coord3DDerivedView.h"


class Rva005AD9C0Hit;

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"


class Rva00573F03;

class BuildPhase
{
public:
	void update();
};

class Xfer;
class Rva005DCE08 : public BuildPhase
{
public:
	~Rva005DCE08();
	Rva005AD9C0Hit *rva005DCC86(void *arg);
	void rva005DCEAD(Xfer *xfer);
	void rva005DCE62(Rva00573F03 *order);
};

class Rva005DCDD9
{
public:
	Rva005DCDD9(int index, int owner);
private:
	char m_data[0x18];
};

class Rva004E9378
{
public:
	bool rva004E9378();
};

#include "../../../../Include/Common/Rva00506FE9Hit.h"

#include "../../../../Include/GameNetwork/GameInfo.h"

struct Rva00506C82Arg;
GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

struct Rva002A8AB1Record;
#include "../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

class Rva005ADA40Owned
{
public:
	virtual ~Rva005ADA40Owned();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void start(void*,int); virtual void run(int); virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11();
	virtual void xfer(Xfer *xfer, void *owner);	// slot 12
	virtual Coord3D getOffset() const;		// slot 13
};

class Rva00573F03 : public Rva005ADA40Owned
{
public:
	Rva00573F03();
	Rva00573F03(const Rva00573F03 &that);
	~Rva00573F03();
	int m_04;
	char m_pad08[4];
	AsciiString m_name;
	char m_pad10[0x11];
	bool m_21;
	char m_pad22[0x1e];
	Coord3D m_point;	// +0x40
	float m_angle;		// +0x4C
	int m_50;		// +0x50, the 1-based item it goes to
	char m_pad54[0x60 - 0x54];
};

#include "GameLogicObjectLookupView.h"

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos;		// +0x38
};


extern GameLogic *TheGameLogic;

class PlayerTemplate
{
public:
	char m_pad00[0x44];
	AsciiString m_side;	// +0x44
};

#include "../../../../Include/Common/PlayerTemplateStore.h"
extern PlayerTemplateStore *ThePlayerTemplateStore;

class ThingTemplate;

#include "../../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../../Include/Common/Player.h"

struct Rva005AD9E6Node;
class Rva005AD9E6
{
public:
	int rva005AD9E6();
private:
	Rva005AD9E6Node *m_head; // +0x00
};

struct Rva002A8AB1Target
{
	char m_pad00[0x20];
	int m_20;		// +0x20
};

struct Rva002A8AB1Record
{
	char m_pad000[0x140];
	Rva005AD9E6 m_140;			// +0x140
	_STL::list<ObjectID> m_144;		// +0x144
	char m_pad148[0x160 - 0x148];
	Rva002A8AB1Target *m_160;		// +0x160
	char m_pad164[0x16C - 0x164];
	int m_16C;				// +0x16C
};

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
class Rva00573A00 { public: inline __declspec(noinline) void rva00573A00(const Coord3D *p) { m_pos=*p;m_pos.z=TheTerrainLogic->getGroundHeight(m_pos.x,m_pos.y,0); } char pad[0x30];Coord3D m_pos; };



enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00573F03;

// One base layout from TheBaseTemplateLibrary (+0x08 map name, +0x0C start
// positions it fits).
class Rva0041E912Template
{
public:
	char m_pad00[0x08];
	AsciiString m_name;			// +0x08
	_STL::vector<int> m_starts;		// +0x0C
	bool m_18;				// +0x18
	_STL::vector<Rva00573F03 *> m_orders;	// +0x1C
};

#include "../../../../Include/GameClient/MapMetaData.h"

#include "../../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;

#include "../../../../Include/Common/GlobalData.h"
extern class GlobalData *TheWritableGlobalData;

// A file-level AsciiString in .bss that a template name may also match.
extern AsciiString g_Va00E06448;	// the "<ANY>" AsciiString at RVA 0x00A06448, defined in AIBase.cpp

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// TheBaseTemplateLibrary (registered at 0x0022F9C0, global 0x00A03124)
class Rva0022BD9ASubsystem
{
public:
	bool rva0041E912(const AsciiString &side, _STL::vector<Rva0041E912Template *> &out);
};
extern Rva0022BD9ASubsystem *TheBaseTemplateLibrary;

// The library's key->template find (0x0041E764) and template->key reverse
// lookup (0x0041E971) are ICF-folded onto these rowed bodies (same hashtable
// shapes): call them under their row names.
class ArmorTemplate;
class Rva0041E764
{
public:
	ArmorTemplate *rva0041E764(NameKeyType key);
};
class GameWindow;
class WindowVideo;
class Rva0041E971
{
public:
	GameWindow *rva0041E971(WindowVideo *video);
};
// The per-item xfer 0x005DCEAD is rowed under the Rva005DCE72 view of the item.
class Rva005DCEB7Arg;
class ModuleData;
class Rva005DCE72
{
public:
	void rva005DCE72(const AsciiString &name, _STL::vector<const ModuleData *> *out);
	void rva005DCEB7(Rva005DCEB7Arg *xfer);
};

class AIBase
{
public:
	AIBase(unsigned int index, void *owner);
	~AIBase();
	Rva005AD9C0Hit *rva005AD9C0(void *arg);
	bool rva005AD964();
	void buildFortressIfNeeded();
	void rva005ADC63();
	void DoXfer(Xfer *xfer);
	Rva0041E912Template *rva005ADCBE(int notFirst, const _STL::vector<Rva0041E912Template *> &list);
	void parseTemplateIntoPhases(const Coord3D *point, float angle, Rva0041E912Template *baseTemplate);
	void loadBestFitTemplate(Coord3D *point, float angle, int notFirst);
private:
	_STL::vector<Rva005DCE08 *> m_items; // +0x00
	int m_index; // +0x0C
	Rva0041E912Template *m_10; // +0x10
	void *m_owner; // +0x14
	Coord3D m_point; // +0x18
	float m_angle; // +0x24
	Rva00573F03 *m_owned; // +0x28
};




void AIBase::rva005ADC63()
{
	Rva00573F03 *owned = m_owned;
	if (owned) {
		if (((Rva004E9378 *)owned)->rva004E9378()) {
			((Rva00506FE9Hit *)owned)->unRegisterWithBuilder(m_owner);
			::delete m_owned;
			m_owned = 0;
		}
	} else {
		buildFortressIfNeeded();
	}
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it)
		(*it)->update();
}


void AIBase::DoXfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_index;
	*xfer == m_point;
	*xfer == m_angle;
	AsciiString name;
	if (xfer->IsStoring() && m_10)
		name = TheNameKeyGenerator->keyToName((NameKeyType)(int)((Rva0041E971 *)TheBaseTemplateLibrary)->rva0041E971((WindowVideo *)m_10));
	*xfer == name;
	if (xfer->IsLoading() && name != AsciiString::TheEmptyString)
		m_10 = (Rva0041E912Template *)((Rva0041E764 *)TheBaseTemplateLibrary)->rva0041E764(TheNameKeyGenerator->nameToKey(name));
	unsigned int count = m_items.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		for (unsigned int i = 0; i < count; ++i)
			m_items.push_back((Rva005DCE08 *)new Rva005DCDD9(i, (int)m_owner));
	}
	Rva005DCE08 **end = m_items.end();
	for (Rva005DCE08 **it = m_items.begin(); it != end; ++it)
		((Rva005DCE72 *)*it)->rva005DCEB7((Rva005DCEB7Arg *)xfer);
	bool hasOwned = m_owned != 0;
	*xfer == hasOwned;
	if (hasOwned) {
		if (xfer->IsLoading())
			m_owned = new Rva00573F03;
		m_owned->xfer(xfer, m_owner);
	}
}

Rva0041E912Template *AIBase::rva005ADCBE(int notFirst, const _STL::vector<Rva0041E912Template *> &list)
{
	Rva0041E912Template *chosen = 0;
	const MapMetaData *map = TheMapCache->findMap(TheWritableGlobalData->m_mapName);
	if (map) {
		bool open = rva005AD964();
		_STL::vector<Rva0041E912Template *> candidates;
		AsciiString mapName = ((MapMetaData *)map)->rva00300D0E();
		for (Rva0041E912Template *const *it = list.begin(); it != list.end(); ++it) {
			Rva0041E912Template *tmpl = *it;
			if (tmpl->m_name.compare(mapName) != 0) {
				if (!open || tmpl->m_name.compare(g_Va00E06448) != 0)
					continue;
			}
			if (tmpl->m_starts.begin() == tmpl->m_starts.end()) {
				candidates.push_back(tmpl);
			} else {
				int start = Rva00506C82Find((const Rva00506C82Arg *)m_owner)->m_startPos + 1;
				int *end = tmpl->m_starts.end();
				if (_STL::find(tmpl->m_starts.begin(), end, start) != end)
					candidates.push_back(tmpl);
			}
		}
		if (!candidates.empty()) {
			unsigned int count = candidates.size();
			if (count > 1)
				chosen = candidates[GetGameLogicRandomValue(0, count - 1,
					"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIBaseBuilder\\AIBase.cpp",
					211)];
			else
				chosen = candidates[0];
		}
	}
	return chosen;
}

void AIBase::loadBestFitTemplate(Coord3D *point, float angle, int notFirst)
{
	_STL::vector<Rva0041E912Template *> templates;
	if (TheBaseTemplateLibrary->rva0041E912(((Rva005AE26AOwner *)m_owner)->m_58, templates)) {
		Rva0041E912Template *chosen = rva005ADCBE(notFirst, templates);
		if (chosen) {
			m_10 = chosen;
			m_point = *point;
			if (chosen->m_18)
				m_angle = angle;
			parseTemplateIntoPhases(&m_point, m_angle, chosen);
			return;
		}
	}
}

// Coord3D from a WWMath vector (retail copies the returned temporary).
static inline void copyVector(Coord3D *dst, const Vector3 &vec)
{
	dst->x = vec.X;
	dst->y = vec.Y;
	dst->z = vec.Z;
}


// WB 0x01534F60 AIBase::buildFortressIfNeeded (AIBase.cpp), native RVA 0x005ADAB2.
// The held pointer and fence preserve the native load before the branch;
// visibility of the rowed terrain setter preserves scheduling around zero.
__forceinline Rva00573F03*heldOwned(Rva00573F03*const&p){Rva00573F03*q=p;_ReadWriteBarrier();return q;}
void AIBase::buildFortressIfNeeded()
{
	GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)m_owner);
	const AsciiString &side = ThePlayerTemplateStore->getNthPlayerTemplate(slot->m_playerTemplate)->m_side;
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(side);
	if (!((Player *)m_owner)->canBuild(thingTemplate))
		return;
	Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(m_owner);
	int count = record->m_16C;
	if (count < 1)
		return;
	if ((unsigned int)record->m_140.rva005AD9E6() <= 0)
		return;
	if (m_owned && !((Rva004E9378 *)m_owned)->rva004E9378())
		return;
	bool clear = true;
	_STL::list<ObjectID>::iterator end = record->m_144.end();
	for (_STL::list<ObjectID>::iterator it = record->m_144.begin(); it != end; ++it) {
		if (!clear)
			break;
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj) {
			float dx = m_point.x - obj->m_pos.x;
			float dy = m_point.y - obj->m_pos.y;
			if (dx * dx + dy * dy <= 350.0f * 350.0f)
				clear = false;
		}
	}
	if (!clear)
		return;
	if (!heldOwned(m_owned)) {
		m_owned = new Rva00573F03;
		m_owned->m_point = m_point;
		Coord3D zero;
		zero.zero();
		((Rva00573A00 *)m_owned)->rva00573A00(&zero);
		m_owned->m_04 = record->m_160->m_20;
		m_owned->m_angle = m_angle;
		m_owned->m_name = side;
		m_owned->m_21 = true;
	}
	m_owned->run(0);
	m_owned->start(m_owner, 0);
}
