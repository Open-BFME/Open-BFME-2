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

static UnsignedInt calcCRC( AsciiString dirName, AsciiString fname )
{
	CRC theCRC;
	theCRC.clear();

	// Try the official map dir
	AsciiString asciiFile;
	char	tempBuf[_MAX_PATH];
	char	filenameBuf[_MAX_PATH];
	int length = 0;
	strcpy(tempBuf, fname.str());
	length = strlen( tempBuf );
	if( length >= 4 )
	{
		memset( filenameBuf, '\0', _MAX_PATH);
		strncpy( filenameBuf, tempBuf, length - 4);
	}

	File *fp;
	asciiFile = fname;
	fp = TheFileSystem->openFile(asciiFile.str(), File::READ);
	if( !fp )
	{
		DEBUG_CRASH(("Couldn't open '%s'\n", fname.str()));
		return 0;
	}

	UnsignedByte buf[4096];
	Int num;
	while ( (num=fp->read(buf, 4096)) > 0 )
	{
		theCRC.computeCRC(buf, num);
	}

	fp->close();
	fp = NULL;

	return theCRC.get();
}

static Bool ParseObjectDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Bool readDict = info->version >= K_OBJECTS_VERSION_2;

	Coord3D loc;
	loc.x = file.readReal();
	loc.y = file.readReal();
	loc.z = file.readReal();
	if (info->version <= K_OBJECTS_VERSION_2) 
	{
		loc.z = 0;
	}

	Real angle = file.readReal();
	Int flags = file.readInt(); 
	AsciiString name = file.readAsciiString();
	Dict d;
	if (readDict)
	{
		d = file.readDict();
	}
	MapObject *pThisOne;
	
	// create the map object
	pThisOne = newInstance( MapObject )( loc, name, angle, flags, &d, 
														TheThingFactory->findTemplate( name, FALSE ) );

//DEBUG_LOG(("obj %s owner %s\n",name.str(),d.getAsciiString(TheKey_originalOwner).str()));

	if (pThisOne->getProperties()->getType(TheKey_waypointID) == Dict::DICT_INT)
	{
		pThisOne->setIsWaypoint();

		// grab useful info
		(*m_waypoints)[pThisOne->getWaypointName()] = loc;
	}
	else if (pThisOne->getThingTemplate() && pThisOne->getThingTemplate()->isKindOf(KINDOF_TECH_BUILDING))
	{
		m_techPositions.push_back(loc);
	}
	else if (pThisOne->getThingTemplate() && pThisOne->getThingTemplate()->isKindOf(KINDOF_SUPPLY_SOURCE_ON_PREVIEW))
	{
		m_supplyPositions.push_back(loc);
	}

	pThisOne->deleteInstance();
	return TRUE;
}

static Bool ParseObjectsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	file.m_currentObject = NULL;
	file.registerParser( AsciiString("Object"), info->label, ParseObjectDataChunk );
	return (file.parse(userData));
}

#pragma optimize("s", on)
Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	worldDict = file.readDict();
	return true;
}
#pragma optimize("", on)

static Bool ParseSizeOnly(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	m_width = file.readInt();
	m_height = file.readInt();
	if (info->version >= K_HEIGHT_MAP_VERSION_3) {
		m_borderSize = file.readInt();
	} else {
		m_borderSize = 0;
	}

	if (info->version >= K_HEIGHT_MAP_VERSION_4) {
		Int numBorders = file.readInt();
		m_boundaries.resize(numBorders);
		for (int i = 0; i < numBorders; ++i) {
			m_boundaries[i].x = file.readInt();
			m_boundaries[i].y = file.readInt();
		}
	}
	return true;

	m_dataSize = file.readInt();
	m_data = NEW UnsignedByte[m_dataSize];	// pool[]ify
	if (m_dataSize <= 0 || (m_dataSize != (m_width*m_height))) {
		throw ERROR_CORRUPT_FILE_FORMAT	;
	}
	file.readArrayOfBytes((char *)m_data, m_dataSize);
	// Resize me. 
	if (info->version == K_HEIGHT_MAP_VERSION_1) {
		Int newWidth = (m_width+1)/2;
		Int newHeight = (m_height+1)/2;
		Int i, j;
		for (i=0; i<newHeight; i++) {
			for (j=0; j<newWidth; j++) {
				m_data[i*newWidth+j] = m_data[2*i*m_width+2*j];
			}
		}
		m_width = newWidth;
		m_height = newHeight;
	}
	return true;
}

