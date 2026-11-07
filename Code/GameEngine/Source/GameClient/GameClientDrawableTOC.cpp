// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// platformsdk
//
// GameClient's drawable table of contents: the save-game list pairing each
// drawable template name with the 16-bit id stored in its place.
// Donor: ZH GameEngine/Source/GameClient/GameClient.cpp (shouldSaveDrawable,
// findTOCEntryByName, findTOCEntryById, addTOCEntry, xferDrawableTOC), same
// control flow.
// Target evidence for the layout: xferDrawableTOC (0x0023AC36) clears the list
// at this+0xF4 through the folded list clear 0x00239D49, walks the drawables
// from virtual slot 35 (+0x8C, ZH getDrawableList) along next at +0x104, takes
// each template (+4) name (+0x64), stores the count (Xfer slot 30) and each
// node's name (+8, slot 27) and id (+0xC, slot 32). The name search 0x00239C5E
// (StringBase compare 0x000069D6 per node) and the append 0x0023AB78 (list
// push_back 0x0023A014) take the same this; the id search 0x002399EB, called
// from GameClient::xfer at 0x0023B68C, walks the same list for node+0xC. shouldSaveDrawable (0x00238F79)
// tests status bit 0x10 at +0x114 and the object pointer at +0xFC, and is
// called with the drawable in EAX: a TU-local static, kept out of line
// (__declspec(noinline)) as retail calls it.
// BFME 2 opens with the out-of-line Xfer::Version1 (0x000053EE) instead of
// xferVersion, as GameLogic::xferObjectTOC does.
//
// ~GameClient (0x0023AE08). Donor: ZH GameClient::~GameClient, same order of
// subsystem teardown and the same translator loop. Target evidence: the two
// vptr stores (+0 vftable 0x00BED850, +0xC Snapshot side 0x00BED840), the
// callers (scalar deleting dtor 0x0023BDBB, derived dtor tail 0x0004C743),
// the globals each deleted subsystem was named after by setName in
// GameClient::init 0x0023A1BB, and the unwind states, which give the members
// in declaration order: hash +0x18, string +0xBC, drawable list +0xE4, vector
// +0xE8, TOC +0xF4, ten drawable lists +0xF8, vectors +0x120 and +0x12C and an
// owning pointer +0x13C. BFME 2 adds the tooltip clear 0x0038072A first, the
// clear 0x0023ABDD after the drawables go, the Apt window manager call and
// the weather/effect managers, and drops TheCampaignManager, TheEva and
// TheChallengeGenerals.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include <vector>
#include <hash_map>
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "GUI/HeaderTemplateView.h"
#include "../Common/GameLogicObjectLookupView.h"
#include "../../Include/Common/BfmeAudioEventPrefix136.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

// The TOC list's out-of-line members fold onto addresses other lists already
// name, so its allocator is a placeholder class (as GameLogic's ObjectTOC list).
template <class T> class Rva0023AC36Allocator : public _STL::allocator<T>
{
};

class Xfer;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
#include "../../../Libraries/Include/Lib/Region3D.h"
class IRegion3D;
class Coord2D;
// BFME 2's ICoord2D has an out-of-line default constructor (0x0047A6A9, a
// folded return-this body): MetaEventTranslator's array of three is built
// through the vector constructor iterator.
#define ICOORD2D_VIEW_EXTERN_DEFAULT_CTOR
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#undef ICOORD2D_VIEW_EXTERN_DEFAULT_CTOR
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/ThingTemplate.h"
// GameClient slot 26 (0x002391AA) passes drawables whose object's
// template has bit 0x40 of the kindof byte at +0x118 set without a cull test.
static inline bool thingTemplateTestKindOfByte118(const ThingTemplate *tmpl, unsigned char bit) { return (((const unsigned char *)tmpl->m_kindof)[0x10] & bit) != 0; }

// ZH ObjectShroudStatus values, under the enum name the matched
// getShroudStatusForPlayer (0x0028D2A2) row carries.
enum CellShroudStatus
{
	SHROUD_STATUS_INVALID,
	SHROUD_STATUS_CLEAR,
	SHROUD_STATUS_PARTIAL_CLEAR,
	SHROUD_STATUS_FOGGED
};

// GameClient::update tests bit 0 of the byte at +0x438 where ZH's
// isEffectivelyDead tests EFFECTIVELY_DEAD in m_privateStatus.
class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template;                                     // +0x04
	unsigned char m_pad008[0x438 - 0x08];
	unsigned char m_privateStatus;                                       // +0x438
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

class Drawable
{
public:
	const ThingTemplate *getTemplate(void) const { return m_template; }
	Object *getObject(void) const { return m_object; }
	Drawable *getNextDrawable(void) const { return m_nextDrawable; }
	bool testDrawableStatus(DrawableStatus bit) const { return (m_status & bit) != 0; }
	unsigned int getShroudClearFrame(void) const { return m_shroudClearFrame; }
	void setFullyObscuredByShroud(bool fullyObscured);
	void updateDrawable(void);
	// ZH Drawable::releaseShadows / allocateShadows: each walks the draw
	// modules at +0x14C calling their slot 13 (+0x34) / slot 14 (+0x38).
	void rva00272A38(void);
	void rva00272A51(void);

private:
	void *m_vtbl;
	const ThingTemplate *m_template;                                     // +0x04
	char m_pad08[0xfc - 0x08];
	Object *m_object;                                                    // +0xFC
	char m_pad100[0x104 - 0x100];
	Drawable *m_nextDrawable;                                            // +0x104
	char m_pad108[0x114 - 0x108];
	unsigned int m_status;                                               // +0x114
	char m_pad118[0x138 - 0x118];
	unsigned int m_shroudClearFrame;                                     // +0x138
	char m_pad13C[0x35c - 0x13c];
public:
	// The frustum plane (1-4) that last culled this drawable, 0 when it
	// passed: written by GameClient slot 26 (0x002391AA), read by slot 27.
	int m_cullPlane;                                                     // +0x35C
public:
	const Coord3D *getPosition() const;
};

// ZH DrawableID.
enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};

// Retail nodes hold the DrawableID at +4 and the Drawable pointer at +8.
namespace rts {
template <class T> struct hash;
template <> struct hash<DrawableID> {
    size_t operator()(DrawableID value) const { return _STL::hash<unsigned int>()((unsigned int)value); }
};
template <class T> struct equal_to {
    bool operator()(const T &left, const T &right) const { return left == right; }
};
}
typedef _STL::hash_map<DrawableID, Drawable *, rts::hash<DrawableID>,
    rts::equal_to<DrawableID> > DrawablePtrHash;
typedef _STL::pair<const DrawableID, Drawable *> DrawableHashPair;
typedef _STL::hashtable<DrawableHashPair, DrawableID, rts::hash<DrawableID>,
    _STL::_Select1st<DrawableHashPair>, rts::equal_to<DrawableID>,
    _STL::allocator<DrawableHashPair> > DrawableHashTable;

namespace _STL {
// Inline the table teardown into the map's complete destructor.
template <> __forceinline DrawableHashTable::~hashtable() { clear(); }
template <> inline DrawablePtrHash::~hash_map() {}
// The allocator is stateless; only its stored pointer needs exchanging.
template <> __declspec(dllimport) __forceinline
void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
          _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{ swap(left._M_data, right._M_data); }
}

// The drawable lists use the rowed pool-backed STLport base constructor
// and destructor, with their sentinel at offset zero.
namespace _STL {
template<> _List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &a);
template<> _List_base<Drawable *, allocator<Drawable *> >::~_List_base() throw();
}

typedef _STL::_List_node<Drawable *> Rva00239AF4Node;
class Rva00239AF4 : public _STL::_List_base<Drawable *, _STL::allocator<Drawable *> >
{
public:
	explicit Rva00239AF4(const _STL::allocator<Drawable *> &a = _STL::allocator<Drawable *>())
		: _STL::_List_base<Drawable *, _STL::allocator<Drawable *> >(a) {}
	~Rva00239AF4() throw() {}
	__declspec(dllimport) __forceinline Rva00239AF4Node *head() { return _M_node._M_data; }
};

class Rva00362862Item;
class Dict;
class Rva00239E25 : public _STL::_Vector_base<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> >
{
public:
	explicit Rva00239E25(const _STL::allocator<OpaqueRefElement4> &a = _STL::allocator<OpaqueRefElement4>())
		: _STL::_Vector_base<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> >(a)
	{
	}
	~Rva00239E25();
};

// Owning pointer at +0x13C: clear 0x0023A039 nulls the slot and deletes the
// pointee.
class Rva0023A039
{
public:
	Rva0023A039() : m_ptr(0) {}
	void clear();
	void *get() const { return m_ptr; }
	~Rva0023A039() { clear(); }

private:
	void *m_ptr;
};

// BFME 2 SubsystemInterface: fourteen vtable slots; init sits in slot 1 (+4)
// and postProcessLoad in slot 3 (+0xC) for every subsystem GameClient::init
// creates, GameClient::reset calls reset in slot 9 (+0x24) and its vftable
// 0x007ED850 keeps update in slot 10. setName is the out-of-line 0x0006F3CC.
#include "../../Include/Common/MessageStream.h"

