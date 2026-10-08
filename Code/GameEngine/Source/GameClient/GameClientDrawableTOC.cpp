// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
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
#include <list>
#include <vector>
#include "ascii_string.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "GUI/HeaderTemplateView.h"

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

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

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

class ThingTemplate
{
public:
	const AsciiString &getName(void) const { return m_name; }

private:
	char m_pad00[0x64];
	AsciiString m_name;
};

class Object;

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

private:
	void *m_vtbl;
	const ThingTemplate *m_template;                                     // +0x04
	char m_pad08[0xfc - 0x08];
	Object *m_object;                                                    // +0xFC
	char m_pad100[0x104 - 0x100];
	Drawable *m_nextDrawable;                                            // +0x104
	char m_pad108[0x114 - 0x108];
	unsigned int m_status;                                               // +0x114
};

// ZH GameClient.h DrawablePtrHash: 0x14 bytes at +0x18 torn down by the
// out-of-line hashtable destructor 0x00239CC9; key and value types unproven.
class Rva00239CC9DrawableHash
{
public:
	~Rva00239CC9DrawableHash();

private:
	unsigned char m_pad[0x14];
};

// Drawable lists whose nodes come from the pool freelist 0x009BA5E8:
// 0x00239AF4 clears one and frees its sentinel, and never throws (retail
// stores no unwind state around it). The ten at +0xF8 are destroyed through
// the out-of-line copy of this destructor, 0x00239BAB.
class Rva00239AF4
{
public:
	void rva00239AF4() throw();
	~Rva00239AF4() { rva00239AF4(); }

private:
	void *m_head;
};

class Rva00362862Item;
class Rva00239E25
{
public:
	~Rva00239E25();

private:
	unsigned char m_pad[0x0C];
};

// Owning pointer at +0x13C: clear 0x0023A039 nulls the slot and deletes the
// pointee.
class Rva0023A039
{
public:
	void clear();
	~Rva0023A039() { clear(); }

private:
	void *m_ptr;
};

// BFME 2 SubsystemInterface: nine vtable slots; init sits in slot 1 (+4) and
// postProcessLoad in slot 3 (+0xC) for every subsystem GameClient::init
// creates, and setName is the out-of-line 0x0006F3CC.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();
	virtual void vf07();
	virtual void vf08();

	void setName(AsciiString name);

private:
	unsigned char m_bfmeBasePad[8];
};

