// cl: /I. /ICode/GameEngine/Source/GameClient /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// platformsdk
// stlport
//
// GameClient::xfer (0x0023B509, 1806 bytes, ret 4), after ZH GameClient.cpp
// GameClient::xfer: version, frame, drawable TOC, the drawables, briefing
// lines, then BFME 2's map dictionary real, object id, Eva, the scored-kill
// announcer, a name and two flags, and the playing audio events and handles.
// Split out of the GameClient unit (GameClientDrawableTOC.cpp, which rows
// findTOCEntryByName/ById, xferDrawableTOC and shouldSaveDrawable); retail
// calls shouldSaveDrawable with the drawable in EAX, so the file static is
// repeated here.
//
// Target evidence: the TOC list at GameClient+0xF4; the drawable list from
// vslot 35, next drawable at +0x104, template at +4, name at +0x64; the
// audio vectors at +0x12C (events) and +0x120 (handles) as the Snapshot side
// (this+0xC) addresses them; the event holder's setter 0x000A8CE5, clear
// 0x000A8C9B, copy constructor 0x000A8C7C and push_back 0x0023AD91.
// Retail keeps the new event's pointer in EBX through push_back and the name
// destructor to the event's inlined destructor: cl only does that when the
// setter, clear and copy constructor bodies are visible in the unit, so they
// are defined here out of line (byte-identical to their retail bodies).

#include <list>

// Keep typed list comparisons local, as in PlayerTemplate.cpp. STLport's
// base comparison tests the same node pointers but emits a conflicting COMDAT.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L> &a,
                              const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
// Expanded inline in the overflow insert, as in retail 0x0023A076; no out-of-line copy.
namespace _STL { template <> __declspec(dllimport) __forceinline const unsigned int &(max)(const unsigned int &__a, const unsigned int &__b) { return __a < __b ? __b : __a; } }

class Xfer;
class DynamicAudioEventInfo {public:void xferNoName(Xfer*);};
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

// BFME 2's Xfer (as GameLogicInit.cpp): MSVC lays the operator== overloads
// out in reverse, so AsciiString is slot 27, unsigned int 30, unsigned
// short 32.
class Snapshot;
class AsciiString;
class UnicodeString;
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

#include "../../Include/Common/XferException.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);


#include "../../Include/Common/ThingTemplate.h"

#include "../Common/Thing/thing.h"

#include "../GameLogic/Object/object.h"

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

// The drawable's snapshot sits at +0x60, after the thing.
#include "../../Include/GameClient/Drawable.h"

// The thing factory's findTemplate (0x002D06CA) and newDrawable
// (0x002CF21B), still rowed under their address-named classes.
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &key); void *newDrawable(void *, int, int); };

class Rva002CF21B
{
public:
	void *rva002CF21B(void *tmplate, int status, int random);
};

extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	bool m_flag;
	AsciiString m_name;
};

// Both snapshots sit after the 0xC-byte subsystem.
class Eva : public SubsystemInterface, public Snapshot
{
};

class Rva0022C22CSubsystem : public SubsystemInterface, public Snapshot
{
};

extern Eva *TheEva;
extern Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController;

// The in-game briefing list (ZH's GetBriefingTextList and
// UpdateDiplomacyBriefingText), BFME 2's lines being Unicode.
int Rva00433B18Get();
void Rva00433C75(const AsciiString &text, bool clear);
void Rva00433C18(const UnicodeString &text, bool clear);

// The map dictionary at VA 0x00E00944 and the cached key at VA 0x00DBDEEC
// (Rva00BCF670CameraSettings.cpp).
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();

	NameKeyType m_key;
	const char *m_name;
};

#include "../../Include/Common/Dict.h"

class MapObject { public: static Dict TheWorldDict; };
extern Rva00148F5ECache g_00DBDEEC;

// The audio events the client keeps playing across a save. Each is a
// 0xD0-byte reference-counted event (vftable 0x0083CB1C) built from the
// looked-up event info or empty.
#include <windows.h>

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

class AudioEventInfoRef
{
public:
	~AudioEventInfoRef()
	{
		if (m_info)
			m_info->Release_Ref();
	}

	OpaqueRefCounted *m_info;
};

struct Rva0023AD91Record;