typedef unsigned int TranslatorID;
enum { TRANSLATOR_ID_INVALID = -1 };

// ZH MessageStream.h GameMessage: only the type GameClient returns.

// GameMessageTranslator: translateGameMessage in slot 0, an inline empty
// virtual destructor in slot 1.
#include "../../Include/GameClient/FormationTranslator.h"

// ZH CommandXlat.h CommandTranslator: the context-command evaluator
// GameClient slot 18 forwards to (retail 0x00429E11). GameClient::init news it
// (0x30 bytes, constructor 0x004296C2) and attaches it at priority 70.
class CommandTranslator : public GameMessageTranslator
{
public:
	enum CommandEvaluateType { DO_COMMAND, DO_HINT, EVALUATE_ONLY };

	CommandTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~CommandTranslator();

	GameMessage::Type evaluateContextCommand(Drawable *draw, const Coord3D *pos, CommandEvaluateType cmdType);

private:
	unsigned char m_pad[0x30 - 4];
};
class FontLibrary;
class InGameUI;
class GameWindowManager;
class Display;
class DisplayStringManager;
class VideoPlayerInterface;
class G00DFF080Obj;
class Keyboard;
class Mouse;
class SnowManager;
class Rva0027070CGlobal;
class CloudBreakEffectManager;
class FireManager;
class Rva002D3627Host;

typedef void (*GameClientFuncPtr)(Drawable *draw, void *userData);

// ZH TimeOfDay; Drawable::setTimeOfDay sets MODELCONDITION_NIGHT for 4.
enum TimeOfDay
{
	TIME_OF_DAY_INVALID,
	TIME_OF_DAY_MORNING,
	TIME_OF_DAY_AFTERNOON,
	TIME_OF_DAY_EVENING,
	TIME_OF_DAY_NIGHT
};

// WW3D FrustumClass: CameraTransform (a Matrix3D, 0x30 bytes), then six
// planes of normal and distance. Slot 26's only caller passes
// CameraClass +0x100 right after CameraClass::Update_Frustum.
class Vector3
{
public:
	float X, Y, Z;
	Vector3(void) {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	static float Dot_Product(const Vector3 &a, const Vector3 &b) { return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
};

class SphereClass
{
public:
	SphereClass(void) {}
	SphereClass(const Vector3 &center, float radius) { Init(center, radius); }
	void Init(const Vector3 &pos, float radius) { Center = pos; Radius = radius; }
	Vector3 Center;
	float Radius;
};

class PlaneClass
{
public:
	Vector3 N;
	float D;
	bool In_Front(const SphereClass &sphere) const
	{
		float dist = Vector3::Dot_Product(sphere.Center, N);
		return ((dist - D) >= sphere.Radius);
	}
};

class FrustumClass
{
public:
	unsigned char CameraTransform[0x30];
	PlaneClass Planes[6];                                                // +0x30
};

struct RayEffectData;
class Rva0023ABDD { public: void rva0023ABDD(); };
class GameClient : public SubsystemInterface, public Snapshot
{
public:
	// ZH GameClient.h DrawableTOCEntry; retail list node: name at +8, id at +0xC.
	struct DrawableTOCEntry
	{
		AsciiString name;
		unsigned short id;
	};
	typedef _STL::list<DrawableTOCEntry, Rva0023AC36Allocator<DrawableTOCEntry> > DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

	GameClient();
	virtual ~GameClient();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void vf14(unsigned int frame) { m_frame = frame; }
	virtual void registerDrawable(Drawable *draw);
	virtual Drawable *findDrawableByID(const DrawableID id);            // slot 16 (+0x40)
	virtual Drawable *firstDrawable(void);                              // slot 17 (+0x44)
	virtual GameMessage::Type evaluateContextCommand(Drawable *draw, const Coord3D *pos,
		CommandTranslator::CommandEvaluateType cmdType);                 // slot 18 (+0x48)
	virtual void removeFromRayEffects(Drawable *draw);
	virtual void getRayEffectData(Drawable *draw, RayEffectData *effectData);
	virtual void vf21() = 0;
	virtual void vf22() = 0;
	virtual bool loadMap(AsciiString mapName);
	virtual void unloadMap(AsciiString mapName);
	virtual void iterateDrawablesInRegion(Region3D *region, GameClientFuncPtr userFunc, void *userData); // slot 25 (+0x64)
	virtual void rva002391AA(const FrustumClass *frustum, float radiusPad, GameClientFuncPtr userFunc, void *userData); // slot 26 (+0x68)
	virtual void rva00238EBF(GameClientFuncPtr userFunc, void *userData); // slot 27 (+0x6C)
	virtual void vf28() = 0;
	virtual void destroyDrawable(Drawable *draw);                       // slot 29 (+0x74)
	virtual void setTimeOfDay(TimeOfDay tod);                           // slot 30 (+0x78)
	virtual unsigned int vf31(void) { return m_frame; }
	virtual void vf32() = 0;
	virtual void releaseShadows(void);                                  // slot 33 (+0x84)
	virtual void allocateShadows(void);                                 // slot 34 (+0x88)
	virtual Drawable *getDrawableList(void);                            // slot 35 (+0x8C)
	virtual void rva00239911(void);                                     // slot 36 (+0x90)
	// Factories, slots 37-50, named after the global init stores each in.
	virtual Display *createGameDisplay() = 0;                                 // +0x94
	virtual InGameUI *createInGameUI() = 0;                                   // +0x98
	virtual GameWindowManager *createWindowManager() = 0;                     // +0x9C
	virtual FontLibrary *createFontLibrary() = 0;                             // +0xA0
	virtual DisplayStringManager *createDisplayStringManager() = 0;           // +0xA4
	virtual VideoPlayerInterface *createVideoPlayer() = 0;                    // +0xA8
	virtual G00DFF080Obj *createTerrainVisual() = 0;                          // +0xAC
	virtual Keyboard *createKeyboard() = 0;                                   // +0xB0
	virtual Mouse *createMouse() = 0;                                         // +0xB4
	virtual SnowManager *createSnowManager() = 0;                             // +0xB8
	virtual Rva0027070CGlobal *createCloudEffectManager() = 0;                // +0xBC
	virtual CloudBreakEffectManager *createCloudBreakEffectManager() = 0;     // +0xC0
	virtual FireManager *createFireManager() = 0;                             // +0xC4
	virtual Rva002D3627Host *vf50() = 0;                                      // +0xC8
	virtual void setFrameRate(float rate) = 0;                                // +0xCC

	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	DrawableTOCEntry *findTOCEntryById(unsigned short id);
	void addTOCEntry(AsciiString name, unsigned short id);
	void xferDrawableTOC(Xfer *xfer);
	/* the rowed Rva0023ABDD::rva0023ABDD */ __declspec(dllimport) __forceinline void rva0023ABDD() { ((Rva0023ABDD *)this)->rva0023ABDD(); }
	void rva00239759();
	void rva0023B383(Dict *props, ThingTemplate *tmpl, const Coord3D *pos);

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:
	enum { MAX_CLIENT_TRANSLATORS = 32 };

	unsigned int m_frame;                                               // +0x10
	Drawable *m_drawableList;                                           // +0x14
	DrawablePtrHash m_drawableHash;                             // +0x18
	unsigned int m_nextDrawableID;                                      // +0x2C
	TranslatorID m_translators[MAX_CLIENT_TRANSLATORS];                 // +0x30
	unsigned int m_numTranslators;                                      // +0xB0
	CommandTranslator *m_commandTranslator;                             // +0xB4
	unsigned int m_dwordB8;                                             // +0xB8
	AsciiString m_stringBC;                                             // +0xBC
	unsigned char m_byteC0;                                             // +0xC0
	unsigned char m_byteC1;                                             // +0xC1
	unsigned char m_padC2[2];
	unsigned int m_dwordC4;                                             // +0xC4
	unsigned char m_byteC8;                                             // +0xC8
	unsigned char m_displayModePending;                                 // +0xC9
	unsigned char m_byteCA;                                             // +0xCA
	unsigned char m_padCB;
	unsigned int m_pendingXRes;                                         // +0xCC
	unsigned int m_pendingYRes;                                         // +0xD0
	unsigned int m_pendingBitDepth;                                     // +0xD4
	unsigned int m_previousWidth;                                       // +0xD8
	unsigned int m_previousHeight;                                      // +0xDC
	unsigned int m_previousBitDepth;                                    // +0xE0
	Rva00239AF4 m_drawableListE4;                                       // +0xE4
	_STL::vector<Rva00362862Item *> m_vectorE8;                         // +0xE8
	DrawableTOCList m_drawableTOC;                                      // +0xF4
	Rva00239AF4 m_drawableListsF8[10];                                  // +0xF8
	_STL::vector<long> m_audioHandles;                                  // +0x120
	Rva00239E25 m_vector12C;                                            // +0x12C
	int m_count138;                                                     // +0x138
	Rva0023A039 m_owned13C;                                             // +0x13C
};

// Instantiate the pinned STLport folds for the TOC's actual element type.
// Keep their calls out of line as in the native parent bodies.
namespace _STL
{
template __declspec(noinline) void _List_base<GameClient::DrawableTOCEntry, Rva0023AC36Allocator<GameClient::DrawableTOCEntry> >::clear();
template __declspec(noinline) _List_base<GameClient::DrawableTOCEntry, Rva0023AC36Allocator<GameClient::DrawableTOCEntry> >::~_List_base();
}

static __declspec(noinline) bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(DRAWABLE_STATUS_NO_SAVE))
	{
		if (draw->getObject() == 0)
			return false;
	}
	return true;
}

