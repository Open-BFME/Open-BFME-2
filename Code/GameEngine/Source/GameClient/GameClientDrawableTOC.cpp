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
#include "../Common/GameLogicObjectLookupView.h"

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

private:
	unsigned char m_pad000[0x438];
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
	void *get() const { return m_ptr; }
	~Rva0023A039() { clear(); }

private:
	void *m_ptr;
};

// BFME 2 SubsystemInterface: eleven vtable slots; init sits in slot 1 (+4)
// and postProcessLoad in slot 3 (+0xC) for every subsystem GameClient::init
// creates, GameClient::reset calls reset in slot 9 (+0x24) and its vftable
// 0x007ED850 keeps update in slot 10. setName is the out-of-line 0x0006F3CC.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual void vf04();
	virtual void vf05();
	virtual void draw();
	virtual void vf07();
	virtual void vf08();
	virtual void reset() = 0;                                           // +0x24
	virtual void update() = 0;                                          // +0x28

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
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual Drawable *firstDrawable(void);                              // slot 17 (+0x44)
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
	void rva00239759();

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
	unsigned char m_byteC0;                                             // +0xC0
	unsigned char m_byteC1;                                             // +0xC1
	unsigned char m_padC2[0xc9 - 0xc2];
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
	_STL::vector<void *> m_vector120;                                   // +0x120
	Rva00239E25 m_vector12C;                                            // +0x12C
	int m_count138;                                                     // +0x138
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

// TheInGameUI's slot 108 (+0x1B0) refreshes the layout after a resolution
// change (AptMainMenu::ResetResolution calls it too).
class InGameUI : public SubsystemInterface
{
public:
	virtual ~InGameUI();
#define V(n) virtual void vf##n();
	V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107)
#undef V
	virtual void vf108();                                               // +0x1B0
};

class Shell : public SubsystemInterface
{
public:
	Shell();
	virtual ~Shell();
	virtual void init();
	virtual void reset();
	virtual void update();
	void push(AsciiString name, bool shutdownImmediate = false);

	// GameClient::update clears +0x6C on its first pass and still updates
	// the shell while the GameLogic byte +0x125 is set if +0x5C is.
	unsigned char m_pad0C[0x5c - 0x0C];
	bool m_byte5C;                                                      // +0x5C
	unsigned char m_pad5D[0x6c - 0x5D];
	bool m_byte6C;                                                      // +0x6C
	unsigned char m_pad6D[0x78 - 0x6D];
};

class IMEManager : public SubsystemInterface { public: virtual ~IMEManager(); };
class GameWindowManager : public SubsystemInterface { public: virtual ~GameWindowManager(); };

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
	unsigned char m_pad38[0xaf2 - 0x38];
	bool m_playIntro;                                                   // +0xAF2
	bool m_afterIntro;                                                  // +0xAF3
	unsigned char m_padAF4[0xc78 - 0xaf4];
	int m_stallMilliseconds;                                            // +0xC78
};

// ZH Mouse; BFME 2 keeps parseIni and initCursorResources virtual (slots 14
// and 15), and init calls slot 22 (+0x58) where ZH sets the mouse limits.
// update calls slot 16 (+0x40) right after the mouse update, as ZH calls
// createStreamMessages.
class Mouse : public SubsystemInterface
{
public:
	virtual ~Mouse();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
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
// ZH Display's mode accessors, three slots later than ZH's.
// GameClient::update redraws through slot 12 (+0x30) where ZH calls draw.
class Display : public SubsystemInterface
{
public:
	virtual ~Display();
	virtual void vf11();
	virtual void drawViews();                                           // +0x30
	virtual void vf13();
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

class ImageCollection
{
public:
	ImageCollection();
	virtual ~ImageCollection();
	void load(int textureSize);

private:
	unsigned char m_pad[0x18 - 4];
};

// ZH Keyboard::createStreamMessages follows the update, here slot 15 (+0x3C).
class Keyboard : public SubsystemInterface
{
public:
	virtual ~Keyboard();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void createStreamMessages();                                // +0x3C
};
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
	void rva0042D068();

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
	void rva0042F213();

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

// Views GameClient::update calls through. TheTacticalView's slots 54 (+0xD8)
// and 30 (+0x78) stand where ZH asks isTimeFrozen and
// isCameraMovementFinished; the two script-engine freeze tests and the
// frame-period check are matched rows under placeholder names.
class View
{
public:
	virtual ~View();
#define V(n) virtual void vf##n();
	V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10)
	V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20)
	V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	virtual bool isCameraMovementFinished();                            // +0x78
	V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40)
	V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50)
	V(51) V(52) V(53)
