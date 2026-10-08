// ?xfer@GameClient@@MAEXPAVXfer@@@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
//
// GameClient's drawable table of contents, after ZH GameClient.cpp
// (findTOCEntryByName, findTOCEntryById, shouldSaveDrawable,
// xferDrawableTOC). GameLogic::xferObjectTOC (GameLogicInit.cpp, 0x00245F79)
// is the same code over the object list.
//
// Target evidence: the TOC list sits at GameClient+0xF4 (both finds and the
// xfer read it there); the xfer walks the drawable list from vslot 35
// (ZH's virtual getDrawableList), next drawable at +0x104, thing template at
// +4 and its name at +0x64; shouldSaveDrawable reads the status bits at
// +0x114 and the object at +0xFC. Callers: GameClient::xfer at 0x0023B5D5
// (name) and 0x0023B68C (id).

#include <list>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
#include "../Common/GameLogicObjectLookupView.h"

class Xfer;
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
class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void beginBlock(const char *name) = 0;
	virtual void endBlock() = 0;
	virtual void skip(const char *name) = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

// The override chain head of a thing template (ZH's Overridable): the
// getter at 0x001E35DF follows the next override at +4.
class Rva001E35DFView
{
public:
	const Rva001E35DFView *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Rva001E35DFView *m_nextOverride; // +0x04
	bool m_isOverride;
};

class ThingTemplate : public Rva001E35DFView
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad00C[0x64 - 0x0C];
	AsciiString m_name; // +0x64
};

class Thing
{
public:
	virtual ~Thing();

	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const; // 0x005508E2

private:
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0x60 - 0x08];
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }

private:
	char m_pad060[0x74 - 0x60];
	ObjectID m_id; // +0x74
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

// The drawable's snapshot sits at +0x60, after the thing.
class Drawable : public Thing, public Snapshot
{
public:
	const Object *getObject() const { return m_object; }
	Drawable *getNextDrawable() const { return m_nextDrawable; }
	bool testDrawableStatus(DrawableStatus bit) const { return (m_status & bit) != 0; }

private:
	char m_pad064[0xFC - 0x64];
	Object *m_object; // +0xFC
	char m_pad100[0x104 - 0x100];
	Drawable *m_nextDrawable; // +0x104
	char m_pad108[0x114 - 0x108];
	unsigned int m_status; // +0x114
};

// The thing factory's findTemplate (0x002D06CA) and newDrawable
// (0x002CF21B), still rowed under their address-named classes.
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

class Rva002CF21B
{
public:
	void *rva002CF21B(void *tmplate, int status, int random);
};

extern Rva002D06CA *TheThingFactory;
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

class Dict
{
public:
	float getReal(int key, bool *exists) const;
	void setReal(int key, float value);

private:
	struct DictPairData;
	DictPairData *m_data;
};

extern Dict g_Va00E00944;
extern Rva00148F5ECache g_00DBDEEC;

// The audio events the client keeps playing across a save. Each is a
// 0xD0-byte reference-counted event (vftable 0x0083CB1C) built from the
// looked-up event info or empty.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

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

	void rva000A8CE5(OpaqueRefCounted *ptr);
	operator const Rva0023AD91Record &() const { return *reinterpret_cast<const Rva0023AD91Record *>(this); }

	OpaqueRefCounted *m_ptr;
};

class Rva001DA2D5;

class Rva00433390
{
public:
	Rva00433390(int val);

private:
	char m_data[0xD0];
};

class Rva004333C0
{
public:
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
struct Rva000B56F0Object
{
	unsigned char m_prefix[8];
	unsigned char m_inlineStorage[0xBC];
	unsigned int m_flags;
	unsigned char m_externalStorage[1];

	void *selectStorage();
	void rva004331C6(Xfer *xfer);
};

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
	Rva0036CA00Str(const Rva0036CA00Str &);
	~Rva0036CA00Str();
	Rva0036CA00Str &operator=(const Rva0036CA00Str &);

private:
	void *m_data;
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

namespace _STL
{
template<> void vector<Rva0036CA00Str, allocator<Rva0036CA00Str> >::reserve(size_t n);
template<> void vector<Rva0023AD91Record, allocator<Rva0023AD91Record> >::push_back(const Rva0023AD91Record &x);
template<> void vector<const ModuleData *, allocator<const ModuleData *> >::reserve(size_t n);
template<> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &x);
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

class Rva0023ABDD
{
public:
	void rva0023ABDD();
};

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

// Retail 0x00239C5E, 89 bytes.
GameClient::DrawableTOCEntry *GameClient::findTOCEntryByName(AsciiString name)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).name == name)
			return &(*it);

	return 0;
}