GameClient::DrawableTOCEntry *GameClient::findTOCEntryByName(AsciiString name)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).name == name)
			return &(*it);
	return 0;
}

GameClient::DrawableTOCEntry *GameClient::findTOCEntryById(unsigned short id)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).id == id)
			return &(*it);
	return 0;
}

void GameClient::addTOCEntry(AsciiString name, unsigned short id)
{
	DrawableTOCEntry tocEntry;
	tocEntry.name = name;
	tocEntry.id = id;
	m_drawableTOC.push_back(tocEntry);
}

void GameClient::xferDrawableTOC(Xfer *xfer)
{
	xfer->Version1();
	m_drawableTOC.clear();
	unsigned int tocCount = 0;
	if (xfer->IsStoring()) {
		AsciiString templateName;
		for (Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable()) {
			if (!shouldSaveDrawable(draw))
				continue;
			templateName = draw->getTemplate()->getName();
			if (findTOCEntryByName(templateName) != 0)
				continue;
			addTOCEntry(draw->getTemplate()->getName(), ++tocCount);
		}
		*xfer == tocCount;
		for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it) {
			DrawableTOCEntry *tocEntry = &(*it);
			*xfer == tocEntry->name;
			*xfer == tocEntry->id;
		}
	} else {
		AsciiString templateName;
		unsigned short id;
		*xfer == tocCount;
		for (unsigned int i = 0; i < tocCount; ++i) {
			*xfer == templateName;
			*xfer == id;
			addTOCEntry(templateName, id);
		}
	}
}

// Subsystems GameClient::init creates and this destructor deletes. The data
// ledger's names are kept where it has one; setName in init names each
// (TheHotKeyManager, TheAnimationSoundModuleManager, TheTerrainVisual,
// TheCloudEffectManager); 0x009FEF18 is created without one.
struct DrawGroupInfo
{
	DrawGroupInfo();

	AsciiString m_fontName;
	int m_fontSize;                                                     // +0x04
	bool m_fontIsBold;                                                  // +0x08
	unsigned char m_pad09[0x2c - 0x09];
};

// ZH GlobalLanguage FontDesc; init reads the draw-group font at +0xD4.
#include "../../Include/Common/GlobalLanguageClass.h"


enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

#include "../../Include/Common/INI/INI.h"

class RayEffectSystem : public SubsystemInterface
{
public:
	RayEffectSystem();
	virtual ~RayEffectSystem();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_pad[0xE0C - 0x0C];
};

// TheHotKeyManager (0x30-byte HotKeyManager, ctor 0x0035973D).
class Rva00359290 : public SubsystemInterface
{
public:
	Rva00359290();
	virtual ~Rva00359290();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_pad[0x30 - 0x0C];
};

// TheInGameUI's slot 108 (+0x1B0) refreshes the layout after a resolution
// change (AptMainMenu::ResetResolution calls it too).
#include "../../Include/GameClient/InGameUI.h"

class Shell : public SubsystemInterface
{
public:
	Shell();
	virtual ~Shell();
	virtual void init();
	virtual void reset();
	virtual void update();
	void push(AsciiString name, bool shutdownImmediate = false);
	void showShell(bool);
	bool showShellMap(bool, bool);

	// GameClient::update clears +0x6C on its first pass and still updates
	// the shell while the GameLogic byte +0x125 is set if +0x5C is.
	unsigned char m_pad0C[0x5c - 0x0C];
	bool m_byte5C;                                                      // +0x5C
	unsigned char m_pad5D[0x6c - 0x5D];
	bool m_byte6C;                                                      // +0x6C
	unsigned char m_pad6D[0x78 - 0x6D];
};

#include "../../Include/GameClient/IMEManagerClass.h"
#include "../../Include/GameClient/GameWindowManager.h"

// GlobalData's screen resolution (ZH m_xResolution, m_yResolution), the
// intro flags GameClient::update returns early on (ZH m_playIntro and
// m_afterIntro; the logo callback 0x00239539 tests +0xAF2 too) and the
// millisecond stall it spins for at most every three seconds (+0xC78).
class GlobalData
{
public:
	unsigned char m_pad[0x30];
	unsigned int m_xResolution;                                         // +0x30
	unsigned int m_yResolution;                                         // +0x34
	unsigned char m_pad38[0xabc - 0x38];
	AsciiString m_initialFile;                                          // +0xABC
	unsigned char m_padAC0[0xaf0 - 0xac0];
	bool m_shellMapOn;                                                  // +0xAF0
	unsigned char m_padAF1[1];
	bool m_playIntro;                                                   // +0xAF2
	bool m_afterIntro;                                                  // +0xAF3
	bool m_byteAF4;                                                     // +0xAF4
	unsigned char m_padAF5[0xc78 - 0xaf5];
	int m_stallMilliseconds;                                            // +0xC78
	unsigned char m_padC7C[0xd36 - 0xc7c];
	bool m_byteD36;                                                     // +0xD36
};

// ZH Mouse; BFME 2 keeps parseIni and initCursorResources virtual (slots 14
// and 15), and init calls slot 22 (+0x58) where ZH sets the mouse limits.
// update calls slot 16 (+0x40) right after the mouse update, as ZH calls
// createStreamMessages.
class Mouse : public SubsystemInterface
{
public:
	virtual ~Mouse();
	virtual void parseIni();                                            // +0x38
	virtual void initCursorResources();                                 // +0x3C
	virtual void createStreamMessages();                                // +0x40
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void setMouseLimits();                                      // +0x58
	// The shared empty body 0x000B3FD0, pinned by address; called after a
	// resolution change here and in AptMainMenu::ResetResolution.
	void rva000B3FD0();
};

// TheAnimationSoundModuleManager (the 0x2C-byte ctor; its list helpers are
// rowed in Rva00432F23Remove.cpp).
class AnimationSoundModuleManager : public SubsystemInterface
{
public:
	AnimationSoundModuleManager();
	virtual ~AnimationSoundModuleManager();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_pad[0x2C - 0x0C];
};

// Created by GameClient factory slot 50 (+0xC8) and not named; init calls
// its slot 4 (+0x10) and hands it to the object owned at +0x13C.
class Rva002D3627Host
{
public:
	virtual ~Rva002D3627Host();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();                                                // +0x10
	virtual void vf05();                                                // +0x14
#define V(n) virtual void vf##n();
	V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
	V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26)
#undef V
	virtual void vf27();                                                // +0x6C
};

// TheTerrainVisual: ZH TerrainVisual (Snapshot, SubsystemInterface), the
// subsystem side at +4.
class G00DFF080Obj : public Snapshot, public SubsystemInterface { public: virtual ~G00DFF080Obj(); };
// Display's movie update is nonvirtual; its subsystem update stays in slot 10.
// Native redraw and mode accessors retain their observed virtual positions.
class Display
{
public:
	virtual ~Display();
	virtual void init();
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual void draw();
	virtual void vslot07(int);
	virtual void vslot08();
	virtual void reset();
	virtual void updateSubsystem();
	virtual bool vslot11(int);
	virtual void vslot12();                                           // +0x30
	virtual void vslot13(int);
	virtual void setWidth(unsigned int width);                         // +0x38
	virtual void setHeight(unsigned int height);                       // +0x3C
	virtual unsigned int getWidth();                                    // +0x40
	virtual unsigned int getHeight();                                   // +0x44
	virtual void setBitDepth(unsigned int bitDepth);                    // +0x48
	virtual unsigned int getBitDepth();                                 // +0x4C
	virtual void setWindowed(bool windowed);                            // +0x50
	virtual bool getWindowed();                                         // +0x54
	virtual bool setDisplayMode(unsigned int xres, unsigned int yres,
		unsigned int bitDepth, bool windowed);                          // +0x58
	virtual void vf23(); virtual void vf24(); virtual void vf25(); virtual void vf26();
	virtual void vf27(); virtual void vf28(); virtual void vf29(); virtual void vf30();
	virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34();
	virtual void vf35(); virtual void vf36(); virtual void vf37(); virtual void vf38();
	virtual void vf39(); virtual void vf40(); virtual void vf41(); virtual void vf42();
	virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46();
	virtual void vf47(); virtual void vf48(); virtual void vf49(); virtual void vf50();
	virtual void vf51(); virtual void vf52(); virtual void vf53(); virtual void vf54();
	virtual void vf55(); virtual void vf56(); virtual void vf57(); virtual void vf58();
	virtual void vf59(); virtual void vf60(); virtual void vf61(); virtual void vf62();
	virtual void vf63(); virtual void vf64(); virtual void vf65(); virtual void vf66();
	virtual void vf67(AsciiString movie, int, int);                     // +0x10C
	virtual void vf68();
	virtual bool isMoviePlaying();                                      // +0x114

