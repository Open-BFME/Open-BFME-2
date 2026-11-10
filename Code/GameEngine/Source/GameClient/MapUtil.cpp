// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/maputil_widesort /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// platformsdk
// dxsdk
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/MapUtil.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: MapUtil.cpp //////////////////////////////////////////////////////////////////////////////
// Author: Matt Campbell, December 2001
// Description: Map utility/convenience routines
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/CRC.h"
#include "Common/FileSystem.h"
#include "Common/LocalFileSystem.h"
#include "Common/File.h"
#include "Common/GlobalData.h"
#include "Common/GameState.h"
#include "Common/GameEngine.h"
#include "Common/NameKeyGenerator.h"
#include "Common/DataChunk.h"
#include "Common/MapReaderWriterInfo.h"
#include "Common/MessageStream.h"
#include "Common/WellKnownKeys.h"
#include "Common/INI.h"
#include "Common/QuotedPrintable.h"
#include "Common/SkirmishBattleHonors.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/MapObject.h"
#include "GameClient/GameText.h" 
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Image.h"
#include "GameClient/Shell.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#define __MAPUTIL_H__
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "Common/STLTypedefs.h"
class GameWindow;
class AsciiString;
struct Coord3D;
struct FileInfo;
class Image;
class DataChunkInput;
struct DataChunkInfo;
enum { SUPPLY_TECH_SIZE = 15 };
typedef std::list<ICoord2D> ICoord2DList;
class TechAndSupplyImages
{
public:
	ICoord2DList m_techPosList;
	ICoord2DList m_supplyPosList;
};
struct WinTimeStamp
{
	UnsignedInt m_lowTimeStamp;
	UnsignedInt m_highTimeStamp;
};
class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	void update( void );
	Int m_numStartSpots;
};
typedef std::list<Coord3D> Coord3DList;
class MapMetaData
{
public:
	MapMetaData();
	MapMetaData(const MapMetaData &);
	~MapMetaData();
	MapMetaData &operator=(const MapMetaData &);
	UnicodeString m_displayName;
	AsciiString m_nameLookupTag;
	Region3D m_extent;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	WinTimeStamp m_timestamp;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	AsciiString m_fileName;
};
// The map's value pair: its constructor and destructor are the rowed
// out-of-line copies (retail 0x0022DDF4 for the destructor), not this TU's.
namespace _STL {
template <> struct pair<const AsciiString, MapMetaData>
{
	typedef const AsciiString first_type;
	typedef MapMetaData second_type;
	const AsciiString first;
	MapMetaData second;
	pair(const AsciiString &, const MapMetaData &);
	pair(const pair &o) : first(o.first), second(o.second) {}
	~pair();
};
}
#include "../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;
extern TechAndSupplyImages TheSupplyAndTechImageLocations;
Int populateMapListbox( GameWindow *listbox, Bool useSystemMaps, Bool isMultiplayer, AsciiString mapToSelect = AsciiString::TheEmptyString );
Int populateMapListboxNoReset( GameWindow *listbox, Bool useSystemMaps, Bool isMultiplayer, AsciiString mapToSelect = AsciiString::TheEmptyString );
Bool isValidMap( AsciiString mapName, Bool isMultiplayer );
Image *getMapPreviewImage( AsciiString mapName );
AsciiString getDefaultMap( Bool isMultiplayer );
AsciiString getDefaultOfficialMap();
Bool isOfficialMap( AsciiString mapName );
Bool parseMapPreviewChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
void findDrawPositions( Int startX, Int startY, Int width, Int height, Region3D extent, ICoord2D *ul, ICoord2D *lr );
Bool WouldMapTransfer( const AsciiString& mapName );
#include "GameLogic/GameLogic.h"
#include "GameLogic/FPUControl.h"
#include "GameNetwork/GameInfo.h"
#include "GameNetwork/NetworkDefs.h"
// Preserve STLport operations inline without unused external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline ICoord2D *
__copy_backward_ptrs<ICoord2D *, ICoord2D *>(ICoord2D *__first, ICoord2D *__last, ICoord2D *__result, const __false_type &)
{
    return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (ptrdiff_t *)0);
}
template <> __declspec(dllimport) __forceinline ICoord2D *
vector<ICoord2D, allocator<ICoord2D> >::erase(ICoord2D *__first, ICoord2D *__last)
{
    pointer __i = __copy_ptrs(__last, this->_M_finish, __first, _TrivialAss());
    _Destroy(__i, this->_M_finish);
    this->_M_finish = __i;
    return __first;
}
}
// bfme link decl-only begin
namespace _STL { template <> list<Coord3D, allocator<Coord3D> >::list(allocator<Coord3D> const &); }
namespace _STL { template <> _List_node<Coord3D> * list<Coord3D, allocator<Coord3D> >::_M_create_node(Coord3D const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<UnicodeString, _Const_traits<UnicodeString> >, bool> set<UnicodeString, rts::less_than_nocase<UnicodeString>, allocator<UnicodeString> >::insert(UnicodeString const &); }
namespace _STL { template <> _List_base<Coord3D, allocator<Coord3D> >::_List_base(allocator<Coord3D> const &); }
namespace _STL { template <> list<Coord3D, allocator<Coord3D> >::list(list<Coord3D, allocator<Coord3D> > const &); }
namespace _STL { template <> map<AsciiString, Coord3D, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::map(map<AsciiString, Coord3D, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > > const &); }
namespace _STL { template <> _List_base<Coord3D, allocator<Coord3D> >::~_List_base(); }
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > > & _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::operator=(_Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > > const &); }
namespace _STL { template <> list<Coord3D, allocator<Coord3D> > & list<Coord3D, allocator<Coord3D> >::operator=(list<Coord3D, allocator<Coord3D> > const &); }
namespace _STL { template <> map<AsciiString, Coord3D, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > > & map<AsciiString, Coord3D, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::operator=(map<AsciiString, Coord3D, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > > const &); }
namespace _STL { template <> void _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::_M_erase(_Rb_tree_node<pair<AsciiString const, Coord3D> > *); }
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
namespace _STL { template <> void _List_base<Coord3D, allocator<Coord3D> >::clear(); }
namespace _STL { template <> void _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::clear(); }
namespace _STL { template <> _List_iterator<Coord3D, _Nonconst_traits<Coord3D> > list<Coord3D, allocator<Coord3D> >::insert(_List_iterator<Coord3D, _Nonconst_traits<Coord3D> >, Coord3D const &); }
namespace _STL { template <> void list<Coord3D, allocator<Coord3D> >::push_back(Coord3D const &); }
// The canonical map lookup is already emitted by GameEngineInit and the
// matched map-cache consumers. Do not offer this TU's shorter wrapper.
namespace _STL {
typedef _Rb_tree<AsciiString, pair<const AsciiString, MapMetaData>,
    _Select1st<pair<const AsciiString, MapMetaData> >, less<AsciiString>,
    allocator<pair<const AsciiString, MapMetaData> > > MapUtilMetadataTree;
template <>
_Rb_tree_node<pair<const AsciiString, MapMetaData> > *
MapUtilMetadataTree::_M_lower_bound(const AsciiString &) const;
template <> template <>
__declspec(dllimport) __forceinline
MapUtilMetadataTree::iterator MapUtilMetadataTree::find<AsciiString>(const AsciiString &key)
{
    return iterator(_M_find(key));
}
}
// Retail calls the map's out-of-line operator[] (0x00304DC7, an /O1 copy);
// expanding it here emits a non-retail pair<const AsciiString, MapMetaData>
// destructor that the link would keep ahead of the retail one.
namespace _STL { template <> MapMetaData & map<AsciiString, MapMetaData, less<AsciiString>, allocator<pair<AsciiString const, MapMetaData> > >::operator[](AsciiString const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct Coord3D;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<AsciiString const ,Coord3D> > >::deallocate(_Rb_tree_node<pair<AsciiString const ,Coord3D> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??R?$less@VUnicodeString@@@_STL@@QBE_NABVUnicodeString@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class UnicodeString;
namespace _STL { template <> bool less<UnicodeString>::operator()(UnicodeString const &,UnicodeString const &) const; }
// Suppress this TU's non-retail copy of ??R?$less@VAsciiString@@@_STL@@QBE_NABVAsciiString@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> bool less<AsciiString>::operator()(AsciiString const &,AsciiString const &) const; }
// Suppress this TU's non-retail copy of ?test@?$bitset@$0HE@@_STL@@QBE_NI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool bitset<116>::test(unsigned int) const; }
// Suppress this TU's non-retail copy of ?_Unchecked_test@?$bitset@$0HE@@_STL@@QBE_NI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool bitset<116>::_Unchecked_test(unsigned int) const; }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
static char *mapExtension = ".map";

extern "C" Int m_width;						///< Height map width.
extern "C" Int m_height;					///< Height map height (y size of array).
extern "C" Int m_borderSize;			///< Non-playable border area.
static std::vector<ICoord2D> m_boundaries;	///< All the boundaries we use for the map
static Int m_dataSize = 0;				///< size of m_data.
static UnsignedByte *m_data = 0;	///< array of z(height) values in the height map.
extern "C" { Dict worldDict = 0; }

extern "C" { WaypointMap *m_waypoints = 0; }
extern "C" { Coord3DList	m_supplyPositions; }
extern "C" { Coord3DList	m_techPositions; }

static Int m_mapDX = 0;
static Int m_mapDY = 0;

#pragma optimize("s", on)
Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	worldDict = file.readDict();
	return true;
}

#pragma optimize("s", on)
void resetMap( void )
{
	if (m_data)
	{
		delete[] m_data;
		m_data = 0;
	}

	if (m_waypoints)
	{
		delete m_waypoints;
		m_waypoints = 0;
	}
	m_techPositions.clear();
	m_supplyPositions.clear();
}
#pragma optimize("", on)

static void getExtent( Region3D *extent )
{
	extent->lo.x = 0.0f;

	extent->lo.y = 0.0f;

	// Note - m_mapDX & Y are the number of height map grids wide, so we have to
	// multiply by the grid width.
	extent->hi.x = m_mapDX*MAP_XY_FACTOR;
	extent->hi.y = m_mapDY*MAP_XY_FACTOR;

	extent->lo.z = 0;
	extent->hi.z = 0;
}

// getExtent's row (0x003000B5) takes extent in EAX, the convention the
// compiler gives a static only when it sees every caller, and it emits the
// out-of-line copy only when a later function references it. Retail's caller
// is MapCache::addMap (0x00304E64, which inlines it). That body is still in
// MapCacheAddMap.cpp until MapUtil.cpp's TU merge, so this anchor stands in for
// it. Not retail code (LINK-181).
void bfmeMapUtilGetExtentAnchor( Region3D *extent );
// ?bfmeMapUtilGetExtentAnchor absent-from-retail
void bfmeMapUtilGetExtentAnchor( Region3D *extent )
{
	getExtent( extent );
}

//-------------------------------------------------------------------------------

// WaypointMap::update is recovered in WaypointMapUpdate.cpp (302B7D/260).

const char * MapCache::m_mapCacheName = "MapCache.ini";

static __forceinline void concatStringBase(AsciiString &dst, const AsciiString &src)
{
	((StringBase<char> *)&dst)->concat(*(const StringBase<char> *)&src);
}

// ?getMapDir@MapCache@@ present-unmatched
AsciiString MapCache::getMapDir() const 
{ 
	return AsciiString("Maps"); 
}

// ?getUserMapDir@MapCache@@ present-unmatched
AsciiString MapCache::getUserMapDir() const
{
	AsciiString tmp = TheGlobalData->getPath_UserData();
	concatStringBase(tmp, getMapDir());
	return tmp;
}

// MapCache::getMapExtension is rowed at 0x003004A5 in
// Common/RvaAsciiStringNameGetters.cpp.



// MapCache::addMap is retail's 0x00304E64 body in MapCacheAddMap.cpp. Zero
// Hour's copy, and the static calcCRC/loadMap/parser chain only it reached,
// was a second strong addMap that kept MapCacheAddMap.cpp and
// MapCacheLoadUserMapsBFME2.cpp from linking. Retail's own calcCRC, loadMap,
// ParseObjectDataChunk, ParseObjectsDataChunk and ParseSizeOnlyInChunk are the
// external rows at 0x0030050E, 0x00302F2B, 0x00302907, 0x00302B06 and
// 0x00302F1B.
//
// The waypoint tree members below are this file's rows 0x0016DB20, 0x0016D590,
// 0x0016D760 and 0x0073B560 (WaypointMap is map<AsciiString, Coord3D>); the
// chain above used to emit them implicitly, so they are instantiated here.
namespace _STL {
template _Rb_tree<AsciiString, pair<const AsciiString, Coord3D>,
    _Select1st<pair<const AsciiString, Coord3D> >, less<AsciiString>,
    allocator<pair<const AsciiString, Coord3D> > >::_Rb_tree(
        const less<AsciiString> &, const allocator<pair<const AsciiString, Coord3D> > &);
template _Rb_tree_base<pair<const AsciiString, Coord3D>,
    allocator<pair<const AsciiString, Coord3D> > >::_Rb_tree_base(
        const allocator<pair<const AsciiString, Coord3D> > &);
template _Rb_tree_node<pair<const AsciiString, Coord3D> > *
_Rb_tree<AsciiString, pair<const AsciiString, Coord3D>,
    _Select1st<pair<const AsciiString, Coord3D> >, less<AsciiString>,
    allocator<pair<const AsciiString, Coord3D> > >::_M_create_node(
        const pair<const AsciiString, Coord3D> &);
template _Rb_tree_node<pair<const AsciiString, Coord3D> > *
allocator<_Rb_tree_node<pair<const AsciiString, Coord3D> > >::allocate(
    size_t, const void *) const;
// The vector<ICoord2D> growth path row 0x00181770 was emitted here through
// the dropped chain's _M_fill_insert; it stays this file's row until its
// approved TU (dx8fvf.cpp) takes it, so it is instantiated here too.
template void vector<ICoord2D, allocator<ICoord2D> >::_M_insert_overflow(
    ICoord2D *, const ICoord2D &, const __false_type &, size_t, bool);
// The map<UnicodeString, AsciiString> constructor rows 0x00157020,
// 0x00620E90 and 0x00620720 were emitted here by Zero Hour's
// populateMapListboxNoReset (dropped below). They stay this file's rows, as
// before, so they are instantiated here too.
template _Rb_tree<UnicodeString, pair<const UnicodeString, AsciiString>,
    _Select1st<pair<const UnicodeString, AsciiString> >, less<UnicodeString>,
    allocator<pair<const UnicodeString, AsciiString> > >::_Rb_tree(
        const less<UnicodeString> &, const allocator<pair<const UnicodeString, AsciiString> > &);
template _Rb_tree_base<pair<const UnicodeString, AsciiString>,
    allocator<pair<const UnicodeString, AsciiString> > >::_Rb_tree_base(
        const allocator<pair<const UnicodeString, AsciiString> > &);
template map<UnicodeString, AsciiString, less<UnicodeString>,
    allocator<pair<const UnicodeString, AsciiString> > >::map();
// PeerThread.cpp binds __default_constructed<AsciiString> to this file's copy,
// which the same Zero Hour body emitted.
template AsciiString __default_constructed<AsciiString>(AsciiString *);
}

MapCache *TheMapCache = NULL;

// PUBLIC FUNCTIONS //////////////////////////////////////////////////////////////////////////////

Bool WouldMapTransfer( const AsciiString& mapName )
{
	return ((const StringBase<char> *)&mapName)->startsWithNoCase(
		TheMapCache->getUserMapDir().str());
}

// NOTE (link lane): Zero Hour's populateMapListboxNoReset and populateMapListbox
// (AsciiString taken by value) were dropped. No row holds them, and no other
// object references them. BFME 2's are the rows 0x00304BA9 and 0x00304744 in
// MapUtilGetDefaultMap.cpp, which take const AsciiString &. The Zero Hour bodies
// called SkirmishBattleHonors' constructor and getEnduranceMedal,
// GadgetListBoxGetBottomVisibleEntry and UnicodeString::set, none of which
// BFME 2 provides under those spellings (LINK-181).
	


//-------------------------------------------------------------------------------------------------
/** Validate a map */
//-------------------------------------------------------------------------------------------------
#pragma optimize("s", on)
Bool isValidMap( AsciiString mapName, Bool isMultiplayer )
{
	if(!TheMapCache || mapName.isEmpty())
		return FALSE;
	TheMapCache->updateCache();

	((StringBase<char> *)&mapName)->toLower();
	MapCache::iterator it = TheMapCache->find(mapName);
	if (it != TheMapCache->end())
	{
		if (isMultiplayer == it->second.m_isMultiplayer)
		{
			return TRUE;
		}
	}

	return FALSE;
}  // end isValidMap
#pragma optimize("", on)

AsciiString getDefaultOfficialMap()
{
	if(!TheMapCache)
		return AsciiString::TheEmptyString;
	TheMapCache->updateCache();

	MapCache::iterator it = TheMapCache->begin();
	while (it != TheMapCache->end())
	{
		if (it->second.m_isMultiplayer && it->second.m_isOfficial)
		{
			return it->first;
		}
		++it;
	}
	return AsciiString::TheEmptyString;
}


Bool isOfficialMap( AsciiString mapName )
{
	if(!TheMapCache || mapName.isEmpty())
		return FALSE;
	TheMapCache->updateCache();
	((StringBase<char> *)&mapName)->toLower();
	MapCache::iterator it = TheMapCache->find(mapName);
	if (it != TheMapCache->end())
		return it->second.m_isOfficial;
	return FALSE;
}


// MapCache::findMap: defined in MapCacheFindMap.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
/** Embed the pristine map into the xfer stream */
// ------------------------------------------------------------------------------------------------
static void copyFromBigToDir( const AsciiString& infile, const AsciiString& outfile )
{
	// open the map file

	File *file = TheFileSystem->openFile( infile.str(), File::READ | File::BINARY );
	if( file == NULL )
	{
		DEBUG_CRASH(( "copyFromBigToDir - Error opening source file '%s'\n", infile.str() ));
		throw SC_INVALID_DATA;
	} // end if

	// how big is the map file
	Int fileSize = file->seek( 0, File::END );


	// rewind to beginning of file
	file->seek( 0, File::START );

	// allocate buffer big enough to hold the entire map file
	char *buffer = NEW char[ fileSize ];
	if( buffer == NULL )
	{
		DEBUG_CRASH(( "copyFromBigToDir - Unable to allocate buffer for file '%s'\n", infile.str() ));
		throw SC_INVALID_DATA;
	} // end if

	// copy the file to the buffer
	if( file->read( buffer, fileSize ) < fileSize )
	{
		DEBUG_CRASH(( "copyFromBigToDir - Error reading from file '%s'\n", infile.str() ));
		throw SC_INVALID_DATA;
	} // end if
	// close the BIG file
	file->close();
	
	File *filenew = TheFileSystem->openFile( outfile.str(), File::WRITE | File::CREATE | File::BINARY );
	
	if( !filenew || filenew->write(buffer, fileSize) < fileSize)
	{
		DEBUG_CRASH(( "copyFromBigToDir - Error writing to file '%s'\n", outfile.str() ));
		throw SC_INVALID_DATA;
	} // end if

	filenew->close();

	// delete the buffer
	delete [] buffer;
} // end embedPristineMap

// Retail owns getMapPreviewImage as a single 967B body at 0x00300EB4, rowed and
// byte-matched in MapPreviewImage.cpp (the BF1 f98983a7 donor port). This unit
// used to carry a second, divergent copy of the same function, so link.exe kept
// this one and MapPreviewImage.cpp's rowed retail bytes never entered the link
// (LNK2005 plus a COMDAT whose kept copy was proven not retail's). Declaring it
// here leaves the rowed copy in MapPreviewImage.cpp as the only definition.
Image *getMapPreviewImage( AsciiString mapName );

Bool parseMapPreviewChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
/*
	ICoord2D size;
	
	SurfaceClass *surface;
	size.x = file.readInt();
	size.y = file.readInt();


	surface = (TextureClass *)mapPreviewImage->getRawTextureData()->Get_Surface_Level();
	//texture->Get_Surface_Level();
	
	DEBUG_LOG(("BeginMapPreviewInfo\n"));
	UnsignedInt *buffer = new UnsignedInt[size.x * size.y];
	Int x,y;
	for (y=0; y<size.y; y++) {
		for(x = 0; x< size.x; x++)
		{
			surface->DrawPixel( x, y, file.readInt() );
			buffer[y + x] = file.readInt();
			DEBUG_LOG(("x:%d, y:%d, %X\n", x, y, buffer[y + x]));
		}
	}
	mapPreviewImage->setRawTextureData(buffer);
	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Unexpected data left over."));
	DEBUG_LOG(("EndMapPreviewInfo\n"));
	REF_PTR_RELEASE(surface);
	return true;
*/
	return FALSE;
}

#pragma optimize("s", on)
void findDrawPositions( Int startX, Int startY, Int width, Int height, Region3D extent,
															 ICoord2D *ul, ICoord2D *lr )
{

	Real ratioWidth;
	Real ratioHeight;
	Coord2D radar;
	ratioWidth = extent.width()/(width * 1.0f);
	ratioHeight = extent.height()/(height* 1.0f);
	
	if( ratioWidth >= ratioHeight)
	{
		radar.x = extent.width() / ratioWidth;
		radar.y = extent.height()/ ratioWidth;
		ul->x = 0;
		ul->y = (height - radar.y) / 2.0f;
		lr->x = radar.x;
		lr->y = height - ul->y;
	}
	else
	{
		radar.x = extent.width() / ratioHeight;
		radar.y = extent.height()/ ratioHeight;
		ul->x = (width - radar.x ) / 2.0f;
		ul->y = 0;
		lr->x = width - ul->x;
		lr->y = radar.y;
	}

	// make them pixel positions
	ul->x += startX;
	ul->y += startY;
	lr->x += startX;
	lr->y += startY;

}  // end findDrawPositions
#pragma optimize("", on)
