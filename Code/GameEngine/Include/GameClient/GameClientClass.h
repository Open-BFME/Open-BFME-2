/* Target facts (code addresses are RVAs and table addresses are VAs):
Constructor 0x0023BC36 calls SubsystemInterface's constructor at 0x0023BC4B, installs Snapshot's base table 0x00BBB554 at +0x0C (0x0023BC55), then stores GameClient's primary table 0x00BED850 and secondary table 0x00BED840 at 0x0023BC63/0x0023BC69. Destructor 0x0023AE08 restores these same GameClient tables at 0x0023AE1C/0x0023AE22. Its final secondary store at 0x0023B255 restores Snapshot for base teardown before calling SubsystemInterface's destructor at 0x0023B25C. These stores describe successive base lifetimes. The parent occupies +0..+0x0B and Snapshot occupies +0x0C..+0x0F.
The primary table has 52 slots, ending at non-code word VA 0x00BED920. Slots 0..13 have SubsystemInterface's order: deleting destructor 0x0023BDBB, init 0x0023A1BB, loadIniFilesFromLegend 0x001B5384, the inherited default bodies, reset 0x0023B278 and update 0x0023BEE8. The registered parent exposes those slots through BFME_SUBSYSTEM_SLOTS. The secondary table has four slots, ending at the primary table: destructor thunk 0x0023B270 (subtract 0x0C then jump to 0x0023BDBB), loadPostProcess 0x00239A9D, name getter 0x0004C457 and xfer 0x0023B509. Both lifetime methods are declared out of line.
Primary slots 14/17/31/35 target 0x005F69CE/0x0057E556/0x001DB09D/0x0057E556: store dword +0x10, read pointer +0x14, read dword +0x10, read pointer +0x14. The other named primary slots use their GameClient ledger rows at 0x00238E25, 0x00239C21, 0x00238F15, 0x00238F34, 0x00238F29, 0x00239949, 0x00239982, 0x00238E4C, 0x002391AA, 0x00238EBF, 0x00239F40, 0x00238EF2, 0x00238F3F, 0x00238F5C and 0x00239911. Slot 18's row proves a three-argument enum-returning dispatch; its neutral ABI declaration avoids inventing a definition of CommandTranslator, whose nested enum lacks a shared declaration.
Slots 21/22/28/32/37..51 are purecall in GameClient. Device table 0x00BC4738 gives slots 21/22/28/32 the rowed createRayEffectByTemplate/addScorch/friend_createDrawable/setTeamColor implementations at 0x0004C7F0/0x0004C7A8/0x0004C75F/0x0004C8BC. Slot 28's ledger signature has three arguments, with an additional integer; its body returns with ret 0x0C. Factories 37..46 and rate setter 51 follow Zero Hour's declarations; the pointer-returning factories 47..50 (0x0004C62D/0x0004C662/0x0004C694/0x0004C8DD) remain neutral. Slot 51's device implementation is 0x0004C6C6. Factory 50 allocates a 0x1D4-byte object and returns its pointer.
The constructor writes through +0x13C (0x0023BD67), proving an extent of at least 0x140. Factory 0x00041D62 allocates 0x140 bytes and calls 0x0004C43E, which calls GameClient's constructor and only replaces its two tables. This bounds GameClient to sizeof 0x140 with four-byte alignment. Constructor stores prove frame +0x10, drawable head +0x14, next drawable ID +0x2C, 32 translator IDs at +0x30 (0x0023BD71..0x0023BD7A), count +0xB0, command translator +0xB4 and a dword +0xB8. The AsciiString at +0xBC is constructed at 0x0023BC7B..0x0023BCA3 and destroyed at 0x0023B234..0x0023B23E. The constructor clears bytes +0xC0/+0xC1 and dword +0xC4 at 0x0023BCB6/0x0023BCBC/0x0023BCC2. W3DView::draw clears the rendered-object counter at +0xC4 (0x00088CC0), drawablePostDraw increments it at 0x00085B2D, and gatherDebugStats reads it at 0x00048DB9. Camera construction tests +0xC1/+0xC0 at 0x0008AA75/0x0008AA80. Other storage remains opaque.
Nonvirtual declarations follow ledger rows: allocDrawableID 0x002FDB5D, addIconLayer 0x00239FCC, findTOCEntryByName 0x00239C5E, findTOCEntryById 0x002399EB, addTOCEntry 0x0023AB78, xferDrawableTOC 0x0023AC36, rva00239759 0x00239759 and rva0023B383 0x0023B383. DrawableTOCEntry remains opaque: its copy constructor at 0x00239B46 and destructor at 0x0048BA39 have rowed out-of-line providers.
Donor facts: Zero Hour GeneralsMD GameClient.h supplies setFrame, firstDrawable, getFrame, getDrawableList, the factory names, the translator/rendered-count field names and the nonvirtual counter accessors. The retail table entries and accesses above establish their BFME2 placement. No donor header is included.
*/
#pragma once
#ifndef BFME2_GAMECLIENTCLASS_H
#define BFME2_GAMECLIENTCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class Drawable;
class ThingTemplate;
class FrustumClass;
class CommandTranslator;
class Dict;
class Display;
class InGameUI;
class GameWindowManager;
class FontLibrary;
class DisplayStringManager;
class VideoPlayerInterface;
class TerrainVisual;
class Keyboard;
class Mouse;
class SnowManager;
struct Coord3D;
struct Region3D;
struct RayEffectData;
enum DrawableID;
enum DrawableStatus;
enum Scorches;
enum TimeOfDay;