	void update();
	void SetStaticImage(int image, int arg, float x0, float y0, float x1, float y1);
	void rva0025C776(int image, float x0, float y0, float x1, float y1, int a, int b);

	unsigned char m_base04[8];
	unsigned char m_pad0C[0x114 - 0x0C];
	bool m_byte114;                                                     // +0x114
};

class W3DDisplay : public Display
{
public:
	void rva0025D2F6();
};
class LanguageFilter : public SubsystemInterface { public: virtual ~LanguageFilter(); };
class VideoPlayerInterface : public SubsystemInterface { public: virtual ~VideoPlayerInterface(); };

class Anim2DCollection : public SubsystemInterface
{
public:
	Anim2DCollection();
	virtual ~Anim2DCollection();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_pad[0x14 - 0x0C];
};

class Image;
#include "../../Include/GameClient/Image.h"

// ZH Keyboard::createStreamMessages follows the update, here slot 15 (+0x3C).
#include "../../Include/GameClient/KeyboardClass.h"
#include "../../Include/GameClient/DisplayStringManager.h"
class SnowManager : public SubsystemInterface { public: virtual ~SnowManager(); };
class Rva0027070CGlobal : public SubsystemInterface { public: virtual ~Rva0027070CGlobal(); };
class CloudBreakEffectManager : public SubsystemInterface { public: virtual ~CloudBreakEffectManager(); };
class FireManager : public SubsystemInterface { public: virtual ~FireManager(); };

#include "../../Include/GameClient/FontLibrary.h"

class BfmeAptWindowManager
{
public:
	virtual void vf00();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void vf06();
	virtual void vf07();
	virtual void vf08();
	virtual void vf09();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();                                                // +0x38
};

// The same Apt window manager object under the placeholder its 0x002227DF
// row was landed with.
class Rva002227DF
{
public:
	void rva002227DF();
};

class GameMessage;
enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

// BFME 2 GameMessageTranslator: translateGameMessage in slot 0, the deleting
// dtor (folded at 0x004296EE) in slot 1.
#include "../../Include/GameClient/FormationTranslator.h"

// Both mode constructors install BED684 and use WindowTranslator's handler.
// The derived default constructor selects mode zero.
class WindowTranslator : public GameMessageTranslator
{
public:
	__declspec(dllimport) __forceinline WindowTranslator() : m_mode(1) {}
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
protected:
	int m_mode;
};

class Rva002390F8 : public WindowTranslator
{
public:
	Rva002390F8() { m_mode = 0; }
};

class AptTranslator : public GameMessageTranslator
{
public:
	AptTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	unsigned char m_pad[0x204 - 4];
};

class MetaEventTranslator : public GameMessageTranslator
{
public:
	MetaEventTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	int m_lastKeyDown;						// +0x04
	int m_lastModState;						// +0x08
	ICoord2D m_mouseDownPosition[3];		// +0x0C
	bool m_nextUpShouldCreateDoubleClick[3];	// +0x24
};

// Zero Hour's MetaEventTranslator constructor (MetaEvent.cpp), retail
// 0x001DB432, 92 bytes, after MetaMap::findGameMessageMetaType 0x001DB3FE;
// GameClient::init news it. It lives in this unit because MetaEvent.cpp's
// ICoord2D is a plain struct inside the message-argument union.
MetaEventTranslator::MetaEventTranslator() : m_lastKeyDown(0), m_lastModState(0)
{
	for (int i = 0; i < 3; ++i)
	{
		m_nextUpShouldCreateDoubleClick[i] = false;
		m_mouseDownPosition[i].x = 0;
		m_mouseDownPosition[i].y = 0;
	}
}

// vftable 0x00BED660, translate 0x00359729.
class HotKeyTranslator : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};

class Rva0042CBB6 : public GameMessageTranslator
{
public:
	Rva0042CBB6();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	void rva0042D068();

private:
	unsigned char m_pad[0x44 - 4];
};

class PlaceEventTranslator : public GameMessageTranslator
{
public:
	PlaceEventTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	unsigned char m_pad[0x18 - 4];
};


// Constructor 0x0043132D, priority 40.
class GUICommandTranslator : public GameMessageTranslator
{
public:
	GUICommandTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~GUICommandTranslator();

private:
	unsigned char m_pad[0x3C - 4];
};

class SelectionTranslator : public GameMessageTranslator
{
public:
	SelectionTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	unsigned char m_pad[0x40 - 4];
};

class BfmeOwnVVD : public GameMessageTranslator
{
public:
	BfmeOwnVVD();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	void rva0042F213();

private:
	unsigned char m_pad[0x158 - 4];
};

// vftable 0x00BED668, translate 0x00428C43.
class HintSpyTranslator : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};

// vftable 0x00BED670, translate 0x00428D66.
class GameClientMessageDispatcher : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};


// The object owned at +0x13C: ctor 0x0023A128, dtor 0x00239D7A, and the
// owning slot's reset 0x0023A053, each landed under its own placeholder.
class Rva00239D7A;

class Rva0023A053
{
public:
	void reset(Rva00239D7A *p);
};

class Rva0023A128
{
public:
	Rva0023A128(void *client, void *host, int arg);

private:
	unsigned char m_pad[0x20];
};

// Views GameClient::update calls through. TheTacticalView's slots 54 (+0xD8)
// and 30 (+0x78) stand where ZH asks isTimeFrozen and
// isCameraMovementFinished; the two script-engine freeze tests and the
// frame-period check are matched rows under placeholder names.
#include "../../Include/GameClient/View.h"

class ScriptEngine;
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00203ACEByteField { public: unsigned char get() const; };

// ZH PlayerList::getLocalPlayer and Player::getPlayerIndex: the local
// player at +0x10, its index at +0x54.
#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"

#include "../../Include/Common/GameEngine.h"

// ZH GhostObjectManager::updateOrphanedObjects, slot 6 (+0x18).
#include "../../Include/GameLogic/GhostObjectManager.h"

// ZH ParticleSystemManager::setLocalPlayerIndex stores +0x64.
class ParticleSystemManager
{
public:
	void setLocalPlayerIndex(int index) { m_localPlayerIndex = index; }

private:
	unsigned char m_pad[0x64];
	int m_localPlayerIndex;                                             // +0x64
};

#include "../../Include/GameClient/Eva.h"
// TheScoredKillEvaAnnouncerController, under the placeholder class
// GameEngine::init creates it with.
class Rva0022C22CSubsystem : public SubsystemInterface { public: virtual ~Rva0022C22CSubsystem(); };

class Rva005D124D { public: int rva005D124D(); };
class Rva00239105 { public: void rva00239105(); };
class Rva00239300 { public: void rva00239300(int frame, int periodFrame); };

// The matched one-int handle ctor 0x00211E75; update passes one by value,
// built from a callback address, to the unrowed registration 0x003FE7E6,
// which writes the next id to its second argument. Retail builds each handle
// in the argument slot and saves its address before loading ECX, which is
// what an inline forwarding constructor over the out-of-line one emits.
class Rva00211E75
{
public:
	Rva00211E75(const int *arg);
	Rva00211E75(const Rva00211E75 &other);
	~Rva00211E75();

private:
	void *m_impl;
};

class Rva00211E75Callback : public Rva00211E75
{
public:
	Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}
};

extern DrawGroupInfo *TheDrawGroupInfo;
extern RayEffectSystem *TheRayEffects;
class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;
extern InGameUI *TheInGameUI;
extern Shell *TheShell;
extern IMEManager *TheIMEManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern GameWindowManager *TheWindowManager;
extern FontLibrary *TheFontLibrary;
extern Mouse *TheMouse;
extern AnimationSoundModuleManager *TheAnimationSoundModuleManager;               // TheAnimationSoundModuleManager
class LivingWorld; extern LivingWorld *TheLivingWorld;
extern G00DFF080Obj *TheTerrainVisual;                        // TheTerrainVisual
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern HeaderTemplateManager *TheHeaderTemplateManager;
extern LanguageFilter *TheLanguageFilter;
extern VideoPlayerInterface *TheVideoPlayer;
extern Anim2DCollection *TheAnim2DCollection;
extern ImageCollection *TheMappedImageCollection;
extern Keyboard *TheKeyboard;
extern DisplayStringManager *TheDisplayStringManager;
extern SnowManager *TheSnowManager;
extern Rva0027070CGlobal *TheCloudEffectManager;                   // TheCloudEffectManager
extern CloudBreakEffectManager *TheCloudBreakEffectManager;
extern FireManager *TheFireManager;
extern class MessageStream *TheMessageStream;           // TheMessageStream
extern GlobalLanguage *TheGlobalLanguageData;
extern float g_00DBA4FC;                                // client frame rate
extern void *g_00E03210;                                // the Rva0042CBB6 translator
class LookAtTranslator; extern LookAtTranslator *TheLookAtTranslator;
extern FormationTranslator *TheFormationTranslator;
extern Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController;
extern Eva *TheEva;
extern View *TheTacticalView;
extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern GameEngine *TheGameEngine;
extern GhostObjectManager *TheGhostObjectManager;
extern ParticleSystemManager *TheParticleSystemManager;
extern int BfmeLogicFramesPerSecond;                                // LogicFramesPerSecond
extern int g_00E02EC4;

