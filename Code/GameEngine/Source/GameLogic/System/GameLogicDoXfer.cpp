// cl: /I. /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
// GameLogic::DoXfer (GameLogicSnapshot receiver), retail 0x0024797E, 2195 B.
// The frame layout depends on BFME 2's rts::hash<AsciiString>: hashing the key by
// const reference through _STL::hash<const char *> on str() makes the out-of-line
// buildable-map ++ (0x411084, via _M_skip_to_next 0x3F7925 and _M_bkt_num_key
// 0x223149) a non-throwing call, so the hash iterator does not conflict with the
// object-load guard and shares its stack colour as in retail. Zero Hour's by-value
// key (copy and releaseBuffer) or an opaque declaration leaves ++ may-throw.
// stlport
//
// GameLogic::DoXfer, retail 0x0024797E (2195 B, RET 4; WB 0x00D097E0, GameLogic.cpp 7168..7472).
// The receiver is the Snapshot sub-object at GameLogic+0x0C (the body subtracts 0x0C
// to reach the logic for its out-of-line calls). Structure follows the WB debug body and
// Zero Hour's GameLogic::xfer; BFME 2's save format adds the skirmish game info and
// preferences block, the buildable overrides, the control bar overrides and the
// Snapshot-valued sub-systems. Members keep offset names (receiver-relative offsets
// are the Snapshot view's, GameLogic offset = receiver offset + 0x0C).
#include "ascii_string.h"
#include "unicode_string.h"
#include <set>
#include <map>
#include <hash_map>

class Xfer;
class Object;
struct Rva00243B52DestroyEntry;
#include "reference/shims/moduledata/Common/Snapshot.h"

struct XferVersionInfo
{
	XferVersionInfo(unsigned char a, unsigned char b) : m_a(a), m_b(b) {}
	unsigned char m_a, m_b;
};

#include "Lib/Coord3DBase.h"
// Keep STLport pair construction inline without emitting another external copy.
class AsciiString; enum BuildableStatus;
namespace _STL {
template <> __declspec(dllimport) __forceinline
pair<const AsciiString, BuildableStatus>::pair(const AsciiString &name, const BuildableStatus &status)
    : first(name), second(status) {}
}
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@UTreeKey00242F5E@@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapp:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct TreeKey00242F5E; struct TreeOpaqueMapped242F5E;
namespace _STL { template <> _Rb_tree_node<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > * _Rb_tree<TreeKey00242F5E,pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E>,_Select1st<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> >,less<TreeKey00242F5E>,allocator<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > >::_M_create_node(pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> const &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@UTreeKey00242F5E@@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMappe:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct TreeKey00242F5E; struct TreeOpaqueMapped242F5E;
namespace _STL { template <> pair<_Rb_tree_iterator<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E>,_Nonconst_traits<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > >,bool> _Rb_tree<TreeKey00242F5E,pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E>,_Select1st<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> >,less<TreeKey00242F5E>,allocator<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > >::insert_unique(pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> const &); }
// Suppress this TU's non-retail copy of ??R?$less@I@_STL@@QBE_NABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<unsigned int>::operator()(unsigned int const &,unsigned int const &) const; }
// Suppress this TU's non-retail copy of ?get_allocator@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBE?AV?$allocator@PAX@2@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> allocator<void *> vector<void *,allocator<void *> >::get_allocator() const; }
// Keep const vector access inline without emitting external accessor copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *const *vector<void *>::begin() const { return _M_start; }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *const &vector<void *>::operator[](size_t n) const { return *(begin() + n); }
}

class Snapshot;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"


#include "../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *id);
void XferBuildableStatus(Xfer *xfer, int *value);
void XferGameDifficulty(Xfer *xfer, int *value);

struct ObjectTOCEntry;
class CommandButton;
class Team;
#include "../../../Include/Common/ThingTemplate.h"

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

struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }
	unsigned int m_bits[4];
};

#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../Include/Common/Player.h"
#include "../../../Include/Common/PlayerList.h"

#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

