// ?validateSides@SidesList@@QAE_NXZ
// ?validateSides@SidesList@@QAE_NXZ
// ?validateSides@SidesList@@QAE_NXZ
// ?validateSides@SidesList@@QAE_NXZ
// ?validateSides@SidesList@@QAE_NXZ
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// SidesList::validateSides (BFME2 SidesList.cpp). The class view below is
// shared with SidesListDataChunks.cpp, which owns the map-file chunk parsers
// and writers this unit used to repeat.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
#include <vector>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Rb_tree_base<AsciiString, allocator<AsciiString> >::~_Rb_tree_base(); }
namespace _STL { template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base(); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * allocator<_Rb_tree_node<AsciiString> >::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_Rb_tree_node<AsciiString> *, _Rb_tree_node<AsciiString>, allocator<_Rb_tree_node<AsciiString> > >::deallocate(_Rb_tree_node<AsciiString> *, unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *, AsciiString, allocator<AsciiString> >::deallocate(AsciiString *, unsigned int); }
namespace _STL { template <> void allocator<_Rb_tree_node<AsciiString> >::deallocate(_Rb_tree_node<AsciiString> *, unsigned int) const; }
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, unsigned int) const; }
// bfme link decl-only end

enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

class StaticNameKey
{
public:
	NameKeyType key() const;			// 0x00148F5E
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_objectName;			// VA 0x00DBDCC4
extern const StaticNameKey TheKey_objectIsABase;		// VA 0x00DBDD0C
extern const StaticNameKey TheKey_objectBaseName;		// VA 0x00DBDD14
extern const StaticNameKey TheKey_objectBasePriority;	// VA 0x00DBDD84
extern const StaticNameKey TheKey_objectBasePhase;		// VA 0x00DBDD8C
// Preserve the data ledger's established provider spelling for this key.
class Rva00148F5ECache
{
public:
	NameKeyType get(void); // 0x00148F5E
	operator NameKeyType() { return get(); }
	NameKeyType key;
	const char *name;
};
extern Rva00148F5ECache TheKey_playerAIType;
extern const StaticNameKey TheKey_playerName;			// VA 0x00DBDE24
extern const StaticNameKey TheKey_teamOwner;			// VA 0x00DBD9FC
extern const StaticNameKey TheKey_teamLibraryMapName;	// VA 0x00DBDC1C
extern const StaticNameKey TheKey_teamName;			// VA 0x00DBD9F4

enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005 };

#include "../../../Include/Common/DataChunkInfo.h"

class Dict
{
public:
	Dict(int numPairsToPreAllocate);
	void setBool(int key, bool value);
	Dict(const Dict &src) : m_data(src.m_data) { if (m_data) ++*(unsigned short *)m_data; }
	~Dict() { releaseData(); }
	enum DataType { DICT_NONE = -1, DICT_BOOL = 0, DICT_INT, DICT_REAL, DICT_ASCIISTRING };
	DataType getType(int key) const;	// 0x0031317C
	bool getBool(int key, bool *exists = 0) const;	// 0x00313198
	int getInt(int key, bool *exists = 0) const;	// 0x003131CA
	AsciiString getAsciiString(int key, bool *exists = 0) const;	// 0x0031359F
	void setAsciiString(int key, const AsciiString &value);	// 0x0031375A

private:
	void releaseData();					// 0x0031339C
	void *m_data;
};

#include "../../../Include/Common/ChunkInputStreamClass.h"

// The cached file stream the build-list loader reads (BFME 1's
// CachedFileInputStream), rowed under its constructor's address name: ctor
// 0x00240000, dtor 0x0023F4F0 and open 0x00308050; its close is rowed under
// Rva003079ED below. 0x20 bytes on the loader's stack.
class Rva00240000 : public ChunkInputStream
{
public:
	Rva00240000() throw(); // 0x00240000
	~Rva00240000(); // 0x0023F4F0
	bool rva00308050(AsciiString path); // 0x00308050, open
private:
	char m_data[0x20]; // +0x00
};

class Rva003079ED
{
public:
	void rva003079ED();					// 0x003079ED, close
};

#include "../../../Include/Common/DataChunk.h"

// DataChunkInput's parser unregistration (WB DataChunkInput::unregisterParser),
// rowed under its address-era spelling.
#include "../../../Include/GameLogic/Q1Forwardee0000871A.h"

// The parser binding that registers "PlayerScriptsList" on construction and
// unregisters itself on destruction; its base dtor is inline here (vtable
// 0x007C9574), its ctor out of line.
class BfmeParserRegistryVE;

class BfmeParserBindingBaseVE
{
public:
	__declspec(dllimport) __forceinline virtual ~BfmeParserBindingBaseVE() { m_registry->handle(m_token); }
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	Q1Forwardee0000871A *m_registry;	// +0x04, the DataChunkInput
	int m_token;						// +0x08
};