void Rva0038072AClear();
IMEManager *CreateIMEManagerInterface();
LanguageFilter *createLanguageFilter();
class AptGuiFX
{
public:
	static void Init();
};
void Rva00220DCDInit();
void rva002210CF();
void Rva002220DCInit();
void bfmeReset();
// Unrowed 0x0041267F (10 bytes: two calls), pinned by address.
void Rva0041267F();
// Unrowed 0x0038076D, the per-frame companion of the 0x0038072A clear.
void Rva0038076DUpdate();
void bfmeReleaseQueuedDeviceInterfaces();
bool Rva003FE7E6(Rva00211E75Callback callback, int *id);
// The four callbacks update registers on its first pass (0x00239539 is the
// logo-movie gate).
int rva00239539(void *, bool);
int rva0023BDD7(void *, bool);
int rva0023958B(void *, bool);
int rva00239122(void *, bool);
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>

// ZH GameClient::GameClient. Retail 0x0023BC36: Snapshot vptr 0xBBB554 is
// stored first, then the GameClient vptrs 0x00BED850/0x00BED840, unwind states
// 0..0xB over the members; the 32 translator slots at +0x30 are filled with -1,
// the TOC is cleared through the fold 0x00239D49 and a new(0x2C) built by
// 0x00317B35 is stored in TheDrawGroupInfo (data ledger 0x00A01CD8).
GameClient::GameClient()
	: m_frame(0), m_drawableList(0), m_nextDrawableID(1), m_numTranslators(0),
	  m_commandTranslator(0), m_dwordB8(0), m_stringBC(""), m_byteC0(0), m_byteC1(0), m_dwordC4(0),
	  m_byteC8(0), m_displayModePending(0), m_byteCA(0), m_pendingXRes(0),
	  m_pendingYRes(0), m_pendingBitDepth(0), m_previousWidth(0), m_previousHeight(0),
	  m_previousBitDepth(0), m_count138(0)
{
	// zero our translator list
	for (int i = 0; i < MAX_CLIENT_TRANSLATORS; i++)
		m_translators[i] = TRANSLATOR_ID_INVALID;

	m_drawableTOC.clear();

	TheDrawGroupInfo = new DrawGroupInfo;
}

GameClient::~GameClient()
{
	Rva0038072AClear();

	delete TheDrawGroupInfo;
	TheDrawGroupInfo = 0;

	// clear any drawable TOC we might have
	m_drawableTOC.clear();

	// destroy all Drawables
	Drawable *draw, *nextDraw;
	for (draw = m_drawableList; draw; draw = nextDraw)
	{
		nextDraw = draw->getNextDrawable();
		destroyDrawable(draw);
	}
	m_drawableList = 0;

	rva0023ABDD();

	::delete TheRayEffects;
	TheRayEffects = 0;

	::delete ((Rva00359290 *)TheHotKeyManager);
	TheHotKeyManager = 0;

	::delete TheInGameUI;
	TheInGameUI = 0;

	::delete TheShell;
	TheShell = 0;

	::delete TheIMEManager;
	TheIMEManager = 0;

	if (g_bfmeAptWindowManager)
		g_bfmeAptWindowManager->vf14();

	::delete TheWindowManager;
	TheWindowManager = 0;

	if (TheFontLibrary)
	{
		TheFontLibrary->reset();
		::delete TheFontLibrary;
		TheFontLibrary = 0;
	}

	::delete TheMouse;
	TheMouse = 0;

	::delete TheAnimationSoundModuleManager;
	TheAnimationSoundModuleManager = 0;

	::delete ((Rva002D3627Host *)TheLivingWorld);
	TheLivingWorld = 0;

	::delete TheTerrainVisual;
	TheTerrainVisual = 0;

	::delete TheDisplay;
	TheDisplay = 0;

	delete TheHeaderTemplateManager;
	TheHeaderTemplateManager = 0;

	::delete TheLanguageFilter;
	TheLanguageFilter = 0;

	::delete TheVideoPlayer;
	TheVideoPlayer = 0;

	// destroy all translators
	for (unsigned int i = 0; i < m_numTranslators; i++)
		TheMessageStream->removeTranslator(m_translators[i]);
	m_numTranslators = 0;
	m_commandTranslator = 0;

	::delete TheAnim2DCollection;
	TheAnim2DCollection = 0;

	::delete TheMappedImageCollection;
	TheMappedImageCollection = 0;

	::delete TheKeyboard;
	TheKeyboard = 0;

	::delete TheDisplayStringManager;
	TheDisplayStringManager = 0;

	::delete TheSnowManager;
	TheSnowManager = 0;

	::delete TheCloudEffectManager;
	TheCloudEffectManager = 0;

	::delete TheCloudBreakEffectManager;
	TheCloudBreakEffectManager = 0;

	::delete TheFireManager;
	TheFireManager = 0;
}

void GameClient::init()
{
	setFrameRate(g_00DBA4FC);

	INI ini;
	ini.loadFile(AsciiString("Data\\INI\\DrawGroupInfo.ini"), INI_LOAD_OVERWRITE, 0);

	if (TheGlobalLanguageData)
	{
		const AsciiString &fontName = TheGlobalLanguageData->m_drawGroupInfoFont.name;
		if (!((const StringBase<char> *)&fontName)->isEmpty())
		{
			TheDrawGroupInfo->m_fontName = fontName;
			TheDrawGroupInfo->m_fontSize = TheGlobalLanguageData->m_drawGroupInfoFont.size;
			TheDrawGroupInfo->m_fontIsBold = TheGlobalLanguageData->m_drawGroupInfoFont.bold;
		}
	}

	// create the display string factory
	TheDisplayStringManager = createDisplayStringManager();
	if (TheDisplayStringManager)
	{
		TheDisplayStringManager->init();
		TheDisplayStringManager->setName(AsciiString("TheDisplayStringManager"));
	}

	// create the keyboard
	TheKeyboard = createKeyboard();
	TheKeyboard->init();
	TheKeyboard->setName(AsciiString("TheKeyboard"));

	// allocate and load image collection for the GUI and just load the 256x256 ones for now
	TheMappedImageCollection = new ImageCollection;
	TheMappedImageCollection->load(512);

	// now that we have all the images loaded ... load any animation definitions from those images
	TheAnim2DCollection = new Anim2DCollection;
	TheAnim2DCollection->init();
	TheAnim2DCollection->setName(AsciiString("TheAnim2DCollection"));

	TheAnimationSoundModuleManager = new AnimationSoundModuleManager;
	TheAnimationSoundModuleManager->init();
	TheAnimationSoundModuleManager->setName(AsciiString("TheAnimationSoundModuleManager"));

	// register message translators
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new Rva002390F8, 4);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new AptTranslator, 5);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new WindowTranslator, 10);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new MetaEventTranslator, 20);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new HotKeyTranslator, 25);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new Rva0042CBB6, 27);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new PlaceEventTranslator, 30);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new FormationTranslator, 35);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new GUICommandTranslator, 40);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new SelectionTranslator, 50);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new BfmeOwnVVD, 60);
	m_translators[m_numTranslators] = TheMessageStream->attachTranslator(new CommandTranslator, 70);
	// we keep a pointer to the command translator because it's useful
	m_commandTranslator = (CommandTranslator *)TheMessageStream->findTranslator(m_translators[m_numTranslators++]);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new HintSpyTranslator, 100);
	m_translators[m_numTranslators++] = TheMessageStream->attachTranslator(new GameClientMessageDispatcher, 999999999);

	// create the font library
	TheFontLibrary = createFontLibrary();
	if (TheFontLibrary)
	{
		TheFontLibrary->init();
		TheFontLibrary->loadIniFilesFromLegend();
	}

	// create the mouse
	TheMouse = createMouse();
	TheMouse->parseIni();
	TheMouse->initCursorResources();
	TheMouse->setName(AsciiString("TheMouse"));

	// instantiate the display
	TheDisplay = createGameDisplay();
	if (TheDisplay)
	{
		TheDisplay->init();
		((SubsystemInterface *)TheDisplay)->setName(AsciiString("TheDisplay"));
	}

	TheHeaderTemplateManager = new HeaderTemplateManager;
	if (TheHeaderTemplateManager)
		TheHeaderTemplateManager->init();

	// create the window manager
	TheWindowManager = createWindowManager();
	if (TheWindowManager)
	{
		TheWindowManager->init();
		TheWindowManager->setName(AsciiString("TheWindowManager"));
	}

	// create the IME manager
	TheIMEManager = CreateIMEManagerInterface();
	if (TheIMEManager)
	{
		TheIMEManager->init();
		TheIMEManager->setName(AsciiString("TheIMEManager"));
	}

	// create the shell
	TheShell = new Shell;
	if (TheShell)
	{
		TheShell->init();
		TheShell->setName(AsciiString("TheShell"));
	}

	// instantiate the in-game user interface
	TheInGameUI = createInGameUI();
	if (TheInGameUI)
	{
		TheInGameUI->init();
		TheInGameUI->setName(AsciiString("TheInGameUI"));
	}

	TheHotKeyManager = (HotKeyManager *)new Rva00359290;
	if (TheHotKeyManager)
	{
		((Rva00359290 *)TheHotKeyManager)->init();
		((Rva00359290 *)TheHotKeyManager)->setName(AsciiString("TheHotKeyManager"));
	}

	// create the terrain visual
	TheTerrainVisual = createTerrainVisual();
	if (TheTerrainVisual)
	{
		TheTerrainVisual->init();
		TheTerrainVisual->setName(AsciiString("TheTerrainVisual"));
	}

	TheLivingWorld = (LivingWorld *)vf50();
	if (((Rva002D3627Host *)TheLivingWorld))
	{
		((Rva002D3627Host *)TheLivingWorld)->vf04();
		((Rva0023A053 *)&m_owned13C)->reset((Rva00239D7A *)new Rva0023A128(this, ((Rva002D3627Host *)TheLivingWorld), (int)g_00E03210));
	}

	// create the ray effects manager
	TheRayEffects = new RayEffectSystem;
	if (TheRayEffects)
	{
		TheRayEffects->init();
		TheRayEffects->setName(AsciiString("TheRayEffects"));
	}

	TheMouse->init();	//finish initializing the mouse.

	// set the limits of the mouse now that we've created the display and such
	if (TheMouse)
	{
		TheMouse->setMouseLimits();
		TheMouse->setName(AsciiString("TheMouse"));
	}

	// create the video player
	TheVideoPlayer = createVideoPlayer();
	if (TheVideoPlayer)
	{
		TheVideoPlayer->init();
		TheVideoPlayer->setName(AsciiString("TheVideoPlayer"));
	}

	// create the language filter.
	TheLanguageFilter = createLanguageFilter();
	if (TheLanguageFilter)
	{
		TheLanguageFilter->init();
		TheLanguageFilter->setName(AsciiString("TheLanguageFilter"));
	}

	TheDisplayStringManager->postProcessLoad();

	TheSnowManager = createSnowManager();
	if (TheSnowManager)
	{
		TheSnowManager->init();
		TheSnowManager->setName(AsciiString("TheSnowManager"));
	}

	TheCloudEffectManager = createCloudEffectManager();
	if (TheCloudEffectManager)
	{
		TheCloudEffectManager->init();
		TheCloudEffectManager->setName(AsciiString("TheCloudEffectManager"));
	}

	TheCloudBreakEffectManager = createCloudBreakEffectManager();
	if (TheCloudBreakEffectManager)
	{
		TheCloudBreakEffectManager->init();
		TheCloudBreakEffectManager->setName(AsciiString("TheCloudBreakEffectManager"));
	}

	TheFireManager = createFireManager();
	if (TheFireManager)
	{
		TheFireManager->init();
		TheFireManager->setName(AsciiString("TheFireManager"));
	}

	((Rva002227DF *)g_bfmeAptWindowManager)->rva002227DF();
	AptGuiFX::Init();
	Rva00220DCDInit();
	rva002210CF();
	Rva002220DCInit();
}