#include "../../../Include/GameNetwork/GameInfo.h"
class SkirmishGameInfo : public GameInfo
{
public:
	SkirmishGameInfo();
	virtual ~SkirmishGameInfo();
	char m_rest2[0xE3C - 0xDC];
};
extern SkirmishGameInfo *TheSkirmishGameInfo;
extern GameInfo *TheGameInfo;

#include "../../../Include/GameClient/SkirmishPreferencesClass.h"

class LinearCampaignManager;
class CaveSystem;
class LargeGroupAudio;
class DelayedExperienceLevelGrantSystem;
extern LinearCampaignManager *TheLinearCampaignManager;
extern CaveSystem *TheCaveSystem;
extern LargeGroupAudio *TheLargeGroupAudio;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;

// Pointer conversion to a Snapshot sub-object at +off, null-guarded as a base conversion is.
static __forceinline Snapshot *snapshotAt(void *p, int off) { return p ? (Snapshot *)((char *)p + off) : 0; }

class GameLogic;
extern GameLogic *TheGameLogic;
class Rva000421FD
{
public:
	void rva000421FD(void);
};
struct LogicFPView { char opaque[0x1B4]; int depth; };
class Rva0004224C
{
public:
	Rva0004224C(void)
	{
		if (TheGameLogic)
			((Rva000421FD *)TheGameLogic)->rva000421FD();
	}
	~Rva0004224C(void) { if (TheGameLogic) --((LogicFPView *)TheGameLogic)->depth; }
};

struct Rva0023E887Source { int m_00; const char *m_text; };
class Rva0023E887
{
public:
	Rva0023E887(const Rva0023E887Source &source);
private:
	int m_00;
	AsciiString m_text;
};

struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);
typedef _STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > ControlBarOverrideMap;

enum BuildableStatus { BUILDABLE_STATUS_UNKNOWN = 0 };
namespace rts
{
	template <class T> struct hash { size_t operator()(const T &value) const; };
	template <class T> struct equal_to {
		__declspec(dllimport) __forceinline bool operator()(const T &left, const T &right) const
		{ return left == right; }
	};
}
typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
// The buildable map's hasher is the AsciiString hash at retail 0x00055041 (30 B): the
// key by reference, hashed through _STL::hash<const char *> on str(). Its body is visible
// so the out-of-line ++ chain (0x411084 -> 0x3F7925 -> 0x223149 -> 0x55041) is nothrow.
// Same functor and pinned name as Rva00212858Resize.cpp; the ledger's rts::hash<AsciiString>
// at 0x0002BF8C is a different (lowercasing) body.
struct Rva00055041AsciiHash
{
	unsigned int operator()(const AsciiString &ast) const
	{
		_STL::hash<const char *> tmp;
		return tmp((const char *) ast.str());
	}
};
typedef _STL::hash_map<AsciiString, BuildableStatus, Rva00055041AsciiHash,
	rts::equal_to<AsciiString>, _STL::allocator<BuildableStatusPair> > BuildableMap;


class Rva0023E7B4 { public: void *rva0023E7B4(unsigned short key); };

struct ObjectView
{
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3DBase m_position;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	char m_pad78[0x8C - 0x78];
	ObjectView *m_next;
};


#include "../../../Include/Common/XferException.h"

// StringBase<wchar_t>::compare is called out of line, bound to the string_base.cpp row.
template<> __declspec(nothrow) int StringBase<wchar_t>::compare(const StringBase<wchar_t>&str)const;

static __forceinline bool differs(const UnicodeString &a, const UnicodeString &b) { return a.compare(b) != 0; }