class Rva003B3417 : public BfmeParserBindingBaseVE
{
public:
	Rva003B3417(void *a, void *b, BfmeParserRegistryVE *registry, const AsciiString *parentLabel); // 0x003B3417
	virtual ~Rva003B3417(); // 0x003B3417
private:
	void *m_a; // +0x0C
	void *m_b; // +0x10
};

// The binding that registers "LibraryMaps" and fills one vector<AsciiString>
// per side and the count of lists read.
class LibraryMapsParser : public BfmeParserBindingBaseVE
{
public:
	LibraryMapsParser(void *lists, void *count, void *table, void *info);	// 0x00329F83

private:
	void *m_lists;
	void *m_count;
};

#include "../../../Include/GameLogic/ScriptList.h"

// ScriptList's merge of another list (WB 0xaa4840), rowed under its
// address-era spelling.
struct BfmeSubGE;
#include "../../../Include/GameLogic/BfmeThingGE.h"

class Dict;
#include "../../../Include/Common/DataChunkOutput.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// The kind-of mask at +0x108 and the name at +0x64 of the template a map
// object resolves to through its override chain.
#include "../../../Include/Common/ThingTemplate.h"

// MapObject resolves the final template override at 0x0030D833; the
// location getter at 0x0030D631 retains its address-derived spelling.
class BfmeRetBWF;
class Rva0030D631 { public: BfmeRetBWF *rva0030D631(); };

class MapObject
{
public:
	MapObject *getNext() const { return m_nextMapObject; }
	const ThingTemplate *getThingTemplate() const;
	const Coord3D *getLocation() { return (const Coord3D *)((Rva0030D631 *)this)->rva0030D631(); }
	float getAngle() const { return m_angle; }
	Dict *getProperties() { return &m_properties; }

private:
	char m_pad00[0x04];
	MapObject *m_nextMapObject;			// +0x04
	char m_pad08[0x1C - 0x08];
	float m_angle;						// +0x1C
	char m_pad20[0x24 - 0x20];
	Dict m_properties;					// +0x24
};

// A castle path: its two-real points in a vector at +0x08, the next path at
// +0x3C and its name at +0x40. The by-value point getter 0x002E3A8D keeps its
// address-era spelling (hidden return pointer explicit).
struct Rva002E3A8DPair
{
	float m_x;
	float m_y;
};

class Rva002E3A8DHolder
{
public:
	Rva002E3A8DPair *get(Rva002E3A8DPair *out, int index);	// 0x002E3A8D
	int getNumPoints() const { return m_points.size(); }
	Rva002E3A8DHolder *getNext() const { return m_next; }
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad00[0x08];
	_STL::vector<Rva002E3A8DPair> m_points;	// +0x08
	char m_pad14[0x3C - 0x14];
	Rva002E3A8DHolder *m_next;			// +0x3C
	AsciiString m_name;					// +0x40
};

// The 128-byte entry SidesList::addToFactionBuildListMap 0x0032CDFE copies.
struct BfmePod128 { int a[32]; };

// A castle path point: two reals (vector<BfmeE8>::push_back 0x00539A2E).
struct BfmeE8 { float x; float y; };

// By-value AsciiString setters at BuildListInfo +0x04, +0x08 and +0x30. The
// first and last sit beside BuildListInfo's ctor and dtor; +0x08 is folded
// with another class's setter at 0x002AAE81.
class Rva0032A438
{
public:
	void rva0032A438(AsciiString s);
private:
	int m_00; // +0x00
	AsciiString m_04; // +0x04
};
class Rva0032A46C
{
public:
	void rva0032A46C(AsciiString s);
	char m_pad00[0x30];
private:
	AsciiString m_30; // +0x30
};

// The by-value getter of the AsciiString at +0x04, folded with other classes'
// name getters at 0x00564DF2.
#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"

class SidesInfo
{
public:
	BuildListInfo *getBuildList() { return m_pBuildList; }
	Dict *getDict() { return &m_dict; }
	void addToBuildList(BuildListInfo *buildList, int position);	// 0x003297FB
	void setScriptList(ScriptList *scriptList) { m_scripts.swap(scriptList); }

private:
	friend class SidesList;

	BuildListInfo *m_pBuildList;		// +0x00
	Dict m_dict;						// +0x04
	ScriptList m_scripts;				// +0x08
	_STL::vector<AsciiString> m_libraryMaps;	// +0x54
};

// The 16-byte team entries (SidesListRemoveSideAndTeams.cpp): the next team
// id at +0 and the team dict at +0xC.
class TeamsInfoEntry
{
public:
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;						// +0x0C
};