typedef unsigned int TranslatorID;
class CommandTranslator;
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

	virtual ~GameClient();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void vf09();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void vf22();
	virtual void vf23();
	virtual void vf24();
	virtual void vf25();
	virtual void vf26();
	virtual void vf27();
	virtual void vf28();
	virtual void destroyDrawable(Drawable *draw);                       // slot 29 (+0x74)
	virtual void vf30();
	virtual void vf31();
	virtual void vf32();
	virtual void vf33();
	virtual void vf34();
	virtual Drawable *getDrawableList(void);                            // slot 35 (+0x8C)
	virtual void vf36();
	// Factories, slots 37-50, named after the global init stores each in.
	virtual Display *createGameDisplay();                               // +0x94
	virtual InGameUI *createInGameUI();                                 // +0x98
	virtual GameWindowManager *createWindowManager();                   // +0x9C
	virtual FontLibrary *createFontLibrary();                           // +0xA0
	virtual DisplayStringManager *createDisplayStringManager();         // +0xA4
	virtual VideoPlayerInterface *createVideoPlayer();                  // +0xA8
	virtual G00DFF080Obj *createTerrainVisual();                        // +0xAC
	virtual Keyboard *createKeyboard();                                 // +0xB0
	virtual Mouse *createMouse();                                       // +0xB4
	virtual SnowManager *createSnowManager();                           // +0xB8
	virtual Rva0027070CGlobal *createCloudEffectManager();              // +0xBC
	virtual CloudBreakEffectManager *createCloudBreakEffectManager();   // +0xC0
	virtual FireManager *createFireManager();                           // +0xC4
	virtual Rva002D3627Host *vf50();                                    // +0xC8
	virtual void setFrameRate(float rate);                              // +0xCC

	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	DrawableTOCEntry *findTOCEntryById(unsigned short id);
	void addTOCEntry(AsciiString name, unsigned short id);
	void xferDrawableTOC(Xfer *xfer);
	void rva0023ABDD();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:
	enum { MAX_CLIENT_TRANSLATORS = 32 };

	unsigned int m_frame;                                               // +0x10
	Drawable *m_drawableList;                                           // +0x14
	Rva00239CC9DrawableHash m_drawableHash;                             // +0x18
	unsigned int m_nextDrawableID;                                      // +0x2C
	TranslatorID m_translators[MAX_CLIENT_TRANSLATORS];                 // +0x30
	unsigned int m_numTranslators;                                      // +0xB0
	CommandTranslator *m_commandTranslator;                             // +0xB4
	unsigned char m_padB8[0xbc - 0xb8];
	AsciiString m_stringBC;                                             // +0xBC
	unsigned char m_padC0[0xe4 - 0xc0];
	Rva00239AF4 m_drawableListE4;                                       // +0xE4
	_STL::vector<Rva00362862Item *> m_vectorE8;                         // +0xE8
	DrawableTOCList m_drawableTOC;                                      // +0xF4
	Rva00239AF4 m_drawableListsF8[10];                                  // +0xF8
	_STL::vector<void *> m_vector120;                                   // +0x120
	Rva00239E25 m_vector12C;                                            // +0x12C
	unsigned char m_pad138[0x13c - 0x138];
	Rva0023A039 m_owned13C;                                             // +0x13C
};

// Retail's clear is the shared fold at 0x00239D49 and the list teardown the
// fold at 0x002FECBC; emit no copy of either here.
namespace _STL
{
template<> void _List_base<GameClient::DrawableTOCEntry, Rva0023AC36Allocator<GameClient::DrawableTOCEntry> >::clear();
template<> _List_base<GameClient::DrawableTOCEntry, Rva0023AC36Allocator<GameClient::DrawableTOCEntry> >::~_List_base();
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
	AsciiString m_fontName;
	int m_fontSize;                                                     // +0x04
	bool m_fontIsBold;                                                  // +0x08
};

// ZH GlobalLanguage FontDesc; init reads the draw-group font at +0xD4.
struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;
};

class GlobalLanguage
{
public:
	unsigned char m_pad00[0xd4];
	FontDesc m_drawGroupInfoFont;                                       // +0xD4
};

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);

private:
	unsigned char m_unported[0x87C];
};

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
class Rva00E01E28Owner : public SubsystemInterface
{
public:
	Rva00E01E28Owner();
	virtual ~Rva00E01E28Owner();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_pad[0x30 - 0x0C];
};

class InGameUI : public SubsystemInterface { public: virtual ~InGameUI(); };

class Shell : public SubsystemInterface
{
public:
	Shell();
	virtual ~Shell();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_pad[0x78 - 0x0C];
};

class IMEManager : public SubsystemInterface { public: virtual ~IMEManager(); };
class GameWindowManager : public SubsystemInterface { public: virtual ~GameWindowManager(); };

// ZH Mouse; BFME 2 keeps parseIni and initCursorResources virtual (slots 14
// and 15), and init calls slot 22 (+0x58) where ZH sets the mouse limits.
class Mouse : public SubsystemInterface
{
public:
	virtual ~Mouse();
	virtual void vf09();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void parseIni();                                            // +0x38
	virtual void initCursorResources();                                 // +0x3C
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void setMouseLimits();                                      // +0x58
};

// TheAnimationSoundModuleManager: Rva00432F23 and Rva00432FA7 (the 0x2C-byte
// ctor) are two placeholder names of the one class.
class Rva00432F23 : public SubsystemInterface { public: virtual ~Rva00432F23(); };