// Retail 0x002399EB, 37 bytes.
GameClient::DrawableTOCEntry *GameClient::findTOCEntryById(unsigned short id)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).id == id)
			return &(*it);

	return 0;
}

// Retail 0x00238F79, 24 bytes; as a file static cl passes the drawable in EAX.
// Retail calls it from GameClient::xfer too (not in this unit yet), so it is
// kept out of line here.
static __declspec(noinline) bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(DRAWABLE_STATUS_NO_SAVE))
	{
		if (draw->getObject() == 0)
			return false;
	}
	return true;
}

// Retail 0x0023AC36, 347 bytes. As GameLogic::xferObjectTOC, BFME 2 opens
// with Xfer::Version1 instead of xferVersion.
void GameClient::xferDrawableTOC(Xfer *xfer)
{
	xfer->Version1();
	((Rva00239D49List *)&m_drawableTOC)->clear();

	unsigned int tocCount = 0;
	if (xfer->IsStoring())
	{
		AsciiString templateName;
		for (Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable())
		{
			if (!shouldSaveDrawable(draw))
				continue;

			templateName = draw->getTemplate()->getName();
			if (findTOCEntryByName(templateName) != 0)
				continue;

			((Rva0023AB78 *)this)->rva0023AB78(draw->getTemplate()->getName(), ++tocCount);
		}
		*xfer == tocCount;
		for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		{
			DrawableTOCEntry *tocEntry = &(*it);
			*xfer == tocEntry->name;
			*xfer == tocEntry->id;
		}
	}
	else
	{
		AsciiString templateName;
		unsigned short id;
		*xfer == tocCount;
		for (unsigned int i = 0; i < tocCount; ++i)
		{
			*xfer == templateName;
			*xfer == id;
			((Rva0023AB78 *)this)->rva0023AB78(templateName, id);
		}
	}
}

// Retail 0x0023B509, 1806 bytes: the client's snapshot, after ZH
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

			tocEntry = findTOCEntryByName(draw->getTemplate()->getName());
			if (tocEntry == 0)
				throw XferException(5, 0);

			*xfer == tocEntry->id;
			xfer->beginBlock("Drawable");
			objectID = draw->getObject() ? draw->getObject()->getID() : INVALID_OBJECT_ID;
			XferObjectID(xfer, &objectID);
			*xfer == *static_cast<Snapshot *>(draw);
			xfer->endBlock();
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

			thingTemplate = (const ThingTemplate *)TheThingFactory->rva002D06CA(&tocEntry->name);
			if (thingTemplate == 0)
			{
				xfer->skip("Drawable");
				continue;
			}

			xfer->beginBlock("Drawable");
			XferObjectID(xfer, &objectID);
			if (objectID != INVALID_OBJECT_ID)
			{
				Object *object = TheGameLogic->findObjectByID(objectID);
				if (object == 0)
					throw XferException(5, 0);

				draw = object->getDrawable();
				if (draw == 0)
					throw XferException(5, 0);

				const ThingTemplate *drawTemplate = draw->getTemplate();
				if (drawTemplate->getFinalOverride() != thingTemplate->getFinalOverride())
				{
					TheGameClient->destroyDrawable(draw);
					draw = (Drawable *)((Rva002CF21B *)TheThingFactory)->rva002CF21B((void *)thingTemplate, 0, -1);
					TheGameLogic->bindObjectAndDrawable(object, draw);
				}
			}
			else
			{
				draw = (Drawable *)((Rva002CF21B *)TheThingFactory)->rva002CF21B((void *)thingTemplate, 0, -1);
				if (draw == 0)
					throw XferException(5, 0);
			}

			*xfer == *static_cast<Snapshot *>(draw);
			xfer->endBlock();
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
			float value = g_Va00E00944.getReal(g_00DBDEEC.get(), &exists);
			*xfer == exists;
			*xfer == value;
			if (exists && xfer->IsLoading())
			{
				NameKeyType key = g_00DBDEEC.get();
				g_Va00E00944.setReal(key, value);
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
				event.rva000A8CE5(info.m_info == 0
					? (OpaqueRefCounted *)new Rva00433390(0)
					: (OpaqueRefCounted *)new Rva004333C0(*(const Rva001DA2D5 *)info.m_info, 0));
				AsciiString name;
				*xfer == name;
				OpaqueRefCounted *p = event.m_ptr;
				((Rva004EC166 *)p)->rva00433403(name);
				((Rva000B56F0Object *)p)->rva004331C6(xfer);
				TheAudio->vslot74(p);
				((Rva0023AD91Vector *)&m_audioEvents)->push_back(event);
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
				((Rva000B56F0Object *)m_audioEvents[i].m_ptr)->rva004331C6(xfer);
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