class TeamsInfoRec
{
public:
	friend class SidesList;
	void renameTeam(int id, const AsciiString &owner, const AsciiString &name);
	TeamsInfoEntry &entryRaw(unsigned int n) { return (*reinterpret_cast<TeamsInfoEntry **>(&m_teams))[n]; }
	TeamsInfoRec();
	~TeamsInfoRec();
	void swap(TeamsInfoRec *other);		// 0x0032B651
	__forceinline int getNumTeams() const { return m_count; }
	int addTeam(const Dict *dict);		// 0x0032DA4E
	void rva0032C2C4();					// 0x0032C2C4, WB discards overridden teams
	void removeTeam(int id);			// 0x0032C26D, WB removeTeam
	int getFirstTeamID() const { return m_teams[0].m_next; }
	int getNextTeamID(int id) const { return m_teams[id].m_next; }
	Dict *getTeamInfo(int id) { return &m_teams[id].m_dict; }

private:
	char m_index[0x0C];
	_STL::vector<TeamsInfoEntry> m_teams;	// +0x0C
	short m_count;						// +0x18, signed test at 0x0032E48C
	char m_rest[0x1C - 0x1A];
};

class LibraryMapCache;

// The case-insensitive set of library map names linkLibraryMaps has visited;
// its _M_find 0x0002C751 and insert 0x0002CA26 are rowed in WWLib.
struct BfmeStringNoCaseLess { bool operator()(const AsciiString &a, const AsciiString &b) const; };
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> AsciiStringNoCaseSet;

// BFME 2's SidesList has two bases (SidesList_sidesInfo.cpp), so its member
// pointers are the 8-byte multiple-inheritance form; this view flattens them.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class SidesList
{
public:
	SidesList();						// 0x0032EE24
	virtual ~SidesList();				// 0x0032EC63

	bool parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info);
	bool parseBuildListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void writeSidesDataChunk(DataChunkOutput &chunkWriter);
	void addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType);	// 0x0032CDFE
	int addSide(const Dict *dict);		// 0x0032D076
	SidesInfo *getSideInfo(int side);	// 0x002035BA
	void swap(SidesList *other);		// 0x0032B690
	bool validateSides();
	int getNumSides() { return m_numSides; }
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);
	bool validateAllyEnemyList(const AsciiString &name, AsciiString &list);
	int addPlayerByTemplate(const AsciiString &playerTemplate);
	void rva0032ED61();					// 0x0032ED61, castle template map clear
	void parseCastleTemplateMaps();		// 0x0032F84F
	bool parseCastleTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info);
	bool parseLibraryMapListsChunk(DataChunkInput &file, DataChunkInfo *info);
	void writeCastleTemplateDataChunk(DataChunkOutput &out, MapObject *pMapObjs, const AsciiString &mapName, Rva002E3A8DHolder *paths);
	void rva0032E6F4(int key, const BfmePod128 &entry);	// 0x0032E6F4, castle build entry add
	void rva0032ED75(int key, const _STL::vector<BfmeE8> &path);	// 0x0032ED75, castle path add
	void rva0032C88F(int index);		// 0x0032C88F, WB 0xa86610
	bool rva0032D038(DataChunkInput &file, DataChunkInfo *info);
	bool rva0032D04A(DataChunkInput &file, DataChunkInfo *info);
	void rva0032D554();
	bool rva0032F0AA(DataChunkInput &file, void *info);	// 0x0032F0AA, the "Teams" callback
	void discardOverriddenScriptsAndTeams();
	void addMusicScriptReference();
	void rva0032FC70(int sideIndex, LibraryMapCache *cache);
	void rva0032E474(SidesInfo *side, ScriptList *scripts, TeamsInfoRec *teams);
	void linkLibraryMaps(int sideIndex, LibraryMapCache *cache, const _STL::vector<AsciiString> &libraryMaps,
		AsciiStringNoCaseSet &visited, ScriptList *scripts, TeamsInfoRec *teams);

private:
	// getSideInfo expanded in place, as linkLibraryMaps has it for a library
	// map's second side (cmp [sides+0x3C],1 / lea [sides+0xA0]).
	SidesInfo *getSideInfoInline(int side) { return side >= 0 && side < m_numSides ? (SidesInfo *)m_sides + side : 0; }

	char m_bases[0x20 - 4];
	_STL::list<AsciiString> m_castleTemplateMaps;	// +0x20
	char m_castleTemplates[0x3C - 0x24];
	int m_numSides;						// +0x3C
	char m_sides[0xF44 - 0x40];
	TeamsInfoRec m_teamrec;				// +0xF44
	char m_secondTeamRec[0x1C]; // distinct adjacent TeamsInfoRec at +0xF60
	bool m_cleared;						// +0xF7C
	char m_factionBuildLists[0x11B0 - 0xF7D];
};
// The chunk parsers, writers and library-map linkers of this class are rowed
// in SidesListDataChunks.cpp; this unit keeps validateSides only.