class Rva00432FA7 : public SubsystemInterface
{
public:
	Rva00432FA7();
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
};

// TheTerrainVisual: ZH TerrainVisual (Snapshot, SubsystemInterface), the
// subsystem side at +4.
class G00DFF080Obj : public Snapshot, public SubsystemInterface { public: virtual ~G00DFF080Obj(); };
class Display : public SubsystemInterface { public: virtual ~Display(); };
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

class ImageCollection
{
public:
	ImageCollection();
	virtual ~ImageCollection();
	void load(int textureSize);

private:
	unsigned char m_pad[0x18 - 4];
};

class Keyboard : public SubsystemInterface { public: virtual ~Keyboard(); };
class DisplayStringManager : public SubsystemInterface { public: virtual ~DisplayStringManager(); };
class SnowManager : public SubsystemInterface { public: virtual ~SnowManager(); };
class Rva0027070CGlobal : public SubsystemInterface { public: virtual ~Rva0027070CGlobal(); };
class CloudBreakEffectManager : public SubsystemInterface { public: virtual ~CloudBreakEffectManager(); };
class FireManager : public SubsystemInterface { public: virtual ~FireManager(); };

class FontLibrary
{
public:
	virtual ~FontLibrary();
	virtual void init();                                                // slot 1 (+4)
	virtual bool loadIniFilesFromLegend();                              // slot 2 (+8)
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void vf06();
	virtual void vf07();
	virtual void vf08();
	virtual void reset();                                               // slot 9 (+0x24)
};

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
class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg) = 0;
	virtual ~GameMessageTranslator() {}
};

// vftable 0x00BED684 (translate 0x0040FF12, 8 bytes): ZH's WindowTranslator
// logic with a mode word at +4 (written to the window manager at +0x3C). Its
// default ctor 0x002390F8 clears the mode. init builds one with mode 0 and one
// with mode 1 and stores the vftable immediate both times, so the two were
// distinct classes whose identical vftables the linker folded.
class Rva002390F8 : public GameMessageTranslator
{
public:
	Rva002390F8() : m_mode(0) {}
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	int m_mode;
};

class Rva002390F8Mode1 : public GameMessageTranslator
{
public:
	Rva002390F8Mode1() : m_mode(1) {}
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	int m_mode;
};

class Rva00432987 : public GameMessageTranslator
{
public:
	Rva00432987();
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
	unsigned char m_pad[0x28 - 4];
};

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

private:
	unsigned char m_pad[0x44 - 4];
};

class Rva0043216D : public GameMessageTranslator
{
public:
	Rva0043216D();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	unsigned char m_pad[0x18 - 4];
};

class Rva00431F61 : public GameMessageTranslator
{
public:
	Rva00431F61();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	unsigned char m_pad[0x0C - 4];
};

class Rva005B1A00 : public GameMessageTranslator
{
public:
	Rva005B1A00();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

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

private:
	unsigned char m_pad[0x158 - 4];
};