class Rva000A8C9B
{
public:
	Rva000A8C9B() : m_ptr(0) {}
	~Rva000A8C9B()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	// 0x000A8C9B and 0x000A8CE5, out of line but visible here, as in retail:
	// cl then proves the event's address does not escape the loop body.
	__declspec(noinline) void clear()
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
	}
	__declspec(noinline) void rva000A8CE5(OpaqueRefCounted *value)
	{
		if (value != m_ptr)
		{
			clear();
			m_ptr = value;
			if (value)
				InterlockedIncrement(&value->m_04);
		}
	}
	operator const Rva0023AD91Record &() const { return *reinterpret_cast<const Rva0023AD91Record *>(this); }

	OpaqueRefCounted *m_ptr;
};

class Rva001DA2D5;

class Rva004333C0
{
public:
	Rva004333C0(int val);
	Rva004333C0(const Rva001DA2D5 &src, int val);

private:
	char m_data[0xD0];
};

class Rva004EC166
{
public:
	void rva00433403(const AsciiString &name);
};

// The event's name storage and its own xfer (unrowed 0x004331C6).
#include "../../Include/Common/Rva000B56F0Object.h"


#define V(n) virtual void pad##n();
class AudioManager
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73)
	virtual void vslot74(OpaqueRefCounted *event);
	virtual AudioEventInfoRef findAudioEvent(const AsciiString &name);
	V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	virtual void vslot88(Xfer *xfer, unsigned int *handle);
};
#undef V

extern AudioManager *TheAudio;

// The vector bodies the client's two audio vectors fold to, rowed under
// other element types.
class ModuleData;

class Rva0036CA00Str
{
public:
	Rva0036CA00Str();
	// 0x000A8C7C, out of line but visible here (see Rva000A8C9B).
	__declspec(noinline) Rva0036CA00Str(const Rva0036CA00Str &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			InterlockedIncrement(&m_ptr->m_04);
	}
	~Rva0036CA00Str();
	Rva0036CA00Str &operator=(const Rva0036CA00Str &);

private:
	OpaqueRefCounted *m_ptr;
};

// The audio event vector's element, sharing the reference's copy
// constructor (0x0023AD91 push_back -> 0x002393AA _Construct -> 0x000A8C7C).
struct Rva0023AD91Record : Rva0036CA00Str
{
};

namespace _STL
{
template<> void vector<Rva0036CA00Str, allocator<Rva0036CA00Str> >::reserve(size_t n);
template<> void vector<const ModuleData *, allocator<const ModuleData *> >::reserve(size_t n);
template<> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &x);
// Retail's 18-byte frameless nothrow placement copy 0x002393AA, spelled as
// GameClientDrawableTOC.cpp spells it.
template <> __declspec(noinline) inline void _Construct<Rva0023AD91Record, Rva0023AD91Record>(Rva0023AD91Record *__p, const Rva0023AD91Record &__val) throw()
{
	new (__p) Rva0023AD91Record(__val);
}
// STLport's overflow insert as retail's 0x0023A076 compiles it: no unwind
// block, as StlVectorRva0023AD91.cpp emits it.
template <> inline void vector<Rva0023AD91Record, allocator<Rva0023AD91Record> >::_M_insert_overflow(
	Rva0023AD91Record *__position, const Rva0023AD91Record &__x, const __false_type &, size_t __fill_len, bool __atend)
{
	const size_type __old_size = size();
	const size_type __len = __old_size + (max)(__old_size, __fill_len);
	pointer __new_start = this->_M_end_of_storage.allocate(__len);
	pointer __new_finish = __new_start;
	__new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
	if (__fill_len == 1) {
		_Construct(__new_finish, __x);
		++__new_finish;
	} else
		__new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
	if (!__atend)
		__new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
	_M_clear();
	_M_set(__new_start, __new_finish, __new_start + __len);
}
}

typedef _STL::vector<Rva0036CA00Str> Rva00239ED8Vector;
typedef _STL::vector<Rva0023AD91Record> Rva0023AD91Vector;
typedef _STL::vector<const ModuleData *> ModuleDataVector;

// The TOC list's clear is the body every {AsciiString, short} list folds to
// (0x00239D49); the ledger names it after this placeholder element.
struct Rva00239D49Element
{
	AsciiString name;
	unsigned short id;
};
typedef _STL::list<Rva00239D49Element> Rva00239D49List;

namespace _STL
{
template<> void _List_base<Rva00239D49Element, allocator<Rva00239D49Element> >::clear();
}