class Rva00329EE9StringValue;
class Rva00329EE9Dict
{
public:
	Rva00329EE9StringValue getAsciiString(int key, bool *exists) const;
};

class Rva00329EE9
{
public:
	bool rva00329EE9(void) const;
private:
	int m_prefix; // +0x00
	Rva00329EE9Dict m_dict; // +0x04
	char m_pad05[0x3];
};


extern Rva00148F5ECache TheKey_teamIsSingleton;
extern Rva00148F5ECache TheKey_playerAllies;
extern Rva00148F5ECache TheKey_playerEnemies;
struct Rva0019B780Key
{
	AsciiString first;
	AsciiString second;
};

struct Rva0019B780Node
{
	unsigned char m_data[0x1c];
};

class Rva0019B780Tree
{
public:
	Rva0019B780Node *find( const Rva0019B780Key &key ) const throw();

private:
	unsigned char m_tree[12];
};

struct Rva0019B780Entry
{
	unsigned char m_data[16];
};

class Rva0019C520Member
{
public:
	int lookup( AsciiString *name, int extra );

private:
	Rva0019B780Tree m_tree;
	Rva0019B780Entry *m_entries;
};

class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int extra);

private:
	char m_head[0xF44];
	Rva0019C520Member m_member;
};
AsciiString Rva0032B389Join(const AsciiString &a, const AsciiString &b);

bool SidesList::validateSides()
{
	bool modified = false;
	int i;

	int neutral = -1;
	int numSides = m_numSides;
	for (i = 0; i < numSides; i++) {
		if (((const Rva00329EE9 *)getSideInfo(i))->rva00329EE9()) {
			neutral = i;
			break;
		}
	}
	if (neutral == -1) {
		addPlayerByTemplate(AsciiString::TheEmptyString);
		modified = true;
	}

	for (i = 0; i < getNumSides(); i++) {
		Dict *pdict = getSideInfo(i)->getDict();
		AsciiString pname = pdict->getAsciiString(TheKey_playerName);
		AsciiString tname("team");
		tname.concat(pname);
		int index;
		Dict *ti = (Dict *)((Rva0019C520Owner *)this)->forward(Rva0032B389Join(pname, tname), (int)&index);
		if (ti != 0 && index != 0) {
			if (ti->getAsciiString(TheKey_teamOwner) != pname) {
				m_teamrec.renameTeam(index, pname, ti->getAsciiString(TheKey_teamName));
				modified = true;
			}
			if (!ti->getBool(TheKey_teamIsSingleton.get())) {
				ti->setBool(TheKey_teamIsSingleton.get(), true);
				modified = true;
			}
		} else {
			Dict d(0);
			d.setAsciiString(TheKey_teamName, tname);
			d.setAsciiString(TheKey_teamOwner, pname);
			d.setBool(TheKey_teamIsSingleton.get(), true);
			m_teamrec.addTeam(&d);
			modified = true;
		}
		AsciiString allies = pdict->getAsciiString(TheKey_playerAllies.get());
		AsciiString enemies = pdict->getAsciiString(TheKey_playerEnemies.get());
		if (validateAllyEnemyList(pname, allies)) {
			pdict->setAsciiString(TheKey_playerAllies.get(), allies);
			modified = true;
		}
		if (validateAllyEnemyList(pname, enemies)) {
			pdict->setAsciiString(TheKey_playerEnemies.get(), enemies);
			modified = true;
		}
	}

restart:
	for (i = m_teamrec.entryRaw(0).m_next; i != 0; ) {
		char *base = (char *)&m_teamrec.m_teams[0];
		unsigned int teamOffset = (unsigned int)i * sizeof(TeamsInfoEntry);
		TeamsInfoEntry *entry = (TeamsInfoEntry *)(base + teamOffset);
		int next = entry->m_next;
		Dict *tdict = &m_teamrec.entryRaw(i).m_dict;
		AsciiString tname = tdict->getAsciiString(TheKey_teamName);
		if (findSideInfo(tname) != 0) {
			m_teamrec.removeTeam(i);
			modified = true;
			goto restart;
		}
		i = next;
	}

	for (i = m_teamrec.entryRaw(0).m_next; i != 0; i = m_teamrec.entryRaw(i).m_next) {
		if (m_teamrec.m_teams[i].m_free != 0)
			continue;
		Dict *tdict = &m_teamrec.m_teams[i].m_dict;
		AsciiString tname = tdict->getAsciiString(TheKey_teamName);
		AsciiString towner = tdict->getAsciiString(TheKey_teamOwner);
		if (findSideInfo(towner) == 0 || towner == tname) {
			m_teamrec.renameTeam(i, AsciiString::TheEmptyString, tname);
			modified = true;
		}
	}
	return modified;
}

