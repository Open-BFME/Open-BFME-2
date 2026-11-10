// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructors 0x0032EE24 and 0x0032EF3E call SubsystemInterface at +0, store Snapshot's 0x00BBB554 at +0x0C, and construct the nonvirtual Rva00330757Member base at +0x10 (0x00330757). Their final stores install 0x00C0DA98 at +0 and 0x00C0DA88 at +0x0C. Destructor 0x0032EC63 installs the same pair before restoring the base tables during teardown. The different tables belong to the two base subobjects and their construction phases.
// Table 0x00C0DA98 has fourteen slots: 0=0x0032EF22 (deleting destructor), 1/3/8/10/12=0x000B3FD0, 2=0x001B5384, 4/11=0x005CB9FF, 5=0x0047A699, 6=0x000D43D0, 7/13=0x0047A69C, 9=0x0032E53D (tail-jumps to clear at 0x0032DDDE). The registered SubsystemInterface contract proves this order; Zero Hour supplies the init, reset and update names. SidesList adds no primary virtual slots and inherits the common defaults.
// Table 0x00C0DA88 has four Snapshot slots: 0=0x0032ED59 (this -= 0x0C, then deleting destructor), 1=0x000B3FD0 (LoadPostProcess), 2=0x0032ED53 (returns "SidesList" at VA 0x00BC9618), 3=0x00329AEA (DoXfer; its receiver is the Snapshot subobject). The next table starts at 0x00C0DA98.
// Constructor 0x0032EE24 constructs list/maps at +0x20/+0x24/+0x30, clears dword counts +0x3C/+0x7C0, constructs twenty 0x60-byte SidesInfo records at +0x40/+0x7C4, TeamsInfoRec at +0xF44/+0xF60, sets byte +0xF7C, and constructs twenty 0x1C-byte records at +0xF80. Allocation sites 0x0022E968 and 0x0032F4D8 request 0x11B0 bytes before calling that constructor. Getter 0x002035BA proves count +0x3C and stride 0x60; 0x002A98D1 proves +0x7C0/+0x7C4 and the same stride; 0x0016809F reads +0x7C0; 0x00313840 reads signed word +0xF78.
// Copy constructor 0x0032EF3E and assignment 0x0032E978 call the rowed base/member copies; destructor 0x0032EC63 is out of line. All three are declared only. Other declarations preserve the SidesList ledger spellings. Zero Hour SidesList.h supplies the names of the counts and getNumSides; retail 0x00205358 reads +0x3C in its side loop. Unrecovered member storage is opaque.
// The +0x10 base constructor 0x00330757 calls the empty-vector initializer 0x00211E58, then writes -1 at its +0x0C. Its rowed destructor is the nullable first-pointer release at 0x0007FAB3. The registered headers supply the proven SubsystemInterface, Snapshot and Rva00330757Member layouts; their selectable slot surfaces change no offsets.
// Remaining named member rows: emptySides 0x0032D81B, emptyTeams 0x0032D05C, addSide 0x0032D076, removeSide 0x0032D850, removeSideAndTeams 0x0032D8C7, addPlayerByTemplate 0x0032DE04, swap 0x0032B690, exchangeFlag 0x0032B833, duplicateScripts 0x00329A80, discardOverriddenScriptsAndTeams 0x0032C991, addMusicScriptReference 0x0032FD8E, and addToFactionBuildListMap 0x0032CDFE.
// Lookup and validation rows: findSideInfo 0x0032B0A9, findSkirmishSideInfo 0x0032B13F, isPlayerDefaultTeam 0x0032B1E1, validateAllyEnemyList 0x0032B2A5, and validateSides 0x0032E02B. Parser and writer rows: parseBuildListDataChunk 0x0032CE9E, parseCastleTemplateDataChunk 0x0032F664, parseLibraryMapListsChunk 0x0032C779, parseSidesDataChunk 0x0032F13C, parseCastleTemplateMaps 0x0032F84F, writeCastleTemplateDataChunk 0x0032B88C, writeSidesDataChunk 0x0032E542, and linkLibraryMaps 0x0032FA07.
// The rva-prefixed declarations retain their ledger names and encode their own entry RVAs, including rva0032996EWriteScripts and rva00329FF4WriteLibraryMaps. Their decorated rows prove the parameter types and access. Forward declarations do not assert layouts for their parameter types.
#pragma once