typedef void (*GameClientFuncPtr)(Drawable *, void *);

class GameClient : public SubsystemInterface, public Snapshot
{
public:
    struct DrawableTOCEntry;

    GameClient();
    virtual ~GameClient();
    virtual void init();
    virtual void reset();
    virtual void update();

    virtual void setFrame(unsigned int frame) { m_frame = frame; }
    virtual void registerDrawable(Drawable *draw);
    virtual Drawable *findDrawableByID(DrawableID id);
    virtual Drawable *firstDrawable() { return m_drawableList; }
    virtual int vslot18(Drawable *draw, const Coord3D *pos, int commandType);
    virtual void removeFromRayEffects(Drawable *draw);
    virtual void getRayEffectData(Drawable *draw, RayEffectData *data);
    virtual void createRayEffectByTemplate(const Coord3D *start, const Coord3D *end, const ThingTemplate *tmpl) = 0;
    virtual void addScorch(const Coord3D *pos, float radius, Scorches type) = 0;
    virtual bool loadMap(AsciiString name);
    virtual void unloadMap(AsciiString name);
    virtual void iterateDrawablesInRegion(Region3D *region, GameClientFuncPtr func, void *data);
    virtual void rva002391AA(const FrustumClass *frustum, float radius, GameClientFuncPtr func, void *data);
    virtual void rva00238EBF(GameClientFuncPtr func, void *data);
    virtual Drawable *friend_createDrawable(const ThingTemplate *tmpl, DrawableStatus status, int extra) = 0;
    virtual void destroyDrawable(Drawable *draw);
    virtual void setTimeOfDay(TimeOfDay tod);
    virtual unsigned int getFrame() { return m_frame; }
    virtual void setTeamColor(int red, int green, int blue) = 0;
    virtual void releaseShadows();
    virtual void allocateShadows();
    virtual Drawable *getDrawableList() { return m_drawableList; }
    virtual void rva00239911();
    virtual Display *createGameDisplay() = 0;
    virtual InGameUI *createInGameUI() = 0;
    virtual GameWindowManager *createWindowManager() = 0;
    virtual FontLibrary *createFontLibrary() = 0;
    virtual DisplayStringManager *createDisplayStringManager() = 0;
    virtual VideoPlayerInterface *createVideoPlayer() = 0;
    virtual TerrainVisual *createTerrainVisual() = 0;
    virtual Keyboard *createKeyboard() = 0;
    virtual Mouse *createMouse() = 0;
    virtual SnowManager *createSnowManager() = 0;
    virtual void *vslot47() = 0;
    virtual void *vslot48() = 0;
    virtual void *vslot49() = 0;
    virtual void *vslot50() = 0;
    virtual void setFrameRate(float rate) = 0;

    void addIconLayer(int layer, Drawable *draw);
    DrawableTOCEntry *findTOCEntryByName(AsciiString name);
    DrawableTOCEntry *findTOCEntryById(unsigned short id);
    void addTOCEntry(AsciiString name, unsigned short id);
    void xferDrawableTOC(Xfer *xfer);
    void rva00239759();
    void rva0023B383(Dict *props, ThingTemplate *tmpl, const Coord3D *pos);

    void setDrawableIDCounter(DrawableID id) { m_nextDrawableID = (unsigned int)id; }
    DrawableID getDrawableIDCounter() { return (DrawableID)m_nextDrawableID; }
    void resetRenderedObjectCount() { m_renderedObjectCount = 0; }
    unsigned int getRenderedObjectCount() const { return m_renderedObjectCount; }
    void incrementRenderedObjectCount() { ++m_renderedObjectCount; }

protected:
    DrawableID allocDrawableID();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

public:
    unsigned int m_frame;
    Drawable *m_drawableList;
    unsigned char m_opaque18[0x14];
    unsigned int m_nextDrawableID;
    unsigned int m_translators[32];
    unsigned int m_numTranslators;
    CommandTranslator *m_commandTranslator;
    unsigned int m_fieldB8;
    AsciiString m_stringBC;
    bool m_fieldC0;
    bool m_fieldC1;
    unsigned char m_padC2[2];
    unsigned int m_renderedObjectCount;
    unsigned char m_opaqueC8[0x78];
};

extern GameClient *TheGameClient;

#endif