// The Snapshot sub-object of GameLogic (receiver of DoXfer); offsets are receiver-relative.
class GameLogicSnapshot
{
public:
	void DoXfer(Xfer *xfer);

private:
	char m_pad00[4];
	BuildableMap m_buildableOverrides;                   // +0x04 (GameLogic +0x10)
	ControlBarOverrideMap m_controlBarOverrides;         // +0x18
	char m_pad2C[0x2c - 0x18 - sizeof(ControlBarOverrideMap)];
	unsigned int m_timestamp;                            // +0x2C
	char m_pad30[0x34 - 0x30];
	unsigned int m_frame;                                // +0x34
	char m_pad38[0x88 - 0x38];
	int m_88;
	bool m_scoring;                                      // +0x8C
	bool m_8d, m_8e, m_8f;
	char m_pad90[0x93 - 0x90];
	bool m_93;
	int m_94;
	int m_98;
	char m_pad9C[0xA0 - 0x9C];
	ObjectView *m_objList;                               // +0xA0
	char m_padA4[0x104 - 0xA4];
	int m_mode;                                          // +0x104
	int m_second;                                        // +0x108
	int m_10c;
	bool m_110;
	char m_pad111[0x158 - 0x111];
	_STL::vector<Rva00243B52DestroyEntry *> m_158;
	Snapshot *m_164;
	Snapshot *m_168;
	Snapshot *m_16c;
	int m_170;
	unsigned int m_174;
};