#undef V
	virtual bool isTimeFrozen();                                        // +0xD8
};

class ScriptEngine;
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00203ACEByteField { public: unsigned char get() const; };

// ZH PlayerList::getLocalPlayer and Player::getPlayerIndex: the local
// player at +0x10, its index at +0x54.
class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad[0x54];
	int m_playerIndex;                                                  // +0x54
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }

private:
	unsigned char m_pad[0x10];
	Player *m_local;                                                    // +0x10
};

class GameEngine
{
private:
	bool rva00225D38();
	friend class GameClient;
};

// ZH GhostObjectManager::updateOrphanedObjects, slot 6 (+0x18).
class GhostObjectManager
{
public:
	virtual ~GhostObjectManager();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void updateOrphanedObjects(int *playerIndexList, int playerIndexCount); // +0x18
};

// ZH ParticleSystemManager::setLocalPlayerIndex stores +0x64.
class ParticleSystemManager
{
public:
	void setLocalPlayerIndex(int index) { m_localPlayerIndex = index; }

private:
	unsigned char m_pad[0x64];
	int m_localPlayerIndex;                                             // +0x64
};

class Eva : public SubsystemInterface { public: virtual ~Eva(); };
// TheScoredKillEvaAnnouncerController, under the placeholder class
// GameEngine::init creates it with.
class Rva0022C22CSubsystem : public SubsystemInterface { public: virtual ~Rva0022C22CSubsystem(); };

class Rva005D124D { public: int rva005D124D(); };
class Rva00239105 { public: void rva00239105(); };
class Rva00239300 { public: void rva00239300(int frame, int periodFrame); };
class Rva0004378D { public: void first(); };

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
extern GlobalData *TheWritableGlobalData;
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
extern void *g_00E03210;                                // the Rva0042CBB6 translator
extern BfmeOwnVVD *g_bfmeSingletonVVD;
extern Rva00431F61 *g_00E0322C;
extern Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController;
extern Eva *TheEva;
extern View *TheTacticalView;
extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern GameEngine *TheGameEngine;
extern GhostObjectManager *TheGhostObjectManager;
extern ParticleSystemManager *TheParticleSystemManager;
extern int g_Va00DBA4E4;                                // LogicFramesPerSecond
extern int g_00E02EC4;

void Rva0038072AClear();
IMEManager *CreateIMEManagerInterface();
LanguageFilter *createLanguageFilter();
void Rva00380B0CInit();
void Rva00220DCDInit();
void Rva002210CFInit();
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
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime(void);

// The drawable hash's clear (0x001DBCDC) and resize (0x0053F1EC) are folded
// STLport hashtable bodies; called through their pinned placeholder names.
class Rva001DBCDCTarget { public: void rva001DBCDC(); };
class Rva00057D38 { public: int rva0053F1EC(unsigned int); };

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