// addTOCEntry (0x0023AB78) and the audio vectors' clear (0x0023ABDD) are
// still rowed under their address-named classes.
class Rva0023AB78
{
public:
	void rva0023AB78(AsciiString s, unsigned short v);
};

#include "../../Include/Common/Rva0023ABDD.h"

class GameClient : public SubsystemInterface, public Snapshot
{
public:
	struct DrawableTOCEntry
	{
		AsciiString name;
		unsigned short id;
	};
	typedef _STL::list<DrawableTOCEntry> DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

	virtual ~GameClient();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void destroyDrawable(Drawable *draw); // vslot 29
	virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34();
	virtual Drawable *getDrawableList(); // vslot 35

	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	DrawableTOCEntry *findTOCEntryById(unsigned short id);
	void xferDrawableTOC(Xfer *xfer);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_frame; // +0x10
	char m_pad014[0xB8 - 0x14];
	ObjectID m_B8; // +0xB8
	AsciiString m_BC; // +0xBC
	bool m_C0; // +0xC0
	bool m_C1; // +0xC1
	char m_pad0C2[0xF4 - 0xC2];
	DrawableTOCList m_drawableTOC; // +0xF4
	char m_pad0F8[0x120 - 0xF8];
	_STL::vector<unsigned int> m_audioHandles; // +0x120
	_STL::vector<Rva000A8C9B> m_audioEvents; // +0x12C
	int m_138; // +0x138
};

extern GameClient *TheGameClient;

// Retail 0x00238F79, 24 bytes; as a file static cl passes the drawable in EAX.
// Repeated from GameClientDrawableTOC.cpp for GameClient::xfer's two calls.
static __declspec(noinline) bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(DRAWABLE_STATUS_NO_SAVE))
	{
		if (draw->getObject() == 0)
			return false;
	}
	return true;
}