// ?reset@GameClient@@UAEXXZ
void GameClient::reset()
{
	Drawable *draw, *nextDraw;

	m_drawableHash.clear();
	m_drawableHash.resize(0x2000);
	m_frame = 0;

	// need to reset the in game UI to clear drawables before they are destroyed
	TheInGameUI->reset();

	// destroy all Drawables
	for (draw = m_drawableList; draw; draw = nextDraw)
	{
		nextDraw = draw->getNextDrawable();
		destroyDrawable(draw);
	}
	m_drawableList = 0;

	TheDisplay->reset();
	TheTerrainVisual->reset();
	TheRayEffects->reset();
	TheVideoPlayer->reset();
	if (((Rva002D3627Host *)TheLivingWorld))
		((Rva002D3627Host *)TheLivingWorld)->vf05();
	TheAnimationSoundModuleManager->reset();
	bfmeReset();

	if (TheSnowManager)
		TheSnowManager->reset();
	if (TheCloudEffectManager)
		TheCloudEffectManager->reset();
	if (TheCloudBreakEffectManager)
		TheCloudBreakEffectManager->reset();
	if (TheFireManager)
		TheFireManager->reset();

	// clear any drawable TOC we might have
	m_drawableTOC.clear();

	m_stringBC = "";
	m_byteC1 = 0;
	m_byteC0 = 0;
	rva0023ABDD();
	m_count138 = 0;
}

// The pending display-mode apply update calls (0x00239759) is rowed in
// GameClientDisplayModeChange.cpp.

// ?update@GameClient@@UAEXXZ
void GameClient::update()
{
	((BfmeOwnVVD *)TheLookAtTranslator)->rva0042F213();
	((Rva0042CBB6 *)g_00E03210)->rva0042D068();
	((Rva005D124D *)TheFormationTranslator)->rva005D124D();

	if (((Rva002D3627Host *)TheLivingWorld))
	{
		((Rva002D3627Host *)TheLivingWorld)->vf27();
		((Rva00239105 *)m_owned13C.get())->rva00239105();
	}

	static bool firstUpdate = true;
	if (firstUpdate)
	{
		if (TheShell)
			TheShell->m_byte6C = 0;
		Rva003FE7E6(Rva00211E75Callback((int)rva00239539), &g_00E02EC4);
		Rva003FE7E6(Rva00211E75Callback((int)rva0023BDD7), &g_00E02EC4);
		Rva003FE7E6(Rva00211E75Callback((int)rva0023958B), &g_00E02EC4);
		Rva003FE7E6(Rva00211E75Callback((int)rva00239122), &g_00E02EC4);
	}
	firstUpdate = false;

	if (TheSnowManager)
		TheSnowManager->update();
	if (TheCloudEffectManager)
		TheCloudEffectManager->update();
	if (TheCloudBreakEffectManager)
		TheCloudBreakEffectManager->update();
	if (TheFireManager)
		TheFireManager->update();

	TheAnim2DCollection->update();

	if (TheKeyboard)
	{
		TheKeyboard->update();
		TheKeyboard->createStreamMessages();
	}

	TheScoredKillEvaAnnouncerController->update();
	TheEva->update();

	if (TheMouse)
	{
		TheMouse->update();
		TheMouse->createStreamMessages();
	}

	Rva0038076DUpdate();

	if (TheWritableGlobalData->m_playIntro || TheWritableGlobalData->m_afterIntro)
	{
		TheDisplay->vslot12();
		TheDisplay->updateSubsystem();
		return;
	}

	TheWindowManager->update();
	TheVideoPlayer->update();
	bfmeReleaseQueuedDeviceInterfaces();

	static unsigned int lastStallTime;
	if (TheWritableGlobalData->m_stallMilliseconds > 0)
	{
		unsigned int now = timeGetTime();
		if (now - lastStallTime > 3000)
		{
			while (timeGetTime() < TheWritableGlobalData->m_stallMilliseconds + now)
				;
			lastStallTime = timeGetTime();
		}
	}

	bool freezeTime = TheTacticalView->isTimeFrozen() && !TheTacticalView->isCameraMovementFinished();
	freezeTime = freezeTime || ((Rva00203B08 *)TheScriptEngine)->rva0020424FF();
	freezeTime = freezeTime || ((Rva00203ACEByteField *)TheScriptEngine)->get();
	freezeTime = freezeTime || TheGameLogic->isGamePaused();
	int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

	static unsigned int lastFrame = ~0;
	freezeTime = freezeTime || (lastFrame == m_frame);

	bool shroudOn = TheGameEngine->rva00225D38();
	if (!freezeTime && !TheGameLogic->getFlag125())
	{
		lastFrame = m_frame;

		if (shroudOn)
			TheGhostObjectManager->updateOrphanedObjects(0, 0);

		Drawable *draw = firstDrawable();
		while (draw)
		{
			Drawable *next = draw->getNextDrawable();
			if (shroudOn)
			{
				Object *object = draw->getObject();
				if (object)
				{
					CellShroudStatus ss = object->getShroudStatusForPlayer(localPlayerIndex);
					if (ss >= SHROUD_STATUS_FOGGED && draw->getShroudClearFrame() != 0)
					{
						unsigned int limit = 2 * BfmeLogicFramesPerSecond;
						if (object->isEffectivelyDead())
							limit += 3 * BfmeLogicFramesPerSecond;
						if (TheGameLogic->getFrame() < limit + draw->getShroudClearFrame())
							ss = SHROUD_STATUS_CLEAR;
					}
					draw->setFullyObscuredByShroud(ss >= SHROUD_STATUS_FOGGED);
				}
			}
			draw->updateDrawable();
			draw = next;
		}

		TheAnimationSoundModuleManager->update();
		if (TheGameEngine->rva00225D38())
			((Rva00239300 *)this)->rva00239300(TheGameLogic->getFrame(), 1);
		else
			((Rva00239300 *)this)->rva00239300(TheGameLogic->getFrame(), 0);
	}

	TheGameLogic->rva002423E3();

	if (!TheGameLogic->getFlag125())
	{
		TheTerrainVisual->update();
		TheDisplay->updateSubsystem();
	}
	else
	{
		TheDisplay->update();
	}

	if (!freezeTime)
		TheParticleSystemManager->setLocalPlayerIndex(localPlayerIndex);

	TheDisplay->vslot12();
	TheDisplayStringManager->update();

	if (!TheGameLogic->getFlag125() || TheShell->m_byte5C)
	{
		TheShell->update();
		if (m_displayModePending)
			rva00239759();
	}

	TheInGameUI->update();
	rva00239911();
}