void GameLogicSnapshot::DoXfer(Xfer *xfer)
{
	XferVersionInfo version(1, 8);
	*xfer == (Xfer::Version &)version;

	int mode = m_mode;
	*xfer == mode;
	m_mode = mode;
	int second = m_second;
	*xfer == second;
	int curMode = m_mode;
	m_second = second;

	if (curMode == 2 || second == 0) {
		if (xfer->IsLoading()) {
			if (!TheSkirmishGameInfo) {
				TheSkirmishGameInfo = new SkirmishGameInfo;
			} else if (TheSkirmishGameInfo->m_inGame) {
				TheSkirmishGameInfo->endGame();
			}
			TheGameInfo = TheSkirmishGameInfo;
			TheSkirmishGameInfo->init();
			TheSkirmishGameInfo->clearSlotList();
			TheSkirmishGameInfo->reset();
		}
		TheSkirmishGameInfo->xfer(xfer);
	}

	if (version.m_b >= 4 && m_mode == 2) {
		SkirmishPreferences prefs(0);
		UnicodeString name = prefs.Rva0043B9F5();
		*xfer == name;
		bool changed = xfer->IsLoading() && differs(prefs.Rva0043B9F5(), name);
		if (changed) {
			prefs.setCurrentUserName(name);
			prefs.write();
		}
	}

	if (xfer->IsCRC())
		*xfer == m_timestamp;
	*xfer == m_frame;
	*xfer == m_170;
	*xfer == m_110;

	if (xfer->IsLightCRC()) {
		for (ObjectView *obj = m_objList; obj; obj = obj->m_next) {
			Coord3DBase pos;
			pos.x = obj->m_position.x;
			pos.y = obj->m_position.y;
			pos.z = obj->m_position.z;
			*xfer == pos;
		}
		return;
	}

	Rva0004224C guard;
	GameLogic *logic = (GameLogic *)((char *)this - 0x0C);
	logic->xferObjectTOC(xfer);
	if (xfer->IsLoading())
		logic->prepareLogicForObjectLoad();
	unsigned int objectCount = logic->getObjectCount();
	*xfer == objectCount;

	ObjectID id;
	Team *defaultTeam;
	if (xfer->IsStoring()) {
		for (ObjectView *obj = m_objList; obj; obj = obj->m_next) {
			ObjectTOCEntry *entry = logic->findTOCEntryByName(*(AsciiString *)((char *)obj->m_template + 0x64));
			if (entry == 0)
				throw XferException(5, 0);
			*xfer == *((unsigned short *)((char *)entry + 4));
			id = obj->m_id;
			XferObjectID(xfer, &id);
			xfer->BeginBlock("Object");
			*xfer == *((Snapshot *)((char *)obj + 0x60));
			xfer->EndBlock();
		}
	} else {
		defaultTeam = ThePlayerList->m_players[0]->m_defaultTeam;
		for (unsigned int i = 0; i < objectCount; ++i) {
			unsigned short tocID;
			*xfer == tocID;
			AsciiString *entryName = (AsciiString *)((Rva0023E7B4 *)logic)->rva0023E7B4(tocID);
			if (entryName == 0)
				throw XferException(5, 0);
			XferObjectID(xfer, &id);
			const ThingTemplate *tt = TheThingFactory->findTemplate(*entryName);
			if (tt == 0) {
				xfer->SkipBlock("Object");
				continue;
			}
			AssetLoadMode mode;
			AssetList assets;
			((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
			bfmeMergeReceiverKeys((int)&assets);
			Object *obj = TheThingFactory->newObject(tt, defaultTeam, &CreateMask(), id);
			xfer->BeginBlock("Object");
			*xfer == *(snapshotAt(obj, 0x60));
			xfer->EndBlock();
		}
	}

	if (version.m_b < 7)
		*xfer == *(Snapshot *)TheLinearCampaignManager;
	*xfer == *(snapshotAt(TheCaveSystem, 0x0C));
	*xfer == *m_164;
	*xfer == *m_168;
	*xfer == *m_16c;
	*xfer == *(snapshotAt(TheLargeGroupAudio, 0x0C));
	*xfer == m_scoring;
	*xfer == m_10c;

	if (xfer->IsStoring()) {
		for (BuildableMap::const_iterator it = m_buildableOverrides.begin(); it != m_buildableOverrides.end(); ++it) {
			AsciiString name = it->first;
			int status = it->second;
			*xfer == name;
			XferBuildableStatus(xfer, &status);
		}
		AsciiString empty;
		*xfer == empty;
	} else {
		if (!m_buildableOverrides.empty())
			throw XferException(5, 0);
		for (;;) {
			AsciiString name;
			*xfer == name;
			if (name.isEmpty())
				break;
			int status;
			XferBuildableStatus(xfer, &status);
			m_buildableOverrides[name] = (BuildableStatus)status;
		}
	}

	*xfer == m_8d;
	*xfer == m_8e;
	*xfer == m_8f;
	*xfer == m_94;
	if (version.m_b >= 3)
		XferGameDifficulty(xfer, &m_98);
	*xfer == m_174;

	if (xfer->IsStoring()) {
		for (ControlBarOverrideMap::iterator it = m_controlBarOverrides.begin(); it != m_controlBarOverrides.end(); ++it) {
			AsciiString value = it->second.m_bits ? *(AsciiString *)(it->second.m_bits + 0x10) : AsciiString::TheEmptyString;
			int slot = it->first.m_id;
			AsciiString key = it->first.m_name;
			xfer->operator==(slot).operator==(key).operator==(value);
		}
		int end = -1;
		*xfer == end;
	} else {
		if (!m_controlBarOverrides.empty())
			throw XferException(5, 0);
		for (;;) {
			if (version.m_b >= 5) {
				int slot;
				*xfer == slot;
				if (slot < 0)
					break;
				AsciiString key;
				AsciiString value;
				xfer->operator==(key).operator==(value);
				const CommandButton *button = 0;
				if (!value.isEmpty())
					button = TheControlBar->findCommandButton(value);
				m_controlBarOverrides[(const TreeKey00242F5E &)_STL::make_pair(slot, key)].m_bits = (unsigned int)button;
			} else {
				AsciiString name;
				*xfer == name;
				if (name.isEmpty())
					break;
				AsciiString value;
				*xfer == value;
				const CommandButton *button = 0;
				if (!value.isEmpty())
					button = TheControlBar->findCommandButton(value);
				const char *rest = name.str() + 1;
				Rva0023E887Source source;
				source.m_00 = name.str()[0] - '0';
				source.m_text = rest;
				Rva0023E887 key(source);
				m_controlBarOverrides[(const TreeKey00242F5E &)key].m_bits = (unsigned int)button;
			}
		}
	}

	*xfer == m_88;
	if (version.m_b >= 2)
		*xfer == m_93;
	if (version.m_b >= 8)
		*xfer == *(snapshotAt(TheDelayedExperienceLevelGrantSystem, 0x0C));
	m_158.clear();
}

// The shared GameLogic view leaves +0x24 unmodelled; the override map lives there.
struct GameLogicControlBarOverrides
{
	unsigned char m_pad00[0x24];
	ControlBarOverrideMap m_controlBarOverrides;	// +0x24
};

// setControlBarOverride is rowed at 0x0024792F (GameLogicSetControlBarOverride.cpp).