// ?reset@GameClient@@UAEXXZ
void GameClient::reset()
{
	Drawable *draw, *nextDraw;

	((Rva001DBCDCTarget *)&m_drawableHash)->rva001DBCDC();
	((Rva00057D38 *)&m_drawableHash)->rva0053F1EC(0x2000);
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
	g_00DFF080->reset();
	TheRayEffects->reset();
	TheVideoPlayer->reset();
	if (g_00DFEF18)
		g_00DFEF18->vf05();
	g_004C9DC9Container->reset();
	bfmeReset();

	if (TheSnowManager)
		TheSnowManager->reset();
	if (g_00DFE1E4)
		g_00DFE1E4->reset();
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

// Called from update: applies a display mode change requested while the
// shell was up, then rebuilds the shell and returns to the main menu.
// ?rva00239759@GameClient@@QAEXXZ
void GameClient::rva00239759()
{
	if (m_displayModePending)
	{
		::delete TheShell;
		TheShell = 0;
		m_displayModePending = 0;
		if (m_pendingXRes > 0 && m_pendingYRes > 0 && m_pendingBitDepth > 0
			&& (m_pendingXRes != TheWritableGlobalData->m_xResolution
				|| m_pendingYRes != TheWritableGlobalData->m_yResolution))
		{
			if (m_byteCA)
			{
				m_previousWidth = TheDisplay->getWidth();
				m_previousHeight = TheDisplay->getHeight();
				m_previousBitDepth = TheDisplay->getBitDepth();
			}
			if (TheDisplay->setDisplayMode(m_pendingXRes, m_pendingYRes, m_pendingBitDepth, TheDisplay->getWindowed()))
			{
				TheWritableGlobalData->m_xResolution = m_pendingXRes;
				TheWritableGlobalData->m_yResolution = m_pendingYRes;
				TheHeaderTemplateManager->onResolutionChanged();
				TheMouse->rva000B3FD0();
				Rva0041267F();
			}
			else
			{
				m_byteCA = 0;
			}
			m_pendingXRes = 0;
			m_pendingYRes = 0;
			m_pendingBitDepth = 0;
		}
		TheShell = new Shell;
		if (TheShell)
			TheShell->init();
		TheWindowManager->update();
		g_bfmeAptWindowManager->vf10();
		TheInGameUI->vf108();
		TheShell->push(AsciiString("MainMenu.apt"));
	}
}

// ?update@GameClient@@UAEXXZ
void GameClient::update()
{
	g_bfmeSingletonVVD->rva0042F213();
	((Rva0042CBB6 *)g_00E03210)->rva0042D068();
	((Rva005D124D *)g_00E0322C)->rva005D124D();

	if (g_00DFEF18)
	{
		g_00DFEF18->vf27();
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
	if (g_00DFE1E4)
		g_00DFE1E4->update();
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
		TheDisplay->drawViews();
		TheDisplay->update();
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
						unsigned int limit = 2 * g_Va00DBA4E4;
						if (object->isEffectivelyDead())
							limit += 3 * g_Va00DBA4E4;
						if (TheGameLogic->getFrame() < limit + draw->getShroudClearFrame())
							ss = SHROUD_STATUS_CLEAR;
					}
					draw->setFullyObscuredByShroud(ss >= SHROUD_STATUS_FOGGED);
				}
			}
			draw->updateDrawable();
			draw = next;
		}

		g_004C9DC9Container->update();
		if (TheGameEngine->rva00225D38())
			((Rva00239300 *)this)->rva00239300(TheGameLogic->getFrame(), 1);
		else
			((Rva00239300 *)this)->rva00239300(TheGameLogic->getFrame(), 0);
	}

	TheGameLogic->deleteLoadScreen();

	if (!TheGameLogic->getFlag125())
	{
		g_00DFF080->update();
		TheDisplay->update();
	}
	else
	{
		((Rva0004378D *)TheDisplay)->first();
	}

	if (!freezeTime)
		TheParticleSystemManager->setLocalPlayerIndex(localPlayerIndex);

	TheDisplay->drawViews();
	TheDisplayStringManager->update();

	if (!TheGameLogic->getFlag125() || TheShell->m_byte5C)
	{
		TheShell->update();
		if (m_displayModePending)
			rva00239759();
	}

	TheInGameUI->update();
	vf36();
}