static Bool ParseSizeOnlyInChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	return ParseSizeOnly(file, info, userData);
}

static Bool loadMap( AsciiString filename )
{
	char	tempBuf[_MAX_PATH];
	char	filenameBuf[_MAX_PATH];
	AsciiString asciiFile;
	int length = 0;

	strcpy(tempBuf, filename.str());

	length = strlen( tempBuf );
	if( length >= 4 )
	{
		memset( filenameBuf, '\0', _MAX_PATH);
		strncpy( filenameBuf, tempBuf, length - 4);
	}

	CachedFileInputStream fileStrm;

	asciiFile = filename;
	if( !fileStrm.open(asciiFile) )
	{
		return FALSE;
	}

	ChunkInputStream *pStrm = &fileStrm;

	DataChunkInput file( pStrm );

	m_waypoints = NEW WaypointMap;

	file.registerParser( AsciiString("HeightMapData"), AsciiString::TheEmptyString, ParseSizeOnlyInChunk );
	file.registerParser( AsciiString("WorldInfo"), AsciiString::TheEmptyString, ParseWorldDictDataChunk );
	file.registerParser( AsciiString("ObjectsList"), AsciiString::TheEmptyString, ParseObjectsDataChunk );
	if (!file.parse(NULL)) {
		throw(ERROR_CORRUPT_FILE_FORMAT);
	}

	m_mapDX = m_width  - 2*m_borderSize;
	m_mapDY = m_height - 2*m_borderSize;

	return TRUE;
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



//Bool MapCache::addMap( AsciiString dirName, AsciiString fname, WinTimeStamp timestamp, UnsignedInt filesize, Bool isOfficial )
// ?addMap@MapCache@@ present-unmatched
Bool MapCache::addMap( AsciiString dirName, AsciiString fname, FileInfo *fileInfo, Bool isOfficial)
{
	if (fileInfo == NULL) {
		return FALSE;
	}

	AsciiString lowerFname;
	lowerFname = fname;
	((StringBase<char> *)&lowerFname)->toLower();
	MapCache::iterator it = find(lowerFname);

	MapMetaData md;
	UnsignedInt filesize = fileInfo->sizeLow;

	if (it != end())
	{
		// Found the map in our cache.  Check to see if it has changed.
		md = it->second;

		if ((md.m_filesize == filesize) &&
				(md.m_CRC != 0))
		{
			// Force a lookup so that we don't display the English localization in all builds.
			if (md.m_nameLookupTag.isEmpty())
			{
				// unofficial maps or maps without names
				AsciiString tempdisplayname;
				tempdisplayname = ((const StringBase<char> *)&fname)->reverseFind('\\') + 1;
				(*this)[lowerFname].m_displayName.translate(tempdisplayname);
				if (md.m_numPlayers >= 2)
				{
					UnicodeString extension;
					extension.format(L" (%d)", md.m_numPlayers);
					(*this)[lowerFname].m_displayName.concat(extension);
				}
			}
			else
			{
				// official maps with name tags
				(*this)[lowerFname].m_displayName = TheGameText->fetch(md.m_nameLookupTag);
				if (md.m_numPlayers >= 2)
				{
					UnicodeString extension;
					extension.format(L" (%d)", md.m_numPlayers);
					(*this)[lowerFname].m_displayName.concat(extension);
				}
			}
//			DEBUG_LOG(("MapCache::addMap - found match for map %s\n", lowerFname.str()));
			return FALSE;	// OK, it checks out.
		}
		DEBUG_LOG(("%s didn't match file in MapCache\n", fname.str()));
		DEBUG_LOG(("size: %d / %d\n", filesize, md.m_filesize));
		DEBUG_LOG(("time1: %d / %d\n", fileInfo->timestampHigh, md.m_timestamp.m_highTimeStamp));
		DEBUG_LOG(("time2: %d / %d\n", fileInfo->timestampLow, md.m_timestamp.m_lowTimeStamp));
//		DEBUG_LOG(("size: %d / %d\n", filesize, md.m_filesize));
//		DEBUG_LOG(("time1: %d / %d\n", timestamp.m_highTimeStamp, md.m_timestamp.m_highTimeStamp));
//		DEBUG_LOG(("time2: %d / %d\n", timestamp.m_lowTimeStamp, md.m_timestamp.m_lowTimeStamp));
	}

	DEBUG_LOG(("MapCache::addMap(): caching '%s' because '%s' was not found\n", fname.str(), lowerFname.str()));

	loadMap(fname); // Just load for querying the data, since we aren't playing this map.

	// The map is now loaded.  Pick out what we need.
	md.m_fileName = lowerFname;
	md.m_filesize = filesize;
	md.m_isOfficial = isOfficial;
	md.m_waypoints.update();
	md.m_numPlayers = md.m_waypoints.m_numStartSpots;
	md.m_isMultiplayer = (md.m_numPlayers >= 2);
	md.m_timestamp.m_highTimeStamp = fileInfo->timestampHigh;
	md.m_timestamp.m_lowTimeStamp = fileInfo->timestampLow;
	md.m_supplyPositions = m_supplyPositions;
	md.m_techPositions = m_techPositions;
	md.m_CRC = calcCRC(dirName, fname);

	Bool exists = false;
	AsciiString munkee = worldDict.getAsciiString(TheKey_mapName, &exists);
	md.m_nameLookupTag = munkee;
	if (!exists || munkee.isEmpty())
	{
		DEBUG_LOG(("Missing TheKey_mapName!\n"));
		AsciiString tempdisplayname;
		tempdisplayname = ((const StringBase<char> *)&fname)->reverseFind('\\') + 1;
		md.m_displayName.translate(tempdisplayname);
		if (md.m_numPlayers >= 2)
		{
			UnicodeString extension;
			extension.format(L" (%d)", md.m_numPlayers);
			md.m_displayName.concat(extension);
		}
		TheGameText->reset();
	}
	else
	{
		AsciiString stringFileName;
		stringFileName.format("%s\\%s", dirName.str(), fname.str());
		for (Int i=0; i<4; ++i)
			stringFileName.removeLastChar();
		((StringBase<char> *)&stringFileName)->concat("\\map.str");
		TheGameText->initMapStringFile(stringFileName);
		md.m_displayName = TheGameText->fetch(munkee);
		if (md.m_numPlayers >= 2)
		{
			UnicodeString extension;
			extension.format(L" (%d)", md.m_numPlayers);
			md.m_displayName.concat(extension);
		}
		DEBUG_LOG(("Map name is now '%ls'\n", md.m_displayName.str()));
		TheGameText->reset();
	}

	getExtent(&(md.m_extent));

	(*this)[lowerFname] = md;

	DEBUG_LOG(("  filesize = %d bytes\n", md.m_filesize));
	DEBUG_LOG(("  displayName = %ls\n", md.m_displayName.str()));
	DEBUG_LOG(("  CRC = %X\n", md.m_CRC));
	DEBUG_LOG(("  timestamp = %d\n", md.m_timestamp));
	DEBUG_LOG(("  isOfficial = %s\n", (md.m_isOfficial)?"yes":"no"));

	DEBUG_LOG(("  isMultiplayer = %s\n", (md.m_isMultiplayer)?"yes":"no"));
	DEBUG_LOG(("  numPlayers = %d\n", md.m_numPlayers));

	DEBUG_LOG(("  extent = (%2.2f,%2.2f) -> (%2.2f,%2.2f)\n",
		md.m_extent.lo.x, md.m_extent.lo.y,
		md.m_extent.hi.x, md.m_extent.hi.y));

	Coord3D pos;
	WaypointMap::iterator itw = md.m_waypoints.begin();
	while (itw != md.m_waypoints.end())
	{
		pos = itw->second;
		DEBUG_LOG(("    waypoint %s: (%2.2f,%2.2f)\n", itw->first.str(), pos.x, pos.y));
		++itw;
	}

	resetMap();

	return TRUE;
}

MapCache *TheMapCache = NULL;

// PUBLIC FUNCTIONS //////////////////////////////////////////////////////////////////////////////

Bool WouldMapTransfer( const AsciiString& mapName )
{
	return ((const StringBase<char> *)&mapName)->startsWithNoCase(
		TheMapCache->getUserMapDir().str());
}

//-------------------------------------------------------------------------------------------------
/** Load the listbox with all the map files available to play */
//-------------------------------------------------------------------------------------------------
Int populateMapListboxNoReset( GameWindow *listbox, Bool useSystemMaps, Bool isMultiplayer, AsciiString mapToSelect )
{
	if(!TheMapCache)
		return -1;

	if (!listbox)
		return -1;
	
	// reset the listbox content
	//GadgetListBoxReset( listbox );
	
	Int numColumns = GadgetListBoxGetNumColumns( listbox );
	const Image *easyImage = NULL;
	const Image *mediumImage = NULL;
	const Image *brutalImage = NULL;
	const Image *maxBrutalImage = NULL;
	SkirmishBattleHonors *battleHonors = NULL;
	Int w = 10, h = 10;
	if (numColumns > 1)
	{
		easyImage = TheMappedImageCollection->findImageByName("Star-Bronze");
		mediumImage = TheMappedImageCollection->findImageByName("Star-Silver");
		brutalImage = TheMappedImageCollection->findImageByName("Star-Gold");
		maxBrutalImage = TheMappedImageCollection->findImageByName("RedYell_Star");
		battleHonors = new SkirmishBattleHonors;

		w = (brutalImage)?brutalImage->getImageWidth():10;
		w = min(GadgetListBoxGetColumnWidth(listbox, 0), w);
		h = w;
	}

	Color color = GameMakeColor( 255, 255, 255, 255 );
	UnicodeString mapDisplayName;

	Int selectionIndex = 0; // always select *something*

	MapCache::iterator it = TheMapCache->begin();
	AsciiString mapDir;
	if (useSystemMaps)
	{
		mapDir = TheMapCache->getMapDir();
	}
	else
	{
		mapDir = TheGlobalData->getPath_UserData();
		concatStringBase(mapDir, TheMapCache->getMapDir());
	}
	((StringBase<char> *)&mapDir)->toLower();

typedef std::set<UnicodeString, rts::less_than_nocase<UnicodeString> > MapNameList;
typedef MapNameList::iterator MapNameListIter;

typedef std::map<UnicodeString, AsciiString> MapDisplayToFileNameList;
typedef MapDisplayToFileNameList::iterator MapDisplayToFileNameListIter;

	MapNameList tempCache;
	MapDisplayToFileNameList filenameMap;
	UnsignedInt numMapsListed = 0;
	UnsignedInt curNumPlayersInMap = 0;

	while (numMapsListed < TheMapCache->size()) {

		DEBUG_LOG(("Adding maps with %d players\n", curNumPlayersInMap));
		it = TheMapCache->begin();
		while (it != TheMapCache->end()) {
			const MapMetaData *md = &(it->second);
			if (md != NULL) {
				if (md->m_numPlayers == curNumPlayersInMap) {
					tempCache.insert(it->second.m_displayName);
					filenameMap[it->second.m_displayName] = it->first;
					DEBUG_LOG(("Adding map %s to temp cache.\n", it->first.str()));
					++numMapsListed;
				}
			}
			++it;
		}

		MapNameListIter tempit = tempCache.begin();

		while (tempit != tempCache.end())
		{

			AsciiString asciiMapName;
			asciiMapName = filenameMap[*tempit];
			it = TheMapCache->find(asciiMapName);
			/*
			if (it != TheMapCache->end())
			{
				DEBUG_LOG(("populateMapListbox(): looking at %s (displayName = %ls), mp = %d (== %d?) mapDir=%s (ok=%d)\n",
					it->first.str(), it->second.m_displayName.str(), it->second.m_isMultiplayer, isMultiplayer,
					mapDir.str(), it->first.startsWith(mapDir.str())));
			}
			*/
			
			//Patch 1.03 -- Purposely filter out these broken maps that exist in Generals.
			if( !asciiMapName.compare( "maps\\armored fury\\armored fury.map" ) || 
				!asciiMapName.compare( "maps\\scorched earth\\scorched earth.map" ) )
			{
				++tempit;
				continue;
			}

			DEBUG_ASSERTCRASH(it != TheMapCache->end(), ("Map %s not found in map cache.", *tempit));
			if (((const StringBase<char> *)&it->first)->startsWithNoCase(mapDir.str()) && isMultiplayer == it->second.m_isMultiplayer && !it->second.m_displayName.isEmpty())
			{
				/// @todo: mapDisplayName = TheGameText->fetch(it->second.m_displayName.str());
				mapDisplayName = it->second.m_displayName;
				Int index = -1;
				Int imageItemData = -1;
				if (numColumns > 1 && it->second.m_isMultiplayer)
				{
					Int numEasy = battleHonors->getEnduranceMedal(it->first.str(), SLOT_EASY_AI);
					Int numMedium = battleHonors->getEnduranceMedal(it->first.str(), SLOT_MED_AI);
					Int numBrutal = battleHonors->getEnduranceMedal(it->first.str(), SLOT_BRUTAL_AI);
					if (numBrutal)
					{
						int maxBrutalSlots = it->second.m_numPlayers - 1;
						if (numBrutal == maxBrutalSlots)
						{
							index = GadgetListBoxAddEntryImage( listbox, maxBrutalImage, index, 0, w, h, TRUE);
							imageItemData = 4;
						}
						else	
						{
							index = GadgetListBoxAddEntryImage( listbox, brutalImage, index, 0, w, h, TRUE);
							imageItemData = 3;
						}
					}
					else if (numMedium)
					{
						imageItemData = 2;
						index = GadgetListBoxAddEntryImage( listbox, mediumImage, index, 0, w, h, TRUE);
					}
					else if (numEasy)
					{
						imageItemData = 1;
						index = GadgetListBoxAddEntryImage( listbox, easyImage, index, 0, w, h, TRUE);
					}
					else
					{
						imageItemData = 0;
						index = GadgetListBoxAddEntryImage( listbox, NULL, index, 0, w, h, TRUE);
					}
				}
				index = GadgetListBoxAddEntryText( listbox, mapDisplayName, color, index, numColumns-1 );

				if (it->first == mapToSelect)
				{
					selectionIndex = index;
				}

				// now set the char* as the item data.  this works because the map cache isn't being
				// modified while a map listbox is up.
				GadgetListBoxSetItemData( listbox, (void *)(it->first.str()), index );

				if (numColumns > 1)
				{
					GadgetListBoxSetItemData( listbox, (void *)imageItemData, index, 1 );
				}
			}
			++tempit;
		}

		tempCache.clear();
		filenameMap.clear();
		++curNumPlayersInMap;
	}

	if (battleHonors)
	{
		delete battleHonors;
		battleHonors = NULL;
	}

	GadgetListBoxSetSelected(listbox, &selectionIndex, 1);
	if (selectionIndex >= 0)
	{
		Int topIndex = GadgetListBoxGetTopVisibleEntry(listbox);
		Int bottomIndex = GadgetListBoxGetBottomVisibleEntry(listbox);
		Int rowsOnScreen = bottomIndex - topIndex;

		if (selectionIndex >= bottomIndex)
		{
			Int newTop = max( 0, selectionIndex - max( 1, rowsOnScreen / 2 ) ); 
		//The trouble is that rowsonscreen/2 can be zero if bottom is 1 and top is zero
			GadgetListBoxSetTopVisibleEntry( listbox, newTop );
		}
	}
	return selectionIndex;

}  // end loadMapListbox

//-------------------------------------------------------------------------------------------------
/** Load the listbox with all the map files available to play */
//-------------------------------------------------------------------------------------------------
Int populateMapListbox( GameWindow *listbox, Bool useSystemMaps, Bool isMultiplayer, AsciiString mapToSelect )
{
	if(!TheMapCache)
		return -1;

	if (!listbox)
		return -1;
	
	// reset the listbox content
	GadgetListBoxReset( listbox );

	return populateMapListboxNoReset( listbox, useSystemMaps, isMultiplayer, mapToSelect );
}
	


//-------------------------------------------------------------------------------------------------
/** Validate a map */
//-------------------------------------------------------------------------------------------------
#pragma optimize("t", off)
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