// Drawable helpers under the names their ledger rows carry. 0x00276470
// lerps +0x418 toward +0x424 and returns +0x38 for a drawable without an
// object.
class Rva00276470Drawable { public: const Coord3D *rva00276470() const; };
class Rva00270FEE { public: float rva00271008(); };
class Rva00270260 { public: bool rva00270260(); };
class Rva002707FA { public: void rva002707FA(unsigned char value); };

// GameClient slot 26 (0x002391AA): BFME 2 has no ZH counterpart. Target
// evidence: the only caller hands it the frustum of the camera it just
// updated; each drawable is bounded by a sphere around 0x00276470 padded by
// the argument (25 when negative) plus 0x00271008, tested against planes
// 1-4 of the frustum's six, and the plane
// that rejects it is cached at +0x35C. The sphere and plane test follow
// WW3D SphereClass and PlaneClass::In_Front.
void GameClient::rva002391AA(const FrustumClass *frustum, float radiusPad, GameClientFuncPtr userFunc, void *userData)
{
	if (radiusPad < 0.0f)
		radiusPad = 25.0f;

	Drawable *draw, *nextDrawable;
	for (draw = m_drawableList; draw; draw = nextDrawable)
	{
		nextDrawable = draw->getNextDrawable();

		bool visible;
		Object *obj = draw->getObject();
		if (obj && thingTemplateTestKindOfByte118(obj->getTemplate(), 0x40))
			visible = true;
		else
		{
			const Coord3D *pos = ((Rva00276470Drawable *)draw)->rva00276470();
			Vector3 center(pos->x, pos->y, pos->z);
			SphereClass sphere(Vector3(center.X, center.Y, center.Z), radiusPad);
			sphere.Radius += ((Rva00270FEE *)draw)->rva00271008();

			// The plane that culled the drawable last time is tried first.
			int cullPlane = draw->m_cullPlane;
			if (cullPlane >= 1 && cullPlane <= 4)
			{
				const PlaneClass &plane = frustum->Planes[cullPlane];
				if (plane.In_Front(sphere))
					continue;
			}

			visible = !((Rva00270260 *)draw)->rva00270260();
			for (int i = 1; i <= 4; ++i)
			{
				if (cullPlane == i)
					continue;
				const PlaneClass &plane = frustum->Planes[i];
				if (plane.In_Front(sphere))
				{
					draw->m_cullPlane = i;
					visible = false;
					break;
				}
			}
		}

		if (visible)
		{
			(*userFunc)(draw, userData);
			draw->m_cullPlane = 0;
			((Rva002707FA *)draw)->rva002707FA(1);
		}
		else
			((Rva002707FA *)draw)->rva002707FA(0);
	}
}

// 0x002763E6 spline-interpolates the position between +0x40C and +0x430 and
// is the getPosition ZH's iterateDrawablesInRegion calls. 0x0027930F is ZH
// Drawable::setTimeOfDay (MODELCONDITION_NIGHT set for TIME_OF_DAY_NIGHT).
class Rva0027930FHost { public: void rva0027930F(int v); };

// Donor: ZH GameClient::iterateDrawablesInRegion and setTimeOfDay, same
// loops. Slot 27 (0x00238EBF) visits the drawables slot 26 left uncached.
void GameClient::iterateDrawablesInRegion(Region3D *region, GameClientFuncPtr userFunc, void *userData)
{
	Drawable *draw, *nextDrawable;

	for (draw = m_drawableList; draw; draw = nextDrawable)
	{
		nextDrawable = draw->getNextDrawable();

		const Coord3D *pos = ((Drawable *)draw)->getPosition();
		float x = pos->x;
		float y = pos->y;
		float z = pos->z;
		if (region == 0 ||
			(x >= region->lo.x && x <= region->hi.x &&
			 y >= region->lo.y && y <= region->hi.y &&
			 z >= region->lo.z && z <= region->hi.z))
		{
			(*userFunc)(draw, userData);
		}
	}
}

void GameClient::rva00238EBF(GameClientFuncPtr userFunc, void *userData)
{
	Drawable *draw, *nextDrawable;

	for (draw = m_drawableList; draw; draw = nextDrawable)
	{
		int cullPlane = draw->m_cullPlane;
		nextDrawable = draw->getNextDrawable();
		if (cullPlane < 1 || cullPlane > 4)
			(*userFunc)(draw, userData);
	}
}

void GameClient::setTimeOfDay(TimeOfDay tod)
{
	Drawable *draw = firstDrawable();

	while (draw)
	{
		((Rva0027930FHost *)draw)->rva0027930F(tod);

		draw = draw->getNextDrawable();
	}
}

// Donor: ZH GameClient::findDrawableByID's hash lookup (commented out in ZH
// for the vector); retail has no INVALID_DRAWABLE_ID test.
Drawable *GameClient::findDrawableByID(const DrawableID id)
{
	DrawablePtrHash::iterator it = m_drawableHash.find(id);
	if (it == m_drawableHash.end())
		return 0;

	return (*it).second;
}

// Donor: ZH GameClient::evaluateContextCommand.
GameMessage::Type GameClient::evaluateContextCommand(Drawable *draw, const Coord3D *pos,
	CommandTranslator::CommandEvaluateType cmdType)
{
	if (m_commandTranslator)
		return m_commandTranslator->evaluateContextCommand(draw, pos, cmdType);
	else
		return GameMessage::MSG_INVALID;
}

// Donor: ZH GameClient::releaseShadows and allocateShadows.
void GameClient::releaseShadows(void)
{
	Drawable *draw;
	for (draw = firstDrawable(); draw; draw = draw->getNextDrawable())
		draw->rva00272A38();
}

void GameClient::allocateShadows(void)
{
	Drawable *draw;
	for (draw = firstDrawable(); draw; draw = draw->getNextDrawable())
		draw->rva00272A51();
}

// The objects held in the +0xE4 list: destroyed through the virtual
// destructor in slot 7 (+0x1C) and freed with the global operator delete.
class Rva00239911Item
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual ~Rva00239911Item();
};

class Rva00239380Holder
{
public:
	void rva00239380();
};

// Slot 36, no ZH counterpart: delete every object in the +0xE4 list, then
// clear it through 0x00239380.
void GameClient::rva00239911(void)
{
	for (Rva00239AF4Node *node = (Rva00239AF4Node *)m_drawableListE4.head()->_M_next;
		node != m_drawableListE4.head(); node = (Rva00239AF4Node *)node->_M_next)
		::delete (Rva00239911Item *)node->_M_data;

	((Rva00239380Holder *)&m_drawableListE4)->rva00239380();
}

// Map-object ambient sound (0x0023B383), called from the GameLogic map-object
// loop at 0x002454FB with the object's property Dict, its ThingTemplate and
// position. No ZH counterpart: ZH applies the same objectSoundAmbient* map
// properties inline in Object.cpp; BFME 2 reads them through 0x00433796
// (Dict getBool/getAsciiString/getReal/getInt, TheAudio slot 0x12C lookup,
// Drawable 0x0027682F base info), which reports forced-off, a customized info
// reference and enabled. A customized info is renamed " OC %d " plus its name
// (0x00433403) under the counter at +0x138 and handed to TheAudio (slot 74);
// otherwise the template's ambient slot 0x25 (0x00239435) is used. The event
// (canonical 0x88-byte prefix, ctor 0x002D982A, dtor 0x002D9A43) is added
// through slot 25; handles from 5 up are kept at +0x120 (folded push_back
// 0x004DFCB0, compared unsigned) and the customized reference at +0x12C
// (push_back 0x0023AD91); 0x0023ABDD removes and clears both.
class Rva004EC166
{
public:
	void rva00433403(const AsciiString &name);

	char m_pad00[8];
	AsciiString m_audioName;                                            // +0x08
};

class AudioManager
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03(); virtual void vf04();
	virtual void vf05(); virtual void vf06(); virtual void vf07(); virtual void vf08(); virtual void vf09();
	virtual void vf10(); virtual void vf11(); virtual void vf12(); virtual void vf13(); virtual void vf14();
	virtual void vf15(); virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23(); virtual void vf24();
	virtual unsigned int addAudioEvent(const BfmeAudioEventPrefix136 *event);  // slot 25 (+0x64)
	virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29(); virtual void vf30();
	virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
	virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40();
	virtual void vf41(); virtual void vf42(); virtual void vf43(); virtual void vf44(); virtual void vf45();
	virtual void vf46(); virtual void vf47(); virtual void vf48(); virtual void vf49(); virtual void vf50();
	virtual void vf51(); virtual void vf52(); virtual void vf53(); virtual void vf54(); virtual void vf55();
	virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59(); virtual void vf60();
	virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64(); virtual void vf65();
	virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70();
	virtual void vf71(); virtual void vf72(); virtual void vf73();
	virtual void addAudioEventInfo(Rva004EC166 *info);                      // slot 74 (+0x128)
};
extern AudioManager *TheAudio;