// GameClient::xfer (version 4 here). Past ZH's drawables and briefing
// lines it keeps a map dictionary real, an object id, Eva and (version 4)
// the scored-kill announcer, a name and two flags, and from version 3 the
// playing audio events and handles.
void GameClient::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 4);
	*xfer == version;

	*xfer == m_frame;

	xferDrawableTOC(xfer);

	Drawable *draw;
	unsigned short drawableCount = 0;
	for (draw = getDrawableList(); draw; draw = draw->getNextDrawable())
	{
		if (xfer->IsStoring() && !shouldSaveDrawable(draw))
			continue;
		drawableCount++;
	}
	*xfer == drawableCount;

	DrawableTOCEntry *tocEntry;
	ObjectID objectID;
	if (xfer->IsStoring())
	{
		for (draw = getDrawableList(); draw; draw = draw->getNextDrawable())
		{
			if (!shouldSaveDrawable(draw))
				continue;

			tocEntry = findTOCEntryByName(draw->m_template->getName());
			if (tocEntry == 0)
				throw XferException(5, 0);

			*xfer == tocEntry->id;
			xfer->BeginBlock("Drawable");
			objectID = draw->getObject() ? draw->getObject()->getID() : INVALID_OBJECT_ID;
			XferObjectID(xfer, &objectID);
			*xfer == *static_cast<Snapshot *>(draw);
			xfer->EndBlock();
		}
	}
	else
	{
		unsigned short tocID;
		const ThingTemplate *thingTemplate;
		for (unsigned short i = 0; i < drawableCount; ++i)
		{
			*xfer == tocID;
			tocEntry = findTOCEntryById(tocID);
			if (tocEntry == 0)
				throw XferException(5, 0);

			thingTemplate = (const ThingTemplate *)TheThingFactory->findTemplate(tocEntry->name);
			if (thingTemplate == 0)
			{
				xfer->SkipBlock("Drawable");
				continue;
			}

			xfer->BeginBlock("Drawable");
			XferObjectID(xfer, &objectID);
			if (objectID != INVALID_OBJECT_ID)
			{
				Object *object = TheGameLogic->findObjectByID(objectID);
				if (object == 0)
					throw XferException(5, 0);

				draw = object->getDrawable();
				if (draw == 0)
					throw XferException(5, 0);

				const ThingTemplate *drawTemplate = draw->m_template;
				if (drawTemplate->getFinalOverride() != thingTemplate->getFinalOverride())
				{
					TheGameClient->destroyDrawable(draw);
					draw = (Drawable *)TheThingFactory->newDrawable((void *)thingTemplate, 0, -1);
					TheGameLogic->bindObjectAndDrawable(object, draw);
				}
			}
			else
			{
				draw = (Drawable *)TheThingFactory->newDrawable((void *)thingTemplate, 0, -1);
				if (draw == 0)
					throw XferException(5, 0);
			}

			*xfer == *static_cast<Snapshot *>(draw);
			xfer->EndBlock();
		}
	}

	if (!xfer->IsCRC())
	{
		if (xfer->IsStoring())
		{
			_STL::list<UnicodeString> *bList = (_STL::list<UnicodeString> *)Rva00433B18Get();
			int numEntries = bList->size();
			*xfer == numEntries;
			for (_STL::list<UnicodeString>::const_iterator bIt = bList->begin(); bIt != bList->end(); ++bIt)
			{
				UnicodeString tempStr = *bIt;
				*xfer == tempStr;
			}
		}
		else
		{
			int numEntries = 0;
			*xfer == numEntries;
			Rva00433C75(AsciiString::TheEmptyString, true);
			while (numEntries-- > 0)
			{
				UnicodeString tempStr;
				*xfer == tempStr;
				Rva00433C18(tempStr, false);
			}
		}

		if (version.m_minimum > 1)
		{
			bool exists;
			float value = MapObject::TheWorldDict.getReal(g_00DBDEEC.get(), &exists);
			*xfer == exists;
			*xfer == value;
			if (exists && xfer->IsLoading())
			{
				NameKeyType key = g_00DBDEEC.get();
				MapObject::TheWorldDict.setReal(key, value);
			}
		}
	}

	XferObjectID(xfer, &m_B8);
	*xfer == *static_cast<Snapshot *>(TheEva);
	if (version.m_minimum >= 4)
		*xfer == *static_cast<Snapshot *>(TheScoredKillEvaAnnouncerController);
	*xfer == m_BC;
	*xfer == m_C0;
	*xfer == m_C1;

	if (version.m_minimum >= 3)
	{
		*xfer == m_138;
		if (xfer->IsLoading())
		{
			((Rva0023ABDD *)this)->rva0023ABDD();

			int count;
			*xfer == count;
			((Rva00239ED8Vector *)&m_audioEvents)->reserve(count);
			for (int i = 0; i < count; ++i)
			{
				AsciiString eventName;
				*xfer == eventName;
				AudioEventInfoRef info = TheAudio->findAudioEvent(eventName);
				Rva000A8C9B event;
				if (info.m_info == 0)
					event.rva000A8CE5((OpaqueRefCounted *)new Rva004333C0(0));
				else
					event.rva000A8CE5((OpaqueRefCounted *)new Rva004333C0(*(const Rva001DA2D5 *)info.m_info, 0));
				{
				AsciiString name;
				*xfer == name;
				((Rva004EC166 *)event.m_ptr)->rva00433403(name);
				((DynamicAudioEventInfo *)event.m_ptr)->xferNoName(xfer);
				TheAudio->vslot74(event.m_ptr);
				((Rva0023AD91Vector *)&m_audioEvents)->push_back(event);
				}
			}

			*xfer == count;
			((ModuleDataVector *)&m_audioHandles)->reserve(count);
			for (int j = 0; j < count; ++j)
			{
				unsigned int handle = 1;
				TheAudio->vslot88(xfer, &handle);
				((ModuleDataVector *)&m_audioHandles)->push_back(*(const ModuleData **)&handle);
			}
		}
		else
		{
			int count = m_audioEvents.size();
			*xfer == count;
			for (int i = 0; i < count; ++i)
			{
				AsciiString eventName = *(AsciiString *)((Rva000B56F0Object *)m_audioEvents[i].m_ptr)->selectStorage();
				*xfer == eventName;
				AsciiString name = *(AsciiString *)((char *)m_audioEvents[i].m_ptr + 8);
				*xfer == name;
				DynamicAudioEventInfo *info = (DynamicAudioEventInfo *)m_audioEvents[i].m_ptr;
				info->xferNoName(xfer);
			}

			count = m_audioHandles.size();
			*xfer == count;
			for (int j = 0; j < count; ++j)
			{
				unsigned int handle = m_audioHandles[j];
				TheAudio->vslot88(xfer, &handle);
			}
		}
	}
	else
	{
		((Rva0023ABDD *)this)->rva0023ABDD();
		m_138 = 0;
	}
}