#ifndef BFME2_COMMON_SIDESLIST_H
#define BFME2_COMMON_SIDESLIST_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "Rva00330757Member.h"

class AsciiString;
class BuildListInfo;
class DataChunkInput;
class DataChunkOutput;
class Dict;
class LibraryMapCache;
class MapObject;
class PolygonalArea;
class Rva002E3A8DHolder;
class ScriptList;
class SidesInfo;
class SidesList;
class TeamsInfo;
class TeamsInfoRec;
class Xfer;
struct BfmeE8;
struct BfmePod128;
struct BfmeStringNoCaseLess;
struct DataChunkInfo;
enum NameKeyType;

namespace _STL {
template<class T> class allocator;
template<class T, class Alloc> class vector;
template<class Key, class Compare, class Alloc> class set;
}

class SidesList : public SubsystemInterface, public Snapshot, public Rva00330757Member
{
public:
    SidesList();
    SidesList(const SidesList &that);
    virtual ~SidesList();
    SidesList &operator=(const SidesList &that);

    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

    int getNumSides() const { return m_numSides; }
    int getNumSkirmishSides();
    int getNumSkirmishTeams();
    SidesInfo *getSideInfo(int side);
    SidesInfo *getSkirmishSideInfo(int side);
    SidesInfo *findSideInfo(AsciiString name, int *index = 0);
    SidesInfo *findSkirmishSideInfo(AsciiString name, int *index = 0);
    bool isPlayerDefaultTeam(TeamsInfo *team);
    bool validateAllyEnemyList(const AsciiString &name, AsciiString &allies);
    bool validateSides();
    void emptySides();
    void emptyTeams();
    int addSide(const Dict *dict);
    void removeSide(int side);
    void removeSideAndTeams(int side);
    int addPlayerByTemplate(const AsciiString &name);
    void clear();
    void swap(SidesList *that);
    void exchangeFlag(SidesList *that);
    void duplicateScripts(const SidesList &that);
    void discardOverriddenScriptsAndTeams();
    void addMusicScriptReference();
    void addToFactionBuildListMap(NameKeyType key, const BfmePod128 &value, int index);
    void linkLibraryMaps(int side, LibraryMapCache *cache,
        const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &maps,
        _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &visited,
        ScriptList *scripts, TeamsInfoRec *teams);
    bool parseBuildListDataChunk(DataChunkInput &, DataChunkInfo *, void *);
    bool parseCastleTemplateDataChunk(DataChunkInput &, DataChunkInfo *);
    bool parseLibraryMapListsChunk(DataChunkInput &, DataChunkInfo *);
    bool parseSidesDataChunk(DataChunkInput &, DataChunkInfo *);
    void parseCastleTemplateMaps();
    void writeCastleTemplateDataChunk(DataChunkOutput &, MapObject *, const AsciiString &, Rva002E3A8DHolder *);
    void writeSidesDataChunk(DataChunkOutput &);
    void rva0032996EWriteScripts(DataChunkOutput &);
    void rva00329FF4WriteLibraryMaps(DataChunkOutput &);
    void rva0032A4D7(DataChunkOutput &);
    bool rva0032A587(int, int, BuildListInfo *, int);
    void rva0032A5FC(DataChunkOutput &);
    void rva0032B7A7(SidesList *);
    void rva0032B7E3(SidesList *);
    void rva0032B833(SidesList *);
    void rva0032B871(bool);
    bool rva0032BD25(int, int, BuildListInfo *);
    bool rva0032BD64(int, int, PolygonalArea *);
    void rva0032C88F(int);
    bool rva0032D038(DataChunkInput &, DataChunkInfo *);
    bool rva0032D04A(DataChunkInput &, DataChunkInfo *);
    void rva0032D554();
    void rva0032E474(SidesInfo *, ScriptList *, TeamsInfoRec *);
    void rva0032E6F4(int, const BfmePod128 &);
    void rva0032ED75(int, const _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > &);
    bool rva0032F0AA(DataChunkInput &, void *);
    void rva0032FC70(int, LibraryMapCache *);
    void rva0032FEF5();
    void rva0032FF48(int);
    void rva0032FF91();

    char m_field20[0x1C];
    int m_numSides;
    char m_field40[0x780];
    int m_numSkirmishSides;
    char m_field7C4[0x7B8];
    bool m_fieldF7C;
    char m_fieldF7D[0x233];
};

extern SidesList *TheSidesList;

#endif