class Rva005A7A90 : public GameMessageTranslator
{
public:
	Rva005A7A90();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	unsigned char m_pad[0x30 - 4];
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

class MessageStream
{
public:
	TranslatorID attachTranslator(GameMessageTranslator *translator, unsigned int priority);
	GameMessageTranslator *findTranslator(TranslatorID id);
	void removeTranslator(TranslatorID id);
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

extern DrawGroupInfo *TheDrawGroupInfo;
extern RayEffectSystem *TheRayEffects;
extern Rva00E01E28Owner *g_00E01E28;                    // TheHotKeyManager
extern InGameUI *TheInGameUI;
extern Shell *TheShell;
extern IMEManager *TheIMEManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern GameWindowManager *TheWindowManager;
extern FontLibrary *TheFontLibrary;
extern Mouse *TheMouse;
extern Rva00432F23 *g_004C9DC9Container;               // TheAnimationSoundModuleManager
extern Rva002D3627Host *g_00DFEF18;
extern G00DFF080Obj *g_00DFF080;                        // TheTerrainVisual
extern Display *TheDisplay;
extern HeaderTemplateManager *TheHeaderTemplateManager;
extern LanguageFilter *TheLanguageFilter;
extern VideoPlayerInterface *TheVideoPlayer;
extern Anim2DCollection *TheAnim2DCollection;
extern ImageCollection *TheMappedImageCollection;
extern Keyboard *TheKeyboard;
extern DisplayStringManager *TheDisplayStringManager;
extern SnowManager *TheSnowManager;
extern Rva0027070CGlobal *g_00DFE1E4;                   // TheCloudEffectManager
extern CloudBreakEffectManager *TheCloudBreakEffectManager;
extern FireManager *TheFireManager;
extern MessageStream *MessageStreamSubsystem;           // TheMessageStream
extern GlobalLanguage *TheGlobalLanguageData;
extern float g_00DBA4FC;                                // client frame rate
extern void *g_00E03210;

void Rva0038072AClear();
IMEManager *CreateIMEManagerInterface();
LanguageFilter *createLanguageFilter();
void Rva00380B0CInit();
void Rva00220DCDInit();
void Rva002210CFInit();
void Rva002220DCInit();

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

	::delete g_00E01E28;
	g_00E01E28 = 0;

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

	::delete g_004C9DC9Container;
	g_004C9DC9Container = 0;

	::delete g_00DFEF18;
	g_00DFEF18 = 0;

	::delete g_00DFF080;
	g_00DFF080 = 0;

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
		MessageStreamSubsystem->removeTranslator(m_translators[i]);
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

	::delete g_00DFE1E4;
	g_00DFE1E4 = 0;

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

	g_004C9DC9Container = (Rva00432F23 *)new Rva00432FA7;
	g_004C9DC9Container->init();
	g_004C9DC9Container->setName(AsciiString("TheAnimationSoundModuleManager"));

	// register message translators
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva002390F8, 4);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva00432987, 5);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva002390F8Mode1, 10);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new MetaEventTranslator, 20);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new HotKeyTranslator, 25);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva0042CBB6, 27);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva0043216D, 30);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva00431F61, 35);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new Rva005B1A00, 40);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new SelectionTranslator, 50);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new BfmeOwnVVD, 60);
	m_translators[m_numTranslators] = MessageStreamSubsystem->attachTranslator(new Rva005A7A90, 70);
	// we keep a pointer to the command translator because it's useful
	m_commandTranslator = (CommandTranslator *)MessageStreamSubsystem->findTranslator(m_translators[m_numTranslators++]);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new HintSpyTranslator, 100);
	m_translators[m_numTranslators++] = MessageStreamSubsystem->attachTranslator(new GameClientMessageDispatcher, 999999999);

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
		TheDisplay->setName(AsciiString("TheDisplay"));
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

	g_00E01E28 = new Rva00E01E28Owner;
	if (g_00E01E28)
	{
		g_00E01E28->init();
		g_00E01E28->setName(AsciiString("TheHotKeyManager"));
	}

	// create the terrain visual
	g_00DFF080 = createTerrainVisual();
	if (g_00DFF080)
	{
		g_00DFF080->init();
		g_00DFF080->setName(AsciiString("TheTerrainVisual"));
	}

	g_00DFEF18 = vf50();
	if (g_00DFEF18)
	{
		g_00DFEF18->vf04();
		((Rva0023A053 *)&m_owned13C)->reset((Rva00239D7A *)new Rva0023A128(this, g_00DFEF18, (int)g_00E03210));
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

	g_00DFE1E4 = createCloudEffectManager();
	if (g_00DFE1E4)
	{
		g_00DFE1E4->init();
		g_00DFE1E4->setName(AsciiString("TheCloudEffectManager"));
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
	Rva00380B0CInit();
	Rva00220DCDInit();
	Rva002210CFInit();
	Rva002220DCInit();
}