// The 4-byte owning reference; release is inlined at each scope exit.
struct Rva00239057Ref : OpaqueRefElement4
{
	Rva004EC166 *get() const { return (Rva004EC166 *)referent; }
};

// 8-byte template audio slot, returned by value; the info reference is at +4.
class Rva002390CB
{
public:
	int m_00;
	OpaqueRefElement4 m_info;                                           // +0x04
};

// Declared nothrow: retail stores no EH state for the reference constructed
// before this call (the state moves straight from 0 to the temporary's 3).
class Rva00239435
{
public:
	Rva002390CB rva00239435(int index) throw();
};

struct Rva0023AD91Record
{
	Rva0023AD91Record();
	Rva0023AD91Record(const Rva0023AD91Record &);
	~Rva0023AD91Record();
	Rva0023AD91Record &operator=(const Rva0023AD91Record &);

private:
	char bytes[4];
};

// Retail's _Construct<Rva0023AD91Record> is the 18-byte frameless nothrow
// placement copy rowed at 0x002393AA (folded with _Construct<Rva0036CA00Str>);
// this TU's private EH-frame copy and its 250-byte inline-overflow copy are not
// retail's bodies. Emit the nothrow placement copy (inline, so it stays a
// foldable COMDAT like the other units'; an anchor below forces it out) and take
// push_back's overflow/copy/fill helpers out of line, so the link keeps retail's
// bodies instead of this TU's private copies.
namespace _STL {
template <> inline void _Construct<Rva0023AD91Record, Rva0023AD91Record>(Rva0023AD91Record *__p, const Rva0023AD91Record &__val) throw()
{
	new (__p) Rva0023AD91Record(__val);
}
template <> void vector<Rva0023AD91Record, allocator<Rva0023AD91Record> >::push_back(const Rva0023AD91Record &);
}

// Anchor only: makes this unit emit its nothrow _Construct COMDAT for the
// 0x002393AA row. Not retail code.
void bfmeEmitGameClientDrawableTOCConstruct(Rva0023AD91Record *__p, const Rva0023AD91Record &__val)
{
	_STL::_Construct(__p, __val);
}

void TranslateAudioProperties(Dict *props, Drawable *draw, ThingTemplate *tmpl, bool *soundOff,
	Rva000A8C9B *customInfo, bool *soundEnabled);

void GameClient::rva0023B383(Dict *props, ThingTemplate *thingTemplate, const Coord3D *pos)
{
	bool soundOff = false;
	bool soundEnabled = false;
	Rva00239057Ref customInfo;

	TranslateAudioProperties(props, 0, thingTemplate, &soundOff, (Rva000A8C9B *)&customInfo, &soundEnabled);
	if (soundOff || !soundEnabled)
		return;

	Rva00239057Ref info;
	if (customInfo.referent)
	{
		AsciiString name;
		name.format(" OC %d ", m_count138);
		name.concat(customInfo.get()->m_audioName);
		customInfo.get()->rva00433403(name);
		m_count138++;
		TheAudio->addAudioEventInfo(customInfo.get());
		info.rva00239057(&customInfo);
	}
	else
	{
		(OpaqueRefElement4 &)info = ((Rva00239435 *)thingTemplate)->rva00239435(0x25).m_info;
		if (!info.referent)
			return;
	}

	BfmeAudioEventPrefix136 event(info, *(const BfmeEventPositionView *)pos, 0);
	long handle = TheAudio->addAudioEvent(&event);
	if ((unsigned long)handle >= 5)
	{
		m_audioHandles.push_back(handle);
		if (customInfo.referent)
			((_STL::vector<Rva0023AD91Record> *)&m_vector12C)->push_back((const Rva0023AD91Record &)customInfo);
	}
}

// Callback 3 (0x0023958B): BFME 2's title-screen logo, no ZH counterpart.
// It shows the mapped image TitleScreenLogo through the display's 0x0025C72C,
// plays the FadeInGameMovie transition and pumps the window loop for five
// seconds, then either fades the image out over the shell map (0x0025C776)
// or replays the transition.
class GameWindowTransitionsHandler : public SubsystemInterface
{
public:
	virtual ~GameWindowTransitionsHandler();
	void setGroup(AsciiString groupName, bool immediate);
	void reverse(AsciiString groupName);
	void rva001DC5EC();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;
void setFPMode();

int rva0023958B(void *, bool allowLegal)
{
	int result = 1;
	TheGameEngine->serviceWindowsOS();
	if (allowLegal)
	{
		TheWritableGlobalData->m_byteD36 = false;
		TheWritableGlobalData->m_byteAF4 = true;
		TheWritableGlobalData->m_byteD36 = false;
		AsciiString name("TitleScreenLogo");
		const Image *image = TheMappedImageCollection->findImageByName(name);
		if (image)
		{
			TheDisplay->SetStaticImage((int)image, 2, 0.0f, 0.0f, 1.0f, 1.0f);
			TheTransitionHandler->reverse(AsciiString("FadeInGameMovie"));
			TheTransitionHandler->rva001DC5EC();
			int beginTime = timeGetTime();
			while (beginTime + 5000 > timeGetTime())
			{
				TheGameEngine->serviceWindowsOS();
				TheWindowManager->update();
				TheDisplay->vslot12();
				Sleep(100);
			}
			setFPMode();
			TheDisplay->m_byte114 = true;
			TheTransitionHandler->reset();
			if (TheWritableGlobalData->m_shellMapOn)
			{
				((W3DDisplay *)TheDisplay)->rva0025D2F6();
				TheDisplay->rva0025C776((int)image, 0.0f, 0.0f, 1.0f, 1.0f, 10, 0x2d);
			}
			else
			{
				TheTransitionHandler->setGroup(AsciiString("FadeInGameMovie"), false);
				TheTransitionHandler->rva001DC5EC();
				((W3DDisplay *)TheDisplay)->rva0025D2F6();
			}
		}
		TheWritableGlobalData->m_byteD36 = false;
	}
	else
		result = 6;
	return result;
}

// Callback 4 (0x00239122): the tail of ZH GameClient::update's intro
// handling. A pending intro is dropped; once no movie plays the shell comes
// up (0x0035C194 and 0x0035C7CF where ZH shows the shell map and the shell,
// skipped when an initial file is set) and m_afterIntro is cleared.
int rva00239122(void *, bool allowIntro)
{
	int result = 5;
	TheGameEngine->serviceWindowsOS();
	if (allowIntro && TheWritableGlobalData->m_playIntro)
	{
		TheWritableGlobalData->m_playIntro = false;
	}
	else if (!TheDisplay->isMoviePlaying())
	{
		result = 7;
		if (((const StringBase<char> *)&TheWritableGlobalData->m_initialFile)->isEmpty())
		{
			TheShell->showShellMap(true, false);
			TheShell->showShell(true);
		}
		TheShell->m_byte6C = 1;
		TheWritableGlobalData->m_afterIntro = false;
	}
	return result;
}

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

#include "../../Include/Common/OptionPreferences.h"


// Callback 2 (0x0023BDD7): BFME 2's logo movies in place of ZH's EALogoMovie.
// Three movies play through display slot 67 (+0x10C, where ZH has
// playLogoMovie), the HasSeenLogoMovies option is written and m_afterIntro
// set.
int rva0023BDD7(void *, bool allowIntro)
{
	int result = 5;
	TheGameEngine->serviceWindowsOS();
	if (allowIntro)
	{
		if (TheWritableGlobalData->m_playIntro)
		{
			OptionPreferences prefs;
			TheDisplay->vf67(AsciiString("NewLineLogo"), 0, 8);
			TheDisplay->vf67(AsciiString("TolkienLogo"), 0, 8);
			TheDisplay->vf67(AsciiString("Overall_Game_Intro"), 1, 0x30);
			prefs[AsciiString("HasSeenLogoMovies")] = "yes";
			prefs.write();
		}
		TheWritableGlobalData->m_afterIntro = true;
	}
	else
		result = 7;
	return result;
}

// ?update@Rva004C743@@UAEXXZ @0x0004C755 and ?reset@Rva004C743@@UAEXXZ
// @0x0004C75A, 5B each: slots 10 and 9 of the device game client's vtable
// (??_7Rva004C743, the W3DGameClient of W3DGameClientFactories.cpp). Both
// only extend GameClient: tail jumps to update and reset above.
class Rva004C743 : public GameClient
{
public:
	virtual void reset();
	virtual void update();
};

void Rva004C743::update()
{
	GameClient::update();
}

void Rva004C743::reset()
{
	GameClient::reset();
}
